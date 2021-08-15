#include "telemetry.h"

Telemetry::Telemetry(std::string name)
{
  ROS_INFO_STREAM(name);
  Connect("/dev/ttyUSB1",115200);

}

Telemetry::~Telemetry()
{
  Disconnect();
}

void Telemetry::Connect(std::string PORT,uint32_t baud){
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
        ROS_INFO_STREAM("Serial Port Telemetry initialized");
        ROS_INFO_STREAM("Reading Data from Serial Port Telemetry :");
    }

  }
  catch(serial::IOException &e){
    ROS_ERROR_STREAM("Error !! Unable to Open Port "+PORT);
  }

}

void Telemetry::Disconnect(void){
    ser.close();
}

void Telemetry::Read_data(void){


  if(ser.available()){

    ser.read(tdata,ser.available());
    if ( (tdata[0]== 0x40) && ( tdata[9] == qCRC16_HIGH(tdata,9) ) && ( tdata[10] == qCRC16_LOW(tdata,9) ) )
    {
      ROS_INFO_STREAM("READ: " <<tdata[1] <<tdata[2] <<tdata[3] <<tdata[4] <<tdata[5] <<tdata[6] <<tdata[7]<<tdata[8]);
    }

  }
}
void Telemetry::Get_Waypoint(){
  if(ser.available()){
    ser.read(waypoint,ser.available());
    if ((waypoint[0]== 0x4A) && ( waypoint[17] == qCRC16_HIGH(waypoint,17) ) && ( waypoint[18] == qCRC16_LOW(waypoint,17) ) )
    {
      arr[0]=waypoint[1];
      arr[1]=waypoint[2];
      arr[2]=waypoint[3];
      arr[3]=waypoint[4];
      arr[4]=waypoint[5];
      arr[5]=waypoint[6];
      arr[6]=waypoint[7];
      arr[7]=waypoint[8];
      byte2double(&lat,arr);
      arr[0]=waypoint[9];
      arr[1]=waypoint[10];
      arr[2]=waypoint[11];
      arr[3]=waypoint[12];
      arr[4]=waypoint[13];
      arr[5]=waypoint[14];
      arr[6]=waypoint[15];
      arr[7]=waypoint[16];
      byte2double(&lon,arr);
      ROS_INFO(" Lat : %.15f",lat);
      ROS_INFO(" Lon : %.15f",lon);

    }


    // ROS_INFO_STREAM("READ Lat: " <<waypoint[0]<<waypoint[1] <<waypoint[2] <<waypoint[3] <<waypoint[4] <<waypoint[5] <<waypoint[6] <<waypoint[7]);
    // ROS_INFO_STREAM("READ Lon: " <<waypoint[8] <<waypoint[9] <<waypoint[10] <<waypoint[11] <<waypoint[12] <<waypoint[13] <<waypoint[14]<<waypoint[15]);    
    // ROS_INFO_STREAM("Lat: "<<lat);
    // ROS_INFO_STREAM("Lon: "<<lon);



  }
}

uint8_t Telemetry::Get_Data(uint8_t k)
{
  return tdata[k];
}
