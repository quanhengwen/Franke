#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp32.h"
#include "main.h"
#include "usart.h"
#include "key.h"
#include "lcd.h"
#include "tim.h"
#include "AT24Cxx.h"
#include "key.h"
#include "cmsis_os.h"

/*
	#define AT+CWMODE						//设置Wi-Fi模式 AT+CWMODE=?\r\n  ? = 0,表示无Wi-Fi模式，并且关闭Wi-Fi，1表示Station模式，2表示SoftAp模式，3表示SoftAP+Station模式
	#define AT+CWJAP						//连接AP			 AT+CWJAP=<ssid>,<pwd>
	#define AT+CWLAPORT					//设置AT+CWLAP指令扫描结果的属性
	#define AT+CWLAP						//扫描附近的AP信息			AT+CWLAP :列出当前可用的AP
	#define AT+CWQAP						//与AP断开连接					返回OK
	#define AT+CWSAP						//设置ESP32 SoftAP配置			AT+CWSAP=<ssid>,<pwd>,<chl>,<ecn>\r\n配置Wi-Fi的参数 ,例:AT+CWSAP="ESP32","1234567890","5","3"
	#define AT+CWLIF						//获取连接到ESP32 SoftAP的Station的信息   即查看有啥手机连接到自己的热点了
	#define AT+CWDHCP						//设置DHCP
	#define AT+CWDHCPS					//设置ESP32 SoftAp DHCP分配的IP范围，保存到Flash
	#define AT+CWAUTOCONN				//设置上电是是否自动连接AP 			AT+CWAUTOCONN=<enable> enable:0上电不自动连接AP，1上电自动连接AP
	#define AT+CWSTARTSMART			//开始SmartConfig
	#define AT+CWSTOPSMART			//停止SmartConfig
	#define AT+WPS							//设置WPS功能
	#define AT+CWHOSTNAME				//设置ESP32 station主机名称   AT+CWHOSTNAME="esp32_test"\r\n
	#define AT+MDNS							//MDNS功能
	
	*****************************			BLE 功能与 Wi-Fi 透传无法共存，因此，开启 BLE 功能之前，请确认 Wi-Fi 透传已关闭(AT+CIPMODE=0)			*****************************
*/


/*
	#define AT+BLEINIT					//BLE初始化
	#define AT+BLEADDR					//设置BLE设备地址
	#define AT+BLENAME					//设置BLE设备名称
	#define AT+BLESCANPARM			//设置BLE扫描参数
	#define AT+BLESCAN					//使能BLE扫描
	#define AT+BLESCANRSPDATA		//设置BLE扫描响应
	#define AT+BLEADYPARM				//设置BLE广播参数
	#define AT+BLEADVDATA				//设置BLE广播数据
	#define AT+BLEADVSTART			//开始BLE广播
	#define AT+BLEADVSTOP				//结束BLE广播
	#define AT+BLECONN					//建立BLE连接
	#define AT+BLECONNPARM			//更新BLE连接参数
	#define AT+BLEDISCONN				//断开BLE连接
	#define AT+BLEDATALEN				//设置BLE数据包长度
	#define AT+BLECFGMTU				//设置BLE MTU的长度
	#define AT+BLEGATTSSRVCRE		//GATTS创建服务
	#define AT+BLEGATTSSRVSRART	//GATTS开启服务
	#define AT+BLEGATTSSRVSTOP	//GATTS关闭服务
	#define AT+BLEGATTSSRV			//GATTS查询服务
	#define AT+BLEGATTSCHAR			//GATTS查询服务特征
	#define AT+BLEGATTSNTFY			//GATTS通知服务特征值
	#define AT+BLEGATTSIND			//GATTS指示服务特征值
	#define AT+BLEGATTSSETATTR	//GATTS设置服务特征值
	#define AT+BLEGATTCPRIMSRV	//GATTS发现基本服务
	#define AT+BLEGATTCINCLSRV	//GATTS发现包含服务
	#define AT+BLEGATTCCHAR			//GATTS查询服务特征
	#define AT+BLEGATTCRD				//GATTS读取武夫特征值
	#define AT+BLEGATTCWR				//GATTS写服务特征值
	#define AT+BLESPPCFG				//配置BLESPP
	#define AT+BLESPP						//开启BLESPP
	#define AT+BLESECPARM				//设置BLESMP参数
	#define AT+BLEENC						//开始BLE配对
	#define AT+BLEENCERSP				//设置BLE配对响应
	#define AT+BLEKEYREPLY			//回复BLE配对密钥
	#define AT+BLECONFREPLY			//回复BLE配对结果
	#define AT+BLEENCDEV				//列举已配对的设备
	#define AT+BLEENCCLEAR			//解除绑定
	
	*****************************			BLE 功能与 Wi-Fi 透传无法共存，因此，开启 BLE 功能之前，请确认 Wi-Fi 透传已关闭(AT+CIPMODE=0)			*****************************
*/
//static char aaxx[300] = {0};
//static char bbxx[300] = {0};int16_t St;//LS~US
float St2 = 0.0;
float Hy2 = 0.0;//0.1~25℃
int16_t LS2 = 0;//-55℃~Set
int8_t US2 = 0;//SET~99℃
float ot2 = 0.0;//-9.9~9.9℃
int8_t P22 = 0;
float oE2 = 0.0;//-9.9~9.9℃
int8_t od2 = 0;//0~99分钟
int8_t AC2 = 0;//0~50分钟
int8_t Cy2 = 0;//0~99分钟
int8_t Cn2 = 0;//0~99分钟
int16_t dAd2 = 0;//0~255分钟
uint16_t PA12;
uint16_t PA22;
int8_t CF2 = 0;//℃/℉
int8_t rE2 = 0;
int8_t Ld2 = 0;
int8_t dy2 = 0;
uint8_t d12 = 0;
uint8_t d22 = 0;
int8_t P012 = 0;//语言
char P312[30] = {0};//????
char P322[30] = {0};
int8_t td2 = 0;
int16_t dE2 = 0;//-55~50℃
int8_t id2 = 0;//0~99小时
int8_t Md2 = 0;//0~99分钟
int8_t dd2 = 0;//0~99分钟
int8_t dF2 = 0;//融霜期间的温度显示
int8_t dt2 = 0;//0~99分钟
int8_t dP2 = 0;//上电融霜
int8_t F12 = 0;
int8_t F22 = 0;
int8_t Fd2 = 0;//0~99min
int8_t FS2 = 0;//-55/50℃  -67/99℃
uint8_t FAd2 = 0;//1~50
int8_t Fn2 = 0;//	0/15(min.)
int8_t FF2 = 0;//	0/15(min.)
int16_t dad2 = 0;//0~255分钟
int8_t AU2 = 0;//ALL~99℃
int8_t AL2 = 0;//-55℃~ALU
int8_t Ad2 = 0;//0~99分钟
int8_t dA2 = 0;//0~99分钟
uint8_t P102 = 0;
uint8_t P112 = 0;
uint16_t P132 = 0;
uint16_t P142 = 0;
uint16_t P162 = 0;
uint16_t P172 = 0;
int8_t P182 = 0;
int8_t P192 = 0;
int8_t P202 = 0;
uint8_t P212 = 0;
uint8_t P222 = 0;
uint8_t P232 = 0;
uint8_t P262 = 0;
int8_t P282 = 0;
uint8_t P292 = 0;
uint8_t P302 = 0;
static char connect[200] = {0};
//static uint8_t ssid[16] = "googol-YF";
//static uint8_t pwd[16] = "googoltech123";
static uint8_t Ack = 0;
static uint8_t aack = 0;
static char *Copychar[RX_LEN] = {0};
//int8_t ava = 0;
static uint8_t WiFiFailed = 0;
//static uint8_t BLEFailed = 0;
static char upweight[10] = {0};
//uint8_t BLEStatus = 0;
//uint8_t WIFIStatus = 0;
float send_temp = 0.0;
char recetemp[20] = {0};
static uint16_t receweight = 0;
char receupweight[10] = {0};
char recedrum [10] = {0};
char receout [10] = {0};
char rececom [10] = {0};
char recevap [10] = {0};
char recedef [10] = {0};
uint16_t recelow = 0;
uint16_t recehigh = 0;
uint16_t receeva = 0;
uint16_t receref = 0;
uint16_t recedoor = 0;
uint16_t DC2 = 0;
uint16_t CC2 = 0;
uint16_t SC2 = 0;
uint16_t MC2 = 0;
uint16_t LC2 = 0;
uint16_t DrTQ2 = 0;
uint16_t DTQ2 = 0;
uint16_t FTO2 = 0;
uint16_t DTO2 = 0;
uint16_t CL2 = 0;
uint16_t CP2 = 0;
uint16_t RE2 = 0;
uint16_t P02_P2 = 0;
uint16_t DT_P2 = 0;
uint16_t RT_P2 = 0;
static char *recebijiao[84] = {"a0","a1","a2","a3","a4","a5","a6","a7","a8","a9",
								"b10","b11","b12","b13","b14","b15","b16","b17","b18","b19",
								"c20","c21","c22","c23","c24","c25","c26","c27","c28","c29",
								"d30","d31","d32","d33","d34","d35","d36","d37","d38","d39",
								"e40","e41","e42","e43","e44","e45","e46","e47","e48","e49",
								"f50","f51","f52","f53","f54","f55","f56","f57","f58","f59",
								"g60","g61","g62","g63","g64","g65","g66","g67","g68","g69",
								"h70","h71","h72","h73","h74","h75","h76","h77","h78","h79",
								"i80","i81","i82","i83"};
//59

