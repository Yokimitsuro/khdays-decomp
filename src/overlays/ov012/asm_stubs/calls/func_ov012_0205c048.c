extern void data_ov012_0205cb24(void);
extern void func_ov012_0205be44(void);

asm void func_ov012_0205c048(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5941070
    dcd     0xe3510000
    dcd     0x0a000004
    dcd     0xe3510001
    dcd     0x0a000005
    dcd     0xe3510002
    dcd     0x0a000016
    dcd     0xe8bd8010
    mov r0, #0
    dcd     0xe5840058
    dcd     0xe8bd8010
    dcd     0xe594105c
    dcd     0xe3510000
    dcd     0x1a00000b
    bl      func_ov012_0205be44
    dcd     0xe5941040
    dcd     0xe0410000
    dcd     0xe0800fa0
    dcd     0xe1b000c0
    dcd     0xe5840058
    dcd     0x43a00000
    dcd     0x45840058
    dcd     0xe5941058
    dcd     0xe59f0028
    dcd     0xe5801000
    dcd     0xe8bd8010
    dcd     0xe59f001c
    dcd     0xe5900000
    dcd     0xe5840058
    dcd     0xe8bd8010
    bl      func_ov012_0205be44
    dcd     0xe5941040
    dcd     0xe0410000
    dcd     0xe5840058
    dcd     0xe8bd8010
    dcd     data_ov012_0205cb24
}
