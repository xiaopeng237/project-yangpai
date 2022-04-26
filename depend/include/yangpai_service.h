//
// Created by lenovo on 2019/10/24.
//

#ifndef YANGPAI_YANGPAI_SERVICE_H
#define YANGPAI_YANGPAI_SERVICE_H
#include <dbus/dbus.h>
struct tComponentInstance
{
    DBusConnection * connection;
    const char *     path;
};
struct tRemoteComponent
{
    DBusConnection * connection;

    const char *     path;
    const char *     service;
};

extern DBusConnection *gp_Connection;

typedef const struct tComponentInstance *HStub;
typedef const struct tRemoteComponent *HProxy;
typedef void (*dbus_work)();
void yp_bus_init();
//dbus总线连接
void yp_dbus_connect();
//等待dbus总线上的服务
void yp_dbus_wait_service(const char *p_name_);
//注册本地服务
void yp_dbus_register_service(const char *p_name_);
//注册本地函数调用和信号过滤
void yp_dbus_register_component(HStub stub_, DBusObjectPathMessageFunction handler,	DBusHandleMessageFunction  function_filter);
//就开始任务
void yp_dbus_work(dbus_work dbus_work);


typedef void (*tRequestHandler)(HStub stub, DBusMessage *message, DBusMessage *reply);
typedef void (*tResponseHandler)(HProxy proxy, DBusMessage *message);
typedef void (*tReplyHandler)(DBusPendingCall *rpc, HProxy proxy);
//远程调用发送，当需要返回值时在callback中调用yp_dbus_response，在yp_dbus_response的callback中处理
//在yp_dbus_method_call_create之后调用
void yp_dbus_call(HProxy proxy_, DBusMessage *p_message_, tReplyHandler responser);
void yp_dbus_response(tResponseHandler handler, HProxy proxy_, DBusPendingCall *p_rpc_);
//暂时没用预留
void yp_dbus_request(tRequestHandler handler, HStub stub_, DBusMessage *p_message_, DBusMessage *p_reply_);
void yp_dbus_signal(tResponseHandler handler, HProxy proxy_,DBusMessage *p_message_);
//信号发送
void yp_dbus_reply(HStub stub_, DBusMessage *p_reply_);
////创建发送消息头，初始化消息并添加一种消息参数(用户不适用，给内部使用)
int yp_dbus_send_mes_create(DBusMessage *p_message_,DBusMessageIter *p_arg_,int retFlag_,void *p_retParam_,int retLen_);

//在使用，yp_dbus_signal_create或yp_dbus_method_call_create这个后使用增加参数，推荐使用宏
void yp_dbus_mes_create_base(DBusMessageIter *p_arg_,int Flag_,void *p_retParam_);
void yp_dbus_mes_create_string(DBusMessageIter *p_arg_,void *p_retParam_);
void yp_dbus_mes_create_arry(DBusMessageIter *p_arg_,void *p_retParam_,int retLen_);

//创建消息后调用增加发送参数
#define yp_dbus_mes_add_base(p_arg_,Flag_,p_retParam_) {\
	yp_dbus_mes_create_base(p_arg_,Flag_,p_retParam_);\
}
#define yp_dbus_mes_add_string(p_arg_,p_retParam_) {\
	yp_dbus_mes_create_string(p_arg_,p_retParam_);\
}
#define yp_dbus_mes_add_arry(p_arg_,p_retParam_,retLen_) {\
	yp_dbus_mes_create_arry(p_arg_,p_retParam_,retLen_);\
}


//解析消息头创建，并解析一种消息
int yp_dbus_incept_message(DBusMessage *p_message_, DBusMessageIter *p_arg_,int inceptFlag_,void *p_inceptParam_);
//用户不适用
void yp_dbus_mes_get_base(DBusMessageIter *p_arg_,void *p_inceptParam_);
void yp_dbus_mes_get_string(DBusMessageIter *p_arg_,void *p_inceptParam_);
void yp_dbus_mes_get_arry(DBusMessageIter *p_arg_,void *p_inceptParam_);
//解析下一个参数
#define yp_dbus_mes_get_next_base(p_arg_,p_retParam_) {\
	dbus_message_iter_next(p_arg_);\
	yp_dbus_mes_get_base(p_arg_,p_retParam_);\
}
#define yp_dbus_mes_get_next_string(p_arg_,p_retParam_) {\
	dbus_message_iter_next(p_arg_);\
	yp_dbus_mes_get_string(p_arg_,p_retParam_);\
}
#define yp_dbus_mes_get_next_arry(p_arg_,p_retParam_) {\
	dbus_message_iter_next(p_arg_);\
	yp_dbus_mes_get_arry(p_arg_,p_retParam_);\
}


//创建返回值
int yp_dbus_ret_message_create(DBusMessage *p_message_,DBusMessageIter *p_arg_,DBusMessage **pp_reply_,int retFlag_,void *p_retParam,int retLen_);

//创建远程调用
int yp_dbus_method_call_create(DBusMessage **pp_msg_,DBusMessageIter *p_arg_,const char *p_destination_,const char *p_path_,const char *p_iface_,\
					const char *p_method_,int sendFlag_, void *p_sendParam_,int sendLen_);
//创建信号发送
int yp_dbus_signal_create(DBusMessage **pp_msg_,DBusMessageIter *p_arg_,const char *p_path_,const char *p_iface_,\
					const char *p_signal_,int sendFlag_, void *p_sendParam_,int sendLen_);

#endif //YANGPAI_YANGPAI_SERVICE_H
