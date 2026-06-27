extern void func_020037fc(void);
extern void func_02003c48(void);

asm void func_02003c38(void)
{
    stmdb sp!, {r3, lr}
    bl func_020037fc
    bl func_02003c48
    DCD 0xeafffffc
}
