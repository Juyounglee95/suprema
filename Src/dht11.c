
#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "defines.h"
#include "stm32fxxx_hal.h"
#include "tm_stm32_delay.h"
#include "math.h"
#include "dht11.h"
#include "STM_MY_LCD16X2.h"
uint8_t Rh=0;
uint8_t RhDec=0;
uint8_t Temp=0;
uint8_t TempDec=0; 
uint8_t ChkSum=0;
uint8_t gError=0;

#define dht_pin GPIO_PIN_4
#define dht_pin_GPIO_Port GPIOF
void DHT11Read(void)
{
    int i = 0;
    int j = 0;
    gError=0;
    uint8_t Value[5];
		for(int k =0; k<5; k++)
		{
					Value[k] =0;
		}
			
    int timeout =100000;
    
 
    dht_outputinit();

    /* start sequence */
    HAL_GPIO_WritePin(GPIOF,dht_pin, GPIO_PIN_RESET);
		Delay(18000); //delay 18ms //wait for pull up 
	
		HAL_GPIO_WritePin(GPIOF,dht_pin, GPIO_PIN_SET);
    Delay(40);
 
    dht_inputinit();
		Delay(30);
    while(0 == HAL_GPIO_ReadPin(GPIOF, dht_pin)) /* 80us on '0' */
    {
        
        if (--(timeout) <= 0)
        {
            gError=1;
            break;
        }
       
    };
     
    
    timeout = 100000;
    
    if (gError==0)
    {
        while(1 == HAL_GPIO_ReadPin(GPIOF, dht_pin)) /* 80us on '1' */
        {
            
            if (--(timeout) <= 0)
            {
                gError=1;
                break;
            }
           
        };
    }        
    /* start sequence - end */
 
    /* read sequence */
    if (gError==0)
    {
        for(j=0;j<5;j++)
        {
            for(i=0;i<8;i++)
            {
                
                timeout = 100000;
               
                while(0 == HAL_GPIO_ReadPin(GPIOF, dht_pin))
                {
                   
                    if (--(timeout) <= 0)
                    {
                        gError=1;
                        break;
                    }
                    
                }; /* 50 us on 0 */
 
                if (1 == HAL_GPIO_ReadPin(GPIOF, dht_pin))
                {
                    Delay(30);
									Value[j] <<= 1;
                }
								
               
								
                if(1 == HAL_GPIO_ReadPin(GPIOF, dht_pin))
                {
									 
                    Delay(40); /* wait 'till 70us */
									Value[j] |= 1;
                
                   
                }
								 else
                {
									
                    Value[j] &= 0xfe;
                }
							
								 
            }
        }
    }
    /* read sequence - end */
     
  
    /* checksum check */
    if (gError==0)
    {
        if ((Value[0] +Value[2]) != Value[4])
        {
            gError=1;
					printf("\r error\n");
				}
        else
        {
            gError=0;
            Rh=Value[0];
						RhDec=Value[1];
						Temp=Value[2];
						TempDec=Value[3];
						ChkSum=Value[4];
					printf("\rValue= Rh : %d.%d %% temp: %d.%d C \n",Rh,RhDec,Temp,TempDec);
        }
    }
 

}

		
			
void dht_print(void)
{
	if(gError==0)
	{
		printf("\rValue= Rh : %d.%d temp: %d.%d C \n",Rh,RhDec,Temp,TempDec);
		
		
		
	}
	else{
		
		printf("\r error! Read again \n");
		DHT11Read();
		HAL_Delay(1000);
		dht_print();
		
	}

}	
void dht_LCDprint(void)
{
 
	if(gError==0){
		char lcd_rh[4];
		char lcd_rhDec[4];
		char lcd_temp[4];
		char lcd_tempDec[4];
		sprintf(lcd_rh,"%d", Rh);
		sprintf(lcd_rhDec,"%d", RhDec);
		sprintf(lcd_temp,"%d", Temp);
		sprintf(lcd_tempDec,"%d",TempDec );
		
		//LCD_clear();
		LCD_print("RH: ");
		LCD_print(lcd_rh);
		LCD_print(".");
		LCD_print(lcd_rhDec);
		LCD_setCursor(2,1);
		LCD_print("Temp: ");
		LCD_print(lcd_temp);
		LCD_print(".");
		LCD_print(lcd_tempDec);
	}
	
	
}
void dht_outputinit(void)
{
	GPIO_InitTypeDef GPIO_dht;
	__HAL_RCC_GPIOF_CLK_ENABLE();
	GPIO_dht.Pin = dht_pin;
	GPIO_dht.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_dht.Pull = GPIO_NOPULL;
	GPIO_dht.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOF, &GPIO_dht);
	
}
void dht_inputinit(void)
{
	GPIO_InitTypeDef GPIO_dht;
	__HAL_RCC_GPIOF_CLK_ENABLE();
	GPIO_dht.Pin = dht_pin;
	GPIO_dht.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOF, &GPIO_dht);
	
}