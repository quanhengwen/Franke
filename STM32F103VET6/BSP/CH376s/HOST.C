/* CH376 主机文件系统接口 */
/* @think3r https://git.oschina.net/think3r */
/* STM32 单片机 C语言的 U盘文件读写			 */
/*  本范例演示在扇区模式下处理零碎数据,同时兼顾操作方便和较高速度,
	需要单片机系统提供足够的RAM作为文件数据缓冲区 FILE_DATA_BUF 	*/

#include "HOST.H"
//#include "HAL.H" 	 					/* 对应 UART_HW.C  */
#include <stdio.h>
#include <string.h> 					/* 使用 C 语言库函数中的 字符串操作函数 */
#include "FILE_SYS.H"  				/* 引用FILE_SYS.C 中的函数 */
#include "CH376INC.H"	 				/* 使用 CH376INC.H 中的命令码宏定义 */
#include "rtc.h"
#include "usart.h"
#include "stm32f1xx_hal.h"
#include "LCD19264.h"




/*=======================================可能需要修改的 include 文件包含========================================================*/

/*=======================================可能需要修改的 include 文件包含========================================================*/
//--------------------------modify
#define On		1
#define Off		0
//#define delay_us1 HAL_Delay
//#define delay_ms1 HAL_Delay

UINT8   buf[64];	 /* 缓存 U盘 信息，如  KingstonDataTraveler 3.0PMAP */
UINT16	total;		/* 记录当前缓冲在 FILE_DATA_BUF 中的数据长度 */
UINT32	NewSize;	/* 临时变量 */
struct  UdiskStruct Udisk;

//static UINT16 tempyear;
//static UINT8 tempmonth, tempdate, temphour, tempmin, tempsec;


/* 数组初始化的数值个数小于数组的大小，则全部用0来填充。
	即无需考虑 字符串数组结尾 '\0' 问题 */
//UINT8   LongName1[30] = {0};
//UINT8   LongName2[70] = {0};
//UINT8 	ShortName[15] = {0};
//UINT8		ReadConfigName[12] = {0};

char   LongName1[30] = {0};
char    LongName2[70] = {0};
char  	 ShortName[15]= {0};
char 	 ReadConfigName[12] = {0};



/* 安全移除U盘, 返回USB_INT_SUCCESS说明可以安全移除,否则说明不能安全移除,只能强行移除 */
/* 在操作完U盘准备让用户拔出U盘前调用, 防止用户过早拔出U盘丢失数据 */
UINT8	SafeRemoveDisk( void )
{
    UINT8	i, s;

    for ( i = 0; i < 5; i ++ )
    {
        /* 有的U盘总是返回未准备好,不过可以被忽略 */
        s = CH376DiskMount( );
        if ( s == USB_INT_SUCCESS )
            break;  /* 查询磁盘是否准备好 */
        else if (s == ERR_DISK_DISCON )
        {
            /*=======================================可以在此中间添加 LCD 显示： U盘未插入！！！（可选）=================================================*/

            /*=======================================可以在此中间添加 LCD 显示： U盘未插入！！！（可选）=================================================*/
#ifdef __CH376_DEBUG_
            //printf("磁盘未连接.\r\n");
#endif
            return 0;
        }
    }
    //delay_us1(10 );
		
    s = CH376SendCmdDatWaitInt( CMD1H_SET_CONFIG, 0 );  /* 取消配置,会导致很多U盘的LED灯灭 */
    if ( (i < 6) && (s == USB_INT_SUCCESS) && (Udisk.datawriting == 0))
    {
        /*=======================================需要在中间添加 LCD 显示： 可以安全移除 U盘========================================================*/

        /*=======================================需要在中间添加 LCD 显示： 可以安全移除 U盘========================================================*/
#ifdef __CH376_DEBUG_
        //printf("可以安全移除 U盘。\r\n");
#endif
        return( USB_INT_SUCCESS );  /* 操作成功 */
    }
    else
    {
        /*=======================================需要在中间添加 LCD 显示： U盘正在操作========================================================*/

        /*=======================================需要在中间添加 LCD 显示： U盘正在操作========================================================*/
#ifdef __CH376_DEBUG_
        //printf("正在操作U盘，请稍后！\r\n");
#endif
        return( 0xFF );
    }
}


/*-----------------------------------------------------------------------------------------------*/

/*  测试 CH376S 与 STM32 的 串口通讯 是否正常
	若通讯正常，则返回 USB_INT_SUCCESS ; 否则返回：0 	*/
