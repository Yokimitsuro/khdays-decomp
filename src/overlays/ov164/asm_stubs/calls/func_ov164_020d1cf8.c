extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);

asm void func_ov164_020d1cf8(void) {

    dcd 0xe92d4038
    dcd 0xe24dd018
    dcd 0xe5905004
    dcd 0xe5952000
    dcd 0xe59213cc
    dcd 0xe1a01f81
    dcd 0xe1b01fc1
    dcd 0x0a000006
    dcd 0xe3a01008
    dcd 0xe5c211c7
    dcd 0xe1d012d0
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd8038
    dcd 0xe5901000
    dcd 0xe5952030
    dcd 0xe591102c
    dcd 0xe0821001
    dcd 0xe5851030
    dcd 0xe5954000
    dcd 0xe5d4117a
    dcd 0xe1a01f01
    dcd 0xe1b01fa1
    dcd 0x0a00001a
    dcd 0xe5900000
    dcd 0xe5951030
    dcd 0xe590002c
    dcd 0xe1510080
    dcd 0xba000015
    dcd 0xe3a00a01
    dcd 0xe28d200c
    dcd 0xe2600000
    dcd 0xe285103c
    bl func_01ffa724
    dcd 0xe28d000c
    dcd 0xe2841f45
    bl VEC_DotProduct
    dcd 0xe28d2000
    dcd 0xe1a00080
    dcd 0xe2841f45
    bl func_01ffa724
    dcd 0xe28d0000
    dcd 0xe28d100c
    dcd 0xe1a02000
    bl VEC_Subtract
    dcd 0xe28d0000
    dcd 0xe285103c
    bl func_01ff8d18
    dcd 0xe3a00000
    dcd 0xe5850040
    dcd 0xe5850030
    dcd 0xe5950038
    dcd 0xe285103c
    dcd 0xe2852018
    bl func_01ffa724
    dcd 0xe5952038
    dcd 0xe59f001c
    dcd 0xe59f101c
    dcd 0xe0030092
    dcd 0xe0c20391
    dcd 0xe1a00fa3
    dcd 0xe08023c2
    dcd 0xe5852038
    dcd 0xe28dd018
    dcd 0xe8bd8038
    dcd 0x000007c6
    dcd 0x10624dd3
}
