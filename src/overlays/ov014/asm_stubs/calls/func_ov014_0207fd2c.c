extern void func_0202af1c(void);
extern void func_0202af2c(void);

asm void func_ov014_0207fd2c(void)
{
    dcd     0xe92d4008
    dcd     0xe3510000
    dcd     0x0a000003
    dcd     0xe3510001
    dcd     0x0a000007
    dcd     0xe3510002
    dcd     0xe8bd8008
    dcd     0xe5901038
    dcd     0xe3110020
    dcd     0x18bd8008
    dcd     0xe280003c
    bl      func_0202af2c
    dcd     0xe8bd8008
    dcd     0xe5901038
    dcd     0xe3110020
    dcd     0x18bd8008
    dcd     0xe280003c
    bl      func_0202af1c
    dcd     0xe8bd8008
}
