#include "headfile.h"



uint8_t KeyNum = 0; // 按键值



// 枚举状态

typedef enum {

    STATE_A, // 状态A

    STATE_B, // 状态B

    STATE_C  // 状态C

} State;



// 定义结构体

typedef struct {

    State state; // 当前状态

} StateMachine;



// 函数声明

void handle_A(StateMachine *machine, uint8_t KeyNum); // 处理状态A

void handle_B(StateMachine *machine, uint8_t KeyNum); // 处理状态B

void handle_C(StateMachine *machine, uint8_t KeyNum); // 处理状态C



void handle_A(StateMachine *machine, uint8_t KeyNum)

{

    switch (KeyNum)

    {

        case 1:

            machine->state = STATE_B; // 进入下一个状态B

            break;

        case 2:

            machine->state = STATE_C; // 进入下一个状态C

            break;

        case 3:

            machine->state = STATE_A; // 回到第一个状态A

            break;

        default:

            break;

    }

}



void handle_B(StateMachine *machine, uint8_t KeyNum)

{

    switch (KeyNum)

    {

        case 1:

            machine->state = STATE_C; // 进入下一个状态C

            break;

        case 2:

            machine->state = STATE_A; // 进入上一个状态A

            break;

        case 3:

            machine->state = STATE_A; // 回到第一个状态A

            break;

        default:

            break;

    }

}



void handle_C(StateMachine *machine, uint8_t KeyNum)

{

    switch (KeyNum)

    {

        case 1:

            machine->state = STATE_A; // 进入下一个状态A

            break;

        case 2:

            machine->state = STATE_B; // 进入上一个状态B

            break;

        case 3:

            machine->state = STATE_A; // 回到第一个状态A

            break;

        default:

            break;

    }

}



int main(void)

{

    OLED_Init(); // 初始化OLED

    LED_Init();  // 初始化LED

    Key_Init();  // 初始化按键



    uint8_t i;  // 计数用

    uint8_t t;  // 进入B状态的标志位

    StateMachine machine = {STATE_A}; // 初始化状态机，初始状态为A

    State previousState = STATE_A;    // 记录上一个状态，初始为A



    while (1)

    {

        KeyNum = Key_GetNum(); // 获取按键值



        // 如果状态发生变化，则清除OLED屏幕

        if (machine.state != previousState)

        {

            OLED_Clear();

            previousState = machine.state; // 更新上一个状态

            t = 1;

        }

        else

        {

            t = 0;

        }



        // 根据当前状态处理逻辑

        switch (machine.state)

        {

            case STATE_A:

                handle_A(&machine, KeyNum); // 处理状态A

                OLED_ShowString(1, 1, "Press the");

                OLED_ShowString(2, 1, "first key");

                break;



            case STATE_B:

                handle_B(&machine, KeyNum); // 处理状态B

                if (t)

                {

                    for (i = 0; i < 100; i++)

                    {

                        OLED_ShowString(1, 1, "yuan shen");

                    }

                }

                OLED_ShowString(1, 1, "qi dong");

                break;



            case STATE_C:

                handle_C(&machine, KeyNum); // 处理状态C

                OLED_ShowNum(3, 1, 12345, 5);

                break;



            default:

                break;

        }

    }

}