extern void func_0202a634(void);
extern void func_ov022_02092384(void);
extern void func_ov068_020b6754(void);
extern void *data_ov068_020b7500;
extern void *data_ov068_020b7498;
extern void *data_ov068_020b7344;

asm void func_ov068_020b625c(void)
{
    stmfd   sp!, {r3, r4, r5, r6, lr}
    sub     sp, sp, #0x14
    ldr     r1, =data_ov068_020b7500
    mov     r3, #0
    ldr     r4, [r1]
    ldr     r1, =data_ov068_020b7498
    add     r2, r4, #0x2000
    strb    r3, [r2, #0xcfc]
    ldrb    r3, [r4, #9]
    add     r2, r4, #0xfc
    add     r2, r2, #0x2c00
    mov     r5, r0
    add     r0, r2, #4
    add     r3, r3, #7
    mov     r2, #1
    bl      func_0202a634
    ldr     ip, =data_ov068_020b7344
    add     r6, sp, #0
    ldmia   ip!, {r0, r1, r2, r3}
    mov     lr, r6
    stmia   r6!, {r0, r1, r2, r3}
    ldr     ip, [ip]
    add     r0, r5, #0x248
    str     ip, [r6]
    ldrb    r1, [r5, #9]
    mov     r3, lr
    add     r0, r0, #0x2400
    mov     r2, #5
    bl      func_ov022_02092384
    mov     r0, r4
    bl      func_ov068_020b6754
    add     sp, sp, #0x14
    ldmfd   sp!, {r3, r4, r5, r6, pc}
}
