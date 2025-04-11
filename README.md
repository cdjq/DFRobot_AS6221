# DFRobot_FM17550

* [中文版](./README_CN.md)

The AS6221 IC is a high accuracy digital temperature sensor system that communicates via a 2-wire digital bus with other devices. It consists of a Si bandgap temperature sensor, an ADC and a digital signal processor.

This sensor is especially designed to be used in applications where a high measurement accuracy is needed, for example measuring the skin temperature. Beside these applications, it can also be used to replace PTC resistors.

The high temperature accuracy and an ultra-low power consumption (low operation and quiescent current) makes the AS6221 ideally suited for mobile/battery powered applications.The AS6221 is an easy to integrate and use solution, featuring a factory-calibrated sensor, integrated linearization and the possibility to use 8 different I²C addresses, enabling to use eight AS6221 devices on one bus.

Additionally, the AS6221 temperature sensor system features an alert functionality, which triggers e.g. an interrupt to protect devices from excessive temperatures.The AS6221 production test setup is calibrated according NIST and the verification equipment is calibrated by an ISO/IEC-17025 accredited laboratory.
   
   
![正反面svg效果图](../resources/images/featured.png)

## Product Link（https://www.dfrobot.com/)
    
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
   * @brief Constructor for the card reader.
   * @param pWire Pointer to the I2C interface (default: Wire).
   * @param addr I2C address of the card reader (default: 0x28).
   */
  DFRobot_FM17550(TwoWire *pWire , uint8_t addr);
    
  /**
   * @brief Initializes the card reader module.
   * @param rstPin Pin number for resetting the module (default: 0).
   * @return Returns 0 on success; otherwise, returns an error code.
   */
  char begin();

  /**
   * @brief Sets the authentication key for communication with the card.
   * @param key Pointer to an array containing the 6-byte key.
   */
  void setKey(uint8_t *key);
  
  /*!
   * @fn scan(String nfcuid)
   * @brief Scan to determine whether there is a NFC smart card/tag with the specified UID.
   * @param nfcuid UID of the NFC card.
   * @return Boolean type, the result of operation
   * @retval true Finds a card with a specific UID
   * @retval false The card with a specific UID was not found
   */
  bool scan(String nfcuid);

  /*!
   * @fn scan(void)
   * @brief Scan to determine whether there is a NFC smart card/tag.
   * @return Boolean type, the result of operation
   * @retval true means find out a MIFARE Classic card.
   * @retval false no card
   */
  bool  scan(void);

  /*!
   * @fn readUid
   * @brief Obtain the UID of the card .
   * @return UID of the card.
   */
  String  readUid();

   /*!
    * @fn readData(int block, uint8_t offset)
    * @brief Read a byte from a specified block of a MIFARE Classic NFC smart card/tag.
    * @param block The number of the block to read from.
    * @param offset The offset of the block.
    * @return A byte read from the card.
    */
  uint8_t readData(uint8_t block, uint8_t offset);

  /*!
   * @fn readData(uint8_t* buffer, uint8_t block)
   * @brief Read a block from a MIFARE Classic NFC smart card/tag (16 bytes each block).
   * @param buffer The buffer of the read data.
   * @param block The number of the block to read from.
   * @return Status code.
   * @retval 1 successfully read data
   * @retval -1 Failed to read data
   */
  String readData(uint8_t block);

  /*!
   * @fn writeData(int block, uint8_t num, uint8_t data)
   * @brief Write a byte to a MIFARE Classic NFC smart card/tag.
   * @param block The number of pages you want to writes the data.
   * @param num The offset of the data.
   * @param data The byte to be written.
   */
  char writeData(uint8_t block, uint8_t num, uint8_t data);

  /*!
   * @fn writeData(int block, uint8_t data[])
   * @brief Write a block to a MIFARE Classic NFC smart card/tag..
   * @param block The number of the block to write to.
   * @param data The buffer of the data to be written.
   */
  char  writeData(uint8_t block, uint8_t data[]);


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

- Date 2025-02-08
- Version V0.1
## Credits
Written by fary(feng.yang@dfrobot.com), 2025.02.08 (Welcome to our [website](https://www.dfrobot.com/))
