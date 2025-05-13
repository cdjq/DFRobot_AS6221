/*!
 * @file DFRobot_AS6221.h
 * @brief DFRobot_AS6221 class infrastructure
 * @copyright	Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-11
 * @url https://github.com/DFRobot/DFRobot_AS6221
 */
#ifndef _DFROBOT_AS6221_H_
#define _DFROBOT_AS6221_H_

#include <Arduino.h>
#include <Wire.h>

#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define AS6221_ADDR_TVAL      0 
#define AS6221_ADDR_CONFIG    1 
#define AS6221_ADDR_TLOW      2 
#define AS6221_ADDR_THIGH     3 
#define AS6221_RESOLUTION     0.0078125

typedef struct {
  uint8_t   interrputMode: 1;
  uint8_t   polarity:1;
  uint8_t   reserved:6;
} __attribute__ ((packed)) sMode_t;

class DFRobot_AS6221
{
public:

  /**
   * @struct sConfig_t
   * @brief Configuration register
   * @n --------------------------------------------------------------------------------------------------------------------------------
   * @n |     B15    |   b13-b14    |     b11-b12     |    b10    |       b9      |     b8    |      b6-b7     |    b5   |    b0-b4    |
   * @n --------------------------------------------------------------------------------------------------------------------------------
   * @n | singleShot |   reserved   |consecutiveFaults |  polarity | InterrputMode | sleepMode | conversionRate |  alert  |   reserved  |
   * @n --------------------------------------------------------------------------------------------------------------------------------
  */
  typedef struct {
	  uint8_t   reserved: 5;
    uint8_t   alert: 1; /**< The alert bit can be used to easily compare the current temperature reading to the thresholds that can be set in the TLOW and THIGH registers */
                        /**< If the polarity bit is set to 0, the AL bit is read as 1 until the converted temperature value  */
                        /**< exceeds the defined value in the high temperature threshold register THIGH for the number of  */ 
                        /**< defined consecutive faults (bits CF). Such an event causes the AL bit to toggle to 0 and the  */
                        /**< value is kept until the converted temperature value falls below the defined value in the low  */
                        /**< temperature threshold register TLOW for the number of defined consecutive faults. If this condition is met, the AL bit is reset to 1.*/
    uint8_t   conversionRate: 2; /**< The conversion rate bits define the number of executed temperature conversions per time unit. */   
                                 /**< Additional readouts of the temperature register between conversions are possible but not */
                                 /**< recommended because the value is changed only after a conversion is finished.*/
                                 /**< Values of 125 ms, 250 ms, 1 s and 4 s for a conversion can be configured while the default */
                                 /**< rate is set to 4 conversions per second.*/
    uint8_t   sleepMode: 1; /**< The sleep mode is activated by setting the bit SM in the configuration register to 1. This shuts  */
                            /**< the device down immediately and reduces the power consumption to a minimum value. */
                            /**< The serial interface is the only active circuitry in the sleep mode in order to provide access to the digital registers. */
                            /**< After resetting the SM bit to 0, the device enters the continuous conversion mode */
    uint8_t   interrputMode: 1; /**< The interrupt mode bit defines whether the device operates in the temperature comparator  */
                                /**< mode or the interrupt mode. This defines the operation of the ALERT output as described in the polarity section bit.*/
                                /**< The comparator mode is characterized that if the temperature value exceeds the THIGH value,   */
                                /**< the alert output is changed (e.g. from high to low if the polarity bit is set to 0 and vice versa).   */
                                /**< The alert output stays in that condition until the measured temperature drops below the defined TLOW value.  */
                                /**< The interrupt mode is characterized that it changes the alert output as soon as the measured temperature crosses the THIGH or TLOW value threshold.  */
                                /**< The alert bit has the same setting as the alert output if the device is set to comparator mode.  */
    uint8_t   polarity:1; /**< The polarity bit configures the polarity of the ALERT output. If the polarity bit is cleared, the  */
                          /**< ALERT output is low active while it becomes high active if the polarity bit is set to ‘1’. */
	  uint8_t   consecutiveFaults:2; /**< A fault condition persists if the measured temperature either exceeds the configured value in  */
                                   /**< register THIGH or falls below the defined value in register TLOW. As a result, the ALERT pin  */
                                   /**< indicates the fault condition if a defined number of consecutive temperature readings meets  */
                                   /**< this fault condition. The number of consecutive faults are defined with two bits (12 and 11) and  */
                                   /**< prevent a false alert if environmental temperature noise is present */
	  uint8_t   reserved1:2;
	  uint8_t   singleShot:1; /**< The device features a single shot measurement mode if the device is in sleep mode (SM=1).  */
                            /**< By setting the “Single Shot-bit” to 1, a single temperature conversion is started and the SS-bit  */
                            /**< can be read as 1 during the active conversion operation. Once the conversion is completed,  */
                            /**< the device enters the sleep mode again and the SS-bit is set to 0. The single shot conversion  */
                            /**< allows very low power consumption since a temperature conversion is executed on demand  */
                            /**< only. This allows a user defined timing of the temperature conversions to be executed and is  */
                            /**< used if the consecutive operation mode is not required. */

	} __attribute__ ((packed)) sConfig_t;


