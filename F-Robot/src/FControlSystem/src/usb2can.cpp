#include "usb2can.h"

Usb2Can::Usb2Can(std::string Info)
{
  ROS_INFO_STREAM(Info);
  //Connect("/dev/ttyUSB0",115200);

}
Usb2Can::~Usb2Can()
{
  Disconnect();
}

void Usb2Can::Connect(std::string PORT,uint32_t baud){
  try{
    ser.setPort(PORT);
    ser.setBaudrate(baud);
    ser.setBytesize(serial::eightbits);
    ser.setStopbits(serial::stopbits_one);
    ser.setFlowcontrol(serial::flowcontrol_none);
    ser.setParity(serial::parity_none);

    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    ser.setTimeout(to);
    ser.open();

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port USB2CAN initialized");
        ROS_INFO_STREAM("Reading Data from Serial Port USB2CAN :");
    }

  }
  catch(serial::IOException &e){
    ROS_ERROR_STREAM("Error !! Unable to Open Port "+PORT );
  }

}

void Usb2Can::Disconnect(void){
    ser.close();
}

void Usb2Can::Read_data(void){


  if(ser.available()){

    ser.read(udata,ser.available());
    if ( (udata[0]== 0x40) && ( udata[9] == qCRC16_HIGH(udata,9) ) && ( udata[10] == qCRC16_LOW(udata,9) ) )
    {
      ROS_INFO_STREAM("READ: " <<udata[1] <<udata[2] <<udata[3] <<udata[4] <<udata[5] <<udata[6] <<udata[7]<<udata[8]);
    }

  }// Serial

}//Read_data   1->8
uint8_t Usb2Can::Get_Data(uint8_t k)
{
  return udata[k];
}
