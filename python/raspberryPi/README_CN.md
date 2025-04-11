# DFRobot_SFA40

* [English Version](./README.md)
AS6221 IC 是一款高精度数字温度传感器系统，通过 2 线数字总线与其他器件通信。它由一个 Si 带隙温度传感器、一个 ADC 和一个数字信号处理器组成。该传感器专为需要高测量精度的应用而设计，例如测量皮肤温度。除了这些应用外，它还可用于替代 PTC 电阻器。AS6221 具有高温精度和超低功耗（低工作和静态电流）特性，非常适合移动/电池供电应用。AS6221 是一种易于集成和使用的解决方案，具有工厂校准的传感器、集成线性化功能，可使用 8 个不同的 I²C 地址，从而能够在一条总线上使用 8 个 AS6221 器件。此外，AS6221 温度传感器系统具有警报功能，可触发中断等功能，以保护设备免受过热的影响。AS6221 生产测试装置根据 NIST 进行校准，验证设备由 ISO/IEC-17025 认可的实验室进行校准。

![Product Image](../../resources/images/SEN0626svg.png)


## 产品链接（https://www.dfrobot.com.cn/)

  SEN0661 Gravity: SFA40 甲醛传感器

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

要使用这个库，首先将库下载到Raspberry Pi，然后打开用例文件夹。要执行一个用例demox.py，请在命令行中输入python demox.py。
本库依赖smbus库，使用本库前，请保证已经安装了smbus。安装方式：pip install smbus2

## 方法
```python
    def begin(self)
        """
        @fn begin
        @brief 查找IIC总线上是否存在AS6221设备
        @return 是否发现传感器设备
        @retval 0:存在传感器设备，其他值：不存在传感器设备
        """
    def get_temperature(self)
        """
        @fn get_temperature
        @brief 获取温度
        @return 温度数值（单位：℃）
        """
    def set_high_threshold(self, threshold)
        """
        @fn set_high_threshold
        @brief 设置高温报警阈值
        @return 设置成功返回true，不成功返回false
        """
    def get_high_threshold(self)
        """
        @fn get_high_threshold
        @brief 获取高温报警阈值
        @return 高温报警阈值
        """
    def set_low_threshold(self, threshold)
        """
        @fn set_low_threshold
        @brief 设置低温报警阈值
        @return 设置成功返回true，不成功返回false
        """
    def get_low_threshold(self)
        """
        @fn getLowThreshold
        @brief 设置高温报警阈值
        @return 设置成功返回true，不成功返回false
        """
    def set_config(self, interrupt_mode, polarity=0)
        """
        @fn set_config
        @brief 设置Interrupt mode和Polbit
        @param interrupt_mode
        @n interrupt_mode = 0,比较器模式：仅当温度超过高温阈值，警报输出会发生
        @n interrupt_mode = 1,中断模式：只要温度超过高温阈值或者低温阈值，警报
        @param polarity：0:低电平报警 ； 1：高电平报警
        @return 设置成功返回true，不成功返回false
        """
    def get_alert(self)
        """
        @fn get_alert
        @brief 获取警报位
        @return 警报位是0或1
        """
    def set_conversion_rate(self, rate)
        """
        @fn setConversionRate
        @brief 设置采集速率
        @param rate
        @n     ConversionRate.e4000ms  = 0.25 Conv/s 
        @n     ConversionRate.e1000ms  = 1 Conv/s 
        @n     ConversionRate.e250ms   = 4 Conv/s 
        @n     ConversionRate.e125ms   = 8 Conv/s 
        """
    def set_consecutive_faults(self, consecutive_faults)
        """
        @fn setConversionRate
        @brief 设置连续最大故障次数，超过最大故障次数将会报警
        @param consecutive_faults
        @n     ConsecutiveFaults.eOnce
        @n     ConsecutiveFaults.eTwice
        @n     ConsecutiveFaults.eThreeTimes
        @n     ConsecutiveFaults.eFourTimes
        """
    def sleep(self)
        """
        @fn sleep
        @brief 进入睡眠模式
        """
    def wakeup(self)
        """
        @fn wakeup
        @brief 唤醒设备，开始连续采集   
        """
    def set_single_shot_conversion(self):
        """
        @fn set_single_shot_conversion
        @brief 设置单次采集，只在睡眠模式有效
        """
    def is_single_shot_complete(self)
        """
        @fn is_single_shot_complete
        @brief 判断单次采集是否完成，只在睡眠模式有效
        @return 采集完成返回true，否则返回false
        """
```

## 兼容性

| MCU         | Work Well | Work Wrong  | Untested | Remarks |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi4 |  √   |        |        |      |

* Python version 

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |
## 历史 

- 2025/04/10 - Version 1.0.0 released.

## 贡献者

Written by fary(feng.yang@dfrobot.com), 2025.04.10 (Welcome to our [website](https://www.dfrobot.com.cn/))





