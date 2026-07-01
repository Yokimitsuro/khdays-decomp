extern void func_0202a634(void);
extern void data_ov092_020bc4a4(void);

asm void func_ov092_020bbf1c(void)
{
    dcd     0xe92d4010
    dcd     0xe2801a02
    dcd     0xe3a02000
    dcd     0xe5812c80
    dcd     0xe5d02009
    dcd     0xe2804db2
    dcd     0xe59f101c
    dcd     0xe2823007
    dcd     0xe284000c
    dcd     0xe3a02001
    bl      func_0202a634
    mov r0, #0
    dcd     0xe5840004
    dcd     0xe5840008
    dcd     0xe8bd8010
    dcd     data_ov092_020bc4a4
}
