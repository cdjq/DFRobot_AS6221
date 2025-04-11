#include "DFRobot_AS6221.h"


byte DFRobot_AS6221::begin(void){
  _pWire->begin();
  _pWire->beginTransmission(_deviceAddr);
  return _pWire->endTransmission();
}
void DFRobot_AS6221::wakeup(){
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  config.sleepMode=0;
  writeReg(AS6221_ADDR_CONFIG,(void *)&config,2);
}
void DFRobot_AS6221::sleep(){
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  config.sleepMode=1;
  writeReg(AS6221_ADDR_CONFIG,(void *)&config,2);
}
float DFRobot_AS6221::getTemperature(void){
  int16_t  data;
  readReg(AS6221_ADDR_TVAL,(void *)&data,2);
  float temperature= data*AS6221_RESOLUTION;
  return temperature;	
}
bool DFRobot_AS6221::setHighThreshold(float highThreshold){
  if((highThreshold>100) || (highThreshold<(-40))){
    return false;
  }
  int16_t data = highThreshold / AS6221_RESOLUTION;
  data &= 0xFFF0;
  writeReg(AS6221_ADDR_THIGH,(void *)&data,2);	
  return true;
}
float DFRobot_AS6221::getHighThreshold(void){
  uint16_t data;
  readReg(AS6221_ADDR_THIGH,(void *)&data,2);
  float highThreshold= data * AS6221_RESOLUTION;
  return highThreshold;
}
bool DFRobot_AS6221::setLowThreshold(float lowThreshold){
  if((lowThreshold>100) || (lowThreshold<(-40))){
    return false;
  }
  int16_t data =lowThreshold / AS6221_RESOLUTION;
  data &= 0xFFF0;
  writeReg(AS6221_ADDR_TLOW,(void *)&data,2);
  return true;
}
float DFRobot_AS6221::getLowThreshold(void){
  uint16_t data;
  readReg(AS6221_ADDR_TLOW,(void *)&data,2);
  float lowThreshold= data*AS6221_RESOLUTION;
  return lowThreshold;
}
bool DFRobot_AS6221::setConfig(uint8_t interrputMode,uint8_t polarity){
  if((interrputMode > 1) || (polarity > 1)){
    return false;
  }
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  config.interrputMode=interrputMode;
  config.polarity=polarity;
  writeReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  return true;
}
sMode_t DFRobot_AS6221::getConfig(){
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  sMode_t mode;
  mode.interrputMode=config.interrputMode;
  mode.polarity = config.polarity;
  return mode;
}
uint8_t DFRobot_AS6221::getAlert(){
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  return config.alert;
}

void DFRobot_AS6221::setConversionRate(eConversionRate_t conversionRate ){
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  config.conversionRate=conversionRate;
  writeReg(AS6221_ADDR_CONFIG,(void *)&config,2);
}
void DFRobot_AS6221::setConsecutiveFaults(eConsecutiveFaults_t consecutiveFaults){
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  config.consecutiveFaults=consecutiveFaults;
  writeReg(AS6221_ADDR_CONFIG,(void *)&config,2);
}
void DFRobot_AS6221::setSingleShotConversion(){
  sConfig_t config;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  config.singleShot=1;
  writeReg(AS6221_ADDR_CONFIG,(void *)&config,2);
}
bool DFRobot_AS6221::IsSingleShotComplete(){
  sConfig_t config;
  config.singleShot=1;
  readReg(AS6221_ADDR_CONFIG,(void *)&config,2);
  if(config.singleShot==0){
    return true;
  }
  return false;
}
void DFRobot_AS6221::writeReg(uint8_t reg, void* pBuf, size_t size){
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  
  for(int i = size; i >0; i--){
    _pWire->write(_pBuf[i-1]);
  }
  _pWire->endTransmission();
}
uint8_t DFRobot_AS6221::readReg(uint8_t reg, void* pBuf, size_t size){
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  if( _pWire->endTransmission() != 0){
    return 0;
  }
  _pWire->requestFrom(_deviceAddr, (uint8_t) size);
  for(int i = size; i >0; i--){
    _pBuf[i-1] = _pWire->read();
  }
  return size;
}

