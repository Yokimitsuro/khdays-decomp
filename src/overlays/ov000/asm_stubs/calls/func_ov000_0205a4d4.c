typedef unsigned char u8;
typedef void *(*Ov000StateFn)(void);

typedef struct Ov000SceneContext {
    u8 pad_0000[0xd138];
    int transitionMode;
    void *loadedClass;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02059f50(void);
extern void func_0201e470(int processor, int overlayId);
extern void *func_02023930(void *classDescriptor, int enabled);
extern char data_ov012_0205c2bc[];
extern char data_ov011_0205e8a0[];
extern Ov000SceneContext *data_ov000_0205ac3c;
extern void *func_ov000_0205a5e8(void);
asm Ov000StateFn func_ov000_0205a4d4(void)
{
    dcd 0xe92d4010
    bl NNSi_FndGetCurrentRootHeap
    dcd 0xe1a04000
    bl func_ov000_02059f50
    dcd 0xe59f1050
    dcd 0xe2840a0d
    dcd 0xe5814000
    dcd 0xe5900138
    dcd 0xe3500000
    dcd 0xe3a00000
    dcd 0x1a000005
    dcd 0xe59f1038
    bl func_0201e470
    dcd 0xe59f0034
    dcd 0xe3a01001
    bl func_02023930
    dcd 0xea000004
    dcd 0xe59f1028
    bl func_0201e470
    dcd 0xe59f0024
    dcd 0xe3a01001
    bl func_02023930
    dcd 0xe2841a0d
    dcd 0xe581013c
    dcd 0xe59f0014
    dcd 0xe8bd8010
    dcd data_ov000_0205ac3c
    dcd 0x0000000c
    dcd data_ov012_0205c2bc
    dcd 0x0000000b
    dcd data_ov011_0205e8a0
    dcd func_ov000_0205a5e8
}
