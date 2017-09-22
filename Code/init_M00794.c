#define uchar unsigned char
#define uint unsigned int

#include <stdio.h>
#include <stdint.h>

#include <wiringPi.h>
#include "IO.h"
#include "Delay.h"

/*
sbit RES=P1^0;
sbit CS=P1^1;
sbit DC=P1^2;

sbit k1=P1^6;
sbit k2=P1^7;
sbit POWER_LED=P2^0;
sbit AUTO_LED=P2^1;
sbit TEST_LED=P2^2;

sbit VCC=P3^4;

*/
/*
void delay_ms(uint z)
{
	uint x,y;
	for(x=100;x>0;x--)
		for(y=z;y>0;y--);
}
*/



void writeDisplayData(char data)
{

    (data & 0x01) ? (digitalWrite(D0,HIGH)):(digitalWrite(D0, LOW));
    (data & 0x02) ? (digitalWrite(D1,HIGH)):(digitalWrite(D1, LOW));
    (data & 0x04) ? (digitalWrite(D2,HIGH)):(digitalWrite(D2, LOW));
    (data & 0x08) ? (digitalWrite(D3,HIGH)):(digitalWrite(D3, LOW));
    (data & 0x10) ? (digitalWrite(D4,HIGH)):(digitalWrite(D4, LOW));
    (data & 0x20) ? (digitalWrite(D5,HIGH)):(digitalWrite(D5, LOW));
    (data & 0x40) ? (digitalWrite(D6,HIGH)):(digitalWrite(D6, LOW));
    (data & 0x80) ? (digitalWrite(D7,HIGH)):(digitalWrite(D7, LOW));


}



