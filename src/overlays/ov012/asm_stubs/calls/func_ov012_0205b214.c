extern void data_ov012_0205cb20(void);
extern void func_ov024_02084df4(void);

asm void func_ov012_0205b214(void)
{
    dcd     0xe92d4008
    dcd     0xe59f2034
    dcd     0xe3e03000
    dcd     0xe5922000
    dcd     0xe2822902
    dcd     0xe5821be4
    dcd     0xe5823be8
    dcd     0xe5c20be2
    dcd     0xe5920bdc
    dcd     0xe3500001
    dcd     0x18bd8008
    dcd     0xe3a01002
    dcd     0xe3a00000
    dcd     0xe5821bdc
    bl      func_ov024_02084df4
    dcd     0xe8bd8008
    dcd     data_ov012_0205cb20
}
