extern void func_02000fb4(void);
extern void NNSi_FndFreeFromDefaultHeap(void);
extern void func_0201ef9c(void);
extern void data_ov011_0205e960(void);
extern void data_ov011_0205dd10(void);
extern void data_ov011_0205e930(void);

asm void func_ov011_0205c074(void)
{
    dcd     0xe92d4008
    dcd     0xe59f10f8
    dcd     0xe59f20f8
    dcd     0xe5910004
    dcd     0xe3a03002
    dcd     0xe5803004
    dcd     0xe5910004
    dcd     0xe59f30e8
    dcd     0xe2800a23
    dcd     0xe5803acc
    dcd     0xe5910004
    dcd     0xe3a03006
    dcd     0xe18030b2
    dcd     0xe5913004
    dcd     0xe59f10d0
    dcd     0xe2422002
    dcd     0xe3a0c000
    mov r0, #1
    dcd     0xe183c0b2
    bl      func_02000fb4
    dcd     0xe59f00ac
    dcd     0xe5900004
    dcd     0xe5900014
    bl      NNSi_FndFreeFromDefaultHeap
    dcd     0xe59f109c
    dcd     0xe59f00a8
    dcd     0xe5912004
    dcd     0xe3a0100e
    dcd     0xe592200c
    dcd     0xe2822902
    dcd     0xe0020000
    dcd     0xe1a00380
    dcd     0xe3800112
    bl      func_0201ef9c
    dcd     0xe59f1074
    dcd     0xe3a0e301
    dcd     0xe5912004
    dcd     0xe28eca01
    dcd     0xe5820014
    dcd     0xe59e0000
    dcd     0xe3a02000
    dcd     0xe3c00a0e
    dcd     0xe58e0000
    dcd     0xe59c3000
    dcd     0xe59f0060
    dcd     0xe3c33a0e
    dcd     0xe58c3000
    dcd     0xe58e2018
    dcd     0xe58e201c
    dcd     0xe5802000
    dcd     0xe5802004
    dcd     0xe59e0000
    dcd     0xe3c00c1f
    dcd     0xe3800c19
    dcd     0xe58e0000
    dcd     0xe59c0000
    dcd     0xe3c00c1f
    dcd     0xe3800c11
    dcd     0xe58c0000
    dcd     0xe5910004
    dcd     0xe2800a23
    dcd     0xe5d01abd
    dcd     0xe3c11001
    dcd     0xe5c01abd
    dcd     0xe8bd8008
    dcd     data_ov011_0205e960
    dcd     0x00023aca
    dcd     data_ov011_0205dd10
    dcd     data_ov011_0205e930
    dcd     0x00fffffc
    dcd     0x04001018
}
