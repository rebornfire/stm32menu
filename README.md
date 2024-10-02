# 项目名称

基于STM32的多级菜单系统

## 项目简介

本项目是一个基于STM32微控制器的多级菜单系统，使用OLED显示屏和按键输入来实现菜单导航。项目包括多个菜单级别，每个级别都有不同的选项和功能。用户可以通过按键在菜单之间导航，并执行相应的操作，但是很多选项只是放在那里，并不能点进去。

## 硬件需求

- STM32F10x系列微控制器
- OLED显示屏
- 按键模块
- LED模块
- PWM模块

## 软件需求

- STM32标准外设库
- Keil uVision或其他支持STM32开发的IDE

## 文件结构

- `main.c`：主程序文件，包含系统初始化和主循环。
- `menu.h`：菜单处理文件的头文件。
- `OLED.c` 和 `OLED.h`：OLED显示屏驱动代码。
- `Key.c` 和 `Key.h`：按键处理代码。
- `LED.c` 和 `LED.h`：LED控制代码。
- `PWM.c` 和 `PWM.h`：PWM控制代码。
- `delay.c` 和 `delay.h`：延时函数代码。

## 使用说明

### 硬件连接

1. 将OLED显示屏连接到STM32的I2C接口。
2. 将按键模块连接到STM32的GPIO引脚。
3. 将LED模块连接到STM32的GPIO引脚。
4. 将PWM模块连接到STM32的PWM输出引脚。

### 软件配置

1. 使用Keil uVision或其他支持STM32开发的IDE打开项目。
2. 配置项目使用STM32标准外设库。
3. 根据实际硬件连接修改`stm32f10x.h`和其他相关配置文件。

### 编译和下载

1. 编译项目，确保没有错误。
2. 将编译生成的固件下载到STM32微控制器中。

### 操作说明

1. 上电后，系统会初始化并显示一级菜单。
2. 使用按键在菜单项之间导航：
   - 按键1：向上移动菜单项。
   - 按键2：向下移动菜单项。
   - 按键3：进入选中的子菜单或执行选中的操作。
   - 按键4：返回上一级菜单。
3. 根据菜单提示进行操作，例如控制LED灯的开关或调整PWM占空比。

## 菜单结构

- 一级菜单：
  - Chat
  - Game
  - Setting
  - Exit

- 二级菜单：
  - Game：
    - yuanshen
    - minchao
    - juequ0
    - xinqiongtiedao
  - Chat：
    - WeChat
    - QQ
    - FeiShu
    - DouYin
  - Setting：
    - Turn Light
    - PWM Breath

- 三级菜单：
  - Setting - Turn Light：控制LED灯的开关。
  - Setting - PWM Breath：调整PWM占空比，实现LED呼吸灯效果。



## 贡献

欢迎提交问题和贡献代码。请确保在提交之前运行所有测试并遵循代码风格指南。

## 许可证

本项目采用MIT许可证，详情请参阅LICENSE文件。
