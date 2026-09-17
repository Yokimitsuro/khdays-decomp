typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))





/* GXi_NopClearFifo128_ -- NitroSDK g3x.c: GXi_NopClearFifo128_. */
asm void GXi_NopClearFifo128_ (register void *pDest)
{
	mov r1, #0
	mov r2, #0
	mov r3, #0
	mov r12, #0
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	bx lr
}
