typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov000LoadEntry {
    int currentValue;
    int savedValue;
    u8 pad_0008[0x18];
} Ov000LoadEntry;

typedef struct Ov000LoadSceneContext {
    u8 pad_0000[0x4adc];
    int transitionMode;
    u8 pad_4ae0[0x1b];
    u8 loadState;
    u8 pad_4afc[0x24];
    Ov000LoadEntry loadEntries[1];
    u8 pad_4b40[0x1f08];
    u32 loadFlags;
    u32 pad_6a4c;
    u32 completionFlags;
    int ready;
    u32 pad_6a58;
    int resultX;
    int resultY;
} Ov000LoadSceneContext;

extern Ov000LoadSceneContext *volatile data_ov000_0205ac24;
extern void func_ov000_0204f7ac(void);
extern int func_ov000_0204f6e0(void);
extern void func_ov000_0204faf0(int index, int result);
extern int func_020235d0(int field, int kind);

asm u8 func_ov000_0204fc64(int index) {
    dcd 0xe92d4010
    dcd 0xe59f1138
    dcd 0xe1a04000
    dcd 0xe5912000
    dcd 0xe2821901
    dcd 0xe5d11afb
    dcd 0xe3510000
    dcd 0x0a000002
    dcd 0xe3510001
    dcd 0x0a00000b
    dcd 0xea000040
    dcd 0xe0821284
    dcd 0xe2811901
    dcd 0xe5912b20
    dcd 0xe5812b24
    bl func_ov000_0204f7ac
    dcd 0xe59f00fc
    dcd 0xe3a01001
    dcd 0xe5900000
    dcd 0xe2800901
    dcd 0xe5c01afb
    dcd 0xea000035
    bl func_ov000_0204f6e0
    dcd 0xe1a01000
    dcd 0xe3510003
    dcd 0x1a000018
    dcd 0xe59f20d4
    dcd 0xe3a01801
    dcd 0xe5920000
    dcd 0xe3a03002
    dcd 0xe2800901
    dcd 0xe5c03afb
    dcd 0xe5920000
    dcd 0xe3a03003
    dcd 0xe2800901
    dcd 0xe5803adc
    dcd 0xe5920000
    dcd 0xe2611000
    dcd 0xe2800a06
    dcd 0xe590ca48
    dcd 0xe3a03000
    dcd 0xe00c1001
    dcd 0xe3811001
    dcd 0xe5801a48
    dcd 0xe5920000
    dcd 0xe2800a06
    dcd 0xe5803a5c
    dcd 0xe5920000
    dcd 0xe2800a06
    dcd 0xe5803a60
    dcd 0xea000018
    dcd 0xe3510000
    dcd 0xba000016
    dcd 0xe1a00004
    bl func_ov000_0204faf0
    dcd 0xe59f1060
    dcd 0xe3a02002
    dcd 0xe5910000
    dcd 0xe2800901
    dcd 0xe5c02afb
    dcd 0xe5910000
    dcd 0xe2800a06
    dcd 0xe5900a54
    dcd 0xe3500000
    dcd 0x0a00000a
    dcd 0xe2620e45
    dcd 0xe3a01003
    bl func_020235d0
    dcd 0xe3500006
    dcd 0x1a000005
    dcd 0xe59f0024
    dcd 0xe5900000
    dcd 0xe2800a06
    dcd 0xe5901a50
    dcd 0xe3811001
    dcd 0xe5801a50
    dcd 0xe59f000c
    dcd 0xe5900000
    dcd 0xe2800901
    dcd 0xe5d00afb
    dcd 0xe8bd8010
    dcd data_ov000_0205ac24
}
