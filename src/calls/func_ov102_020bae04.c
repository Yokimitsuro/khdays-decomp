extern void func_0202a634(void);
extern void func_ov102_020bafdc(void);
extern char data_ov102_020bb920[];
extern char data_ov102_020bb8e0[];

asm void func_ov102_020bae04(void)
{
    stmdb   sp!, {r4, lr}
    ldr     r0, =data_ov102_020bb920
    mov     r3, #0
    ldr     r4, [r0]
    ldr     r1, =data_ov102_020bb8e0
    add     r0, r4, #0xc50
    add     r2, r4, #0x2000
    add     r0, r0, #0x2000
    str     r3, [r2, #0xc50]
    str     r3, [r0, #0x10]
    ldrb    r3, [r4, #9]
    add     r0, r0, #0x14
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202a634
    mov     r0, r4
    bl      func_ov102_020bafdc
    ldmia   sp!, {r4, pc}
}