static UINT8 Check_Ch376sUart2Connect(void)
{
    UINT8 x = 0, res;
    Udisk.uarttest = 0;

    for(x = 0; x < 5; x++)		//若首次通讯失败，则对CH376芯片再进行5次通讯测试
    {
        xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* 测试单片机与CH376之间的通讯接口 */
        xWriteCH376Data( 0x65 );
        res = xReadCH376Data( );

        /* 通讯接口不正常,可能原因有:接口连接异常,其它设备影响(片选不唯一),串口波特率,一直在复位,晶振不工作 */
        if(res == 0x9A)
        {
            Udisk.uarttest = 1;
						//printf("\r\nCH376与STM3芯片正常！接收数据为：%#X\r\n", res);
					  //printf("Udisk.uarttest == %d\r\n", Udisk.uarttest);

            return USB_INT_SUCCESS; //通讯正常，跳出通讯测试。
        }
        else
        {
#ifdef __CH376_DEBUG_
            //printf("CH376与STM32通讯失败！返回值为：%X\r\n", res);
            //printf("正在进行第 %d 次通讯重试。\r\n", x);
            HAL_Delay(500);
#endif
            HAL_Delay(10);
            continue ;
        }
    }
    /*=======================================需要在中间添加 LCD 显示： CH376 初始化失败（可选）========================================================*/


    /*=======================================需要在中间添加 LCD 显示： CH376 初始化失败（可选）========================================================*/
#ifdef __CH376_DEBUG_
    //printf("请检查与CH376S芯片的通讯。\r\n");
#endif
    Udisk.uarttest = 0;
    return 0;
}

/* 初始化CH376 ：
       1   初始化 STM32 串口2, 设置 串口2 波特率。(调用函数 CH376_PORT_INIT() )
       2.  测试 CH376S 与 STM32 的 串口通讯 (调用函数：Check_Ch376sUart2Connect() )
       3.  设置CH376S 为 U盘主机模式06
    初始化成功，返回 USB_INT_SUCCESS
    初始化失败，返回 ERR_USB_UNKNOWN          */
UINT8	mInitCH376Host(void)  /* 初始化CH376 */
{
    UINT8	res;
    //CH376_PORT_INIT( );  /* 接口硬件初始化 */
	////printf("reset start\r\n");
//		USB_L;
//		HAL_Delay(500);
//		USB_H;

  xWriteCH376Cmd(CMD00_RESET_ALL);//硬件复位
	//CH376ModelReset(Off);
	//HAL_Delay(100);
	//CH376ModelReset(On);

	HAL_Delay(300);
	//printf("reset ok\r\n");
  Check_Ch376sUart2Connect();

    if( Udisk.uarttest == 1)
    {
        xWriteCH376Cmd( CMD11_SET_USB_MODE );  /* 设备USB工作模式 */
        xWriteCH376Data( 0x06 );
        HAL_Delay(10);
        res = xReadCH376Data( );

        if ( res == CMD_RET_SUCCESS )
        {
            Udisk.hostmode = 1;
#ifdef __CH376_DEBUG_
            //printf("\r\nCh376_set_usb_mode()函数 设置为U盘主机模式 06 成功！接收数据为：%#X\r\n", res);
            //printf("Udisk.hostmode == %d\r\n", Udisk.hostmode);
            //printf("mInitCH376Host() 函数初始化 CH376 成功。\r\n");
#endif
            return( USB_INT_SUCCESS );
        }
        else
        {
            Udisk.hostmode = 0;
#ifdef __CH376_DEBUG_
            //printf("\r\nCh376_set_usb_mode()函数 设置U盘主机模式 06 失败！返回值为：%#X\r\n", res);
            //printf("Udisk.hostmode == %d\r\n", Udisk.hostmode);
#endif
            return( ERR_USB_UNKNOWN );  /* 设置模式错误 */
        }
    }
    return( ERR_USB_UNKNOWN );
}

/* 测试 U盘 是否连接。
    U盘连接，返回 USB_INT_SUCCESS; 否则返回：0  */
UINT8 Check_UdiskConnect(void)
{
    Udisk.disk = 0;

    if (Udisk.hostmode == 1)
    {
        if(CH376DiskConnect( ) == USB_INT_SUCCESS)
        {
            Udisk.disk = 1;
#ifdef __CH376_DEBUG_
            //printf("CH376DiskConnect() 函数 检测到 U盘插入。\r\n");
            //printf("Udisk.disk == %d\r\n", Udisk.disk);
#endif

            if (Udisk.alreadyinit == 0)   /*  只在 U盘 初次插入时，显示  */
            {
                /*=======================================需要在此中间添加 LCD 显示： U盘插入 ========================================================*/
                /*=======================================需要在此中间添加 LCD 显示： U盘插入 ========================================================*/
            }


            return USB_INT_SUCCESS;
        }
        else
        {
#ifdef __CH376_DEBUG_
            //printf("CH376DiskConnect() 函数 未检测到 U盘插入。\r\n");
            //printf("Udisk.disk == %d\r\n", Udisk.disk);
#endif
            /*  拔出 U盘，清除 U盘 全局状态标志  */
            Udisk.mount = 0;
            Udisk.freespace = 0;
            Udisk.nowriteprotect = 0;
            Udisk.creatfile = 0;
            Udisk.openfile = 0;
            Udisk.alreadyinit = 0;
            Udisk.datawriting = 0;
        }
    }
    return 0;
}