void write_com(uchar com)
{

    digitalWrite (A0_PIN, LOW);
    digitalWrite (CSB_PIN, LOW);

    writeDisplayData(com);

    delayMicroseconds(1);
    digitalWrite (WRB_PIN, LOW);
    digitalWrite (WRB_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite (CSB_PIN, HIGH);


    /*
    CS=0;
    DC=0;
	WR=0;
	P0=com;
	WR=1;
    CS=1;*/
}
void write_dat(uchar dat)
{	

    digitalWrite (A0_PIN, HIGH);
    digitalWrite (CSB_PIN, LOW);
    digitalWrite (WRB_PIN, LOW);

    writeDisplayData(dat);

    delayMicroseconds(1);

    digitalWrite (WRB_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite (CSB_PIN, HIGH);

    /*CS=0;
	DC=1;
	WR=0;
	P0=dat;
	WR=1;
    CS=1;*/
}

void read

void setup_DisplayIO()
{

    pinMode (RSTB_PIN, OUTPUT) ;
    digitalWrite (RSTB_PIN, HIGH);

    pinMode (RDB_PIN, OUTPUT) ;
    digitalWrite (RDB_PIN, HIGH);

    pinMode (WRB_PIN, OUTPUT) ;
    digitalWrite (WRB_PIN, HIGH);

    pinMode (CSB_PIN, OUTPUT) ;
    digitalWrite (CSB_PIN, HIGH);


    pinMode (A0_PIN, OUTPUT) ;
    digitalWrite (A0_PIN, LOW);

    pinMode (SWVIEN_PIN, OUTPUT) ;
    digitalWrite (SWVIEN_PIN, LOW);

    pinMode (SWCE_PIN, OUTPUT) ;
    digitalWrite (SWCE_PIN, LOW);


    pinMode (D0, OUTPUT) ;
    digitalWrite (D0, LOW);

    pinMode (D1, OUTPUT) ;
    digitalWrite (D1, LOW);

    pinMode (D2, OUTPUT) ;
    digitalWrite (D2, LOW);

    pinMode (D3, OUTPUT) ;
    digitalWrite (D3, LOW);

    pinMode (D4, OUTPUT) ;
    digitalWrite (D4, LOW);

    pinMode (D5, OUTPUT) ;
    digitalWrite (D5, LOW);

    pinMode (D6, OUTPUT) ;
    digitalWrite (D6, LOW);

    pinMode (D7, OUTPUT) ;
    digitalWrite (D7, LOW);



}

void init_LD7134()
{

    digitalWrite (SWVIEN_PIN, HIGH);
    digitalWrite (SWCE_PIN, HIGH);
    Delay_Ms(100);

    digitalWrite (CSB_PIN, HIGH);
    digitalWrite (A0_PIN, HIGH);
    digitalWrite (WRB_PIN, HIGH);

    digitalWrite (RSTB_PIN, LOW);
    Delay_Ms(50);
    digitalWrite (RSTB_PIN, HIGH);

    /*
    CS=0;
	RES=0;
	delay_ms(50);
    RES=1;*/

	write_com(0x02);
	write_dat(0x00);	//turn OFF

	write_com(0x01); 	//software reset The OSC.is stopped.

	write_com(0x03);
	write_dat(0x00);	//Ste Dot Matrix Display Stand-by OFF 	

	write_com(0x04);	//Set OSC Control
	write_dat(0x03);	//105Hz

	write_com(0x05);	//Set Graphic RAM Writing Direction
    write_dat(0x03);	//RGB	0x08 BGR         original 0x01       //03

	write_com(0x06);	//Set Row Scan Direction
    write_dat(0x00);    //0x01..0x00

	write_com(0x07);	//Set Diplay Size

	write_dat(0x00);	//X start 1
	write_dat(0x00);	//X start 2

	write_dat(0x04);	//X end 1
    write_dat(0x1f);	//X end 2

	write_dat(0x00);	//Y start 1
	write_dat(0x00);	//Y start 2

	write_dat(0x05);	//Y end 1
	write_dat(0x0f);	//Y end 2

	write_com(0x08);	//Set Interface Bus Type
	write_dat(0x01);	//8Bit I/F Bus	

	write_com(0x09);	//Set Masking Data
    write_dat(0x07);	//Data AND Palette(R,G,B) -->Output Data

	write_com(0x0a);	//Set Read/Write Box Data

	write_dat(0x00);	//X start 1
	write_dat(0x00);	//X start 2

	write_dat(0x05);	//X end 1
	write_dat(0x0f);	//X end 2

	write_dat(0x00);	//Y start 1
	write_dat(0x00);	//Y start 2

	write_dat(0x05);	//Y end 1
	write_dat(0x0f);	//Y end 2

    write_com(0x0b);	//Set Display Start Address

	write_dat(0x00);	//1st Parameter
	write_dat(0x00);	//2st Parameter

	write_dat(0x00);	//3st Parameter
	write_dat(0x00);	//4st Parameter
	
	write_com(0x0e);	//Set Dot Matrix Current Level

	write_dat(0x03);	//1st Paramenter 	R[7:4]
	write_dat(0x0f);	//2st Paramenter	R[3:0]

	write_dat(0x02);	//3st Paramenter	G[7:4]
	write_dat(0x04);	//4st Paramenter 	G[3:0]

	write_dat(0x03);	//5st Paramenter	B[7:4]
	write_dat(0x08);	//6st Paramenter	B[3:0]

	write_com(0x0f);	//Set Dot Matrix Peak Current Level

	write_dat(0x0a);	//PR[5:0]	16uA Step
	write_dat(0x0a);	//PG[5:0]	16uA Step
	write_dat(0x0a);	//PB[5:0]	16uA Step

    write_com(0x1c);	//Set Pre-Charge Width
	write_dat(0x08);	//0x08	//Parameter Range :01h-3fh

    write_com(0x1d);	//Set Peak Pulse Width;Parameter Range :01h-3fh

//	write_dat(0x00);	//for Red
//	write_dat(0x00);	//for Green
//	write_dat(0x00);	//for Blue
    write_dat(0x0F);	//for Red
    write_dat(0x0F);	//for Green
    write_dat(0x0F);	//for Blue

    write_com(0x1e);	//Set Peak Pulse Delay
	write_dat(0x05);	//01h-0fh

    write_com(0x1f);	//Set Row Scan Operation
    write_dat(0x10);    //0x00..0x10

    write_com(0x30);	//Set Internal Regulator for Row Scan
    write_dat(0x10);	//VCC_R =0.85 VCC_C

    write_com(0x3b);	//Set Gamma Correction Table Initialize

    write_com(0x3c);	//Set VDD Selection
	write_dat(0x00);	//VDD=2.8V; 0x01:VDD=1.8V
	
    write_com(0x3d);	//Set DMODE Selection
    write_dat(0x00);	//Resolution=96*96,65k Color

	
    write_com(0x02);     //Original 0x02
    write_dat(0x01);	//turn ON

}