  /**
   * @enum eConversionRate_t
   * @brief The conversion rate bits define the number of executed temperature conversions per time unit.
   * @n     Additional readouts of the temperature register between conversions are possible but not
   * @n     recommended because the value is changed only after a conversion is finished.
   * @n     Values of 125 ms, 250 ms, 1 s and 4 s for a conversion can be configured while the default rate is set to 4 conversions per second.
  */
  typedef enum{
    e4000ms = 0, /**< 0.25 Conv/s */
    e1000ms,     /**< 1 Conv/s */
    e250ms,      /**< 4 Conv/s */
    e125ms,      /**< 8 Conv/s */
  }eConversionRate_t;
  
  /**
   * @enum  eConversionFaults_t
   * @brief A fault condition persists if the measured temperature either exceeds the configured value in register THIGH or falls below the defined value in register TLOW. 
   * @n     As a result, the ALERT pin indicates the fault condition if a defined number of consecutive temperature readings meets this fault condition.
   * @n     The number of consecutive faults are defined with two bits (12 and 11) and prevent a false alert if environmental temperature noise is present.
  */
  typedef enum{
    eOnce = 0,  
    eTwice, 
	  eThreeTimes,
	  eFourTimes
  }eConsecutiveFaults_t;
private:
  TwoWire *_pWire;
  uint8_t _deviceAddr;  

public:

  /**
   * @fn DFRobot_AS6221
   * @brief Constructor
   * @param addr device address
   * @param pWire device bus
   * @return None
  */
  DFRobot_AS6221(uint8_t addr, TwoWire *pWire = &Wire){
    _pWire=pWire;
    _deviceAddr=addr;
  }

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

protected:
  /**
   * @fn getConfig
   * @brief Get the settings for Interrupt mode and Polbit
   * @return the settings for Interrupt mode and Polbit
  */
  sMode_t getConfig();

  /** 
   * @fn writeReg
   * @brief write register
   * @param reg register address 8bits
   * @param pBuf to write data to the storage cache
   * @param size The length of the data to be written
   * @return None
  */
  void writeReg(uint8_t reg, void* pBuf, size_t size);

  /**
   * @fn readReg
   * @brief read register function
   * @param reg register address 8bits
   * @param pBuf to write data to the storage cache
   * @param size The length of the data to be written
   * @return uint8_t type, which indicates the return of the read register
   * @retval -1: A null pointer was passed, 0: IIC communication failed, and a non-negative integer greater than zero: the byte length read
  */
  uint8_t readReg(uint8_t reg, void* pBuf, size_t size);

};

#endif