/* 初始化 U盘 并测试磁盘是否就绪
	参见 CH376DS1.PDF 5.17 CMD_DISK_MOUNT 命令
	初始化成功，返回 USB_INT_SUCCESS ;否则返回：0 */
UINT8 Ch376_UdiskMount(void)
{
    UINT8 i, s;
    /* 对于检测到USB设备的,最多等待10*50mS */
    /* 需要修改 挂载 U盘 的延时 */
    if ((Udisk.hostmode == 1) && (Udisk.disk == 1) && (Udisk.alreadyinit == 0))
    {
        for ( i = 0; i < 10; i ++ )
        {
            /* 最长等待时间, 8*50mS */
            HAL_Delay( 500 );
#ifdef __CH376_DEBUG_
            //printf( "Ready ?\r\n" );
#endif
            s = CH376DiskMount( );  /* 初始化磁盘并测试磁盘是否就绪 */

            if ( s == USB_INT_SUCCESS )
            {
                Udisk.mount = 1;
#ifdef __CH376_DEBUG_
                //printf("CH376DiskMount() 函数检测到 磁盘就绪。返回值为：%#X\r\n", s);
                //printf("Udisk.mount == %d\r\n", Udisk.mount);
#endif

                return USB_INT_SUCCESS; /* 准备好 */
            }
            else if ( s == ERR_DISK_DISCON )
            {
                Udisk.mount = 0;
#ifdef __CH376_DEBUG_
                //printf("CH376DiskMount() 函数检测到 U盘断开。\r\n");
                //printf("Udisk.mount == %d\r\n", Udisk.mount);
#endif
                continue;  /* 检测到断开,重新检测并计时 */
            }
            if ( CH376GetDiskStatus( ) >= DEF_DISK_MOUNTED && i >= 5 )
            {
                Udisk.mount = 1;
                break;  /* 有的U盘总是返回未准备好,不过可以忽略,只要其建立连接MOUNTED且尝试5*50mS */
            }
        }
    }
    if (Udisk.alreadyinit == 0)
    {
        /*=======================================需要在此中间添加 LCD 显示： 不能识别插入的 U盘========================================================*/

        /*=======================================需要在此中间添加 LCD 显示： 不能识别插入的 U盘========================================================*/
    }
    return 0;
}


/* 查询 U盘 信息，通过串口输出。
	如  KingstonDataTraveler 3.0PMAP */
static UINT8 Quire_UdiskInform(void)
{
    UINT8 s = 0;
    if( (Udisk.disk == 1) && (Udisk.mount == 1) && (Udisk.alreadyinit == 0))
    {
        s = CH376ReadBlock( buf );  /* 如果需要,可以读取数据块CH376_CMD_DATA.DiskMountInq,返回长度 */
        if ( s == sizeof( INQUIRY_DATA ) )
        {
            /* U盘的厂商和产品信息 */
            buf[ s ] = 0;
#ifdef __CH376_DEBUG_
            //printf( "磁盘信息---UdiskInfo: %s\r\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
#endif
            /* 待拷贝到缓存区 或者进行 LCD 显示 */
            /*=======================================需要在此中间添加 LCD 显示： U盘的厂商和产品信息========================================================*/

            /*=======================================需要在此中间添加 LCD 显示： U盘的厂商和产品信息========================================================*/
            return USB_INT_SUCCESS;
        }
    }
    return 0;
}


/* 查询 U盘 剩余容量
	返回值： U盘剩余空间； 单位: MB
	若失败，则返回 0 ；		*/
