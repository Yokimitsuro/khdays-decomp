extern char data_ov056_020b7620[];
extern void func_ov056_020b6b60(void);
extern void func_ov056_020b6d5c(void);

asm void func_ov056_020b5f30(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe283402c
    dcd     0xe2841b0b
    bl      func_ov056_020b6b60
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov056_020b6d5c
    dcd     0xe8bd8038
    dcd     data_ov056_020b7620
}
