//*************************************************************************************
//MMC/SD卡读写头文件mmc.h
//定义了SD卡的硬件连接、宏定义了MMC/SD卡常用命令、卡读写函数声明、返回代码(成功代码、错误代码)
//根据硬件连接不同，可以更改端口
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2011.09.19
// *************************************************************************************

/**********************************************************************
              MMC/SD卡硬件连接IO口分配情况
***********************************************************************/

#define HIGH(a) ((a>>8)&0xFF)                     //获取一个字数据的高字节部分
#define LOW(a)  (a&0xFF)                          //获取一个字数据的低字节部分

#define CS_LOW()    P3OUT &= ~BIT0                //MMC/SD卡片选信号置低，选中状态
#define CS_HIGH()   SPI_TX_DONE; P3OUT |= BIT0    //MMC/SD卡片选信号置高，无效状态
#define SPI_RXC     (IFG1 & URXIFG0)
#define SPI_TXC     (IFG1 & UTXIFG0)

#define SPI_RX_COMPLETE (IFG1 & URXIFG0)
#define SPI_TX_READY    (IFG1 & UTXIFG0)
#define SPI_TX_DONE     while((U0TCTL & TXEPT)==0)


/**********************************************************************
             数据传输开始标志，需要在读数据和写数据前进行检测
***********************************************************************/

#define MMC_START_DATA_BLOCK_TOKEN          0xfe   //数据传输开始标志位，开始单块读操作
#define MMC_START_DATA_MULTIPLE_BLOCK_READ  0xfe   //数据传输开始标志位，开始多块读操作
#define MMC_START_DATA_BLOCK_WRITE          0xfe   //数据传输开始标志位，开始单块写操作
#define MMC_START_DATA_MULTIPLE_BLOCK_WRITE 0xfc   //数据传输开始标志位，开始多块写操作
#define MMC_STOP_DATA_MULTIPLE_BLOCK_WRITE  0xfd   //数据传输停止标志位，停止多块写操作

// an affirmative R1 response (no errors)
#define MMC_R1_RESPONSE       0x00

/**********************************************************************
             返回成功或错误代码
***********************************************************************/

#define MMC_SUCCESS           0x00           //执行成功代码
#define MMC_BLOCK_SET_ERROR   0x01           //卡没有完全插入到卡座中
#define MMC_RESPONSE_ERROR    0x02
#define MMC_DATA_TOKEN_ERROR  0x03
#define MMC_INIT_ERROR        0x04
#define MMC_CRC_ERROR         0x10
#define MMC_WRITE_ERROR       0x11
#define MMC_OTHER_ERROR       0x12
#define MMC_TIMEOUT_ERROR     0xFF

/**********************************************************************
              MMC/SD卡命令
***********************************************************************/

#define MMC_GO_IDLE_STATE          0x40     //CMD0 MMC/SD卡上电后进入空闲模式
#define MMC_SEND_OP_COND           0x41     //CMD1 MMC卡初始化使用CMD1，可以用来判定SD卡还是MMC卡
#define MMC_CID                    0x48     //CMD8 SD卡版本判断信息，Ver1.x或者Ver2.x，如果对CMD8响应错误，则为Ver1.x
#define MMC_READ_CSD               0x49     //CMD9 读取扇区信息，Ver1.x只支持最大2GB，Ver2.x支持更大容量
#define MMC_SEND_CID               0x4a     //CMD10 MMC/SD卡鉴别信息，厂商ID、生产日期等等，不是必须
#define MMC_STOP_TRANSMISSION      0x4c     //CMD12 多块操作时停止命令
#define MMC_SEND_STATUS            0x4d     //CMD13 发送状态读取命令
#define MMC_SET_BLOCKLEN           0x50     //CMD16 设置读写块的长度
#define MMC_READ_SINGLE_BLOCK      0x51     //CMD17 读单块命令
#define MMC_READ_MULTIPLE_BLOCK    0x52     //CMD18 读多块
#define MMC_CMD_WRITEBLOCK         0x54     //CMD20 
#define MMC_WRITE_BLOCK            0x58     //CMD24 写单块
#define MMC_WRITE_MULTIPLE_BLOCK   0x59     //CMD25
#define MMC_WRITE_CSD              0x5b     //CMD27 写CSD寄存器
#define MMC_SET_WRITE_PROT         0x5c     //CMD28
#define MMC_CLR_WRITE_PROT         0x5d     //CMD29
#define MMC_SEND_WRITE_PROT        0x5e     //CMD30
#define MMC_TAG_SECTOR_START       0x60     //CMD32 擦除起始地址
#define MMC_TAG_SECTOR_END         0x61     //CMD33 擦除结束地址
#define MMC_UNTAG_SECTOR           0x62     //CMD34
#define MMC_TAG_EREASE_GROUP_START 0x63     //CMD35
#define MMC_TAG_EREASE_GROUP_END   0x64     //CMD36
#define MMC_UNTAG_EREASE_GROUP     0x65     //CMD37
#define MMC_EREASE                 0x66     //CMD38 擦除命令
#define MMC_READ_OCR               0x67     //CMD39 读OCR寄存器
#define MMC_CRC_ON_OFF             0x68     //CMD40 关闭CRC校验

#define SD_APP_COND                0x77     //CMD55  SD卡初始化，先写CMD55命令，再写AMD41命令
#define SD_APP_OP_COND             0x69     //ACMD41 初始化SD卡，MMC卡用CMD1

/********************************************************************************
                    函数声明区
********************************************************************************/
void initSPI (void);
uchar spiSendByte(const unsigned char data);
char mmc_GoIdle();
uchar mmcGetResponse(void);
uchar mmcGetXXResponse(const char resp);
uchar mmcCheckBusy(void);
void spiInit(void);
uchar spiSendByte(uchar data);
uchar mmcGoIdle();
uchar initMMC (void);
uchar mmcEreaseBlock(ulong Sector);
void mmcSendCmd (uchar cmd, ulong data, uchar crc);
uchar mmcSetBlockLength (uint blocklength);
uchar mmcReadBlock(ulong address, uint count, uchar *pBuffer);
#define mmcReadSector(sector, pBuffer) mmcReadBlock(sector*512ul, 512, pBuffer)  //读扇区函数，参数为扇区号与存放数据地址
uchar mmcWriteBlock(ulong address, uint count, uchar *pBuffer);
#define mmcWriteSector(sector, pBuffer) mmcWriteBlock(sector*512ul, 512, pBuffer) //写扇区函数，参数为扇区号与需写入数据地址
uchar mmcReadRegister(uchar cmd_register, uchar length, uchar *pBuffer);
ulong MMC_ReadCardSize(void);