static UINT16 Quire_UdiskFreeVolume(void)
{
    UINT16 volume;

    if( (Udisk.disk == 1) && (Udisk.mount == 1) && (Udisk.alreadyinit == 0))
    {
        CH376DiskQuery( (PUINT32)buf );  /* 查询磁盘剩余空间信息,扇区数 */

        /* 检查U盘或者SD卡的剩余空间,单位 MB ，volume 最大值为 65535MB, 64GB */
        volume = *(PUINT32)buf / ( 1000000 / DEF_SECTOR_SIZE );

        if (volume >= 50)
        {
            Udisk.freespace = 1;
#ifdef __CH376_DEBUG_
            //printf("Udisk.freespace == %d\r\n", Udisk.freespace);
#endif
        }
        else
        {
            Udisk.freespace = 0;
#ifdef __CH376_DEBUG_
            //printf("Udisk.freespace == %d\r\n", Udisk.freespace);
            /*=======================================需要在此中间添加 LCD 显示：  U盘剩余空间不足========================================================*/

            /*=======================================需要在此中间添加 LCD 显示：  U盘剩余空间不足========================================================*/
#endif
        }
#ifdef __CH376_DEBUG_
        //printf( "DiskQuery: \r\n" );
        //printf( "正在查询磁盘剩余空间。free cap = %ld MB\r\n", volume );  /* 上面一行的计算可能会溢出,换个顺序计算 */
#endif
        /*=======================================需要在此中间添加 LCD 显示： U盘剩余容量显示========================================================*/

        /*=======================================需要在此中间添加 LCD 显示： U盘剩余容量显示========================================================*/
        return volume;
    }
    else
        return 0;
}

/* 检查U盘是否写保护, 返回USB_INT_SUCCESS说明可以写,返回0xFF说明只读/写保护,返回其它值说明是错误代码 */
/* 其它BulkOnly传输协议的命令可以参考这个例子处理,修改前必须了解USB MassStorage和SCSI规范 */
static UINT8	IsDiskWriteProtect( void )
{
    UINT8	s, SysBaseInfo;
    P_BULK_ONLY_CBW	pCbw;
    if( (Udisk.disk == 1) && (Udisk.mount == 1) && (Udisk.freespace == 1) && (Udisk.alreadyinit == 0))
    {
        Udisk.alreadyinit = 1;
        SysBaseInfo = CH376ReadVar8( VAR_SYS_BASE_INFO );  /* 当前系统的基本信息 */
        pCbw = (P_BULK_ONLY_CBW)buf;
        for ( s = 0; s != sizeof( pCbw -> CBW_CB_Buf ); s ++ )
            pCbw -> CBW_CB_Buf[ s ] = 0;  /* 默认清0 */
        pCbw -> CBW_DataLen0 = 0x10;  /* 数据传输长度 */
        pCbw -> CBW_Flag = 0x80;  /* 传输方向为输入 */
        if ( SysBaseInfo & 0x40 )
        {
            /* SubClass-Code子类别非6 */
            pCbw -> CBW_CB_Len = 10;  /* 命令块的长度 */
            pCbw -> CBW_CB_Buf[0] = 0x5A;  /* 命令块首字节, MODE SENSE(10) */
            pCbw -> CBW_CB_Buf[2] = 0x3F;
            pCbw -> CBW_CB_Buf[8] = 0x10;
        }
        else
        {
            /* SubClass-Code子类别为6 */
            pCbw -> CBW_CB_Len = 6;  /* 命令块的长度 */
            pCbw -> CBW_CB_Buf[0] = 0x1A;  /* 命令块首字节, MODE SENSE(6) */
            pCbw -> CBW_CB_Buf[2] = 0x3F;
            pCbw -> CBW_CB_Buf[4] = 0x10;
        }
        CH376WriteHostBlock( (PUINT8)pCbw, sizeof( BULK_ONLY_CBW ) );  /* 向USB主机端点的发送缓冲区写入数据块,剩余部分CH376自动填补 */
        s = CH376SendCmdWaitInt( CMD0H_DISK_BOC_CMD );  /* 对U盘执行BulkOnly传输协议 */
        if ( s == USB_INT_SUCCESS )
        {
            s = CH376ReadBlock( buf );  /* 从当前主机端点的接收缓冲区读取数据块,返回长度 */
            if ( s > 3 )
            {
                /* MODE SENSE命令返回数据的长度有效 */
                if ( SysBaseInfo & 0x40 ) s = buf[3];  /* MODE SENSE(10), device specific parameter */
                else s = buf[2];  /* MODE SENSE(6), device specific parameter */
                if ( s & 0x80 )
                {
                    Udisk.nowriteprotect = 0;
#ifdef __CH376_DEBUG_
                    //printf("Udisk.nowriteprotect == %d\r\n", Udisk.nowriteprotect);
#endif
                    /*=======================================需要在此中间添加 LCD 显示： U盘写保护，无法写入数据====================================================*/

                    /*=======================================需要在此中间添加 LCD 显示： U盘写保护，无法写入数据====================================================*/
                    return( 0xFF );  /* U盘写保护 */
                }
                else
                {
                    Udisk.nowriteprotect = 1;
#ifdef __CH376_DEBUG_
                    //printf("Udisk.nowriteprotect == %d\r\n", Udisk.nowriteprotect);
#endif
                    return( USB_INT_SUCCESS );  /* U盘没有写保护 */
                }
            }
#ifdef __CH376_DEBUG_
            //printf("Udisk.nowriteprotect == %d\r\n", Udisk.nowriteprotect);
#endif
            Udisk.nowriteprotect = 0;
            return( USB_INT_DISK_ERR );
        }
        CH376DiskReqSense( );  /* 检查USB存储器错误 */
        return( s );
    }
    else
        return 0;
}

