#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

// 初始化W25Q64 Flash并配置SPI
void W25Q64_Init(void)
{
	MySPI_Init(); // 初始化SPI接口
}

// 读取W25Q64的制造商ID和设备ID
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();                              // 启动SPI通信
	MySPI_SwapByte(W25Q64_JEDEC_ID);           // 发送读取ID命令
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);  // 读取制造商ID
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);  // 读取设备ID低字节
	*DID <<= 8;                                // 设备ID左移8位
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE); // 读取设备ID高字节
	MySPI_Stop();                             // 停止SPI通信
}

// 使能W25Q64写操作
void W25Q64_WriteEnable(void)
{
	MySPI_Start();                        // 启动SPI通信
	MySPI_SwapByte(W25Q64_WRITE_ENABLE); // 发送写使能命令
	MySPI_Stop();                         // 停止SPI通信
}

// 等待W25Q64忙状态变为空闲
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	MySPI_Start(); // 启动SPI通信
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1); // 发送读取状态寄存器1命令
	Timeout = 100000;  // 设置超时计数器
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01) // 检查忙标志位
	{
		Timeout--;        // 递减超时计数器
		if (Timeout == 0) // 超时退出
		{
			break;
		}
	}
	MySPI_Stop(); // 停止SPI通信
}

// 向W25Q64指定地址编程页数据
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	uint16_t i;
	
	W25Q64_WriteEnable(); // 使能写操作
	
	MySPI_Start(); // 启动SPI通信
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM); // 发送页编程命令
	MySPI_SwapByte(Address >> 16); // 发送地址高字节
	MySPI_SwapByte(Address >> 8);  // 发送地址中字节
	MySPI_SwapByte(Address);       // 发送地址低字节
	for (i = 0; i < Count; i++)
	{
		MySPI_SwapByte(DataArray[i]); // 发送数据
	}
	MySPI_Stop(); // 停止SPI通信
	
	W25Q64_WaitBusy(); // 等待编程完成
}

// 擦除W25Q64指定扇区
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable(); // 使能写操作
	
	MySPI_Start(); // 启动SPI通信
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB); // 发送扇区擦除命令
	MySPI_SwapByte(Address >> 16); // 发送地址高字节
	MySPI_SwapByte(Address >> 8);  // 发送地址中字节
	MySPI_SwapByte(Address);       // 发送地址低字节
	MySPI_Stop(); // 停止SPI通信
	
	W25Q64_WaitBusy(); // 等待擦除完成
}

// 从W25Q64指定地址读取数据
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start(); // 启动SPI通信
	MySPI_SwapByte(W25Q64_READ_DATA); // 发送读取数据命令
	MySPI_SwapByte(Address >> 16); // 发送地址高字节
	MySPI_SwapByte(Address >> 8);  // 发送地址中字节
	MySPI_SwapByte(Address);       // 发送地址低字节
	for (i = 0; i < Count; i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE); // 读取数据
	}
	MySPI_Stop(); // 停止SPI通信
}