void ESP32_Test(void)
{
//	if(Up<=10){
//		sprintf(connect,"AT+CWJAP=\"%s\",\"%s\"",ssid,pwd);
//		//Usart3_Printf("%s\r\n",connect);
//	}
//	ESP32_WIFI();
/*	if(Up < 0){
		scanf("%s",aaxx);
		//Usart2_Printf("%s",bbxx);//模块
		Usart3_Printf("%s 长度:%d\r\n",aaxx,strlen((const char*)aaxx));//信息打印
		memset(aaxx,0,sizeof(aaxx));
		osDelay(1000);
		Up = 10;
	}*/
//	if(Up >= 10){
//		if(ava == 0){
////			HAL_UART_Receive_IT(&huart2,(uint8_t *)USART2_Rx_Buf,1024);
////			ava = 1;
//		}
//			osDelay(1000);
//			Usart3_Printf("收到没啊%s\r\n",UsartReceiveType2.RX_pData);
//			//HAL_UART_Receive_IT(&huart2,(uint8_t*)aaxx,sizeof(aaxx));
//	}
	//串口数据收发
	static uint16_t ble4 = 0;
//	static uint16_t receive = 0;
	if(weight == 100){
		sprintf(upweight,"Small");
	}
	else if(weight == 200){
		sprintf(upweight,"Mid");
	}
	else if(weight == 300){
		sprintf(upweight,"Large");
	}
//	ESP32_BLE();
	if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
		if(UsartReceiveType4.RX_flag){
			char* p = 0;
			static int memcmpreturn = 1;
//			char bijiao[20] = {0};
//			sprintf(bijiao,"%s",UsartReceiveType4.RX_pData);
			for(uint8_t i=0;i<84;i++){
				memcmpreturn = memcmp(recebijiao[i],UsartReceiveType4.RX_pData,strlen(recebijiao[i]));
//				if(memcmp(recebijiao[i],UsartReceiveType4.RX_pData,strlen(recebijiao[i])) == 0){
				if(memcmpreturn == 0){
					switch(i){
						case 0:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(recetemp,"%s",p);
							Uart4_Printf("ok");
							//receive = 0;
							i = 84;
							break;
						case 1:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							St2 = atof(p);
							Uart4_Printf("ok");
							//receive = 1;
							i = 84;
							break;
						case 2:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Hy2 = atof(p);
							Uart4_Printf("ok");
							//receive = 2;
							i = 84;
							break;
						case 3:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							receweight = atoi(p);
							Uart4_Printf("ok");
							//receive = 3;
							i = 84;
							break;
						case 4:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(receupweight,"%s",p);
							Uart4_Printf("ok");
							//receive = 4;
							i = 84;
							break;
						case 5:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(recedrum,"%s",p);
							Uart4_Printf("ok");
							//receive = 5;
							i = 84;
							break;
						case 6:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(receout,"%s",p);
							Uart4_Printf("ok");
							//receive = 6;
							i = 84;
							break;
						case 7:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(rececom,"%s",p);
							Uart4_Printf("ok");
							//receive = 7;
							i = 84;
							break;
						case 8:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(recevap,"%s",p);
							Uart4_Printf("ok");
							//receive = 8;
							i = 84;
							break;
						case 9:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(recedef,"%s",p);
							Uart4_Printf("ok");
							//receive = 9;
							i = 84;
							break;
						case 10:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							recehigh = atoi(p);
							Uart4_Printf("ok");
							//receive = 10;
							i = 84;
							break;
						case 11:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							recelow = atoi(p);
							Uart4_Printf("ok");
							//receive = 11;
							i = 84;
							break;
						case 12:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							receeva = atoi(p);
							Uart4_Printf("ok");
							//receive = 12;
							i = 84;
							break;
						case 13:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							receref = atoi(p);
							Uart4_Printf("ok");
							//receive = 13;
							i = 84;
							break;
						case 14:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							recedoor = atoi(p);
							Uart4_Printf("ok");
							//receive = 14;
							i = 84;
							break;
						case 15:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							DC2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 15;
							i = 84;
							break;
						case 16:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							CC2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 16;
							i = 84;
							break;
						case 17:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							SC2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 17;
							i = 84;
							break;
						case 18:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							MC2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 18;
							i = 84;
							break;
						case 19:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							LC2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 19;
							i = 84;
							break;
						case 20:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							DrTQ2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 20;
							i = 84;
							break;
						case 21:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							DTQ2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 21;
							i = 84;
							break;
						case 22:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							FTO2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 22;
							i = 84;
							break;
						case 23:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							DTO2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 23;
							i = 84;
							break;
						case 24:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							CL2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 24;
							i = 84;
							break;
						case 25:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							CP2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 25;
							i = 84;
							break;
						case 26:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							RE2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 26;
							i = 84;
							break;
						case 27:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P02_P2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 27;
							i = 84;
							break;
						case 28:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							DT_P2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 28;
							i = 84;
							break;
						case 29:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							RT_P2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 29;
							i = 84;
							break;
						case 30:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P102 = atoi(p);
							Uart4_Printf("ok");
							//receive = 30;
							i = 84;
							break;
						case 31:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P112 = atoi(p);
							Uart4_Printf("ok");
							//receive = 31;
							i = 84;
							break;
						case 32:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P132 = atoi(p);
							Uart4_Printf("ok");
							//receive = 32;
							i = 84;
							break;
						case 33:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P142 = atoi(p);
							Uart4_Printf("ok");
							//receive = 33;
							i = 84;
							break;
						case 34:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P162 = atoi(p);
							Uart4_Printf("ok");
							//receive = 34;
							i = 84;
							break;
						case 35:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P172 = atoi(p);
							Uart4_Printf("ok");
							//receive = 35;
							i = 84;
							break;
						case 36:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P182 = atoi(p);
							Uart4_Printf("ok");
							//receive = 36;
							i = 84;
							break;
						case 37:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P192 = atoi(p);
							Uart4_Printf("ok");
							//receive = 37;
							i = 84;
							break;
						case 38:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P212 = atoi(p);
							Uart4_Printf("ok");
							//receive = 38;
							i = 84;
							break;
						case 39:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P222 = atoi(p);
							Uart4_Printf("ok");
							//receive = 39;
							i = 84;
							break;
						case 40:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P232 = atoi(p);
							Uart4_Printf("ok");
							//receive = 40;
							i = 84;
							break;
						case 41:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P262 = atoi(p);
							Uart4_Printf("ok");
							//receive = 41;
							i = 84;
							break;
						case 42:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P282 = atoi(p);
							Uart4_Printf("ok");
							//receive = 42;
							i = 84;
							break;
						case 43:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P292 = atoi(p);
							Uart4_Printf("ok");
							//receive = 43;
							i = 84;
							break;
						case 44:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P302 = atoi(p);
							Uart4_Printf("ok");
							//receive = 44;
							i = 84;
							break;
						case 45:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							LS2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 45;
							i = 84;
							break;
						case 46:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							US2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 46;
							i = 84;
							break;
						case 47:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							ot2 = atof(p);
							Uart4_Printf("ok");
							//receive = 47;
							i = 84;
							break;
						case 48:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P22 = atoi(p);
							Uart4_Printf("ok");
							//receive = 48;
							i = 84;
							break;
						case 49:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							oE2 = atof(p);
							Uart4_Printf("ok");
							//receive = 49;
							i = 84;
							break;
						case 50:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							od2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 50;
							i = 84;
							break;
						case 51:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							AC2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 51;
							i = 84;
							break;
						case 52:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Cy2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 52;
							i = 84;
							break;
						case 53:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Cn2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 53;
							i = 84;
							break;
						case 54:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dAd2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 54;
							i = 84;
							break;
						case 55:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							PA12 = atoi(p);
							Uart4_Printf("ok");
							//receive = 55;
							i = 84;
							break;
						case 56:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							PA22 = atoi(p);
							Uart4_Printf("ok");
							//receive = 56;
							i = 84;
							break;
						case 57:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							CF2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 57;
							i = 84;
							break;
						case 58:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							rE2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 58;
							i = 84;
							break;
						case 59:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Ld2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 59;
							i = 84;
							break;
						case 60:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dy2 = atoi(p);
							Uart4_Printf("ok");
							//receive = 60;
							i = 84;
							break;
						case 61:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							d12 = atoi(p);
							Uart4_Printf("ok");
							//receive = 61;
							i = 84;
							break;
						case 62:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							d22 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 63:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							P012 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 64:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(P312,"%s",p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 65:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							sprintf(P322,"%s",p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 66:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							td2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 67:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dE2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 68:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							id2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 69:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Md2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 70:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dd2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 71:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dF2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 72:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dt2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 73:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dP2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 74:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Fd2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 75:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							FS2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 76:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							FAd2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
						case 77:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Fn2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 78:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							FF2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 79:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dad2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 80:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							AU2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 81:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							AL2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
						case 82:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							Ad2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							break;
						case 83:
							p = strtok((char*)UsartReceiveType4.RX_pData,":");
							p = strtok(NULL,":");
							dA2 = atoi(p);
							Uart4_Printf("ok");
							//receive = i;
							i = 84;
							break;
					}
				}
				else{
					if(i == 84)
						memset(UsartReceiveType4.RX_pData,0,sizeof(UsartReceiveType4.RX_pData));
				}
//				StringCompare((char *)UsartReceiveType2.RX_pData);
			}
			memset(UsartReceiveType4.RX_pData,0,sizeof(UsartReceiveType4.RX_pData));
			UsartReceiveType4.RX_flag = 0;
		}
		else
			ESP32_BLE();
	}
	else{
		static TIME sendtime;
		static uint8_t bsendtime = true;
		static uint32_t sendtimes = 0;
		sendtimes = GetDiffTime(&sendtime,&bsendtime);
		char aaxa[30] = {0};
		if(sendtimes >= 10){
			if(UsartReceiveType4.RX_flag){
				if(memcmp(UsartReceiveType4.RX_pData, "ok",2) == 0){
					ble4++;
					if(ble4 > 83)
						ble4 = 0;
					memset(UsartReceiveType4.RX_pData,0,sizeof(UsartReceiveType4.RX_pData));
				}
				else{
					StringCompare_s((char*)UsartReceiveType4.RX_pData);
					memset(UsartReceiveType4.RX_pData,0,sizeof(UsartReceiveType4.RX_pData));
				}
			}
			switch(ble4){
				//辅机
				case 0:
					if(factdis.Ld){
						if(custdis.CF)
							sprintf(aaxa,"a%d:%d F",ble4,Vapor_T_HSD);
						else if(custdis.CF == 0 && custdis.rE == 0)
							sprintf(aaxa,"a%d:%.1f C",ble4,Vapor_T);
						else
							sprintf(aaxa,"a%d:%.0f C",ble4,Vapor_T);
					}
					else{
						if(custdis.CF)
							sprintf(aaxa,"a%d:%d F",ble4,Case_T_HSD);
						else if(custdis.CF == 0 && custdis.rE == 0)
							sprintf(aaxa,"a%d:%.1f C",ble4,Case_T);
						else
							sprintf(aaxa,"a%d:%.0f C",ble4,Case_T);
					}
					break;
				case 1:
					sprintf(aaxa,"a%d:%d",ble4,custcp.St);
					break;
				case 2:
					sprintf(aaxa,"a%d:%.1f",ble4,custcp.Hy);
					break;
				case 3:
					if(weight == 100)
						sprintf(aaxa,"a%d:%.0f",ble4,(float)((factdsp.P30 * custvs.CL) / 100));
					else if(weight == 200)
						sprintf(aaxa,"a%d:%.0f",ble4,(float)((factdsp.P29 * custvs.CL) / 100));
					else if(weight == 300)
						sprintf(aaxa,"a%d:%d",ble4,custvs.CL);
					break;
				case 4:
					sprintf(aaxa,"a%d:%s",ble4,upweight);
					break;
				case 5:
					if(HAL_GPIO_ReadPin(Drum_motor_en_GPIO_Port,Drum_motor_en_Pin) == 0)
						sprintf(aaxa,"a%d:Close",ble4);
					else
						sprintf(aaxa,"a%d:Open",ble4);
					break;
				case 6:
					if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin) == 0)
						sprintf(aaxa,"a%d:Close",ble4);
					else
						sprintf(aaxa,"a%d:Open",ble4);
					break;
				case 7:
					if(HAL_GPIO_ReadPin(Compressor_Relay_GPIO_Port,Compressor_Relay_Pin))
						sprintf(aaxa,"a%d:Open",ble4);
					else
						sprintf(aaxa,"a%d:Close",ble4);
					break;
				case 8:
					if(HAL_GPIO_ReadPin(Vaporization_Relay_GPIO_Port,Vaporization_Relay_Pin))
						sprintf(aaxa,"a%d:Run",ble4);
					else
						sprintf(aaxa,"a%d:Stop",ble4);
					break;
				case 9:
					if(HAL_GPIO_ReadPin(Defrosting_Relay_GPIO_Port,Defrosting_Relay_Pin))
						sprintf(aaxa,"a%d:Run",ble4);
					else
						sprintf(aaxa,"a%d:Stop",ble4);
					break;
				case 10:
					sprintf(aaxa,"b%d:%d",ble4,Record_High_Temp);
					break;
				case 11:
					sprintf(aaxa,"b%d:%d",ble4,Record_Low_Temp);
					break;
				case 12:
					sprintf(aaxa,"b%d:%d",ble4,Record_Evap_Probe_alarm);
					break;
				case 13:
					sprintf(aaxa,"b%d:%d",ble4,Record_Refri_Probe_alarm);
					break;
				case 14:
					sprintf(aaxa,"b%d:%d",ble4,Record_Door_Opening_alarm);
					break;
				case 15:
					sprintf(aaxa,"b%d:%d",ble4,custvs.DC);
					break;
				case 16:
					sprintf(aaxa,"b%d:%d",ble4,custvs.CC);
					break;
				case 17:
					sprintf(aaxa,"b%d:%d",ble4,custvs.SC);
					break;
				case 18:
					sprintf(aaxa,"b%d:%d",ble4,custvs.MC);
					break;
				case 19:
					sprintf(aaxa,"b%d:%d",ble4,custvs.LC);
					break;
				case 20:
					sprintf(aaxa,"c%d:%d",ble4,custvs.DrTQ);
					break;
				case 21:
					sprintf(aaxa,"c%d:%d",ble4,custvs.DTQ);
					break;
				case 22:
					sprintf(aaxa,"c%d:%d",ble4,custvs.FTO);
					break;
				case 23:
					sprintf(aaxa,"c%d:%d",ble4,custvs.DTO);
					break;
				case 24:
					sprintf(aaxa,"c%d:%d",ble4,custvs.CL);
					break;
				case 25:
					sprintf(aaxa,"c%d:%d",ble4,custvs.CP);
					break;
				case 26:
					sprintf(aaxa,"c%d:Reset",ble4);
					break;
				case 27:
					sprintf(aaxa,"c%d:%d",ble4,custdsp.P02_P);
					break;
				case 28:
					sprintf(aaxa,"c%d:%d",ble4,custdsp.DT_P);
					break;
				case 29:
					sprintf(aaxa,"c%d:%d",ble4,custdsp.RT_P);
					break;
				case 30:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P10);
					break;
				case 31:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P11);
					break;
				case 32:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P13);
					break;
				case 33:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P14);
					break;
				case 34:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P16);
					break;
				case 35:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P17);
					break;
				case 36:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P18);
					break;
				case 37:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P19);
					break;
				case 38:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P21);
					break;
				case 39:
					sprintf(aaxa,"d%d:%d",ble4,factdsp.P22);
					break;
				case 40:
					sprintf(aaxa,"e%d:%d",ble4,factdsp.P23);
					break;
				case 41:
					sprintf(aaxa,"e%d:%d",ble4,factdsp.P26);
					break;
				case 42:
					sprintf(aaxa,"e%d:%d",ble4,factdsp.P28);
					break;
				case 43:
					sprintf(aaxa,"e%d:%d",ble4,factdsp.P29);
					break;
				case 44:
					sprintf(aaxa,"e%d:%d",ble4,factdsp.P30);
					break;
				/*case 45:
					sprintf(aaxa,"e%d:%d",ble4,custvs.DC);
					break;
				case 46:
					sprintf(aaxa,"e%d:%d",ble4,custvs.CC);
					break;
				case 47:
					sprintf(aaxa,"e%d:%d",ble4,custvs.SC);
					break;
				case 48:
					sprintf(aaxa,"e%d:%d",ble4,custvs.MC);
					break;
				case 49:
					sprintf(aaxa,"e%d:%d",ble4,custvs.LC);
					break;
				case 50:
					sprintf(aaxa,"e%d:%d",ble4,custvs.DrTQ);
					break;
				case 51:
					sprintf(aaxa,"e%d:%d",ble4,custvs.DTQ);
					break;
				case 52:
					sprintf(aaxa,"e%d:%d",ble4,custvs.FTO);
					break;
				case 53:
					sprintf(aaxa,"e%d:%d",ble4,custvs.DTO);
					break;
				case 54:
					sprintf(aaxa,"e%d:%d",ble4,custvs.CL);
					break;
				case 55:
					sprintf(aaxa,"e%d:%d",ble4,custvs.CP);
					break;
				case 56:
					sprintf(aaxa,"e%d:%d F",ble4,custcp.St);		//用户具有
					break;
				case 57:
					sprintf(aaxa,"e%d:%.1f F",ble4,custcp.Hy);	//用户具有
					break;*/
				case 45:
					sprintf(aaxa,"e%d:%d",ble4,factcp.LS);
					break;
				case 46:
					sprintf(aaxa,"e%d:%d",ble4,factcp.US);
					break;
				case 47:
					sprintf(aaxa,"e%d:%.1f",ble4,custcp.ot);		//用户具有
					break;
				case 48:
					sprintf(aaxa,"e%d:%d",ble4,custcp.p2);	//用户具有
					break;
				case 49:
					sprintf(aaxa,"e%d:%.1f",ble4,factcp.oE);
					break;
				case 50:
					sprintf(aaxa,"f%d:%d",ble4,factcp.od);
					break;
				case 51:
					sprintf(aaxa,"f%d:%d",ble4,custcp.AC);	//用户具有
					break;
				case 52:
					sprintf(aaxa,"f%d:%d",ble4,factcp.Cy);
					break;
				case 53:
					sprintf(aaxa,"f%d:%d",ble4,factcp.Cn);
					break;
				case 54:
					sprintf(aaxa,"f%d:%d",ble4,factcp.dAd);
					break;
				case 55:
					sprintf(aaxa,"f%d:%d",ble4,factdis.PA1);
					break;
				case 56:
					sprintf(aaxa,"f%d:%d",ble4,factdis.PA2);
					break;
				case 57:
					sprintf(aaxa,"f%d,%d",ble4,custdis.CF);	//用户具有
					break;
				case 58:
					sprintf(aaxa,"f%d,%d",ble4,custdis.rE);	//用户具有
					break;
				case 59:
					sprintf(aaxa,"f%d,%d",ble4,factdis.Ld);
					break;
				case 60:
					sprintf(aaxa,"g%d:%d",ble4,factdis.dy);
					break;
				case 61:
					sprintf(aaxa,"g%d:%d",ble4,custdis.d1);	//用户具有
					break;
				case 62:
					sprintf(aaxa,"g%d:%d",ble4,custdis.d2);	//用户具有
					break;
				case 63:
					sprintf(aaxa,"g%d:%d",ble4,custdis.P01);	//用户具有
					break;
				case 64:
					sprintf(aaxa,"g%d:%s",ble4,factdis.P31);
					break;
				case 65:
					sprintf(aaxa,"g%d:%s",ble4,factdis.P32);
					break;
				case 66:
					sprintf(aaxa,"g%d:%d",ble4,factdef.td);
					break;
				case 67:
					sprintf(aaxa,"g%d:%d",ble4,custdef.dE);	//用户具有
					break;
				case 68:
					sprintf(aaxa,"g%d:%d",ble4,custdef.id);	//用户具有
					break;
				case 69:
					sprintf(aaxa,"g%d:%d",ble4,custdef.Md);	//用户具有
					break;
				case 70:
					sprintf(aaxa,"h%d:%d",ble4,factdef.dd);
					break;
				case 71:
					sprintf(aaxa,"h%d:%d",ble4,factdef.dF);
					break;
				case 72:
					sprintf(aaxa,"h%d:%d",ble4,factdef.dt);
					break;
				case 73:
					sprintf(aaxa,"h%d:%d",ble4,factdef.dP);
					break;
				case 74:
					sprintf(aaxa,"h%d:%d",ble4,custfan.Fd); //用户具有
					break;
				case 75:
					sprintf(aaxa,"h%d:%d",ble4,factfan.FS);
					break;
				case 76:
					sprintf(aaxa,"h%d:%d",ble4,factfan.FAd);
					break;
				case 77:
					sprintf(aaxa,"h%d:%d",ble4,custfan.Fn);	//用户具有
					break;
				case 78:
					sprintf(aaxa,"h%d:%d",ble4,custfan.FF); // 用户具有
					break;
				case 79:
					sprintf(aaxa,"h%d:%d",ble4,factfan.dAd);
					break;
				case 80:
					sprintf(aaxa,"i%d:%d",ble4,custal.AU);
					break;
				case 81:
					sprintf(aaxa,"i%d:%d F",ble4,custal.AL);
					break;
				case 82:
					sprintf(aaxa,"i%d:%d",ble4,factal.Ad);
					break;
				case 83:
					sprintf(aaxa,"i%d:%d",ble4,factal.dA);
					break;
			}
			Uart4_Printf("%s",aaxa);
			osDelay(500);
		}
	}
}


