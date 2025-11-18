/*
 *小车直流电机控制
 */
#ifndef _ELECTRICAL_MACHINERY_H_
#define _ELECTRICAL_MACHINERY_H_

void car_run(int speed, int difference);
void car_stop();
extern int MAX;
extern int MIN;

#endif