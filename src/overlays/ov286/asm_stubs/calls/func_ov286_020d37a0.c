extern void func_ov107_020c2f7c(void);
extern void func_ov286_020d37b8(void);

asm void func_ov286_020d37a0(void)
{
    ldr     ip, =func_ov107_020c2f7c
    ldr     r1, =func_ov286_020d37b8
    mov     r0, #0x6a
    bx      ip
}
