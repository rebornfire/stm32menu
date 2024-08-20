#include "stm32f10x.h"                  // Device header

// 初始化LED的GPIO端口
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       // 配置为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_0; // 配置引脚1和引脚2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 设置GPIO速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 初始化GPIOA
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_0);          // 默认关闭LED（设置高电平）
}

// 打开LED1（点亮LED1）
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // 置低电平以点亮LED1
}

// 关闭LED1（熄灭LED1）
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);    // 置高电平以熄灭LED1
}

// 切换LED1的状态（如果LED1是点亮的则熄灭，如果是熄灭的则点亮）
void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0) // 检查LED1的当前状态
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);    // 当前为低电平，设置为高电平以熄灭LED1
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // 当前为高电平，设置为低电平以点亮LED1
	}
}

// 打开LED2（点亮LED2）
void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // 置低电平以点亮LED2
}

// 关闭LED2（熄灭LED2）
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);    // 置高电平以熄灭LED2
}

// 切换LED2的状态（如果LED2是点亮的则熄灭，如果是熄灭的则点亮）
void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) // 检查LED2的当前状态
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);    // 当前为低电平，设置为高电平以熄灭LED2
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // 当前为高电平，设置为低电平以点亮LED2
	}
}



void LED3_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // 置低电平以点亮LED3
}

// 关闭LED3（熄灭LED3）
void LED3_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0);    // 置高电平以熄灭LED3
}

// 切换LED3的状态（如果LED3是点亮的则熄灭，如果是熄灭的则点亮）
void LED3_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0) // 检查LED3的当前状态
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);    // 当前为低电平，设置为高电平以熄灭LED2
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // 当前为高电平，设置为低电平以点亮LED2
	}
}
