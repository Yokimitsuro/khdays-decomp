extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_02023eb4(void);
extern void func_ov002_02073094(void);

asm void func_ov127_020cc3ec(void)
{
    dcd     0xe92d4070
    dcd     0xe5904004
    dcd     0xe3a00064
    bl      func_02023eb4
    dcd     0xe350000a
    dcd     0xb3a06000
    dcd     0xba000002
    dcd     0xe3500028
    dcd     0xb3a06001
    dcd     0xa3a06002
    dcd     0xe5940000
    dcd     0xe2800fe6
    bl      func_01fffd70
    dcd     0xe3a05000
    dcd     0xe1b01000
    dcd     0x08bd8070
    dcd     0xe1550006
    dcd     0xba000005
    dcd     0xe5940000
    dcd     0xe5911000
    dcd     0xe3a02000
    dcd     0xe3a03a01
    bl      func_ov002_02073094
    dcd     0xe8bd8070
    dcd     0xe5940000
    dcd     0xe2800fe6
    bl      func_01fffd8c
    dcd     0xe1b01000
    dcd     0xe2855001
    dcd     0x1afffff1
    dcd     0xe8bd8070
}
