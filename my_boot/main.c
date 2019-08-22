#include "s3c2440-regsaddr.h"
#include "nand.h"
#include "common.h"
////NAND FLASH OPERATION
//#define NF_nFCE_L() {(*NFCONT) &= ~(1<<1);}
//#define NF_nFCE_H() {(*NFCONT) |= (1<<1);}
//#define RDDATAB() (*NFDATA)  
//#define NFCMDf(cmd) {(*NFCMD) = cmd;}
//#define NFADDRf(addr) {*NFADDR = addr;}
//#define WAITRB() {while(!((*NFSTAT)&(1<<0)));}
//#define NF_CLEAR_RB() {(*NFSTAT) |= (1<<2);}
//#define DETECTRB() {while(!((*NFSTAT)&(1<<2)));}
//void Print(char *str){
//          while(*str!='\0'){
//                  while(!((*IsReady)&0x2));
//                  (*TX) = *str;
//		  str++;
//          }//while
//  }
//void static inline NandReset(void){
//
//	NF_nFCE_L();
//	NF_CLEAR_RB();
//	NFCMDf(0xff);
//	//等待，究竟等待哪个比较好呢？这点还不清楚
//	DETECTRB();
//	NF_nFCE_H();
//}
//void static inline NandCheckID(void){
//	unsigned char mid,did,concare,id4th;
//	
//	NF_nFCE_L();
//	//一个疑惑是为什么这里不需要对RnB位进行清除
//	NFCMDf(0x90);
//	NFADDRf(0X0);
//	mid = RDDATAB();
//	did = RDDATAB();
//	concare = RDDATAB();
//	id4th = RDDATAB();
//	NF_nFCE_H();
//	if(did==0xda) Print("IT IS DA!\n\r");
//}
//void NandInit(void){
//
//	SET_TACLS(0x0);
//        SET_TWRPH0(0X6);
//        SET_TWRPH1(0X2);
//        *NFCONF = (0X0<<12)|(0X6<<8)|(0X2<<4);
//	*NFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(0<<6)|(0<<5)|(1<<4)|(1<<1)|(1<<0);
//	*NFSTAT = 0;
//	NandReset();
//	NandCheckID();	
//}
void PortInit(void);
extern void Read2048Page(unsigned char* dst,volatile unsigned char* addr);
#define p_shift 11
#define b_shift_p 6 
//notice that the block size contain valid content
#define p_size (1<<p_shift)
#define b_size (p_size<<b_shift_p)
#define os_ram_start 0x30008000
#define os_nand_start 0x60000
#define os_length 0x500000

//unsigned int IsBadBlock(unsigned int addr){
//	
//	unsigned int row = addr>>11;
//	unsigned char bad_value;
//	NandReset();
//	NF_nFCE_L();
//	NF_CLEAR_RB();
//	NFCMDf(0x0);
//	//big or little endian is a problem
//	NFADDRf(2048&0xff);
//	NFADDRf((2048>>8)&0x0f);
//	NFADDRf(row&0xff);
//	NFADDRf((row>>8)&0xff);
//	NFADDRf((row>>16)&0x01);
//	NFCMDf(0x30);
//	DETECTRB();
//	bad_value = RDDATAB();
//	NF_nFCE_H();
//	if(bad_value == 0xff) return 0;
//	else return 1;//it is a bad block
//}
//extern void ReadPage512(unsigned char* buf,volatile unsigned char* nf_data_ptr);
//the unit of address is byte, but in vboot, read from boundary by default.
//void ReadOneSector(unsigned char* dst_addr,unsigned int src_addr){
//	
//	unsigned int row,col;
//	col = src_addr&0x0fff;
//	//row = (src_addr>>16)&0x1ffff;//>>16 is wrong, mislead by Page 9.the content of different address cycle.
//	row = src_addr>>11;
//	NandReset();
//	NF_nFCE_L();
//	NF_CLEAR_RB();
//	NFCMDf(0x00);
//	//NFADDRf(col&0xff);
//	NFADDRf(0x00);
//	//NFADDRf((col>>8)&0xff);
//	NFADDRf(0x00);
//	NFADDRf((row)&0xff);
//	NFADDRf((row>>8)&0xff);
//	NFADDRf((row>>16)&0xff);
//	NFCMDf(0x30);	
//	//Print("\r\nbefore!\r\n");
//	DETECTRB();
//	//Print("\r\nafter!\r\n");
//	//notice that read from NFDATA register
//	//Read2048Page(dst_addr,NFDATA);	
//	ReadPage512(dst_addr+0*512,NFDATA);
//	ReadPage512(dst_addr+1*512,NFDATA);
//	ReadPage512(dst_addr+2*512,NFDATA);
//	ReadPage512(dst_addr+3*512,NFDATA);
//	NF_nFCE_H();
//	///Print("\r\nso?!\r\n");
//}
//void* memset(void* dst,int src,unsigned int len){
//	char *p = dst;
//	while(len--)
//		*p++ = src;
//	return dst;	
//	
//}
const char cmdline[] = "noinitrd root=/dev/mtdblock3 init=/linuxrc console=ttySAC0";

