#include "include.h"

#define ON				1
#define OFF				0
#define PUMP_POS		GPIOC, GPIO_Pin_13
#define PUMP_STEP		GPIOE, GPIO_Pin_3

#define ReadPUMPPos(dat)		(GPIO_ReadInputDataBit(dat))
#define SetPUMPStep(ctl, sw)	(sw == ON? GPIO_SetBits(ctl): GPIO_ResetBits(ctl))

struct pumpctl_t PumpCtl;

/*
ͨ��ʵ�⣬����1�������Ӧ��Һ�����
5000����һȦ
��⵽��翪�أ��ۼ�ֵ��10000
δ��⵽�Ĺ����У��ۼ�ֵ��ʵ�ʷ���������*2
ֹͣ��ʼ������ʵ������ʱ�䣬���������趨���������������Ա�ʵ�ʷ������������������ڼ��ٹ����в������˾�ͣ��
ֹͣ��������ۼ�ֵ��ÿ�μ���翪�ز�������ƽ��ֵ�ı�����1/10000��
���й����У���⵽��翪�أ������ٶȣ��������趨���٣��򽵵Ͷ�ʱ���ж��ٶ�
*/

/*********************************************************************************************************
**                           ������У׼ϵ������������
********************************************************************************************************/
/*******10ml********/
#if MAXFLOW == 10
struct pumpflow_t const PUMP_FlowCnts[] = {
10, 59,
20, 117,
50, 283,
100, 585,
200, 1170,
500, 2925,
1000, 5850,
2000, 11701,
5000, 29252,
10000, 58504,
};
#endif
/***************/

/*******50ml********/
#if MAXFLOW == 50
struct pumpflow_t const PUMP_FlowCnts[] = {
5, 59,
10, 117,
25, 283,
50, 585,
100, 1170,
250, 2925,
500, 5850,
1000, 11701,
2500, 29252,
5000, 58504,
};
#endif
/***************/

/********100ml*******/
#if MAXFLOW == 100
struct pumpflow_t const PUMP_FlowCnts[] = {
1, 59,
2, 117,
5, 283,
10, 585,
20, 1170,
50, 2925,
100, 5850,
200, 11701,
500, 29252,
1000, 58504,
};
#endif
/***************/

/********200ml*******/
#if MAXFLOW == 200
struct pumpflow_t const PUMP_FlowCnts[] = {
2, 59,
4, 117,
10, 283,
20, 585,
40, 1170,
100, 2925,
200, 5850,
4000, 11701,
1000, 29252,
2000, 58504,
};
#endif
/***************/



struct pumppress_t const PUMP_PressArg = {5000, 0};

//void GetStep(void)
//{
//	unsigned char i = 0;
//	if (ReadPUMPPos(PUMP_POS)) {
//		i = 1;
//	} else {
//		i = 0;
//	}
//}

void delayms(u16 k)
{  
	u16 i;
	for(i=0;i<2000;i++); 	
}

void SetStep(void)
{
	static unsigned int i = 0;
	if (i <= 5000) {
	SetPUMPStep(PUMP_STEP, ON);
	delayms(2000);
	SetPUMPStep(PUMP_STEP, OFF);
	delayms(2000);
	} else {
		i = 10000;
	}
	i++;
}

void PumpSetFlow(u16 setFlow)
{
	PumpCtl.startFlow = PumpCtl.nowFlow;
	PumpCtl.dstFlow = (double)setFlow;
	PumpCtl.nowTime = 0;
	PumpCtl.dCndMax = PumpCtl.calCnt - PumpCtl.accCnt;
	PID_Init(0.8, 0, 0, PumpCtl.dstFlow / 10, PumpCtl.dstFlow * 5);
}

void PumpStart(u16 setFlow)
{
	if (PumpCtl.nowState == 1) return;
	
	PumpCtl.nowInterval = 2000;
	TIM2->ARR = PumpCtl.nowInterval;
	PumpCtl.startFlow = 0;
	PumpCtl.dstFlow = (double)setFlow;
	PumpCtl.nowFlow = PumpCtl.startFlow;
	PumpCtl.nowTime = 0;
	PumpCtl.dCndMax = 0;
	PID_Init(0.8, 0, 0, PumpCtl.dstFlow / 10, PumpCtl.dstFlow * 5);
	
	PumpCtl.nowState = 1;
	PumpCtl.accCnt = 0;
	PumpCtl.accTime = 0;
	PumpCtl.calCnt = 0;
	PumpCtl.dCndMax = 0;
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

void PumpStop(void)
{
	if (PumpCtl.nowState != 1) return;
	PumpCtl.nowState = 2;
	
	PumpCtl.startFlow = PumpCtl.dstFlow;
	PumpCtl.dstFlow = 0;
	PumpCtl.nowTime = 0;
	PumpCtl.dCndMax = PumpCtl.calCnt - PumpCtl.accCnt;
	PID_Init(0.8, 0, 0, PumpCtl.dstFlow / 10, PumpCtl.dstFlow * 5);
	
	TIM_Cmd(TIM4, DISABLE);
	if (PumpCtl.sysctl->pressProtect == 1) {
		TIM_Cmd(TIM2, DISABLE);
		TIM_Cmd(TIM3, DISABLE);
		PumpCtl.nowState = 0;
		PumpCtl.sysctl->pressProtect = 0;
	}
}

u16 GetFlowPara(double flow)
{
	u8 i = 0;
	u16 cnt;
	
	if (flow == 0) flow = 100;
		
	for (i = 0; i < 10 && flow > PUMP_FlowCnts[i].index; ++i);
	if (i == 10)
		cnt = (flow - PUMP_FlowCnts[9].index) * (PUMP_FlowCnts[9].cnt - PUMP_FlowCnts[8].cnt) / (PUMP_FlowCnts[9].index - PUMP_FlowCnts[8].index) + PUMP_FlowCnts[9].cnt;
	else if (i == 0) 
		cnt = PUMP_FlowCnts[i].cnt * flow / PUMP_FlowCnts[i].index;
	else {
		cnt = (PUMP_FlowCnts[i].cnt - PUMP_FlowCnts[i - 1].cnt) * ((float)(flow - PUMP_FlowCnts[i - 1].index) / (float)(PUMP_FlowCnts[i].index - PUMP_FlowCnts[i - 1].index));
		cnt += PUMP_FlowCnts[i - 1].cnt;
	}
	if (cnt < 1) cnt = 1;
	return cnt;
//	return 58504/10000*flow;
}