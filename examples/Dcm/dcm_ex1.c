#include "Os.h"
#include "Dcm.h"
#include "Can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "PduR.h"
#include <stdio.h>
/* 通知回调函数 */
Std_ReturnType vSecurityLevel_1_GetSeed (uint8 *securityAccessDataRecord, uint8 *seed, 
                        Dcm_NegativeResponseCodeType *errorCode)
{
    printf("in vSecurityLevel_1_GetSeed().\r\n");
    *seed = 0xEF;
    *errorCode = E_OK;
    return E_OK;
}
Std_ReturnType vSecurityLevel_1_CompKey (uint8 *key)
{
    printf("in vSecurityLevel_1_CompKey().\r\n");
    if(*key == 0xEF)
    {
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}

Std_ReturnType vSecurityLevel_Locked_GetSeed (uint8 *securityAccessDataRecord, uint8 *seed, 
                            Dcm_NegativeResponseCodeType *errorCode)
{
    printf("in vSecurityLevel_Locked_GetSeed().\r\n");
    *seed = 0xEF;
    *errorCode = E_OK;
    return E_OK;
}
Std_ReturnType vSecurityLevel_Locked_CompKey (uint8 *key)
{
    printf("in vSecurityLevel_Locked_CompKey().\r\n");
    if(*key == 0xEF)
    {
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}

Std_ReturnType vRequestService_1_Start (Dcm_ProtocolType protocolID)
{
     printf("in vRequestService_1_Start().\r\n");
    return E_OK;
}
Std_ReturnType vRequestService_1_Stop (Dcm_ProtocolType protocolID)
{
    printf("in vRequestService_1_Stop().\r\n");
    return E_OK;
}

Std_ReturnType vSessionControl_1_GetSesChgPer(Dcm_SesCtrlType sesCtrlTypeActive, 
                                            Dcm_SesCtrlType sesCtrlTypeNew)
{
    printf("in vSessionControl_1_GetSesChgPer().\r\n");
    return E_OK;
}
Std_ReturnType vDid_1_ReadDataLength_Cbk(uint16 *didLength){
    static uint8 callcnt = 0;
    printf("in  vDid_1_ReadDataLength_Cbk().\r\n");
    if(callcnt == 0)
    {
        *didLength = 128;   //for read test
    }
    else
    {
        *didLength = 4;    //for write test
    }
    callcnt++;
    if(callcnt == 2)
    {
       callcnt = 0; 
    }
    return E_OK;
}
Std_ReturnType vDid_1_ConditionCheckRead_Cbk(Dcm_NegativeResponseCodeType *errorCode){
    *errorCode = DCM_E_POSITIVERESPONSE;
    printf("in  vDid_1_ConditionCheckRead_Cbk().\r\n");
    return E_OK;
}
Std_ReturnType vDid_1_ReadData_Cbk(uint8 *data){
    int i;
    printf("in  vDid_1_ReadData_Cbk().\r\n");
    for(i=0;i<128;i++)
    {
        data[i] = i;
    }
    return E_OK;
}
Std_ReturnType vDid_1_ConditionCheckWrite_Cbk(Dcm_NegativeResponseCodeType *errorCode){
    *errorCode = DCM_E_POSITIVERESPONSE;
    printf("in  vDid_1_ConditionCheckWrite_Cbk().\r\n");
    return E_OK;
}
Std_ReturnType vDid_1_WriteData_Cbk(uint8 *data, uint16 dataLength, 
                Dcm_NegativeResponseCodeType *errorCode){
    int i;
    *errorCode = DCM_E_POSITIVERESPONSE;
    printf("in  vDid_1_WriteData_Cbk().\r\n[");
    for(i=0;i<dataLength;i++)
    {
        printf("0x%x,",data[i]);
    }
    printf("]\r\n");
    return E_OK;               
}
Std_ReturnType vDid_1_GetScalingInfo_Cbk(uint8 *scalingInfo, 
                Dcm_NegativeResponseCodeType *errorCode){
    *errorCode = DCM_E_POSITIVERESPONSE;
    scalingInfo[0] = 0xEE;
    printf("in  vDid_1_GetScalingInfo_Cbk().\r\n[");
    return E_OK;
}
Std_ReturnType vRequestService_1_Indication(uint8 *requestData, uint16 dataSize)
{
    printf("in  vRequestService_1_Indication().\r\n[");
    return E_OK;
}
Std_ReturnType vRoutine_1_Start(uint8 *inBuffer, uint8 *outBuffer, 
                            Dcm_NegativeResponseCodeType *errorCode)
{
    *errorCode = DCM_E_POSITIVERESPONSE;
    outBuffer[0] = 0xBF;
    printf("in  vRoutine_1_Start().\r\n[");
    return E_OK;   
}
Std_ReturnType vRoutine_1_Stop(uint8 *inBuffer, uint8 *outBuffer, 
                            Dcm_NegativeResponseCodeType *errorCode)
{
    *errorCode = DCM_E_POSITIVERESPONSE;
    outBuffer[0] = 0xEF;
    printf("in  vRoutine_1_Stop().\r\n[");
    return E_OK; 
}
Std_ReturnType vRoutine_1_RequestResult(uint8 *outBuffer, Dcm_NegativeResponseCodeType *errorCode)
{
    *errorCode = DCM_E_POSITIVERESPONSE;
    outBuffer[0] = 0xDB;
    printf("in  vRoutine_1_RequestResult().\r\n[");
    return E_OK; 
}
/* Dcm Example Initialise Routine.
 * 初始化Can、CanIf、PduR和DCM ，
 * 需要使用“dcm_ex1.arxml”生成其相应配置文件。*/
void DcmEx1Init(void)
{
    Can_Init(&Can_ConfigData); 
    CanIf_Init(&CanIf_Config);
    CanTp_Init();
    PduR_Init(&PduR_Config);
    Dcm_Init();
    //启动配置的两个CAN通道 CAN_CTRL_0 和 CAN_CTRL_1
    CanIf_SetControllerMode(vCanIf_Channel_0,CANIF_CS_STARTED);
    CanIf_SetControllerMode(vCanIf_Channel_1,CANIF_CS_STARTED);
}

/* Dcm Example Main Function Routine.
 * 这个API必须被周期性的调用，建议每 5ms 一次*/
void DcmEx1MainFunction(void)
{
    CanTp_MainFunction();
    Dcm_MainFunction();
}
#define ISO15765_TPCI_SF        0x00  /* Single Frame */
static void ex1DiagnosticSessionControl(void)
{
    static uint8 callcnt = 0;
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF | 2;
    sduData[1] = 0x10;
    callcnt++;
    switch(callcnt)
    {
        case 1:
            sduData[2] = 0x01;  //default Session
        break;
        case 2:
            sduData[2] = 0x02;  //program Session
        break;
        case 3:
            sduData[2] = 0x03;  //extended Session
        break;
        case 4:
            sduData[2] = 0x04;  //safety system Session
        break;
        default:
            callcnt = 0;
        break;
    }
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 3;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}
static void ex1SecurityAccess_RequestSeed(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF|2;
    sduData[1] = 0x27;
    sduData[2] = 0x01|(1<<1);   //requestSeed,want to set level 1
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 3;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}
static void ex1SecurityAccess_SendKey(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF | 3;
    sduData[1] = 0x27;
    sduData[2] = 0x02;   //sendKey,want to set level 1
    sduData[3] = 0xEF;
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 4;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}
static void ex1ReadDataById(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF | 3;
    sduData[1] = 0x22;
    sduData[2] = 0x09;   //id = 0x0999;
    sduData[3] = 0x99;
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 4;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}
static void ex1WriteDataById(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF | 7;
    sduData[1] = 0x2E;
    sduData[2] = 0x09;   //id = 0x0999;
    sduData[3] = 0x99;
    sduData[4] = 0x11;
    sduData[5] = 0x22;
    sduData[6] = 0x33;
    sduData[7] = 0x44;
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 8;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}
static void ex1RoutineControl(void)
{
    uint8  sduData[8];
    static uint8 callcnt = 0;
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF | 4;
    sduData[1] = 0x31;
    callcnt++;
    switch(callcnt)
    {
        case 1:
            sduData[2] = 0x01;  //start routine
        break;
        case 2:
            sduData[2] = 0x02;  //stop routine
        break;
        case 3:
            sduData[2] = 0x03;  //request routine result
        break;
        default:
            callcnt = 3;
            return;
        break;
    }
    sduData[3] = 0x08;   //id = 0x0888;
    sduData[4] = 0x88;
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 5;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}

static void ex1ReadScalingDataById(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF | 3;
    sduData[1] = 0x24;
    sduData[2] = 0x09;   //id = 0x0999;
    sduData[3] = 0x99;
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 4;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}

static void ex1TesterPresent(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = ISO15765_TPCI_SF | 2;
    sduData[1] = 0x3e;
    sduData[2] = 0x00; 
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 3;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}

static void ex1EcuReset(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    static uint8 callcnt = 0;
    sduData[0] = ISO15765_TPCI_SF | 2;
    sduData[1] = 0x11;
    callcnt++;
    switch(callcnt)
    {
        case 1:
            sduData[2] = 0x01;  //hard reset,infact only this sub function was supported.
                // But as Mcu was not integrated,So this API has no effect.
        break;
        case 2:
            sduData[2] = 0x02;  //key off on reset
        break;
        case 3:
            sduData[2] = 0x03;  //soft reset
        break;
        case 4:
            sduData[2] = 0x04;
        break;
        case 5:
            sduData[2] = 0x05;
        break;
        default:
            callcnt = 5;
            return;
        break;
    }  
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 3;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}
// this is the Client reveiver
void CanIf_UserRxIndication(uint8 channel, PduIdType pduId, const uint8 *sduPtr,
                           uint8 dlc, Can_IdType canId)
{
    int len = dlc;
    char* ptr= sduPtr;
    static int fcnt = 0;
    printf("channel=%d,pduId=%d,canId=%d.\r\r\n",(int)channel,(int)pduId,(int)canId);
    printf("[");      
    while(len > 0)
    {
        printf("0x%x,",(uint8)(*ptr));
        ptr++;
        len--;
    }
    printf("]\r\n");
    //if it is FF or CF,send FC 
    switch (sduPtr[0] & 0x30) {
	case 0x10:       //First Frame
		SetEvent(ID_vTaskReceiver,0x01);
		fcnt = 0;
		break;
	case 0x20:       //Consecutive Frame
		fcnt ++;
		if(3 == fcnt)
		{
		    SetEvent(ID_vTaskReceiver,0x01);
	    	fcnt = 0;
		}
		break;
	}   
}
static void ex1SendFC(void)
{
    uint8  sduData[8];
    PduInfoType pduinfo;
    sduData[0] = 0x30;  /* Flow Control */
    sduData[1] = 3;    //BS
    sduData[2] = 10;   //stmin
    pduinfo.SduDataPtr = sduData;
    pduinfo.SduLength = 3;
    
    CanIf_Transmit(vCanIf_Channel_0, &pduinfo);
}
void Dcm_Ex1Receiver(void)
{
    WaitEvent(0x01);
    ClearEvent(0x01);
    ex1SendFC();   
}
void DcmEx1Sender(void)
{
    
    static uint8 callcnt = 0;
    /* 摆在我面前的难题，没有专业的CAN调试设备，我将如何测试DCM */
    /* 使用CanIf来发送SF，模拟 Client */
    callcnt++; 
    switch(callcnt)
    {
        case 1:
            ex1SecurityAccess_RequestSeed(); //try to get the seed              
        break;
        case 2:
            ex1SecurityAccess_SendKey();    //try to unlock for level 1
        break;
        case 3:
            ex1DiagnosticSessionControl();    //now,unlocked, can do session control on level 1   
        break;
        case 4:
            ex1ReadDataById();
        break;
        case 5:
            ex1WriteDataById();
        break;
        case 6:
            ex1RoutineControl();
        break; 
        case 7:
            ex1ReadScalingDataById();
        break;
        case 8:
            ex1TesterPresent();
        break;
        case 9:
            ex1EcuReset();
        break;
        default:
            callcnt = 3;
        break;
    }     
}
//============================= OS TASK ==============================
extern void DcmEx1Init(void);
#include "osek_os.h"
TASK(vTaskInit)
{
	StatusType ercd;
	(void)SetRelAlarm(ID_vAlarmReceiver,50,10);
	(void)SetRelAlarm(ID_vAlarmSender,100,200);
	(void)SetRelAlarm(ID_vAlarmMainFunction,200,1); //so cyclic 1 Ticks = 4ms
	
	DcmEx1Init();
    /* Add your task special code here, but Don't delete this Task declaration.*/
    (void)printf("vTaskInit is running.\r\n");

    (void)TerminateTask();
}
extern void DcmEx1Sender(void);
TASK(vTaskSender)
{
    /* Add your task special code here, but Don't delete this Task declaration.*/
    DcmEx1Sender();
    (void)TerminateTask();
}
extern void Dcm_Ex1Receiver(void);
TASK(vTaskReceiver)
{
    /* Add your task special code here, but Don't delete this Task declaration.*/
    //(void)printf("vTaskReceiver is running.\r\n");
    Dcm_Ex1Receiver();
    (void)TerminateTask();
}
extern void DcmEx1MainFunction(void);
TASK(vTaskMainFunction)
{
    /* Add your task special code here, but Don't delete this Task declaration.*/
    //(void)printf("vTaskMainFunction is running.\r\n");
    DcmEx1MainFunction();
    (void)TerminateTask();
}

ALARM(vAlarmSender)
{
    /* Alarm Type: Task, you still can add your special code here.*/
    (void)ActivateTask(ID_vTaskSender);
}
ALARM(vAlarmReceiver)
{
    /* Alarm Type: Task, you still can add your special code here.*/
    (void)ActivateTask(ID_vTaskReceiver);
}
ALARM(vAlarmMainFunction)
{
    /* Alarm Type: Task, you still can add your special code here.*/
    (void)ActivateTask(ID_vTaskMainFunction);
}
