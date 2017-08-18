#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "UF_SysParameter.h"
#include "UF_API.h"
#include "UF_Packet.h"
#include "UF_Error.h"
#include "UF_Command.h"
#include "math.h"
#include "UF_Enroll.h"
#include "dht11.h"
#include "STM_MY_LCD16X2.h"
#include "sfm6020.h"
int g_nPort = COMPORT1;
int g_nBaudrate = 115200;
int g_nProtocol = 0;  //0 : single   1: network
int g_nModuleID = 1;
int g_bConnectionStatus = 0;
int g_bTrace = 0;
uint8_t transmitBuffer[32];
uint8_t receiveBuffer[32];
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;
#define BinaryToAscii( data ) ( ( data ) >= 10 ? ( data ) - 10 + 'A' : ( data ) + '0' )
#define AsciiToBinary( data ) ( ( data ) >= 'A' ? ( data ) - 'A' + 10 : ( data ) - '0' )
char hextable[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
#define TOHEX(a, b)     {*b++ = hextable[a >> 4];*b++ = hextable[a&0xf];}
SysParameter *sysParameter;

char sysParamList[][20]={
    "TIMEOUT",
    "ENROLL_MODE",
    "SECURITY_LEVEL",
    "ENCRYPTION_MODE",
    "SENSOR_TYPE",
    "IMAGE_FORMAT",
    "MODULE_ID",
    "FIRMWARE_VERSION", //7
    "SERIAL_NUMBER", //8
    "BAUDRATE",
    "AUX_BAUDRATE",
    "ENROLLED_FINGER",
    "AVAILABLE_FINGER",
    "SEND_SCAN_SUCCESS",
    "ASCII_PACKET",
    "ROTATE_IMAGE",
    "SENSITIVITY",
    "IMAGE_QUALITY",
    "AUTO_RESPONSE",
    "NETWORK_MODE",
    "FREE_SCAN",
    "PROVISIONAL_ENROLL",
    "PASS_WHEN_EMPTY",
    "RESPONSE_DELAY",
    "MATCHING_TIMEOUT",
    "BUILD_NO", //25
    "ENROLL_DISPLACEMENT",
    "TEMPLATE_SIZE",
    "ROTATION",
    "LIGHTING_CONDITION",
    "FREESCAN_DELAY",
    "CARD_ENROLL_MODE",
    "FAST_MODE",
    "WATCHDOG",
    "TEMPLATE_TYPE",
    "ENHANCED_PRIVACY",
    "FAKE_DETECT",
    "CHECK_LATENT",
    "VOLTAGE_WARNING",
    "POWEROFF_TIMEOUT",
    "EXPOSURE",
    "RESERVED"
};

typedef struct _command
{
    char strCommand[4];
    int nCommand;
}UF_CommandList;

UF_CommandList commandParamList[]=
{
    {"SR",0x03},
    {"ES",0x05},
    {"VS",0x08},
    {"IS",0x11},
    {"DA",0x17},
    {"-1",-1}
};
//#include "stm32f4xx_hal_msp.c"
int StartProgram(void)
{
    char strMenu[1];
    int nMenu;
		int bExit = 0;
    int RcvStat;
		HAL_Delay(2);
		LCD_print("Start Program");
		LCD_setCursor(2,1);
		LCD_print("Check connection");
		HAL_Delay(1000);
	//	finger_button_init();
	
	
    while(bExit != 1)
    {
        MainMenu();
			
			
				
		
#if 0
      //  RcvStat = HAL_UART_Receive(&huart2, (uint8_t *)strMenu, 1, 1000);
//        RcvStat = HAL_UART_Receive_IT(&huart2, strMenu, 1);
      //  if (RcvStat == HAL_OK)
      //  {
      //      nMenu = atoi(strMenu);
      //      printf("%s\n", strMenu);
      //  }
				
#else
			
	
				fflush(stdin);
        strMenu[0] = getchar();
    		nMenu = atoi(strMenu);
				
				
			

#endif
			
        switch(nMenu)
        {
            case 0:
               Commander();
                break;
            case 1:
                CommunicationSetup();
                break;
           case 2:
               Enroll();
                break;
            case 3:
                Identify();
                break;
            case 4:
                Verify();
                break;
            case 5:
              SystemParameterSetting();
                break;
            case 6:
               Delete_all();
                break;
            case 7:
								bExit=1;
                break;
            default:
                printf("Please, try again!\n");
                fflush(stdin);
                getchar();
						
                break;
        }
     				nMenu = -1;
    }
    return 0;
}




void MainMenu(void)
{
    Intro();
    CurrentCummunicationSetup();
    if(g_bConnectionStatus)
			LCD_clear();
			HAL_Delay(2);
			LCD_print("Select menu");	
    printf("\r\n0.Commander\n");
    printf("\r\n1.Communication Setup\n");
    printf("\r\n2.Enroll\n");
    printf("\r\n3.Identify\n");
    printf("\r\n4.Verify\n");
    printf("\r\n5.Sytem Parameter Setting\n");
    printf("\r\n6.Delete All\n");
    printf("\r\n7.Exit\n");
    printf("\r\n>>");
}
void Intro(void)
{
    printf("\r(%d)******************************\n", HAL_GetTick());
    printf("\r**********************************\n");
    printf("\r UFCommander v1.0 for STM32F4x \n");
    printf("\r**********************************\n");
}

void CommunicationSetupMenu(void)
{
    CurrentCummunicationSetup();
    printf("\r1.Connect\n");
    printf("\r2.Disconnect\n");
    printf("\r3.Reconnect\n");
    printf("\r4.Search Module\n");
    printf("\r5.Change Communication Setup\n");
    printf("\r6.Back\n");
    printf("\r>>");
}

void CurrentCummunicationSetup(void)
{
    printf("\r----------------------------------\n");
    printf("\r  Current Communication Setting   \n");
    printf("\r----------------------------------\n");

    printf("\r%-11s : %dbps\n", "Baudrate",huart6.Init.BaudRate);

    if(g_nProtocol == 0)
        printf("\r%-11s : Single\n","Protocol");
    else
        printf("\r%-11s : Network\n","Protocol");

    if(g_nProtocol == 1)
        printf("\r%-11s : %d\n","ModuleID", g_nModuleID);

    if(g_bConnectionStatus == 0)
        printf("\r%s\n","Status : [ Disconnected ]");
    else
        printf("\r%s\n","Status : [ Connected ]");


    if(sysParameter!=NULL && g_bConnectionStatus!=0)
    {
        printf("\r----------------------------------\n");
        printf("\r   Connected module information   \n");
        printf("\r----------------------------------\n");
        printf("\r%-11s : %c%c%c%c\n","F/W version", sysParameter[7].value>>24 & 0xff,sysParameter[7].value>>16 & 0xff,sysParameter[7].value>>8 & 0xff,sysParameter[7].value &0xff );
        printf("\r%-11s : %d\n", "Serial No.",sysParameter[8].value);
        printf("\r%-11s : %02x%02x%02x%02x\n","Build No.", sysParameter[25].value>>24 & 0xff, sysParameter[25].value>>16 & 0xff,sysParameter[25].value>>8 & 0xff,sysParameter[25].value &0xff );
    }

    printf("\r----------------------------------\n");
}
void Commander(void)
{
    if(g_bConnectionStatus == 0)
    {
        printf("\rThe module was not connected. Please, Connect to module first.\n");
        WaitKey();
        return;
    }

    printf("\rEnter the command and parameters.\n");
    printf("\rex: (SR 0x0 0x0 0x6d) or (0x3 0x0 0x0 0x6d)\n");
    printf("\r    (3 0 0 109)\n");
    printf("\r    (3 0 0 0x6d)\n");
    printf("\rType 'exit' to exit commander\n");

    while (1)
    {
        char  buf[100]="";
        char  command[100]="";
        char  param[100]="";
        char size[100]="";
        char flag[100]="";
        unsigned char  packet[UF_PACKET_LEN];
        int nCommand, nParam, nSize, nFlag;
        char *p;
        int s;

        printf("\r## ");
				scanf("%s", buf);

        p = strtok(buf, " ,");

        if(p!=NULL) {
            strcpy(command, p);
            if(strcmp(command,"exit")==0) {
                printf("\rcommander will be exit!\n");
                WaitKey();
                break;
            }
         } else {
            printf("\rWrong command! Try again!\n");
            continue;
         }

         p = strtok(NULL, " ,");
         if(p!=NULL)
            strcpy(param, p);
        else {
            printf("\rWrong command! Try again!\n");
            continue;
        }

        p = strtok(NULL, " ,");
        if(p!=NULL)
            strcpy(size, p);
        else
        {
            printf("\rWrong command! Try again!\n");
            continue;
        }

        p = strtok(NULL, " ,");
        if(p!=NULL)
            strcpy(flag, p);
        else {
           printf("\rWrong command! Try again!\n");
            continue; 
        }

        if(GetStrToInt(command) != 0)
        {
            nCommand = GetStrToInt(command);
        }
        else
        {
             nCommand = GetCommandParameterIndex(command);
        }
        nParam = GetStrToInt(param);
        nSize = GetStrToInt(size);
        nFlag = GetStrToInt(flag);

        UF_MakePacket(nCommand, nParam, nSize, nFlag, packet );
        SendPacket(packet);
        
        ClearBuffer();

//        s = GetTickCount();
        s = HAL_GetTick();
        
        while(1)
        {
            memset(packet,0,UF_PACKET_LEN);
            //RecievePacket(packet, UF_PACKET_LEN, 1000);
            HAL_UART_Receive_IT(&huart2, packet, UF_PACKET_LEN);
            if(UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_SUCCESS &&  packet[UF_PACKET_END_CODE_POS]== UF_PACKET_END_CODE)
            {
                printf("\rERROR FLAG : 0x%02x\n", UF_GetPacketValue(UF_PACKET_FLAG, packet));
//                break;
            }

            //if(GetTickCount()-s > 10000)
            if(HAL_GetTick()-s > 10000)
                break;
        }
    
    }
}
void CommunicationSetup(void)
{
    char strMenu[1];
    int nMenu=-1;
    int bExit = 0;
    int RcvStat;
    
    while(bExit!=1)
    {
        CommunicationSetupMenu();
        fflush(stdin);
        strMenu[0] = getchar();
        nMenu  = atoi(strMenu);
        switch(nMenu)
        {
            //Connect
            case 1:
                Connect();
                printf("\r Connect()\n");
                if(g_bConnectionStatus==1)
                    bExit=1;
                break;
            //Disconnect
            case 2:
                Disconnect();
                printf("\r Disconnect()\n");
                break;
            //Reconnect
            case 3:
                Reconnect();
                printf("\r Reconnect()\n");
                if(g_bConnectionStatus==1)
                    bExit=1;
                break;
            //Search module
            case 4:
    //            SearchModule();
                printf("\r SearchModule()\n");
                break;
            //Change Communication Setup
            case 5:
    //            ChangeCommunicationSetup();
                printf("\r ChangeCommunicationSetup()\n");
                break;
            //Exit
            case 6:
                bExit = 1;
                break;
            default:
                printf("Please, try again!\n");
                fflush(stdin);
                getchar();
                break;
        }
        nMenu = -1;
        ClearBuffer();
    }
}
int Connect(void)
{
    unsigned char send_buf[UF_PACKET_LEN]={0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x0A}; 
    unsigned char recv_buf[UF_PACKET_LEN]="";
    int flag;
    int chksum;

    int ret;
	
		LCD_print("Program Start");
		LCD_setCursor(2,1);
		LCD_print("Connect Start");
	 HAL_UART_Receive_IT(&huart6, recv_buf, UF_PACKET_LEN); 
	
		HAL_UART_Transmit_IT(&huart6, send_buf, UF_PACKET_LEN); 

    printf("\r[RX] ");
    for (int i = 0; i < UF_PACKET_LEN; i++)
    {
        HAL_Delay(2);   // The delay time may need to be changed.
        printf("%02X ", recv_buf[i]); 
    }
    printf("\n");
    
    flag = UF_GetPacketValue(UF_PACKET_FLAG, recv_buf);
    chksum = UF_GetPacketValue(UF_PACKET_CHECKSUM, recv_buf);

    printf("\r[CONNECT] flag = %x\n", flag);
    printf("\r[CONNECT] chksum = %x\n", chksum);
		//UF_MakePacket(UF_COM_DA, param, UF_PACKET_LEN, flag, (BYTE*)recv_buf);
    if(flag == UF_PROTO_RET_SUCCESS)
    {
      g_bConnectionStatus = 1;
      ReadSystemParameterSetting();
      printf("\r\n[ Port %d (%dbps)was connected ]\n\n", g_nPort, g_nBaudrate);
    }
    buzzer_start(1);
		LCD_clear();
		LCD_print("Connect Success");
		HAL_Delay(2000);
		LCD_clear();
    //Reconnect();
    WaitKey();

    return 1;
}

int Disconnect(void)
{
    if(g_bConnectionStatus ==  1)
			
    {
        HAL_UART_MspDeInit(&huart6);
        g_bConnectionStatus = 0;
        printf("\r\n[ Port was closed ]\n\n");
        WaitKey();
        return 1;
    }
    else
    {
        printf("\rPort was not connected. press any key!\n");
        WaitKey();
        return 0;
    }
}

void Reconnect(void)
{
    Disconnect();
    Connect();
    printf("Reconnected. press any key!\n");
    WaitKey();
}

void ReadSystemParameterSetting(void)
{
    int i, s;
    int param;
    int size;
    int flag;
    int result;
    BYTE packet[UF_PACKET_LEN];
    UF_InitSysParameter();

    i = 0;

    if (g_bConnectionStatus == 0) {
        printf("\rThe module was not connected. Please, Connect to module first.\n");
        WaitKey();
        return;
    }

    sysParameter = GetSysParamPointer();

    while( sysParameter[i].parameter != -1)
    {
        UF_MakePacket( UF_COM_SR , param, size, sysParameter[i].parameter, packet );
        SendPacket(packet);
        ClearBuffer();
        //RecievePacket(packet, UF_PACKET_LEN, 3000);
        HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN);
        HAL_Delay(300);
        
        result = UF_GetPacketValue(UF_PACKET_FLAG, packet);
        if(result == UF_PROTO_RET_SUCCESS) {
            sysParameter[i].value = UF_GetPacketValue(UF_PACKET_SIZE, packet);
        }

        i++;
    }

    i = 0;
    printf("\r======================================\n");
    while( sysParameter[i].parameter != -1)
    {
        printf("\r%20s : 0x%08x(%d)\n", 
			sysParamList[i], sysParameter[i].value, sysParameter[i].value);
        i++;
    }
    printf("\r======================================\n");
}
void WaitKey(void)
{
	while(1){
	LCD_clear();
	HAL_Delay(1000);
	
	dht_LCDprint();
	HAL_Delay(1000);
//	LCD_clear();
		

	}
    printf("\rpress any key!");
   // fflush(stdin);
   // getchar();
}
void BinToHex(unsigned char c , unsigned char *buf)
{
                 // Device header
    TOHEX(c, buf);
}

