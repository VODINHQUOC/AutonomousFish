#ifndef USB2CAN_H
#define USB2CAN_H
#include <serial/serial.h>
#include<ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/UInt8.h>
#include <stdint.h>
#include <string.h>
#include "uSerial/uSerial.h"

class Usb2Can: public uSerial
{
public:
  Usb2Can(std::string Info);
  virtual ~Usb2Can();
  void Connect(std::string PORT,uint32_t baud);
  void Disconnect(void);
  void Read_data(void);
  uint8_t Get_Data(uint8_t k);
private:
  uint8_t udata[11]={0};


};

#endif // USB2CAN_H