//void memcpy(void* dst,const void* src,unsigned int size){
//
//	const char* s = src;
//	char * d = dst;
//	while(size--)
//		*d++ = *s++;
//
//}
void callinux(void);
void CopyLinuxFromNand(void);
	
int main(void){
	Print("nihao,huanyingni\n");
	PortInit();
	NandInit();	
//how to handle with the parameters	
	//unsigned int Buf[2048];
	//为什么要对地址进行类型声明？
	//ReadOneSector((unsigned char*)Buf,0x48000);	
	CopyLinuxFromNand();
	Print("before judege!");
	return 0;
}
void CopyLinuxFromNand(void){
 
         //get the address of os in nand
         unsigned int BlockNum,pos,Length;
         BlockNum = os_nand_start>>(p_shift+b_shift_p);
         Length = ((os_length+b_size-1)>>(p_shift+b_shift_p))<<(p_shift+b_shift_p);
         unsigned int ram_start = os_ram_start;
 
         for(pos=0;pos<Length;pos+=b_size){
                 unsigned int p_pos;
                 for(;;){
                         //if it is a good block, then break;
                         if(!IsBadBlock(BlockNum<<(p_shift+b_shift_p))){
                                 break;
                         }
                         BlockNum++;
                 }//for check if it is a block   
                 //
                 for(p_pos = 0;p_pos<b_size;p_pos+=p_size,ram_start+=p_size){
                         //source address: start address + offset
                         ReadOneSector((unsigned char*)ram_start,(BlockNum<<(p_shift+b_shift_p))+p_pos);
                 }//for copy sectors
                 BlockNum++;
         }//for copy loop
         //unsigned int*pp = (unsigned int*)(0x30008024);
         //if(pp[0]==0x016f2818) Print("\r\nSuo Long!!\r\n");
         //else Print("\r\nNot the right time!!\r\n");
         callinux();
 }

void callinux(void){
	
	struct param_struct {
                  union {
                          struct {
                                  unsigned long page_size;        /*  0 */
                                  unsigned long nr_pages; /*  4 */
                                  unsigned long ramdisk_size;     /*  8 */
                                  unsigned long flags;    /* 12 */
                                  unsigned long rootdev;  /* 16 */
                                  unsigned long video_num_cols;   /* 20 */
                                  unsigned long video_num_rows;   /* 24 */
                                  unsigned long video_x;  /* 28 */
                                  unsigned long video_y;  /* 32 */
                                  unsigned long memc_control_reg; /* 36 */
                                  unsigned char sounddefault;     /* 40 */
                                  unsigned char adfsdrives;       /* 41 */
                                  unsigned char bytes_per_char_h; /* 42 */
                                  unsigned char bytes_per_char_v; /* 43 */
                                  unsigned long pages_in_bank[4]; /* 44 */
                                  unsigned long pages_in_vram;    /* 60 */
                                  unsigned long initrd_start;     /* 64 */
                                  unsigned long initrd_size;      /* 68 */
                                  unsigned long rd_start; /* 72 */
                                  unsigned long system_rev;       /* 76 */
                                  unsigned long system_serial_low;        /* 8    0 */
                                  unsigned long system_serial_high;       /* 8    4 */
                                  unsigned long mem_fclk_21285;   /* 88 */
                          } s;
                          char unused[256];//Ö»ÓÃÀ´Õ¼ÓÃ¿Õ¼ä
                  } u1;
                  union {
                          char paths[8][128];
                          struct {
                                  unsigned long magic;
                                  char n[1024 - sizeof(unsigned long)];
                          } s;//1024¸ö×Ö½Ú
                  } u2;
                  char commandline[1024];
          };//struct paramter
	  struct param_struct *p = (struct param_struct*)(0x30000100);
	  memset(p,0,sizeof(struct param_struct));
	  p->u1.s.page_size = 4*1024;
	  p->u1.s.nr_pages = 64*1024*1024/(4*1024);
	  memcpy(p->commandline,cmdline,sizeof(cmdline)); 
	 asm(
	"mov r5,%2\n"	
	"mov r0,%0\n"
	"mov r1,%1\n"
	"mov ip,#0\n"
	"mov pc,r5\n"
	"nop\n" "nop\n":
	:"r"(0),"r"(1999),"r"(os_ram_start)
	
	); 
}//end of calinux
void PortInit(void){
          GPACON = 0X7FFFFF;
          GPBCON = 0X044555;
          GPBUP = 0X7FF;
          GPCCON = 0XAAAAAAAA;
          GPCUP = 0XFFFF;
          GPDCON = 0x00151544;
          GPDUP = 0x877a;
          GPDDAT = 0x0430;
          GPECON = 0xaa2aaaaa;
          GPEUP  = 0xf7ff;
          GPFCON = 0x55aa;
          GPFUP= 0xff;
          GPGCON = 1<<8;
          GPGDAT = 0;
          EXTINT0 = 0x22222222;
          EXTINT1 = 0x22222222;
          EXTINT2 = 0x22222222;
  }