/*  调用 以下三个静态函数 可向 LCD 输出 U盘信息
	Quire_UdiskInform()
	Quire_UdiskFreeVolume()
	IsDiskWriteProtect()	*/
void Ch376_QuireUdiskInfo(void)
{

    Quire_UdiskInform();

    Quire_UdiskFreeVolume();

    IsDiskWriteProtect();

}

/* 根据实时时钟 设置 写入数据文件的 长短文件名 */
void Ch376_SetFileName(void)
{
    UINT8 j;
    /*=======================================需要修改为自己的RTC ========================================================*/
    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
	
    /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

    	//RTC_Get();	 /* 更新 RTC , 以新的 RTC 时钟作为 文件名。 */
    /* 将当前时间写入 临时变量，保证文件名 一一对应 */
//    tempyear = currentDate.Year;
//    tempmonth = currentDate.Month;
//    tempdate  = currentDate.Date;
//    temphour  = currentTime.Hours;
//    tempmin   = currentTime.Minutes;
//    tempsec = currentTime.Seconds;
    /*=======================================需要修改为自己的RTC ========================================================*/
    /* 设置短文件名  */
//    sprintf(ShortName, "/%02d%02d%02d%02d.CSV", tempmonth, tempdate, temphour, tempmin);
    sprintf(ShortName, "/20190531.CSV");
    ShortName[13] = 0;
    ShortName[14] = 0;
    /* 设置长文件名 */
    //    sprintf( LongName1 , "%04d-%02d-%02d %02d-%02d.CSV", 2000 + tempyear, tempmonth, tempdate, temphour, tempmin);
    sprintf( LongName1 , "20190531TEST.CSV");

#ifdef __CH376_DEBUG_
    //printf("设置短文件名为： %s\r\n", ShortName );
    //printf("设置长文件名为： %s\r\n", LongName1);
#endif

    /*====================================可在此中间添加 LCD 显示：本次 写入数据文件名为 LongName1 ========================================================*/

    /*====================================可在此中间添加 LCD 显示：本次 写入数据文件名为 LongName1 ========================================================*/

    /* 转换英文长文件名 LongName1 到 LongName2 长文件名缓冲区( UTF-16-LE 编码)，
    ASCII码的英文长文件名转换成 UTF-16-LE的编码格式，只需在每个字符对应 ASCII 码的后面增添 1 bit 的 0x00  		*/
    for ( j = 0; LongName1[j] != 0; j++ )
    {
        LongName2[j * 2] = LongName1[j];
        LongName2[j * 2 + 1] = 0x00;
    }
    LongName2[j * 2] = 0x00; // 末尾用两个0表示结束
    LongName2[j * 2 + 1] = 0x00;
}


/* 为指定文件设置创建日期、时间；修改日期、时间 */
/* 输入参数:   原始文件名在iFileName中, 新的创建日期和时间: iCreateDate, iCreateTime */
/* 返回状态码: USB_INT_SUCCESS = 设置成功,
               其它状态码参考CH376INC.H */

