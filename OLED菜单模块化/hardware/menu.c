#include "stm32f10x.h"
#include "OLED.h"
#include "Key.h"
#include "led.h"
#include "PWM.h"
#include "delay.h"

// 枚举状态,第一个是菜单级数,第二个是二级菜单索引,第三个是三级菜单索引
typedef enum {
    STATE_1,
    STATE_2_game,
    STATE_2_chat,
    STATE_2_setting,
    STATE_3_setting_light,
    STATE_3_setting_pwm,
} State;

// 定义结构体
typedef struct {
    State state;
} StateMachine;


StateMachine machine = {STATE_1}; // 初始化状态机
uint8_t KeyNum = 0;
int8_t index_1=0;
int8_t last_index_1=0;
int8_t index_2=0;
int8_t last_index_2=0;
uint8_t UI_1,UI_2;
uint8_t last_UI_1,last_UI_2;
char *menu_1_items[] = {"Chat", "Game", "Setting","Exit"};
char *menu_2_game_items[] = {"yuanshen", "minchao", "juequ0","xinqiongtiedao"};
char *menu_2_chat_items[] = {"WeChat", "QQ","FeiShu","DouYin"};
char *menu_2_setting_items[] = {"Turn Light", "PWM Breath"};
uint8_t menu_1_size = sizeof(menu_1_items) / sizeof(menu_1_items[0]);
uint8_t menu_2_game_size = sizeof(menu_2_game_items) / sizeof(menu_2_game_items[0]);
uint8_t menu_2_chat_size = sizeof(menu_2_chat_items) / sizeof(menu_2_chat_items[0]);
uint8_t menu_2_setting_size = sizeof(menu_2_setting_items) / sizeof(menu_2_setting_items[0]);
/**
  * @brief  显示一级菜单
  * @param  无
  * @retval 无
 **/
void display_menu_1(void)
{
    UI_1=(index_1-(index_1%3))/3+1;//计算当前显示的页面
    if(UI_1!=last_UI_1)
    {
        OLED_Clear();
        last_UI_1=UI_1;
    }
    OLED_ShowDot(index_1%3+1, 1);
    switch(UI_1)
    {
        case 1:
        for (uint8_t i = 0; i < 3; i++)
        {
            OLED_ShowString(i+1, 2, menu_1_items[i]);
        }
            break;
        case 2:
            OLED_ShowString(1, 2, menu_1_items[3]);
            break;
    }
}
/**
  * @brief  显示二级菜单
  * @param  无
  * @retval 无
 **/
void display_menu_2(void)
{
    //二级游戏菜单显示
    if(machine.state==STATE_2_game)
    {
        UI_2=(index_2-(index_2%3))/3+1;//计算当前显示的页面
        if(UI_2!=last_UI_2)
        {
            OLED_Clear();
            last_UI_2=UI_2;
        }
        OLED_ShowDot(index_2%3+1, 1);
        switch(UI_2)
        {
            case 1:
            for (uint8_t i = 0; i < 3; i++)
                OLED_ShowString(i+1, 2, menu_2_game_items[i]);
                break;
            case 2:
                OLED_ShowString(1, 2, menu_2_game_items[3]);
                break;
        }
    }
    //二级微信菜单显示
    if(machine.state==STATE_2_chat)
    {
        UI_2=(index_2-(index_2%3))/3+1;//计算当前显示的页面
        if(UI_2!=last_UI_2)
        {
            OLED_Clear();
            last_UI_2=UI_2;
        }
        OLED_ShowDot(index_2%3+1, 1);
        switch(UI_2)
        {
        case 1:
        for (uint8_t i = 0; i < 3; i++)
            OLED_ShowString(i+1, 2, menu_2_chat_items[i]);
            break;
        case 2:
            OLED_ShowString(1, 2, menu_2_chat_items[3]);
            break;
        }
    }
    //二级设置菜单显示
    if(machine.state==STATE_2_setting)
    {
        UI_2=(index_2-(index_2%3))/3+1;//计算当前显示的页面
        if(UI_2!=last_UI_2)
        {
            OLED_Clear();
            last_UI_2=UI_2;
        }
    
    OLED_ShowDot(index_2%3+1, 1);
    switch(UI_2)
    {
        case 1:
            for (uint8_t i = 0; i < 2; i++)
                OLED_ShowString(i+1, 2, menu_2_setting_items[i]);
                break;
        /*case 2:
                OLED_ShowString(1, 2, menu_2_setting_items[3]);
                break;*/
    }
    }
}