void ESP32_WIFI(void)
{
	char *strx = 0;
	if(Up >= 50 && Up <= 70){
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		
//		Usart2_Printf("ATE1\r\n");//关闭回显
//		osDelay(1000);
//		Usart3_Printf("回显功能:%s\r\n",UsartReceiveType2.RX_pData);
		
		//第一步：响应OK
		Usart2_Printf("AT+CWMODE=3\r\n");
		osDelay(1000);
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数1：%d响应ack：%s\r\n",strx,__LINE__);
			}
		}
		Usart3_Printf("输出---%s\r\n",Copychar);//信息打印
		Usart3_Printf("%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		
		//第二步：响应OK
		Usart2_Printf("%s\r\n",connect);
		osDelay(5000);
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数2：%d响应ack：%s\r\n",strx,__LINE__);
			}
		}
		Usart3_Printf("输出---%s\r\n",Copychar);//信息打印
		Usart3_Printf("%s\r\n",UsartReceiveType2.RX_pData);
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		
//		osDelay(2000);
//		Usart2_Printf("AT+CIFSR\r\n");
//		osDelay(1000);
//		Usart3_Printf("%s查询设备ip地址\r\n",aaxx);
		
		osDelay(2000);
		//第三步：响应OK
		Usart2_Printf("AT+CIPSTART=\"TCP\",\"192.168.20.200\",8080\r\n");
		osDelay(5000);
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数3：%d响应ack：%s\r\n",strx,__LINE__);
			}
		}
		Usart3_Printf("输出---%s\r\n",Copychar);//信息打印
		Usart3_Printf("%s\r\n",UsartReceiveType2.RX_pData);
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		
		//第四步：响应OK
		Usart2_Printf("AT+CIPMODE=1\r\n");
		osDelay(1000);
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				aack++;
				Usart3_Printf("响应成功，行数4：%d响应ack：%s\r\n",strx,__LINE__);
			}
		}
		Usart3_Printf("输出---%s\r\n",Copychar);//信息打印
		Usart3_Printf("%s\r\n",UsartReceiveType2.RX_pData);
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		
		//第五步：响应OK
		Usart2_Printf("AT+CIPSEND\r\n");
		osDelay(1000);
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				aack++;
				Usart3_Printf("响应成功，行数5：%d响应ack：%s\r\n",strx,__LINE__);
			}
		}
		Usart3_Printf("输出---%s\r\n",Copychar);//信息打印
		Usart3_Printf("%s\r\n",UsartReceiveType2.RX_pData);
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		if(Ack >= 5 || aack >= 2){
			Ack =0;
			Up = 71;
			Usart3_Printf("WiFi成功\r\n");
		}
		else{
			Ack = 0;
			WiFiFailed++;
			Usart3_Printf("WiFi失败\r\n");
			if(WiFiFailed >= 5){
				WiFiFailed = 0;
				Usart2_Printf("+++");
				osDelay(2000);
				Usart2_Printf("AT+RST\r\n");
				osDelay(5000);
			}
		}
	}
	else if(Up == 71){
//			WIFIStatus = 1;
			if(UsartReceiveType2.RX_flag)
			{
				for(int i=0; i<RX_LEN;i++)
					Copychar[i] = UsartReceiveType2.RX_pData[i];
				//SMALL
				if(memcmp(UsartReceiveType2.RX_pData,"Small",5) == 0){
						weight = 100;
				}
				//MID
				if(memcmp(UsartReceiveType2.RX_pData,"Mid",3) == 0){
						weight = 200;
				}
				//Large_Set
				if(memcmp(UsartReceiveType2.RX_pData,"Large",5) == 0){
						weight = 300;
				}
				//UP
				if(memcmp(UsartReceiveType2.RX_pData,"Up",2) == 0){
					
				}
				//DOWN
				if(memcmp(UsartReceiveType2.RX_pData,"Down",4) == 0){
					
				}
				//下料判断
				if(memcmp(UsartReceiveType2.RX_pData,"Run",3) == 0){
						Standby = 310;
				}
				//+++退出兰塔透传
				if(memcmp(UsartReceiveType2.RX_pData,"+++",3) == 0){
//						WIFIStatus = 0;
						Usart2_Printf("+++");
						osDelay(1000);
						Usart2_Printf("AT+CIPMODE=0\r\n");
						osDelay(1000);
						Usart3_Printf("退出透传模式\r\n");
						Down = 50;
						Up = 0;
						UsartReceiveType2.RX_flag = 0;
						memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
						memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
						return;
				}
				Usart2_Printf("Fan_Run_Mode1：%d\r\nFan_Run_Mode2：%d\r\nFan_Start_Delay：%d\r\nFan_Start_Time：%d\r\nFan_Stop_Time：%d\r\n",custfan.F1, custfan.F2, custfan.Fd, custfan.Fn, custfan.FF);
				Usart3_Printf("111%s  长度%d\r\n",UsartReceiveType2.RX_pData,strlen((char *)UsartReceiveType2.RX_pData));
				Usart3_Printf("222%s\r\n",Copychar);
				StringCompare((char *)UsartReceiveType2.RX_pData);
				UsartReceiveType2.RX_flag = 0;
				memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
				memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
			}
			osDelay(1000);
	}
}

