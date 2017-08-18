//#include "stm32f4xx_hal.h"

/*#include "UF_SysParameter.h"
#include "UF_API.h"
#include "UF_Packet.h"
#include "UF_Error.h"
#include "UF_Command.h"
#include "UF_Enroll.h"
#include "stm32f4xx_hal.h"
#include "dht11.h"*/
#define COMPORT0  0
#define COMPORT1  1
#define COMPORT2  2
void Program_Select(void);
int StartProgram(void);
void MainMenu(void);
void Intro(void);
void CommunicationSetupMenu(void);
void CurrentCummunicationSetup(void);
void Commander(void);
void CommunicationSetup(void);
int Connect(void);
int Disconnect(void);
void Reconnect(void);
void ReadSystemParameterSetting(void);
void WaitKey(void);
void BinToHex(unsigned char c , unsigned char *buf);
void BinToHexPacket(unsigned char* inbuf, unsigned char *outbuf, int inbuf_size);
int GetCommandParameterIndex(char* paramName);
int GetStrToInt(char* str);
void SendPacket(unsigned char* data);
void ClearBuffer(void);
void Enroll(void);
void Identify(void);
void Verify(void);
void Delete_all(void);
void SystemParameterSetting(void);
void ChangeSystemParameterSetting(void);
int GetSystemParameterIndex(char* paramName);