void BinToHexPacket(unsigned char* inbuf, unsigned char *outbuf, int inbuf_size)
{
    int i;

    for(i=0; i<inbuf_size; i++)
    {
        BinToHex(inbuf[i], &outbuf[i*3]);
        outbuf[i*3+2] = 32;
    }

}
int GetCommandParameterIndex(char* paramName)
{
    int i=0;
    int result=-1;

    while(commandParamList[i].nCommand != -1)
    {
        if(strcmp(paramName, commandParamList[i].strCommand)==0)
        {
            result = commandParamList[i].nCommand;
            break;
        }
        i++;
    }
    return result;
}
int GetStrToInt(char* str)
{
    long int result=0;

    if(strtol(str, NULL, 0) != 0L)
        result = strtol(str, NULL, 0);
    else if(strtol(str, NULL, 10) != 0L)
        result = strtol(str, NULL, 10);

    return result;
}
void SendPacket(unsigned char* data)
{
    int i;
    unsigned char hexbuf[UF_PACKET_LEN*3];

    memset(hexbuf, 0, UF_PACKET_LEN);

    HAL_UART_Transmit_IT(&huart6, data, UF_PACKET_LEN);

    BinToHexPacket(data, hexbuf, UF_PACKET_LEN);

    printf("%8s : ", "[SEND]",UF_PACKET_LEN);

    for(i=0; i<UF_PACKET_LEN*3; i++)
    {
        printf("%c",(char)hexbuf[i]);
    }
    printf("\n");
}

