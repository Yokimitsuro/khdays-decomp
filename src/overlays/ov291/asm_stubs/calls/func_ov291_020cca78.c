extern void func_ov022_020ad114(void);

asm void func_ov291_020cca78(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x03a00000
    dcd     0x08bd8010
    dcd     0xe2940e4f
    dcd     0x0a000002
    dcd     0xe5d00000
    dcd     0xe3500001
    dcd     0x0a000001
    mov r0, #0
    dcd     0xe8bd8010
    mov r0, #1
    dcd     0xe8bd8010
}
