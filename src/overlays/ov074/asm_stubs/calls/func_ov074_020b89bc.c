extern char data_ov074_020b9b80[];
extern void func_0202a7dc(void);
extern void func_ov074_020b911c(void);

asm void func_ov074_020b89bc(void)
{
    dcd     0xe92d4010
    dcd     0xe59f101c
    dcd     0xe1a04000
    dcd     0xe5910000
    dcd     0xe28000b8
    dcd     0xe2800b0b
    bl      func_0202a7dc
    dcd     0xe1a00004
    bl      func_ov074_020b911c
    dcd     0xe8bd8010
    dcd     data_ov074_020b9b80
}
