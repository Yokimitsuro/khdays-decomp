extern void func_ov039_020b3e8c(void);
extern void func_ov039_020b3ed8(void);
extern void data_ov039_020b5600(void);

asm void func_ov039_020b3ad4(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340d4
    dcd     0xe2841b0b
    bl      func_ov039_020b3e8c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov039_020b3ed8
    dcd     0xe8bd8038
    dcd     data_ov039_020b5600
}
