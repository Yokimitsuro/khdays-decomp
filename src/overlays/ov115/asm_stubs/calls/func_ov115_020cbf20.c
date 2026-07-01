extern void func_ov107_020c2f7c(void);
extern void func_ov115_020cbf38(void);

asm void func_ov115_020cbf20(void)
{
    ldr ip, [pc, #8]
    ldr r1, [pc, #8]
    mov r0, #1
    bx  ip
    dcd     func_ov107_020c2f7c
    dcd     func_ov115_020cbf38
}
