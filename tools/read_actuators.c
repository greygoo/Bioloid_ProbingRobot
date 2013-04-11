#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "serial.h"
#include "dynamixel.h"
#include "status.h"
#include "../global.h"

#define NUM_ACTUATORS 7

int CommStatus;
int PresentPos;

int main(void)
{
	serial_initialize(57600);
        dxl_initialize( 0, DEFAULT_BAUDNUM ); // Not using device index
        sei();  // Interrupt Enable

	CommStatus = dxl_get_result();
	if ( CommStatus == COMM_RXSUCCESS )
	{
		int id;
		while(1)
		{
			for ( id = 1; id <= NUM_ACTUATORS; id++)
			{
				// Read current position
				PresentPos = dxl_read_word( id, P_PRESENT_POSITION_L );
				printf("Servo: %i Current Position: %i \n", id, PresentPos );
		
			}
			printf("\n\n");
			_delay_ms(2000);
		}
	}
	else
	{
		PrintCommStatus(CommStatus);
	}
}

