extern void func_ov082_020b9764(void);

asm void func_ov082_020b895c(void)
{
    ldr ip, [pc, #8]
    dcd     0xe28000a8
    dcd     0xe2800b0b
    bx  ip
    dcd     func_ov082_020b9764
}
