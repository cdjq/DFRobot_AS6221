# -*- coding: utf-8 -*-
'''
 @file body_thermometer.py
 @brief This example simulates a body thermometer
 @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 @license The MIT License (MIT)
 @author [fary](feng.yang@dfrobot.com)
 @version V1.0
 @date 2025-04-08
 @url https://github.com/DFRobot/DFRobot_AS6221
'''
import time
import sys
sys.path.append("../")
from DFRobot_AS6221 import DFRobot_AS6221

as6221 = DFRobot_AS6221(addr=0x49,bus=1)
def setup():
	if as6221.begin()!=0:
		print("AS6221 init failed,Not found AS6221!")
	print("AS6221 init successed")
	as6221.wakeup()
	'''Conversion rate
		as6221.ConversionRate.e4000ms  = 0.25 Conv/s 
		as6221.ConversionRate.e1000ms  = 1 Conv/s 
		as6221.ConversionRate.e250ms   = 4 Conv/s 
		as6221.ConversionRate.e125ms   = 8 Conv/s 
	'''
	as6221.set_conversion_rate(as6221.ConversionRate.e1000ms)
	as6221.set_config(interrupt_mode=0)
def loop():
	while True:
		temperature = as6221.get_temperature()
		if temperature>37.5 :
			print("You have a fever and the temperature is {}  degrees Celsius".format(temperature))
		elif temperature>37.0 and temperature<37.5:
			print("You have a bit of a low-grade fever and the temperature is {}  degrees Celsius".format(temperature))
		elif temperature>36.0 and temperature<37.5:
			print("Your body temperature is normal, the temperature is {}  degrees Celsius".format(temperature))
		elif temperature<36.0 :
			print("You're in a state of instability, and the temperature is {}  degrees Celsius".format(temperature))
		time.sleep(1)
# Execute setup function
setup()
# Execute loop function
loop()