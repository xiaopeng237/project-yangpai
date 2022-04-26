//
// Created by lenovo on 2019/10/24.
//

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include "yangpai_service.h"

#define QUEUE_ID_REQUEST  0
#define QUEUE_ID_RESPONSE 1
#define QUEUE_ID_SIGNAL   2
#define QUEUE_ID_CALL     3
#define QUEUE_ID_REPLY    4
#define QUEUE_ID_EVENT    5


DBusConnection *gp_Connection;
static pthread_cond_t       g_DispatchCondition;
static DBusError            g_Error;

typedef struct tDBusRequest
{
    tRequestHandler handler;
    HStub           stub;
    DBusMessage *   message;
    DBusMessage *   reply;
}tDBusRequest;

typedef struct tMessageQueue
{
    int            head;
    int            tail;
    int            num;
    pthread_cond_t condition;
}tMessageQueue;

typedef struct tMainQueue
{
    unsigned char   array[4096];
    int             head;
    int             tail;
    int             num;
    pthread_cond_t  condition;
    pthread_mutex_t mutex;
}tMainQueue;

typedef struct tDBusReply
{
    HStub         stub;
    DBusMessage * message;
}tDBusReply;
typedef void (*tSignalHandler)(HProxy proxy, DBusMessage *message);
typedef struct tDBusSignal
{
    tSignalHandler handler;
    HProxy         proxy;
    DBusMessage *  message;
}tDBusSignal;

typedef struct tDBusCall
{
    HProxy        proxy;
    DBusMessage * message;
    tReplyHandler responser;
}tDBusCall;

typedef struct tDBusResponse
{
    tResponseHandler handler;
    HProxy           proxy;
    DBusMessage *    message;
}tDBusResponse;

static tDBusRequest         g_mRequests[1024];
static tMessageQueue        g_mRequestQueue;

static tDBusReply           g_mReplys[1024];
static tMessageQueue        g_mReplyQueue;

static tDBusSignal          g_mSignals[1024];
static tMessageQueue        g_mSignalQueue;

static tDBusCall            g_mCalls[1024];
static tMessageQueue        g_mCallQueue;

static tDBusResponse        g_mResponses[1024];
static tMessageQueue        g_mResponseQueue;


static tMainQueue           g_mIncomings; //QUEUE_ID_REQUEST, QUEUE_ID_RESPONSE, QUEUE_ID_SIGNAL
static tMainQueue           g_mOutgoings;


static int                  g_iDispatchPaused;



//声明


int message_queue_enter_push(tMessageQueue *queue, pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    while(1024 == queue->num)
    {
        printf("message_queue_enter_push start\n");
        pthread_cond_wait(&(queue->condition), mutex);
        printf("message_queue_enter_push end \n");
    }

    int cursor = queue->head;
    ++(queue->num);
    ++(queue->head);
    if (queue->head >= 1024) queue->head = 0;

    return cursor;
}
int message_queue_take(tMessageQueue *queue)
{
    int cursor = queue->tail;
    if (1024 == queue->num) pthread_cond_signal(&(queue->condition));
    --(queue->num);
    ++(queue->tail);
    if (queue->tail >= 1024) queue->tail = 0;
    return cursor;
}
void main_queue_leave_push(tMainQueue *queue, unsigned char index)
{
    queue->array[queue->head] = index;

    ++(queue->num);
    ++(queue->head);
    if (queue->head >= 4096) queue->head = 0;

    pthread_cond_signal(&(queue->condition));
    pthread_mutex_unlock(&(queue->mutex));
}

unsigned char main_queue_take(tMainQueue *queue)
{
    unsigned char index = queue->array[queue->tail];

    --(queue->num);
    ++(queue->tail);
    if (queue->tail >= 4096) queue->tail = 0;

    return index;
}

