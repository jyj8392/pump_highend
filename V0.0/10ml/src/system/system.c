#include "include.h"

/*********************************************************************************************************
**                           TaskP1Func һ�ſڹ�������
********************************************************************************************************/
void TaskP1Func(void *pdata)
{
	struct sys_ctl *sysctl = pdata;
	u16 loopIntVCnt = 0;
	
	if ((sysctl->stickState & PORT(1)) != 0) {					//��ʼ��λ
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,60,48,24,BmpDinWei,0); 
		//ʱ������
		sysctl->runTime_Min[0] = 0;
		sysctl->runTime_Sec[0] = 0;
		//��ŷ�����
	} else if ((sysctl->freezeState & PORT(1)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 200; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,60,48,24,BmpLengDong,0); 
		//ʱ������
		sysctl->runTime_Min[0] = 0;
		sysctl->runTime_Sec[0] = 0;
		//��ŷ�����
	} else if ((sysctl->thawState & PORT(1)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 200;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,60,48,24,BmpFuWen,0); 
		//ʱ������
		sysctl->runTime_Min[0] = 0;
		sysctl->runTime_Sec[0] = 0;
		//��ŷ�����
	}
	
	while(1) {
		if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {	//�ͷ���Դ���رն�λ
			//����������
			sysctl->bzRepts = 1; sysctl->bzOnTime = 500; sysctl->bzOffTime = 0;
			if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
			OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
			//״̬��ʾ
			writestring(24,60,48,24,BmpGuanBi,0);	
			//��ŷ�����

			if (sysctl->stickState == 0 && sysctl->freezeState == 0)


			if (sysctl->thawState == 0) {

			}
			OSTaskDel(OS_PRIO_SELF);
        } else if (loopIntVCnt == 0 || loopIntVCnt >= 5) {//������1����ʱ
			loopIntVCnt = 0;
			//ʱ����ʾ
			writestring(14,60,16,24,(Num24+(sysctl->runTime_Min[0]/10)*48),0);
			writestring(16,60,16,24,(Num24+(sysctl->runTime_Min[0]%10)*48),0);
			writestring(18,60,8,24,BmpMaoHao,0);
			writestring(19,60,16,24,(Num24+(sysctl->runTime_Sec[0]/10)*48),0);
			writestring(21,60,16,24,(Num24+(sysctl->runTime_Sec[0]%10)*48),0);

			sysctl->runTime_Sec[0]++;
			if (sysctl->runTime_Sec[0] >= 60) {
				sysctl->runTime_Sec[0] = 0;
				sysctl->runTime_Min[0]++;
			}
			if (sysctl->runTime_Min[0] >= 100)
				sysctl->runTime_Min[0] = 0;
			//��ŷ�����
			
			//��ʱ����			
		}
		if (loopIntVCnt == 0) OSTimeDly(195);
		else OSTimeDly(200);
		loopIntVCnt++;
	}
}
/*********************************************************************************************************
**                           TaskP2Func ���ſڹ�������
********************************************************************************************************/
void TaskP2Func(void *pdata)
{
	struct sys_ctl *sysctl = pdata;
	u16 loopIntVCnt = 0;

	if ((sysctl->stickState & PORT(2)) != 0) {					//��ʼ��λ
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,88,48,24,BmpDinWei,0); 
		//ʱ������
		sysctl->runTime_Min[1] = 0;
		sysctl->runTime_Sec[1] = 0;
		//��ŷ�����
	} else if ((sysctl->freezeState & PORT(2)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 200; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,88,48,24,BmpLengDong,0); 
		//ʱ������
		sysctl->runTime_Min[1] = 0;
		sysctl->runTime_Sec[1] = 0;
		//��ŷ�����
	} else if ((sysctl->thawState & PORT(2)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 200;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,88,48,24,BmpFuWen,0); 
		//ʱ������
		sysctl->runTime_Min[1] = 0;
		sysctl->runTime_Sec[1] = 0;
		//��ŷ�����
	}
	
	while(1) {
		if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {	//�ͷ���Դ
			//����������
			sysctl->bzRepts = 1; sysctl->bzOnTime = 500; sysctl->bzOffTime = 0;
			if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
			OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
			//״̬��ʾ
			writestring(24,88,48,24,BmpGuanBi,0);	
			//��ŷ�����

			if (sysctl->stickState == 0 && sysctl->freezeState == 0)


			if (sysctl->thawState == 0) {


			}
			OSTaskDel(OS_PRIO_SELF);
        } else if (loopIntVCnt == 0 || loopIntVCnt >= 5) {//99Ϊ������1����ʱ
			loopIntVCnt = 0;
			//ʱ����ʾ
			writestring(14,88,16,24,(Num24+(sysctl->runTime_Min[1]/10)*48),0);
			writestring(16,88,16,24,(Num24+(sysctl->runTime_Min[1]%10)*48),0);
			writestring(18,88,8,24,BmpMaoHao,0);
			writestring(19,88,16,24,(Num24+(sysctl->runTime_Sec[1]/10)*48),0);
			writestring(21,88,16,24,(Num24+(sysctl->runTime_Sec[1]%10)*48),0);

			sysctl->runTime_Sec[1]++;
			if (sysctl->runTime_Sec[1] >= 60) {
				sysctl->runTime_Sec[1] = 0;
				sysctl->runTime_Min[1]++;
			}
			if (sysctl->runTime_Min[1] >= 100)
				sysctl->runTime_Min[1] = 0;
			//��ŷ�����
			
			//��ʱ����			
		}
		if (loopIntVCnt == 0) OSTimeDly(195);
		else OSTimeDly(200);
		loopIntVCnt++;
	}
}
/*********************************************************************************************************
**                           TaskP3Func ���ſڹ�������
********************************************************************************************************/
void TaskP3Func(void *pdata)
{
	struct sys_ctl *sysctl = pdata;
	u16 loopIntVCnt = 0;
	
	if ((sysctl->stickState & PORT(3)) != 0) {						//��ʼ��λ
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 200; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,116,48,24,BmpDinWei,0); 
		//ʱ������
		sysctl->runTime_Min[2] = 0;
		sysctl->runTime_Sec[2] = 0;
		//��ŷ�����
	} else if ((sysctl->freezeState & PORT(3)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,116,48,24,BmpLengDong,0); 
		//ʱ������
		sysctl->runTime_Min[2] = 0;
		sysctl->runTime_Sec[2] = 0;
		//��ŷ�����

	} else if ((sysctl->thawState & PORT(3)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 200;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,116,48,24,BmpFuWen,0); 
		//ʱ������
		sysctl->runTime_Min[2] = 0;
		sysctl->runTime_Sec[2] = 0;
		//��ŷ�����

	}
	
	while(1) {
		if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {	//�ͷ���Դ
			//����������
			sysctl->bzRepts = 1; sysctl->bzOnTime = 500; sysctl->bzOffTime = 0;
			if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
			OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
			//״̬��ʾ
			writestring(24,116,48,24,BmpGuanBi,0);	
			//��ŷ�����

			if (sysctl->stickState == 0 && sysctl->freezeState == 0)


			if (sysctl->thawState == 0) {

			}
			OSTaskDel(OS_PRIO_SELF);
        } else if (loopIntVCnt == 0 || loopIntVCnt >= 5) {//99Ϊ������1����ʱ
			loopIntVCnt = 0;
			//ʱ����ʾ
			writestring(14,116,16,24,(Num24+(sysctl->runTime_Min[2]/10)*48),0);
			writestring(16,116,16,24,(Num24+(sysctl->runTime_Min[2]%10)*48),0);
			writestring(18,116,8,24,BmpMaoHao,0);
			writestring(19,116,16,24,(Num24+(sysctl->runTime_Sec[2]/10)*48),0);
			writestring(21,116,16,24,(Num24+(sysctl->runTime_Sec[2]%10)*48),0);

			sysctl->runTime_Sec[2]++;
			if (sysctl->runTime_Sec[2] >= 60) {
				sysctl->runTime_Sec[2] = 0;
				sysctl->runTime_Min[2]++;
			}
			if (sysctl->runTime_Min[2] >= 100)
				sysctl->runTime_Min[2] = 0;
			//��ŷ�����
			
			//��ʱ����			
		}
		if (loopIntVCnt == 0) OSTimeDly(195);
		else OSTimeDly(200);
		loopIntVCnt++;
	}
}
/*********************************************************************************************************
**                           TaskP4Func �ĺſڹ�������
********************************************************************************************************/
void TaskP4Func(void *pdata)
{
	struct sys_ctl *sysctl = pdata;
	u16 loopIntVCnt = 0;
	
	if ((sysctl->stickState & PORT(4)) != 0) {						//��ʼ��λ
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,144,48,24,BmpDinWei,0); 
		//ʱ������
		sysctl->runTime_Min[3] = 0;
		sysctl->runTime_Sec[3] = 0;
		//��ŷ�����
	} else if ((sysctl->freezeState & PORT(4)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 200; sysctl->bzOffTime = 100;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,144,48,24,BmpLengDong,0); 
		//ʱ������
		sysctl->runTime_Min[3] = 0;
		sysctl->runTime_Sec[3] = 0;
		//��ŷ�����
	} else if ((sysctl->thawState & PORT(4)) != 0) {
		//����������
		sysctl->bzRepts = 5; sysctl->bzOnTime = 100; sysctl->bzOffTime = 200;
		if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
		OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
		//״̬��ʾ
		writestring(24,144,48,24,BmpFuWen,0); 
		//ʱ������
		sysctl->runTime_Min[3] = 0;
		sysctl->runTime_Sec[3] = 0;
		//��ŷ�����
	}
	
	while(1) {
		if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {	//�ͷ���Դ
			//����������
			sysctl->bzRepts = 1; sysctl->bzOnTime = 500; sysctl->bzOffTime = 0;
			if (OSTCBPrioTbl[PRI_BZ] != (OS_TCB *)0) OSTaskDel(PRI_BZ);
			OSTaskCreate(TaskBZ, sysctl, &TaskStkBZ[TaskStkBZLengh - 1], PRI_BZ);
			//״̬��ʾ
			writestring(24,144,48,24,BmpGuanBi,0);	
			//��ŷ�����
			if (sysctl->stickState == 0 && sysctl->freezeState == 0)


			if (sysctl->thawState == 0) {

			}
			OSTaskDel(OS_PRIO_SELF);
        } else if (loopIntVCnt == 0 || loopIntVCnt >= 5) {//99Ϊ������1����ʱ
			loopIntVCnt = 0;
			//ʱ����ʾ
			writestring(14,144,16,24,(Num24+(sysctl->runTime_Min[3]/10)*48),0);
			writestring(16,144,16,24,(Num24+(sysctl->runTime_Min[3]%10)*48),0);
			writestring(18,144,8,24,BmpMaoHao,0);
			writestring(19,144,16,24,(Num24+(sysctl->runTime_Sec[3]/10)*48),0);
			writestring(21,144,16,24,(Num24+(sysctl->runTime_Sec[3]%10)*48),0);

			sysctl->runTime_Sec[3]++;
			if (sysctl->runTime_Sec[3] >= 60) {
				sysctl->runTime_Sec[3] = 0;
				sysctl->runTime_Min[3]++;
			}
			if (sysctl->runTime_Min[3] >= 100)
				sysctl->runTime_Min[3] = 0;
			//��ŷ�����
			
			//��ʱ����			
		}
		if (loopIntVCnt == 0) OSTimeDly(195);
		else OSTimeDly(200);
		loopIntVCnt++;
	}
}
/*********************************************************************************************************
**                           TaskTemp �ĺſڹ�������
********************************************************************************************************/
//void TaskP4Func(void *pdata)
//{

//}
