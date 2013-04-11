#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include "serial.h"
#include "status.h"
#include "dynamixel.h"
#include "global.h"

int CommStatus;



void wait_motion()
{
	int moving;
	do {
		int id;
		moving = 0;
		for ( id = 5; id <= ( NUM_ACTUATOR + 4 ); id++ ) {
			moving = moving + dxl_read_byte(id, P_MOVING );
		}
	} while ( moving != 0 );
}


void claw_close()
{
	wait_motion();
        CommStatus = dxl_get_result();
        if( CommStatus == COMM_RXSUCCESS )
	{
		dxl_write_word( 6, P_GOAL_POSITION_L, 670 );
		dxl_write_word( 7, P_GOAL_POSITION_L, 352 );
		wait_motion();
	}
	else
	{
                PrintCommStatus(CommStatus);
	}
}


void claw_open()
{
	wait_motion();
        CommStatus = dxl_get_result();
        if( CommStatus == COMM_RXSUCCESS )
	{
		dxl_write_word( 6, P_GOAL_POSITION_L, 492 );
		dxl_write_word( 7, P_GOAL_POSITION_L, 532 );
		wait_motion();
	}
	else
	{
                PrintCommStatus(CommStatus);
	}
}


void claw_lower()
{
	wait_motion();
        CommStatus = dxl_get_result();
        if( CommStatus == COMM_RXSUCCESS )
	{
		dxl_write_word( 5, P_GOAL_POSITION_L, 465 );
		wait_motion();
	}
	else
	{
                PrintCommStatus(CommStatus);
	}
}


void claw_lift()
{
	wait_motion();
        CommStatus = dxl_get_result();
        if( CommStatus == COMM_RXSUCCESS )
	{
		dxl_write_word( 5, P_GOAL_POSITION_L, 825 );
		wait_motion();
	}
	else
	{
                PrintCommStatus(CommStatus);
	}
}


void claw_init()
{
	claw_lift();
	claw_open();
}