void ESP32_BLE(void)
{
	char *strx = 0;
	
	if(Down >=1 && Down <= 50){
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		//第一步：关闭WIFI
//		Usart2_Printf("AT+CWMODE=0\r\n");
//		osDelay(1000);
//		if(UsartReceiveType2.RX_flag){
//			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
//			if(memcmp(strx,"OK",2) == 0){
//				Ack++;
//				Usart3_Printf("蓝牙响应成功，行数1：%d响应ack：%s\r\n",strx,__LINE__);
//			}
//		}
//		Usart3_Printf("%s\r\n",UsartReceiveType2.RX_pData);//信息打印
//		UsartReceiveType2.RX_flag = 0;
//		strx = 0;
//		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		
		
		//第1步：蓝牙初始化成服务端
		Usart2_Printf("AT+BLEINIT=2\r\n");
		osDelay(2000);
		for(int i=0; i<RX_LEN;i++)
			Copychar[i] = UsartReceiveType2.RX_pData[i];
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("蓝牙响应成功，行数1响应ack：%s\r\n",strx);
			}
		}
		Usart3_Printf("输出1---%s\r\n",Copychar);//信息打印
		Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
		
		
		//第2步：蓝牙改名
		Usart2_Printf("AT+BLENAME=\"BLE_NW\"\r\n");
		osDelay(2000);
		for(int i=0; i<RX_LEN;i++)
			Copychar[i] = UsartReceiveType2.RX_pData[i];
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数2响应ack：%s\r\n",strx);
			}
		}
		Usart3_Printf("输出2---%s\r\n",Copychar);//信息打印
		Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
		
		
		//第3步：配置广播参数
		Usart2_Printf("AT+BLEADVDATA=\"02010607094672616E6B6506FFE502434847030302A003174103\"\r\n");
		osDelay(2000);
		for(int i=0; i<RX_LEN;i++)
			Copychar[i] = UsartReceiveType2.RX_pData[i];
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数3响应ack：%s\r\n",strx);
			}
		}
		Usart3_Printf("输出3---%s\r\n",Copychar);//信息打印
		Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
		
		
		//第4步：创建服务
		Usart2_Printf("AT+BLEGATTSSRVCRE\r\n");
		osDelay(2000);
		for(int i=0; i<RX_LEN;i++)
			Copychar[i] = UsartReceiveType2.RX_pData[i];
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数4响应ack：%s\r\n",strx);
			}
		}
		Usart3_Printf("输出4---%s\r\n",Copychar);//信息打印
		Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
		
		
		//第5步：开启服务
		Usart2_Printf("AT+BLEGATTSSRVSTART\r\n");
		osDelay(2000);
		for(int i=0; i<RX_LEN;i++)
			Copychar[i] = UsartReceiveType2.RX_pData[i];
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数5响应ack：%s\r\n",strx);
			}
		}
		Usart3_Printf("输出5---%s\r\n",Copychar);//信息打印
		Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
		
		//第4步：查询服务特征
//		Usart2_Printf("AT+BLEGATTSCHAR?\r\n");
//		osDelay(2000);
//		if(UsartReceiveType2.RX_flag){
//			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
//			if(memcmp(strx,"OK",2) == 0){
//				Ack++;
//				Usart3_Printf("响应成功，行数5：%d响应ack：%s\r\n",strx,__LINE__);
//			}
//		}
//		Usart3_Printf("输出5---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
//		UsartReceiveType2.RX_flag = 0;
//		strx = 0;
//		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));

		
		//第6步：广播开启
		Usart2_Printf("AT+BLEADVSTART\r\n");
		osDelay(2000);
		for(int i=0; i<RX_LEN;i++)
			Copychar[i] = UsartReceiveType2.RX_pData[i];
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("响应成功，行数6响应ack：%s\r\n",strx);
			}
		}
		Usart3_Printf("输出6---%s\r\n",Copychar);//信息打印
		Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
	
		
		Usart2_Printf("AT\r\n");
		osDelay(2000);
		for(int i=0; i<RX_LEN;i++)
			Copychar[i] = UsartReceiveType2.RX_pData[i];
		if(UsartReceiveType2.RX_flag){
			strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
			if(memcmp(strx,"OK",2) == 0){
				Ack++;
				Usart3_Printf("at响应成功，行数7响应ack：%s\r\n",strx);
			}
		}
		Usart3_Printf("at输出6---%s\r\n",Copychar);//信息打印
		Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
		UsartReceiveType2.RX_flag = 0;
		strx = 0;
		memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
		memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
		Down = 51;
	}
	
	else if(Down > 50 && Down <= 70){
			if(UsartReceiveType2.RX_flag){
				while(1){
					//第7步：选择通道
					Usart2_Printf("AT+BLESPPCFG=1,1,7,1,5\r\n");
					osDelay(2000);
					for(int i=0; i<RX_LEN;i++)
						Copychar[i] = UsartReceiveType2.RX_pData[i];
					if(UsartReceiveType2.RX_flag){
						strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
						if(memcmp(strx,"OK",2) == 0){
							Ack++;
							Usart3_Printf("响应成功，行数7：%d响应ack：%s\r\n",strx,__LINE__);
						}
					}
					Usart3_Printf("输出7---%s\r\n",Copychar);//信息打印
					Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
					UsartReceiveType2.RX_flag = 0;
					strx = 0;
					memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
					memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
					
					osDelay(10000);
					
					//第8步：开启透传模式
					Usart2_Printf("AT+BLESPP\r\n");
					osDelay(2000);
					for(int i=0; i<RX_LEN;i++)
						Copychar[i] = UsartReceiveType2.RX_pData[i];				
					if(UsartReceiveType2.RX_flag){
						strx = strstr((const char *)UsartReceiveType2.RX_pData, "OK");
						if(memcmp(strx,"OK",2) == 0){
							Ack++;
							Usart3_Printf("响应成功，行数8：%d响应ack：%s\r\n",strx,__LINE__);
						}
					}
					Usart3_Printf("输出8---%s\r\n",Copychar);//信息打印
					Usart3_Printf("输出---%s\r\n",UsartReceiveType2.RX_pData);//信息打印
					UsartReceiveType2.RX_flag = 0;
					strx = 0;
					memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
					memset(UsartReceiveType2.RX_pData,0,sizeof(Copychar));
					
					if(Ack >= 5){
						Ack = 0;
						Down = 71;
						Usart3_Printf("蓝牙成功\r\n");
					}
					else{
						Ack = 0;
						Usart3_Printf("蓝牙失败\r\n");
					}
					break;
				}
			}
			else{
				Usart3_Printf("等待蓝牙连接\r\n");
				osDelay(1000);
			}
	}
	else if(Down == 71){
			if(UsartReceiveType2.RX_flag)
			{
				/*for(int i=0; i<RX_LEN;i++)
					Copychar[i] = UsartReceiveType2.RX_pData[i];
				
				//SMALL
				if(memcmp(UsartReceiveType2.RX_pData,"Small",5) == 0){
						weight = 100;
						Usart2_Printf("Received：Small\r\n");
				}
				//MID
				else if(memcmp(UsartReceiveType2.RX_pData,"Mid",3) == 0){
						weight = 200;
						Usart2_Printf("Received：Mid\r\n");
				}
				//Large_Set
				else if(memcmp(UsartReceiveType2.RX_pData,"Large",5) == 0){
						weight = 300;
						Usart2_Printf("Received：Large_Set\r\n");
				}
				//UP
				else if(memcmp(UsartReceiveType2.RX_pData,"Up",2) == 0){
					
				}
				//DOWN
				else if(memcmp(UsartReceiveType2.RX_pData,"Down",4) == 0){
					
				}
				//下料判断
				else if(memcmp(UsartReceiveType2.RX_pData,"Run",3) == 0){
						Standby = 310;
						Scan();
				}
				//+++退出兰塔透传
				else if(memcmp(UsartReceiveType2.RX_pData,"+++",3) == 0){
						BLEStatus = 0;
						Usart2_Printf("+++");
						osDelay(1000);
						Usart2_Printf("AT+BLEINIT=0\r\n");
						osDelay(1000);
						Usart3_Printf("退出透传模式\r\n");
						Up = 50;
						Down = 0;
						UsartReceiveType2.RX_flag = 0;
						memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
						memset(Copychar,0,sizeof(Copychar));
						return;
				}
				//Usart2_Printf("Fan_Run_Mode1：%d\r\nFan_Run_Mode2：%d\r\nFan_Start_Delay：%d\r\nFan_Start_Time：%d\r\nFan_Stop_Time：%d\r\n",custfan.F1, custfan.F2, custfan.Fd, custfan.Fn, custfan.FF);
				Usart3_Printf("嘻嘻嘻%s\r\n",UsartReceiveType2.RX_pData);
				Usart3_Printf("哈哈哈%s\r\n",Copychar);*/
				StringCompare((char *)UsartReceiveType2.RX_pData);
				UsartReceiveType2.RX_flag = 0;
				memset(UsartReceiveType2.RX_pData,0,sizeof(UsartReceiveType2.RX_pData));
				memset(Copychar,0,sizeof(Copychar));
			}
			//sprintf(upload,"Temp:26 C,\r\nTemp_Setting:%d C,\r\nDiff_Temp:%d C,\r\nweight:%dg,\r\nallocation:%s,\r\nLar_cal_val:%dg,\r\nNo_Load_val:%dg,\r\n",custcp.St,custcp.Hy,weight,upweight,custvs.CL,custvs.CP);
			//sprintf(upload,"{\"Temp\":\"26\",\"Temp_Setting\":\"%d\",\"Diff_Temp\":\"%d\",\"weight\":\"%d\",\"allocation\":\"%s\",\"Lar_cal_val\":\"%d\",\"No_Load_val\":\"%d\"}",
			//									custcp.St,custcp.Hy,weight,upweight,custvs.CL,custvs.CP);
			//Usart3_Printf("%s\r\n",upload);
			//Usart2_Printf("%s\r\n",upload);
			static uint16_t blesend = 0;
			Send_Data(weight,blesend);
			blesend++;
			if(blesend > 197)
				blesend = 0;
			//osDelay(2000);
	}
}

