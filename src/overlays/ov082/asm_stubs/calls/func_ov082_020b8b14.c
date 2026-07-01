extern void func_ov082_020b8b5c(void);

asm void func_ov082_020b8b14(void)
{
    dcd     0xe92d4010
    dcd     0xe3a01002
    dcd     0xe1a04000
    bl      func_ov082_020b8b5c
    dcd     0xe3a00005
    dcd     0xe5c4012c
    mov r0, #0
    dcd     0xe5840130
    dcd     0xe8bd8010
}
