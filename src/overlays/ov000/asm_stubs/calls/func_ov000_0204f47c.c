typedef unsigned char u8;
typedef void (*Ov000StateFn)(void);

typedef struct Ov000MenuTransitionContext {
    int fadeCounter;
    u8 pad_0004[8];
    u8 renderNode[1];
    u8 pad_000d[0x506b];
    void *loadedClass;
} Ov000MenuTransitionContext;

extern Ov000MenuTransitionContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202aa9c(void *renderNode);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern int func_02034014(int processor);
extern void func_ov000_0204dbb4(void);
extern void func_0201e470(int processor, int overlayId);
extern void *func_02023930(void *classDescriptor, int enabled);
extern Ov000MenuTransitionContext *data_ov000_0205ac20;
extern char data_ov012_0205c2bc[];
extern void func_ov000_0204f404(void);
asm Ov000StateFn func_ov000_0204f47c(void)
{
    dcd 0xe92d4010
    bl NNSi_FndGetCurrentRootHeap
    dcd 0xe1a04000
    dcd 0xe284000c
    bl func_0202aa9c
    dcd 0xe5940000
    dcd 0xe3500010
    dcd 0xca000005
    dcd 0xe2600000
    bl func_0201e374
    dcd 0xe5940000
    dcd 0xe2600000
    bl func_0201e3cc
    dcd 0xea000010
    dcd 0xe3a00000
    bl func_02034014
    dcd 0xe3500000
    dcd 0x1a00000c
    bl func_ov000_0204dbb4
    dcd 0xe59f203c
    dcd 0xe59f103c
    dcd 0xe3a00000
    dcd 0xe5824000
    bl func_0201e470
    dcd 0xe59f0030
    dcd 0xe3a01001
    bl func_02023930
    dcd 0xe2841a05
    dcd 0xe5810078
    dcd 0xe59f0020
    dcd 0xe8bd8010
    dcd 0xe5941000
    dcd 0xe3a00000
    dcd 0xe2811001
    dcd 0xe5841000
    dcd 0xe8bd8010
    dcd data_ov000_0205ac20
    dcd 0x0000000c
    dcd data_ov012_0205c2bc
    dcd func_ov000_0204f404
}
