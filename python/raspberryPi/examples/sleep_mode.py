# -*- coding: utf-8 -*-
'''
@file sleep_mode.py
@brief This section describes how to use the sleep mode of the AS6221.
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
	print("AS6221 init...")
	if as6221.begin()!=0:
		print("failed,Not found AS6221!")
	print("successed")
	as6221.sleep()
def loop():
	while True:
		as6221.set_single_shot_conversion()
		while True:
			time.sleep(2)
			if as6221.is_single_shot_complete():
				break
			print("Please wait! A single measurement was not completed!")
		temperature = as6221.get_temperature()
		print("temperature: {} ℃".format(temperature))
		time.sleep(1)
# Execute setup function
setup()
# Execute loop function
loop()