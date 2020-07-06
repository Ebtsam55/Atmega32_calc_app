/*
 * Calculator_app.c
 *
 * Created: 4/4/2020 9:17:53 PM
 *  Author: Ebtsam
 */ 


#include "lcd.h"
#include "keypad.h"
uint32_t calculate_result (uint8_t * list , uint8_t index , uint8_t *  );



int main(void)
{ LCD_init();
  keypad_init();
  
  
  uint8_t keypad_reading_list [20];
  uint8_t index=0;
  uint8_t ISPRESSED =1;
  uint8_t IsNegative =0 ;

  
    while(1)
    {
       int8_t key = keypad_read();
	   _delay_ms(10);
	   
	   if (key=='C')
	    {  
			LCD_clear();
			index=0;
			IsNegative=0;
		    continue ;   
		}
	   
	 else if(key!=-1 && ISPRESSED) // flag to avoid bouncing of keypad buttons
	   {   
		   LCD_goToRowColumn(0,index);
		   keypad_reading_list[index++]=key;
		   LCD_write_char(key);
		   ISPRESSED=0;
		      
	   }
	   else if (key==-1 && !ISPRESSED)
	   {
		   ISPRESSED=1;
	   }		
	      
	   if(key=='=')
	   {
		   LCD_goToRowColumn(1,0);
		   uint32_t result =calculate_result(keypad_reading_list , index , &IsNegative) ;
		   if(IsNegative==1)
		   {
			  LCD_write_char('-') ;
			  LCD_goToRowColumn(1,1);
			 
		   }
		   LCD_write_num(result);
	   }
    }
}

uint32_t calculate_result (uint8_t * list , uint8_t index  , uint8_t *IsNegative ) 
{
	uint32_t operands[3]; // As the design of that calculator is 3 operands as maximum , and 2 operators as maximum
	uint8_t operator[3];
	uint32_t num=0 ; 
	uint8_t operand_index=0; 
	uint8_t operator_index=0; 
	
	for (uint8_t i=0; i<index ; i++)   // (index-1) as list index contains '=' , and no need to it 
	{
		if(list[i]>='0'&&list[i]<='9')
		{
			num *=10; 
			num +=(list[i]-'0');
		}
		else 
		{
			operator[operator_index++]=list[i];
			operands[operand_index++]=num;
			num=0;	
		}
	}
	
	
	
		for (uint8_t i=0; i<operator_index ; i++)	
		{
			switch (operator[i])
			{
				case '*':
				   operands[0] *=operands[1];
				   operands[1]=operands[2];
				   break;
					 
			   case '+':
				   operands[0]+=operands[1];
				   operands[1]=operands[2];
				   break;
				   
			   case '-':
			       if (operands[1]>operands[0])
				       {  *IsNegative=1;
				          operands[0]=operands[1]-operands[0];
						  operands[1]=operands[2];
					   }
				  else
					   { 
						   operands[0]-=operands[1];
						   operands[1]=operands[2];
					    }				  
				  break;
			   
			   case '/':
				   operands[0] /=operands[1];
				   operands[1]=operands[2];
				   break;
			   
			   case '=':
			        return operands[0];
					break;
					
			   default:
			        break;
				
					 
			}
		}
	}

