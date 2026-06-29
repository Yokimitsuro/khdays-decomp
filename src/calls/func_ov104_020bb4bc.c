extern char data_ov104_020bc2a0[];
extern void func_ov104_020bb60c(void);

asm void func_ov104_020bb4bc(void)
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
    bl      func_ov104_020bb60c
    dcd     0xe3a00000
    dcd     0xe5840120
    dcd     0xe8bd8010
    dcd     data_ov104_020bc2a0
}