void ClearBuffer(void)
{
#if 0
    huart1.gState = HAL_UART_STATE_RESET;
    if (HAL_UART_Init(&huart2) != HAL_OK||HAL_UART_Init(&huart6) != HAL_OK) {
        Error_Handler();
    }
#else
    memset(transmitBuffer, 0x0, 13);
    memset(receiveBuffer, 0x0, 13);
//    __HAL_UART_RESET_HANDLE_STATE(&huart1);
#endif
}
void Enroll(void)
{
    printf("\r[andro.yoon] %s\n", __func__);
	
    int result;
    UINT32 userID;
    int imageQaulity;
    int enroll_mode;
    int index;
    BYTE packet[UF_PACKET_LEN];
    int param = 0;
    int size = 0;
    int flag = UF_ENROLL_AUTO_ID;
		char ID[10];
    if(g_bConnectionStatus == 0)
    {
        printf("\rThe module was not connected. Please, Connect to module first.\n");
				
				
        WaitKey();
        return;
    }

	//Wait(500);
	index = GetSystemParameterIndex("ENROLL_MODE");
	enroll_mode = sysParameter[index].value;
	dht_print();
	HAL_Delay(100);
		
	UF_MakePacket( UF_COM_ES , param, size, flag, packet );
	SendPacket(packet);
  
    printf("\rPlace finger on the sensor\n");
    ClearBuffer();
//    RecievePacket(packet, UF_PACKET_LEN, 10000);
   
		printf("\r First Scan \n");
		while(1)	
		{    
			 HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN); //scanner execute
				HAL_Delay(4);
			if(UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_SCAN_SUCCESS) //62
				 {  printf("\r\n[%s - Scan Success ]\n", __func__);
					
						break;
				 } 
				 else if (UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_TIME_OUT) {
						printf("\r\n[%s - Time out ]\n", __func__);
					
						return;
						}
		}
    //Wait(500);
    ClearBuffer();
