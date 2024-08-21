#include "stm32f10x.h"
#include "OLED.h"
#include "Key.h"


uint8_t KeyNum = 0;
uint8_t index_1=1;
uint8_t last_index_1=1;
uint8_t index_2=1;
uint8_t last_index_2=1;

//菜单界面初始化
void menu_init()
{
    OLED_Init();
    Key_Init();
}

//一级菜单界面
void menu_1()//实际上一级菜单只有三个按键,上下和确认
{
    
    while(KeyNum!=3)//按下确定时跳转二级菜单
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
                index_1++;
                if(index_1>3)
                    index_1=1;
                break;
            case 2:
                index_1--;
                if(index_1<1)
                    index_1=3;
                break;
        }
        OLED_ShowDot(index_1, 1);
        OLED_ShowString(1, 2, "WeChat");
        OLED_ShowString(2, 2, "Game");
        OLED_ShowString(3, 2, "Setting");
    }
}

//二级游戏菜单界面
void menu_2_game()
{
    
    while(KeyNum!=4)//按下返回时返回一级菜单
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
                index_2++;
                if(index_2>3)
                    index_2=1;
                break;
            case 2:
                index_2--;
                if(index_2<1)
                    index_2=3;
                break;  
            case 3:
                /*if(index_2==3)
                    return 0; // 返回一级菜单*/
                break;
        }
        OLED_ShowDot(index_2, 1);
        OLED_ShowString(1, 2, "Genshin Impact");
        OLED_ShowString(2, 2, "Start");
        OLED_ShowString(3, 2, "Setting");
    }
}

//二级微信菜单界面
void menu_2_wechat()
{
    
    while(KeyNum!=4)//按下返回时返回一级菜单
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
                index_2++;
                if(index_2>2)
                    index_2=1;
                break;
            case 2:
                index_2--;
                if(index_2<1)
                    index_2=2;
                break;
            case 3:
                break;//先写着这个分支,等到二级菜单界面完成后再修改
            
        }
        OLED_ShowDot(index_2, 1);
        OLED_ShowString(1, 2, "Chat");
        OLED_ShowString(2, 2, "QQ");
    }
}


//二级设置菜单界面
void menu_2_setting()
{
    
    while(KeyNum!=4)//按下返回时返回一级菜单
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
                index_2++;
                if(index_2>2)
                    index_2=1;
                break;
            case 2:
                index_2--;
                if(index_2<1)
                    index_2=2;
                break;
            case 3:
                break;
                    
        }
        OLED_ShowDot(index_2, 1);
        OLED_ShowString(1, 2, "Light");
        OLED_ShowString(2, 2, "Setting");
    }
}
