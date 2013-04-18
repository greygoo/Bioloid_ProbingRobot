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
#include "adc.h"
#include "led.h"


int dms;
int ir;
int val_battery;

int main()
{
	serial_initialize(57600);
	led_init();
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
			_delay_ms(600);
			turn_r();
			_delay_ms(3200);
			drive_f();
		}

		
		dms = read_dms();
		if ( dms >= 630 )
		{
			object_detect();
		}

		val_battery = adc_readBatteryMillivolts();
		if ( val_battery <= LOW_VOLTAGE_CUTOFF ) {
			printf ("Battery value has reached low voltage %i. Stopping", val_battery );
			stop();
			led_off(ALL_LED);
			while(1)
			{
				led_toggle(LED_POWER);
				_delay_ms(300);
			}
		}

	}
}
