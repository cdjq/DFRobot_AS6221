/*!
 * @file sleepMode.ino
 * @brief This section describes how to use the sleep mode of the AS6221.
 * @n After AS6221 enters sleep mode, the single acquisition mode can be configured through registers, 
 * @n and access to the registers can determine whether the acquisition is complete.
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-08
 * @url https://github.com/DFRobot/DFRobot_AS6221
 */
#include "DFRobot_AS6221.h"
DFRobot_AS6221 AS6221(/*uint8_t addr=*/0x49,/*TwoWire *pWire=*/&Wire);

void setup() {
	Serial.begin(115200);
	while(!Serial);
	Serial.print("AS6221 init...");
	while(AS6221.begin()!=0){
		Serial.print("failed,Not found AS6221!");
	}
	Serial.println("successed");
	AS6221.sleep();
}
  
void loop() {
	AS6221.setSingleShotConversion();
	while(1){
		delay(2000);
		if(AS6221.IsSingleShotComplete()){
			break;
		}
		Serial.println("Please wait! A single measurement was not completed!");
	}
	float temperature = AS6221.getTemperature();
	Serial.print("temperature: ");
	Serial.print(temperature);
	Serial.println(" C");
	delay(1000);
}
