#include "include.h"

struct uart4data_t frameData;


u16 CalCRC(char str[], u8 len)
{
	u32 sum = 0;
	while (len) {
		sum += str[--len];
	}
	return sum % 256;
}

/*********************************************************************************************************
**                           TaskPC PC´®¿ÚÈÎÎñ
********************************************************************************************************/
void TaskPC(void *pdata)
{
	struct sys_ctl *sysctl = pdata;
	u8 keyBufTmp;

	char frameIDStr[3] = {0, 0, 0};
	char frameAIStr[2] = {0, 0};
	char framePFCStr[3] = {0, 0, 0};
	char frameValueStr[7] = {0, 0, 0, 0, 0, 0, 0};
	char frameCRCStr[4] = {0, 0, 0, 0};
	
	char SendDataStr[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char SendCRCStr[4] = {0, 0, 0, 0};
	char SendFrameStr[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0A, 0};

		
	u8 sendPressCnt = 0;
	
	while(1) {
		OSTimeDly(10);
		
		if (frameData.STX == '!' && frameData.ETX == 0x0A && frameData.revLen == 16) {
			sysctl->controlMode = 1;
			frameData.revLen = 0;
//			frameData.CRC = 0;
			memcpy(frameIDStr, frameData.revData + 1, 2);
			frameData.ID = atoi(frameIDStr);
			memcpy(frameAIStr, frameData.revData + 3, 1);
			frameData.AI = atoi(frameAIStr);
			memcpy(framePFCStr, frameData.revData + 4, 2);
			frameData.PFC = atoi(framePFCStr);
			memcpy(frameValueStr, frameData.revData + 6, 6);
			frameData.VALUE = atoi(frameValueStr);
			memcpy(frameCRCStr, frameData.revData + 12, 3);
			frameData.CRCCode = atoi(frameCRCStr);
			if (frameData.CRCCode != CalCRC(frameData.revData, 12)) 
				UART4_Putc(NACK);
			if (frameData.PFC != 1 && frameData.ID != EQUID) 
				UART4_Putc(NACK);
			switch (frameData.PFC) {
			case 1:
				sprintf(SendDataStr, "!%2d001    %2d", EQUID, EQUID);
				sprintf(SendCRCStr, "%03d", CalCRC(SendDataStr, 12));
				memcpy(SendFrameStr, SendDataStr, 12);
				memcpy(SendFrameStr+12, SendCRCStr, 3);
				UART4_Puts(SendFrameStr);
				break;
			case 2:
				
				UART4_Putc(ACK);
				break;
			case 3:
				sprintf(SendDataStr, "!%2d003%s", EQUID, EQUSERNO);
				sprintf(SendCRCStr, "%03d", CalCRC(SendDataStr, 12));
				memcpy(SendFrameStr, SendDataStr, 12);
				memcpy(SendFrameStr+12, SendCRCStr, 3);
				UART4_Puts(SendFrameStr);
				break;
			case 4:
				
				UART4_Putc(ACK);
				break;
			case 6:
				
				UART4_Putc(ACK);
				break;
			case 9:
				
				UART4_Putc(ACK);
				break;
			case 10:
				if (frameData.VALUE <= 9999) {
					sysctl->setFlow = frameData.VALUE;
					PumpSetFlow(sysctl->setFlow);
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 11:
				if (frameData.VALUE <= 1000 && (frameData.AI >= 1 && frameData.AI <= 4)) {
					
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 13:
				if (frameData.VALUE <= 4200) {
					sysctl->pressMax = frameData.VALUE;
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 14:
				if (frameData.VALUE <= sysctl->pressMax) {
					sysctl->pressMin = frameData.VALUE;
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				UART4_Putc(ACK);
				break;
			case 15:
//				if (GetFlowPara(sysctl->setFlow) < 20) {
//					TIM2->PSC = 360;
//					PumpCtl.dstInterval = 100000 / GetFlowPara(sysctl->setFlow);
//				} else {
//					TIM2->PSC = 36;
//					PumpCtl.dstInterval = 1000000 / GetFlowPara(sysctl->setFlow);
//				}
//				if (sysctl->flowMode == 9)
//					PumpCtl.maxTime = sysctl->purgeFlow * 100;
//				else 
//					PumpCtl.maxTime = (0xffffffff / (2000000 / (PumpCtl.dstInterval-1)) * 100);
//				PumpStart(sysctl->setFlow);
				keyBufTmp = KEYPUMP;
				OSMboxPostOpt(KeyMbox, (void *)&keyBufTmp, OS_POST_OPT_BROADCAST);
				UART4_Putc(ACK);
				break;
			case 16:
//				PumpStop();
				keyBufTmp = KEYSTOP;
				OSMboxPostOpt(KeyMbox, (void *)&keyBufTmp, OS_POST_OPT_BROADCAST);
				UART4_Putc(ACK);
				break;
			case 17:

				UART4_Putc(ACK);
				break;
			case 18:
				if (frameData.VALUE <= 100) {
					sysctl->sendPressInterval = frameData.VALUE;
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 19:
				if (frameData.VALUE <= 5) {
					sysctl->pumpMode = 	frameData.VALUE;		
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 40:
				if (frameData.VALUE <= 999999 && frameData.AI <= 9) {
				
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 41:
				if (frameData.VALUE <= 9999) {
				
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 42:
				if (frameData.VALUE <= 999999) {
				
					UART4_Putc(ACK);
				} else {
					UART4_Putc(NACK);
				}
				break;
			case 43:
				
				UART4_Putc(ACK);
				break;
			case 44:
				
				UART4_Putc(ACK);
				break;
			default:
				UART4_Putc(NACK);
				break;
			}
		} else {
			sendPressCnt++;
			if (sysctl->sendPressInterval != 0 && sendPressCnt >= sysctl->sendPressInterval * 5) {
				sprintf(SendDataStr, "!%2d090%06d", EQUID, sysctl->nowPress);
				sprintf(SendCRCStr, "%03d", CalCRC(SendDataStr, 12));
				memcpy(SendFrameStr, SendDataStr, 12);
				memcpy(SendFrameStr+12, SendCRCStr, 3);
				UART4_Puts(SendFrameStr);
			}
		}
		
	}
}
