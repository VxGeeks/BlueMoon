#include "photo.h"
#include "init_M00794.h"

typedef char uchar;
typedef unsigned int uint;

void all_screen()
{
    uchar num,num1;
    write_com(0x02);     //Original 0x02
    write_dat(0x01);	//turn ON


    write_com(0x0b);	//Set Diplay Start Address

    write_dat(0x00);	//1st Parameter
    write_dat(0x00);	//2st Parameter

    write_dat(0x00);	//3st Parameter
    write_dat(0x00);	//4st Parameter



    write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<96;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0xff);
			write_dat(0xff);
		}
	}
}

void clear_screen()
{

    uchar num,num1;

    write_com(0x02);     //Original 0x02
    write_dat(0x01);	//turn ON


    write_com(0x0b);	//Set Diplay Start Address

    write_dat(0x00);	//1st Parameter
    write_dat(0x00);	//2st Parameter

    write_dat(0x00);	//3st Parameter
    write_dat(0x00);	//4st Parameter

	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<96;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0);
			write_dat(0);
		}
	}
}
//****************************************红场********************************//
void all_R()
{ 
    uchar num,num1;

    write_com(0x0b);	//Set Diplay Start Address

    write_dat(0x00);	//1st Parameter
    write_dat(0x00);	//2st Parameter

    write_dat(0x00);	//3st Parameter
    write_dat(0x00);	//4st Parameter

	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<96;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0xf8); 
			write_dat(0x00);
		}	
	}	

}
//*****************************************绿场*********************************//
void all_G()
{ 
	uchar num,num1;	
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<96;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0x07); 
			write_dat(0xe0);
		}
	}	
}
//****************************************蓝场***********************************//
void all_B()
{ 
	uchar num,num1;	
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<96;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0x00);
			write_dat(0x1f);
		} 
	}	
}  
//***************************************隔行135************************************//
void row_135()
{
	uchar num,num1;	
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<48;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0xff);
			write_dat(0xff);
		}
		for(num1=0;num1<96;num1++)
		{
			write_dat(0);
			write_dat(0);
		}
	}
}

//****************************************隔行246************************************//
void row_246()
{
	uchar num,num1;	
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<48;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0);
			write_dat(0);
		}
		for(num1=0;num1<96;num1++)
		{
			write_dat(0xff);
			write_dat(0xff);
		}
	}
}

//*********************************隔行147************************************//
void row_147()
{
	uchar num,num1,num2,num3;
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<32;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0xff);
			write_dat(0xff);
		}
		for(num2=0;num2<96;num2++)
		{
			write_dat(0);
			write_dat(0);
		}
		for(num3=0;num3<96;num3++)
		{
			write_dat(0);
			write_dat(0);
		}
		
	}

}

//*********************************隔行258******************************************//
void row_258()
{
	uchar num,num1,num2,num3;
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<32;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0);
			write_dat(0);
		}
		for(num2=0;num2<96;num2++)
		{
			write_dat(0xff);
			write_dat(0xff);
		}
		for(num3=0;num3<96;num3++)
		{
			write_dat(0);
			write_dat(0);
		}
		
	}

}

//********************************隔行369******************************************//
void row_369()

{
	uchar num,num1,num2,num3;
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<32;num++)
	{
		for(num1=0;num1<96;num1++)
		{
			write_dat(0);
			write_dat(0);
		}
		for(num2=0;num2<96;num2++)
		{
			write_dat(0);
			write_dat(0);
		}
		for(num3=0;num3<96;num3++)
		{
			write_dat(0xff);
			write_dat(0xff);
		}
		
	}

}
/**********************************显列1*****************************************/
void column1()

{
	uchar num,num1;
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<96;num++)
	{
		for(num1=0;num1<48;num1++)
		{
			write_dat(0);
			write_dat(0);
			write_dat(0xff);
			write_dat(0xff);
		}
		
	}

}
/**********************************显列2*****************************************/
void column2()