//	RecievePacket(packet, UF_PACKET_LEN, 10000);
   	HAL_Delay(500);
		
		printf("\r Second Scan \n");
				while(1)	
		{    
			 HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN); //scanner execute
				HAL_Delay(4);
			if(UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_SCAN_SUCCESS) //62
				 {  printf("\r\n[%s - Scan Success ]\n", __func__);
					
						break;
				 } 
				 else if (UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_TIME_OUT) {
						printf("\r\n[%s - Time out ]\n", __func__);
					
						return;
						}
		}
    //Wait(500);
    ClearBuffer();
//	RecievePacket(packet, UF_PACKET_LEN, 10000);
   	HAL_Delay(500);
		
			while(1)
			{		
				 HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN); //scanner execute
				HAL_Delay(4);
					if(UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_SUCCESS) //61
					{
					
						buzzer_start(1);
					printf("\r\n[%s - Enroll Success ]\n", __func__);
							  HAL_Delay(1);
						LCD_clear();
						LCD_print("Enroll Success");
					//	HAL_Delay(2000);	
					//	LCD_clear();
					userID = UF_GetPacketValue(UF_PACKET_PARAM, packet);
					imageQaulity = UF_GetPacketValue(UF_PACKET_SIZE, packet);
				
						sprintf(ID, "%d",userID);
						LCD_setCursor(2,1);
						LCD_print("Enrolled ID:");
						LCD_print(ID);
						HAL_Delay(2000);	
						LCD_clear();
					printf("\r\n[ Enrolled UserID : %d  Score : %d ]\n",userID, imageQaulity);
						
					 return;
				 } else if (UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_TIME_OUT) 
				{
						buzzer_start(2);
						LCD_clear();
						LCD_print("Enroll Failed");
						printf("\r\n[%s - Time out ]\n", __func__);
						LCD_setCursor(2,1);
						LCD_print("Timeout");
						HAL_Delay(2000);	
						LCD_clear();
				 
						return;
				}
				}
			
    ClearBuffer();
		
    WaitKey();
}

