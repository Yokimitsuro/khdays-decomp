extern void func_0203c634(void);
extern void func_ov234_020ccef4(void);

asm void func_ov234_020ccedc(void *r0)
{
    ldr     ip, =func_0203c634
    ldrsb   r1, [r0, #0x20]
    ldr     r2, =func_ov234_020ccef4
    bx      ip
}