tRequestHandler handler_requset;
static void *work_request(void *p_param_)
{
    ((dbus_work)p_param_)();

    for(;;)
    {
        pthread_mutex_lock(&(g_mIncomings.mutex));
        while(0 == g_mIncomings.num)
        {
            pthread_cond_wait(&(g_mIncomings.condition), &(g_mIncomings.mutex));
        }

        unsigned char index = main_queue_take(&g_mIncomings);
        if (QUEUE_ID_EVENT == index)
        {

        }
        else if (QUEUE_ID_REQUEST == index)
        {
            tDBusRequest *p = g_mRequests + message_queue_take(&g_mRequestQueue);
            tRequestHandler handler = p->handler;
            HStub stub              = p->stub;
            DBusMessage *message    = p->message;
            DBusMessage *reply      = p->reply;

            pthread_mutex_unlock(&(g_mIncomings.mutex));

            handler(stub, message, reply);


            dbus_message_unref(message);
            if (NULL != reply) dbus_message_unref(reply);


        }
        else if (QUEUE_ID_RESPONSE == index)
        {
            tDBusResponse *p = g_mResponses + message_queue_take(&g_mResponseQueue);
            tResponseHandler handler = p->handler;
            HProxy proxy             = p->proxy;
            DBusMessage *message     = p->message;

            pthread_mutex_unlock(&(g_mIncomings.mutex));

            handler(proxy, message);
            dbus_message_unref(message);
        }
        else if (QUEUE_ID_SIGNAL == index)
        {
            tDBusSignal *p = g_mSignals + message_queue_take(&g_mSignalQueue);
            tSignalHandler handler = p->handler;
            HProxy proxy           = p->proxy;
            DBusMessage *message   = p->message;

            pthread_mutex_unlock(&(g_mIncomings.mutex));

            handler(proxy, message);
            dbus_message_unref(message);
        }
        else
        {
        }
    }
    return NULL;
}

int add_to_epoll(int fd, int epollFd)
{
    int result;
    struct epoll_event eventItem;
    memset(&eventItem, 0, sizeof(eventItem));
    eventItem.events = EPOLLIN;
    eventItem.data.fd = fd;
    result = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &eventItem);
    return result;
}

static void *select_monitoring(void *p_param_)
{
    int fd = (int)p_param_;
//    int mEpollFd;
//    int i;
//    char buf[1024];
//    struct epoll_event mPendingEventItems[16];
//
//    mEpollFd = epoll_create(8);
//    add_to_epoll(fd, mEpollFd);
//
//    while(1)
//    {
//        int pollResult = epoll_wait(mEpollFd, mPendingEventItems, 16, -1);
//        for (i = 0; i < pollResult; i++)
//        {
//            if(mPendingEventItems[i].events & EPOLLIN)
//            {
//                if(( mPendingEventItems[i].data.fd) < 0)
//                    continue;
//                pthread_mutex_lock(&(g_mOutgoings.mutex));
//                g_iDispatchPaused = 1;
//                pthread_cond_signal(&(g_mOutgoings.condition));
//                while(1 == g_iDispatchPaused) pthread_cond_wait(&g_DispatchCondition, &(g_mOutgoings.mutex));
//                pthread_mutex_unlock(&(g_mOutgoings.mutex));
//
//            }
//        }
//    }

    fd_set fds;
    while(1)
    {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        int result = select(fd + 1, &fds, NULL, NULL, NULL);
        if (result < 0)
        {
            printf("select error %d %d %d\n",getpid(),getppid(),fd + 1);
            perror("select() error:");

            exit(1);
        }
        else if (FD_ISSET(fd, &fds))
        {
            do
            {
                dbus_connection_read_write_dispatch(gp_Connection, 0);
            } while (dbus_connection_get_dispatch_status(gp_Connection) == DBUS_DISPATCH_DATA_REMAINS);
        }
    }

    return NULL;

}

