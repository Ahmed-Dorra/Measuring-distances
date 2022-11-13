/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultrasonic driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

# include "icu.h"
#include "ultrasonic.h"
#include "gpio.h"
#include<util/delay.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
volatile uint16 g_timerValue =0;

void Ultrasonic_init(void)
{
	ICU_config settings = {RISING, FCPU_8};
	ICU_SetCallBack(Ultrasonic_edgeProcessing);
	ICU_init(&settings);
	GPIO_setupPinDirection(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, PIN_OUTPUT);

}


void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, LOGIC_LOW);
	_delay_us(10);

}


uint16 Ultrasonic_readDistance(void)
{
	uint16 distance;
	Ultrasonic_Trigger();
	distance = g_timerValue/58.8;
	return distance;


}


void Ultrasonic_edgeProcessing(void)
{
	static uint8 g_ultrasonicEdgeId =0;
	g_ultrasonicEdgeId++;
	if(1 == g_ultrasonicEdgeId)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);

	}
	else if(2 == g_ultrasonicEdgeId)
	{
		g_timerValue = Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		g_ultrasonicEdgeId = 0;
	}
}