//static UINT8 SetFileCreateTime( PUINT8 iFileName, UINT16 iCreateDate, UINT16 iCreateTime )
//{
//    UINT8	s;
//    s = CH376FileOpen( iFileName );  /* 打开文件 */
//    if ( s == USB_INT_SUCCESS )
//    {
//        /* 文件读写操作等... */
//        s = CH376DirInfoRead( );  /* 读取当前文件的目录信息FAT_DIR_INFO,将相关数据调到内存中 */
//        if ( s == USB_INT_SUCCESS )
//        {
//            buf[0] = (UINT8)iCreateTime;  /* 文件创建的时间,低8位在前 */
//            buf[1] = (UINT8)(iCreateTime >> 8); /* 文件创建的时间,高8位在后 */
//            CH376WriteOfsBlock( buf, STRUCT_OFFSET( FAT_DIR_INFO, DIR_CrtTime ), 2 );  /* 向内部缓冲区偏移地址DIR_CrtTime写入2个字节 */
//            CH376WriteOfsBlock( buf, STRUCT_OFFSET(FAT_DIR_INFO, DIR_WrtTime), 2 );
//            buf[0] = (UINT8)iCreateDate;  /* 文件创建的日期,低8位在前 */
//            buf[1] = (UINT8)(iCreateDate >> 8); /* 文件创建的日期,高8位在后 */
//            CH376WriteOfsBlock( buf, STRUCT_OFFSET( FAT_DIR_INFO, DIR_CrtDate ), 2 );  /* 向内部缓冲区偏移地址DIR_CrtDate写入2个字节 */
//            CH376WriteOfsBlock( buf, STRUCT_OFFSET( FAT_DIR_INFO, DIR_WrtDate ), 2 );
//            s = CH376DirInfoSave( );  /* 保存文件的目录信息 */
//            if ( s == USB_INT_SUCCESS )
//            {
//                /* 成功修改并保存 */
//                /* 文件读写操作等... */
//            }
//        }
//        CH376FileClose( FALSE );  /* 关闭文件 */
//    }
//    return( s );
//}



/*  创建根据实时时钟指定文件名的文件。
	若操作成功，返回 USB_INT_SUCCESS;
	若长文件名对应都按文件名已存在，返回 ERR_NAME_EXIST；
	否则返回：0			*/
UINT8 Ch376_CreatFile(void)
{
    UINT8 s = 0;
    Udisk.datawriting = 1;
    //    if ( (Udisk.disk == 1) && (Udisk.mount == 1) && (Udisk.freespace == 1)\
    //            && (Udisk.nowriteprotect == 1))
    if ( (Udisk.disk == 1) && (Udisk.mount == 1))
    {
#ifdef __CH376_DEBUG_
        //printf( "Open\r\n" );
#endif
        //        sprintf(ShortName, "/20190531Test.CSV");
        s = CH376FileCreatePath((PUINT8)ShortName);

        //s = CH376CreateLongName( ShortName, LongName2 );  /* 新建具有长文件名的文件 */
        Udisk.datawriting = 0;
        if ( s == USB_INT_SUCCESS )
        {
#ifdef __CH376_DEBUG_
            //printf("创建 长文件名 成功。\r\n ");
#endif
            Udisk.creatfile = 1;
            //SetFileCreateTime(ShortName, MAKE_FILE_DATE( 2000 + tempyear, tempmonth, tempdate ), MAKE_FILE_TIME( temphour, tempmin, tempsec) );
						
            return USB_INT_SUCCESS;
        }
        else if ( s == ERR_NAME_EXIST )
        {
#ifdef __CH376_DEBUG_
            //printf("创建 长文件名失败，该长文件名对应的短文件名已经存在。\r\n");
#endif
            Udisk.creatfile = 1;
            Udisk.datawriting = 0;
            return ERR_NAME_EXIST;
        }
        else
        {
#ifdef __CH376_DEBUG_
            //printf( "创建 长文件名 失败.Error Code: %02X\r\n", (UINT16)s );
#endif
            Udisk.creatfile = 0;
            return 0;
        }
    }
    Udisk.datawriting = 0;
    return 0;
}


/* 打开创建的 文件名。
   若操作成功，返回 USB_INT_SUCCESS;
   否则返回：0		*/
UINT8 Ch376_OpenFile(void)
{
    UINT8 s = 0;
    //    if ((Udisk.disk == 1) && Udisk.creatfile == 1)
    if ((Udisk.disk == 1) && Udisk.mount == 1)
    {
        memset(ShortName, 0, sizeof(ShortName));
        sprintf(ShortName, "/20190531.CSV");
        ShortName[13] = 0;
        ShortName[14] = 0;
        s = CH376FileOpen((PUINT8)ShortName);
        if(s == ERR_MISS_FILE)
        {
            s = CH376FileCreatePath((PUINT8)ShortName);
        }
        total = 0;  /* 此前没有零头数据 */
        NewSize = 0;

        if ( s == USB_INT_SUCCESS )
        {
            Udisk.openfile = 1;
            Udisk.creatfile = 1;
#ifdef __CH376_DEBUG_
            //printf("CH376 打开已创建的 长文件名 文件 成功。\r\n");
            //printf("Udisk.openfile == %d\r\n", Udisk.openfile);
#endif
            return USB_INT_SUCCESS;
        }
        else
        {
            Udisk.openfile = 0;
            Udisk.creatfile = 0;
#ifdef __CH376_DEBUG_
            //printf("CH376 打开已创建的 长文件名 文件 失败。 返回数据为： %#X \r\n", s);
            //printf("Udisk.openfile == %d\r\n", Udisk.openfile);
#endif
            return 0;
        }
    }
    else
        return 0;
}

