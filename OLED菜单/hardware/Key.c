#include "stm32f10x.h"                  // Device header
#include "Delay.h"

// 初始化按键的GPIO端口
void Key_Init(void)
{
	//配置GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能GPIOB时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           // 配置为上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11; // 配置引脚1和引脚11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 设置GPIO速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);                 // 初始化GPIOB
	//配置GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能GPIOB时钟
	//GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 初始化GPIOA

}

// 读取按键状态并返回按键编号（1或2）
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;  // 初始化按键编号为0
	// 检测按键1的状态
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
	{
		Delay_ms(20);                          // 消抖延时
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0); // 等待按键释放
		Delay_ms(20);                          // 再次消抖延时
		KeyNum = 1;                            // 设置按键编号为1
	}
	
	// 检测按键2的状态
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		Delay_ms(20);                          // 消抖延时
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0); // 等待按键释放
		Delay_ms(20);                          // 再次消抖延时
		KeyNum = 2;                            // 设置按键编号为2
	}
	// 检测按键3的状态
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
	{
		Delay_ms(20);                          // 消抖延时
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0); // 等待按键释放
		Delay_ms(20);                          // 再次消抖延时
		KeyNum = 3;                            // 设置按键编号为3
	}
	
	return KeyNum;  // 返回检测到的按键编号
}
