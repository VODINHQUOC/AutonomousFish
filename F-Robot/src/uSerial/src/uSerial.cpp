#include "uSerial/uSerial.h"

uSerial::uSerial() {

}

uSerial::~uSerial() {

}
void uSerial::Connect(std::string PORT,uint32_t baud)
{

}
void uSerial::Read_data(void)
{

}

void uSerial::Disconnect(void)
{

}
void uSerial::double2byte(double double_input,uint8_t* data_out)
{
	union u_double2byte{
		double value_double;
		uint8_t data[8];
	};
	union u_double2byte t;
	t.value_double = double_input;
	data_out[0]= t.data[0];
	data_out[1]= t.data[1];
	data_out[2]= t.data[2];
	data_out[3]= t.data[3];
	data_out[4]= t.data[4];
	data_out[5]= t.data[5];
	data_out[6]= t.data[6];
	data_out[7]= t.data[7];

}
void uSerial::byte2double(double *doubleout,uint8_t* datain)
{
	union u_byte2double{
		double value_double;
		uint8_t data[8];
	};
	union u_byte2double t;
	t.data[0]=datain[0];
	t.data[1]=datain[1];
	t.data[2]=datain[2];
	t.data[3]=datain[3];
	t.data[4]=datain[4];
	t.data[5]=datain[5];
	t.data[6]=datain[6];
	t.data[7]=datain[7];
	*doubleout=t.value_double;

}
uint8_t uSerial::qCRC16_HIGH( uint8_t * pucFrame, uint8_t usLen )
{
    uint8_t ucCRCHi = 0xFF;
    uint8_t ucCRCLo = 0xFF;
    int iIndex;

    while( usLen-- )
    {
      iIndex = ucCRCLo ^ *( pucFrame++ );
      ucCRCLo = static_cast<uint8_t>( ucCRCHi ^ static_cast<uint8_t>(aucCRCHi[iIndex]) );
      ucCRCHi = static_cast<uint8_t>(aucCRCLo[iIndex]);
    }
    return static_cast<uint8_t>(ucCRCHi);
}
uint8_t uSerial::qCRC16_LOW( uint8_t * pucFrame, uint8_t usLen )
{
    uint8_t ucCRCHi = 0xFF;
    uint8_t ucCRCLo = 0xFF;
    int iIndex;

    while( usLen-- )
    {
    iIndex = ucCRCLo ^ *( pucFrame++ );
    ucCRCLo = static_cast<uint8_t>( ucCRCHi ^ static_cast<uint8_t>(aucCRCHi[iIndex]) );
    ucCRCHi = static_cast<uint8_t>(aucCRCLo[iIndex]);
    }
    return static_cast<uint8_t>(ucCRCLo);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "uSerial");
  ROS_INFO("Serial CLass !");

}

