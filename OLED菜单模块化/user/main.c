#include "stm32f10x.h"                  // 设备头文件
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "menu.h"
#include "LED.h"

extern uint8_t KeyNum;
extern int8_t index_1;
extern int8_t last_index_1;
extern int8_t index_2;
extern int8_t last_index_2;
/* 总体过程便是轮询系统,从一级菜单轮询到末级菜单,
再从末级菜单轮询到一级菜单,根据menu.c里设置的状态
进行菜单切换 */
/**
  * @brief  主函数
  * @param  无
  * @retval 无
 **/
int main(void)
{
    LED_Init();
    OLED_Init();
    Key_Init();
    
    while(1)
    {
        OLED_Clear(); // 下级菜单回上级菜单时刷新
        menu_1();
        OLED_Clear(); // 上级菜单进下级菜单时刷新
        switch(index_1)
        {
            case 0:
                menu_2_chat();
                break;
            case 1:
                menu_2_game();
                break;
            case 2:
                menu_2_setting();
                OLED_Clear();
                switch(index_2)
                {
                    case 0:
                        menu_3_setting_light();
                        break;
                    case 1:
                        menu_3_setting_pwm();
                        break;
                }
                break;
            default:
                break;
        }
    }
}
