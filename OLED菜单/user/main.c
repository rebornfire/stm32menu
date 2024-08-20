#include "headfile.h"

uint8_t KeyNum = 0;

// 枚举状态
typedef enum {
    STATE_A,
    STATE_B,
    STATE_C,
    STATE_D,
} State;

// 定义结构体
typedef struct {
    State state;
} StateMachine;


int main(void)
{
    OLED_Init();
    LED_Init();
    Key_Init();
    //uint8_t i;  // 计数用
    uint8_t index_1=1;   // 一级菜单索引
    uint8_t last_index_1;   // 记录上一个一级菜单索引
    uint8_t index_2=1;   // 二级菜单索引
    uint8_t last_index_2;   // 记录上一个二级菜单索引
    StateMachine machine = {STATE_A}; // 初始化状态机
    State previousState = STATE_A;    // 记录上一个状态
    while (1)
    {
        KeyNum = Key_GetNum(); // 获取按键值
        if(machine.state!=previousState)
        {
            OLED_Clear();
        }
		//用于显示一级菜单的索引值
        if (machine.state == STATE_A)
        {
            if(KeyNum==1)
            {
                index_1++;
                if(index_1>3)
                {
                    index_1=1;
                }
            }
            else if(KeyNum==2)
            {
                index_1--;
                if(index_1<1)
                {
                    index_1=3;
                }
            }
            previousState=machine.state;
        }
        
        //用于显示二级菜单的索引值,在进入二级菜单时会重新刷新index_2的值
        if (machine.state != STATE_A)
        {   
            if (previousState==STATE_A)
            {
                OLED_Clear(); 
                previousState=machine.state;
                index_2=1;
            }
            if(KeyNum==1)
            {
                index_2++;
                if(index_2>3)
                {
                    index_2=1;
                }
            }
            else if(KeyNum==2)
            {
                index_2--;
                if(index_2<1)
                {
                    index_2=3;
                }
            }
        }
        
        if (index_1!=last_index_1)
        {
            last_index_1=index_1;
            OLED_ClearLine();
        }
        if (index_2!=last_index_2)
        {
            last_index_2=index_2;
            OLED_ClearLine();
        }
        // 根据当前状态处理逻辑
        switch (machine.state)
        {
            case STATE_A://一级菜单
                if(KeyNum==3)//跳转回一级菜单
                {
                    OLED_Clear();
                    switch(index_1)
                    {
                        case 1:
                            machine.state=STATE_B;
                            break;
                        case 2:
                            machine.state=STATE_C;
                            break;
                        case 3:
                            machine.state=STATE_D;
                            break;
                    }
                }
                OLED_ShowDot(index_1, 1);
                
                OLED_ShowString(1, 2, "Game");
                OLED_ShowString(2, 2, "WeChat");
                OLED_ShowString(3, 2, "Setting");
                break;

            case STATE_B://二级游戏菜单
                if(KeyNum==3)//跳转回一级菜单
                {
                    if(index_2==3)
                    {
                        OLED_Clear();
                        machine.state=STATE_A;
                    }
                }
                OLED_ShowDot(index_2, 1);
                
                //显示原神启动
                OLED_ShowChinese(1, 2, 0);
                OLED_ShowChinese(1, 4, 1);
                OLED_ShowChinese(2, 2, 2);
                OLED_ShowChinese(2, 4, 3);
                OLED_ShowString(3, 2, "Back");
                break;

            case STATE_C://二级设置菜单
                if(KeyNum==3)//跳转回一级菜单
                {
                    if(index_2==3)
                    {
                        OLED_Clear();
                        machine.state=STATE_A;
                    }
                }
                OLED_ShowDot(index_2, 1);
                OLED_ShowString(1, 2, "Light");
                OLED_ShowString(2, 2, "Airplane mode");
                OLED_ShowString(3, 2, "Back");
                break;

            case STATE_D://二级微信菜单
                if(KeyNum==3)//跳转回一级菜单
                {
                    if(index_2==3)
                    {
                        OLED_Clear();
                        machine.state=STATE_A;
                    }
                }
                OLED_ShowDot(index_2, 1);
                OLED_ShowString(1, 2, "WeChat");
                OLED_ShowString(2, 2, "WeChat");
                OLED_ShowString(3, 2, "Back");
                break;
            default:
                break;
        }
    }
}