void Send_Data(int16_t weight,uint16_t i)
{
//	BLEStatus = 1;
	//for(int i=0;i<198;i++){
		char aaxa[30] = {0};
		//sprintf(aaxa,"%d:%d",i,custcp.St);
		switch(i)
		{
			case 0:
				if(factdis.Ld){
					if(custdis.CF)
						sprintf(aaxa,"0%d:%d F",i+1,Vapor_T_HSD);
					else if(custdis.CF == 0 && custdis.rE == 0)
						sprintf(aaxa,"0%d:%.1f C",i+1,Vapor_T);
					else
						sprintf(aaxa,"0%d:%.0f C",i+1,Vapor_T);
				}
				else{
					if(custdis.CF)
						sprintf(aaxa,"0%d:%d F",i+1,Case_T_HSD);
					else if(custdis.CF == 0 && custdis.rE == 0)
						sprintf(aaxa,"0%d:%.1f C",i+1,Case_T);
					else
						sprintf(aaxa,"0%d:%.0f C",i+1,Case_T);
				}
				break;
			case 1:
				sprintf(aaxa,"0%d:%d F",i+1,custcp.St);
				break;
			case 2:
				sprintf(aaxa,"0%d:%.1f F",i+1,custcp.Hy);
				break;
			case 3:
				if(weight == 100)
					sprintf(aaxa,"0%d:%.0fg",i+1,(float)((factdsp.P30 * custvs.CL) / 100));
				else if(weight == 200)
					sprintf(aaxa,"0%d:%.0fg",i+1,(float)((factdsp.P29 * custvs.CL) / 100));
				else if(weight == 300)
					sprintf(aaxa,"0%d:%dg",i+1,custvs.CL);
				break;
			case 4:
				sprintf(aaxa,"0%d:%s",i+1,upweight);
				break;
			case 5:
				if(HAL_GPIO_ReadPin(Drum_motor_en_GPIO_Port,Drum_motor_en_Pin) == 0)
					sprintf(aaxa,"0%d:Close",i+1);
				else
					sprintf(aaxa,"0%d:Open",i+1);
				break;
			case 6:
				if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin) == 0)
					sprintf(aaxa,"0%d:Close",i+1);
				else
					sprintf(aaxa,"0%d:Open",i+1);
				break;
			case 7:
				if(HAL_GPIO_ReadPin(Compressor_Relay_GPIO_Port,Compressor_Relay_Pin))
					sprintf(aaxa,"0%d:Open",i+1);
				else
					sprintf(aaxa,"0%d:Close",i+1);
				break;
			case 8:
				if(HAL_GPIO_ReadPin(Vaporization_Relay_GPIO_Port,Vaporization_Relay_Pin))
					sprintf(aaxa,"0%d:Run",i+1);
				else
					sprintf(aaxa,"0%d:Stop",i+1);
				break;
			case 9:
				if(HAL_GPIO_ReadPin(Defrosting_Relay_GPIO_Port,Defrosting_Relay_Pin))
					sprintf(aaxa,"%d:Run",i+1);
				else
					sprintf(aaxa,"%d:Stop",i+1);
				break;
			case 10:
				sprintf(aaxa,"%d:%d",i+1,Record_High_Temp);
				break;
			case 11:
				sprintf(aaxa,"%d:%d",i+1,Record_Low_Temp);
				break;
			case 12:
				sprintf(aaxa,"%d:%d",i+1,Record_Evap_Probe_alarm);
				break;
			case 13:
				sprintf(aaxa,"%d:%d",i+1,Record_Refri_Probe_alarm);
				break;
			case 14:
				sprintf(aaxa,"%d:%d",i+1,Record_Door_Opening_alarm);
				break;
			case 15:
				sprintf(aaxa,"%d:%d",i+1,custvs.DC);
				break;
			case 16:
				sprintf(aaxa,"%d:%d",i+1,custvs.CC);
				break;
			case 17:
				sprintf(aaxa,"%d:%d",i+1,custvs.SC);
				break;
			case 18:
				sprintf(aaxa,"%d:%d",i+1,custvs.MC);
				break;
			case 19:
				sprintf(aaxa,"%d:%d",i+1,custvs.LC);
				break;
			case 20:
				sprintf(aaxa,"%d:%d",i+1,custvs.DrTQ);
				break;
			case 21:
				sprintf(aaxa,"%d:%d",i+1,custvs.DTQ);
				break;
			case 22:
				sprintf(aaxa,"%d:%d",i+1,custvs.FTO);
				break;
			case 23:
				sprintf(aaxa,"%d:%d",i+1,custvs.DTO);
				break;
			case 24:
				sprintf(aaxa,"%d:%d",i+1,custvs.CL);
				break;
			case 25:
				sprintf(aaxa,"%d:%d",i+1,custvs.CP);
				break;
			case 26:
				sprintf(aaxa,"%d:Reset",i+1);
				break;
			case 27:
				sprintf(aaxa,"%d:%d",i+1,custdsp.P02_P);
				break;
			case 28:
				sprintf(aaxa,"%d:%d",i+1,custdsp.DT_P);
				break;
			case 29:
				sprintf(aaxa,"%d:%d",i+1,custdsp.RT_P);
				break;
			case 30:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P10);
				break;
			case 31:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P11);
				break;
			case 32:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P13);
				break;
			case 33:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P14);
				break;
			case 34:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P16);
				break;
			case 35:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P17);
				break;
			case 36:
				if(factdsp.P18)
					sprintf(aaxa,"%d:On",i+1);
				else
					sprintf(aaxa,"%d:Off",i+1);
				break;
			case 37:
				if(factdsp.P19)
					sprintf(aaxa,"%d:On",i+1);
				else
					sprintf(aaxa,"%d:Off",i+1);
				break;
			case 38:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P21);
				break;
			case 39:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P22);
				break;
			case 40:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P23);
				break;
			case 41:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P26);
				break;
			case 42:
				if(factdsp.P28)
					sprintf(aaxa,"%d:Numerica",i+1);
				else
					sprintf(aaxa,"%d:English",i+1);
				break;
			case 43:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P29);
				break;
			case 44:
				sprintf(aaxa,"%d:%d",i+1,factdsp.P30);
				break;
			case 45:
				sprintf(aaxa,"%d:%d",i+1,custvs.DC);
				break;
			case 46:
				sprintf(aaxa,"%d:%d",i+1,custvs.CC);
				break;
			case 47:
				sprintf(aaxa,"%d:%d",i+1,custvs.SC);
				break;
			case 48:
				sprintf(aaxa,"%d:%d",i+1,custvs.MC);
				break;
			case 49:
				sprintf(aaxa,"%d:%d",i+1,custvs.LC);
				break;
			case 50:
				sprintf(aaxa,"%d:%d",i+1,custvs.DrTQ);
				break;
			case 51:
				sprintf(aaxa,"%d:%d",i+1,custvs.DTQ);
				break;
			case 52:
				sprintf(aaxa,"%d:%d",i+1,custvs.FTO);
				break;
			case 53:
				sprintf(aaxa,"%d:%d",i+1,custvs.DTO);
				break;
			case 54:
				sprintf(aaxa,"%d:%d",i+1,custvs.CL);
				break;
			case 55:
				sprintf(aaxa,"%d:%d",i+1,custvs.CP);
				break;
			case 56:
				sprintf(aaxa,"%d:%d F",i+1,custcp.St);		//用户具有
				break;
			case 57:
				sprintf(aaxa,"%d:%.1f F",i+1,custcp.Hy);	//用户具有
				break;
			case 58:
				sprintf(aaxa,"%d:%d F",i+1,factcp.LS);
				break;
			case 59:
				sprintf(aaxa,"%d:%d F",i+1,factcp.US);
				break;
			case 60:
				sprintf(aaxa,"%d:%.1f F",i+1,custcp.ot);		//用户具有
				break;
			case 61:
				if(custcp.p2)
					sprintf(aaxa,"%d:n",i+1);
				else
					sprintf(aaxa,"%d:y",i+1);		//用户具有
				break;
			case 62:
				sprintf(aaxa,"%d:%.1f F",i+1,factcp.oE);
				break;
			case 63:
				sprintf(aaxa,"%d:%d min",i+1,factcp.od);
				break;
			case 64:
				sprintf(aaxa,"%d:%d min",i+1,custcp.AC);	//用户具有
				break;
			case 65:
				sprintf(aaxa,"%d:%d min",i+1,factcp.Cy);
				break;
			case 66:
				sprintf(aaxa,"%d:%d min",i+1,factcp.Cn);
				break;
			case 67:
				sprintf(aaxa,"%d:%d min",i+1,factcp.dAd);
				break;
			case 68:
				sprintf(aaxa,"%d:%d",i+1,factdis.PA1);
				break;
			case 69:
				sprintf(aaxa,"%d:%d",i+1,factdis.PA2);
				break;
			case 70:
				if(custdis.CF)
					sprintf(aaxa,"%d: F",i+1);
				else
					sprintf(aaxa,"%d: C",i+1);		//用户具有
				break;
			case 71:
				if(custdis.rE)
					sprintf(aaxa,"%d:in",i+1);
				else
					sprintf(aaxa,"%d:dE",i+1);		//用户具有
				break;
			case 72:
				if(factdis.Ld)
					sprintf(aaxa,"%d:P2",i+1);
				else
					sprintf(aaxa,"%d:P1",i+1);
				break;
			case 73:
				sprintf(aaxa,"%d:%d min",i+1,factdis.dy);
				break;
			case 74:
				sprintf(aaxa,"%d:%d",i+1,custdis.d1);	//用户具有
				break;
			case 75:
				sprintf(aaxa,"%d:%d",i+1,custdis.d2);	//用户具有
				break;
			case 76:
				sprintf(aaxa,"%d:%d",i+1,custdis.P01);	//用户具有
				break;
			case 77:
				sprintf(aaxa,"%d:%s",i+1,factdis.P31);
				break;
			case 78:
				sprintf(aaxa,"%d:%s",i+1,factdis.P32);
				break;
			case 79:
				if(factdef.td == 0)
					sprintf(aaxa,"%d:EL",i+1);
				else if(factdef.td == 1)
					sprintf(aaxa,"%d:in",i+1);
				else
					sprintf(aaxa,"%d:Ar",i+1);
				break;
			case 80:
				sprintf(aaxa,"%d:%d F",i+1,custdef.dE);	//用户具有
				break;
			case 81:
				sprintf(aaxa,"%d:%d hour",i+1,custdef.id);	//用户具有
				break;
			case 82:
				sprintf(aaxa,"%d:%d min",i+1,custdef.Md);	//用户具有
				break;
			case 83:
				sprintf(aaxa,"%d:%d min",i+1,factdef.dd);
				break;
			case 84:
				if(factdef.dF == 0)
					sprintf(aaxa,"%d:rt",i+1);
				else if(factdef.dF == 1)
					sprintf(aaxa,"%d:it",i+1);
				else if(factdef.dF == 2)
					sprintf(aaxa,"%d:SP",i+1);
				else
					sprintf(aaxa,"%d:dE",i+1);
				break;
			case 85:
				sprintf(aaxa,"%d:%d min",i+1,factdef.dt);
				break;
			case 86:
				if(factdef.dP)
					sprintf(aaxa,"%d:n",i+1);
				else
					sprintf(aaxa,"%d:y",i+1);
				break;
			case 87:
				sprintf(aaxa,"%d:%d min",i+1,custfan.Fd); //用户具有
				break;
			case 88:
				sprintf(aaxa,"%d:%d F",i+1,factfan.FS);
				break;
			case 89:
				sprintf(aaxa,"%d:%d F",i+1,factfan.FAd);
				break;
			case 90:
				sprintf(aaxa,"%d:%d min",i+1,custfan.Fn);	//用户具有
				break;
			case 91:
				sprintf(aaxa,"%d:%d min",i+1,custfan.FF); // 用户具有
				break;
			case 92:
				sprintf(aaxa,"%d:%d min",i+1,factfan.dAd);
				break;
			case 93:
				sprintf(aaxa,"%d:%d F",i+1,custal.AU);
				break;
			case 94:
				sprintf(aaxa,"%d:%d F",i+1,custal.AL);
				break;
			case 95:
				sprintf(aaxa,"%d:%d min",i+1,factal.Ad);
				break;
			case 96:
				sprintf(aaxa,"%d:%d min",i+1,factal.dA);
				break;
			case 97:
				break;
			case 98:
				break;
			case 99:
				break;
			case 100:
				break;
			
			//辅机
			case 101:
				sprintf(aaxa,"%d:%s",i,recetemp);
				break;
			case 102:
				sprintf(aaxa,"%d:%.0f F",i,St2);
				break;
			case 103:
				sprintf(aaxa,"%d:%.1f F",i,Hy2);
				break;
			case 104:
				sprintf(aaxa,"%d:%d",i,receweight);
				break;
			case 105:
				sprintf(aaxa,"%d:%s",i,receupweight);
				break;
			case 106:
				sprintf(aaxa,"%d:%s",i,recedrum);
				break;
			case 107:
				sprintf(aaxa,"%d:%s",i,receout);
				break;
			case 108:
				sprintf(aaxa,"%d:%s",i,rececom);
				break;
			case 109:
				sprintf(aaxa,"%d:%s",i,recevap);
				break;
			case 110:
				sprintf(aaxa,"%d:%s",i,recedef);
				break;
			case 111:
				sprintf(aaxa,"%d:%d",i,recehigh);
				break;
			case 112:
				sprintf(aaxa,"%d:%d",i,recelow);
				break;
			case 113:
				sprintf(aaxa,"%d:%d",i,receeva);
				break;
			case 114:
				sprintf(aaxa,"%d:%d",i,receref);
				break;
			case 115:
				sprintf(aaxa,"%d:%d",i,recedoor);
				break;
			case 116:
				sprintf(aaxa,"%d:%d",i,DC2);
				break;
			case 117:
				sprintf(aaxa,"%d:%d",i,CC2);
				break;
			case 118:
				sprintf(aaxa,"%d:%d",i,SC2);
				break;
			case 119:
				sprintf(aaxa,"%d:%d",i,MC2);
				break;
			case 120:
				sprintf(aaxa,"%d:%d",i,LC2);
				break;
			case 121:
				sprintf(aaxa,"%d:%d",i,DrTQ2);
				break;
			case 122:
				sprintf(aaxa,"%d:%d",i,DTQ2);
				break;
			case 123:
				sprintf(aaxa,"%d:%d",i,FTO2);
				break;
			case 124:
				sprintf(aaxa,"%d:%d",i,DTO2);
				break;
			case 125:
				sprintf(aaxa,"%d:%d",i,CL2);
				break;
			case 126:
				sprintf(aaxa,"%d:%d",i,CP2);
				break;
			case 127:
				sprintf(aaxa,"%d:%d",i,RE2);
				break;
			case 128:
				sprintf(aaxa,"%d:%d",i,P02_P2);
				break;
			case 129:
				sprintf(aaxa,"%d:%d",i,DT_P2);
				break;
			case 130:
				sprintf(aaxa,"%d:%d",i,RT_P2);
				break;
			case 131:
				sprintf(aaxa,"%d:%d",i,P102);
				break;
			case 132:
				sprintf(aaxa,"%d:%d",i,P112);
				break;
			case 133:
				sprintf(aaxa,"%d:%d",i,P132);
				break;
			case 134:
				sprintf(aaxa,"%d:%d",i,P142);
				break;
			case 135:
				sprintf(aaxa,"%d:%d",i,P162);
				break;
			case 136:
				sprintf(aaxa,"%d:%d",i,P172);
				break;
			case 137:
				if(P182)
					sprintf(aaxa,"%d:On",i);
				else
					sprintf(aaxa,"%d:Off",i);
				break;
			case 138:
				if(P192)
					sprintf(aaxa,"%d:On",i);
				else
					sprintf(aaxa,"%d:Off",i);
				break;
			case 139:
				sprintf(aaxa,"%d:%d",i,P212);
				break;
			case 140:
				sprintf(aaxa,"%d:%d",i,P222);
				break;
			case 141:
				sprintf(aaxa,"%d:%d",i,P232);
				break;
			case 142:
				sprintf(aaxa,"%d:%d",i,P262);
				break;
			case 143:
				if(P282)
					sprintf(aaxa,"%d:Numerica",i);
				else
					sprintf(aaxa,"%d:English",i);
				break;
			case 144:
				sprintf(aaxa,"%d:%d",i,P292);
				break;
			case 145:
				sprintf(aaxa,"%d:%d",i,P302);
				break;
			case 146:
				sprintf(aaxa,"%d:%d",i,DC2);
				break;
			case 147:
				sprintf(aaxa,"%d:%d",i,CC2);
				break;
			case 148:
				sprintf(aaxa,"%d:%d",i,SC2);
				break;
			case 149:
				sprintf(aaxa,"%d:%d",i,MC2);
				break;
			case 150:
				sprintf(aaxa,"%d:%d",i,LC2);
				break;
			case 151:
				sprintf(aaxa,"%d:%d",i,DrTQ2);
				break;
			case 152:
				sprintf(aaxa,"%d:%d",i,DTQ2);
				break;
			case 153:
				sprintf(aaxa,"%d:%d",i,FTO2);
				break;
			case 154:
				sprintf(aaxa,"%d:%d",i,DTO2);
				break;
			case 155:
				sprintf(aaxa,"%d:%d",i,CL2);
				break;
			case 156:
				sprintf(aaxa,"%d:%d",i,CP2);
				break;
			case 157:
				sprintf(aaxa,"%d:%.0f F",i,St2);		//用户具有
				break;
			case 158:
				sprintf(aaxa,"%d:%.1f F",i,Hy2);	//用户具有
				break;
			case 159:
				sprintf(aaxa,"%d:%d F",i,LS2);
				break;
			case 160:
				sprintf(aaxa,"%d:%d F",i,US2);
				break;
			case 161:
				sprintf(aaxa,"%d:%.1f F",i,ot2);		//用户具有
				break;
			case 162:
				if(P22)
					sprintf(aaxa,"%d:n",i);
				else
					sprintf(aaxa,"%d:y",i);		//用户具有
				break;
			case 163:
				sprintf(aaxa,"%d:%.1f F",i,oE2);
				break;
			case 164:
				sprintf(aaxa,"%d:%d min",i,od2);
				break;
			case 165:
				sprintf(aaxa,"%d:%d min",i,AC2);	//用户具有
				break;
			case 166:
				sprintf(aaxa,"%d:%d min",i,Cy2);
				break;
			case 167:
				sprintf(aaxa,"%d:%d min",i,Cn2);
				break;
			case 168:
				sprintf(aaxa,"%d:%d min",i,dAd2);
				break;
			case 169:
				sprintf(aaxa,"%d:%d",i,PA12);
				break;
			case 170:
				sprintf(aaxa,"%d:%d",i,PA22);
				break;
			case 171:
				if(CF2)
					sprintf(aaxa,"%d: F",i);
				else
					sprintf(aaxa,"%d: C",i);		//用户具有
				break;
			case 172:
				if(rE2)
					sprintf(aaxa,"%d:in",i);
				else
					sprintf(aaxa,"%d:dE",i);		//用户具有
				break;
			case 173:
				if(Ld2)
					sprintf(aaxa,"%d:P2",i);
				else
					sprintf(aaxa,"%d:P1",i);
				break;
			case 174:
				sprintf(aaxa,"%d:%d min",i,dy2);
				break;
			case 175:
				sprintf(aaxa,"%d:%d",i,d12);	//用户具有
				break;
			case 176:
				sprintf(aaxa,"%d:%d",i,d22);	//用户具有
				break;
			case 177:
				sprintf(aaxa,"%d:%d",i,P012);	//用户具有
				break;
			case 178:
				sprintf(aaxa,"%d:%s",i,P312);
				break;
			case 179:
				sprintf(aaxa,"%d:%s",i,P322);
				break;
			case 180:
				if(td2 == 0)
					sprintf(aaxa,"%d:EL",i);
				else if(td2 == 1)
					sprintf(aaxa,"%d:in",i);
				else
					sprintf(aaxa,"%d:Ar",i);
				break;
			case 181:
				sprintf(aaxa,"%d:%d F",i,dE2);	//用户具有
				break;
			case 182:
				sprintf(aaxa,"%d:%d hour",i,id2);	//用户具有
				break;
			case 183:
				sprintf(aaxa,"%d:%d min",i,Md2);	//用户具有
				break;
			case 184:
				sprintf(aaxa,"%d:%d min",i,dd2);
				break;
			case 185:
				if(dF2 == 0)
					sprintf(aaxa,"%d:rt",i);
				else if(dF2 == 1)
					sprintf(aaxa,"%d:it",i);
				else if(dF2 == 2)
					sprintf(aaxa,"%d:SP",i);
				else
					sprintf(aaxa,"%d:dE",i);
				break;
			case 186:
				sprintf(aaxa,"%d:%d min",i,dt2);
				break;
			case 187:
				if(dP2)
					sprintf(aaxa,"%d:n",i);
				else
					sprintf(aaxa,"%d:y",i);
				break;
			case 188:
				sprintf(aaxa,"%d:%d min",i,Fd2); //用户具有
				break;
			case 189:
				sprintf(aaxa,"%d:%d F",i,FS2);
				break;
			case 190:
				sprintf(aaxa,"%d:%d F",i,FAd2);
				break;
			case 191:
				sprintf(aaxa,"%d:%d min",i,Fn2);	//用户具有
				break;
			case 192:
				sprintf(aaxa,"%d:%d min",i,FF2); // 用户具有
				break;
			case 193:
				sprintf(aaxa,"%d:%d min",i,dAd2);
				break;
			case 194:
				sprintf(aaxa,"%d:%d F",i,AU2);
				break;
			case 195:
				sprintf(aaxa,"%d:%d F",i,AL2);
				break;
			case 196:
				sprintf(aaxa,"%d:%d min",i,Ad2);
				break;
			case 197:
				sprintf(aaxa,"%d:%d min",i,dA2);
				i = 0;
				break;
		}
		//Usart3_Printf("%s\r\n",aaxa);
		Usart2_Printf("%s\r\n",aaxa);
	//	osDelay(19);
	//}
}

