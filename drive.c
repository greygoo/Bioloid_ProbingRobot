#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include "serial.h"
#include "dynamixel.h"
#include "status.h"
#include "global.h"


int debug = 1;
int CommStatus;
int Moving;

void set_wheel_mode(int id)
{
	CommStatus = dxl_get_result();
	if( CommStatus == COMM_RXSUCCESS ){
		// Set CCW/CW angle limit to 0 to switch to wheel mode
		if ( debug == 1 ) {
			printf ("switching ID %i to wheel mode\n", id);
		}
		int cw_limit;
		cw_limit = dxl_read_word ( id, CW_ANGLE_LIMIT_L );
		printf("CW_LIMIT is: %i", cw_limit);
		dxl_write_word( id, CW_ANGLE_LIMIT_L, 0 );
		//dxl_write_word( id, CCW_ANGLE_LIMIT_L, 0 );
	}
	else
	{
		PrintCommStatus(CommStatus);
	}
}

void drive_f()
{
	Moving = dxl_read_byte( 1, P_MOVING );
	CommStatus = dxl_get_result();
	if( CommStatus == COMM_RXSUCCESS ){
		if ( debug == 1 ){
			printf ("DRIVE: Set goal speed for ID 1,3 to 1536, for ID 2,4 to 512\n");
		}
		dxl_write_word( 2, P_GOAL_SPEED_L, 512 );
		dxl_write_word( 4, P_GOAL_SPEED_L, 512 );
		dxl_write_word( 1, P_GOAL_SPEED_L, 1536 );
		dxl_write_word( 3, P_GOAL_SPEED_L, 1536 );
	}
	else {
		PrintCommStatus(CommStatus);
	}
}

void drive_r()
{
	Moving = dxl_read_byte( 1, P_MOVING );
	CommStatus = dxl_get_result();
	if( CommStatus == COMM_RXSUCCESS ){
		if ( debug == 1 ){
			printf ("DRIVE: Set goal speed for ID 1,3 to 1536, for ID 2,4 to 512\n");
		}
		dxl_write_word( 2, P_GOAL_SPEED_L, 1536 );
		dxl_write_word( 4, P_GOAL_SPEED_L, 1536 );
		dxl_write_word( 1, P_GOAL_SPEED_L, 512 );
		dxl_write_word( 3, P_GOAL_SPEED_L, 512 );
	}
	else {
		PrintCommStatus(CommStatus);
	}
}

void turn_r()
{
	Moving = dxl_read_byte( 1, P_MOVING );
	CommStatus = dxl_get_result();
	if( CommStatus == COMM_RXSUCCESS ){
		int i;
		for ( i = 1; i <= NUM_WHEELS; i++) {
			dxl_write_word( i, P_GOAL_SPEED_L, 512 );
		}
	}
	else {
		PrintCommStatus(CommStatus);
	}
}

void turn_l()
{
	Moving = dxl_read_byte( 1, P_MOVING );
	CommStatus = dxl_get_result();
	if( CommStatus == COMM_RXSUCCESS ){
		int i;
		for ( i = 1; i <= NUM_WHEELS; i++) {
			dxl_write_word( i, P_GOAL_SPEED_L, 1536 );
		}
	}
	else {
		PrintCommStatus(CommStatus);
	}
}

void stop()
{
	CommStatus = dxl_get_result();
	if( CommStatus == COMM_RXSUCCESS ){
		if ( debug == 1 ){
			printf ("STOP: Set goal speed for ID 1,3 to 1024, for ID 2,4 to 0\n");
		}
		dxl_write_word( 2, P_GOAL_SPEED_L, 0 );
		dxl_write_word( 4, P_GOAL_SPEED_L, 0 );
		dxl_write_word( 1, P_GOAL_SPEED_L, 1024 );
		dxl_write_word( 3, P_GOAL_SPEED_L, 1024 );
	}
	else {
		PrintCommStatus(CommStatus);
	}
}
