#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include "serial.h"
#include "dynamixel.h"
#include "drive.h"
#include "sensors.h"
#include "claw.h"
#include "global.h"
#include "objects.h"

int dms;
int ir;

int main()
{
	serial_initialize(57600);
        dxl_initialize( 0, DEFAULT_BAUDNUM ); // Not using device index
        sei();  // Interrupt Enable 

	printf("Starting main\n");
	int i;
	for (i = 1; i <= NUM_WHEELS; i++) {
		set_wheel_mode(i);
	}

	initial();

	while (1) 
	{
		ir = read_ir();
		if ( ir < 80 )
		{
			// avoid cliffs/voids
			drive_r();
			_delay_ms(1792);
			turn_r;
			_delay_ms(3200);
			drive_f();
		}

		
		dms = read_dms();
		if ( dms >= 600 )
		{
			object_detect();
		}
	}
}
