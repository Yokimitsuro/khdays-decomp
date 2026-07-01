extern void func_0202fae8(void);
extern void func_0202fb8c(void);
extern void func_ov012_0205c048(void);

asm void func_ov012_0205bbac(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    bl      func_0202fae8
    dcd     0xe5941054
    dcd     0xe594205c
    dcd     0xe0811000
    dcd     0xe0820001
    dcd     0xe584005c
    dcd     0xe0803001
    dcd     0xe5942054
    dcd     0xe5940044
    dcd     0xe0432002
    dcd     0xe1520000
    dcd     0xda000004
    dcd     0xe594205c
    dcd     0xe1a00004
    dcd     0xe0422001
    dcd     0xe584205c
    bl      func_0202fb8c
    dcd     0xe1a00004
    bl      func_ov012_0205c048
    mov r0, #1
    dcd     0xe8bd8010
}
