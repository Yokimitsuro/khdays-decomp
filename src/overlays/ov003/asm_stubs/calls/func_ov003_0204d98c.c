extern char data_0204c300[];
extern char data_ov003_0204f8bc[];
extern char data_ov003_0204f8d0[];
extern char data_ov003_0204f8f8[];
extern char data_ov003_0204f944[];
extern char data_ov003_0204f950[];
extern char data_ov003_0204f958[];
extern char data_ov003_0204f964[];
extern char data_ov003_0204f978[];
extern char data_ov003_0204f9a0[];
extern void NNSi_FndGetCurrentRootHeap(void);
extern void OS_SPrintf(void);
extern void MIi_CpuClear16(void);
extern void func_02000f48(void);
extern void DC_FlushRange(void);
extern void func_020056b4(void);
extern void GX_SetBankForBG(void);
extern void GX_SetBankForTex(void);
extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_SetBankForSubBG(void);
extern void G2S_GetBG0ScrPtr(void);
extern void func_02011174(void);
extern void func_020115b8(void);
extern void func_02013484(void);
extern void func_0201e1d0(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void func_0201ef9c(void);
extern void func_0202497c(void);
extern void func_020249b0(void);
extern void func_020249e4(void);
extern void func_02024a6c(void);
extern void func_02024ae0(void);
extern void func_02024b04(void);
extern void func_02024c94(void);
extern void func_02024d68(void);
extern void func_02024e5c(void);
extern void func_02024ee8(void);
extern void func_0202a388(void);
extern void func_0202a634(void);
extern void func_0202accc(void);
extern void func_0202af3c(void);
extern void func_0202e358(void);
extern void func_0202e8ec(void);
extern void func_0202ea14(void);
extern void func_0202ea1c(void);
extern void func_02033500(void);
extern void func_0203355c(void);
extern void func_ov003_0204cba0(void);
extern void func_ov003_0204d308(void);
extern void func_ov003_0204d3b0(void);
extern void func_ov003_0204d74c(void);
extern void func_ov003_0204e5b0(void);
extern void func_ov105_020bd7c4(void);

asm void func_ov003_0204d98c(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd028
    dcd     0xe1a05000
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a04000
    dcd     0xe59f199c
    dcd     0xe3e0000f
    dcd     0xe5814000
    bl      func_0201e374
    dcd     0xe3e0000f
    bl      func_0201e3cc
    bl      func_0201e1d0
    dcd     0xe59f0984
    dcd     0xe3a0100f
    bl      func_02024ee8
    dcd     0xe5840040
    dcd     0xe3550000
    dcd     0xe2840a01
    dcd     0x0a000004
    dcd     0xe3a01001
    dcd     0xe5801e10
    dcd     0xe3a01003
    dcd     0xe5801e14
    dcd     0xea000004
    dcd     0xe3a01000
    dcd     0xe5801e10
    bl      func_ov105_020bd7c4
    dcd     0xe2841a01
    dcd     0xe5810e14
    dcd     0xe59f5944
    dcd     0xe1a03004
    dcd     0xe3a0200a
    dcd     0xe1d510b0
    dcd     0xe1d500b2
    dcd     0xe2855004
    dcd     0xe2522001
    dcd     0xe1c310b0
    dcd     0xe1c300b2
    dcd     0xe2833004
    dcd     0x1afffff7
    dcd     0xe1d500b0
    dcd     0xe3a05000
    dcd     0xe1c300b0
    dcd     0xe1d400b0
    dcd     0xe3500000
    dcd     0xda000008
    dcd     0xe1a01005
    dcd     0xe0842005
    dcd     0xe1d200d6
    dcd     0xe2855001
    dcd     0xe3500013
    dcd     0x05c21006
    dcd     0xe1d400b0
    dcd     0xe1550000
    dcd     0xbafffff7
    bl      func_ov003_0204d74c
    dcd     0xe2840044
    dcd     0xe3a01000
    bl      func_0202e8ec
    dcd     0xe2840044
    dcd     0xe3a01001
    bl      func_0202ea14
    dcd     0xe2840044
    dcd     0xe3a01001
    bl      func_0202ea1c
    dcd     0xe3a00003
    bl      GX_SetBankForTex
    dcd     0xe3a00020
    bl      GX_BeginLoadOBJExtPltt
    dcd     0xe3a00010
    bl      GX_SetBankForBG
    dcd     0xe3a00901
    dcd     0xe3a01001
    bl      func_02011174
    mov r0, #1
    dcd     0xe3a01000
    dcd     0xe1a02000
    bl      func_020056b4
    dcd     0xe3a01301
    dcd     0xe5910000
    dcd     0xe59f687c
    dcd     0xe3c00c1f
    dcd     0xe3800c01
    dcd     0xe5810000
    dcd     0xe1d120ba
    dcd     0xe2463002
    dcd     0xe28400b0
    dcd     0xe2022043
    dcd     0xe3822c0d
    dcd     0xe1c120ba
    dcd     0xe1d650b0
    dcd     0xe59f2854
    dcd     0xe2055043
    dcd     0xe3855c0d
    dcd     0xe1c650b0
    dcd     0xe1d150bc
    dcd     0xe2055043
    dcd     0xe3855c0e
    dcd     0xe1c150bc
    dcd     0xe1d650b2
    dcd     0xe2055043
    dcd     0xe3855c0e
    dcd     0xe1c650b2
    dcd     0xe1d150be
    dcd     0xe2055043
    dcd     0xe3855c0f
    dcd     0xe1c150be
    dcd     0xe1d310b0
    dcd     0xe2011043
    dcd     0xe3811c0f
    dcd     0xe1c310b0
    dcd     0xe5941040
    dcd     0xe2811902
    dcd     0xe0011002
    dcd     0xe1a01381
    dcd     0xe3811106
    bl      func_0202e358
    dcd     0xe2840058
    dcd     0xe5942040
    dcd     0xe59f17e4
    dcd     0xe2822902
    dcd     0xe0021001
    dcd     0xe1a01381
    dcd     0xe381110a
    bl      func_0202e358
    dcd     0xe5941040
    dcd     0xe59f07c8
    dcd     0xe2811902
    dcd     0xe0010000
    dcd     0xe1a01380
    dcd     0xe2840f42
    dcd     0xe3811122
    dcd     0xe3a02001
    dcd     0xe3a03000
    bl      func_0202a634
    dcd     0xe1d420b0
    dcd     0xe3a0a000
    dcd     0xe3520000
    dcd     0xda00009a
    dcd     0xe2840e2a
    dcd     0xe2809a01
    dcd     0xe3e00000
    dcd     0xe284be21
    dcd     0xe2845e63
    dcd     0xe2846ea5
    dcd     0xe2847d5b
    dcd     0xe2848ee7
    dcd     0xe58d001c
    dcd     0xe59f1774
    dcd     0xe28d0020
    dcd     0xe28a3001
    bl      OS_SPrintf
    dcd     0xe5941040
    dcd     0xe28a2003
    dcd     0xe2813902
    dcd     0xe59f1754
    dcd     0xe1a0000b
    dcd     0xe0031001
    dcd     0xe1a01381
    dcd     0xe3813102
    dcd     0xe59f1740
    dcd     0xe00217a1
    dcd     0xe1831001
    dcd     0xe3a02001
    dcd     0xe3a03000
    bl      func_0202a634
    dcd     0xe1a0000b
    dcd     0xe2841f42
    dcd     0xe28d2020
    bl      func_0202af3c
    dcd     0xe5941040
    dcd     0xe1a00005
    dcd     0xe2813902
    dcd     0xe59f170c
    dcd     0xe3a02001
    dcd     0xe0031001
    dcd     0xe1a01381
    dcd     0xe381111e
    dcd     0xe3a03000
    bl      func_0202a634
    dcd     0xe1a00005
    dcd     0xe2841f42
    dcd     0xe28d2020
    bl      func_0202af3c
    dcd     0xe084000a
    dcd     0xe58d0018
    dcd     0xe59d1018
    dcd     0xe1a00006
    dcd     0xe1d1c0d6
    dcd     0xe59f16d4
    dcd     0xe3a02001
    dcd     0xe791110c
    dcd     0xe3a03006
    bl      func_0202a634
    dcd     0xe5943040
    dcd     0xe59d2018
    dcd     0xe283c902
    dcd     0xe59f36ac
    dcd     0xe1d220d6
    dcd     0xe00c3003
    dcd     0xe1a03383
    dcd     0xe383e102
    dcd     0xe59f36a4
    dcd     0xe1a00007
    dcd     0xe193c0d2
    dcd     0xe59f268c
    dcd     0xe1a01006
    dcd     0xe00c27a2
    dcd     0xe3a03006
    dcd     0xe18e2002
    bl      func_0202a388
    dcd     0xe1a00006
    dcd     0xe2841f42
    dcd     0xe28d2020
    bl      func_0202af3c
    dcd     0xe3a01000
    dcd     0xe1a00006
    dcd     0xe1a02007
    dcd     0xe1a03001
    bl      func_0202accc
    dcd     0xe59d0018
    dcd     0xe1d010d6
    dcd     0xe59f0658
    dcd     0xe19010d1
    dcd     0xe59d001c
    dcd     0xe1510000
    dcd     0x0084010a
    dcd     0x02801a01
    dcd     0x03a00000
    dcd     0x0a000018
    dcd     0xe59f0628
    dcd     0xe3a02001
    dcd     0xe00137a0
    dcd     0xe5941040
    dcd     0xe1a00008
    dcd     0xe281c902
    dcd     0xe59f1610
    dcd     0xe00c1001
    dcd     0xe1a01381
    dcd     0xe3811102
    dcd     0xe1811003
    dcd     0xe3a03006
    bl      func_0202a634
    dcd     0xe1a00008
    dcd     0xe2841f42
    dcd     0xe28d2020
    bl      func_0202af3c
    dcd     0xe3a01000
    dcd     0xe1a00008
    dcd     0xe28820e0
    dcd     0xe1a03001
    bl      func_0202accc
    dcd     0xe084010a
    dcd     0xe2801a01
    mov r0, #1
    dcd     0xe5810290
    dcd     0xe59f15d4
    dcd     0xe1a00009
    dcd     0xe3a02001
    dcd     0xe3a0300f
    bl      func_0202a634
    dcd     0xe1a00009
    dcd     0xe2841f42
    dcd     0xe28d2020
    bl      func_0202af3c
    dcd     0xe3a01000
    dcd     0xe1a00009
    dcd     0xe28920e0
    dcd     0xe1a03001
    bl      func_0202accc
    dcd     0xe1a00009
    dcd     0xe3a01004
    dcd     0xe28920e0
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe1a00009
    dcd     0xe3a01002
    dcd     0xe28920e0
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe084010a
    dcd     0xe2801a01
    mov r0, #0
    dcd     0xe581078c
    dcd     0xe1d420b0
    dcd     0xe28aa001
    dcd     0xe28bbf42
    dcd     0xe2855f42
    dcd     0xe2866f42
    dcd     0xe2877024
    dcd     0xe2888f42
    dcd     0xe2899f42
    dcd     0xe15a0002
    dcd     0xbaffff6d
    dcd     0xe3a00004
    bl      GX_SetBankForSubBG
    dcd     0xe5941040
    dcd     0xe59f051c
    dcd     0xe2811902
    dcd     0xe0010000
    dcd     0xe1a00380
    dcd     0xe3800102
    dcd     0xe3a0100e
    bl      func_0201ef9c
    dcd     0xe2841a01
    dcd     0xe5810db8
    bl      func_02024e5c
    dcd     0xe3500001
    dcd     0x03a00001
    dcd     0x13a00000
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe2840a01
    dcd     0xe3a01000
    dcd     0xe5801dbc
    dcd     0xea000004
    dcd     0xe59f04e8
    dcd     0xe3a0100e
    bl      func_0201ef9c
    dcd     0xe2841a01
    dcd     0xe5810dbc
    dcd     0xe3a02000
    dcd     0xe1a01004
    dcd     0xe1a03002
    dcd     0xe2840d77
    dcd     0xe58d2000
    bl      func_ov003_0204d308
    dcd     0xe2840fee
    dcd     0xe2801b05
    mov r0, #0
    dcd     0xe3a02c06
    bl      MIi_CpuClear16
    dcd     0xe3e03000
    dcd     0xe2840f73
    dcd     0xe58d3000
    dcd     0xe2841a01
    dcd     0xe5911db8
    dcd     0xe2800b07
    dcd     0xe3a02001
    bl      func_02024c94
    dcd     0xe1d400b0
    dcd     0xe3a05000
    dcd     0xe3500000
    dcd     0xda000005
    dcd     0xe1a00005
    bl      func_ov003_0204d3b0
    dcd     0xe1d400b0
    dcd     0xe2855001
    dcd     0xe1550000
    dcd     0xbafffff9
    dcd     0xe59f0438
    dcd     0xe3a01c06
    dcd     0xe5900000
    dcd     0xe2800fee
    dcd     0xe2800b05
    bl      DC_FlushRange
    dcd     0xe2842a01
    dcd     0xe5921dc8
    mov r0, #1
    dcd     0xe5915008
    dcd     0xe3a03000
    dcd     0xe58d5000
    dcd     0xe5922dc0
    bl      func_02024a6c
    dcd     0xe2840a01
    dcd     0xe5901dc4
    mov r0, #1
    dcd     0xe5913010
    dcd     0xe3a02000
    bl      func_02024ae0
    dcd     0xe2840fee
    dcd     0xe2801b05
    mov r0, #1
    dcd     0xe3a02000
    dcd     0xe3a03c06
    bl      func_0202497c
    dcd     0xe2842a01
    dcd     0xe5921dc8
    dcd     0xe3a00005
    dcd     0xe5915008
    dcd     0xe3a03000
    dcd     0xe58d5000
    dcd     0xe5922dc0
    bl      func_02024a6c
    dcd     0xe2840a01
    dcd     0xe5901dc4
    dcd     0xe3a00005
    dcd     0xe5913010
    dcd     0xe3a02000
    bl      func_02024ae0
    dcd     0xe2841fee
    dcd     0xe3a00005
    dcd     0xe2811b05
    dcd     0xe3a02000
    dcd     0xe3a03c06
    bl      func_0202497c
    mov r0, #0
    dcd     0xe58d0000
    dcd     0xe2840f76
    dcd     0xe2800b07
    dcd     0xe1a01004
    dcd     0xe3a02003
    dcd     0xe3a03002
    bl      func_ov003_0204d308
    dcd     0xe3a05000
    dcd     0xe2840a01
    dcd     0xe5901dd8
    dcd     0xe1a02085
    dcd     0xe281300c
    dcd     0xe19310b2
    dcd     0xe2855001
    dcd     0xe3550040
    dcd     0xe2811060
    dcd     0xe18310b2
    dcd     0xbafffff6
    dcd     0xe2840a01
    dcd     0xe5901ddc
    dcd     0xe3a00002
    dcd     0xe5913010
    dcd     0xe3a02b03
    bl      func_02024ae0
    dcd     0xe2840a01
    dcd     0xe5901dd8
    dcd     0xe3a00002
    dcd     0xe5913008
    dcd     0xe3a02000
    bl      func_02024b04
    dcd     0xe2840a01
    dcd     0xe5901ddc
    dcd     0xe3a00006
    dcd     0xe5913010
    dcd     0xe3a02b03
    bl      func_02024ae0
    dcd     0xe2840a01
    dcd     0xe5901dd8
    dcd     0xe3a00006
    dcd     0xe5913008
    dcd     0xe3a02000
    bl      func_02024b04
    mov r0, #0
    dcd     0xe58d0000
    dcd     0xe2840f79
    dcd     0xe2800b07
    dcd     0xe1a01004
    dcd     0xe3a02002
    dcd     0xe3a03001
    bl      func_ov003_0204d308
    dcd     0xe3a05000
    dcd     0xe2840a01
    dcd     0xe5901de4
    dcd     0xe1a02085
    dcd     0xe281300c
    dcd     0xe19310b2
    dcd     0xe2855001
    dcd     0xe3550020
    dcd     0xe2811080
    dcd     0xe18310b2
    dcd     0xbafffff6
    dcd     0xe2840a01
    dcd     0xe5901de8
    dcd     0xe3a00003
    dcd     0xe5913010
    dcd     0xe3a02a01
    bl      func_02024ae0
    dcd     0xe2840a01
    dcd     0xe5901de8
    dcd     0xe3a00004
    dcd     0xe5913010
    dcd     0xe3a02a01
    bl      func_02024ae0
    bl      func_020115b8
    mov r0, #1
    dcd     0xe58d0000
    dcd     0xe2402002
    dcd     0xe2840edf
    dcd     0xe2800a01
    dcd     0xe2841a01
    dcd     0xe5911db8
    dcd     0xe3a03003
    bl      func_02024c94
    dcd     0xe3a00002
    dcd     0xe58d0000
    dcd     0xe2402003
    dcd     0xe2840f7f
    dcd     0xe2800b07
    dcd     0xe2841a01
    dcd     0xe5911db8
    dcd     0xe3a03004
    bl      func_02024c94
    dcd     0xe3a0a000
    dcd     0xe1d400b0
    dcd     0xe3500000
    dcd     0xda000033
    dcd     0xe3a08c01
    dcd     0xe2845a01
    dcd     0xe3a0b024
    dcd     0xe084000a
    dcd     0xe1d030d6
    dcd     0xe3530010
    dcd     0xaa000007
    dcd     0xe5950df4
    dcd     0xe0010b93
    dcd     0xe5902014
    dcd     0xe5950df8
    dcd     0xe0827281
    dcd     0xe590000c
    dcd     0xe0806283
    dcd     0xea000008
    dcd     0xe2431010
    dcd     0xe3a00024
    dcd     0xe0020091
    dcd     0xe5953e00
    dcd     0xe5950e04
    dcd     0xe5933014
    dcd     0xe590000c
    dcd     0xe0837282
    dcd     0xe0806281
    dcd     0xe1a09288
    mov r0, #1
    dcd     0xe1a01007
    dcd     0xe1a02009
    dcd     0xe3a03d12
    bl      func_020249b0
    dcd     0xe1a01007
    dcd     0xe1a02009
    dcd     0xe3a00005
    dcd     0xe3a03d12
    bl      func_020249b0
    dcd     0xe28a0001
    dcd     0xe1a07280
    mov r0, #1
    dcd     0xe1a01006
    dcd     0xe1a02007
    dcd     0xe3a03020
    bl      func_020249e4
    dcd     0xe1a01006
    dcd     0xe1a02007
    dcd     0xe3a00005
    dcd     0xe3a03020
    bl      func_020249e4
    dcd     0xe1d400b0
    dcd     0xe28aa001
    dcd     0xe2888024
    dcd     0xe15a0000
    dcd     0xbaffffce
    dcd     0xe3a00d06
    bl      GX_SetBankForSubBG
    dcd     0xe2840a01
    dcd     0xe5901ddc
    dcd     0xe3a00006
    dcd     0xe5913010
    dcd     0xe3a02b03
    bl      func_02024ae0
    dcd     0xe2840a01
    dcd     0xe5901dd8
    dcd     0xe3a00006
    dcd     0xe5913008
    dcd     0xe3a02000
    bl      func_02024b04
    dcd     0xe2840a01
    dcd     0xe5901de8
    dcd     0xe3a00004
    dcd     0xe3a02a01
    dcd     0xe5913010
    bl      func_02024ae0
    bl      G2S_GetBG0ScrPtr
    dcd     0xe3a01008
    dcd     0xe58d1000
    dcd     0xe3a01016
    dcd     0xe58d1004
    dcd     0xe3a01020
    dcd     0xe58d1008
    dcd     0xe3a01018
    dcd     0xe58d100c
    dcd     0xe3a01010
    dcd     0xe58d1010
    dcd     0xe3a01002
    dcd     0xe58d1014
    dcd     0xe2841a01
    dcd     0xe5911de4
    dcd     0xe3a02000
    dcd     0xe1a03002
    bl      func_02013484
    bl      func_020115b8
    mov r0, #0
    bl      func_02033500
    dcd     0xe59f00b4
    bl      func_0203355c
    dcd     0xe3a02000
    dcd     0xe1d400b0
    dcd     0xe3500000
    dcd     0xda000008
    dcd     0xe1a01002
    dcd     0xe0840102
    dcd     0xe2800a01
    dcd     0xe5801750
    dcd     0xe5801764
    dcd     0xe1d400b0
    dcd     0xe2822001
    dcd     0xe1520000
    dcd     0xbafffff7
    dcd     0xe2840a01
    dcd     0xe3a02000
    dcd     0xe5802760
    dcd     0xe58027ac
    dcd     0xe58027b0
    dcd     0xe5802e08
    dcd     0xe5802e0c
    dcd     0xe59f1060
    dcd     0xe5802774
    dcd     0xe1d100b0
    dcd     0xe3c00a03
    dcd     0xe3800010
    dcd     0xe1c100b0
    bl      func_02024d68
    dcd     0xe59f1048
    dcd     0xe59f2048
    mov r0, #1
    bl      func_02000f48
    dcd     0xe59f0040
    dcd     0xe28dd028
    dcd     0xe8bd8ff8
    dcd     data_ov003_0204f9a0
    dcd     data_ov003_0204f944
    dcd     data_0204c300
    dcd     0x0400100a
    dcd     0x00fffffc
    dcd     data_ov003_0204f950
    dcd     data_ov003_0204f8f8
    dcd     data_ov003_0204f8d0
    dcd     data_ov003_0204f8bc
    dcd     data_ov003_0204f958
    dcd     data_ov003_0204f964
    dcd     0x00000182
    dcd     0x04000060
    dcd     data_ov003_0204f978
    dcd     func_ov003_0204cba0
    dcd     func_ov003_0204e5b0
}
