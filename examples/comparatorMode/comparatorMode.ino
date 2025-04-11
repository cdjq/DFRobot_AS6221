/*!
 * @file comparatorMode.ino
 * @brief This section describes how to use the comparator mode of the AS6221.
 * @details The comparator mode is characterized that if the temperature value exceeds the THIGH value, 
 * @n the alert output is changed (e.g. from high to low if the polarity bit is set to 0 and vice versa). 
 * @n The alert output stays in that condition until the measured temperature drops below the defined TLOW value.
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-08
 * @url https://github.com/DFRobot/DFRobot_AS6221
 */
#include "DFRobot_AS6221.h"
DFRobot_AS6221 AS6221(/*uint8_t addr=*/0x49,/*TwoWire *pWire=*/&Wire);
const uint8_t interruptPin = 2;
bool lowThresholdFlag,highThresholdFlag=false;

void isrHandler() {
	static bool expectFall = true;
	if(expectFall) {
	  detachInterrupt(digitalPinToInterrupt(interruptPin));
	  attachInterrupt(digitalPinToInterrupt(interruptPin), isrHandler, RISING);
	  expectFall = false;
	  highThresholdFlag=true;
	} else {
	  detachInterrupt(digitalPinToInterrupt(interruptPin));
	  attachInterrupt(digitalPinToInterrupt(interruptPin), isrHandler, FALLING);
	  expectFall = true;
	  lowThresholdFlag=true;
	}
}
void setup() {
	Serial.begin(115200);
	while(!Serial);
	Serial.print("AS6221 init...");
	pinMode(interruptPin, INPUT_PULLUP);
	while(AS6221.begin()!=0){
		Serial.print("failed,Not found AS6221!");
	}
	Serial.println("successed");
	AS6221.wakeup();
    if(!AS6221.setHighThreshold(/*float highThreshold(range:-40~100)=*/30)){
		Serial.println("set high threshold failed!");
	}
	if(!AS6221.setLowThreshold(/*float lowThreshold(range:-40~100)=*/28)){
		Serial.println("set low threshold failed!");
	}
	/** eConversionRate_t conversionRate
	 *  AS6221.e4000ms  = 0.25 Conv/s 
   	 *  AS6221.e1000ms  = 1 Conv/s 
   	 *  AS6221.e250ms   = 4 Conv/s 
   	 *  AS6221.e125ms   = 8 Conv/s 
	 */
	AS6221.setConversionRate(/*eConversionRate_t conversionRate=*/AS6221.e1000ms);
	
	/** eConsecutiveFaults_t consecutiveFaults (An alarm will be given if the maximum number of faults exceeds the set)
	 *  AS6221.eOnce 
   	 *  AS6221.eTwice 
   	 *  AS6221.eThreeTimes 
   	 *  AS6221.eFourTimes
	 */
	AS6221.setConsecutiveFaults(/*eConsecutiveFaults_t consecutiveFaults=*/AS6221.eFourTimes);
	AS6221.setConfig(/*uint8_t interrputMode(range:0-1)=*/0,/*uint8_t polarity(range:0-1)=*/0);

  	attachInterrupt(digitalPinToInterrupt(interruptPin), isrHandler, FALLING);
}
  
void loop() {

	if(highThresholdFlag){
		highThresholdFlag=false;
		Serial.println("The temperature exceeds a high threshold!");
	}else if(lowThresholdFlag){
		lowThresholdFlag=false;
		Serial.println("The temperature is below the lower threshold!");
	}
	float temperature = AS6221.getTemperature();
	Serial.print("temperature: ");
	Serial.print(temperature);
	Serial.println(" C");

	delay(1000);
}
