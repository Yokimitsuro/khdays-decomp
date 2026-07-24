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
    u8 pad_0004[0xd150];
    void *resource;
    u8 pad_d158[8];
    void (*teardownCallback)(void);
    u8 pad_d164[8];
    int (*readyCallback)(void);
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int brightness);
extern void func_0201e4a8(int processor, int overlayId);
extern int func_02024fd4(void *resource);
extern void func_020235bc(int handlerId);
extern void func_02020a90(int value);
extern void func_020208f0(void);
extern Ov000StateFn func_ov000_02059e00(const OverlayStartParams *params);
asm Ov000StateFn func_ov000_0205a554(void)
{
    dcd 0xe92d4010
    dcd 0xe24dd008
    bl NNSi_FndGetCurrentRootHeap
    dcd 0xe1a04000
    dcd 0xe2840a0d
    dcd 0xe590016c
    dcd 0xe12fff30
    dcd 0xe3500000
    dcd 0x028dd008
    dcd 0x03a00000
    dcd 0x08bd8010
    dcd 0xe2840a0d
    dcd 0xe5900160
    dcd 0xe12fff30
    dcd 0xe3e0000f
    bl func_0201e374
    dcd 0xe59f1044
    dcd 0xe3a00000
    bl func_0201e4a8
    dcd 0xe2840a0d
    dcd 0xe5900154
    bl func_02024fd4
    dcd 0xe1d410f2
    dcd 0xe59f002c
    dcd 0xe58d1000
    dcd 0xe1d410f0
    dcd 0xe58d1004
    bl func_020235bc
    dcd 0xe3a00000
    bl func_02020a90
    bl func_020208f0
    dcd 0xe28d0000
    bl func_ov000_02059e00
    dcd 0xe28dd008
    dcd 0xe8bd8010
    dcd 0x00000018
    dcd 0x000020e9
}
