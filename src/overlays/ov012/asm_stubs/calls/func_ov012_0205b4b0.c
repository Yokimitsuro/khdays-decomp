extern void G2x_SetBlendAlpha_(void);
extern void func_0202060c(void);

asm void func_ov012_0205b4b0(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04002
    dcd     0xe5942000
    dcd     0xe1a05000
    dcd     0xe0410002
    dcd     0xe1d410b8
    dcd     0xe1a00200
    bl      func_0202060c
    dcd     0xe2853902
    dcd     0xe1d410b6
    dcd     0xe5d32bf0
    dcd     0xe1a0c000
    dcd     0xe1e00001
    dcd     0xe0122000
    dcd     0x1a00000f
    dcd     0xe35c0010
    dcd     0xba000009
    dcd     0xe3a02301
    dcd     0xe5921000
    mov r0, #0
    dcd     0xe3c11c1f
    dcd     0xe5821000
    dcd     0xe5c30bf0
    dcd     0xe2400010
    dcd     0xe5830bf4
    mov r0, #1
    dcd     0xe8bd8038
    dcd     0xe26c0000
    dcd     0xe5830bf4
    mov r0, #0
    dcd     0xe8bd8038
    dcd     0xe35c0010
    dcd     0xba00000a
    dcd     0xe5c32bf0
    dcd     0xe3a03301
    dcd     0xe5931000
    dcd     0xe20200ff
    dcd     0xe3c11c1f
    dcd     0xe1810400
    dcd     0xe5830000
    mov r0, #0
    dcd     0xe1c305b0
    mov r0, #1
    dcd     0xe8bd8038
    dcd     0xe59f0010
    dcd     0xe26c3010
    dcd     0xe58dc000
    bl      G2x_SetBlendAlpha_
    mov r0, #0
    dcd     0xe8bd8038
    dcd     0x04000050
}
