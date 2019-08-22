#include "s3c2440-regsaddr.h"
.section .text.vector
	b Reset
UndefEntryPoint:
	b UndefEntryPoint
SWIEntryPoint:
	b SWIEntryPoint
PrefetchAbortEntryPoint:
	b PrefetchAbortEntryPoint
DataAbortEntryPoint:
	b DataAbortEntryPoint
NotUsedEntryPoint:
	b NotUsedEntryPoint
IRQEntryPoint:
	b IRQEntryPoint
@0x1c size space
FIQEntryPoint:
	b FIQEntryPoint
.section .text
Reset:
////////////////////////////////////////////////////////////////////////////////////////////////

	ldr r0,=0x53000000
	ldr r1,=0x0000
	str r1,[r0]
	ldr r0,=0x4A000000//Ê¹ÓÃµÄÎ±Ö¸Áî£¬OK
	ldr r1,=0xffffffff
	str r1,[r0]
	ldr r0,=0x4A000008
	ldr r1,=0xffffffff
	str r1,[r0]
	ldr r0,=0x4A00001c
	ldr r1,=0xffffffff
	str r1,[r0]
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr r0,=CLKCFG_BASEADDR
	ldr r1,=LOCKTIME_CFGVALUE
	str r1,[r0,#LOCKTIME_OFFSET]
	ldr r1,=UPLLCON_CFGVAL
	str r1,[r0,#UPLLCON_OFFSET]
	ldr r1,=CLKDIVN_CFGVAL
	str r1,[r0,#CLKDIVN_OFFSET]
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000
	mcr p15,0,r0,c1,c0,0
	ldr r0,=CLKCFG_BASEADDR
	ldr r1,=MPLLCON_CFGVAL
	str r1,[r0,#MPLLCON_OFFSET]
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr sp,=SP
//////////////////////////////////////////////////////////////////////////////////////////////////
 	bl memsetup
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr r0,=0x0016faaa
	ldr r1,=GPH_CON
	str r0,[r1]
	ldr r0,=0x000007ff
	ldr r1,=GPH_UP
	str r0,[r1]
//
//	ldr r0,=0x55555555
//	ldr r1,=GPB_CON
//	str r0,[r1]
//	ldr r0,=0xffffffff
//	ldr r1,=GPB_UP
//	str r0,[r1]
//	ldr r0,=0x0
//	ldr r1,=GPB_DAT
//	str r0,[r1]
////////////////////////////////////////////////////////////////////////////////////////////////
	ldr r0,=ULCON0
	ldr r1,=0x03
	str r1,[r0]
	//UCON 0b0000_00_0_1_0_1_0_0_01_01
	ldr r0,=UCON0
	ldr r1,=0x245
	str r1,[r0]
	//UFCON 0b00_00_0_0_0_0
	ldr r0,=UFCON0
	ldr r1,=0x0
	str r1,[r0]
	//UMCON 0b00000000
	ldr r0,=UMCON0
	ldr r1,=0x0
	str r1,[r0]
	//UBRDIV UBRDIV
	ldr r0,=UBRDIV0
	ldr r1,=UBRDIVVAL
	str r1,[r0]
	mov r3,#100
	mov r2,#0
	1:sub r3,r3,#0x1
	tst r2,r3
	bne 1b
	
//	ldr r0,=0x32000000
//	ldr r1,=0x12345678
//	str r1,[r0]
//	ldr r2,=0x0
//	ldr r2,[r0]
//	cmp r1,r2
	bl main
1:	b 1b
memsetup:
         mov     r1, #MEMCFG_BASE
         adrl    r2, MEMCFG_POOL
         add     r3, r1, #52
 1:      ldr     r4, [r2], #4
         str     r4, [r1], #4
         cmp     r1, r3
         bne     1b
         mov     pc, lr
//
//	ldr r0,=MEMCFG_BASE
//	ldr r1,MEMCFG_POOL
//	mov r2,#0
//1:      ldr r3,[r1],#4
//	str r3,[r0],#4
//	add r2,r2,#1
//	cmp r2,#13
//	bne 1b
//	mov pc,lr
//.global Read2048Page
//Read2048Page:
//	stmfd sp!,{r2,r7}
//	//r0,dst;r1,src
//	mov r2,#0
//1:	ldr r3,[r1]
//	ldr r4,[r1]
//	ldr r5,[r1]
//	ldr r6,[r1] 
//	//there are some limits about the num of data?
//	stmia r0!,{r3-r6}
//	ldr r3,[r1]
//        ldr r4,[r1]
//        ldr r5,[r1]
//        ldr r6,[r1] 
//        //there are some 
//        stmia r0!,{r3-r6}
//	ldr r3,[r1]
//        ldr r4,[r1]
//        ldr r5,[r1]
//        ldr r6,[r1] 
//        //there are some 
//        stmia r0!,{r3-r6}
//	ldr r3,[r1]
//        ldr r4,[r1]
//        ldr r5,[r1]
//        ldr r6,[r1] 
//        //there are some 
//	stmia r0!,{r3-r6}
//	ldr r3,=UTXH0
//	ldr r4,=0x31
//	str r4,[r3]
//	add r2,r2,#1
//	cmp r2,#32
//	bne 1b
//	ldmfd sp!,{r2-r7}
//	mov pc,lr
.global ReadPage512
ReadPage512:
        stmfd   sp!, {r2-r7}//{r2,r3,r5-r7}¿¿¿¿¿¿¿¿¿
        mov     r2, #0x200//¿¿¿¿512
1:
        ldr     r4, [r1]//¿NANDFlash¿¿¿¿¿¿¿
        ldr     r5, [r1]
        ldr     r6, [r1]
        ldr     r7, [r1]
        stmia   r0!, {r4-r7}
        ldr     r4, [r1]
        ldr     r5, [r1]
        ldr     r6, [r1]
        ldr     r7, [r1]
        stmia   r0!, {r4-r7}
        ldr     r4, [r1]
        ldr     r5, [r1]
        ldr     r6, [r1]
        ldr     r7, [r1]
        stmia   r0!, {r4-r7}
        ldr     r4, [r1]
        ldr     r5, [r1]
        ldr     r6, [r1]
        ldr     r7, [r1]
        stmia   r0!, {r4-r7}
        subs    r2, r2, #64
        bne     1b;
        ldmfd   sp!, {r2-r7}
        mov     pc,lr

.align 4
MEMCFG_POOL:
.long 	vBWSCON
.long	vBANKCON0
.long	vBANKCON1 
.long	vBANKCON2 
.long	vBANKCON3
.long	vBANKCON4
.long	vBANKCON5
.long	vBANKCON6
.long	vBANKCON7
.long	vREFRESH
.long	vBANKSIZE
.long	vMRSRB6
.long	vMRSRB7



	