void StringCompare_s(char *s)
{
	char *str[56] ={"factcp.St","factcp.Hy","factcp.LS","factcp.US","factcp.ot","factcp.P2","factcp.oE","factcp.od","factcp.AC","factcp.Cy","factcp.Cn","factcp.dAd",
			 "factdis.PA1","factdis.PA2","factdis.CF","factdis.rE","factdis.Ld","factdis.dy","factdis.d1","factdis.d2","factdis.P01","factdis.P31","factdis.P32",
			 "factdef.td","factdef.dE","factdef.id","factdef.Md","factdef.dd","factdef.dF","factdef.dt", "factdef.dP",
			 "factfan.Fd","factfan.FS","factfan.FAd","factfan.Fn","factfan.FF","factfan.dAd"
			 "factal.AU","factal.AL","factal.Ad","factal.dA",
			 "factdsp.P10","factdsp.P11","factdsp.P13","factdsp.P14","factdsp.P16","factdsp.P17","factdsp.P18","factdsp.P19","factdsp.P21","factdsp.P22","factdsp.P23","factdsp.P26","factdsp.P28","factdsp.P29","factdsp.P30"};
	char *p;
	for(int i=0; i<56;i++){
		if(memcmp(str[i],s,strlen(str[i])) == 0){
			Usart3_Printf("%d优秀啊%s\r\n",i,str[i]);
			switch(i){
				case 0:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.St = atoi(p);
					custcp.St = factcp.St;
					break;
				case 1:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.Hy = atof(p);
					custcp.Hy = factcp.Hy;
					break;
				case 2:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.LS = atoi(p);
					break;
				case 3:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.US = atoi(p);
					break;
				case 4:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.ot = atoi(p);
					custcp.ot = factcp.ot;
					break;
				case 5:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.P2 = atoi(p);
					custcp.p2 = factcp.P2;
					break;
				case 6:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.oE = atof(p);
					break;
				case 7:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.od = atoi(p);
					break;
				case 8:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.AC = atoi(p);
					custcp.AC = factcp.AC;
					break;
				case 9:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.Cy = atoi(p);
					break;
				case 10:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.Cn = atoi(p);
					break;
				case 11:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.dAd = atoi(p);
					break;
				case 12:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.PA1 = atoi(p);
					break;
				case 13:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.PA2 = atoi(p);
					break;
				case 14:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.CF = atoi(p);
					custdis.CF = factdis.CF;
					break;
				case 15:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.rE = atof(p);
					custdis.rE = factdis.rE;
					break;
				case 16:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.Ld = atoi(p);
					break;
				case 17:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.dy = atoi(p);
					break;
				case 18:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.d1 = atoi(p);
					custdis.d1 = factdis.d1;
					break;
				case 19:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.d2 = atoi(p);
					custdis.d2 = factdis.d2;
					break;
				case 20:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.P01 = atoi(p);
					custdis.P01 = factdis.P01;
					break;
				case 21:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					factdis.P31 = atoi(p);
					break;
				case 22:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					factdis.P32 = atoi(p);
					break;
				case 23:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.td = atoi(p);
					break;
				case 24:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dE = atoi(p);
					custdef.dE = factdef.dE;
					break;
				case 25:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.id = atoi(p);
					custdef.id = factdef.id;
					break;
				case 26:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.Md = atoi(p);
					custdef.Md = factdef.Md;
					break;
				case 27:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dd = atoi(p);
					break;
				case 28:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dF = atoi(p);
					break;
				case 29:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dt = atoi(p);
					break;
				case 30:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dP = atoi(p);
					break;
				case 31:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.Fd = atoi(p);
					custfan.Fd = factfan.Fd;
					break;
				case 32:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.FS = atoi(p);
					break;
				case 33:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.FAd = atoi(p);
					break;
				case 34:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.Fn = atoi(p);
					custfan.Fn = factfan.Fn;
					break;
				case 35:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.FF = atoi(p);
					custfan.FF = factfan.FF;
					break;
				case 36:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.dAd = atoi(p);
					break;
				case 37:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.AU = atoi(p);
					custal.AU = factal.AU;
					break;
				case 38:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.AL = atoi(p);
					custal.AL = factal.AL;
					break;
				case 39:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.Ad = atoi(p);
					break;
				case 40:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.dA = atoi(p);
					break;
				case 41:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P10 = atoi(p);
					break;
				case 42:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P11 = atoi(p);
					break;
				case 43:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P13 = atoi(p);
					break;
				case 44:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P14 = atoi(p);
					break;
				case 45:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P16 = atoi(p);
					break;
				case 46:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P17 = atoi(p);
					break;
				case 47:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P18 = atoi(p);
					break;
				case 48:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P19 = atoi(p);
					break;
				case 49:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P21 = atoi(p);
					break;
				case 50:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P22 = atoi(p);
					break;
				case 51:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P23 = atoi(p);
					break;
				case 52:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P26 = atoi(p);
					break;
				case 53:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P28 = atoi(p);
					break;
				case 54:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P29 = atoi(p);
					break;
				case 55:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P30 = atoi(p);
					break;
				/*
				//副机
				case 56:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					St2 = atoi(p);
					Uart4_Printf("factcp.St=%f",St2);
					break;
				case 57:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Hy2 = atof(p);
					Uart4_Printf("factcp.St=%f",Hy2);
					break;
				case 58:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					LS2 = atoi(p);
					Uart4_Printf("factcp.LS=%d",LS2);
					break;
				case 59:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					US2 = atoi(p);
					Uart4_Printf("factcp.US=%d",US2);
					break;
				case 60:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					ot2 = atoi(p);
					Uart4_Printf("factcp.ot=%f",ot2);
					break;
				case 61:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P22 = atoi(p);
					Uart4_Printf("factcp.P2=%d",P22);
					break;
				case 62:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					oE2 = atof(p);
					Uart4_Printf("factcp.oE=%f",oE2);
					break;
				case 63:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					od2 = atoi(p);
					Uart4_Printf("factcp.od=%d",od2);
					break;
				case 64:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					AC2 = atoi(p);
					Uart4_Printf("factcp.AC=%d",AC2);
					break;
				case 65:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Cy2 = atoi(p);
					Uart4_Printf("factcp.Cy=%d",Cy2);
					break;
				case 66:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Cn2 = atoi(p);
					Uart4_Printf("factcp.Cn=%d",Cn2);
					break;
				case 67:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dAd2 = atoi(p);
					Uart4_Printf("factcp.dAd=%d",dAd2);
					break;
				case 68:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					PA12 = atoi(p);
					Uart4_Printf("factdis.PA1=%d",PA12);
					break;
				case 69:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					PA22 = atoi(p);
					Uart4_Printf("factdis.PA2=%d",PA22);
					break;
				case 70:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					CF2 = atoi(p);
					Uart4_Printf("factdis.CF=%d",CF2);
					break;
				case 71:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					rE2 = atof(p);
					Uart4_Printf("factdis.rE=%d",rE2);
					break;
				case 72:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Ld2 = atoi(p);
					Uart4_Printf("factdis.Ld=%d",Ld2);
					break;
				case 73:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dy2 = atoi(p);
					Uart4_Printf("factdis.dy=%d",dy2);
					break;
				case 74:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					d12 = atoi(p);
					Uart4_Printf("factdis.d1=%d",d12);
					break;
				case 75:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					d22 = atoi(p);
					Uart4_Printf("factdis.d2=%d",d22);
					break;
				case 76:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P012 = atoi(p);
					Uart4_Printf("factdis.P01=%d",P012);
					break;
				case 77:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					P312 = atoi(p);
					Uart4_Printf("factdis.P31=%s",P312);
					break;
				case 78:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					P322 = atoi(p);
					Uart4_Printf("factdis.P32=%s",P322);
					break;
				case 79:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					td2 = atoi(p);
					Uart4_Printf("factdef.td=%d",td2);
					break;
				case 80:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dE2 = atoi(p);
					Uart4_Printf("factdef.dE=%d",dE2);
					break;
				case 81:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					id2 = atoi(p);
					Uart4_Printf("factdef.id=%d",id2);
					break;
				case 82:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Md2 = atoi(p);
					Uart4_Printf("factdef.Md=%d",Md2);
					break;
				case 83:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dd2 = atoi(p);
					Uart4_Printf("factdef.dd=%d",dd2);
					break;
				case 84:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dF2 = atoi(p);
					Uart4_Printf("factdef.dF=%d",dF2);
					break;
				case 85:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dt2 = atoi(p);
					Uart4_Printf("factdef.dt=%d",dt2);
					break;
				case 86:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dP2 = atoi(p);
					Uart4_Printf("factdef.dP=%d",dP2);
					break;
				case 87:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Fd2 = atoi(p);
					Uart4_Printf("factfan.Fd=%d",Fd2);
					break;
				case 88:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					FS2 = atoi(p);
					Uart4_Printf("factfan.FS=%d",FS2);
					break;
				case 89:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					FAd2 = atoi(p);
					Uart4_Printf("factfan.FAd=%d",FAd2);
					break;
				case 90:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Fn2 = atoi(p);
					Uart4_Printf("factfan.Fn=%d",Fn2);
					break;
				case 91:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					FF2 = atoi(p);
					Uart4_Printf("factfan.FF=%d",FF2);
					break;
				case 92:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dad2 = atoi(p);
					Uart4_Printf("factfan.dad=%d",dad2);
					break;
				case 93:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					AU2 = atoi(p);
					Uart4_Printf("factal.AU=%d",AU2);
					break;
				case 94:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					AL2 = atoi(p);
					Uart4_Printf("factal.AL=%d",AL2);
					break;
				case 95:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Ad2 = atoi(p);
					Uart4_Printf("factal.Ad=%d",Ad2);
					break;
				case 96:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dA2 = atoi(p);
					Uart4_Printf("factal.dA=%d",dA2);
					break;
				case 97:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P102 = atoi(p);
					Uart4_Printf("factdsp.P10=%d",P102);
					break;
				case 98:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P112 = atoi(p);
					Uart4_Printf("factdsp.P11=%d",P112);
					break;
				case 99:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P132 = atoi(p);
					Uart4_Printf("factdsp.P13=%d",P132);
					break;
				case 100:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P142 = atoi(p);
					Uart4_Printf("factdsp.P14=%d",P142);
					break;
				case 101:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P162 = atoi(p);
					Uart4_Printf("factdsp.P16=%d",P162);
					break;
				case 102:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P172 = atoi(p);
					Uart4_Printf("factdsp.P17=%d",P172);
					break;
				case 103:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P182 = atoi(p);
					Uart4_Printf("factdsp.P18=%d",P182);
					break;
				case 104:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P192 = atoi(p);
					Uart4_Printf("factdsp.P19=%d",P192);
					break;
				case 105:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P212 = atoi(p);
					Uart4_Printf("factdsp.P21=%d",P212);
					break;
				case 106:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P222 = atoi(p);
					Uart4_Printf("factdsp.P22=%d",P222);
					break;
				case 107:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P232 = atoi(p);
					Uart4_Printf("factdsp.P23=%d",P232);
					break;
				case 108:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P262 = atoi(p);
					Uart4_Printf("factdsp.P26=%d",P262);
					break;
				case 109:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P282 = atoi(p);
					Uart4_Printf("factdsp.P28=%d",P282);
					break;
				case 110:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P292 = atoi(p);
					Uart4_Printf("factdsp.P29=%d",P292);
					break;
				case 111:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P302 = atoi(p);
					Uart4_Printf("factdsp.P30=%d",P302);
					break;
				*/
			}
		}
	}
	ParamSave();
	memset(str,0,sizeof(str));
}

