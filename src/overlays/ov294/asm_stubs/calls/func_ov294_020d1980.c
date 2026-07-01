extern void func_ov107_020c2f7c(void);
extern void func_ov294_020d1998(void);

asm void func_ov294_020d1980(void)
{
    ldr     ip, =func_ov107_020c2f7c
    ldr     r1, =func_ov294_020d1998
    mov     r0, #0x70
    bx      ip
}
