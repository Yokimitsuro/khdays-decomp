extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern char data_ov066_020b6b54[];
extern void func_ov022_020911f0(void);
extern void func_ov022_02091298(void);
extern void func_ov066_020b6398(void);

asm void func_ov066_020b623c(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0xa8
    mov     r4, r0
    mov     r0, #0x30
    bl      NNSi_FndAllocFromDefaultExpHeap
    add     r2, r4, #0x2000
    mov     r1, #0
    str     r0, [r2, #0x644]
    mov     r2, r1
    bl      func_ov022_020911f0
    mov     r7, #0
    mov     r2, #0x100
    ldr     ip, [pc, #0xc0]
    mov     r6, #0x800
    mov     r3, #0x2000
    mov     r1, #0x300
    mov     r5, #5
    mov     r0, #0xa
    str     ip, [sp, #8]
    add     lr, sp, #8
    add     ip, sp, #0x58
    str     r6, [sp, #0x14]
    str     r7, [sp, #0xc]
    strh    r7, [sp, #0x12]
    str     r7, [sp, #0x18]
    str     r7, [sp, #0x1c]
    str     r7, [sp, #0x20]
    str     r7, [sp, #0x24]
    str     r7, [sp, #0x28]
    str     r7, [sp, #0x30]
    str     r3, [sp, #0x48]
    str     r2, [sp, #0x34]
    str     r1, [sp, #0x38]
    str     r2, [sp, #0x3c]
    str     r5, [sp, #0x40]
    strb    r0, [sp, #0x54]
_L0090:
    ldmia   lr!, {r0, r1, r2, r3}
    stmia   ip!, {r0, r1, r2, r3}
    subs    r5, r5, #1
    bne     _L0090
    ldr     r1, [sp, #0x58]
    ldr     r0, [sp, #0x90]
    orr     r1, r1, #0x200
    orr     r0, r0, #0x20
    str     r1, [sp, #0x58]
    str     r0, [sp, #0x90]
    mov     r0, #2
    str     r0, [sp]
    mov     r0, #0xa
    str     r0, [sp, #4]
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    ldr     r2, [pc, #0x24]
    add     r3, sp, #8
    mov     r1, r4
    bl      func_ov022_02091298
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    ldr     r1, [pc, #0x10]
    str     r1, [r0, #0x20]
    add     sp, sp, #0xa8
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
    andeq   r0, r0, r9, asr #3
    dcd     data_ov066_020b6b54
    dcd     func_ov066_020b6398
}
