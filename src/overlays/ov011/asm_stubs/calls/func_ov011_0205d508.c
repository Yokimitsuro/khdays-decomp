extern void func_02024c94(void);
extern void GFXi_EnqueueCommand(void);
extern void func_ov011_0205b1bc(void);
extern void func_ov011_0205b9f4(void);
extern void data_ov011_0205dcd0(void);
extern void data_ov011_0205e960(void);

asm void func_ov011_0205d508(void)
{
    dcd     0xe92d47f8
    dcd     0xe24dd044
    dcd     0xe59fe13c
    dcd     0xe28dc004
    dcd     0xe1a04001
    dcd     0xe1a0a000
    dcd     0xe1a09002
    dcd     0xe1a08003
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe59f1120
    dcd     0xe59f0120
    dcd     0xe1a050c4
    dcd     0xe5916004
    dcd     0xe0070095
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe89e000f
    dcd     0xe88c000f
    dcd     0xe2866018
    dcd     0xe0866007
    dcd     0xe1a0100a
    dcd     0xe58d9000
    dcd     0xe1a00006
    dcd     0xe1a02009
    dcd     0xe1a03009
    bl      func_02024c94
    dcd     0xe5963008
    dcd     0xe28d1010
    dcd     0xe28d0004
    dcd     0xe7911204
    dcd     0xe593200c
    dcd     0xe7900204
    dcd     0xe5933008
    dcd     0xe1a01681
    bl      GFXi_EnqueueCommand
    dcd     0xe3580000
    dcd     0x0a000013
    dcd     0xe59f00a8
    dcd     0xe1a01008
    dcd     0xe5900004
    dcd     0xe2800014
    dcd     0xe0800007
    bl      func_ov011_0205b1bc
    dcd     0xe59f1090
    dcd     0xe59f0094
    dcd     0xe5912004
    dcd     0xe2801002
    dcd     0xe0822007
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe1a00006
    dcd     0xe1a031c1
    dcd     0xe1a01005
    dcd     0xe1a021c2
    dcd     0xe2433001
    bl      func_ov011_0205b9f4
    dcd     0xea00000d
    dcd     0xe5961004
    dcd     0xe28d0008
    dcd     0xe5912014
    dcd     0xe5913010
    dcd     0xe7900204
    dcd     0xe3a01000
    bl      GFXi_EnqueueCommand
    dcd     0xe5961000
    dcd     0xe28d000c
    dcd     0xe5913008
    dcd     0xe281200c
    dcd     0xe7900204
    dcd     0xe3a01000
    bl      GFXi_EnqueueCommand
    dcd     0xe59f0020
    dcd     0xe5900004
    dcd     0xe2800a23
    dcd     0xe5901ab8
    dcd     0xe3c11001
    dcd     0xe3811001
    dcd     0xe5801ab8
    dcd     0xe28dd044
    dcd     0xe8bd87f8
    dcd     data_ov011_0205dcd0
    dcd     data_ov011_0205e960
    dcd     0x00010940
    dcd     0x00010930
}
