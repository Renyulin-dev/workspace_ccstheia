#include "line_follower.h"
#include "ti_msp_dl_config.h"
#include "mspm0_motor_i2c.h"
#include "uart.h"
#include "draw.h"
#include "clock.h"
#include "electrical_machinery.h"

#include "stdbool.h"

unsigned char IRbuf[2];
uint8_t s1, s2, s3, s4, s5, s6, s7, s8;

static float error = 0, last_error = 0, integral = 0;

bool left_flage = false;
bool trun_flage = false;

void line_follower_update(void)
{
    mspm0_motor_i2c_read(IIC_ADDRESS, REGISTER_READ_ADDRESS, 2, IRbuf);
	
	s1 = (IRbuf[0]>>7)&0x01;
	s2 = (IRbuf[0]>>6)&0x01;
	s3 = (IRbuf[0]>>5)&0x01;
	s4 = (IRbuf[0]>>4)&0x01;
	s5 = (IRbuf[0]>>3)&0x01;
	s6 = (IRbuf[0]>>2)&0x01;
	s7 = (IRbuf[0]>>1)&0x01;
	s8 = (IRbuf[0]>>0)&0x01;
}

float line_folower(float kp, float ki, float kd)
{
    

    /* 1 1 1 1 1 1 1 1 */
    if (s1 && s2 && s3 && s4 && s5 && s6 && s7 && s8) 
    {
        trun_flage = true;
        integral = 0;
        return 0;
    }
    /* 1 1 1 0 0 1 1 1 */
    else if(s1 && s2 && s3 && !s4 && !s5 && s6 && s7 && s8) 
    {
        error =  0;
        integral = 0;
    } 
    /* 1 1 1 0 1 1 1 1 */  
    else if(s1 && s2 && s3 && !s4 && s5 && s6 && s7 && s8) 
    {
        error = 1;
    } 
    /* 1 1 0 0 1 1 1 1 */
    else if(s1 && s2 && !s3 && !s4 && s5 && s6 && s7 && s8) 
    { 
        error = 2;
    }
    /* 1 1 0 1 1 1 1 1 */
    else if(s1 && s2 && !s3 && s4 && s5 && s6 && s7 && s8) 
    { 
        error = 3;
    }  
    /* 1 0 0 1 1 1 1 1 */
    else if(s1 && !s2 && !s3 && s4 && s5 && s6 && s7 && s8) 
    { 
        error = 4;
    } 
    /* 1 0 1 1 1 1 1 1 */
    else if(s1 && !s2 && s3 && s4 && s5 && s6 && s7 && s8) 
    { 
        error = 5;
    } 
    /* 0 0 1 1 1 1 1 1 */
    else if(!s1 && !s2 && s3 && s4 && s5 && s6 && s7 && s8) 
    { 
        error = 6;
    }
    /* 0 1 1 1 1 1 1 1 */
    else if(!s1 && s2 && s3 && s4 && s5 && s6 && s7 && s8) 
    { 
        error =  7;
    }
    /* 1 1 1 1 0 1 1 1 */
    else if(s1 && s2 && s3 && s4 && !s5 && s6 && s7 && s8) 
    {
        error = -1;
    }
    /* 1 1 1 1 0 0 1 1 */
    else if(s1 && s2 && s3 && s4 && !s5 && !s6 && s7 && s8) 
    {
        error = -2;
    }
    /* 1 1 1 1 1 0 1 1 */
    else if(s1 && s2 && s3 && s4 && s5 && !s6 && s7 && s8) 
    {
        error = -3;
    }
    /* 1 1 1 1 1 0 0 1 */
    else if(s1 && s2 && s3 && s4 && s5 && !s6 && !s7 && s8) 
    {
        error = -4;
    }
    /* 1 1 1 1 1 1 0 1 */
    else if(s1 && s2 && s3 && s4 && s5 && s6 && !s7 && s8) 
    {
        error = -5;
    }
    /* 1 1 1 1 1 1 0 0 */
    else if(s1 && s2 && s3 && s4 && s5 && s6 && !s7 && !s8) 
    {
        error = -6;
    }
    /* 1 1 1 1 1 1 1 0 */
    else if(s1 && s2 && s3 && s4 && s5 && s6 && s7 && !s8) 
    {
        error = -7;
    }

    if(!s1)
    {
        left_flage = true;
    }
    else if(!s8)
    {
        left_flage = false;
    }
    
    integral += error;
    float output = kp * error + ki * integral + kd * (error - last_error);
    last_error = error;
    
    return output;
}

void car_trun(int8_t trun_speed)
{
    car_run(0, trun_speed);
    if(!s4 || !s5)
    {
        trun_flage = false;
    }
}

void CAR_CONTROL(void)
{
    line_follower_update();
    if(!trun_flage)
    {
        car_run(base_speed, line_folower(5,1,0));
    }
    else 
    {
        if(left_flage)
        {
           car_trun(15); 
        }
        else 
        {
            car_trun(-15);
        }
    }
}