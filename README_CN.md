# DFRobot_AS6221

* [English Version](./README.md)

AS6221 IC 是一款高精度数字温度传感器系统，通过 2 线数字总线与其他器件通信。它由一个 Si 带隙温度传感器、一个 ADC 和一个数字信号处理器组成。

该传感器专为需要高测量精度的应用而设计，例如测量皮肤温度。除了这些应用外，它还可用于替代 PTC 电阻器。AS6221 具有高温精度和超低功耗（低工作和静态电流）特性，非常适合移动/电池供电应用。

AS6221 是一种易于集成和使用的解决方案，具有工厂校准的传感器、集成线性化功能，可使用 8 个不同的 I²C 地址，从而能够在一条总线上使用 8 个 AS6221 器件。

此外，AS6221 温度传感器系统具有警报功能，可触发中断等功能，以保护设备免受过热的影响。AS6221 生产测试装置根据 NIST 进行校准，验证设备由 ISO/IEC-17025 认可的实验室进行校准。


![正反面svg效果图](../resources/images/SEN0660.png)

## 产品链接（ https://www.dfrobot.com.cn/ ）

      SEN0660 Gravity: AS6221 皮肤温度传感器

## 目录

* [简介](#简介)
* [安装](#安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [贡献者](#贡献者)

## 简介

本库提供了在Arduino IDE 下驱动AS6221的办法，可在不同工作模式下获取温度。

## 安装

1.要使用此库，首先下载库文件，将其粘贴到 `\Arduino\libraries` 目录中，然后打开示例文件夹并运行其中的示例。

## 方法
```c++
  /**
   * @fn begin
   * @brief 查找IIC总线上是否存在AS6221设备
   * @return 是否发现传感器设备
   * @retval 0:存在传感器设备，其他值：不存在传感器设备
  */ 
  byte begin(void);

  /**
   * @fn getTemperature
   * @brief 获取温度
   * @return 温度数值（单位：℃）
   */
  float getTemperature(void);
  
  /**
   * @fn setHighThreshold
   * @brief 设置高温报警阈值
   * @return 设置成功返回true，不成功返回false
   */
  bool setHighThreshold(float highThreshold);
  
  /**
   * @fn getHighThreshold
   * @brief 获取高温报警阈值
   * @return 高温报警阈值
   */
  float getHighThreshold(void);
  
  /**
   * @fn setLowThreshold
   * @brief 设置低温报警阈值
   * @return 设置成功返回true，不成功返回false
   */
  bool setLowThreshold(float lowThreshold);
  
  /**
   * @fn getLowThreshold
   * @brief 设置高温报警阈值
   * @return 设置成功返回true，不成功返回false
   */
  float getLowThreshold(void);
  
  /**
   * @fn setConfig
   * @brief 设置Interrupt mode和Polbit
   * @param interrputMode
   * @n interrputMode = 0,比较器模式：仅当温度超过高温阈值，警报输出会发生变化
   * @n interrputMode = 1,中断模式：只要温度超过高温阈值或者低温阈值，警报输出电平发生变化
   * @param polarity：0:低电平报警 ； 1：高电平报警
   * @return 设置成功返回true，不成功返回false
  */
  bool setConfig(uint8_t interrputMode,uint8_t polarity=0);
  
  /**
   * @fn setConversionRate
   * @brief 设置采集速率
   * @param conversionRate
   * @n     e4000ms  = 0.25 Conv/s 
   * @n     e1000ms  = 1 Conv/s 
   * @n     e250ms   = 4 Conv/s 
   * @n     e125ms   = 8 Conv/s 
  */  
  void setConversionRate(eConversionRate_t conversionRate );

  /**
   * @fn setConversionRate
   * @brief 设置连续最大故障次数，超过最大故障次数将会报警
   * @param consecutiveFaults
   * @n     eOnce
   * @n     eTwice
   * @n     eThreeTimes
   * @n     eFourTimes
  */  
  void setConsecutiveFaults(eConsecutiveFaults_t consecutiveFaults);

  /**
   * @fn setSingleShotConversion
   * @brief 设置单次采集，只在睡眠模式有效
  */ 
  void setSingleShotConversion()；

  /**
   * @fn IsSingleShotComplete
   * @brief 判断单次采集是否完成
   * @return 采集完成返回true，否则返回false
  */  
  bool IsSingleShotComplete();

  /**
   * @fn wakeup
   * @brief 唤醒设备，开始连续采集
  */   
  void wakeup();

  /**
   * @fn sleep
   * @brief 进入睡眠模式
  */  
  void sleep();

  /**
   * @fn getAlert
   * @brief get alert,报警状态和设置的polarity有关
   * @n polarity=0 , alert=0  Active
   * @n polarity=0 , alert=1  No Active
   * @n polarity=1 , alert=1  Active
   * @n polarity=1 , alert=0  No Active
   * @return 0 or 1
  */
  uint8_t getAlert();
```


## 兼容性

MCU                | 表现良好	|表现异常	|未测试	|备注 |
------------------ | :----------: | :----------: | :---------: | -----
Arduino UNO        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
Micro:bit        |      √       |              |             |




## 历史

- Date 2025-04-10
- Version V1.0.0



## 贡献者

Written by fary(feng.yang@dfrobot.com), 2025.04.11 (Welcome to our [website](https://www.dfrobot.com.cn/))
