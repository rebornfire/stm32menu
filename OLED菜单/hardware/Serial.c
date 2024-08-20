#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

// 初始化USART1和相关GPIO引脚
void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 使能USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       // 配置为复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;            // 配置引脚9为USART1_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 设置GPIO速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;            // 设置波特率为9600
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx;       // 配置为发送模式
	USART_InitStructure.USART_Parity = USART_Parity_No;   // 无奇偶校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // 1个停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 数据位8位
	USART_Init(USART1, &USART_InitStructure);             // 初始化USART1
	
	USART_Cmd(USART1, ENABLE);  // 使能USART1
}

// 发送一个字节数据
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte); // 发送数据
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送完成
}

// 发送一个字节数组
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i++)
	{
		Serial_SendByte(Array[i]); // 逐个发送字节
	}
}

// 发送一个以'\0'结尾的字符串
void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		Serial_SendByte(String[i]); // 逐个发送字符
	}
}

// 计算X的Y次幂
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X; // 累乘计算幂
	}
	return Result;
}

// 发送一个数字（以指定长度格式化）
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		// 计算并发送数字的每一位
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

// 将字符输出到标准输出（重定向为串口发送）
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch); // 发送字符
	return ch;
}

// 格式化并发送字符串到串口
void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg); // 格式化字符串
	va_end(arg);
	Serial_SendString(String); // 发送格式化后的字符串
}
