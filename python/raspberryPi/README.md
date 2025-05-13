# DFRobot_AS6221

* [中文版](./README_CN.md)

The AS6221 IC is a high accuracy digital temperature sensor system that communicates via a 2-wire digital bus with other devices. It consists of a Si bandgap temperature sensor, an ADC and a digital signal processor.
This sensor is especially designed to be used in applications where a high measurement accuracy is needed, for example measuring the skin temperature. Beside these applications, it can also be used to replace PTC resistors.
The high temperature accuracy and an ultra-low power consumption (low operation and quiescent current) makes the AS6221 ideally suited for mobile/battery powered applications.The AS6221 is an easy to integrate and use solution, featuring a factory-calibrated sensor, integrated linearization and the possibility to use 8 different I²C addresses, enabling to use eight AS6221 devices on one bus.
Additionally, the AS6221 temperature sensor system features an alert functionality, which triggers e.g. an interrupt to protect devices from excessive temperatures.The AS6221 production test setup is calibrated according NIST and the verification equipment is calibrated by an ISO/IEC-17025 accredited laboratory.

![Product Image](../../resources/images/SEN0660.png)

## Product Link（https://www.dfrobot.com/)

      SEN0660 Gravity: AS6221 Skin Temperature Sensor

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

This library provides a way to drive the AS6221 under a Raspberry Pi to obtain formaldehyde, temperature and humidity, and the serial number of the sensor.
## Installation

To use this library, first download the library to your Raspberry Pi and then open the use cases folder. To perform a use case demox.py, enter the python demox.py on the command line.
This library depends on the SMBUS library, please ensure that SMBUS has been installed before using this library. Installation: pip install smbus2

## Methods
```python
  
    def begin(self)
        '''
        @fn begin
        @brief Check whether the AS6221 device exists on the IIC bus.
        @return Whether the sensor device is found.
        @retval 0: Sensor device exists, other values: Sensor device does not exist.
        '''

    def get_temperature(self)
        '''
        @fn get_temperature
        @brief  get temperature
        @return temperature ℃
        '''

    def set_high_threshold(self, threshold)
        '''
        @fn set_high_threshold
        @brief  set high threshold
        @return true or false
        '''

    def get_high_threshold(self):
        '''
        @fn get_high_threshold
        @brief  get high threshold
        @return high threshold
        '''

    def set_low_threshold(self, threshold)
        '''
        @fn set_low_threshold
        @brief  set low threshold
        @return true or false
        '''

    def get_low_threshold(self)
        '''
        @fn getLowThreshold
        @brief  get low threshold
        @return low threshold
        '''

    def set_config(self, interrupt_mode, polarity=0)
        '''
        @fn set_config
        @brief set 'Interrupt mode' adn 'Polbit'
        @param interrupt_mode
        @n interrupt_mode = 0,The comparator mode is characterized that if the temperature value exceeds the THIGH value,
        @n                    the alert output is changed (e.g. from high to low if the polarity bit is set to 0 and vice versa). 
        @n                    alert output stays in that condition until the measured temperature drops below the defined TLOW value.
        @n interrupt_mode = 1,The interrupt mode is characterized that it changes the alert output as soon as the measured emperature crosses the THIGH or TLOW value threshold.
        @param polarity 1:Active high; 0:Active low.the polarity bit configures the polarity of the ALERT output. If the polarity bit is cleared, the ALERT output is low active while it becomes high active if the polarity bit is set to ‘1’.
        @return true or false
        '''

    def get_alert(self)
        '''
        @fn get_alert
        @brief get alert,The alarm status is related to the polarity of the setting
        @n polarity=0 , alert=0  Active
        @n polarity=0 , alert=1  No Active
        @n polarity=1 , alert=1  Active
        @n polarity=1 , alert=0  No Active
        @return 0 or 1
        '''

    def set_conversion_rate(self, rate)
        '''
        @fn set_conversion_rate
        @brief set conversion rate
        @param rate
        @n     ConversionRate.e4000ms  = 0.25 Conv/s 
        @n     ConversionRate.e1000ms  = 1 Conv/s 
        @n     ConversionRate.e250ms   = 4 Conv/s 
        @n     ConversionRate.e125ms   = 8 Conv/s 
        '''

    def set_consecutive_faults(self, consecutive_faults)
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

    def sleep(self)
        '''
        @fn sleep
        @brief sleep mode
        '''

    def wakeup(self)
        '''
        @fn wakeup
        @brief  Wake up the device and start continuous acquisition
        '''
    
    def set_single_shot_conversion(self)
        '''
        @fn set_single_shot_conversion
        @brief set single shot conversion,only sleep mode
        '''

    def is_single_shot_complete(self)
        '''
        @fn is_single_shot_complete
        @brief Determine whether a single acquisition is completed, only in sleep mode
        @return Returns true after the collection is complete, otherwise it returns false
        '''

```

## Compatibility

| MCU         | Work Well | Work Wrong  | Untested | Remarks |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi4 |  √   |        |        |      |

* Python version 

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |
## History 

- 2025/04/10 - Version 1.0.0 released.

## Credits

Written by fary(feng.yang@dfrobot.com), 2025.04.10 (Welcome to our [website](https://www.dfrobot.com/))



