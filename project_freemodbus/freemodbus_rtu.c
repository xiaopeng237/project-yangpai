/*
 * FreeModbus Libary: Linux Demo Application
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: demo.c,v 1.2 2006/10/12 08:12:06 wolti Exp $
 */

/* ----------------------- Standard includes --------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <sys/shm.h>
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "rtu_service.h"
#include "rtu_data_base.h"
#include "pioneers.h"
#include "yangpi_mysql_proxy.h"


/* ----------------------- Defines ------------------------------------------*/
#define PROG            "freemodbus"

#define REG_INPUT_START 1000
#define REG_INPUT_NREGS 4
//#define REG_HOLDING_START 0001
#define REG_HOLDING_START 0000
#define REG_HOLDING_NREGS 130

/* ----------------------- Static variables ---------------------------------*/
static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];
static USHORT   usRegHoldingStart = REG_HOLDING_START;
static USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];



static enum ThreadState
{
    STOPPED,
    RUNNING,
    SHUTDOWN
} ePollThreadState;

static pthread_mutex_t xLock = PTHREAD_MUTEX_INITIALIZER;
static BOOL     bDoExit;

/* ----------------------- Static functions ---------------------------------*/
static BOOL     bCreatePollingThread( void );
static enum ThreadState eGetPollingThreadState( void );
static void     vSetPollingThreadState( enum ThreadState eNewState );
static void    *pvPollingThread( void *pvParameter );

/* ----------------------- Start implementation -----------------------------*/
BOOL
bSetSignal( int iSignalNr, void ( *pSigHandler ) ( int ) )
{
	BOOL            bResult;
	struct sigaction xNewSig, xOldSig;

	xNewSig.sa_handler = pSigHandler;
	sigemptyset( &xNewSig.sa_mask );
	xNewSig.sa_flags = 0;
	if( sigaction( iSignalNr, &xNewSig, &xOldSig ) != 0 )
	{
		bResult = FALSE;
	}
	else
	{
		bResult = TRUE;
	}
	return bResult;
}

void
vSigShutdown( int xSigNr )
{
	switch ( xSigNr )
	{
	case SIGQUIT:
	case SIGINT:
	case SIGTERM:
		vSetPollingThreadState( SHUTDOWN );
		bDoExit = TRUE;
		break;
	}
}
float register_value[REG_HOLDING_NREGS];
//enum register_adde
//{
//    DP_CPS = 1,
//    P_WC_CPS = 3,
//    T_P_WC_CPS = 5,
//    Qvg_CPS = 9,
//    Qvg_add_CPS = 17,
//    Qvl_CPS = 47,
//    Qvl_add_CPS =61
//};
//typedef struct _TmpShared
//{
//	float P_WC_CPS;
//	float DP_CPS;
//    float T_P_WC_CPS;
//    float Time_add;
//
//	float Qvg_CPS;
//	float Qvl_CPS;
//
//	float Qvg_add_CPS;
//	float Qvl_add_CPS;
//
//
//}TmpShared;

enum register_adde
{
    P_WC_CPS = 1,       //绝压
    DP_CPS = 3,         //差压
    T_P_WC_CPS = 5,     //温度
    Add_Sctime = 7,     //累计运行时间
    Qvg_CPS = 9,        //气瞬时
    Qvl_CPS = 11,       //液瞬时
    Qvg_add_CPS =13,    //累计气
    Qvl_add_CPS=15      //累计液
};

typedef struct _TmpShared
{

    float DP_CPS;
    float P_WC_CPS;
    float T_P_WC_CPS;


    float Qvg_CPS;
    float Qvg_add_CPS;
    float Qvl_CPS;
    float Qvl_add_CPS;


}TmpShared;

void FloatToShort(int StartIndx_ )
{
    float tmp;
    int i = 0,j = 1;
    //0位空，因为是双数，所以129也为空所以是1-128
    for(i = 0; i < REG_HOLDING_NREGS/2 -2; i++)
    {
        tmp = register_value[j];
        usRegHoldingBuf[StartIndx_ + i*2 ]= ( UCHAR ) *((UCHAR*)(&tmp) + 3 ) << 8 \
									|( UCHAR ) *((UCHAR*)(&tmp) + 2);
        usRegHoldingBuf[StartIndx_ + i*2 + 1]= ( UCHAR ) *((UCHAR*)(&tmp) + 1 ) << 8 \
									|( UCHAR ) *((UCHAR*)(&tmp) + 0);
        j+=2;
    }

}


