#include "stm32f10x.h"                  // Device header

/**
  * @brief  初始化LED GPIO端口
  * @param  无
  * @retval 无
 **/
void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能GPIOA时钟
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       // 配置为推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0; // 配置引脚1, 2和0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // 设置GPIO速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 初始化GPIOA
    
    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0); // 默认关闭LED（设置高电平）
}

/**
  * @brief  打开LED1（点亮LED1）
  * @param  无
  * @retval 无
 **/
void LED1_ON(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // 设置低电平点亮LED1
}

/**
  * @brief  关闭LED1（熄灭LED1）
  * @param  无
  * @retval 无
 **/
void LED1_OFF(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_2);    // 设置高电平熄灭LED1
}

/**
  * @brief  切换LED1状态（如果LED1亮，则熄灭；如果LED1灭，则点亮）
  * @param  无
  * @retval 无
 **/
void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)    // 检查LED1当前状态
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_2);    // 当前为低电平，设置为高电平熄灭LED1
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // 当前为高电平，设置为低电平点亮LED1
    }
}

/**
  * @brief  打开LED2（点亮LED2）
  * @param  无
  * @retval 无
 **/
void LED2_ON(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // 设置低电平点亮LED2
}

/**
  * @brief  关闭LED2（熄灭LED2）
  * @param  无
  * @retval 无
 **/
void LED2_OFF(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_1);    // 设置高电平熄灭LED2
}

/**
  * @brief  切换LED2状态（如果LED2亮，则熄灭；如果LED2灭，则点亮）
  * @param  无
  * @retval 无
 **/
void LED2_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)    // 检查LED2当前状态
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);    // 当前为低电平，设置为高电平熄灭LED2
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // 当前为高电平，设置为低电平点亮LED2
    }
}

/**
  * @brief  打开LED3（点亮LED3）
  * @param  无
  * @retval 无
 **/
void LED3_ON(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // 设置低电平点亮LED3
}

/**
  * @brief  关闭LED3（熄灭LED3）
  * @param  无
  * @retval 无
 **/
void LED3_OFF(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_0);    // 设置高电平熄灭LED3
}

/**
  * @brief  切换LED3状态（如果LED3亮，则熄灭；如果LED3灭，则点亮）
  * @param  无
  * @retval 无
 **/
void LED3_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0)    // 检查LED3当前状态
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0);    // 当前为低电平，设置为高电平熄灭LED3
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // 当前为高电平，设置为低电平点亮LED3
    }
}