/*  更新数据缓冲区中的数据，并通过 CH376 向U盘中写入缓冲区中的数据。
		需要注意数据缓冲区的数据格式。
	若操作成功，返回： USB_INT_SUCCESS;
	否则返回：0			*/
UINT8 Ch376_WriteData(void)
{
//    UINT8 x;
//		//x=0;
//    if ( (Udisk.disk == 1) && (Udisk.mount == 1) && (Udisk.creatfile == 1) )
//    {
//        /*---------------------------------------写入数据时，尽量关闭 所有能关闭 的中断。--------------------------------------------------------*/
//        //		TIM5_CLOSE();
//        //TIM3_Disable();
//        /*---------------------------------------写入数据时，尽量关闭 所有能关闭 的中断。--------------------------------------------------------*/
//        Udisk.datawriting = 1;

//        /*=======================================下面代码在移植时，可以删去========================================================*/

//        /*	下面这段代码主用于测试，向 数据缓冲区 FileDataBuf[] 写入 RTC 数据。Write
//        		若在别的函数中，已向 FileDataBuf[] 写入数据，可以删去本段代码。
//        		若使用 *.CSV 表格文件，则在向缓冲区中写入数据时，应注意写入数据的格式。   */
//        //        {
//        //#ifdef __CH376_DEBUG_
//        //            //printf( "正在向文件中写入 RTC 数据。Write RTC data\r\n" );
//        //#endif
////                    for ( x = 1; x <= 30; x ++  )
////                    {
////                        HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
////                        /* Get the RTC current Date */
////                        HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);
////                        total += sprintf( FileDataBuf + total, "%04d-%02d-%02d,%02d: %02d: %02d, 第 %d 次写入数据\xd\xa", currentDate.Year, currentDate.Month, currentDate.Date, currentTime.Hours, currentTime.Minutes, currentTime.Seconds, x ); /* 将二制制数据格式为一行字符串 */

////                        if ( x % 15 == 0 )
////                            mFlushBufferToDisk( 1 );  /* 强制刷新缓冲区,定期强制刷新缓冲区,这样在突然断电后可以减少数据丢失 */
////                        else if(x % 5 == 0)
////                        {
////                            mFlushBufferToDisk( 0 );  /* 自动刷新缓冲区,检查缓冲区是否已满,满则写盘 */
////        //#ifdef __CH376_DEBUG_
//        //                    //printf( "当前缓冲在FILE_DATA_BUF中的数据长度，Current total is %d\r\n", total );  /* 用于监控检查 */
//        //#endif
// //                       }
//        //            }
//        //#ifdef __CH376_DEBUG_
//        //            //printf( "向文件中写入数据结束。Write end...........\r\n" );
//        //#endif
////                    total += sprintf( FileDataBuf + total, "********************," );  /* 将新数据添加到缓冲区的尾部,累计缓冲区内的数据长度 */
////                    total += sprintf( FileDataBuf + total, "这次的 RTC数据到此结束,程序即将退出\xd\xa" );  /* 将新数据添加到缓冲区的尾部,累计缓冲区内的数据长度 */
////        //        }
////        //        /*=======================================上面代码在 移植时，可以删去========================================================*/

////                mFlushBufferToDisk( 1 );  /* 强制刷新缓冲区,因为系统要退出了,所以必须强制刷新 */


////        HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
////        /* Get the RTC current Date */
////        HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);
////        memset(FileDataBuf, 0, sizeof(FileDataBuf));
////        uint16_t len = sprintf( FileDataBuf, "%04d-%02d-%02d,%02d: %02d: %02d, Temp:,%d,Humi:,%d\xd\xa", 2000 + currentDate.Year, currentDate.Month, currentDate.Date, currentTime.Hours, currentTime.Minutes, currentTime.Seconds, 28, 80 ); /* 将二制制数据格式为一行字符串 */

////        CH376ByteLocate(0xFFFFFFFF);//移动文件指针到文件末尾
////        CH376ByteWrite(FileDataBuf, len, &len);
//        /*--------------------------------------- 打开进入函数时，关闭的中断。--------------------------------------------------------*/
//        //		TIM5_OPEN();
//        //TIM3_Enable();
//        /*--------------------------------------- 打开进入函数时，关闭的中断。 -------------------------------------------------------*/
//        Udisk.datawriting = 0;
//  //      len = 0;	/*  复位 total  */
//        return USB_INT_SUCCESS;
//    }
//    else
        return 0;
}



