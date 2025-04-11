/*!
 * @file bodyThermometer.ino
 * @brief This example simulates a body thermometer
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-08
 * @url https://github.com/DFRobot/DFRobot_AS6221
 */
#include "DFRobot_AS6221.h"
DFRobot_AS6221 AS6221(/*uint8_t addr=*/0x49);

void setup() {
	Serial.begin(115200);
	while(!Serial);
	Serial.print("AS6221 init...");
	while(AS6221.begin()!=0){
		Serial.print("failed,Not found AS6221!");
	}
	Serial.println("successed");
	AS6221.wakeup();
	/** eConversionRate_t conversionRate
	 *  AS6221.e4000ms  = 0.25 Conv/s 
   	 *  AS6221.e1000ms  = 1 Conv/s 
   	 *  AS6221.e250ms   = 4 Conv/s 
   	 *  AS6221.e125ms   = 8 Conv/s 
	 */
	AS6221.setConversionRate(/*eConversionRate_t conversionRate=*/AS6221.e1000ms);
	AS6221.setConfig(/*uint8_t interrputMode(range 0-1)=*/0);

}
  
void loop() {
	float temperature = AS6221.getTemperature();
	if(temperature>37.5){
		Serial.print("You have a fever and the temperature is ");
		Serial.print(temperature);
		Serial.println(" degrees Celsius");
	}else if(temperature>37.0 && temperature<37.5){
		Serial.print("You have a bit of a low-grade fever and the temperature is ");
		Serial.print(temperature);
		Serial.println(" degrees Celsius");
	}else if(temperature>36.0 && temperature<37.5){
		Serial.print("Your body temperature is normal, the temperature is ");
		Serial.print(temperature);
		Serial.println(" degrees Celsius");
	}else if(temperature<36.0){
		Serial.print("You're in a state of instability, and the temperature is ");
		Serial.print(temperature);
		Serial.println(" degrees Celsius");
	}
	delay(1000);
}