//一级菜单界面
void menu_1(void)//实际上一级菜单只有三个按键,上下和确认
{
    while(machine.state==STATE_1)
    {
        KeyNum = Key_GetNum();
        display_menu_1();
        if(index_1!=last_index_1)
        {
            OLED_ClearLine();
            last_index_1=index_1;
        }
        switch(KeyNum)
        {   
            case 1:
                index_1--;
                if(index_1<0)
                    index_1=menu_1_size-1;
                break;
            case 2:
                index_1++;
                if(index_1>menu_1_size-1)
                    index_1=0;
                break;
            case 3://只在进入下一级菜单时刷新下级菜单索引
                index_2=0;
                last_index_2=0;
                switch(index_1)
                {
                    case 0:
                        machine.state=STATE_2_chat;
                        break;
                    case 1:
                        machine.state=STATE_2_game;
                        break;
                    case 2:
                        machine.state=STATE_2_setting;
                        break;
                }
                break;
        }
    }
}

//二级游戏菜单界面
void menu_2_game(void)
{
    while(machine.state==STATE_2_game)
    {
        KeyNum = Key_GetNum();
        display_menu_2();
        if(index_2!=last_index_2)
        {
            OLED_ClearLine();
            last_index_2=index_2;
        }
        switch(KeyNum)
        {   
            case 1:
                index_2--;
                if(index_2<0)
                    index_2=menu_2_game_size-1;
                break;
            case 2:
                index_2++;
                if(index_2>menu_2_game_size-1)
                    index_2=0;
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
    }
}

//二级微信菜单界面
void menu_2_chat(void)
{
    while(machine.state==STATE_2_chat)
    {
        KeyNum = Key_GetNum();
        display_menu_2();
        if(index_2!=last_index_2)
        {
            OLED_ClearLine();
            last_index_2=index_2;
        }
        switch(KeyNum)
        {   
            case 1:
                index_2--;
                if(index_2<0)
                    index_2=menu_2_chat_size-1;
                break;
            case 2:
                index_2++;
                if(index_2>menu_2_chat_size-1)
                    index_2=0;
                break;
            case 3:
                break;//先写着这个分支,等到二级菜单界面完成后再修改
            case 4:
                machine.state=STATE_1;
                break;
        }
    }
}


//二级设置菜单界面
void menu_2_setting(void)
{
    
    while(machine.state==STATE_2_setting)
    {
        KeyNum = Key_GetNum();
        display_menu_2();
        if(index_2!=last_index_2)
        {
            OLED_ClearLine();
            last_index_2=index_2;
        }
        switch(KeyNum)
        {   
            case 1:
                index_2--;
                if(index_2<0)
                    index_2=menu_2_setting_size-1;
                break;
            case 2:
                index_2++;
                if(index_2>menu_2_setting_size-1)
                    index_2=0;
                break;
            case 3:
                switch(index_2)
                {
                    case 0:
                        machine.state=STATE_3_setting_light;
                        break;
                    case 1:
                        machine.state=STATE_3_setting_pwm;
                        break;
                }
                break;
            case 4:
                machine.state=STATE_1;
                break;
        }
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

void menu_3_setting_pwm(void)
{
	uint8_t i;
    while(machine.state==STATE_3_setting_pwm)
    {
        KeyNum = Key_GetNum();
        if(KeyNum==4)
            machine.state=STATE_2_setting;
        OLED_ShowString(1, 2, "PWM1:");
        //led变亮
        PWM_Init();
		for (i = 0; i <= 100; i++)       // 逐渐增加PWM占空比
		{
            KeyNum = Key_GetNum();
            if(KeyNum==4)
            {
                machine.state=STATE_2_setting;
                LED_Init();
                break;
            }
			PWM_SetCompare1(i);          // 设置PWM比较值
			Delay_ms(5);                // 延时10ms
		}
		//led变暗
		for (i = 0; i <= 100; i++)       // 逐渐减少PWM占空比
		{
            KeyNum = Key_GetNum();
            if(KeyNum==4)
            {
                machine.state=STATE_2_setting;
                LED_Init();
                break;
            }
			PWM_SetCompare1(100 - i);    // 设置PWM比较值
			Delay_ms(5);                // 延时10ms
		}
    }
}