/*  关闭打开的文件，并更新文件长度。
	若操作成功，则返回 USB_INT_SUCCESS;
	否则返回： 0;
	*/
UINT8 Ch376_CloseFile(void)
{
    UINT8 s;
    Udisk.datawriting = 1;
    if( (Udisk.disk == 1) && (Udisk.openfile == 1)  )
    {
#ifdef __CH376_DEBUG_
        //printf( "正在关闭文件。Close\r\n" );
#endif

        s = CH376FileClose( TRUE );  /* 关闭文件,扇区模式通常不自动更新文件长度,需要自动更新文件长度 */
        Udisk.datawriting = 0;
        if (s == USB_INT_SUCCESS)
        {
#ifdef __CH376_DEBUG_
            //printf( "CH376 关闭文件 成功。\r\n" );
#endif
            Udisk.openfile = 0;

            return USB_INT_SUCCESS;
        }
        else
        {
#ifdef __CH376_DEBUG_
            //printf("CH376 关闭文件 失败。\r\n");
#endif
            return 0;
        }
    }
    else if((Udisk.disk == 1) && (Udisk.openfile == 0) )
    {
        Udisk.datawriting = 0;
#ifdef __CH376_DEBUG_
        //printf("Ch376_CloseFile() 函数提示，未打开文件，无需关闭文件。\r\n");
#endif
        return 0;
    }
    else
    {
        Udisk.datawriting = 0;
        return 0;
    }
}

/*  输出 U盘全局状态 主要用于 USMART debug 调试 */
void Ch376_DisplayMusk(void)
{
#ifdef __CH376_DEBUG_
    //printf("\r\n---------------------------\r\n");
    //printf("Udisk.uarttest == %d\r\n", Udisk.uarttest);
    //printf("Udisk.hostmode == %d\r\n", Udisk.hostmode);
    //printf("Udisk.disk == %d\r\n", Udisk.disk);
    //printf("Udisk.mount == %d\r\n", Udisk.mount);
    //printf("Udisk.freespace == %d\r\n", Udisk.freespace);
    //printf("Udisk.nowriteprotect == %d\r\n", Udisk.nowriteprotect);
    //printf("Udisk.openfile == %d\r\n", Udisk.openfile);
    //printf("Udisk.alreadyinit == %d\r\n", Udisk.alreadyinit);
    //printf("Udisk.datawriting == %d\r\n", Udisk.datawriting);
    //printf("---------------------------\r\n");
#endif

    /*================================可以在此中间添加 Udisk结构体的 LCD 显示，以用来 debug (可选)========================================================*/

    /*==============================可以在此中间添加 Udisk结构体的 LCD 显示，以用来 debug（可选） ========================================================*/

}


/*=======================================host 操作主函数========================================================*/

void host(void)
{
    //printf("0\r\n");
#ifdef __CH376_DEBUG_
    //printf( "Wait Udisk/SD\r\n" );
#endif

    /*=======================================函数测试区域========================================================*/

    HAL_Delay( 500 );  /* 延时,可选操作,有的USB存储器需要几十毫秒的延时 */

    Ch376_UdiskMount();

    //Ch376_QuireUdiskInfo();

    //Ch376_SetFileName();  /*  仪器进行 本次测量时再调用 */

    HAL_Delay( 500 );
    //Ch376_CreatFile();

    Ch376_OpenFile();

    Ch376_WriteData();

    Ch376_CloseFile();
    /*=======================================函数测试区域========================================================*/
    HAL_Delay( 500 );
    memset(ReadConfigName, 0, sizeof(ReadConfigName));
    uint16_t read_config_name_len = sprintf(ReadConfigName, "/CONFIG.TXT");
    ReadConfigName[11] = 0;
    //printf("%s len: %d\r\n", ReadConfigName, read_config_name_len);
    uint8_t s = CH376FileOpen((PUINT8)ReadConfigName);
    if(s == ERR_MISS_FILE)
    {
        //printf("open config.txt fail\r\n");
    }
    CH376ByteLocate(0);
    if(s == USB_INT_SUCCESS)
    {
        uint8_t read_config[512] = {0};
        s = CH376ByteRead(read_config, 512, &read_config_name_len);
        //printf("CH376ByteRead: %s\t len: %d\r\n", read_config, read_config_name_len); /* 以字节为单位从文件读出数据,准备读 512 个字节 */
        CH376FileClose( TRUE );
    }

#ifdef __CH376_DEBUG_
    //printf( "任务结束。Take out\r\n" );
    //printf("---------------------------\r\n");
#endif
    //printf("1\r\n");

}
