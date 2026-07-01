extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e470(void);
extern void MI_CpuFill8(void);
extern void func_020235a8(void);
extern void func_02024ee8(void);
extern void func_ov024_020832c4(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void data_ov011_0205e960(void);
extern void data_ov011_0205e8e4(void);
extern void data_ov011_0205e8f0(void);
extern void func_ov011_0205ae4c(void);

asm void func_ov011_0205ac40(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd088
    dcd     0xe1a04000
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe59f119c
    dcd     0xe59f219c
    dcd     0xe5810004
    dcd     0xe1d200b0
    dcd     0xe2000902
    dcd     0xe1b007c0
    dcd     0xe59f0184
    dcd     0x13a01001
    dcd     0xe5900004
    dcd     0x03a01000
    dcd     0xe2802a23
    dcd     0xe5925ac0
    dcd     0xe1a03f81
    dcd     0xe3c55004
    dcd     0xe1853ea3
    dcd     0xe59f1168
    mov r0, #0
    dcd     0xe5823ac0
    bl      func_0201e470
    dcd     0xe59f0150
    dcd     0xe59f2158
    dcd     0xe5900004
    dcd     0xe3a01000
    bl      MI_CpuFill8
    dcd     0xe59f313c
    dcd     0xe3a01000
    dcd     0xe5930004
    dcd     0xe2415010
    dcd     0xe2800a23
    dcd     0xe5804ac4
    dcd     0xe5932004
    dcd     0xe59f0130
    dcd     0xe2822801
    dcd     0xe5c21947
    dcd     0xe5932004
    dcd     0xe2822a21
    dcd     0xe5c21287
    dcd     0xe5932004
    dcd     0xe2822801
    dcd     0xe5c25944
    dcd     0xe5932004
    dcd     0xe2822a21
    dcd     0xe5c25284
    dcd     0xe5932004
    dcd     0xe5821004
    bl      func_020235a8
    dcd     0xe59f00f8
    dcd     0xe3a0100f
    bl      func_02024ee8
    dcd     0xe59f20d8
    dcd     0xe5921004
    dcd     0xe281190b
    dcd     0xe5810f54
    dcd     0xe5922004
    dcd     0xe282090b
    dcd     0xe5901f54
    dcd     0xe2820a23
    dcd     0xe58d1000
    dcd     0xe5900ac4
    dcd     0xe3500000
    dcd     0x13a06001
    dcd     0x03a06000
    dcd     0xe59f00a4
    dcd     0xe59f10b8
    dcd     0xe5900004
    dcd     0xe5d1e000
    dcd     0xe2800fd6
    dcd     0xe28d5008
    dcd     0xe5d1c001
    dcd     0xe5d14002
    dcd     0xe5d13003
    dcd     0xe5d12004
    dcd     0xe5d11005
    dcd     0xe2800bb3
    dcd     0xe58d6004
    dcd     0xe5c5e000
    dcd     0xe5c5c001
    dcd     0xe5c54002
    dcd     0xe5c53003
    dcd     0xe5c52004
    dcd     0xe5c51005
    bl      func_ov024_020832c4
    dcd     0xe59f0054
    dcd     0xe5900004
    dcd     0xe280090b
    dcd     0xe5900f58
    dcd     0xe12fff30
    dcd     0xe59f1040
    dcd     0xe28d0000
    dcd     0xe5911004
    dcd     0xe281190b
    dcd     0xe5911f5c
    dcd     0xe12fff31
    dcd     0xe59f0028
    dcd     0xe5900004
    dcd     0xe280090b
    dcd     0xe5900f64
    dcd     0xe12fff30
    mov r0, #0
    bl      func_0201e374
    mov r0, #0
    bl      func_0201e3cc
    dcd     0xe59f0020
    dcd     0xe28dd088
    dcd     0xe8bd8070
    dcd     data_ov011_0205e960
    dcd     0x027fffa8
    dcd     0x00000018
    dcd     0x0002cf84
    dcd     0x000020e9
    dcd     data_ov011_0205e8e4
    dcd     data_ov011_0205e8f0
    dcd     func_ov011_0205ae4c
}
