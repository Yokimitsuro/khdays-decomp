typedef unsigned char  u8;
typedef unsigned int u32;

typedef struct Ov000TrackerCapacity {
    int nodeCount;
    int resourceCount;
    int shortResourceCount;
    void *nodeInitializer;
    void *nodeDestructor;
} Ov000TrackerCapacity;

typedef struct Ov000ResourceTracker {
    u8 data[0x4c];
} Ov000ResourceTracker;

typedef struct Ov000ObjectList {
    u8 data[0x4a80];
} Ov000ObjectList;

typedef struct Ov000ObjectInitDesc {
    u32 resourceAddress;
    int mode;
    int field_08;
    int field_0c;
    int resourceCount;
    u32 paletteAddress;
} Ov000ObjectInitDesc;

typedef union Ov000ObjectInitStorage {
    int primary[6];
    int secondary[6];
} Ov000ObjectInitStorage;

typedef struct Ov000ListSceneContext {
    u8 pad_0000[0x84];
    int resourceBase;
    u8 pad_0088[0x84];
    Ov000ResourceTracker resourceTracker;
    Ov000ObjectList primaryObjectList;
    Ov000ObjectList secondaryObjectList;
    u8 pad_9658[0x3ae8];
    int *trackerEntry1;
    int *trackerEntry2;
    int *secondaryEntry2;
    int *secondaryEntry3;
    int *secondaryEntry1;
} Ov000ListSceneContext;

extern const Ov000TrackerCapacity data_ov000_0205a95c;

extern Ov000ListSceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_0205647c(Ov000ResourceTracker *tracker,
                                const Ov000TrackerCapacity *capacity);
extern void func_ov000_02056544(Ov000ResourceTracker *tracker,
                                u32 resourceAddress);
extern int *func_ov000_02056818(Ov000ResourceTracker *tracker,
                                unsigned int tag);
extern void func_ov000_020568ac(Ov000ResourceTracker *tracker, int *entry);
extern void func_ov000_020556c8(Ov000ObjectList *objectList,
                                const int *description);
extern int *func_ov000_02055b48(Ov000ObjectList *objectList, int id);
extern void func_ov000_02055cb4(Ov000ObjectList *objectList, int *entry,
                                int visible);

asm void func_ov000_02058e88(void) {
    dcd 0xe92d4030
    dcd 0xe24dd02c
    dcd 0xe59f51cc
    dcd 0xe28d4018
    dcd 0xe8b5000f
    dcd 0xe8a4000f
    dcd 0xe5950000
    dcd 0xe5840000
    bl NNSi_FndGetCurrentRootHeap
    dcd 0xe1a04000
    dcd 0xe28d1018
    dcd 0xe2840f43
    dcd 0xe2845ff6
    bl func_ov000_0205647c
    dcd 0xe5941084
    dcd 0xe59f019c
    dcd 0xe2811902
    dcd 0xe0010000
    dcd 0xe1a01380
    dcd 0xe2840f43
    dcd 0xe381111a
    bl func_ov000_02056544
    dcd 0xe2840f43
    dcd 0xe3a01000
    bl func_ov000_02056818
    dcd 0xe1a01000
    dcd 0xe2840f43
    bl func_ov000_020568ac
    dcd 0xe2840f43
    dcd 0xe3a01001
    bl func_ov000_02056818
    dcd 0xe2841a0d
    dcd 0xe5810140
    dcd 0xe2840f43
    dcd 0xe3a01002
    bl func_ov000_02056818
    dcd 0xe2841a0d
    dcd 0xe5810144
    dcd 0xe5940084
    dcd 0xe59f113c
    dcd 0xe2800902
    dcd 0xe0000001
    dcd 0xe1a00380
    dcd 0xe3800116
    dcd 0xe58d0000
    dcd 0xe3a00001
    dcd 0xe58d0004
    dcd 0xe3a00000
    dcd 0xe58d0008
    dcd 0xe58d000c
    dcd 0xe3a00002
    dcd 0xe58d0010
    dcd 0xe5942084
    dcd 0xe2840f56
    dcd 0xe2822902
    dcd 0xe0021001
    dcd 0xe1a01381
    dcd 0xe3811112
    dcd 0xe58d1014
    dcd 0xe28d1000
    bl func_ov000_020556c8
    dcd 0xe2840f56
    dcd 0xe3a01001
    bl func_ov000_02055b48
    dcd 0xe1a01000
    dcd 0xe2840f56
    dcd 0xe3a02000
    bl func_ov000_02055cb4
    dcd 0xe2840f56
    dcd 0xe3a01002
    bl func_ov000_02055b48
    dcd 0xe1a01000
    dcd 0xe2840f56
    dcd 0xe3a02000
    bl func_ov000_02055cb4
    dcd 0xe5941084
    dcd 0xe59f00a8
    dcd 0xe2811902
    dcd 0xe0011000
    dcd 0xe1a01381
    dcd 0xe381110a
    dcd 0xe58d1000
    dcd 0xe3a03002
    dcd 0xe3a02000
    dcd 0xe3a01015
    dcd 0xe58d1010
    dcd 0xe58d3004
    dcd 0xe58d2008
    dcd 0xe58d200c
    dcd 0xe5942084
    dcd 0xe28d1000
    dcd 0xe2822902
    dcd 0xe0020000
    dcd 0xe1a00380
    dcd 0xe3802106
    dcd 0xe2850b12
    dcd 0xe58d2014
    bl func_ov000_020556c8
    dcd 0xe2850b12
    dcd 0xe3a01002
    bl func_ov000_02055b48
    dcd 0xe2841a0d
    dcd 0xe5810148
    dcd 0xe2850b12
    dcd 0xe3a01003
    bl func_ov000_02055b48
    dcd 0xe2841a0d
    dcd 0xe581014c
    dcd 0xe2850b12
    dcd 0xe3a01001
    bl func_ov000_02055b48
    dcd 0xe2841a0d
    dcd 0xe5810150
    dcd 0xe5911150
    dcd 0xe2850b12
    dcd 0xe3a02001
    bl func_ov000_02055cb4
    dcd 0xe28dd02c
    dcd 0xe8bd8030
    dcd data_ov000_0205a95c
    dcd 0x00fffffc
}
