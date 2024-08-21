#include "stm32f10x.h"
#include "OLED.h"
#include "Key.h"
#include "led.h"

// 枚举状态,第一个是菜单级数,第二个是二级菜单索引,第三个是三级菜单索引
typedef enum {
    STATE_1,
    STATE_2_game,
    STATE_2_chat,
    STATE_2_setting,
    STATE_3_setting_light,
} State;

// 定义结构体
typedef struct {
    State state;
} StateMachine;


StateMachine machine = {STATE_1}; // 初始化状态机
uint8_t KeyNum = 0;
uint8_t index_1=1;
uint8_t last_index_1=1;
uint8_t index_2=1;
uint8_t last_index_2=1;



//一级菜单界面
void menu_1(void)//实际上一级菜单只有三个按键,上下和确认
{
    while(machine.state==STATE_1)
    {
        KeyNum = Key_GetNum();
        if(index_1!=last_index_1)
        {
            OLED_ClearLine();
            last_index_1=index_1;
        }
        switch(KeyNum)
        {   
            case 1:
                index_1--;
                if(index_1<1)
                    index_1=3;
                break;
            case 2:
                index_1++;
                if(index_1>3)
                    index_1=1;
                break;
            case 3:
                switch(index_1)
                {
                    case 1:
                        machine.state=STATE_2_chat;
                        break;
                    case 2:
                        machine.state=STATE_2_game;
                        break;
                    case 3:
                        machine.state=STATE_2_setting;
                        break;
                }
                break;
        }
        OLED_ShowDot(index_1, 1);
        OLED_ShowString(1, 2, "Chat");
        OLED_ShowString(2, 2, "Game");
        OLED_ShowString(3, 2, "Setting");
    }
}

//二级游戏菜单界面
void menu_2_game(void)
{
    while(machine.state==STATE_2_game)
    {
        KeyNum = Key_GetNum();
        if(index_2!=last_index_2)
        {
            OLED_ClearLine();
            last_index_2=index_2;
        }
        switch(KeyNum)
        {   
            case 1:
                index_2--;
                if(index_2<1)
                    index_2=3;
                break;
            case 2:
                index_2++;
                if(index_2>3)
                    index_2=1;
                break;  
            case 3:
                /*switch(index_2)
                {
                    case 1:
                        machine.state=STATE_3_setting_light;
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                }*/
                break;
            case 4:
                machine.state=STATE_1;
                break;
        }
        OLED_ShowDot(index_2, 1);
        OLED_ShowString(1, 2, "Genshin Impact");
        OLED_ShowString(2, 2, "Start");
        OLED_ShowString(3, 2, "Setting");
    }
}

//二级微信菜单界面
void menu_2_chat(void)
{
    while(machine.state==STATE_2_chat)
    {
        KeyNum = Key_GetNum();
        if(index_2!=last_index_2)
        {
            OLED_ClearLine();
            last_index_2=index_2;
        }
        switch(KeyNum)
        {   
            case 1:
                index_2--;
                if(index_2<1)
                    index_2=2;
                break;
            case 2:
                index_2++;
                if(index_2>2)
                    index_2=1;
                break;
            case 3:
                break;//先写着这个分支,等到二级菜单界面完成后再修改
            case 4:
                machine.state=STATE_1;
                break;
        }
        OLED_ShowDot(index_2, 1);
        OLED_ShowString(1, 2, "WeChat");
        OLED_ShowString(2, 2, "QQ");
    }
}


//二级设置菜单界面
void menu_2_setting(void)
{
    
    while(machine.state==STATE_2_setting)
    {
        KeyNum = Key_GetNum();
        if(index_2!=last_index_2)
        {
            OLED_ClearLine();
            last_index_2=index_2;
        }
        switch(KeyNum)
        {   
            case 1:
                index_2--;
                if(index_2<1)
                    index_2=2;
                break;
            case 2:
                index_2++;
                if(index_2>2)
                    index_2=1;
                break;
            case 3:
                switch(index_2)
                {
                    case 1:
                        machine.state=STATE_3_setting_light;
                        break;
                    case 2:
                        break;
                }
                break;
            case 4:
                machine.state=STATE_1;
                break;
        }
        OLED_ShowDot(index_2, 1);
        OLED_ShowString(1, 2, "Turn Light");
        OLED_ShowString(2, 2, "Setting");
    }
}

void menu_3_setting_light(void)
{
    while(machine.state==STATE_3_setting_light)
    {
        KeyNum = Key_GetNum();
        if(KeyNum==1)
            LED1_Turn();
        if(KeyNum==2)
            LED2_Turn();
        if(KeyNum==3)
            LED3_Turn();
        if(KeyNum==4)
            machine.state=STATE_2_setting;
        OLED_ShowString(1, 2, "Light1:");
        if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0) 
            OLED_ShowString(1, 9, "On ");
        else
            OLED_ShowString(1, 9, "Off");
        OLED_ShowString(2, 2, "Light2:");
        if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) 
            OLED_ShowString(2, 9, "On ");
        else
            OLED_ShowString(2, 9, "Off");
        OLED_ShowString(3, 2, "Light3:");
        if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0) 
            OLED_ShowString(3, 9, "On ");
        else
            OLED_ShowString(3, 9, "Off");
    }
}
