extern void func_02023930(void);
extern void data_ov039_020b5554(void);

asm void func_ov039_020b5378(void)
{
    ldr ip, [pc, #8]
    dcd     0xe1a01000
    dcd     0xe59f0004
    bx  ip
    dcd     func_02023930
    dcd     data_ov039_020b5554
}
