#ifndef TELEMETRY_H
#define TELEMETRY_H


#include <serial/serial.h>
#include<ros/ros.h>
#include <stdint.h>
#include <string.h>
#include "uSerial/uSerial.h"

class Telemetry: public uSerial
{
public:
  Telemetry(std::string name);
  virtual ~Telemetry();
  void Connect(std::string PORT,uint32_t baud);
  void Disconnect(void);
  void Read_data(void);
  uint8_t Get_Data(uint8_t k);
  void Get_Waypoint();

  private:
  uint8_t tdata[11]={0};
  uint8_t waypoint[19]={0};
  uint8_t arr[8]={0};
  double lat=0,lon=0;


};

#endif // TELEMETRY_H
