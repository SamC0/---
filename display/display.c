#include "main.h"

void Display1(unsigned char *D)
{
	int D_length=0;
	int i=0;
	int k=0;
	int Num;
	int y_start_c;
	int start;
	int end;
	y_start_c=192;
	start=y_start_c;
	D_length=D[1];
	for (i=2;i<D_length*2+2;i=i+2)
	{
		Num=(D[i]-0xa0)*255+D[i+1];
		if(k==0)
		{
		EPD_init_Part();
		driver_delay_xms(200);
		EPD_Dis_Part(0,128-1,0,250-1,(unsigned char *)Image,1); //pic
		driver_delay_xms(200);
		k=k+1;
		}
		if(Num>=0&&Num<=74)
		{
			start=start-8;
			end=start+7;
			EPD_Dis_Part(0,15,start,end,(unsigned char *)&ascii[Num],1);
		}
		else
		{
			start=start-16;
			end=start+15;
			EPD_Dis_Part(0,15,start,end,(unsigned char *)&chiness[Num-75],1);
		}
	}
}


void Display2(unsigned char *D)
{
	int D_length=0;
	int i=0;
	int Num;
	int y_start_c;
	int start;
	int end;
	y_start_c=175;
	start=y_start_c;
	D_length=D[1];
	for (i=2;i<D_length*2+2;i=i+2)
	{
		Num=(D[i]-0xa0)*255+D[i+1];
//		if(k==0)
//		{
//		EPD_init_Part();
//		driver_delay_xms(200);
//		EPD_Dis_Part(0,128-1,0,250-1,(unsigned char *)Image,1); //pic
//		driver_delay_xms(200);
//		k=k+1;
//		}
		if(Num>=0&&Num<=74)
		{
			start=start-8;
			end=start+7;
			EPD_Dis_Part(24,39,start,end,(unsigned char *)&ascii[Num],1);
		}
		else
		{
			start=start-16;
			end=start+15;
			EPD_Dis_Part(24,39,start,end,(unsigned char *)&chiness[Num-75],1);
		}
	}
}

void Display3(unsigned char *D)
{
	int D_length=0;
	int i=0;
	int Num;
	int y_start_c;
	int start;
	int end;
	y_start_c=175;
	start=y_start_c;
	D_length=D[1];
	for (i=2;i<D_length*2+2;i=i+2)
	{
		Num=(D[i]-0xa0)*255+D[i+1];
//		if(k==0)
//		{
//		EPD_init_Part();
//		driver_delay_xms(200);
//		EPD_Dis_Part(0,128-1,0,250-1,(unsigned char *)Image,1); //pic
//		driver_delay_xms(200);
//		k=k+1;
//		}
		if(Num>=0&&Num<=74)
		{
			start=start-8;
			end=start+7;
			EPD_Dis_Part(48,63,start,end,(unsigned char *)&ascii[Num],1);
		}
		else
		{
			start=start-16;
			end=start+15;
			EPD_Dis_Part(48,63,start,end,(unsigned char *)&chiness[Num-75],1);
		}
	}
}

void Display4(unsigned char *D)
{
	int D_length=0;
	int i=0;
	int Num;
	int y_start_c;
	int start;
	int end;
	y_start_c=192;
	start=y_start_c;
	D_length=D[1];
	for (i=2;i<D_length*2+2;i=i+2)
	{
		Num=(D[i]-0xa0)*255+D[i+1];
//		if(k==0)
//		{
//		EPD_init_Part();
//		driver_delay_xms(200);
//		EPD_Dis_Part(0,128-1,0,250-1,(unsigned char *)Image,1); //pic
//		driver_delay_xms(200);
//		k=k+1;
//		}
		if(Num>=0&&Num<=74)
		{
			start=start-8;
			end=start+7;
			EPD_Dis_Part(72,87,start,end,(unsigned char *)&ascii[Num],1);
		}
		else
		{
			start=start-16;
			end=start+15;
			EPD_Dis_Part(72,87,start,end,(unsigned char *)&chiness[Num-75],1);
		}
	}
}