void init_queue(tMessageQueue *queue)
{
    pthread_cond_init(&(queue->condition), NULL);
    queue->head = 0;
    queue->tail = 0;
    queue->num = 0;
}
void yp_bus_init()
{
    g_mIncomings.head = 0;
    g_mIncomings.tail = 0;
    g_mIncomings.num = 0;
    pthread_cond_init(&(g_mIncomings.condition), NULL);
    pthread_mutex_init(&(g_mIncomings.mutex), NULL);

    g_mOutgoings.head = 0;
    g_mOutgoings.tail = 0;
    g_mOutgoings.num = 0;
    pthread_cond_init(&(g_mOutgoings.condition), NULL);
    pthread_mutex_init(&(g_mOutgoings.mutex), NULL);

    init_queue(&g_mRequestQueue);
    init_queue(&g_mReplyQueue);
    init_queue(&g_mSignalQueue);
    init_queue(&g_mCallQueue);
    init_queue(&g_mResponseQueue);

    pthread_cond_init(&g_DispatchCondition, NULL);

}




static DBusHandlerResult service_filter(DBusConnection *conn, DBusMessage *message, void *user_data)
{
    if (dbus_message_get_type(message) != DBUS_MESSAGE_TYPE_SIGNAL) return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    if (dbus_message_has_path(message, "/org/freedesktop/DBus"))
    {
        if(dbus_message_has_interface(message, "org.freedesktop.DBus"))
        {
            if (dbus_message_has_member(message, "NameOwnerChanged"))
            {

            }
        }

        return DBUS_HANDLER_RESULT_HANDLED;
    }
    else if (dbus_message_has_path(message, "/org/freedesktop/DBus/Local"))
    {
        if (dbus_message_has_interface(message, "org.freedesktop.DBus.Local"))
        {
            if (dbus_message_has_member(message, "Disconnected"))
            {
                printf("dbus exit !!!!!!!!!!! \n");
                //exit(EXIT_SUCCESS);
            }
        }
        return DBUS_HANDLER_RESULT_HANDLED;
    }
    else
    {
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    }
}
void yp_dbus_connect()
{
    dbus_threads_init_default();

    dbus_error_init(&g_Error);
    //gp_Connection = dbus_bus_get(DBUS_BUS_SYSTEM,&g_Error);
    gp_Connection = dbus_connection_open("unix:path=/tmp/dbus_service_socket", &g_Error);
    if (dbus_error_is_set(&g_Error))
    {
        fprintf(stderr, "Connection Error (%s)\n", g_Error.message);
        dbus_error_free(&g_Error);
    }
    if (NULL == gp_Connection)
    {
        fprintf(stderr, "Connection Null\n");
        exit(1);
    }
    dbus_connection_set_exit_on_disconnect(gp_Connection, FALSE);
    dbus_bus_register(gp_Connection, &g_Error);

    dbus_bus_add_match(gp_Connection, "type='signal'", &g_Error);
    dbus_connection_add_filter(gp_Connection, service_filter, NULL, NULL);

}

void yp_dbus_wait_service(const char *p_name_)
{
    dbus_bool_t ret;
    printf("waiting for %s\n", p_name_);
    while (1)
    {
        ret = dbus_bus_name_has_owner(gp_Connection, p_name_, &g_Error);
        if (ret == TRUE) break;

        dbus_connection_read_write_dispatch(gp_Connection, 1000);
    }
    printf("end waiting %s\n", p_name_);
}

void yp_dbus_register_service(const char *p_name_)
{
    int ret = dbus_bus_request_name(gp_Connection, p_name_, DBUS_NAME_FLAG_REPLACE_EXISTING, &g_Error);
    if (dbus_error_is_set(&g_Error))
    {
        fprintf(stderr, "error in registering service [%s]. %s\n", p_name_, g_Error.message);
        dbus_error_free(&g_Error);
    }
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret)
    {
        fprintf(stderr, "failed to register service [%s]. result = %d\n", p_name_, ret);
        return;
    }
    printf("service [%s] is registered\n", p_name_);
}

