extern char data_ov054_020b74a0[];
extern void func_ov002_020519b0(void);
extern void func_ov002_02052024(void);
extern void func_ov002_020521a4(void);
extern void func_ov022_020a384c(void);
extern void func_ov022_020a4490(void);
extern void WM_EndKeySharing_0x020b6308(void);
extern void func_ov054_020b6344(void);

asm void func_ov054_020b5d5c(void)
{
    dcd     0xe92d41f8
    dcd     0xe24dd004
    dcd     0xe59f2170
    dcd     0xe1a07001
    dcd     0xe5926000
    dcd     0xe247202e
    dcd     0xe28610a4
    dcd     0xe1a08000
    dcd     0xe3520004
    dcd     0xe2814b0b
    dcd     0xe3e05000
    dcd     0x908ff102
    dcd     0xea000031
    dcd     0xea000003
    dcd     0xea000007
    dcd     0xea000021
    dcd     0xea000020
    dcd     0xea000010
    dcd     0xe59816bc
    dcd     0xe1510007
    dcd     0x0a000029
    bl      WM_EndKeySharing_0x020b6308
    dcd     0xea000027
    dcd     0xe3a01000
    dcd     0xe5841000
    dcd     0xe59806bc
    dcd     0xe1500007
    dcd     0x0a000022
    dcd     0xe2840010
    bl      func_ov054_020b6344
    dcd     0xe1a00008
    dcd     0xe3a010d3
    dcd     0xe3a02000
    bl      func_ov022_020a4490
    dcd     0xea00001b
    mov r0, #1
    dcd     0xe5840000
    dcd     0xe59806bc
    dcd     0xe1500007
    dcd     0x0a000006
    dcd     0xe2840010
    dcd     0xe3a01a0f
    bl      func_ov054_020b6344
    dcd     0xe1a00008
    dcd     0xe3a010d3
    dcd     0xe3a02002
    bl      func_ov022_020a4490
    dcd     0xe3a0702f
    dcd     0xe3a05032
    dcd     0xea00000c
    dcd     0xe59806bc
    dcd     0xe1500007
    dcd     0x0a000009
    dcd     0xe3a02001
    dcd     0xe3570031
    dcd     0x03a02003
    dcd     0xe1a00008
    dcd     0xe3a010d3
    bl      func_ov022_020a4490
    dcd     0xe5980020
    dcd     0xe1d008b0
    dcd     0xe2400902
    dcd     0xe1c400be
    dcd     0xe1a00008
    dcd     0xe1a01007
    bl      func_ov022_020a384c
    dcd     0xe2880c2b
    dcd     0xe1d00bd2
    dcd     0xe3a03000
    dcd     0xe3500002
    dcd     0x03a03001
    dcd     0xe357002e
    dcd     0xba00000c
    dcd     0xe59816bc
    dcd     0xe598200c
    dcd     0xe1a00007
    bl      func_ov002_020519b0
    dcd     0xe2863ec5
    dcd     0xe2881fc3
    dcd     0xe58d0000
    dcd     0xe1a02007
    dcd     0xe2810b03
    dcd     0xe2831a02
    dcd     0xe3a03002
    bl      func_ov002_02052024
    dcd     0xea000005
    dcd     0xe2880fc3
    dcd     0xe2861ec5
    dcd     0xe1a02007
    dcd     0xe2800b03
    dcd     0xe2811a02
    bl      func_ov002_020521a4
    dcd     0xe3550000
    dcd     0xa58856bc
    dcd     0xe28dd004
    dcd     0xe8bd81f8
    dcd     data_ov054_020b74a0
}
