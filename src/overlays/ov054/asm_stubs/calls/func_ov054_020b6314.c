extern void func_ov054_020b635c(void);

asm void func_ov054_020b6314(void)
{
    ldr ip, [pc, #4]
    dcd     0xe2811010
    bx  ip
    dcd     func_ov054_020b635c
}
