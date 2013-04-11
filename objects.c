#include <util/delay.h>
#include "claw.h"
#include "sensors.h"
#include "drive.h"
#include "objects.h"



void object_detect(void)
{
	int object;
	int object_value;
	int dms;
	object = 1;
	object_value = 8;

	turn_r();

	while(1)
	{
		_delay_ms(128);
		dms = read_dms();
	//	printf("dms: %i\n",dms);
		if ( dms < 300 ) {
	//		printf("breaking\n");
			break;
		}
		object++;
		if ( object > object_value )
		{
			// avoid large obstacles
			do 
			{
				dms = read_dms();
			} while ( dms >= 300 );	
			_delay_ms(1024);
			drive_f();
			return;
		}
	}

	stop();
	object = 3;
	turn_l();
	_delay_ms(256);

	while(1)
	{
		_delay_ms(128);
		dms = read_dms();
		if ( dms < 300 ) {
			break;
		}
		object++;
		if ( object > object_value )
		{
                        // avoid large obstacles
                        do
                        {
                                dms = read_dms();
                        } while ( dms >= 300 );
                        _delay_ms(1024);
                        drive_f();
			return;
		}
	}

	// compare object values
	stop();
	turn_r();
	_delay_ms(object * 50);
	stop();
	set_aside();
	drive_f();
}

void initial(void)
{
	lift_object();
	drive_f();
}

void set_aside(void)
{
	lift_object();
	turn_r();
	_delay_ms(1792);
	drive_f();
	_delay_ms(1000);
	stop();
	set_object();
	drive_r();
	_delay_ms(512);
	turn_l();
	_delay_ms(1792);
	stop();
}

void lift_object(void)
{
	claw_open();
	claw_lower();
	claw_close();
	claw_lift();
}

void set_object(void)
{
	claw_lower();
	claw_open();
	claw_lift();
	claw_close();
}


