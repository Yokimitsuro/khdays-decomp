extern void func_ov002_0207690c(void);
extern void func_ov145_020ce618(void);
extern void func_ov014_0208064c(void);
extern void func_ov002_02076cc8(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);

asm void func_ov145_020ce78c(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe1a04001
    bl      func_ov002_0207690c
    dcd     0xe3500001
    dcd     0x1a00002d
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov145_020ce618
    dcd     0xe1a04000
    dcd     0xe3540000
    dcd     0xd28dd018
    dcd     0xd3a00000
    dcd     0xd8bd8038
    dcd     0xe5950000
    dcd     0xe59003ec
    dcd     0xe3500000
    dcd     0x0a000021
    bl      func_ov014_0208064c
    dcd     0xe3500000
    dcd     0x0a00001e
    dcd     0xe5950000
    dcd     0xe59003ec
    bl      func_ov002_02076cc8
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59d0004
    dcd     0xe28d200c
    dcd     0xe2800b02
    dcd     0xe58d0004
    dcd     0xe5951000
    dcd     0xe1a00003
    dcd     0xe2811074
    bl      VEC_Subtract
    dcd     0xe28d000c
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2010
    bl      func_01ff8d18
    dcd     0xe1500004
    dcd     0xca000009
    dcd     0xe28d0000
    dcd     0xe2854018
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe285300c
    dcd     0xe8940007
    dcd     0xe8830007
    dcd     0xe28dd018
    mov r0, #1
    dcd     0xe8bd8038
    mov r0, #0
    dcd     0xe28dd018
    dcd     0xe8bd8038
}
