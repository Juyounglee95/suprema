#include "main.h"
#include "stepper.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define IN1 GPIO_PIN_12
#define IN2 GPIO_PIN_11
#define IN3 GPIO_PIN_13
#define IN4 GPIO_PIN_14
#define IN1_GPIO_Port GPIOB
#define IN2_GPIO_Port GPIOB
#define IN3_GPIO_Port GPIOB
#define IN4_GPIO_Port GPIOB
int step=0;
bool Direction= true;
void stepping_sensor_init(void)
{
	GPIO_InitTypeDef GPIO_stepping;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_stepping.Pin = IN1|IN2|IN3|IN4;
	GPIO_stepping.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_stepping.Pull = GPIO_NOPULL;
	GPIO_stepping.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIO_stepping);

	
	

}
void stepper(int a)
{
	for(int i =0; i<a; i++)
	{
		switch (step){
			case 0:
						printf("\r0\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_SET);
						break;
			case 1:
						printf("\r1\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_SET);
						break;
			case 2:
						printf("\r2\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_RESET);
						break;
			case 3:
						printf("\r3\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_RESET);
						break;
			case 4:
						printf("\r4\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_RESET);
						break;
			case 5:
						printf("\r5\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_RESET);
						break;			
			case 6:
						printf("\r6\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_RESET);
						break;
			case 7:
						printf("\r7\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB,IN2, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN3, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN4, GPIO_PIN_SET);
						break;
			default:
						printf("\r--\n");
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB,IN1, GPIO_PIN_RESET);
						break;		
		}
		
	}
	set_direction();

}
void set_direction(void)
{
	if(Direction==1)
	{
		step++;
	}
	if(Direction==0)
	{
		step--;
	}
	if(step>7)
	{
		step=0;
	}
if(step<0)
	{
		step=7;
				
	}	
}