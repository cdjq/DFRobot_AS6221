# DFRobot_SFA40

* [中文版](./README_CN.md)

The AS6221 IC is a high accuracy digital temperature sensor system that communicates via a 2-wire digital bus with other devices. It consists of a Si bandgap temperature sensor, an ADC and a digital signal processor.
This sensor is especially designed to be used in applications where a high measurement accuracy is needed, for example measuring the skin temperature. Beside these applications, it can also be used to replace PTC resistors.
The high temperature accuracy and an ultra-low power consumption (low operation and quiescent current) makes the AS6221 ideally suited for mobile/battery powered applications.The AS6221 is an easy to integrate and use solution, featuring a factory-calibrated sensor, integrated linearization and the possibility to use 8 different I²C addresses, enabling to use eight AS6221 devices on one bus.
Additionally, the AS6221 temperature sensor system features an alert functionality, which triggers e.g. an interrupt to protect devices from excessive temperatures.The AS6221 production test setup is calibrated according NIST and the verification equipment is calibrated by an ISO/IEC-17025 accredited laboratory.

![Product Image](../../resources/images/SEN0660svg.png)

## Product Link（https://www.dfrobot.com/)
      SEN0661 Gravity: SFA40 HCHO Sensor

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
        """
        @fn begin
        @brief Check whether the SFA40 device exists on the IIC bus.
        @return Whether the sensor device is found.
        @retval 0: Sensor device exists, -1: Sensor device does not exist.
        """
    def start_measurement(self)
        """
        @fn start_measurement
        @brief start measurement
        """
    def stop_measurement(self)
        """
        @fn stop_measurement
        @brief stop measurement
        """
    def read_measurement_data_raw(self)
        """
        @fn read_measurement_data_raw
        @brief read measurement data
        @return int(0-2)
        @retval 0:The sensor is ready and the data is reliable! 
        @retval 1:The sensor is not ready!
        @retval 2:Sensor is not up to specification!
        """
    def get_serial_number(self)
        """
        @fn get_serial_number
        @brief get serial number
        @return serial number
        """

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

- 2025/03/17 - Version 1.0.0 released.

## Credits

Written by fary(feng.yang@dfrobot.com), 2025.04.10 (Welcome to our [website](https://www.dfrobot.com/))



