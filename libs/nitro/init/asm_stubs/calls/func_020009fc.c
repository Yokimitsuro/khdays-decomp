/* NitroSDK original assembly (libraries/init/src/crt0.c: do_autoload). */

extern void MIi_UncompressBackward(void);
extern void AutoloadCallback(void);

#define HW_CACHE_LINE_SIZE               0x20
#define _start_AutoloadDoneCallback      AutoloadCallback
#define _start_ModuleParams              0x02000b68

asm void func_020009fc (void)
{
#define ptable          r0
#define infop           r1
#define infop_end       r2
#define src             r3
#define dest            r4
#define dest_begin      r5
#define dest_end        r6
#define tmp             r7
	ldr ptable, = _start_ModuleParams
	ldr infop, [ptable, #0]
	ldr infop_end, [ptable, #4]
	ldr src, [ptable, #8]
@2:
	cmp infop, infop_end
	beq @skipout
	ldr dest_begin, [infop], #4
	ldr tmp, [infop], #4
	add dest_end, dest_begin, tmp
	mov dest, dest_begin
@1:
	cmp dest, dest_end
	ldrmi tmp, [src], #4
	strmi tmp, [dest], #4
	bmi @1
	ldr tmp, [infop], #4
	add dest_end, dest, tmp
	mov tmp, #0
@3:
	cmp dest, dest_end
	strcc tmp, [dest], #4
	bcc @3
	bic dest, dest_begin, #HW_CACHE_LINE_SIZE - 1
@cacheflush:
	mcr p15, 0, tmp, c7, c10, 4
	mcr p15, 0, dest, c7, c5, 1
	mcr p15, 0, dest, c7, c14, 1
	add dest, dest, #HW_CACHE_LINE_SIZE
	cmp dest, dest_end
	blt @cacheflush
	b @2
@skipout:
	b _start_AutoloadDoneCallback
}
