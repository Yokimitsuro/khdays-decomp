extern void func_ov107_020c2f7c(void);
extern void func_ov241_020cfb78(void);

asm void func_ov241_020cfb60(void)
{
    ldr     ip, =func_ov107_020c2f7c
    ldr     r1, =func_ov241_020cfb78
    mov     r0, #0x44
    bx      ip
}
