typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*Ov000StateFn)(void);

typedef struct OverlayStartParams {
    u32 first;
    u32 second;
} OverlayStartParams;

typedef struct Ov000SceneContext {
    short secondValue;
    short firstValue;
    u8 pad_0004[0xd134];
    int transitionMode;
    void *sharingHandle;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov012_0205b920(void);
extern int func_ov011_0205dc4c(void);
extern void *WM_EndKeySharing_0x02023ad0(void *handle);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void func_0201e4a8(int processor, int overlayId);
extern void func_020235bc(int handlerId);
extern int func_020208f0(void);
extern Ov000StateFn func_ov000_02059e00(
    const OverlayStartParams *params
);

asm Ov000StateFn func_ov000_0205a5e8(void) {
    dcd 0xe92d4010
    dcd 0xe24dd008
    bl NNSi_FndGetCurrentRootHeap
    dcd 0xe1a04000
    dcd 0xe2840a0d
    dcd 0xe5900138
    dcd 0xe3500000
    dcd 0x1a000005
    bl func_ov012_0205b920
    dcd 0xe3500000
    dcd 0x1a000007
    dcd 0xe28dd008
    dcd 0xe3a00000
    dcd 0xe8bd8010
    bl func_ov011_0205dc4c
    dcd 0xe3500000
    dcd 0x028dd008
    dcd 0x03a00000
    dcd 0x08bd8010
    dcd 0xe2840a0d
    dcd 0xe590013c
    bl WM_EndKeySharing_0x02023ad0
    dcd 0xe3e0000f
    bl func_0201e374
    dcd 0xe3e0000f
    bl func_0201e3cc
    dcd 0xe2840a0d
    dcd 0xe5900138
    dcd 0xe3500000
    dcd 0xe3a00000
    dcd 0x1a000002
    dcd 0xe59f1038
    bl func_0201e4a8
    dcd 0xea000001
    dcd 0xe59f1030
    bl func_0201e4a8
    dcd 0xe1d410f2
    dcd 0xe59f0028
    dcd 0xe58d1000
    dcd 0xe1d410f0
    dcd 0xe58d1004
    bl func_020235bc
    bl func_020208f0
    dcd 0xe28d0000
    bl func_ov000_02059e00
    dcd 0xe28dd008
    dcd 0xe8bd8010
    dcd 0x0000000c
    dcd 0x0000000b
    dcd 0x000020e9
}
