#include "stm32f10x.h"                  // 设备头文件
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "menu.h"
#include "LED.h"



extern uint8_t KeyNum;
extern uint8_t index_1;
extern uint8_t last_index_1;
extern uint8_t index_2;
extern uint8_t last_index_2;


int main(void)
{
    LED_Init();
    OLED_Init();
    Key_Init();
    while(1)
    {
        OLED_Clear();//二级菜单回一级菜单时刷新
        menu_1();
        /*//进入二级菜单时重新刷新索引
        index_2=1;
        last_index_2=1;*/
        OLED_Clear();//一级菜单进二级菜单时刷新
        switch(index_1)
        {
            case 1:
                menu_2_chat();
                break;
            case 2:
                menu_2_game();
                break;
            case 3:
                menu_2_setting();
                OLED_Clear();
                switch(index_2)
                {
                    case 1:
                        menu_3_setting_light();
                        break;
                }

                break;
        }
    }
}