void yp_dbus_register_component(HStub stub_, DBusObjectPathMessageFunction handler,	DBusHandleMessageFunction  function_filter)
{
    DBusObjectPathVTable vt;
    vt.unregister_function = NULL;
    vt.message_function = handler;
    if (dbus_connection_register_object_path(stub_->connection, stub_->path, &vt, (void *)stub_))
    {
        printf("object [%s] is registered\n", stub_->path);
    }
    else
    {
        fprintf(stderr, "failed to register object [%s]\n", stub_->path);
    }

    dbus_connection_add_filter(gp_Connection, function_filter, (void *)stub_, NULL);
}

void yp_dbus_work(dbus_work dbus_work)
{

    pthread_t thread1;
    pthread_attr_t attribute1;
    pthread_attr_init(&attribute1);
    pthread_attr_setdetachstate(&attribute1, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread1, &attribute1, work_request, (void *)dbus_work);

    int fd = -1;
    dbus_connection_get_unix_fd(gp_Connection, &fd);

    pthread_t thread2;
    pthread_attr_t attribute2;
    pthread_attr_init(&attribute2);
    pthread_attr_setdetachstate(&attribute2, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread2, &attribute2, select_monitoring, (void *)(long)fd);


    for(;;)
    {
        pthread_mutex_lock(&(g_mOutgoings.mutex));

        while( 0 == g_mOutgoings.num)
        {
            pthread_cond_wait(&(g_mOutgoings.condition), &(g_mOutgoings.mutex));
        }

        if (g_iDispatchPaused)
        {

        }
        while (g_mOutgoings.num)
        {
            unsigned char index = main_queue_take(&g_mOutgoings);

            if (QUEUE_ID_CALL == index)
            {
                tDBusCall *p = g_mCalls + message_queue_take(&g_mCallQueue);

                if (NULL == p->responser)
                {
                    dbus_message_set_no_reply(p->message, TRUE);
                    dbus_connection_send(p->proxy->connection, p->message, NULL);
                }
                else
                {
                    DBusPendingCall *rpc;
                    dbus_connection_send_with_reply(p->proxy->connection, p->message, &rpc, -1);
                    dbus_pending_call_set_notify(rpc, (DBusPendingCallNotifyFunction)(p->responser), (void *)(p->proxy), NULL);
                }
                dbus_message_unref(p->message);
            }
            else if (QUEUE_ID_REPLY == index)
            {
                tDBusReply *p = g_mReplys + message_queue_take(&g_mReplyQueue);

                dbus_message_set_no_reply(p->message, TRUE);
                dbus_connection_send(p->stub->connection, p->message, NULL);
                dbus_message_unref(p->message);
            }
            else
            {
            }
        }

        pthread_mutex_unlock(&(g_mOutgoings.mutex));

    }
}
//-------------------------------------------------------------------------
//回调函数 调用远程方法，通过queue_response来解析方法（发送方）
void yp_dbus_call(HProxy proxy_, DBusMessage *p_message_, tReplyHandler responser)
{
    tDBusCall *p = g_mCalls + message_queue_enter_push(&g_mCallQueue, &(g_mOutgoings.mutex));

    p->proxy = proxy_;
    p->message = p_message_;
    p->responser = responser;

    main_queue_leave_push(&g_mOutgoings, QUEUE_ID_CALL);
}
void yp_dbus_reply(HStub stub_, DBusMessage *p_reply_)
{
    tDBusReply *p = g_mReplys + message_queue_enter_push(&g_mReplyQueue, &(g_mOutgoings.mutex));
    p->message = p_reply_;
    p->stub = stub_;

    main_queue_leave_push(&g_mOutgoings, QUEUE_ID_REPLY);
}
//-----------------------------------------------------------------------
//本地操作配合yp_dbus_call使用，异步返回后调用函数
void yp_dbus_response(tResponseHandler handler, HProxy proxy_, DBusPendingCall *p_rpc_)
{
    DBusMessage *msg = dbus_pending_call_steal_reply(p_rpc_);
    dbus_pending_call_unref(p_rpc_);
    const char *err = dbus_message_get_error_name(msg);
    if (NULL != err)
    {
        fprintf(stderr, "response error: %s\n", err);
        dbus_message_unref(msg);
        return;
    }

    tDBusResponse *p = g_mResponses + message_queue_enter_push(&g_mResponseQueue, &(g_mIncomings.mutex));
    p->handler = handler;
    p->proxy = proxy_;
    p->message = msg;
    main_queue_leave_push(&g_mIncomings, QUEUE_ID_RESPONSE);
}

