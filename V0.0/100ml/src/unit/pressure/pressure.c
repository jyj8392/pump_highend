#include "include.h"

#define ON				1
#define OFF				0

#define P_CLK			GPIOA, GPIO_Pin_6
#define P_DAT			GPIOA, GPIO_Pin_5
#define P_CS			GPIOB, GPIO_Pin_0

#define ReadPData(dat)		(GPIO_ReadInputDataBit(dat))
#define SetPCTL(ctl, sw)	(sw == ON? GPIO_SetBits(ctl): GPIO_ResetBits(ctl))

unsigned int ReadADValue(void)
{
	unsigned int back_up = 0;
    unsigned char i = 0;
	unsigned char data1 = 0;
	SetPCTL(P_DAT, ON);
	SetPCTL(P_CLK, OFF);
	SetPCTL(P_CS, ON);
	SetPCTL(P_CS, OFF);
	SetPCTL(P_CLK, ON);
	SetPCTL(P_CLK, OFF);
	SetPCTL(P_CLK, ON);
	SetPCTL(P_CLK, OFF);
	SetPCTL(P_CLK, ON);

	for(i = 0; i < 12; i++) {
		SetPCTL(P_CLK, OFF);
		data1 = ReadPData(P_DAT);
		if(data1 == 1) {
			back_up |= (0x0800>>i);
		}
		SetPCTL(P_CLK, ON);
	}
	SetPCTL(P_CS, ON);
	return back_up;

}

unsigned int GetPressure(void)
{
	double ad = 0;
	
	ad = (double)(ReadADValue());
	
	return (unsigned int)(PRESSPARA_X4 * ad * ad * ad * ad + 
						PRESSPARA_X3 * ad * ad * ad + 
						PRESSPARA_X2 * ad * ad + 
						PRESSPARA_X1 * ad + PRESSPARA_X0);
				
}
