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



typedef struct {
    u8 * destp;
    s32 destCount;
    u32 length;
    u16 destTmp;
    u8 destTmpCnt;
    u8 flags;
    u8 flagIndex;
    u8 lengthFlg;
    u8 exFormat;
    u8 _padding[1];
} MIUncompContextLZ;

/* func_02004484 -- NitroSDK mi_uncomp_stream.c: MI_ReadUncompLZ8. */
asm s32 func_02004484 (register MIUncompContextLZ * context, register const u8 * data, register u32 len)
{
    stmfd sp !, {r4 - r11}
    ldr r3, [r0, #MIUncompContextLZ.destp]
    ldr r4, [r0, #MIUncompContextLZ.destCount]
    ldrb r5, [r0, #MIUncompContextLZ.flags]
    ldrb r6, [r0, #MIUncompContextLZ.flagIndex]
    ldr r7, [r0, #MIUncompContextLZ.length]
    ldrb r8, [r0, #MIUncompContextLZ.lengthFlg]
    ldrb r11, [r0, #MIUncompContextLZ.exFormat]
@21:
    cmp r4, #0
    ble @29
    cmp r6, #0
    beq @28
@22
    cmp r2, #0
    beq @29
    tst r5, #0x80
    bne @23
    ldrb r9, [r1], #1
    sub r4, r4, #1
    sub r2, r2, #1
#ifdef MI_USE_STRB
    strb r9, [r3], #1
#else
    swpb r9, r9, [r3]
    add r3, r3, #1
#endif
    b @26
@23:
    cmp r8, #0
    beq @24
    cmp r11, #1
    bne @23_9
    subs r8, r8, #1
    beq @23_7
    cmp r8, #1
    beq @23_6
    ldrb r7, [r1], #1
    tst r7, #0xE0
    beq @23_4
    add r7, r7, #0x10
    mov r8, #0
    b @23_10
@23_4:
    mov r10, #0x110
    tst r7, #0x10
    beq @23_5
    and r7, r7, #0xF
    add r10, r10, #0x1000
    add r7, r10, r7, lsl #16
    b @23_8
@23_5:
    and r7, r7, #0xF
    add r7, r10, r7, lsl #8
    mov r8, #1
    b @23_8
@23_6:
    ldrb r10, [r1], #1
    add r7, r7, r10, lsl #8
    b @23_8
@23_7:
    ldrb r10, [r1], #1
    add r7, r7, r10
    b @23_10
@23_8:
    subs r2, r2, #1
    beq @29
    b @23
@23_9:
    ldrb r7, [r1], #1
    add r7, r7, #0x30
    mov r8, #0
@23_10:
    subs r2, r2, #1
    beq @29
@24:
    and r9, r7, #0xF
    mov r10, r9, lsl #8
    ldrb r9, [r1], #1
    mov r8, #3
    sub r2, r2, #1
    orr r9, r9, r10
    add r9, r9, #1
    movs r7, r7, asr #4
    beq @26
@25:
    ldrb r10, [r3, -r9]
    sub r4, r4, #1
#ifdef MI_USE_STRB
    strb r10, [r3], #1
#else
    swpb r10, r10, [r3]
    add r3, r3, #1
#endif
    subs r7, r7, #1
    bgt @25
@26:
    cmp r4, #0
    beq @29
    mov r5, r5, lsl #1
    subs r6, r6, #1
    bne @22
@28:
    cmp r2, #0
    beq @29
    ldrb r5, [r1], #1
    mov r6, #8
    sub r2, r2, #1
    b @21
@29:
    str r3, [r0, #MIUncompContextLZ.destp]
    str r4, [r0, #MIUncompContextLZ.destCount]
    strb r5, [r0, #MIUncompContextLZ.flags]
    strb r6, [r0, #MIUncompContextLZ.flagIndex]
    str r7, [r0, #MIUncompContextLZ.length]
    strb r8, [r0, #MIUncompContextLZ.lengthFlg]
    strb r11, [r0, #MIUncompContextLZ.exFormat]
    mov r0, r4
    ldmfd sp !, {r4 - r11}
    bx lr
}
