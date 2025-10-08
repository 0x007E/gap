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
*	Library for initializing system clock
* -----------------------------------------
*/

#include "control.h"

void control_init(void)
{
    SWITCH_PORT.DIRCLR = S1_UP | S2_DOWN | S3_LEFT | S4_RIGHT | S5_A | S6_B | S7_SELECT | S8_START;
    SWITCH_PORT.S1_UP_PINCTRL = PORT_PULLUPEN_bm;
    SWITCH_PORT.S2_DOWN_PINCTRL = PORT_PULLUPEN_bm;
    SWITCH_PORT.S3_LEFT_PINCTRL = PORT_PULLUPEN_bm;
    SWITCH_PORT.S4_RIGHT_PINCTRL = PORT_PULLUPEN_bm;
    SWITCH_PORT.S5_A_PINCTRL = PORT_PULLUPEN_bm;
    SWITCH_PORT.S6_B_PINCTRL = PORT_PULLUPEN_bm;
    SWITCH_PORT.S7_SELECT_PINCTRL = PORT_PULLUPEN_bm;
    SWITCH_PORT.S8_START_PINCTRL = PORT_PULLUPEN_bm;
	
	LED_PORT.DIRSET = LED_A_GREEN | LED_B_RED | LED_CROSS_2 | LED_CROSS_1;
	BUZZER_PORT.DIRSET = BUZZER_PIN;
}

CTRL_Status control_status(CTRL_Switch sw)
{
    if(!(SWITCH_PORT.IN & sw))
    {
        return CTRL_STATUS_ON;
    }
    return CTRL_STATUS_OFF;
}

void control_led(CTRL_LED led, CTRL_Mode mode)
{
    switch (mode)
    {
        case CTRL_MODE_OFF:
            LED_PORT.OUTCLR = led;
        break;
        case CTRL_MODE_ON:
            LED_PORT.OUTSET = led;
        break;
        case CTRL_MODE_TOGGLE:
            LED_PORT.OUTTGL = led;
        break;
        default:
            
        break;
    }
}

void control_buzzer(CTRL_Mode mode)
{
    switch (mode)
    {
        case CTRL_MODE_OFF:
            BUZZER_PORT.OUTCLR = BUZZER_PIN;
        break;
        case CTRL_MODE_ON:
            BUZZER_PORT.OUTSET = BUZZER_PIN;
        break;
        case CTRL_MODE_TOGGLE:
            BUZZER_PORT.OUTTGL = BUZZER_PIN;
        break;
        default:
        
        break;
    }
}