void Identify(void)
{
    printf("\r[andro.yoon] %s\n", __func__);
    int result;
    UINT32 userID;
    UINT32 subID;
    BYTE packet[UF_PACKET_LEN];
    int param = 0;
    int size = 0;
    int flag = 0;
		char ID[10];
		char s_ID[10];
    if(g_bConnectionStatus == 0)
    {
        printf("\rThe module was not connected. Please, Connect to module first.\n");
        WaitKey();
        return;
    }
		dht_print();
		HAL_Delay(100);
    UF_MakePacket( UF_COM_IS , param, size, flag, packet );
    SendPacket(packet);

    printf("\r>>>Place finger on the sensor>>>\n");
    ClearBuffer();

    while (1) {
        HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN);
        if(UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_SCAN_SUCCESS) {
            printf("\r\n[%s - Scan Success ]\n", __func__);
            printf("\r----------------------------------");
            break;
        } else if (UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_TIME_OUT) {
            printf("\r\n[%s - Time out ]\n", __func__);
            printf("\r----------------------------------");
            return;
        }
    }
    ClearBuffer();

   
    while (1) {
			 HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN);
        HAL_Delay(5);

        fflush(stdin);
        result = UF_GetPacketValue(UF_PACKET_FLAG, packet);
       
        if(result==UF_PROTO_RET_SUCCESS)
				{				buzzer_start(1);
                printf("\r\n[%s - Success ]\n", __func__);
						  HAL_Delay(1);
								LCD_clear();
								LCD_print("Identify Success");
                userID = UF_GetPacketValue(UF_PACKET_PARAM, packet);
                subID = UF_GetPacketValue(UF_PACKET_SIZE, packet);
								
								sprintf(ID, "%d",userID);
								LCD_setCursor(2,1);
								LCD_print("ID:");
								LCD_print(ID);
								HAL_Delay(2000);	
								LCD_clear();
				
                printf("\r\n[ Identified UserID : %d(%d) ]\n",userID, subID);
                printf("\r----------------------------------");
              return;
				}
				else if(result ==UF_PROTO_RET_NOT_FOUND)
				{				buzzer_start(2);
								HAL_Delay(1);
								LCD_clear();
								LCD_print("Identify Failed");
								HAL_Delay(2000);	
								LCD_clear();
                printf("\r\n[%s - Not found ]\n", __func__);
                printf("\r----------------------------------");
               return;
        
        }


    }
    ClearBuffer(); 

    WaitKey();
}

