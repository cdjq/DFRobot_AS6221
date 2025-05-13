# DFRobot_AS6221

* [中文版](./README_CN.md)

The AS6221 IC is a high accuracy digital temperature sensor system that communicates via a 2-wire digital bus with other devices. It consists of a Si bandgap temperature sensor, an ADC and a digital signal processor.

This sensor is especially designed to be used in applications where a high measurement accuracy is needed, for example measuring the skin temperature. Beside these applications, it can also be used to replace PTC resistors.

The high temperature accuracy and an ultra-low power consumption (low operation and quiescent current) makes the AS6221 ideally suited for mobile/battery powered applications.The AS6221 is an easy to integrate and use solution, featuring a factory-calibrated sensor, integrated linearization and the possibility to use 8 different I²C addresses, enabling to use eight AS6221 devices on one bus.

Additionally, the AS6221 temperature sensor system features an alert functionality, which triggers e.g. an interrupt to protect devices from excessive temperatures.The AS6221 production test setup is calibrated according NIST and the verification equipment is calibrated by an ISO/IEC-17025 accredited laboratory.
   
   
![正反面svg效果图](../resources/images/SEN0660.png)

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

This library provides a way to drive the AS6221 under the Arduino IDE, allowing temperature acquisition in different operating modes.

## Installation

1.To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo 
## Methods
```C++

  /**
   * @fn DFRobot_AS6221
   * @brief Constructor
   * @param addr device address
   * @param pWire device bus
   * @return None
  */
  DFRobot_AS6221(uint8_t addr, TwoWire *pWire = &Wire);

  /**
   * @fn begin
   * @brief Check whether the AS6221 device exists on the IIC bus.
   * @return Whether the sensor device is found.
   * @retval 0: Sensor device exists, other values: Sensor device does not exist.
  */
  byte begin(void);

  /**
   * @fn getTemperature
   * @brief  get temperature
   * @return temperature（℃）
   */
  float getTemperature(void);
  
  /**
   * @fn setHighThreshold
   * @brief  set high threshold
   * @return true or false
   */
  bool setHighThreshold(float highThreshold);
  
  /**
   * @fn getHighThreshold
   * @brief  get high threshold
   * @return high threshold
   */
  float getHighThreshold(void);
  
  /**
   * @fn setLowThreshold
   * @brief  set low threshold
   * @return true or false
  */
  bool setLowThreshold(float lowThreshold);
  
  /**
   * @fn getLowThreshold
   * @brief  get low threshold
   * @return low threshold
  */
  float getLowThreshold(void);
  
  /**
   * @fn setConfig
   * @brief set 'Interrupt mode' adn 'Polbit'
   * @param interrputMode
   * @n interrputMode = 0,The comparator mode is characterized that if the temperature value exceeds the THIGH value,
   * @n                   the alert output is changed (e.g. from high to low if the polarity bit is set to 0 and vice versa). 
   * @n                   alert output stays in that condition until the measured temperature drops below the defined TLOW value.
   * @n interrputMode = 1,The interrupt mode is characterized that it changes the alert output as soon as the measured emperature crosses the THIGH or TLOW value threshold.
   * @param polarity 1:Active high; 0:Active low.the polarity bit configures the polarity of the ALERT output. If the polarity bit is cleared, the ALERT output is low active while it becomes high active if the polarity bit is set to ‘1’.
   * @return true or false
  */
  bool setConfig(uint8_t interrputMode,uint8_t polarity=0);
  
  /**
   * @fn setConversionRate
   * @brief set conversionRate
   * @param conversionRate
   * @n     e4000ms  = 0.25 Conv/s 
   * @n     e1000ms  = 1 Conv/s 
   * @n     e250ms   = 4 Conv/s 
   * @n     e125ms   = 8 Conv/s 
  */  
  void setConversionRate(eConversionRate_t conversionRate );

  /**
   * @fn setConsecutiveFaults
   * @brief A fault condition persists if the measured temperature either exceeds the configured value in 
   * @n     register THIGH or falls below the defined value in register TLOW. As a result, the ALERT pin 
   * @n     indicates the fault condition if a defined number of consecutive temperature readings meets 
   * @n     this fault condition.
   * @param consecutiveFaults
   * @n     eOnce
   * @n     eTwice
   * @n     eThreeTimes
   * @n     eFourTimes
  */  
  void setConsecutiveFaults(eConsecutiveFaults_t consecutiveFaults);

  /**
   * @fn setSingleShotConversion
   * @brief set single shot conversion,only sleep mode
  */ 
  void setSingleShotConversion();

  /**
   * @fn IsSingleShotComplete
   * @brief Determine whether a single acquisition is completed, only in sleep mode
   * @return Returns true after the collection is complete, otherwise it returns false
  */  
  bool IsSingleShotComplete();

  /**
   * @fn wakeup
   * @brief Wake up the device and start continuous acquisition
  */   
  void wakeup();

  /**
   * @fn sleep
   * @brief sleep mode
  */  
  void sleep();

  /**
   * @fn getAlert
   * @brief get alert,The alarm status is related to the polarity of the setting
   * @n polarity=0 , alert=0  Active
   * @n polarity=0 , alert=1  No Active
   * @n polarity=1 , alert=1  Active
   * @n polarity=1 , alert=0  No Active
   * @return 0 or 1
  */
  uint8_t getAlert();

```

## Compatibility

MCU                | 表现良好	|表现异常	|未测试	|备注 |
------------------ | :----------: | :----------: | :---------: | -----
Arduino UNO        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
Micro:bit        |      √       |              |             |


## History

- Date 2025-04-10
- Version V0.1
## Credits
Written by fary(feng.yang@dfrobot.com), 2025.02.08 (Welcome to our [website](https://www.dfrobot.com/))
