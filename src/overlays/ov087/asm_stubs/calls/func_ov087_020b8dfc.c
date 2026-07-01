extern char data_ov087_020b9be0[];
extern void func_ov087_020b8f4c(void);

asm void func_ov087_020b8dfc(void)
{
    dcd     0xe92d4010
    dcd     0xe59f2028
    dcd     0xe2801a02
    dcd     0xe5923000
    dcd     0xe5912640
    dcd     0xe28310fc
    dcd     0xe2814b0b
    dcd     0xe2821004
    dcd     0xe584110c
    bl      func_ov087_020b8f4c
    mov r0, #0
    dcd     0xe5840120
    dcd     0xe8bd8010
    dcd     data_ov087_020b9be0
}
