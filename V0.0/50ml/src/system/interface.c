#include "include.h"

//开机界面
void interface0(void)
{
//	u16 i;
//	SED1335_clear_graphics_layer();	  				
//	writestring(7,64,64,64,Bmp,0);
//	writestring(15,64,160,32,AccuTarget,0); 
//	writestring(15,104,160,16,PinPai,0);
//	
//	writestring(3,156,104,16,Initial,0);
	
//	writestring(33,104,32,16,Pai,0); 
//------------------------------------------------------------	
//	writestring(1,170,48,16,BmpGLB,0);	
//	for(i=0;i<=32;i++)	{	writestring(7+i,178,8,1,BmpHLine,0);}
//	for(i=1;i<=38;i++)	{ writestring(i,230,8,1,BmpHLine,0);}
//	for(i=0;i<52;i++)	{	writestring(0,178+i,8,1,BmpSLine,0);}
//	for(i=0;i<52;i++)	{	writestring(39,178+i,8,1,BmpSLine,0);}
//	writestring(0,178,8,1,BmpLineL,0); 
//	writestring(0,230,8,1,BmpLineL,0);
//	writestring(39,178,8,1,BmpLineR,0); 
//	writestring(39,230,8,1,BmpLineR,0);
//	writestring(1,192,0,24,BmpNull,1);
//	OSTimeDly(1000);
//	OSTimeDly(1000);
//	writestring(4,32,48,24,ShiJian,0);	  //??"??"
//	writestring(15,32,48,24,WenDu,0);	  //??"??"
//	writestring(24,32,48,24,ZhuangTai,0); //??"??"
//	writestring(32,32,48,24,GongLv,0);	  //??"??"//	SendSPIStr("Port 1 is Selected");
//------------------------------------------------------------	
//	writestring(1,170,48,16,BmpGLB,0);	
//	for(i=1;i<=33;i++)	writestring(i,213,8,1,BmpHLine,0);
//	for(i=1;i<=33;i++)	writestring(i,238,8,1,BmpHLine,0);
//	for(i=0;i<25;i++)	writestring(0,213+i,8,1,BmpSLine,0);
//	for(i=0;i<25;i++)	writestring(33,213+i,8,1,BmpSLine,0);
//	writestring(0,213,8,1,BmpLineL,0); 
//	writestring(0,238,8,1,BmpLineL,0);
//	writestring(33,213,8,1,BmpLineR,0); 
//	writestring(33,238,8,1,BmpLineR,0);
//	
//	writestring(1,218,8*5*32/18,16,BmpNull,1);
//	writestring(5*32/18+1,218,240-8*5*32/18,16,BmpNull,0);
//	
//	writestring(34,218,8,16,Sign16,0);
//	writestring(35,218,8,16,(Num16+(abs(0)%10000/1000)*16),0);
//	writestring(36,218,8,16,(Num16+(abs(0)%1000/100)*16),0);
//	writestring(37,218,8,16,(Num16+(abs(0)%100/10)*16),0);
//	writestring(38,218,8,16,Dian16,0);
//	writestring(39,218,8,16,(Num16+(abs(0)%10)*16),0);
	ShowBlock();
//	interface_show();
}

void interface_show(void)
{
	ShowHZ1616Str(1, 5, "流量", 0);ShowASCII816Str(1+8, 5, "(ml)", 1);ShowASCII816Str(1+8+9, 5, "M", 0);
	ShowHZ1616Str(28, 5, "压力", 0);ShowASCII816Str(28+8, 5, "(Mpa)", 1);
	ShowHZ1616Str(54, 16, "设置", 0);
	ShowHZ1616Str(54, 31, "信息", 0);
	ShowHZ1616Str(54, 47, "系统", 0);
	ShowHZ1616Str(54, 1, "显示", 1);
	ShowHZ1616Str(1, 5, "流量", 1);
	
	ShowASCII1624Str(4, 26, "0.100", 0);
	ShowASCII1624Str(30, 26, "+00.00", 0);
}