void Verify(void)
{
    printf("\r[andro.yoon] %s\n", __func__);
    int result;
    char strID[10];
    UINT32 userID=0;
    UINT32 subID=0;
    BYTE packet[UF_PACKET_LEN];
    int param = userID;
    int size = 0;
    int flag = 0;

    if(g_bConnectionStatus == 0)
    {
        printf("The module was not connected. Please, Connect to module first.\n");
        WaitKey();
        return;
    }
		dht_print();
		HAL_Delay(100);
    printf("\rPlease, enter the user ID : ");
   
		scanf("%s", strID);
		fflush(stdin);
    userID  = atoi(strID);
			printf("\n");
	UF_MakePacket( UF_COM_VS , userID, size, flag, packet );

	SendPacket(packet);
	
    printf("\rPlace finger on the sensor\n");
    ClearBuffer();
    //RecievePacket(packet, UF_PACKET_LEN, 10000);
    
		 HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN);
		while(1){
		 if(UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_SCAN_SUCCESS)
		 { 
			 printf("\r[ Scan Success ]\n\n");
				break;
		 }
		  else if (UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_TIME_OUT) {
            printf("\r\n[%s - Time out ]\n", __func__);
            printf("\r----------------------------------");
            return;
        }
			}
    ClearBuffer();
	//RecievePacket(packet, UF_PACKET_LEN, 10000);
   
    
			HAL_Delay(1);
	while (1) {		
		 HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN);
        HAL_Delay(4);
       if(UF_GetPacketValue(UF_PACKET_FLAG, packet)==UF_PROTO_RET_SUCCESS)
			 {					buzzer_start(1);
                printf("\r\n[%s - Success ]\n", __func__);
				 	  HAL_Delay(1);
								LCD_clear();
								LCD_print("Verify Success");
                userID = UF_GetPacketValue(UF_PACKET_PARAM, packet);
                subID = UF_GetPacketValue(UF_PACKET_SIZE, packet);
                printf("\r\n[ verified UserID : %d(%d) ]\n",userID, subID);
                printf("\r----------------------------------");
          break;
			 }
         else if(UF_GetPacketValue(UF_PACKET_FLAG, packet)==UF_PROTO_RET_NOT_MATCH) 
				{
					
						buzzer_start(2);
	
            printf("\r\n[%s - Fail ]\n", __func__);
            break;
           
        }
 

    }
    ClearBuffer();

    WaitKey();
}
void Delete_all(void)
{
    BYTE packet[UF_PACKET_LEN];
    int param = 0;
    int size = 0;
    int flag = 0;

    if(g_bConnectionStatus == 0) {
        printf("\rThe module was not connected. Please, Connect to module first.\n");
        WaitKey();
        return;
    }
		dht_print();
		printf("\r Delete ALL \n");
    UF_MakePacket( UF_COM_DA , param, size, flag, packet );
    SendPacket(packet);

    while(1) {
        HAL_UART_Receive_IT(&huart6, packet, UF_PACKET_LEN);
        if(UF_GetPacketValue(UF_PACKET_FLAG, packet) == UF_PROTO_RET_SUCCESS) {
						buzzer_start(1);
						LCD_clear();
						LCD_print("Delete Success");
						HAL_Delay(2000);	
						LCD_clear();
            printf("\r[%s] Delete All OK\n", __func__);
//            break;
            return;
        }
    }
    ClearBuffer();
    WaitKey();
}
void SystemParameterSetting(void)
{
    unsigned char strMenu[1]="";
    unsigned char c ;
    int nMenu;
    int bExit = 0;

    ReadSystemParameterSetting();

    do
    {
        printf("\rDo you want to change a parameter? [Y/N] : ");
        fflush(stdin);
        strMenu[0] = getchar();
        c = strMenu[0];
        if(c == 'y' || c == 'Y')
            break;
        else if(c == 'n' || c == 'N')
            return;
        else
        {
            printf("Please, try again!\n");
            WaitKey();
        }
    }while(bExit!=1);

    ChangeSystemParameterSetting();
    WaitKey();
}

