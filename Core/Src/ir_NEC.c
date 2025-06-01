#include "ir_NEC.h"
unsigned char start_bit;
unsigned char cout_enter=0;

/**
  * @brief  used to interrupt trigger time point recording
  * @param  falling_edge_time  the array used to record interrupt trigger time point
  * @param  time_couter the time couter  variable ,suggested the timer use 100kHZ (10us)
  * @retval void
  */
void ir_recorded_data(unsigned int *falling_edge_time,unsigned int time_couter)
{
 if(cout_enter==36) cout_enter=0;
			switch(cout_enter)
			{
				case 0: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 1: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 2: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 3: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 4: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 5: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
			  case 6: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 7: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 8: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 9: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 10: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 11: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 12: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 13: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 14: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 15: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 16: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 17: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 18: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 19: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 20: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
			  case 21: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 22: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 23: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 24: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 25: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
			  case 26: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 27: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 28: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 29: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 30: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 31: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 32: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 33: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 34: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
				case 35: falling_edge_time[cout_enter]=time_couter;cout_enter++;break;
			}

}
/**
  * @brief  For processing NEC protocol data
  * @param  value  the array address where the result is stored,suggested space is 4
  * @param  falling_edge_time  the array used to record interrupt trigger time point
  *         
  * @retval void
  */
//红外数据解析
void ir_data_analysis( unsigned char *value,unsigned int *falling_edge_time)
{
	  unsigned int un=0; 
		volatile int pulse[36];
	  int j;
		int start_ok=0;
    for(j=0;j<36;j++)
		{
			pulse[j]=falling_edge_time[j+1]-falling_edge_time[j];
			if(j==35){pulse[35]=falling_edge_time[0]-falling_edge_time[35];}
		}
		//unsigned char begin_start;
		for(j=0;j<36;j++)
		{
			  if(pulse[j]>1000&& pulse[j]<1300) 
				{
					if(pulse[j+1]>100&& pulse[j+1]<130) {start_bit=j+1;start_ok=1;break;}
				
				}
		}
		//printf("start_bit=%d\n",start_bit);
		if(start_ok)
		{
				for(j=0;j<32;j++)    //舍去 j=0 :pulse[0]为引导信号
				{    
					   if(start_bit==36){start_bit=0;}
						 //if(j>29){printf("pules %d =%d\n",j,pulse[start_bit]);printf("start_bit=%d\n",start_bit);}
						 if(pulse[start_bit]>200 && pulse[start_bit]<250) //大于200，即560us+1650us =2150 us  > 200*10us  解码值为1
						 {
							 //if(j<2){printf("pulse_%d=%d\n",j,pulse[start_bit]);}
							 //ir_value[j/8]|=0x80;
							 un|=0x80000000;      //1000 0000  ,0000 0000, 0000 0000 ,0000 0000 
						 }
						 else          																  //小于200，即560us+560us =1200 us  < 200*10us  解码值为0
						 {
						 }
						 if(j<31){/*ir_value[j/8]=ir_value[j/8]>>1;*/ un=un>>1;}
						 start_bit++;
				}

				start_ok=0;
			  for(int i=0;i<4;i++)
				{
						value[i]=(unsigned char) (un>>((24-(3-i)*8)));
						//printf("value=%d\n",value[i]);
				}
				if(value[2]!=(unsigned char)~value[3])
				{
						printf("receive erorr\n");
				}
				printf("value=%d\n",value[2]);
		}
	
}
