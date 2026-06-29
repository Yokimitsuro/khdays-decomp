extern char data_ov081_020b96e0[];
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_ov081_020b93c8(void);

asm void func_ov081_020b9304(void)
{
    dcd     0xe92d43f8
    dcd     0xe24dd018
    dcd     0xe59f20b0
    dcd     0xe1a06001
    dcd     0xe5922000
    dcd     0xe28d300c
    dcd     0xe282102c
    dcd     0xe2814b0b
    dcd     0xe5945010
    dcd     0xe1a07000
    dcd     0xe8960007
    dcd     0xe8830007
    dcd     0xe1a00003
    dcd     0xe1a01003
    bl      func_01ff8d18
    dcd     0xe1a00006
    bl      VEC_Mag
    dcd     0xe5941010
    dcd     0xe0810000
    dcd     0xe3500a02
    dcd     0xd28dd018
    dcd     0xe5840010
    dcd     0xd8bd83f8
    dcd     0xe28d900c
    dcd     0xe28d8000
    dcd     0xe8960007
    dcd     0xe8890007
    dcd     0xe1a00009
    dcd     0xe1a01009
    bl      func_01ff8d18
    dcd     0xe1a01009
    dcd     0xe1a02009
    dcd     0xe2650a02
    bl      func_01ffa724
    dcd     0xe1a00007
    dcd     0xe1a01009
    dcd     0xe1a02008
    bl      VEC_Add
    dcd     0xe1a00008
    dcd     0xe1a01009
    bl      func_ov081_020b93c8
    dcd     0xe5940010
    dcd     0xe2405a02
    dcd     0xe5845010
    dcd     0xe3550a02
    dcd     0xcaffffea
    dcd     0xe28dd018
    dcd     0xe8bd83f8
    dcd     data_ov081_020b96e0
}
