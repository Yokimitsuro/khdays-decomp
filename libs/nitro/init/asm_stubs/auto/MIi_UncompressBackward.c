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

#define HW_CACHE_LINE_SIZE 32
#define inp_top r1
#define outp r2
#define inp r3
#define outp_save r4
#define flag r5
#define count8 r6
#define index r7
#define len r12

typedef enum {
    PXI_FIFO_TAG_EX = 0,
    PXI_FIFO_TAG_USER_0,
    PXI_FIFO_TAG_USER_1,
    PXI_FIFO_TAG_SYSTEM,
    PXI_FIFO_TAG_NVRAM,
    PXI_FIFO_TAG_RTC,
    PXI_FIFO_TAG_TOUCHPANEL,
    PXI_FIFO_TAG_SOUND,
    PXI_FIFO_TAG_PM,
    PXI_FIFO_TAG_MIC,
    PXI_FIFO_TAG_WM,
    PXI_FIFO_TAG_FS,
    PXI_FIFO_TAG_OS,
    PXI_FIFO_TAG_CTRDG,
    PXI_FIFO_TAG_CARD,
    PXI_FIFO_TAG_WVR,
    PXI_FIFO_TAG_CTRDG_Ex,
    PXI_FIFO_TAG_CTRDG_PHI,
    PXI_MAX_FIFO_TAG = 32
} PXIFifoTag;
typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);

/* MIi_UncompressBackward -- NitroSDK init/crt0.c: MIi_UncompressBackward. */
asm void  MIi_UncompressBackward (register void *bottom)
{
#define data            r0
#define inp_top         r1
#define outp            r2
#define inp             r3
#define outp_save       r4
#define flag            r5
#define count8          r6
#define index           r7
#define len             r12
	cmp bottom, #0
	beq @exit
	stmfd sp !, {r4 - r7}
	ldmdb bottom, {r1 - r2}
	add outp, bottom, outp
	sub inp, bottom, inp_top, LSR #24
	bic inp_top, inp_top, #0xff000000
	sub inp_top, bottom, inp_top
	mov outp_save, outp
@loop:
	cmp inp, inp_top
	ble @end_loop
	ldrb flag, [inp, #- 1] !
	mov count8, #8
@loop8:
	subs count8, count8, #1
	blt @loop
	tst flag, #0x80
	bne @blockcopy
@bytecopy:
	ldrb data, [inp, #- 1] !
#ifdef  SDK_TEG
	sub outp, outp, #1
	swpb data, data, [outp]
#else
	strb data, [outp, #- 1] !
#endif
	b @joinhere
@blockcopy:
	ldrb len, [inp, #- 1] !
	ldrb index, [inp, #- 1] !
	orr index, index, len, LSL #8
	bic index, index, #0xf000
	add index, index, #0x0002
	add len, len, #0x0020
@patterncopy:
	ldrb data, [outp, index]
#ifdef  SDK_TEG
	sub outp, outp, #1
	swpb data, data, [outp]
#else
	strb data, [outp, #- 1] !
#endif
	subs len, len, #0x0010
	bge @patterncopy
@joinhere:
	cmp inp, inp_top
	mov flag, flag, LSL #1
	bgt @loop8
@end_loop:
	mov r0, #0
	bic inp, inp_top, #HW_CACHE_LINE_SIZE - 1
@cacheflush:
	mcr p15, 0, r0, c7, c10, 4
	mcr p15, 0, inp, c7, c5, 1
	mcr p15, 0, inp, c7, c14, 1
	add inp, inp, #HW_CACHE_LINE_SIZE
	cmp inp, outp_save
	blt @cacheflush
	ldmfd sp !, {r4 - r7}
	@exit bx lr
}
