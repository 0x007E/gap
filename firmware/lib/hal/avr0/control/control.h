/* -----------------------------------------
* G.Raf^engineering
* www.sunriax.at (github.com/0x007e)
* -----------------------------------------
*    Platform: Independent
*    Hardware: ATTiny406/1606/...
* -----------------------------------------
*     Version: 1.0 Release
*      Author: G.Raf
* Description:
*	Header for initializing control untis
* -----------------------------------------
*/

#ifndef CONTROL_H_
#define CONTROL_H_

    // MACROS
    #define SET(NUMBER, ARGUMENT) PIN ## NUMBER ## ARGUMENT

    // INPUTS
    #define SWITCH_PORT       PORTD

    #define S1_UP             SET(2, _bm)
    #define S1_UP_PINCTRL     SET(2, CTRL)
    #define S2_DOWN           SET(4, _bm)
    #define S2_DOWN_PINCTRL   SET(4, CTRL)
    #define S3_LEFT           SET(3, _bm)
    #define S3_LEFT_PINCTRL   SET(3, CTRL)
    #define S4_RIGHT          SET(7, _bm)
    #define S4_RIGHT_PINCTRL  SET(7, CTRL)
    #define S5_A              SET(6, _bm)
    #define S5_A_PINCTRL      SET(6, CTRL)
    #define S6_B              SET(5, _bm)
    #define S6_B_PINCTRL      SET(5, CTRL)
    #define S7_SELECT         SET(1, _bm)
    #define S7_SELECT_PINCTRL SET(1, CTRL)
    #define S8_START          SET(0, _bm)
    #define S8_START_PINCTRL  SET(0, CTRL)

    // OUTPUTS
    #define LED_PORT     PORTC
    #define LED_CROSS_1 PIN0_bm
    #define LED_CROSS_2 PIN1_bm
    #define LED_B_RED   PIN2_bm
    #define LED_A_GREEN PIN3_bm

    #define BUZZER_PORT PORTF
    #define BUZZER_PIN PIN4_bm

    #include <avr/io.h>

    enum CTRL_Status_t
    {
        CTRL_STATUS_OFF=0,
        CTRL_STATUS_ON
    };
    typedef enum CTRL_Status_t CTRL_Status;
    
    enum CTRL_Mode_t
    {
        CTRL_MODE_OFF=0,
        CTRL_MODE_ON,
        CTRL_MODE_TOGGLE,
        CTRL_MODE_NONE
    };
    typedef enum CTRL_Mode_t CTRL_Mode;

    enum CTRL_Switch_t
    {
        CTRL_SW_START=S8_START,
        CTRL_SW_SELECT=S7_SELECT,
        CTRL_SW_UP=S1_UP,
        CTRL_SW_LEFT=S3_LEFT,
        CTRL_SW_DOWN=S2_DOWN,
        CTRL_SW_B=S6_B,
        CTRL_SW_A=S5_A,
        CTRL_SW_RIGHT=S4_RIGHT
    };
    typedef enum CTRL_Switch_t CTRL_Switch;

    enum CTRL_LED_t
    {
        CTRL_LED_CROSS_1=LED_CROSS_1,
        CTRL_LED_CROSS_2=LED_CROSS_2,
        CTRL_LED_A=LED_B_RED,
        CTRL_LED_B=LED_A_GREEN,
    };
    typedef enum CTRL_LED_t CTRL_LED;

    void control_init(void);
    CTRL_Status control_status(CTRL_Switch sw);
    void control_led(CTRL_LED led, CTRL_Mode mode);
    void control_buzzer(CTRL_Mode mode);

#endif /* CONTROL_H_ */