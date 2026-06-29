extern char data_ov003_0204f978[];
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_02000fb4(void);
extern void func_0200c5fc(void);
extern void func_0200ca50(void);
extern void func_0200ca68(void);
extern void func_02024fd4(void);
extern void func_0202a440(void);
extern void func_0202a7dc(void);
extern void func_0202e3c4(void);
extern void func_0202e944(void);
extern void func_02033500(void);

asm void func_ov003_0204e384(void)
{
    dcd     0xe92d4ff8
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a0b000
    dcd     0xe59f111c
    dcd     0xe3a00001
    bl      func_02000fb4
    bl      func_0200c5fc
    dcd     0xe3a00004
    bl      func_0200ca50
    dcd     0xe3a00004
    bl      func_0200ca68
    dcd     0xe3a00000
    bl      func_02033500
    dcd     0xe28b0a01
    dcd     0xe5900dbc
    dcd     0xe3500000
    dcd     0x0a000000
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe28b0a01
    dcd     0xe5900db8
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe1db00b0
    dcd     0xe2504001
    dcd     0x4a000028
    dcd     0xe3a00f42
    dcd     0xe28b5d5b
    dcd     0xe3a01024
    dcd     0xe0000094
    dcd     0xe28b2e2a
    dcd     0xe2826a01
    dcd     0xe28b7ee7
    dcd     0xe28b8ea5
    dcd     0xe28b3e21
    dcd     0xe28b2e63
    dcd     0xe0255194
    dcd     0xe0866000
    dcd     0xe0877000
    dcd     0xe0888000
    dcd     0xe0839000
    dcd     0xe082a000
    dcd     0xe1a00005
    bl      func_0202a440
    dcd     0xe1a00006
    bl      func_0202a7dc
    dcd     0xe08b0104
    dcd     0xe2800a01
    dcd     0xe5900290
    dcd     0xe3500000
    dcd     0x0a000001
    dcd     0xe1a00007
    bl      func_0202a7dc
    dcd     0xe1a00008
    bl      func_0202a7dc
    dcd     0xe1a00009
    bl      func_0202a7dc
    dcd     0xe1a0000a
    bl      func_0202a7dc
    dcd     0xe2455024
    dcd     0xe2466f42
    dcd     0xe2477f42
    dcd     0xe2488f42
    dcd     0xe2499f42
    dcd     0xe24aaf42
    dcd     0xe2544001
    dcd     0x5affffe6
    dcd     0xe28b0f42
    bl      func_0202a7dc
    dcd     0xe28b00b0
    bl      func_0202e3c4
    dcd     0xe28b0058
    bl      func_0202e3c4
    dcd     0xe28b0044
    bl      func_0202e944
    dcd     0xe59b0040
    bl      func_02024fd4
    dcd     0xe8bd8ff8
    dcd     data_ov003_0204f978
}
