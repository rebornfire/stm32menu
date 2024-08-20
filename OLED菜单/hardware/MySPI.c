#include "stm32f10x.h"                  // Device header

// 设置SPI片选引脚的电平（高或低）
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue); // 根据BitValue设置GPIOA的引脚4
}

// 初始化SPI接口及相关GPIO引脚
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);  // 使能SPI1时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 初始化SPI片选引脚（GPIOA Pin 4）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     // 配置为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;            // 配置引脚4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 设置GPIO速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 初始化SPI时钟引脚（GPIOA Pin 5）和MOSI引脚（GPIOA Pin 7）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       // 配置为复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7; // 配置引脚5和引脚7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 设置GPIO速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 初始化SPI MISO引脚（GPIOA Pin 6）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         // 配置为上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;            // 配置引脚6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 设置GPIO速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置SPI参数
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      // 配置为主模式
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // 全双工通信
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  // 数据宽度8位
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  // 高位先行
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // 设定时钟分频因子
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                          // 时钟极性低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                        // 时钟相位第一沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           // 软件管理NSS信号
	SPI_InitStructure.SPI_CRCPolynomial = 7;                            // CRC多项式
	SPI_Init(SPI1, &SPI_InitStructure);                                 // 初始化SPI1
	
	SPI_Cmd(SPI1, ENABLE);  // 使能SPI1
	
	MySPI_W_SS(1);         // 设定片选信号为高电平
}

// 启动SPI传输（将片选信号设为低电平）
void MySPI_Start(void)
{
	MySPI_W_SS(0);  // 设定片选信号为低电平
}

// 停止SPI传输（将片选信号设为高电平）
void MySPI_Stop(void)
{
	MySPI_W_SS(1);  // 设定片选信号为高电平
}

// 发送一个字节数据并接收响应字节
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET); // 等待发送寄存器空闲
	
	SPI_I2S_SendData(SPI1, ByteSend); // 发送数据
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET); // 等待接收寄存器非空
	
	return SPI_I2S_ReceiveData(SPI1); // 返回接收到的数据
}

