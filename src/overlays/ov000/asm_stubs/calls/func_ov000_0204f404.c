typedef unsigned char u8;
typedef void *StateFn;

typedef struct {
    u8 pad_0000[0x5074];
    void *sharedResourceHandle;
    void *keySharingHandle;
} Ov000SceneContext;

typedef char Ov000SceneContext_size_check[
    sizeof(Ov000SceneContext) == 0x507c ? 1 : -1
];

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov012_0205b920(void);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void WM_EndKeySharing_0x02023ad0(void *handle);
extern void func_0201e4a8(int processor, int overlayId);
extern void func_0201e1d0(void);
extern void *func_ov000_0204d7c8(int variant);

asm StateFn func_ov000_0204f404(void)
{
    stmdb sp!, {r4, lr}
    bl NNSi_FndGetCurrentRootHeap
    mov r4, r0
    bl func_ov012_0205b920
    cmp r0, #0
    moveq r0, #0
    ldmeqia sp!, {r4, pc}
    mvn r0, #0xf
    bl func_0201e374
    mvn r0, #0xf
    bl func_0201e3cc
    add r0, r4, #0x5000
    ldr r0, [r0, #0x78]
    bl WM_EndKeySharing_0x02023ad0
    ldr r1, [pc, #0x30]
    mov r0, #0
    bl func_0201e4a8
    add r0, r4, #0x5000
    mvn r1, #0
    str r1, [r0, #0x74]
    bl func_0201e1d0
    ldr r2, [pc, #0x18]
    mov r0, #2
    ldrh r1, [r2]
    orr r1, r1, #0x8000
    strh r1, [r2]
    bl func_ov000_0204d7c8
    ldmia sp!, {r4, pc}
    dcd 12
    dcd 0x04000304
}
