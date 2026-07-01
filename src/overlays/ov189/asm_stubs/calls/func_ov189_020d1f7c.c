extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void data_0203d210(void);

asm void func_ov189_020d1f7c(void)
{
    dcd     0xe92d4ff0
    dcd     0xe24dd00c
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe28d2000
    dcd     0xe5940000
    dcd     0xe594100c
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840014
    dcd     0xe28d0000
    dcd     0xe1a01000
    dcd     0xe5945000
    bl      func_01ff8d18
    dcd     0xe5948010
    dcd     0xe59f30c0
    dcd     0xe59fc0c0
    dcd     0xe089a398
    dcd     0xe5951080
    dcd     0xe0299c98
    dcd     0xe1a07fc8
    dcd     0xe0299397
    dcd     0xe29aa000
    dcd     0xe2a97b02
    dcd     0xe1a07207
    dcd     0xe1a07827
    dcd     0xe1a07247
    dcd     0xe59fe098
    dcd     0xe1a07107
    dcd     0xe19e70f7
    dcd     0xe3a0b000
    dcd     0xe0405001
    dcd     0xe5847020
    dcd     0xe584b024
    dcd     0xe5948010
    dcd     0xe2841020
    dcd     0xe089a398
    dcd     0xe0299c98
    dcd     0xe1a07fc8
    dcd     0xe0299397
    dcd     0xe29a3000
    dcd     0xe2a93b02
    dcd     0xe1a03203
    dcd     0xe1a03823
    dcd     0xe1a03243
    dcd     0xe1a03083
    dcd     0xe2833001
    dcd     0xe1a03083
    dcd     0xe19e30f3
    dcd     0xe3a00c02
    dcd     0xe1a02001
    dcd     0xe5843028
    bl      func_01ffa724
    dcd     0xe3550a02
    dcd     0xa28dd00c
    dcd     0xa8bd8ff0
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe1a0200b
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8ff0
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
}
