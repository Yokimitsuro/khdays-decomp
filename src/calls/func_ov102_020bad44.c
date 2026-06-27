extern void func_ov102_020baef0(void);
extern void func_ov102_020baf50(void);
extern char data_ov102_020bb920[];

asm void func_ov102_020bad44(void *self)
{
    stmdb   sp!, {r3, r4, r5, lr}
    ldr     r2, =data_ov102_020bb920
    mov     r5, r0
    add     r1, r5, #0x2a00
    ldr     r3, [r2]
    ldrsh   r2, [r1, #0xba]
    add     r4, r3, #0xc50
    add     r1, r4, #0x2000
    bl      func_ov102_020baef0
    mov     r0, r5
    add     r1, r4, #0x2000
    bl      func_ov102_020baf50
    ldmia   sp!, {r3, r4, r5, pc}
}