{
	uchar num,num1;
	write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(num=0;num<96;num++)
	{
		for(num1=0;num1<48;num1++)
		{
			write_dat(0xff);
			write_dat(0xff);
			write_dat(0);
			write_dat(0);
		}
		
	}

}
//********************************列扫************************************//

void column_scan()
{
	unsigned int i,j,k; 
	
	write_com(0x0b);	//Set Diplay Start Address

	write_dat(0x00);	//1st Parameter
	write_dat(0x00);	//2st Parameter

	write_dat(0x00);	//3st Parameter
	write_dat(0x00);	//4st Parameter 
	
	for(k=0;k<97;k++)
	{
		write_com(0x0c);	//Read/Write Dot matrix Display Data
		for(i=0;i<96;i++)
		{
			for(j=0;j<96;j++)
			{
				if(j==k)
				{  
					write_dat(0xff);
					write_dat(0xff);
				}
				else
				{
					write_dat(0x00);
					write_dat(0x00);
				}
			}
		}
//		delay_ms(20); 
	
	}
}
//**********************************边框******************************************//
void frame()
{
	uint num0,num1,num2,num3;

	write_com(0x0b);	//Set Diplay Start Address

	write_dat(0x00);	//1st Parameter
	write_dat(0x00);	//2st Parameter

	write_dat(0x00);	//3st Parameter
	write_dat(0x00);	//4st Parameter

	write_com(0x0c);	//Read/Write Dot matrix Display Data

	for(num0=0;num0<96;num0++)
	{
			write_dat(0xff);
			write_dat(0xff);
	}

	for(num1=0;num1<94;num1++)
	{
			write_dat(0xff);
			write_dat(0xff);
	   for(num2=0;num2<94;num2++)
	   {
	   		write_dat(0x00);
	   		write_dat(0x00);
	   }
			write_dat(0xff);
			write_dat(0xff);
	}
	for(num3=0;num3<96;num3++)
	{
			write_dat(0xff);
			write_dat(0xff);
	}



} 
//***********************************美图****************************************//

void img1()						
{
	unsigned int k,j,n=0;	

	write_com(0x0b);	//Set Diplay Start Address

	write_dat(0x00);	//1st Parameter
	write_dat(0x00);	//2st Parameter

	write_dat(0x00);	//3st Parameter
	write_dat(0x00);	//4st Parameter

    write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(k=0;k<32;k++)
	{
		for(j=0;j<96;j++)
		{
			write_dat(0x00);
			write_dat(0x00);
		}			
	}
	for(k=0;k<32;k++)
	{
		for(j=0;j<96;j++)
		{
			write_dat(logo1[n]);
			write_dat(logo1[n+1]);
			n=n+2;	
		}		
	}
	
			
	for(k=0;k<32;k++)
	{
		for(j=0;j<96;j++)
		{
			write_dat(0x00);
			write_dat(0x00);
		}			
	}	
}

void img2()						
{
	unsigned int k,n=0;	
	write_com(0x0b);	//Set Diplay Start Address

	write_dat(0x00);	//1st Parameter
	write_dat(0x00);	//2st Parameter

	write_dat(0x00);	//3st Parameter
	write_dat(0x00);	//4st Parameter

    write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(k=0;k<9216;k++)
		{	write_dat(logo2[n]);
			write_dat(logo2[n+1]);
			n=n+2;
	}	
}

void img3()						
{
	unsigned int k,n=0;	
	write_com(0x0b);	//Set Diplay Start Address

	write_dat(0x00);	//1st Parameter
	write_dat(0x00);	//2st Parameter

	write_dat(0x00);	//3st Parameter
	write_dat(0x00);	//4st Parameter

    write_com(0x0c);	//Read/Write Dot matrix Display Data
	for(k=0;k<9216;k++)
		{	write_dat(logo3[n]);
			write_dat(logo3[n+1]);
			n=n+2;
	}	
}