void StringCompare(char *s)
{
	char *str[112] ={
			 "factcp.St","factcp.Hy","factcp.LS","factcp.US","factcp.ot","factcp.P2","factcp.oe","factcp.od","factcp.AC","factcp.Cy","factcp.Cn","factcp.dAd",
			 "factdis.PA1","factdis.PA2","factdis.CF","factdis.rE","factdis.Ld","factdis.dy","factdis.d1","factdis.d2","factdis.P01","factdis.P31","factdis.P32",
			 "factdef.td","factdef.dE","factdef.id","factdef.Md","factdef.dd","factdef.dF","factdef.dt", "factdef.dP",
			 "factfan.Fd","factfan.FS","factfan.FAd","factfan.Fn","factfan.FF","factfan.dAd",
			 "factal.AU","factal.AL","factal.Ad","factal.dA",
			 "factdsp.P10","factdsp.P11","factdsp.P13","factdsp.P14","factdsp.P16","factdsp.P17","factdsp.P18","factdsp.P19","factdsp.P21","factdsp.P22","factdsp.P23","factdsp.P26","factdsp.P28","factdsp.P29","factdsp.P30",
			 "2factcp.St","2factcp.Hy","2factcp.LS","2factcp.US","2factcp.ot","2factcp.P2","2factcp.oe","2factcp.od","2factcp.AC","2factcp.Cy","2factcp.Cn","2factcp.dAd",
			 "2factdis.PA1","2factdis.PA2","2factdis.CF","2factdis.rE","2factdis.Ld","2factdis.dy","2factdis.d1","2factdis.d2","2factdis.P01","2factdis.P31","2factdis.P32",
			 "2factdef.td","2factdef.dE","2factdef.id","2factdef.Md","2factdef.dd","2factdef.dF","2factdef.dt", "2factdef.dP",
			 "2factfan.Fd","2factfan.FS","2factfan.FAd","2factfan.Fn","2factfan.FF","2factfan.dAd",
			 "2factal.AU","2factal.AL","2factal.Ad","2factal.dA",
			 "2factdsp.P10","2factdsp.P11","2factdsp.P13","2factdsp.P14","2factdsp.P16","2factdsp.P17","2factdsp.P18","2factdsp.P19","2factdsp.P21","2factdsp.P22","2factdsp.P23","2factdsp.P26","2factdsp.P28","2factdsp.P29","2factdsp.P30"};
	char *p;
//	Usart2_Printf("Receive:%s\r\n",UsartReceiveType2.RX_pData);
	for(int i=0; i<112;i++){
		if(memcmp(str[i],s,strlen(str[i])) == 0){
//			Usart3_Printf("比较后的:%s\r\n",str[i]);
//			Usart3_Printf("收到的数据:%s\r\n",UsartReceiveType2.RX_pData);
			switch(i){
				case 0:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.St = atoi(p);
					custcp.St = factcp.St;
					break;
				case 1:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.Hy = atof(p);
					custcp.Hy = factcp.Hy;
					break;
				case 2:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.LS = atoi(p);
					break;
				case 3:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.US = atoi(p);
					break;
				case 4:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.ot = atof(p);
					custcp.ot = factcp.ot;
					 
					custcp.AC = factcp.AC;
					break;
				case 9:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.Cy = atoi(p);
					break;
				case 10:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.Cn = atoi(p);
					break;
				case 11:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factcp.dAd = atoi(p);
					break;
				case 12:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.PA1 = atoi(p);
					break;
				case 13:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.PA2 = atoi(p);
					break;
				case 14:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.CF = atoi(p);
					custdis.CF = factdis.CF;
					break;
				case 15:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.rE = atof(p);
					custdis.rE = factdis.rE;
					break;
				case 16:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.Ld = atoi(p);
					break;
				case 17:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.dy = atoi(p);
					break;
				case 18:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.d1 = atoi(p);
					custdis.d1 = factdis.d1;
					break;
				case 19:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.d2 = atoi(p);
					custdis.d2 = factdis.d2;
					break;
				case 20:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdis.P01 = atoi(p);
					custdis.P01 = factdis.P01;
					break;
				case 21:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					factdis.P31 = atoi(p);
					break;
				case 22:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					factdis.P32 = atoi(p);
					break;
				case 23:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.td = atoi(p);
					break;
				case 24:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dE = atoi(p);
					custdef.dE = factdef.dE;
					break;
				case 25:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.id = atoi(p);
					custdef.id = factdef.id;
					break;
				case 26:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.Md = atoi(p);
					custdef.Md = factdef.Md;
					break;
				case 27:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dd = atoi(p);
					break;
				case 28:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dF = atoi(p);
					break;
				case 29:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dt = atoi(p);
					break;
				case 30:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdef.dP = atoi(p);
					break;
				case 31:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.Fd = atoi(p);
					custfan.Fd = factfan.Fd;
					break;
				case 32:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.FS = atoi(p);
					break;
				case 33:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.FAd = atoi(p);
					break;
				case 34:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.Fn = atoi(p);
					custfan.Fn = factfan.Fn;
					break;
				case 35:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.FF = atoi(p);
					custfan.FF = factfan.FF;
					break;
				case 36:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factfan.dAd = atoi(p);
					break;
				case 37:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.AU = atoi(p);
					custal.AU = factal.AU;
					break;
				case 38:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.AL = atoi(p);
					custal.AL = factal.AL;
					break;
				case 39:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.Ad = atoi(p);
					break;
				case 40:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factal.dA = atoi(p);
					break;
				case 41:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P10 = atoi(p);
					break;
				case 42:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P11 = atoi(p);
					break;
				case 43:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P13 = atoi(p);
					break;
				case 44:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P14 = atoi(p);
					break;
				case 45:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P16 = atoi(p);
					break;
				case 46:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P17 = atoi(p);
					break;
				case 47:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P18 = atoi(p);
					break;
				case 48:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P19 = atoi(p);
					break;
				case 49:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P21 = atoi(p);
					break;
				case 50:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P22 = atoi(p);
					break;
				case 51:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P23 = atoi(p);
					break;
				case 52:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P26 = atoi(p);
					break;
				case 53:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P28 = atoi(p);
					break;
				case 54:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P29 = atoi(p);
					break;
				case 55:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					factdsp.P30 = atoi(p);
					break;
				
				//副机
				case 56:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					St2 = atoi(p);
					Uart4_Printf("factcp.St=%f",St2);
					break;
				case 57:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Hy2 = atof(p);
					Uart4_Printf("factcp.St=%f",Hy2);
					break;
				case 58:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					LS2 = atoi(p);
					Uart4_Printf("factcp.LS=%d",LS2);
					break;
				case 59:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					US2 = atoi(p);
					Uart4_Printf("factcp.US=%d",US2);
					break;
				case 60:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					ot2 = atoi(p);
					Uart4_Printf("factcp.ot=%f",ot2);
					break;
				case 61:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P22 = atoi(p);
					Uart4_Printf("factcp.P2=%d",P22);
					break;
				case 62:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					oE2 = atof(p);
					Uart4_Printf("factcp.oE=%f",oE2);
					break;
				case 63:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					od2 = atoi(p);
					Uart4_Printf("factcp.od=%d",od2);
					break;
				case 64:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					AC2 = atoi(p);
					Uart4_Printf("factcp.AC=%d",AC2);
					break;
				case 65:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Cy2 = atoi(p);
					Uart4_Printf("factcp.Cy=%d",Cy2);
					break;
				case 66:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Cn2 = atoi(p);
					Uart4_Printf("factcp.Cn=%d",Cn2);
					break;
				case 67:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dAd2 = atoi(p);
					Uart4_Printf("factcp.dAd=%d",dAd2);
					break;
				case 68:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					PA12 = atoi(p);
					Uart4_Printf("factdis.PA1=%d",PA12);
					break;
				case 69:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					PA22 = atoi(p);
					Uart4_Printf("factdis.PA2=%d",PA22);
					break;
				case 70:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					CF2 = atoi(p);
					Uart4_Printf("factdis.CF=%d",CF2);
					break;
				case 71:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					rE2 = atof(p);
					Uart4_Printf("factdis.rE=%d",rE2);
					break;
				case 72:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Ld2 = atoi(p);
					Uart4_Printf("factdis.Ld=%d",Ld2);
					break;
				case 73:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dy2 = atoi(p);
					Uart4_Printf("factdis.dy=%d",dy2);
					break;
				case 74:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					d12 = atoi(p);
					Uart4_Printf("factdis.d1=%d",d12);
					break;
				case 75:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					d22 = atoi(p);
					Uart4_Printf("factdis.d2=%d",d22);
					break;
				case 76:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P012 = atoi(p);
					Uart4_Printf("factdis.P01=%d",P012);
					break;
				case 77:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					P312 = atoi(p);
					Uart4_Printf("factdis.P31=%s",P312);
					break;
				case 78:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
//					P322 = atoi(p);
					Uart4_Printf("factdis.P32=%s",P322);
					break;
				case 79:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					td2 = atoi(p);
					Uart4_Printf("factdef.td=%d",td2);
					break;
				case 80:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dE2 = atoi(p);
					Uart4_Printf("factdef.dE=%d",dE2);
					break;
				case 81:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					id2 = atoi(p);
					Uart4_Printf("factdef.id=%d",id2);
					break;
				case 82:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Md2 = atoi(p);
					Uart4_Printf("factdef.Md=%d",Md2);
					break;
				case 83:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dd2 = atoi(p);
					Uart4_Printf("factdef.dd=%d",dd2);
					break;
				case 84:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dF2 = atoi(p);
					Uart4_Printf("factdef.dF=%d",dF2);
					break;
				case 85:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dt2 = atoi(p);
					Uart4_Printf("factdef.dt=%d",dt2);
					break;
				case 86:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dP2 = atoi(p);
					Uart4_Printf("factdef.dP=%d",dP2);
					break;
				case 87:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Fd2 = atoi(p);
					Uart4_Printf("factfan.Fd=%d",Fd2);
					break;
				case 88:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					FS2 = atoi(p);
					Uart4_Printf("factfan.FS=%d",FS2);
					break;
				case 89:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					FAd2 = atoi(p);
					Uart4_Printf("factfan.FAd=%d",FAd2);
					break;
				case 90:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Fn2 = atoi(p);
					Uart4_Printf("factfan.Fn=%d",Fn2);
					break;
				case 91:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					FF2 = atoi(p);
					Uart4_Printf("factfan.FF=%d",FF2);
					break;
				case 92:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dad2 = atoi(p);
					Uart4_Printf("factfan.dad=%d",dad2);
					break;
				case 93:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					AU2 = atoi(p);
					Uart4_Printf("factal.AU=%d",AU2);
					break;
				case 94:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					AL2 = atoi(p);
					Uart4_Printf("factal.AL=%d",AL2);
					break;
				case 95:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					Ad2 = atoi(p);
					Uart4_Printf("factal.Ad=%d",Ad2);
					break;
				case 96:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					dA2 = atoi(p);
					Uart4_Printf("factal.dA=%d",dA2);
					break;
				case 97:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P102 = atoi(p);
					Uart4_Printf("factdsp.P10=%d",P102);
					break;
				case 98:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P112 = atoi(p);
					Uart4_Printf("factdsp.P11=%d",P112);
					break;
				case 99:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P132 = atoi(p);
					Uart4_Printf("factdsp.P13=%d",P132);
					break;
				case 100:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P142 = atoi(p);
					Uart4_Printf("factdsp.P14=%d",P142);
					break;
				case 101:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P162 = atoi(p);
					Uart4_Printf("factdsp.P16=%d",P162);
					break;
				case 102:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P172 = atoi(p);
					Uart4_Printf("factdsp.P17=%d",P172);
					break;
				case 103:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P182 = atoi(p);
					Uart4_Printf("factdsp.P18=%d",P182);
					break;
				case 104:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P192 = atoi(p);
					Uart4_Printf("factdsp.P19=%d",P192);
					break;
				case 105:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P212 = atoi(p);
					Uart4_Printf("factdsp.P21=%d",P212);
					break;
				case 106:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P222 = atoi(p);
					Uart4_Printf("factdsp.P22=%d",P222);
					break;
				case 107:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P232 = atoi(p);
					Uart4_Printf("factdsp.P23=%d",P232);
					break;
				case 108:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P262 = atoi(p);
					Uart4_Printf("factdsp.P26=%d",P262);
					break;
				case 109:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P282 = atoi(p);
					Uart4_Printf("factdsp.P28=%d",P282);
					break;
				case 110:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P292 = atoi(p);
					Uart4_Printf("factdsp.P29=%d",P292);
					break;
				case 111:
					p = strtok(s,"=");
					p = strtok(NULL,"=");
					P302 = atoi(p);
					Uart4_Printf("factdsp.P30=%d",P302);
					break;
			}
		}
	}
	ParamSave();
	memset(str,0,sizeof(str));
}


