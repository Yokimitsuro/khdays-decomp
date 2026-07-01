extern void func_ov107_020c2f7c(void);
extern void func_ov117_020cbf38(void);

asm void func_ov117_020cbf20(void)
{
    ldr     ip, =func_ov107_020c2f7c
    ldr     r1, =func_ov117_020cbf38
    mov     r0, #2
    bx      ip
}
