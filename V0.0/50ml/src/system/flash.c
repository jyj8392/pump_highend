#include "include.h"

#define FLASH_BASE_ADDR	(0x0807F000)			//0x0807F000-0x0807F7FF
#define FLASH_ADR_SETFLOW   (FLASH_BASE_ADDR + 0)	//16bit
#define FLASH_ADR_PURGEFLOW   (FLASH_BASE_ADDR + 2*1)	//16bit
#define FLASH_ADR_FLOWMODE   (FLASH_BASE_ADDR + 2*2)	//8bit
#define FLASH_ADR_PRESSOFFSET   (FLASH_BASE_ADDR + 2*3)	//16bit
#define FLASH_ADR_PRESSPROTECT   (FLASH_BASE_ADDR + 2*4)	//8bit
#define FLASH_ADR_PRESSMAX   (FLASH_BASE_ADDR + 2*5)	//16bit
#define FLASH_ADR_PRESSMIN   (FLASH_BASE_ADDR + 2*6)	//16bit
#define FLASH_ADR_BLACKLUMIN   (FLASH_BASE_ADDR + 2*7)	//8bit
#define FLASH_ADR_KEYBEEP   (FLASH_BASE_ADDR + 2*8)	//8bit

void Erase_Flash(u32 flash_addr)
{
	RCC_HSICmd(ENABLE);
	FLASH_Unlock();		/* 每次擦除Flash中数据时得先解锁 */
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(flash_addr);  
	FLASH_Lock();							   /* 上锁 */
	RCC_HSICmd(DISABLE);
}

void Write8bit_Flash(u32 flash_addr, u8 flash_data)
{
	RCC_HSICmd(ENABLE);
	FLASH_Unlock();		/* 每次擦除Flash中数据时得先解锁 */
//	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
//	FLASH_ErasePage(0x8002000);  
	FLASH_ProgramOptionByteData(flash_addr,flash_data);
	FLASH_Lock();							   /* 上锁 */
	RCC_HSICmd(DISABLE);
}

void Write16bit_Flash(u32 flash_addr, u16 flash_data)
{
	RCC_HSICmd(ENABLE);
	FLASH_Unlock();		/* 每次擦除Flash中数据时得先解锁 */
//	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
//	FLASH_ErasePage(flash_addr);  
	FLASH_ProgramHalfWord(flash_addr,flash_data);
	FLASH_Lock();							   /* 上锁 */
	RCC_HSICmd(DISABLE);
}

void Write32bit_Flash(u32 flash_addr, u32 flash_data)
{
	RCC_HSICmd(ENABLE);
	FLASH_Unlock();		/* 每次擦除Flash中数据时得先解锁 */
//	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
//	FLASH_ErasePage(0x8002000);  
	FLASH_ProgramWord(flash_addr,flash_data);
	FLASH_Lock();							   /* 上锁 */
	RCC_HSICmd(DISABLE);
}

void Read_Flash(struct sys_ctl *sysctl)
{
	sysctl->setFlow = *(u16*)(FLASH_ADR_SETFLOW);
	sysctl->purgeFlow = *(u16*)(FLASH_ADR_PURGEFLOW);
	sysctl->flowMode = *(u8*)(FLASH_ADR_FLOWMODE);
	sysctl->pressOffset = *(u16*)(FLASH_ADR_PRESSOFFSET);
	sysctl->pressProtect = *(u8*)(FLASH_ADR_PRESSPROTECT);
	sysctl->pressMax = *(u16*)(FLASH_ADR_PRESSMAX);
	sysctl->pressMin = *(u16*)(FLASH_ADR_PRESSMIN);
	sysctl->backLumin = *(u8*)(FLASH_ADR_BLACKLUMIN);
	sysctl->keyBeep = *(u8*)(FLASH_ADR_KEYBEEP);
	
	if (sysctl->backLumin > 9) {	//如果参数未初始化
		sysctl->setFlow = 0;
		sysctl->flowMode = 0;
		sysctl->pressMax = 4200;
		sysctl->pressMin = 0;
		sysctl->purgeFlow = 2000;
		sysctl->backLumin = 9;
		sysctl->keyBeep = 1;
		sysctl->nowPress = 0;
		sysctl->pressOffset = 0;
		sysctl->pressProtect = 0;
	}
}

void Write_Flash(struct sys_ctl *sysctl)
{
	static u16 setFlow = 0xffff;
	static u16 purgeFlow = 0xffff;
	static u8 flowMode = 0xff;
	static u16 pressOffset = 0xffff;
	static u8 pressProtect = 0xff;
	static u16 pressMax = 0xffff;
	static u16 pressMin = 0xffff;
	static u8 backLumin = 0xff;
	static u8 keyBeep = 0xff;
	
	if (sysctl->setFlow != setFlow 
		|| sysctl->purgeFlow != purgeFlow
		|| sysctl->flowMode != flowMode
		|| sysctl->pressOffset != pressOffset
		|| sysctl->pressProtect != pressProtect
		|| sysctl->pressMax != pressMax
		|| sysctl->pressMin != pressMin
		|| sysctl->backLumin != backLumin
		|| sysctl->keyBeep != keyBeep) {
		Erase_Flash(FLASH_BASE_ADDR);
		Write16bit_Flash(FLASH_ADR_SETFLOW, sysctl->setFlow);setFlow = sysctl->setFlow;
		Write16bit_Flash(FLASH_ADR_PURGEFLOW, sysctl->purgeFlow);purgeFlow = sysctl->purgeFlow;
		Write16bit_Flash(FLASH_ADR_FLOWMODE, sysctl->flowMode);flowMode = sysctl->flowMode;
		Write16bit_Flash(FLASH_ADR_PRESSOFFSET, sysctl->pressOffset);pressOffset = sysctl->pressOffset;
		Write16bit_Flash(FLASH_ADR_PRESSPROTECT, sysctl->pressProtect);pressProtect = sysctl->pressProtect;
		Write16bit_Flash(FLASH_ADR_PRESSMAX, sysctl->pressMax);pressMax = sysctl->pressMax;
		Write16bit_Flash(FLASH_ADR_PRESSMIN, sysctl->pressMin);pressMin = sysctl->pressMin;
		Write16bit_Flash(FLASH_ADR_BLACKLUMIN, sysctl->backLumin);backLumin = sysctl->backLumin;
		Write16bit_Flash(FLASH_ADR_KEYBEEP, sysctl->keyBeep);keyBeep = sysctl->keyBeep;
	}
}