//在线程中调用方法
void yp_dbus_signal(tResponseHandler handler, HProxy proxy_,DBusMessage *p_message_)
{
    dbus_message_ref(p_message_);
    tDBusSignal *p = g_mSignals + message_queue_enter_push(&g_mSignalQueue, &(g_mIncomings.mutex));
    p->handler = handler;
    p->proxy = proxy_;
    p->message = p_message_;

    main_queue_leave_push(&g_mIncomings, QUEUE_ID_SIGNAL);

}

//todo:空闲进程执行
//dbus_message_new_method_return(message)
//带返回值的本地操作
void yp_dbus_request(tRequestHandler handler, HStub stub_, DBusMessage *p_message_, DBusMessage *p_reply_)
{
    dbus_message_ref(p_message_);
    if (NULL != p_reply_) dbus_message_ref(p_reply_);

    tDBusRequest *p = g_mRequests + message_queue_enter_push(&g_mRequestQueue, &(g_mIncomings.mutex));
    p->handler = handler;
    p->stub = stub_;
    p->message = p_message_;
    p->reply = p_reply_;

    main_queue_leave_push(&g_mIncomings, QUEUE_ID_REQUEST);
}


//==========================================================
//创建发送消息头后继续创建
void yp_dbus_mes_create_base(DBusMessageIter *p_arg_,int Flag_,void *p_retParam_)
{
    if(!dbus_message_iter_append_basic (p_arg_, Flag_, p_retParam_)){
        printf("Out of Memory!");
    }
}
void yp_dbus_mes_create_string(DBusMessageIter *p_arg_,void *p_retParam_)
{
    if(!dbus_message_iter_append_basic (p_arg_, DBUS_TYPE_STRING, &p_retParam_)){
        printf("Out of Memory!");
    }
}
void yp_dbus_mes_create_arry(DBusMessageIter *p_arg_,void *p_retParam_,int retLen_)
{
    DBusMessageIter  sub;
    const char *v_ARRAY = (char *)p_retParam_;
    char buf[2];
    buf[0] = DBUS_TYPE_BYTE;
    buf[1] = '\0';


    dbus_message_iter_open_container(p_arg_,DBUS_TYPE_ARRAY,buf,&sub);

    if(!dbus_message_iter_append_fixed_array (&sub, DBUS_TYPE_BYTE , &v_ARRAY, retLen_)){
        fprintf(stderr,"Out Of Memory!\n");
        return;
    }

    dbus_message_iter_close_container(p_arg_,&sub);
}
//解析消息头后继续解析
void yp_dbus_mes_get_base(DBusMessageIter *p_arg_,void *p_inceptParam_)
{
    dbus_message_iter_get_basic(p_arg_,p_inceptParam_);
}
void yp_dbus_mes_get_string(DBusMessageIter *p_arg_,void *p_inceptParam_)
{
    char *test;

    dbus_message_iter_get_basic(p_arg_,&test);
    memcpy(p_inceptParam_, test, strlen(test));
}
void yp_dbus_mes_get_arry(DBusMessageIter *p_arg_,void *p_inceptParam_)
{
    DBusMessageIter subArrayIter;
    char *test;
    int len = 0;
    dbus_message_iter_recurse(p_arg_, &subArrayIter); //解开下层迭代
    dbus_message_iter_get_fixed_array(&subArrayIter, &test, &len);

    memcpy(p_inceptParam_, test, len);

}

