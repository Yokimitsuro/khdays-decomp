extern void VEC_Add(void);
extern void func_01ff8e94(void);
extern void func_02030788(void);
extern void func_02033d0c(void);
extern void func_ov022_020914a0(void);
extern void func_ov022_0209198c(void);
extern void func_ov022_02091b48(void);
extern void func_ov022_02091e08(void);
extern void func_ov081_020b9304(void);

asm void func_ov081_020b90d4(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd024
    dcd     0xe1a06001
    dcd     0xe1a07000
    dcd     0xe5974008
    dcd     0xe5965138
    dcd     0xe28dc000
    dcd     0xe28600cc
    dcd     0xe1a03002
    dcd     0xe8900007
    dcd     0xe88c0007
    dcd     0xe28d000c
    dcd     0xe1a01007
    dcd     0xe1a02006
    bl      func_ov022_0209198c
    dcd     0xe1a00007
    dcd     0xe1a01006
    dcd     0xe28d2000
    dcd     0xe28d300c
    bl      func_ov022_02091b48
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe28d2018
    bl      VEC_Add
    dcd     0xe28d0018
    dcd     0xe28630cc
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28d0000
    dcd     0xe28d100c
    bl      func_ov081_020b9304
    dcd     0xe1d600d2
    dcd     0xe3500003
    dcd     0x0a000006
    dcd     0xe28d1018
    dcd     0xe2860010
    bl      func_01ff8e94
    dcd     0xe5951014
    dcd     0xe1500001
    dcd     0xc3a00004
    dcd     0xc5c60002
    dcd     0xe1a00007
    dcd     0xe1a01006
    bl      func_ov022_02091e08
    dcd     0xe5d60000
    dcd     0xe3100001
    dcd     0x0a000004
    dcd     0xe5961004
    dcd     0xe5950018
    dcd     0xe1510000
    dcd     0xa3a00004
    dcd     0xa5c60002
    dcd     0xe1d600d2
    dcd     0xe3500002
    dcd     0x0a00001e
    dcd     0xe5d40694
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x0a000004
    dcd     0xe28d2018
    dcd     0xe3a000c7
    dcd     0xe3a01001
    dcd     0xe3a03000
    bl      func_02033d0c
    dcd     0xe3a00004
    dcd     0xe5c60002
    dcd     0xe3a00d82
    dcd     0xe586000c
    dcd     0xe3a02000
    dcd     0xe3e01000
    dcd     0xe0860082
    dcd     0xe2800c01
    dcd     0xe2822001
    dcd     0xe1c013bc
    dcd     0xe3520008
    dcd     0xbafffff9
    dcd     0xe595103c
    dcd     0xe1a00006
    bl      func_ov022_020914a0
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000003
    dcd     0xe3a00003
    dcd     0xe5c4047a
    mov r0, #1
    dcd     0xe5c4047b
    mov r0, #0
    dcd     0xe28dd024
    dcd     0xe8bd80f0
}
