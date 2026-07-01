extern void func_ov002_0207285c(void);
extern void func_0202ba9c(void);

asm void func_ov017_0207fd88(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5d40010
    bl      func_ov002_0207285c
    dcd     0xe1a01800
    dcd     0xe3a02000
    dcd     0xe1a03002
    dcd     0xe284002c
    dcd     0xe1a01821
    bl      func_0202ba9c
    dcd     0xe8bd8010
}
