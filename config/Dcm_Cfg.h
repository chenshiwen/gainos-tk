/* Copyright(C) 2013, GaInOS-TK by Fan Wang. All rights reserved.
 * Generated by GaInOS-TK Studio at 2013-05-30:21-03-38.
 * Don't Modify it by hand.
 * Email: parai@foxmail.com
 * URL: https://github.com/parai/gainos-tk  && http://hi.baidu.com/parai
 */

#ifndef DCM_CFG_H_
#define DCM_CFG_H_

#define DCM_VERSION_INFO_API              STD_ON
#define DCM_DEV_ERROR_DETECT              STD_ON
#define DCM_RESPOND_ALL_REQUEST           STD_ON  // Activate/Deactivate response on SID 0x40-0x7f and 0xc0-0xff.
#define DCM_REQUEST_INDICATION_ENABLED    STD_ON  // Activate/Deactivate indication request mechanism.
#define DCM_PAGEDBUFFER_ENABLED           STD_OFF	// Enable/disable page buffer mechanism (currently only disabled supported)

#define DCM_DSL_BUFFER_LIST_LENGTH		4
#define DCM_DSL_TX_PDU_ID_LIST_LENGTH		2
#define DCM_DSL_RX_PDU_ID_LIST_LENGTH		2

#define DCM_MAIN_FUNCTION_PERIOD_TIME_MS	10

#define DCM_LIMITNUMBER_PERIODDATA		10  //MaxNumberofSimultaneousPeriodictransmissions
#define DCM_MAX_DDDSOURCE_NUMBER			10  //MaxSourcesforOneDynamicIdentifier
#define DCM_MAX_DDD_NUMBER				10  //MaxNegativeResponse

#define DCM_PERIODICTRANSMIT_SLOW			10
#define DCM_PERIODICTRANSMIT_MEDIUM		11
#define DCM_PERIODICTRANSMIT_FAST			12

#define DCM_RX_vEcuC_Pdu_0 0
#define DCM_RX_vEcuC_Pdu_1 1

#define DCM_TX_vEcuC_Pdu_0 0
#define DCM_TX_vEcuC_Pdu_1 1


#define USE_PDUR

#endif /*DCM_CFG_H_*/