void setShare_rtu(T_RtuData *tRtuData)
{
    memset(register_value,0,REG_HOLDING_NREGS * sizeof(float));
    register_value[DP_CPS]      = tRtuData->DP_CPS;
    register_value[P_WC_CPS]    = tRtuData->P_WC_CPS;
    register_value[T_P_WC_CPS]  = tRtuData->T_P_WC_CPS;
    register_value[Qvg_CPS]     = tRtuData->Qvg_CPS;
    register_value[Qvl_CPS]     = tRtuData->Qvl_CPS;
    register_value[Qvg_add_CPS] = tRtuData->Qvg_add_CPS;
    register_value[Qvl_add_CPS] = tRtuData->Qvl_add_CPS;
    register_value[Add_Sctime] = tRtuData->Add_Sctime;


    printf("tmpShared.P_WC_CPS    %f==%f\n",register_value[P_WC_CPS]   ,tRtuData->P_WC_CPS);
    printf("tmpShared.DP_CPS      %f==%f\n",register_value[DP_CPS]     ,tRtuData->DP_CPS);
    printf("tmpShared.T_P_WC_CPS  %f==%f\n",register_value[T_P_WC_CPS] ,tRtuData->T_P_WC_CPS);
    printf("tmpShared.Qvg_CPS     %f==%f\n",register_value[Qvg_CPS]    ,tRtuData->Qvg_CPS);
    printf("tmpShared.Qvl_CPS     %f==%f\n",register_value[Qvl_CPS]    ,tRtuData->Qvl_CPS);
    printf("tmpShared.Qvg_add_CPS %f==%f\n",register_value[Qvg_add_CPS],tRtuData->Qvg_add_CPS);
    printf("tmpShared.Qvl_add_CPS %f==%f\n",register_value[Qvl_add_CPS],tRtuData->Qvl_add_CPS);

	FloatToShort(1);

}

extern T_Flow_para tFlow_para;

int freeModbusInit( int argc, char *argv[] )
{
	/*********************************************
	 *             	usRegHoldingBuf对此数组进行数据填充
	 * ******************************/

	memset(usRegHoldingBuf,0,REG_HOLDING_NREGS*2);

	/******************************************************************************/
	int             iExitCode;

	const UCHAR     ucSlaveID[] = { 0xAA, 0xBB, 0xCC };
	if( !bSetSignal( SIGQUIT, vSigShutdown ) ||
	        !bSetSignal( SIGINT, vSigShutdown ) || !bSetSignal( SIGTERM, vSigShutdown ) )
	{
		fprintf( stderr, "%s: can't install signal handlers: %s!\n", PROG, strerror( errno ) );
		iExitCode = EXIT_FAILURE;
	}
	else if( eMBInit( tFlow_para.t_Freemodbus.mode, tFlow_para.t_Freemodbus.slaveadd, tFlow_para.t_Freemodbus.port,
                      tFlow_para.t_Freemodbus.baudrate, tFlow_para.t_Freemodbus.parity ) != MB_ENOERR )//MB_RTU, 1, 1, 9600, MB_PAR_NONE
	{
		fprintf( stderr, "%s: can't initialize modbus stack!\n", PROG );
		iExitCode = EXIT_FAILURE;
	}
	else if( eMBSetSlaveID( 0x34, TRUE, ucSlaveID, 3 ) != MB_ENOERR )
	{
		fprintf( stderr, "%s: can't set slave id!\n", PROG );
		iExitCode = EXIT_FAILURE;
	}
	else
	{
		vSetPollingThreadState( STOPPED );

		/* CLI interface. */
		printf( "Type 'q' for quit or 'h' for help!\n" );
		bDoExit = FALSE;
		if (!strcmp(argv[1], "e"))
		{
			if( bCreatePollingThread() != TRUE )
			{
				printf( "Can't start protocol stack! Already running?\n" );
			}
		}
		else if(!strcmp(argv[1], "q"))
		{
			bDoExit = TRUE;
		}
		else if(!strcmp(argv[1], "d"))
		{
			exit(EXIT_SUCCESS);
			vSetPollingThreadState( SHUTDOWN );
		}
		else if(!strcmp(argv[1], "s"))
		{
			switch ( eGetPollingThreadState(  ) )
			{
			case RUNNING:
				printf( "Protocol stack is running.\n" );
				break;
			case STOPPED:
				printf( "Protocol stack is stopped.\n" );
				break;
			case SHUTDOWN:
				printf( "Protocol stack is shuting down.\n" );
				break;
			}

		}
		else if(!strcmp(argv[1], "h"))
		{
			printf( "FreeModbus demo application help:\n" );
			printf( "  'd' ... disable protocol stack.\n" );
			printf( "  'e' ... enabled the protocol stack.\n" );
			printf( "  's' ... show current status.\n" );
			printf( "  'q' ... quit application.\n" );
			printf( "  'h' ... this information.\n" );
			printf( "\n" );
			printf( "Copyright 2006 Christian Walter <wolti@sil.at>\n" );

		}
		else
		{
			printf(  "illegal command!\r\n");
		}
		while(1)
		{
			sleep(20);
		}

		/* Release hardware resources. */
		( void )eMBClose(  );
		iExitCode = EXIT_SUCCESS;
	}
	return iExitCode;
}

