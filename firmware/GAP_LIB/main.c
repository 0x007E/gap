
#include "main.h"

unsigned char buffer[(MATRIX_DISPLAYS * MATRIX_ROWS)];

int main(void)
{
	system_init();
	
	matrix_init();
	matrix_reset();
	_delay_ms(MATRIX_RESET_RECOVERY_TIME_MS);
	
	adc_init();
	adc_channel(ADC_CH15);
	uart_init();
	
	printf("\n\rGamepad Initializing\n\r");
	
	matrix_enable();

	unsigned char i=1;

	for (unsigned char y=0; y < (MATRIX_DISPLAYS * MATRIX_ROWS); y++)
	{

		for (unsigned char x=0; x < MATRIX_COLUMNS; x++)
		{
			if(i <= x)
			{
				break;
			}
			buffer[y] |= (1<<(i - 1));
		}

		if((++i) > MATRIX_COLUMNS)
		{
			i = 1;
		}
	}
	matrix_frame(buffer);
	_delay_ms(1000);

	while (1)
	{
		printf("ADC-Value(CH15): %4u  \r", (adc_read()));
		
		if(control_status(CTRL_SW_UP))
		{
            control_led(CTRL_LED_CROSS_1, CTRL_MODE_TOGGLE);
            matrix_char(1, 'A');
		}
		if(control_status(CTRL_SW_DOWN))
		{
    		control_led(CTRL_LED_CROSS_1, CTRL_MODE_TOGGLE);
			matrix_char(2, 'B');
		}
		if(control_status(CTRL_SW_LEFT))
		{
    		control_led(CTRL_LED_CROSS_2, CTRL_MODE_TOGGLE);
			matrix_char(1, 'C');
		}
		if(control_status(CTRL_SW_RIGHT))
		{
    		control_led(CTRL_LED_CROSS_2, CTRL_MODE_TOGGLE);
			matrix_char(2, 'D');
		}
		if(control_status(CTRL_SW_A))
		{
    		control_led(CTRL_LED_A, CTRL_MODE_TOGGLE);
			matrix_char(1, 'E');
		}
		if(control_status(CTRL_SW_B))
		{
    		control_led(CTRL_LED_B, CTRL_MODE_TOGGLE);
			matrix_char(2, 'F');
		}
		if(control_status(CTRL_SW_SELECT))
		{
            control_led(CTRL_LED_CROSS_1 | CTRL_LED_CROSS_1 | CTRL_LED_A | CTRL_LED_B, CTRL_MODE_ON);
			matrix_char(1, 'X');
			matrix_char(2, 'X');
		}
		if(control_status(CTRL_SW_START))
		{
    		control_led(CTRL_LED_CROSS_1 | CTRL_LED_CROSS_1 | CTRL_LED_A | CTRL_LED_B, CTRL_MODE_OFF);
			matrix_clear(1);
			matrix_clear(2);
		}
	}
}

