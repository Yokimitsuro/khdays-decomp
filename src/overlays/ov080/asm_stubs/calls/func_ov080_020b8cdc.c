extern void func_ov080_020b8dc4(void);
extern void func_ov080_020b8f8c(void);

asm void func_ov080_020b8cdc(void)
{
    dcd     0xe92d43f8
    dcd     0xe1a04001
    dcd     0xe1a05000
    dcd     0xe1a09002
    dcd     0xe2848e33
    dcd     0xe3a07000
    dcd     0xe1a00005
    dcd     0xe1a01008
    dcd     0xe1a02009
    bl      func_ov080_020b8f8c
    dcd     0xe2877001
    dcd     0xe3570003
    dcd     0xe2888e11
    dcd     0xbafffff7
    dcd     0xe59506bc
    dcd     0xe3500030
    dcd     0x18bd83f8
    dcd     0xe59507b0
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe3500a12
    dcd     0xe3a03001
    dcd     0xca00000a
    dcd     0xe3500a12
    dcd     0xaa000010
    dcd     0xe3500a06
    dcd     0xca000002
    dcd     0x01a02003
    dcd     0x059f6064
    dcd     0xea000011
    dcd     0xe3500903
    dcd     0x01a02003
    dcd     0x059f6058
    dcd     0xea00000d
    dcd     0xe3500a1e
    dcd     0xca000001
    dcd     0x0a000007
    dcd     0xea000009
    dcd     0xe3500a2a
    dcd     0x01a02003
    dcd     0x02636a06
    dcd     0xea000005
    dcd     0xe1a02003
    dcd     0xe59f6030
    dcd     0xea000002
    dcd     0xe1a02003
    dcd     0xe1a06001
    dcd     0xe1a03001
    dcd     0xe3520000
    dcd     0x08bd83f8
    dcd     0xe1a00005
    dcd     0xe1a01004
    dcd     0xe1a02006
    bl      func_ov080_020b8dc4
    dcd     0xe8bd83f8
    dcd     0x000051c6
    dcd     0x0000f555
    dcd     0x0000aaaa
}
