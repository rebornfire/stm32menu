#include "stm32f10x.h"
#include "OLED.h"
#include "Key.h"
#include "led.h"
#include "PWM.h"
#include "delay.h"

// 枚举状态,第一个是菜单级数,第二个是二级菜单索引,第三个是三级菜单索引
typedef enum
{
    STATE_1,
    STATE_2_game,
    STATE_2_chat,
    STATE_2_setting,
    STATE_3_setting_light,
    STATE_3_setting_pwm,
} State;

// 定义结构体
typedef struct
{
    State state;
} StateMachine;

StateMachine machine = {STATE_1}; // 初始化状态机
uint8_t KeyNum = 0;               // 记录按键值
int8_t index_1 = 0;               // 记录当前一级菜单索引
int8_t last_index_1 = 0;          // 记录上一次一级菜单索引
int8_t index_2 = 0;               // 记录当前二级菜单索引
int8_t last_index_2 = 0;          // 记录上一次二级菜单索引
//uint8_t UI_1, UI_2;               // 记录当前菜单显示的页面
uint8_t last_UI_1, last_UI_2;     // 记录上一次菜单显示的页面

char *menu_1_items[] = {"Chat", "Game", "Setting", "Exit"};
char *menu_2_game_items[] = {"yuanshen", "minchao", "juequ0", "xinqiongtiedao"};
char *menu_2_chat_items[] = {"WeChat", "QQ", "FeiShu", "DouYin"};
char *menu_2_setting_items[] = {"Turn Light", "PWM Breath"};

uint8_t menu_1_size = sizeof(menu_1_items) / sizeof(menu_1_items[0]);
uint8_t menu_2_game_size = sizeof(menu_2_game_items) / sizeof(menu_2_game_items[0]);
uint8_t menu_2_chat_size = sizeof(menu_2_chat_items) / sizeof(menu_2_chat_items[0]);
uint8_t menu_2_setting_size = sizeof(menu_2_setting_items) / sizeof(menu_2_setting_items[0]);

/**
  * @brief  显示菜单
  * @param  items 菜单项数组
  * @param  size 菜单项数量
  * @param  index 当前索引
  * @param  last_UI 上一次显示的页面
  * @retval 无
 **/
void display_menu(char **items, uint8_t size, int8_t index, uint8_t *last_UI)
{
    uint8_t UI = (index - (index % 3)) / 3 + 1; // 计算当前显示的页面
    //UI改变时刷新OLED,UI仅根据index指针刷新,所以没必要为UI建立指针
    if (UI != *last_UI)
    {
        OLED_Clear();
        *last_UI = UI;
    }
    OLED_ShowDot(index % 3 + 1, 1);
    for (uint8_t i = 0; i < 3 && (UI - 1) * 3 + i < size; i++)
    {
        OLED_ShowString(i + 1, 2, items[(UI - 1) * 3 + i]);
    }
}

/**
  * @brief  处理按键输入
  * @param  index 当前索引
  * @param  size 菜单项数量
  * @retval 无
 **/
void handle_key_input(int8_t *index, uint8_t size)
{
    KeyNum = Key_GetNum();
    switch (KeyNum)
    {
        case 1:
            (*index)--;
            if (*index < 0)
                *index = size - 1;
            OLED_ClearLine();
            break;
        case 2:
            (*index)++;
            if (*index >= size)
                *index = 0;
            OLED_ClearLine();
            break;
    }
}

/**
  * @brief  一级菜单界面
  * @param  无
  * @retval 无
 **/
void menu_1(void)
{
    while (machine.state == STATE_1)
    {
        handle_key_input(&index_1, menu_1_size);
        display_menu(menu_1_items, menu_1_size, index_1, &last_UI_1);
        if (KeyNum == 3)
        {
            index_2 = 0;
            last_index_2 = 0;
            switch (index_1)
            {
                case 0:
                    machine.state = STATE_2_chat;
                    break;
                case 1:
                    machine.state = STATE_2_game;
                    break;
                case 2:
                    machine.state = STATE_2_setting;
                    break;
            }
        }
    }
}

/**
  * @brief  二级菜单界面
  * @param  items 菜单项数组
  * @param  size 菜单项数量
  * @param  state 当前菜单状态
  * @retval 无
 **/
void menu_2(char **items, uint8_t size, State state)
{
    KeyNum = Key_GetNum();
    while (machine.state == state)
    {
        handle_key_input(&index_2, size);
        display_menu(items, size, index_2, &last_UI_2);
        if (KeyNum == 3&&state==STATE_2_setting)
        {
            switch (index_2)
            {
                case 0:
                    machine.state = STATE_3_setting_light;
                    break;
                case 1:
                    machine.state = STATE_3_setting_pwm;
                    break;
            }
        }
        if (KeyNum == 4)
        {
            machine.state = STATE_1;
        }
    }
}

/**
  * @brief  二级游戏菜单界面
  * @param  无
  * @retval 无
 **/
void menu_2_game(void)
{
    menu_2(menu_2_game_items, menu_2_game_size, STATE_2_game);
}

/**
  * @brief  二级微信菜单界面
  * @param  无
  * @retval 无
 **/
void menu_2_chat(void)
{
    menu_2(menu_2_chat_items, menu_2_chat_size, STATE_2_chat);
}

/**
  * @brief  二级设置菜单界面
  * @param  无
  * @retval 无
 **/
void menu_2_setting(void)
{
    menu_2(menu_2_setting_items, menu_2_setting_size, STATE_2_setting);
    if (KeyNum == 3)
    {
        switch (index_2)
        {
            case 0:
                machine.state = STATE_3_setting_light;
                break;
            case 1:
                machine.state = STATE_3_setting_pwm;
                break;
        }
    }
}

/**
  * @brief  三级设置菜单界面 - 灯光
  * @param  无
  * @retval 无
 **/
void menu_3_setting_light(void)
{
    while (machine.state == STATE_3_setting_light)
    {
        KeyNum = Key_GetNum();
        if (KeyNum == 1)
            LED1_Turn();
        if (KeyNum == 2)
            LED2_Turn();
        if (KeyNum == 3)
            LED3_Turn();
        if (KeyNum == 4)
            machine.state = STATE_2_setting;
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

/**
  * @brief  三级设置菜单界面 - PWM
  * @param  无
  * @retval 无
 **/
void menu_3_setting_pwm(void)
{
    uint8_t i;
    while (machine.state == STATE_3_setting_pwm)
    {
        KeyNum = Key_GetNum();
        if (KeyNum == 4)
            machine.state = STATE_2_setting;
        OLED_ShowString(1, 2, "PWM1:");
        // led变亮
        PWM_Init();
        for (i = 0; i <= 100; i++) // 逐渐增加PWM占空比
        {
            KeyNum = Key_GetNum();
            if (KeyNum == 4)
            {
                machine.state = STATE_2_setting;
                LED_Init();
                break;
            }
            PWM_SetCompare1(i); // 设置PWM比较值
            Delay_ms(5);        // 延时10ms
        }
        // led变暗
        for (i = 0; i <= 100; i++) // 逐渐减少PWM占空比
        {
            KeyNum = Key_GetNum();
            if (KeyNum == 4)
            {
                machine.state = STATE_2_setting;
                LED_Init();
                break;
            }
            PWM_SetCompare1(100 - i); // 设置PWM比较值
            Delay_ms(5);              // 延时10ms
        }
    }
}