BOOL
bCreatePollingThread( void )
{
	BOOL            bResult;
	pthread_t       xThread;

	if( eGetPollingThreadState(  ) == STOPPED )
	{
		if( pthread_create( &xThread, NULL, pvPollingThread, NULL ) != 0 )
		{
			bResult = FALSE;
		}
		else
		{
			bResult = TRUE;
		}
	}
	else
	{
		bResult = FALSE;
	}

	return bResult;
}

void           *
pvPollingThread( void *pvParameter )
{
	vSetPollingThreadState( RUNNING );

	if( eMBEnable(  ) == MB_ENOERR )
	{
		do
		{
			if( eMBPoll(  ) != MB_ENOERR )
				break;
			usRegInputBuf[0] = ( USHORT ) rand(  );

		}
		while( eGetPollingThreadState() != SHUTDOWN );
	}

	( void )eMBDisable(  );

	vSetPollingThreadState( STOPPED );

	return 0;
}

enum ThreadState
eGetPollingThreadState(  )
{
	enum ThreadState eCurState;

	( void )pthread_mutex_lock( &xLock );
	eCurState = ePollThreadState;
	( void )pthread_mutex_unlock( &xLock );

	return eCurState;
}

void
vSetPollingThreadState( enum ThreadState eNewState )
{
	( void )pthread_mutex_lock( &xLock );
	ePollThreadState = eNewState;
	( void )pthread_mutex_unlock( &xLock );
}

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;
//	printf("eMBRegInputCB %d %d\n",usAddress,usNRegs);
	if( ( usAddress >= REG_INPUT_START )
	        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
	{
		iRegIndex = ( int )( usAddress - usRegInputStart );
		while( usNRegs > 0 )
		{
			*pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
			*pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
			iRegIndex++;
			usNRegs--;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}

	return eStatus;
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex = 0;
    float           float_tmp = 0;
    float_tmp = register_value[61];

	printf("eMBRegHoldingCB %d %d %f\n",usAddress,usNRegs,register_value[1]);


    printf("----------------------------------------------------------\n");

	if( ( usAddress >= REG_HOLDING_START ) &&
	        ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
	{
        iRegIndex = ( int )( usAddress - usRegHoldingStart );
        switch ( eMode )
		{
			/* Pass current register values to the protocol stack. */
		case MB_REG_READ:
			while( usNRegs > 0 )
			{

//				usRegHoldingBuf[iRegIndex] = ( UCHAR ) *((UCHAR*)(&float_tmp) + 3 ) << 8 |( UCHAR ) *((UCHAR*)(&float_tmp) + 2);
//                usRegHoldingBuf[iRegIndex] = ( UCHAR ) *((UCHAR*)(&float_tmp) + 1 ) << 8 |( UCHAR ) *((UCHAR*)(&float_tmp));
//              buff是8位的，数组是16位的，显示是32位的，单个id也是16位
                if(iRegIndex < REG_HOLDING_NREGS - 1) //因为129为空，因为是<号所以-1就行
                {
                    *pucRegBuffer++ = ( UCHAR )( usRegHoldingBuf[iRegIndex] >> 8 );//( UCHAR ) *((UCHAR*)(&float_tmp) + 3 - 2*i)
                    *pucRegBuffer++ = ( UCHAR )( usRegHoldingBuf[iRegIndex] & 0xFF );//( UCHAR ) *((UCHAR*)(&float_tmp) + 3 - 2*i -1);
                    iRegIndex++;
                }
                else
                {
                    *pucRegBuffer++ = 0;
                    *pucRegBuffer++ = 0;
                }
//                printf("eMBRegHoldingCB %d %d %f\n",usAddress,usNRegs,register_value[usNRegs]);
                usNRegs--;
			}
			break;

			/* Update current register values with new values from the
			 * protocol stack. */
		case MB_REG_WRITE:
			while( usNRegs > 0 )
			{
				usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
				usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
				iRegIndex++;
				usNRegs--;
			}
			break;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}



eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	return MB_ENOREG;
}
