

'''
@file DFRobot_AS6221.py
@brief DFRobot_AS6221 class infrastructure
@copyright	Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
@license The MIT License (MIT)
@author [fary](feng.yang@dfrobot.com)
@version V1.0
@date 2025-04-11
@url https://github.com/DFRobot/DFRobot_AS6221
'''
from smbus2 import SMBus, i2c_msg
import time

class DFRobot_AS6221:

    AS6221_ADDR_TVAL = 0x00
    AS6221_ADDR_CONFIG = 0x01
    AS6221_ADDR_TLOW = 0x02
    AS6221_ADDR_THIGH = 0x03
    AS6221_RESOLUTION = 0.0078125

    class ConversionRate:
        e4000ms = 0
        e1000ms = 1
        e250ms = 2
        e125ms = 3

    class ConsecutiveFaults:
        eOnce = 0
        eTwice = 1
        eThreeTimes = 2
        eFourTimes = 3

    def __init__(self, addr,bus=1):
        self.bus = SMBus(bus)
        self._config = 0x0000  
        self._i2c_addr = addr  
    def begin(self):
        '''
        @fn begin
        @brief Check whether the AS6221 device exists on the IIC bus.
        @return Whether the sensor device is found.
        @retval 0: Sensor device exists, other values: Sensor device does not exist.
        '''
        try:
            self.bus.write_byte(self._i2c_addr, 0)  
            return 0
        except Exception as e:
            print("Init error: {}".format(e))
            return -1

    def _read_register(self, reg, length=2):
        '''
        @fn _read_register
        @brief 读取寄存器函数
        @param reg  寄存器地址 8bits
        @param length 要写入数据的长度
        @return 读取的数据
        '''
        try:
            msg = i2c_msg.write(self._i2c_addr, [reg])
            self.bus.i2c_rdwr(msg)
            read_msg = i2c_msg.read(self._i2c_addr, length)
            self.bus.i2c_rdwr(read_msg)
            return list(read_msg)
        except Exception as e:
            print("Init error: {}".format(e))
            return None

    def _write_register(self, reg, data):
        '''
        @fn _write_register
        @brief 写寄存器函数
        @param reg  寄存器地址 8bits
        @param data 要写入数据的存放缓存
        @return True or False
        '''
        try:
            self.bus.write_i2c_block_data(self._i2c_addr, reg, data)
            return True
        except Exception as e:
            print("Init error: {}".format(e))
            return False

    def get_temperature(self):
        '''
        @fn get_temperature
        @brief  get temperature
        @return temperature ℃
        '''
        data = self._read_register(self.AS6221_ADDR_TVAL)
        if data:
            raw = (data[0] << 8) | data[1]
            if raw & 0x8000: 
                raw -= 0x10000
            return raw * self.AS6221_RESOLUTION
        return None

    def set_high_threshold(self, threshold):
        '''
        @fn set_high_threshold
        @brief  set high threshold
        @return true or false
        '''
        if not (-40 <= threshold <= 100):
            return False
        raw = int(threshold / self.AS6221_RESOLUTION) & 0xFFF0
        return self._write_register(self.AS6221_ADDR_THIGH, [raw >> 8, raw & 0xFF])

    def get_high_threshold(self):
        '''
        @fn get_high_threshold
        @brief  get high threshold
        @return high threshold
        '''
        data = self._read_register(self.AS6221_ADDR_THIGH)
        if data:
            return ((data[0] << 8) | data[1]) * self.AS6221_RESOLUTION
        return None

    def set_low_threshold(self, threshold):
        '''
        @fn set_low_threshold
        @brief  set low threshold
        @return true or false
        '''
        if not (-40 <= threshold <= 100):
            return False
        raw = int(threshold / self.AS6221_RESOLUTION) & 0xFFF0
        return self._write_register(self.AS6221_ADDR_TLOW, [raw >> 8, raw & 0xFF])

    def get_low_threshold(self):
        '''
        @fn getLowThreshold
        @brief  get low threshold
        @return low threshold
        '''
        data = self._read_register(self.AS6221_ADDR_TLOW)
        if data:
            return ((data[0] << 8) | data[1]) * self.AS6221_RESOLUTION
        return None

    def set_config(self, interrupt_mode, polarity=0):
        '''
        @fn set_config
        @brief set 'Interrupt mode' adn 'Polbit'
        @param interrupt_mode
        @n interrupt_mode = 0,The comparator mode is characterized that if the temperature value exceeds the THIGH value,
        @n                   the alert output is changed (e.g. from high to low if the polarity bit is set to 0 and vice versa). 
        @name                alert output stays in that condition until the measured temperature drops below the defined TLOW value.
        @n interrupt_mode = 1,The interrupt mode is characterized that it changes the alert output as soon as the measured emperature crosses the THIGH or TLOW value threshold.
        @param polarity 1:Active high; 0:Active low.the polarity bit configures the polarity of the ALERT output. If the polarity bit is cleared, the ALERT output is low active while it becomes high active if the polarity bit is set to ‘1’.
        @return true or false
        '''
        if interrupt_mode > 1 or polarity > 1:
            return False
        
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if not data:
            return False
            
        config = (data[0] << 8) | data[1]
        config = (config & ~0x0600) | ((interrupt_mode << 9) | (polarity << 10))
        return self._write_register(self.AS6221_ADDR_CONFIG, [config >> 8, config & 0xFF])

    def get_alert(self):
        '''
        @fn get_alert
        @brief get alert,The alarm status is related to the polarity of the setting
        @n polarity=0 , alert=0  Active
        @n polarity=0 , alert=1  No Active
        @n polarity=1 , alert=1  Active
        @n polarity=1 , alert=0  No Active
        @return 0 or 1
        '''
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if data:
            return (data[1] >> 5) & 0x01
        return None

    def set_conversion_rate(self, rate):
        '''
        @fn set_conversion_rate
        @brief set conversion rate
        @param rate
        @n     ConversionRate.e4000ms  = 0.25 Conv/s 
        @n     ConversionRate.e1000ms  = 1 Conv/s 
        @n     ConversionRate.e250ms   = 4 Conv/s 
        @n     ConversionRate.e125ms   = 8 Conv/s 
        '''
        if not (0 <= rate <= 3):
            return False
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if data:
            config = (data[0] << 8) | data[1]
            config = (config & ~0x00C0) | (rate << 6)
            return self._write_register(self.AS6221_ADDR_CONFIG, [config >> 8, config & 0xFF])
        return False

    def set_consecutive_faults(self, consecutive_faults):
        '''
        @fn set_consecutive_faults
        @brief A fault condition persists if the measured temperature either exceeds the configured value in 
        @n     register THIGH or falls below the defined value in register TLOW. As a result, the ALERT pin 
        @n     indicates the fault condition if a defined number of consecutive temperature readings meets 
        @n     this fault condition.
        @param consecutive_faults
        @n     ConsecutiveFaults.eOnce
        @n     ConsecutiveFaults.eTwice
        @n     ConsecutiveFaults.eThreeTimes
        @n     ConsecutiveFaults.eFourTimes
        '''
        if not (0 <= consecutive_faults <= 3):
            return False
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if data:
            config = (data[0] << 8) | data[1]
            config = (config & ~0x1800) | (consecutive_faults << 11)
            return self._write_register(self.AS6221_ADDR_CONFIG, [config >> 8, config & 0xFF])
        return False
    def sleep(self):
        '''
        @fn sleep
        @brief sleep mode
        '''
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if data:
            config = (data[0] << 8) | data[1]
            config |= 0x0100 
            return self._write_register(self.AS6221_ADDR_CONFIG, [config >> 8, config & 0xFF])
        return False

    def wakeup(self):
        '''
        @fn wakeup
        @brief  Wake up the device and start continuous acquisition
        '''
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if data:
            config = (data[0] << 8) | data[1]
            config &= ~0x0100 
            return self._write_register(self.AS6221_ADDR_CONFIG, [config >> 8, config & 0xFF])
        return False
    
    def set_single_shot_conversion(self):
        '''
        @fn set_single_shot_conversion
        @brief set single shot conversion,only sleep mode
        '''
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if not data:
            return False
        config = (data[0] << 8) | data[1]
        config = config | 0x8000
        return self._write_register(self.AS6221_ADDR_CONFIG, [config >> 8, config & 0xFF])

    def is_single_shot_complete(self):
        '''
        @fn is_single_shot_complete
        @brief Determine whether a single acquisition is completed, only in sleep mode
        @return Returns true after the collection is complete, otherwise it returns false
        '''
        data = self._read_register(self.AS6221_ADDR_CONFIG)
        if not data:
            return False
        config = (data[0] << 8) | data[1]
        config = config >> 15
        if config==0:    
            return True
        return False
