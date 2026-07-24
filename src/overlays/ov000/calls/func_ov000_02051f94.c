typedef unsigned char  u8;
typedef unsigned int u32;

typedef struct Ov000SelectionBlock {
    u8 pad_0000[0x4aa0];
    void *heapBuffers[3];
    u8 pad_4aac[0xc];
    void *specialBuffer;
    u8 pad_4abc[0x1ac];
    u8 resource4cb4[0xc];
    u8 resource4cc0[0x3c];
    u8 resource4cfc[0x3c];
    u8 resource4d38[1];
} Ov000SelectionBlock;

typedef struct Ov000SceneContext {
    u8 pad_0000[0x4c];
    Ov000SelectionBlock selection;
} Ov000SceneContext;

extern Ov000SceneContext *volatile data_ov000_0205ac24;
extern void func_ov000_02056960(void *resource);
extern void func_0202ffbc(void *resource);
extern void func_ov000_020568c8(Ov000SceneContext *context);
extern void func_ov000_0205651c(Ov000SceneContext *context);
extern void func_ov000_02055ad8(Ov000SelectionBlock *selection);
extern void func_ov000_02055b0c(Ov000SelectionBlock *selection);
extern void func_ov000_02055750(Ov000SelectionBlock *selection);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *destination, u32 size);
extern void func_020235bc(int handlerId);

asm void func_ov000_02051f94(void) {
    dcd 0xe92d4070
    dcd 0xe59f0174
    dcd 0xe3a02301
    dcd 0xe5921000
    dcd 0xe5904000
    dcd 0xe3c11a0e
    dcd 0xe5821000
    dcd 0xe5900000
    dcd 0xe28000b4
    dcd 0xe2800b13
    bl func_ov000_02056960
    dcd 0xe59f014c
    dcd 0xe5900000
    dcd 0xe28000fc
    dcd 0xe2800b13
    bl func_0202ffbc
    dcd 0xe59f0138
    dcd 0xe5900000
    dcd 0xe2800d33
    dcd 0xe2800901
    bl func_0202ffbc
    dcd 0xe59f0124
    dcd 0xe5900000
    dcd 0xe2800f4e
    dcd 0xe2800b13
    bl func_0202ffbc
    dcd 0xe1a00004
    bl func_ov000_020568c8
    dcd 0xe1a00004
    bl func_ov000_0205651c
    dcd 0xe284004c
    bl func_ov000_02055ad8
    dcd 0xe284004c
    bl func_ov000_02055b0c
    dcd 0xe284004c
    bl func_ov000_02055750
    dcd 0xe3a05000
    dcd 0xe59f60e4
    dcd 0xe1a04005
    dcd 0xe5960000
    dcd 0xe0800105
    dcd 0xe2800901
    dcd 0xe5900aec
    dcd 0xe3500000
    dcd 0x0a000004
    bl NNSi_FndFreeFromDefaultHeap
    dcd 0xe5960000
    dcd 0xe0800105
    dcd 0xe2800901
    dcd 0xe5804aec
    dcd 0xe2850001
    dcd 0xe20050ff
    dcd 0xe3550003
    dcd 0x3afffff0
    dcd 0xe59f00a0
    dcd 0xe5900000
    dcd 0xe2800901
    dcd 0xe5900b04
    dcd 0xe3500000
    dcd 0x0a000005
    bl NNSi_FndFreeFromDefaultHeap
    dcd 0xe59f0084
    dcd 0xe3a01000
    dcd 0xe5900000
    dcd 0xe2800901
    dcd 0xe5801b04
    bl G2S_GetBG0ScrPtr
    dcd 0xe1a01000
    dcd 0xe3a00000
    dcd 0xe3a02b02
    bl MIi_CpuClearFast
    bl G2S_GetBG1ScrPtr
    dcd 0xe1a01000
    dcd 0xe3a00000
    dcd 0xe3a02b02
    bl MIi_CpuClearFast
    bl G2S_GetBG2ScrPtr
    dcd 0xe1a01000
    dcd 0xe3a00000
    dcd 0xe3a02b02
    bl MIi_CpuClearFast
    bl G2S_GetBG3ScrPtr
    dcd 0xe1a01000
    dcd 0xe3a00000
    dcd 0xe3a02b02
    bl MIi_CpuClearFast
    dcd 0xe59f0024
    bl func_020235bc
    dcd 0xe59f0020
    bl func_020235bc
    dcd 0xe59f001c
    bl func_020235bc
    dcd 0xe3a01000
    dcd 0xe59f0004
    dcd 0xe5801000
    dcd 0xe8bd8070
    dcd data_ov000_0205ac24
    dcd 0x0000200a
    dcd 0x0000200c
    dcd 0x0000200d
}
