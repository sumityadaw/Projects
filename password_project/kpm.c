//kpm2.c
#include <LPC21xx.h>
#include "types.h"
#include "kpm_defines.h"

u8 kpmLUT[4][4]=
{

   { '1','2','3','-' },	
	 { '4','5','6','-' },
	 { '7','8','9','+' },
	 { 'C','0','=','=' }
};	

u32 ColScan(void)
{
	return (((IOPIN1>>COL0)&15)==15)?1:0;
}	

void InitKPM(void)
{
	//cfg row lines as gpio out
	IODIR1|=15<<ROW0;
	//& col lines are default input
}	

u32 RowCheck(void)
{
	u32 rNo;
	for(rNo=0;rNo<4;rNo++)
	{
	 //ground 0th to 3rd row iteratively
	 IOPIN1=((IOPIN1&~(15<<ROW0))|(((~(1<<rNo))&15)<<ROW0));	
	  //chk if key was pressed in this row
	 if(ColScan()==0)
	 {
		 break;
	 }
  }	 
	//re-initializing all rows to ground
	IOCLR1=15<<ROW0;
	return rNo;
}	

u32 ColCheck(void)
{
	u32 cNo;
	for(cNo=0;cNo<4;cNo++)
	{
	  if(((IOPIN1>>(COL0+cNo))&1)==0)
     	break;
	}	
	return cNo;
}

u32 KeyScan(void)
{
	u32 rNo,cNo;
	//wait for any key press
	while(ColScan());
	//identify row in which key was pressed
	rNo=RowCheck();
	//identify col in which key was pressed
	cNo=ColCheck();
	//extract/map key pressed to key value
	return kpmLUT[rNo][cNo];
}	