/*********************************************************************************************************
**                           TaskMain 系统主任务
********************************************************************************************************/
void TaskMain(void *pdata)
{
	struct sys_ctl *sysctl = pdata;
	u8 *keyVal;
	u8 DisTabs = 0;
	u8 SetTab0Pos[] = {1, 0, 0};
	u8 SetTab0PosIndex = 0;
	u8 SetTab1Pos[] = {1, 0, 0, 0, 0, 0};
	u8 SetTab1PosIndex = 0;
	
	char PumpModeStr[] = "A";
	
	u8 SetFlowPos[] = {0, 0, 0, 0};
	u8 SetFlowPosIndex;
	char FlowStr[] = "00.00";
	u8 SetFlowMode = 0;
	
	u8 SetPressMaxPos[] = {0, 0, 0, 0};
	u8 SetPressMaxPosIndex;
	char PressMaxStr[] = "00.00";
	u8 SetPressMinPos[] = {0, 0, 0, 0};
	u8 SetPressMinPosIndex;
	char PressMinStr[] = "00.00";
	u8 SetPurgeFlowPos[] = {0, 0, 0, 0};
	u8 SetPurgeFlowPosIndex;
	char PurgeFlowStr[] = "00.00";
//	u8 SetLuminStepPos = 9;
	char LuminStepStr[] = "  9";
	char KeyBeepStr[] = "   开";
	
	u8 SetShowCntPage = 0;
	char ShowCntStr[] = "00000";
	char ShowPressStr[] = "0000";
	
	char NowPressStr[] = "+00.00";
	
	ShowBlock();
	ShowHZ1616Str(1, 5, "流量", SetTab0Pos[0]);ShowASCII816Str(1+8, 5, "(ml)", SetTab0Pos[0]);
	ShowASCII816Str(1+8+9, 5, (SetFlowMode == 1? "M": "A"), SetTab0Pos[1]);
	ShowHZ1616Str(28, 5, "压力", SetTab0Pos[2]);ShowASCII816Str(28+8, 5, "(Mpa)", SetTab0Pos[2]);
	ShowHZ1616Str(54, 16, "设置", 0);
	ShowHZ1616Str(54, 31, "信息", 0);
	ShowHZ1616Str(54, 47, "系统", 0);
	ShowHZ1616Str(54, 1, "显示", 1);

	sprintf(FlowStr, "%02d.%02d", sysctl->setFlow/100, sysctl->setFlow%100);
	ShowASCII1624Str(4, 26, FlowStr, 0);
	PumpModeStr[0] = sysctl->pumpMode - 1 + 'A';
	ShowASCII816Str(22, 23, PumpModeStr, 0);

	ShowASCII1624Str(30, 26, "+00.00", 0);

	while(1) {
		if (PumpCtl.nowState != 1) Write_Flash(sysctl);
		if (DisTabs == 0) {		
			/*************泵控制模式**************/
			if (sysctl->controlMode == 1)
				ShowASCII816Str(22, 5, "P", 0);
			else
				ShowASCII816Str(22, 5, "K", 0);

			/*************串口接收后显示**************/
			if (sysctl->controlMode == 1) {
				PumpModeStr[0] = sysctl->pumpMode - 1 + 'A';
				ShowASCII816Str(22, 23, PumpModeStr, 0);
				sprintf(FlowStr, "%02d.%02d", sysctl->setFlow/100, sysctl->setFlow%100);
				ShowASCII1624Str(4, 26, FlowStr, 0);
			}
			
			/*************压力检测**************/
			sysctl->nowPress = GetPressure();
			if ((sysctl->nowPress - sysctl->pressOffset) >= 0)
				sprintf(NowPressStr, "+%02d.%02d", (sysctl->nowPress - sysctl->pressOffset)/100, (sysctl->nowPress - sysctl->pressOffset)%100);
			else
				sprintf(NowPressStr, "-%02d.%02d", abs(sysctl->nowPress - sysctl->pressOffset)/100, abs(sysctl->nowPress - sysctl->pressOffset)%100);
			ShowASCII1624Str(30, 26, NowPressStr, 0);
		} else if (DisTabs == 1) {
			/*************压力检测**************/
			if (sysctl->controlMode == 1) {
				sprintf(PressMaxStr, "%02d.%02d", sysctl->pressMax/100, sysctl->pressMax%100);
				ShowASCII816Str(1+8+5, 4, PressMaxStr, 0);
				sprintf(PressMinStr, "%02d.%02d", sysctl->pressMin/100, sysctl->pressMin%100);
				ShowASCII816Str(1+8+5, 24, PressMinStr, 0);
			}
		}
			

			/*************压力保护**************/
		if (sysctl->nowPress >= sysctl->pressMax || sysctl->nowPress < sysctl->pressMin) sysctl->pressProtect = 1;

		if (sysctl->flowMode == 0) {
			char AccCntStr[] = "0000000000";
			sprintf(AccCntStr, "% 9d", TIM2->ARR);
//			sprintf(AccCntStr, "%f.1", calPID);
			ShowASCII816Str(1, 50, AccCntStr, 0);
			sprintf(AccCntStr, "% 9d", (u32)(PumpCtl.calCnt - PumpCtl.accCnt));
//			sprintf(AccCntStr, "%06d", (u32)(PumpCtl.calCnt));
			ShowASCII816Str(20, 50, AccCntStr, 0);
		} else if (sysctl->flowMode == 1) {
			char AccCntStr[] = "0000000000               ";
			sprintf(AccCntStr, "%06d             ", PumpCtl.accCnt);
			ShowASCII816Str(1, 50, AccCntStr, 0);		
		} else if (sysctl->flowMode == 9) {
			char AccCntStr[] = "0000000000               ";
			sprintf(AccCntStr, "%06d             ", PumpCtl.accCnt);
			ShowASCII816Str(1, 50, AccCntStr, 0);		
		}
		
		OSTimeDly(100);
		if ((keyVal = OSMboxAccept(KeyMbox)) != NULL) {
			switch (*keyVal) {
			case KEYPUMP:
				if (GetFlowPara(sysctl->setFlow) < 20) {
					TIM2->PSC = 360;
					PumpCtl.dstInterval = 100000 / GetFlowPara(sysctl->setFlow);
				} else {
					TIM2->PSC = 36;
					PumpCtl.dstInterval = 1000000 / GetFlowPara(sysctl->setFlow);
				}
				if (sysctl->flowMode == 9)
					PumpCtl.maxTime = sysctl->purgeFlow * 100;
				else 
					PumpCtl.maxTime = (0xffffffff / (2000000 / (PumpCtl.dstInterval-1)) * 100);
				PumpStart(sysctl->setFlow);
				break;
			case KEYSTOP:
				PumpStop();
				break;
			case KEYPURGE:
				if (GetFlowPara(sysctl->purgeFlow) < 20) {
					TIM2->PSC = 360;
					PumpCtl.dstInterval = 100000 / GetFlowPara(sysctl->purgeFlow);
				} else {
					TIM2->PSC = 36;
					PumpCtl.dstInterval = 1000000 / GetFlowPara(sysctl->purgeFlow);
				}
				PumpCtl.maxTime = 3 * 60 * 100;
				PumpStart(sysctl->purgeFlow);
				break;
			}
			
			switch (*keyVal) {			
			case KEYTAB:
				DisTabs++;
				if (DisTabs == 4) 
					DisTabs = 0;
				switch (DisTabs) {
					case 0:
						Fill_RAM(0x00);
						ShowBlock();
						sprintf(FlowStr, "%02d.%02d", sysctl->setFlow/100, sysctl->setFlow%100);
						ShowHZ1616Str(1, 5, "流量", SetTab0Pos[0]);ShowASCII816Str(1+8, 5, "(ml)", SetTab0Pos[0]);
						switch (sysctl->flowMode) {
							case 0:ShowASCII816Str(1+8+9, 5, "A", SetTab0Pos[1]);break;
							case 1:ShowASCII816Str(1+8+9, 5, "M", SetTab0Pos[1]);break;
							case 9:ShowASCII816Str(1+8+9, 5, "T", SetTab0Pos[1]);break;
						}
//						ShowASCII816Str(1+8+9, 5, (sysctl->flowMode == 1? "M": "A"), SetTab0Pos[1]);
						ShowHZ1616Str(28, 5, "压力", SetTab0Pos[2]);ShowASCII816Str(28+8, 5, "(Mpa)", SetTab0Pos[2]);
						ShowHZ1616Str(54, 16, "设置", 0);
						ShowHZ1616Str(54, 31, "信息", 0);
						ShowHZ1616Str(54, 47, "系统", 0);
						ShowHZ1616Str(54, 1, "显示", 1);
						ShowASCII1624Str(4, 26, FlowStr, 0);
						ShowASCII1624Str(30, 26, "+00.00", 0);
						break;
					case 1:
						Fill_RAM(0x00);
						ShowBlock();
						sprintf(PressMaxStr, "%02d.%02d", sysctl->pressMax/100, sysctl->pressMax%100);
						sprintf(PressMinStr, "%02d.%02d", sysctl->pressMin/100, sysctl->pressMin%100);
						sprintf(PurgeFlowStr, "%02d.%02d", sysctl->purgeFlow/100, sysctl->purgeFlow%100);
						sprintf(LuminStepStr, "  %01d", sysctl->backLumin);
						if (sysctl->keyBeep == 1) sprintf(KeyBeepStr, "    开");
						else if (sysctl->keyBeep == 0) sprintf(KeyBeepStr, "    关");
						ShowHZ1616Str(1, 4, "上限", SetTab1Pos[0]);ShowASCII816Str(1+8, 4, ":", SetTab1Pos[0]);ShowASCII816Str(1+8+5, 4, PressMaxStr, 0);
						ShowHZ1616Str(1, 24, "下限", SetTab1Pos[1]);ShowASCII816Str(1+8, 24, ":", SetTab1Pos[1]);ShowASCII816Str(1+8+5, 24, PressMinStr, 0);
						ShowHZ1616Str(1, 44, "冲洗", SetTab1Pos[2]);ShowASCII816Str(1+8, 44, ":", SetTab1Pos[2]);ShowASCII816Str(1+8+5, 44, PurgeFlowStr, 0);
						ShowHZ1616Str(28, 4, "亮度", SetTab1Pos[3]);ShowASCII816Str(28+8, 4, ":", SetTab1Pos[3]);ShowASCII816Str(28+8+9, 4, LuminStepStr, 0);
						ShowHZ1616Str(28, 24, "按键", SetTab1Pos[4]);ShowASCII816Str(28+8, 24, ":", SetTab1Pos[4]);ShowHZ1616Str(28+8+3, 24, KeyBeepStr, 0);
						ShowHZ1616Str(28, 44, "语言", SetTab1Pos[5]);ShowASCII816Str(28+8, 44, ":", SetTab1Pos[5]);ShowHZ1616Str(28+8+3, 44, "  中文", 0);
						ShowHZ1616Str(54, 1, "显示", 0);
						ShowHZ1616Str(54, 31, "信息", 0);
						ShowHZ1616Str(54, 47, "系统", 0);
						ShowHZ1616Str(54, 16, "设置", 1);
						break;
					case 2:
						Fill_RAM(0x00);
						ShowBlock();
						ShowHZ1616Str(1, 4, "型号", 0);ShowASCII816Str(1+8, 4, ":", 0);ShowASCII816Str(1+8+5, 4, "P2010", 0);
						ShowHZ1616Str(1, 24, "版本", 0);ShowASCII816Str(1+8, 24, ":", 0);ShowASCII816Str(1+8+5, 24, "1.00A", 0);
						ShowHZ1616Str(1, 44, "日期", 0);ShowASCII816Str(1+8, 44, ":", 0);ShowASCII816Str(1+8+5, 44, "11.07", 0);
						ShowHZ1616Str(28, 4, "序号", 0);ShowASCII816Str(28+8, 4, ":", 0);ShowASCII816Str(28+8+5, 4, EQUSERNO, 0);
						ShowHZ1616Str(28, 24, "行程", 0);ShowASCII816Str(28+8, 24, ":", 0);ShowASCII816Str(28+8+5, 24, "00000", 0);
						ShowHZ1616Str(28, 44, "硬件", 0);ShowASCII816Str(28+8, 44, ":", 0);ShowASCII816Str(28+8+5, 44, "1.00A", 0);
						ShowHZ1616Str(54, 1, "显示", 0);
						ShowHZ1616Str(54, 16, "设置", 0);
						ShowHZ1616Str(54, 47, "系统", 0);
						ShowHZ1616Str(54, 31, "信息", 1);
						break;
					case 3:
						Fill_RAM(0x00);
						ShowBlock();
						if (SetShowCntPage == 0) {														
							ShowASCII816Str(1, 4, "0.05", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[0].cnt);ShowASCII816Str(1+8+5, 4, ShowCntStr, 0);
							ShowASCII816Str(1, 24, "0.10", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[1].cnt);ShowASCII816Str(1+8+5, 24, ShowCntStr, 0);
							ShowASCII816Str(1, 44, "0.20", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[2].cnt);ShowASCII816Str(1+8+5, 44, ShowCntStr, 0);
							ShowASCII816Str(28, 4, "0.50", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[3].cnt);ShowASCII816Str(28+8+5, 4, ShowCntStr, 0);
							ShowASCII816Str(28, 24, "01.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[4].cnt);ShowASCII816Str(28+8+5, 24, ShowCntStr, 0);
							ShowASCII816Str(28, 44, "02.50", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[5].cnt);ShowASCII816Str(28+8+5, 44, ShowCntStr, 0);
						} else if (SetShowCntPage == 1) {
							ShowASCII816Str(1, 4, "05.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[6].cnt);ShowASCII816Str(1+8+5, 4, ShowCntStr, 0);
							ShowASCII816Str(1, 24, "10.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[7].cnt);ShowASCII816Str(1+8+5, 24, ShowCntStr, 0);
							ShowASCII816Str(1, 44, "25.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[8].cnt);ShowASCII816Str(1+8+5, 44, ShowCntStr, 0);
							ShowASCII816Str(28, 4, "50.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[9].cnt);ShowASCII816Str(28+8+5, 4, ShowCntStr, 0);
							ShowASCII816Str(28, 24, " P.G.", 0);sprintf(ShowPressStr, " %04d", PUMP_PressArg.pg);ShowASCII816Str(28+8+5, 24, ShowPressStr, 0);
							ShowASCII816Str(28, 44, " P.Z.", 0);sprintf(ShowPressStr, " %01d.%02d", PUMP_PressArg.pz/100, PUMP_PressArg.pz%100);ShowASCII816Str(28+8+5, 44, ShowPressStr, 0);
						}	 
						ShowHZ1616Str(54, 1, "显示", 0);
						ShowHZ1616Str(54, 16, "设置", 0);
						ShowHZ1616Str(54, 31, "信息", 0);
						ShowHZ1616Str(54, 47, "系统", 1);
						break;
				}
				break;
			}
			
			if (DisTabs == 0) {
				switch (*keyVal) {
				case KEYRIGHT:
					SetTab0PosIndex++;
					if (SetTab0PosIndex < sizeof(SetTab0Pos)) {
						SetTab0Pos[SetTab0PosIndex - 1] = 0;
						SetTab0Pos[SetTab0PosIndex] = 1;
					} else {
						SetTab0Pos[SetTab0PosIndex - 1] = 0;
						SetTab0PosIndex = 0;
						SetTab0Pos[SetTab0PosIndex] = 1;
					}
					ShowHZ1616Str(1, 5, "流量", SetTab0Pos[0]);ShowASCII816Str(1+8, 5, "(ml)", SetTab0Pos[0]);
					ShowASCII816Str(1+8+9, 5, (sysctl->flowMode == 1? "M": "A"), SetTab0Pos[1]);
					ShowHZ1616Str(28, 5, "压力", SetTab0Pos[2]);ShowASCII816Str(28+8, 5, "(Mpa)", SetTab0Pos[2]);
					break;
				case KEYLEFT:
					if (SetTab0PosIndex > 0) {
						SetTab0Pos[SetTab0PosIndex] = 0;
						SetTab0Pos[SetTab0PosIndex - 1] = 1;
					SetTab0PosIndex--;
					} else {
						SetTab0Pos[SetTab0PosIndex] = 0;
						SetTab0PosIndex = sizeof(SetTab0Pos) - 1;
						SetTab0Pos[SetTab0PosIndex] = 1;
					}
					ShowHZ1616Str(1, 5, "流量", SetTab0Pos[0]);ShowASCII816Str(1+8, 5, "(ml)", SetTab0Pos[0]);
					ShowASCII816Str(1+8+9, 5, (sysctl->flowMode == 1? "M": "A"), SetTab0Pos[1]);
					ShowHZ1616Str(28, 5, "压力", SetTab0Pos[2]);ShowASCII816Str(28+8, 5, "(Mpa)", SetTab0Pos[2]);
					break;
				case KEYNUM1:
				case KEYNUM2:
				case KEYNUM3:
				case KEYNUM4:
				case KEYNUM5:
				case KEYNUM6:
				case KEYNUM7:
				case KEYNUM8:
				case KEYNUM9:
				case KEYNUM0:
					if (SetTab0PosIndex == 0) {
						for (SetFlowPosIndex = 1; SetFlowPosIndex < sizeof(SetFlowPos); ++SetFlowPosIndex)
							SetFlowPos[SetFlowPosIndex - 1] = SetFlowPos[SetFlowPosIndex];
						
						SetFlowPos[SetFlowPosIndex - 1] = (*keyVal == KEYNUM0? 0: *keyVal);
						FlowStr[0] = SetFlowPos[0] + 0x30;
						FlowStr[1] = SetFlowPos[1] + 0x30;
						FlowStr[2] = '.';
						FlowStr[3] = SetFlowPos[2] + 0x30;
						FlowStr[4] = SetFlowPos[3] + 0x30;
						ShowASCII1624Str(4, 26, FlowStr, 1);
					} else if (SetTab0PosIndex == 1 && PumpCtl.nowState != 1) {
						if (*keyVal == KEYNUM0) 
							sysctl->flowMode = 0;
						else if (*keyVal == KEYNUM1)
							sysctl->flowMode = 1;
						else if (*keyVal == KEYNUM9)
							sysctl->flowMode = 9;
						switch (sysctl->flowMode) {
							case 0:ShowASCII816Str(1+8+9, 5, "A", SetTab0Pos[1]);break;
							case 1:ShowASCII816Str(1+8+9, 5, "M", SetTab0Pos[1]);break;
							case 9:ShowASCII816Str(1+8+9, 5, "T", SetTab0Pos[1]);break;
						}
//						ShowASCII816Str(1+8+9, 5, (sysctl->flowMode == 1? "M": "A"), SetTab0Pos[1]);
					}					
					break;
				case KEYENT:
					if (SetTab0PosIndex == 0) {
						sysctl->setFlow = SetFlowPos[0] * 1000 + SetFlowPos[1] * 100 + SetFlowPos[2] * 10 + SetFlowPos[3] * 1;
						PumpSetFlow(sysctl->setFlow);
						ShowASCII1624Str(4, 26, FlowStr, 0);
					} else if (SetTab0PosIndex == 2 && PumpCtl.nowState != 1) {
						sysctl->pressOffset = sysctl->nowPress;
						ShowASCII1624Str(30, 26, "+00.00", 0);
					}	
					break;
				}			
			} else if (DisTabs == 1) {
				switch (*keyVal) {
				case KEYRIGHT:
					SetTab1PosIndex++;
					if (SetTab1PosIndex < sizeof(SetTab1Pos)) {
						SetTab1Pos[SetTab1PosIndex - 1] = 0;
						SetTab1Pos[SetTab1PosIndex] = 1;
					} else {
						SetTab1Pos[SetTab1PosIndex - 1] = 0;
						SetTab1PosIndex = 0;
						SetTab1Pos[SetTab1PosIndex] = 1;
					}
					sprintf(PressMaxStr, "%02d.%02d", sysctl->pressMax/100, sysctl->pressMax%100);
					sprintf(PressMinStr, "%02d.%02d", sysctl->pressMin/100, sysctl->pressMin%100);
					sprintf(PurgeFlowStr, "%02d.%02d", sysctl->purgeFlow/100, sysctl->purgeFlow%100);
					sprintf(LuminStepStr, "  %01d", sysctl->backLumin);
					if (sysctl->keyBeep == 1) sprintf(KeyBeepStr, "    开");
					else if (sysctl->keyBeep == 0) sprintf(KeyBeepStr, "    关");
					ShowHZ1616Str(1, 4, "上限", SetTab1Pos[0]);ShowASCII816Str(1+8, 4, ":", SetTab1Pos[0]);ShowASCII816Str(1+8+5, 4, PressMaxStr, 0);
					ShowHZ1616Str(1, 24, "下限", SetTab1Pos[1]);ShowASCII816Str(1+8, 24, ":", SetTab1Pos[1]);ShowASCII816Str(1+8+5, 24, PressMinStr, 0);
					ShowHZ1616Str(1, 44, "冲洗", SetTab1Pos[2]);ShowASCII816Str(1+8, 44, ":", SetTab1Pos[2]);ShowASCII816Str(1+8+5, 44, PurgeFlowStr, 0);
					ShowHZ1616Str(28, 4, "亮度", SetTab1Pos[3]);ShowASCII816Str(28+8, 4, ":", SetTab1Pos[3]);ShowASCII816Str(28+8+9, 4, LuminStepStr, 0);
					ShowHZ1616Str(28, 24, "按键", SetTab1Pos[4]);ShowASCII816Str(28+8, 24, ":", SetTab1Pos[4]);ShowHZ1616Str(28+8+3, 24, KeyBeepStr, 0);
					ShowHZ1616Str(28, 44, "语言", SetTab1Pos[5]);ShowASCII816Str(28+8, 44, ":", SetTab1Pos[5]);ShowHZ1616Str(28+8+3, 44, "  中文", 0);
					break;
				case KEYLEFT:
					if (SetTab1PosIndex > 0) {
						SetTab1Pos[SetTab1PosIndex] = 0;
						SetTab1Pos[SetTab1PosIndex - 1] = 1;
						SetTab1PosIndex--;
					} else {
						SetTab1Pos[SetTab1PosIndex] = 0;
						SetTab1PosIndex = sizeof(SetTab1Pos) - 1;
						SetTab1Pos[SetTab1PosIndex] = 1;
					}
					sprintf(PressMaxStr, "%02d.%02d", sysctl->pressMax/100, sysctl->pressMax%100);
					sprintf(PressMinStr, "%02d.%02d", sysctl->pressMin/100, sysctl->pressMin%100);
					sprintf(PurgeFlowStr, "%02d.%02d", sysctl->purgeFlow/100, sysctl->purgeFlow%100);
					sprintf(LuminStepStr, "  %01d", sysctl->backLumin);
					if (sysctl->keyBeep == 1) sprintf(KeyBeepStr, "    开");
					else if (sysctl->keyBeep == 0) sprintf(KeyBeepStr, "    关");
					ShowHZ1616Str(1, 4, "上限", SetTab1Pos[0]);ShowASCII816Str(1+8, 4, ":", SetTab1Pos[0]);ShowASCII816Str(1+8+5, 4, PressMaxStr, 0);
					ShowHZ1616Str(1, 24, "下限", SetTab1Pos[1]);ShowASCII816Str(1+8, 24, ":", SetTab1Pos[1]);ShowASCII816Str(1+8+5, 24, PressMinStr, 0);
					ShowHZ1616Str(1, 44, "冲洗", SetTab1Pos[2]);ShowASCII816Str(1+8, 44, ":", SetTab1Pos[2]);ShowASCII816Str(1+8+5, 44, PurgeFlowStr, 0);
					ShowHZ1616Str(28, 4, "亮度", SetTab1Pos[3]);ShowASCII816Str(28+8, 4, ":", SetTab1Pos[3]);ShowASCII816Str(28+8+9, 4, LuminStepStr, 0);
					ShowHZ1616Str(28, 24, "按键", SetTab1Pos[4]);ShowASCII816Str(28+8, 24, ":", SetTab1Pos[4]);ShowHZ1616Str(28+8+3, 24, KeyBeepStr, 0);
					ShowHZ1616Str(28, 44, "语言", SetTab1Pos[5]);ShowASCII816Str(28+8, 44, ":", SetTab1Pos[5]);ShowHZ1616Str(28+8+3, 44, "  中文", 0);
					break;
				case KEYNUM1:
				case KEYNUM2:
				case KEYNUM3:
				case KEYNUM4:
				case KEYNUM5:
				case KEYNUM6:
				case KEYNUM7:
				case KEYNUM8:
				case KEYNUM9:
				case KEYNUM0:
					if (SetTab1PosIndex == 0) {
						for (SetPressMaxPosIndex = 1; SetPressMaxPosIndex < sizeof(SetPressMaxPos); ++SetPressMaxPosIndex)
							SetPressMaxPos[SetPressMaxPosIndex - 1] = SetPressMaxPos[SetPressMaxPosIndex];
						
						SetPressMaxPos[SetPressMaxPosIndex - 1] = (*keyVal == KEYNUM0? 0: *keyVal);
						PressMaxStr[0] = SetPressMaxPos[0] + 0x30;
						PressMaxStr[1] = SetPressMaxPos[1] + 0x30;
						PressMaxStr[2] = '.';
						PressMaxStr[3] = SetPressMaxPos[2] + 0x30;
						PressMaxStr[4] = SetPressMaxPos[3] + 0x30;
						ShowASCII816Str(1+8+5, 4, PressMaxStr, 0);
					} else if (SetTab1PosIndex == 1) {
						for (SetPressMinPosIndex = 1; SetPressMinPosIndex < sizeof(SetPressMinPos); ++SetPressMinPosIndex)
							SetPressMinPos[SetPressMinPosIndex - 1] = SetPressMinPos[SetPressMinPosIndex];
						
						SetPressMinPos[SetPressMinPosIndex - 1] = (*keyVal == KEYNUM0? 0: *keyVal);
						PressMinStr[0] = SetPressMinPos[0] + 0x30;
						PressMinStr[1] = SetPressMinPos[1] + 0x30;
						PressMinStr[2] = '.';
						PressMinStr[3] = SetPressMinPos[2] + 0x30;
						PressMinStr[4] = SetPressMinPos[3] + 0x30;
						ShowASCII816Str(1+8+5, 24, PressMinStr, 0);
					} else if (SetTab1PosIndex == 2) {	
						for (SetPurgeFlowPosIndex = 1; SetPurgeFlowPosIndex < sizeof(SetPurgeFlowPos); ++SetPurgeFlowPosIndex)
							SetPurgeFlowPos[SetPurgeFlowPosIndex - 1] = SetPurgeFlowPos[SetPurgeFlowPosIndex];
						
						SetPurgeFlowPos[SetPurgeFlowPosIndex - 1] = (*keyVal == KEYNUM0? 0: *keyVal);
						PurgeFlowStr[0] = SetPurgeFlowPos[0] + 0x30;
						PurgeFlowStr[1] = SetPurgeFlowPos[1] + 0x30;
						PurgeFlowStr[2] = '.';
						PurgeFlowStr[3] = SetPurgeFlowPos[2] + 0x30;
						PurgeFlowStr[4] = SetPurgeFlowPos[3] + 0x30;
						ShowASCII816Str(1+8+5, 44, PurgeFlowStr, 0);
					} else if (SetTab1PosIndex == 3) {
						sysctl->backLumin = (*keyVal == KEYNUM0? 0: *keyVal);
						LuminStepStr[0] = ' ';
						LuminStepStr[1] = ' ';
						LuminStepStr[2] = sysctl->backLumin + 0x30;
						ShowASCII816Str(28+8+9, 4, LuminStepStr, 0);
						OLED_SetContrast(sysctl->backLumin);
					}  else if (SetTab1PosIndex == 4) {
						if (*keyVal == KEYNUM0) {
							sysctl->keyBeep = 0;
							ShowHZ1616Str(28+8+3, 24, "    关", 0);
						} else if (*keyVal == KEYNUM1) {
							sysctl->keyBeep = 1;
							ShowHZ1616Str(28+8+3, 24, "    开", 0);
						}
					}						
					break;
				case KEYENT:
					if (SetTab1PosIndex == 0) {
						sysctl->pressMax = SetPressMaxPos[0] * 1000 + SetPressMaxPos[1] * 100 + SetPressMaxPos[2] * 10 + SetPressMaxPos[3] * 1;
					} else if (SetTab1PosIndex == 1) {
						sysctl->pressMin = SetPressMinPos[0] * 1000 + SetPressMinPos[1] * 100 + SetPressMinPos[2] * 10 + SetPressMinPos[3] * 1;
					} else if (SetTab1PosIndex == 2) {
						sysctl->purgeFlow = SetPurgeFlowPos[0] * 1000 + SetPurgeFlowPos[1] * 100 + SetPurgeFlowPos[2] * 10 + SetPurgeFlowPos[3] * 1;
					} else if (SetTab1PosIndex == 3) {
//						sysctl->backLumin = SetLuminStepPos * 1;
//						OLED_SetContrast(sysctl->backLumin);
					}
					break;
				}			
			} else if (DisTabs == 3) {
				switch (*keyVal) {
				case KEYRIGHT:
				case KEYLEFT:
					if (SetShowCntPage == 1) {
						SetShowCntPage = 0;
						ShowASCII816Str(1, 4, "0.05", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[0].cnt);ShowASCII816Str(1+8+5, 4, ShowCntStr, 0);
						ShowASCII816Str(1, 24, "0.10", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[1].cnt);ShowASCII816Str(1+8+5, 24, ShowCntStr, 0);
						ShowASCII816Str(1, 44, "0.20", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[2].cnt);ShowASCII816Str(1+8+5, 44, ShowCntStr, 0);
						ShowASCII816Str(28, 4, "0.50", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[3].cnt);ShowASCII816Str(28+8+5, 4, ShowCntStr, 0);
						ShowASCII816Str(28, 24, "01.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[4].cnt);ShowASCII816Str(28+8+5, 24, ShowCntStr, 0);
						ShowASCII816Str(28, 44, "02.50", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[5].cnt);ShowASCII816Str(28+8+5, 44, ShowCntStr, 0);
					} else if (SetShowCntPage == 0) {
						SetShowCntPage = 1;
						ShowASCII816Str(1, 4, "05.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[6].cnt);ShowASCII816Str(1+8+5, 4, ShowCntStr, 0);
						ShowASCII816Str(1, 24, "10.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[7].cnt);ShowASCII816Str(1+8+5, 24, ShowCntStr, 0);
						ShowASCII816Str(1, 44, "25.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[8].cnt);ShowASCII816Str(1+8+5, 44, ShowCntStr, 0);
						ShowASCII816Str(28, 4, "50.00", 0);sprintf(ShowCntStr, "%05d", PUMP_FlowCnts[9].cnt);ShowASCII816Str(28+8+5, 4, ShowCntStr, 0);
						ShowASCII816Str(28, 24, " P.G.", 0);sprintf(ShowPressStr, " %04d", PUMP_PressArg.pg);ShowASCII816Str(28+8+5, 24, ShowPressStr, 0);
						ShowASCII816Str(28, 44, " P.Z.", 0);sprintf(ShowPressStr, " %01d.%02d", PUMP_PressArg.pz/100, PUMP_PressArg.pz%100);ShowASCII816Str(28+8+5, 44, ShowPressStr, 0);
					}	 					
					break;
				}				
			}
		}
		
		
	}
}











