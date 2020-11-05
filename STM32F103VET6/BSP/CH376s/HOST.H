#ifndef HOST_H_
#define HOST_H_

#include "./CH376INC.H"		/* 使用 CH376INC.H 中的类型定义 */
#include "CH376INC.H"		/* 使用 CH376INC.H 中的类型定义 */
//#include "./HAL.H"

/* U盘全局状态 结构体定义 */
struct  UdiskStruct
{
    UINT16 uarttest: 1;      /* CH376 串口通讯测 */
    UINT16 hostmode: 1;      /* CH376 设置主机模式状态 */
    UINT16 disk: 1;          /* U盘插入与否 */
    UINT16 mount: 1;         /* 初始化 U盘（挂载）成功标志，即 ch376 是否识别插入的 U盘。 参见 CH376DS1.PDF 5.17 CMD_DISK_MOUNT 命令 */
    UINT16 freespace: 1;      /* U盘 是否有空余空间 */
    UINT16 nowriteprotect: 1; /* U盘 是否写保护 */
    UINT16 creatfile: 1;      /* 根据 RTC 创建的 长文件名文件 是否成功 */
    UINT16 openfile : 1;      /* 打开 U盘中 的文件 */
    UINT16 alreadyinit: 1;    /* U盘相关信息是否已经显示过   */
    UINT16 datawriting: 1;    /* 是否正在向 U盘中写入数据   */
};


extern	UINT8   buf[64];
extern  UINT16	total;
extern  UINT32	NewSize;
extern  char    LongName1[30];
extern  char    LongName2[70];
extern  char    ShortName[15];

extern struct UdiskStruct Udisk;



/* 安全移除U盘, 返回USB_INT_SUCCESS说明可以安全移除,否则说明不能安全移除,只能强行移除 */
/* 在操作完U盘准备让用户拔出U盘前调用, 防止用户过早拔出U盘丢失数据 */
UINT8	SafeRemoveDisk( void );

/* 测试 U盘 是否连接。
    U盘连接，返回 USB_INT_SUCCESS; 否则返回：0  */
UINT8 Check_UdiskConnect(void);


/* 初始化 U盘 并测试磁盘是否就绪
	参见 CH376DS1.PDF 5.17 CMD_DISK_MOUNT 命令 */
UINT8 Ch376_UdiskMount(void);


/* 初始化CH376 ：
       1   初始化 STM32 串口2，设置 串口2 波特率。
       2.  测试 CH376S 与 STM32 的 串口通讯
       3.  设置CH376S 为 U盘主机模式06
    初始化成功，返回 USB_INT_SUCCESS
    初始化失败，返回 ERR_USB_UNKNOWN          */
UINT8	mInitCH376Host(void);

/*  调用 以下三个静态函数  可向 LCD 输出 U盘信息
	Quire_UdiskInform()
	Quire_UdiskFreeVolume()
	IsDiskWriteProtect()	*/
void Ch376_QuireUdiskInfo(void);


/* 根据实时时钟 设置 写入数据文件的 长短文件名 */
void Ch376_SetFileName(void);

/*  创建根据实时时钟指定文件名的文件。
	若操作成功，返回 USB_INT_SUCCESS;
	若长文件名对应都按文件名已存在，返回 ERR_NAME_EXIST；
	否则返回：0			*/
UINT8 Ch376_CreatFile(void);

/* 打开创建的 文件名。
   若操作成功，返回 USB_INT_SUCCESS;
   否则返回：0		*/
UINT8 Ch376_OpenFile(void);


/*  更新数据缓冲区中的数据，并通过 CH376 向U盘中写入缓冲区中的数据。
		需要注意数据缓冲区的数据格式。
	若操作成功，返回： USB_INT_SUCCESS;
	否则返回：0			*/
UINT8 Ch376_WriteData(void);

/*  关闭打开的文件，并更新文件长度。
	若操作成功，则返回 USB_INT_SUCCESS;
	否则返回： 0;
	*/
UINT8 Ch376_CloseFile(void);

void Ch376_DisplayMusk(void);

/* HOST 操作主函数 */
void host(void);

#endif