void ChangeSystemParameterSetting(void)
{
    unsigned char strMenu[100]="";
    unsigned char paramID[20]="";
    unsigned char paramValue[10]="";
    BYTE packet[UF_PACKET_LEN];
    int nParamValue=0;
    int nParamID=0;
    int bExit = 0;
    char c;

    printf("Enter parameter name (see above table):");
    fflush(stdin);
    paramID[0] = getchar();
//    gets(paramID);
    nParamID = GetSystemParameterIndex(paramID);

    printf("Enter parameter value (integer or hex) :");
    fflush(stdin);
    strMenu[0] = getchar();
    nParamValue = atoi(strMenu);
    if(strtol(paramValue, NULL, 0) != 0L)
        nParamValue = strtol(paramValue, NULL, 0);
    else if(strtol(paramValue, NULL, 10) != 0L)
        nParamValue = strtol(paramValue, NULL, 10);
}

int GetSystemParameterIndex(char* paramName)
{
    int i=0;
    int result=-1;
    if(sysParameter==NULL) {
        printf("\r[andro.yoon] sysParameter NULL\n");
        return -1;
    }

    while(sysParameter[i].parameter != -1)
    {
        if(strcmp(paramName, sysParamList[i])==0)
        {
            result = i;
            break;
        }
        i++;
    }
    return result;
}