//解析消息头创建
int yp_dbus_incept_message(DBusMessage *p_message_, DBusMessageIter *p_arg_,int inceptFlag_,void *p_inceptParam_)
{

    if(!dbus_message_iter_init(p_message_,p_arg_))
        printf("Message has no args\n");

    switch (inceptFlag_)
    {
        case DBUS_TYPE_DOUBLE:
        case DBUS_TYPE_UINT32:
        case DBUS_TYPE_INT32:
        case DBUS_TYPE_BYTE:{
            yp_dbus_mes_get_base(p_arg_,p_inceptParam_);
        }
            break;
        case DBUS_TYPE_STRING:{
            yp_dbus_mes_get_string(p_arg_,p_inceptParam_);
        }
            break;
        case DBUS_TYPE_ARRAY:{
            yp_dbus_mes_get_arry(p_arg_,p_inceptParam_);
        }
            break;

    }
    return 1;
}
//创建发送消息头
int yp_dbus_send_mes_create(DBusMessage *p_message_,DBusMessageIter *p_arg_,int retFlag_,void *p_retParam_,int retLen_)
{

    dbus_message_iter_init_append(p_message_,p_arg_);

    switch (retFlag_)
    {
        case DBUS_TYPE_DOUBLE:
        case DBUS_TYPE_UINT32:
        case DBUS_TYPE_INT32:
        case DBUS_TYPE_BYTE:{
            yp_dbus_mes_create_base(p_arg_, retFlag_, p_retParam_);
        }
            break;

        case DBUS_TYPE_STRING:{
            yp_dbus_mes_create_string(p_arg_,p_retParam_);
        }
            break;
        case DBUS_TYPE_ARRAY:{
            yp_dbus_mes_create_arry(p_arg_,p_retParam_,retLen_);
        }
            break;

    }
    return 1;
}

//创建返回值
int yp_dbus_ret_message_create(DBusMessage *p_message_,DBusMessageIter *p_arg_,DBusMessage **pp_reply_,int retFlag_,void *p_retParam,int retLen_)
{
    *pp_reply_ = dbus_message_new_method_return(p_message_);

    yp_dbus_send_mes_create(*pp_reply_,p_arg_,retFlag_,p_retParam,retLen_);

    return 1;
}



//创建远程调用
int yp_dbus_method_call_create(DBusMessage **pp_msg_,DBusMessageIter *p_arg_,const char *p_destination_,const char *p_path_,const char *p_iface_,\
					const char *p_method_,int sendFlag_, void *p_sendParam_,int sendLen_)
{
    if((*pp_msg_ = dbus_message_new_method_call (p_destination_,p_path_,p_iface_,p_method_)) == NULL){
        printf("Message NULL\n");
        return -1;
    }
    yp_dbus_send_mes_create(*pp_msg_,p_arg_,sendFlag_,p_sendParam_,sendLen_);


    return 1;

}

//创建信号
int yp_dbus_signal_create(DBusMessage **pp_msg_,DBusMessageIter *p_arg_,const char *p_path_,const char *p_iface_,\
					const char *p_signal_,int sendFlag_, void *p_sendParam_,int sendLen_)
{
    if((*pp_msg_ = dbus_message_new_signal (p_path_,p_iface_,p_signal_)) == NULL){
        fprintf(stderr,"Message NULL\n");
        return -1;
    }

    yp_dbus_send_mes_create(*pp_msg_,p_arg_,sendFlag_,p_sendParam_,sendLen_);

    return 1;

}

