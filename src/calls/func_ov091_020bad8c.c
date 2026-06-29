extern char data_ov091_020bc240[];
extern void func_ov091_020bb0b4(void);
extern void func_ov091_020bb0c4(void);

asm void func_ov091_020bad8c(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340a4
    dcd     0xe2841b0b
    bl      func_ov091_020bb0b4
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov091_020bb0c4
    dcd     0xe8bd8038
    dcd     data_ov091_020bc240
}
