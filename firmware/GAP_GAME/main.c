
#include "main.h"


unsigned char buffer[(MATRIX_DISPLAYS * MATRIX_ROWS)];

int main(void)
{
	system_init();
	control_init();

    matrix_init();
    matrix_reset();
    _delay_ms(MATRIX_RESET_RECOVERY_TIME_MS);
    matrix_enable();

    uart_init();
	
	unsigned char x_pos = (MATRIX_ROWS / 2), y_pos = (MATRIX_DISPLAYS * MATRIX_COLUMNS / 2);
	unsigned char new_dot = 1, dot_x_pos, dot_y_pos;

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL2_bm | TCA_SINGLE_ENABLE_bm;
	TCB0.CTRLA = TCB_CLKSEL1_bm | TCB_ENABLE_bm; 

	while (1)
	{
		// Create a new dot position
		if(new_dot)
		{
			do
			{
				dot_x_pos = TCA0.SINGLE.CNT%(MATRIX_ROWS);
				dot_y_pos = TCB0.CNT%(MATRIX_DISPLAYS * MATRIX_COLUMNS);

			} while ((dot_x_pos == x_pos) || (dot_y_pos == y_pos) || (dot_x_pos == y_pos) || (dot_y_pos == x_pos));

			new_dot = 0;
		}

		// Create crosshairs on display
		for (unsigned char i=0; i < sizeof(buffer)/sizeof(buffer[0]); i++)
		{
			buffer[i] = 0x00;

			if((y_pos/MATRIX_COLUMNS) == (i/MATRIX_ROWS))
			{
				buffer[i] = (1<<(y_pos%MATRIX_COLUMNS));
			}

			if(x_pos == (i%MATRIX_ROWS))
			{
				buffer[i] = 0xFF;
			}
		}
		buffer[(dot_x_pos + ((dot_y_pos / MATRIX_COLUMNS) * MATRIX_ROWS))] |= (1<<(dot_y_pos%MATRIX_COLUMNS));

		matrix_frame(buffer);
		printf("POS(x=%1u/y=%1u) | DOT(x=%1u/y=%1u)    \r", x_pos, y_pos, dot_x_pos, dot_y_pos);

		char temp = 0;

		if(uart_scanchar(&temp) == UART_Received)
		{
			
		}

		if(control_status(CTRL_SW_RIGHT) || temp == 'd')
		{
    		control_led(CTRL_LED_CROSS_2, CTRL_MODE_TOGGLE);

			_delay_ms(100);

			if(x_pos < (MATRIX_ROWS - 1))
			{
				x_pos++;
			}
			else
			{
				x_pos = 0;
			}
		}
		if(control_status(CTRL_SW_LEFT) || temp == 'a')
		{
    		control_led(CTRL_LED_CROSS_2, CTRL_MODE_TOGGLE);

			_delay_ms(100);

			if(x_pos > 0)
			{
				x_pos--;
			}
			else
			{
				x_pos = (MATRIX_ROWS - 1);
			}
		}
		if(control_status(CTRL_SW_DOWN)  || temp == 's')
		{
    		control_led(CTRL_LED_CROSS_1, CTRL_MODE_TOGGLE);

			_delay_ms(100);

			if(y_pos > 0)
			{
				y_pos--;
			}
			else
			{
				y_pos = ((MATRIX_DISPLAYS * MATRIX_COLUMNS) - 1);
			}
		}
		if(control_status(CTRL_SW_UP)  || temp == 'w')
		{
    		control_led(CTRL_LED_CROSS_1, CTRL_MODE_TOGGLE);

			_delay_ms(100);

			if(y_pos < ((MATRIX_DISPLAYS * MATRIX_COLUMNS) - 1))
			{
				y_pos++;
			}
			else
			{
				y_pos = 0;
			}
		}
		if(control_status(CTRL_SW_A)  || control_status(CTRL_SW_B)  || temp == 'f')
		{
    		control_led(CTRL_LED_A | CTRL_LED_B, CTRL_MODE_TOGGLE);

			_delay_ms(100);
			
			if((x_pos == dot_x_pos) && (y_pos == dot_y_pos))
			{
				new_dot = 1;
			}
		}
		_delay_ms(10);
	}
}