//==========================================================
/* HStub YP_MYSQL;
HProxy PROXY_MYSQL;

DBusHandlerResult yp_msg_handler(DBusConnection *connection, DBusMessage *message, void *user_data)
{
	int param = 0;
	DBusMessageIter arg;
	yp_dbus_incept_message(message,&arg,DBUS_TYPE_UINT32,&param);
	printf("call1  %d \n",param);

	yp_dbus_mes_get_next_base(&arg,&param);
	printf("call2  %d \n",param);

	DBusMessage *reply;
	DBusMessageIter arg2;
	int aa= 42;
	yp_dbus_ret_message_create(message,&arg2,&reply,DBUS_TYPE_UINT32,&aa,0);
	aa= 142;
	yp_dbus_mes_add_base(&arg2,DBUS_TYPE_UINT32,(void *)(&aa));
	yp_dbus_reply(YP_MYSQL, reply);

	printf("yp_msg_handler \n");
	return DBUS_HANDLER_RESULT_HANDLED;
}
DBusHandlerResult bus_filter(DBusConnection *conn, DBusMessage *message, void *user_data)
{
	if (dbus_message_get_type(message) != DBUS_MESSAGE_TYPE_SIGNAL)
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	if(dbus_message_has_interface(message, "org.freedesktop.DBus"))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	printf("bus_filter \n");
	int param = 0;
	DBusMessageIter arg;

	yp_dbus_incept_message(message,&arg,DBUS_TYPE_UINT32,&param);
	printf("bus_filter1  %d \n",param);

	yp_dbus_mes_get_next_base(&arg,&param);
	printf("bus_filter2  %d \n",param);
	return DBUS_HANDLER_RESULT_HANDLED;

}

void ResponseHandler(HProxy proxy, DBusMessage *message)
{
	int param=0;
	DBusMessageIter arg;
	yp_dbus_incept_message(message,&arg,DBUS_TYPE_UINT32,&param);
	printf("param1 %d\n",param);
	yp_dbus_mes_get_next_base(&arg,&param);
	printf("param2  %d \n",param);
}

void main_call(DBusPendingCall *pending, HProxy proxy)
{
	yp_dbus_response(ResponseHandler, proxy, pending);
	printf("main_call \n");
}
void main_start()
{
	DBusMessage *msg;
	DBusMessageIter arg;
	dbus_uint32_t level = 32;

	yp_dbus_method_call_create(&msg,&arg,PROXY_MYSQL->service,PROXY_MYSQL->path,"test.method.Type2",\
					"Test2",DBUS_TYPE_UINT32, (void *)(&level),0);
	level = 132;

	yp_dbus_mes_add_base(&arg,DBUS_TYPE_UINT32,(void *)(&level));
	yp_dbus_call(PROXY_MYSQL,msg,main_call);

	DBusMessage *msg1;
	DBusMessageIter arg2;
	yp_dbus_signal_create(&msg1,&arg2,PROXY_MYSQL->path,"test.method.Type",\
					"test",DBUS_TYPE_UINT32, (void *)(&level),0);
	level = 100;
	yp_dbus_mes_add_base(&arg2,DBUS_TYPE_UINT32,(void *)(&level));

	yp_dbus_reply(YP_MYSQL,msg1);
	printf("main_start \n");
}



int main(void)
{
	yp_dbus_connect();
	yp_dbus_register_service("yp.mysql");

	struct tComponentInstance instance_SWDL;
	instance_SWDL.connection = gp_Connection;
	instance_SWDL.path = "/yp/mysql";
	YP_MYSQL = &instance_SWDL;

	struct tRemoteComponent proxy_ota;
	proxy_ota.connection = gp_Connection;
	proxy_ota.path = "/yp/mysql";
	proxy_ota.service = "yp.mysql";
	PROXY_MYSQL = &proxy_ota;


	yp_dbus_register_component(YP_MYSQL,yp_msg_handler,bus_filter);

	yp_dbus_work(main_start);

	return 0;
} */