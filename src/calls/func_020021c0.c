extern void func_020037e8(void);
extern void func_02003c48(void);

asm void func_020021c0(void)
{
    stmdb sp!, {r3, lr}
    bl func_020037e8
    bl func_02003c48
    DCD 0xeafffffd
}
