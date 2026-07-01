extern void *NNSi_FndAllocFromDefaultExpHeap(void);
extern void func_ov022_020911f0(void);
extern void func_ov022_02091254(void);
extern void *data_ov070_020b9c50;
extern void func_ov070_020b941c(void);
extern void *data_ov070_020b9c64;
extern void *data_ov070_020b9c78;
extern void func_ov070_020b9510(void);

asm void func_ov070_020b8ce0(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0x50
    mov     r4, r0
    mov     r0, #0x90
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
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    mov     r1, #2
    add     r0, r0, #0x60
    mov     r2, r1
    bl      func_ov022_020911f0
    mov     r1, #0
    ldr     r0, =0xD93
    str     r1, [sp, #4]
    str     r0, [sp]
    sub     r0, r0, #0xc6
    str     r0, [sp, #0x10]
    mov     r0, #0x12000
    str     r0, [sp, #0x14]
    mov     r0, #0x4000
    str     r0, [sp, #0x18]
    mov     r0, #0x3000
    str     r0, [sp, #0x40]
    mov     r0, #0x1e00
    str     r0, [sp, #0x44]
    mov     r0, #1
    str     r0, [sp, #0x3c]
    mov     r0, #0xcb
    strh    r0, [sp, #0x48]
    mov     r0, #4
    strh    r0, [sp, #0x4a]
    mov     r0, #0x100
    str     r0, [sp, #0x2c]
    str     r0, [sp, #0x34]
    mov     r0, #0x300
    str     r0, [sp, #0x30]
    mov     r0, #5
    str     r0, [sp, #0x38]
    mov     r0, #3
    strb    r0, [sp, #0x4c]
    strh    r1, [sp, #0xa]
    str     r1, [sp, #0x1c]
    str     r1, [sp, #0x20]
    str     r1, [sp, #0x28]
    ldr     r1, =0x99A
    add     r0, r4, #0x2000
    str     r1, [sp, #0xc]
    ldr     r0, [r0, #0x644]
    ldr     r2, =data_ov070_020b9c50
    mov     r1, r4
    add     r3, sp, #0
    bl      func_ov022_02091254
    add     r0, r4, #0x2000
    ldr     r3, =func_ov070_020b941c
    ldr     r2, [r0, #0x644]
    ldr     r1, =0x783
    str     r3, [r2, #0x20]
    mov     lr, #0
    str     r1, [sp]
    add     r1, r1, #0xbb0
    str     r1, [sp, #0xc]
    ldr     r2, =0xCCD
    mov     r1, #0xf000
    str     r1, [sp, #0x14]
    mov     r1, #0x7000
    str     lr, [sp, #4]
    strh    lr, [sp, #0xa]
    str     lr, [sp, #0x1c]
    str     lr, [sp, #0x20]
    str     lr, [sp, #0x28]
    str     r2, [sp, #0x10]
    str     r1, [sp, #0x18]
    mov     r5, #0x200
    mov     r12, #1
    mov     r7, #0xcb
    mov     r6, #4
    mov     r3, #0x400
    mov     r2, #5
    mov     r1, #3
    str     r3, [sp, #0x30]
    str     r2, [sp, #0x38]
    strb    r1, [sp, #0x4c]
    str     lr, [sp, #0x40]
    str     r12, [sp, #0x3c]
    strh    r7, [sp, #0x48]
    strh    r6, [sp, #0x4a]
    str     r5, [sp, #0x2c]
    str     r5, [sp, #0x34]
    ldr     r0, [r0, #0x644]
    ldr     r2, =data_ov070_020b9c64
    add     r3, sp, #0
    mov     r1, r4
    add     r0, r0, #0x30
    bl      func_ov022_02091254
    add     r2, r4, #0x2000
    ldr     r0, [r2, #0x644]
    ldr     r1, =func_ov070_020b941c
    ldr     r3, =0x783
    str     r1, [r0, #0x50]
    mov     r0, #0
    mov     r1, #1
    mov     r5, #0x100
    ldr     r7, =0x99A
    mov     r6, #0x1800
    mov     lr, #0x12000
    mov     r12, #0x9000
    str     r3, [sp]
    mov     r3, #0x2000
    str     r7, [sp, #0xc]
    mov     r7, #0xcb
    str     r6, [sp, #0x10]
    mov     r6, #4
    str     lr, [sp, #0x14]
    mov     lr, #0x300
    str     r12, [sp, #0x18]
    mov     r12, #0x25
    str     r3, [sp, #0x40]
    mov     r3, #3
    strb    r3, [sp, #0x4c]
    strh    r7, [sp, #0x48]
    str     r1, [sp, #4]
    str     r1, [sp, #0x3c]
    strh    r6, [sp, #0x4a]
    str     r5, [sp, #0x2c]
    str     lr, [sp, #0x30]
    str     r5, [sp, #0x34]
    str     r12, [sp, #0x38]
    strh    r0, [sp, #0xa]
    str     r0, [sp, #0x1c]
    str     r0, [sp, #0x20]
    str     r0, [sp, #0x28]
    ldr     r0, [r2, #0x644]
    ldr     r2, =data_ov070_020b9c78
    add     r3, sp, #0
    mov     r1, r4
    add     r0, r0, #0x60
    bl      func_ov022_02091254
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    ldr     r1, =func_ov070_020b9510
    str     r1, [r0, #0x80]
    add     sp, sp, #0x50
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
