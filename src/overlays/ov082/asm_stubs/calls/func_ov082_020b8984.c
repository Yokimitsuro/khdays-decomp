extern void func_ov082_020b97e8(void);

asm void func_ov082_020b8984(void)
{
    ldr ip, [pc, #8]
    dcd     0xe28000a8
    dcd     0xe2800b0b
    bx  ip
    dcd     func_ov082_020b97e8
}
