extern void func_02023c40(void);
extern void func_ov022_020a35f4(void);
extern void data_ov075_020b9e20(void);

asm void func_ov075_020b913c(void)
{
    dcd     0xe92d4070
    dcd     0xe59f2038
    dcd     0xe1a06000
    dcd     0xe5920000
    dcd     0xe1a05001
    dcd     0xe2800f65
    dcd     0xe2804b0b
    bl      func_02023c40
    dcd     0xe3500001
    dcd     0x059f001c
    dcd     0xe3a01021
    dcd     0x13a000f6
    dcd     0xe5840130
    dcd     0xe1a00006
    dcd     0xe5845000
    bl      func_ov022_020a35f4
    dcd     0xe8bd8070
    dcd     data_ov075_020b9e20
    dcd     0x00000171
}
