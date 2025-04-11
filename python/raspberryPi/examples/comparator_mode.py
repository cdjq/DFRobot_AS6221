# -*- coding: utf-8 -*-
'''
@file comparator_mode.py
@brief This section describes how to use the comparator mode of the AS6221.
@details The comparator mode is characterized that if the temperature value exceeds the THIGH value, 
@n the alert output is changed (e.g. from high to low if the polarity bit is set to 0 and vice versa). 
@n The alert output stays in that condition until the measured temperature drops below the defined TLOW value.
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
import RPi.GPIO as GPIO
as6221 = DFRobot_AS6221(addr=0x49,bus=1)
INT_PIN=4
expectFall = True
high_threshol_flag = False
low_threshol_flag = False
def isrHandler(index):
	global expectFall,high_threshol_flag,low_threshol_flag
	if expectFall:
		GPIO.remove_event_detect(INT_PIN)
		GPIO.add_event_detect(INT_PIN, GPIO.RISING, isrHandler)
		expectFall=False
		high_threshol_flag = True
	else:
		GPIO.remove_event_detect(INT_PIN)
		GPIO.add_event_detect(INT_PIN, GPIO.FALLING, isrHandler)
		expectFall=True
		low_threshol_flag = True		
def setup():
	print("AS6221 init...")
	if as6221.begin()!=0:
		print("failed,Not found AS6221!")
	print("successed")
	as6221.wakeup()
	as6221.set_high_threshold(32)#range -40~100
	as6221.set_low_threshold(31)#range -40~100
	'''Conversion rate
		as6221.ConversionRate.e4000ms  = 0.25 Conv/s 
		as6221.ConversionRate.e1000ms  = 1 Conv/s 
		as6221.ConversionRate.e250ms   = 4 Conv/s 
		as6221.ConversionRate.e125ms   = 8 Conv/s 
	'''
	as6221.set_conversion_rate(as6221.ConversionRate.e1000ms)
	'''Consecutive Faults
		as6221.ConsecutiveFaults.eOnce    
		as6221.ConsecutiveFaults.eTwice  
		as6221.ConsecutiveFaults.eThreeTimes   
		as6221.ConsecutiveFaults.eFourTimes   
	'''
	as6221.set_consecutive_faults(as6221.ConsecutiveFaults.eOnce)
	as6221.set_config(interrupt_mode=0,polarity=0)
	GPIO.setmode(GPIO.BCM)
	GPIO.setwarnings(False)
	GPIO.setup(INT_PIN, GPIO.IN)
	GPIO.add_event_detect(INT_PIN, GPIO.FALLING, isrHandler)
def loop():
	global high_threshol_flag,low_threshol_flag
	while True:
		if high_threshol_flag:
			high_threshol_flag=False
			print("The temperature exceeds a high threshold!")
		elif low_threshol_flag:
			low_threshol_flag = False
			print("The temperature is below the lower threshold!")
		temperature = as6221.get_temperature()
		print("temperature: {} ℃".format(temperature))
		time.sleep(1)
# Execute setup function
setup()
# Execute loop function
loop()