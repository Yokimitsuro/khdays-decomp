extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern int data_ov098_020bbd68;
extern int data_ov098_020bbd7c;
extern void func_ov022_020911f0(void);
extern void func_ov022_02091254(void);
extern void func_ov022_02091298(void);
extern void func_ov098_020bb634(void);
extern void func_ov098_020bb740(void);

asm void func_ov098_020bb3c0(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    sub     sp, sp, #0x148
    mov     r4, r0
    mov     r0, #0x60
    bl      NNSi_FndAllocFromDefaultExpHeap
    add     r1, r4, #0x2000
    str     r0, [r1, #0x644]
    mov     r1, #0
    mov     r2, #2
    bl      func_ov022_020911f0
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    mov     r1, #1
    add     r0, r0, #0x30
    mov     r2, #0
    bl      func_ov022_020911f0
    mov     r0, #0
    ldr     r1, =0xd93
    mov     r3, #0x100
    add     r5, r1, #0xd3
    sub     r2, r1, #0xc6
    str     r1, [sp, #8]
    mov     r1, #0xa000
    mov     r6, #0x12000
    str     r5, [sp, #0x14]
    mov     r5, #0x2000
    str     r2, [sp, #0x18]
    mov     r2, #1
    str     r1, [sp, #0x20]
    mov     r1, #0xc7
    str     r6, [sp, #0x1c]
    mov     r6, #0x12c0
    str     r5, [sp, #0x48]
    mov     r5, #4
    str     r2, [sp, #0x44]
    mov     r2, #0x300
    mov     r7, #5
    strh    r1, [sp, #0x50]
    mov     r1, #6
    str     r6, [sp, #0x4c]
    strh    r5, [sp, #0x52]
    add     r6, sp, #8
    str     r2, [sp, #0x38]
    add     r5, sp, #0x58
    strb    r1, [sp, #0x54]
    str     r0, [sp, #0xc]
    strh    r0, [sp, #0x12]
    str     r0, [sp, #0x24]
    str     r0, [sp, #0x28]
    str     r0, [sp, #0x30]
    str     r3, [sp, #0x34]
    str     r3, [sp, #0x3c]
    str     r7, [sp, #0x40]
_L_00d4:
    ldmia   r6!, {r0, r1, r2, r3}
    stmia   r5!, {r0, r1, r2, r3}
    subs    r7, r7, #1
    bne     _L_00d4
    mov     r0, #2
    add     r7, sp, #8
    add     r6, sp, #0xa8
    str     r0, [sp, #0x94]
    mov     r5, #5
_L_00f8:
    ldmia   r7!, {r0, r1, r2, r3}
    stmia   r6!, {r0, r1, r2, r3}
    subs    r5, r5, #1
    bne     _L_00f8
    mov     r0, #3
    str     r0, [sp, #0xe4]
    str     r0, [sp]
    mov     r0, #6
    str     r0, [sp, #4]
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    ldr     r2, =data_ov098_020bbd68
    add     r3, sp, #8
    mov     r1, r4
    bl      func_ov022_02091298
    add     r3, r4, #0x2000
    ldr     r0, [r3, #0x644]
    ldr     r1, =func_ov098_020bb634
    ldr     r7, =0x783
    str     r1, [r0, #0x20]
    mov     r5, #0x1000
    mov     ip, #0x1800
    mov     r2, #0x12000
    str     r7, [sp, #0xf8]
    str     r5, [sp, #0x104]
    str     ip, [sp, #0x108]
    str     r2, [sp, #0x10c]
    mov     r1, #0xc7
    add     r2, sp, #0x108
    strh    r1, [r2, #0x38]
    mov     r0, #0
    str     r0, [sp, #0xfc]
    add     r1, sp, #8
    strh    r0, [r1, #0xfa]
    mov     r8, #0x4000
    mov     r7, #4
    str     r8, [sp, #0x110]
    str     r0, [sp, #0x114]
    str     r0, [sp, #0x118]
    str     r0, [sp, #0x120]
    str     r8, [sp, #0x138]
    str     r0, [sp, #0x134]
    strh    r7, [r2, #0x3a]
    mov     r6, #0x100
    mov     r5, #0x300
    mov     lr, #0x25
    mov     ip, #1
    str     r6, [sp, #0x124]
    str     r5, [sp, #0x128]
    str     r6, [sp, #0x12c]
    str     lr, [sp, #0x130]
    strb    ip, [sp, #0x144]
    ldr     r0, [r3, #0x644]
    ldr     r2, =data_ov098_020bbd7c
    add     r3, sp, #0xf8
    mov     r1, r4
    add     r0, r0, #0x30
    bl      func_ov022_02091254
    add     r0, r4, #0x2000
    ldr     r2, [r0, #0x644]
    ldr     r3, =func_ov098_020bb634
    ldr     r1, =func_ov098_020bb740
    str     r3, [r2, #0x50]
    ldr     r0, [r0, #0x644]
    str     r1, [r0, #0x54]
    add     sp, sp, #0x148
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
