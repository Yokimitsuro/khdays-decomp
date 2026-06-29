extern char data_ov090_020bcc00[];
extern void func_ov090_020bc8bc(void);
extern void func_ov090_020bca30(void);

asm void func_ov090_020bb210(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340e4
    dcd     0xe2841b0b
    bl      func_ov090_020bc8bc
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov090_020bca30
    dcd     0xe8bd8038
    dcd     data_ov090_020bcc00
}
