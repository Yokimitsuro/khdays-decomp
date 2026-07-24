typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OverlayVector {
    int x;
    int y;
} OverlayVector;

typedef struct Ov000SceneContext {
    u8 pad_0000[0x4c];
    u8 selectionObject[0x4b24];
    int alternatePosition;
} Ov000SceneContext;

extern Ov000SceneContext *volatile data_ov000_0205ac24;
extern const int data_ov000_0205a6bc[2];
extern int *func_ov000_02055b48(void *object, int id);
extern OverlayVector *func_ov000_02055bc4(void *object, int *entry);
extern void func_ov000_02055bfc(
    void *object,
    int *entry,
    const OverlayVector *position
);

asm void func_ov000_02051b98(void) {
    dcd 0xe92d4ff8
    dcd 0xe24dd008
    dcd 0xe59f0098
    dcd 0xe3a0b922
    dcd 0xe5907000
    dcd 0xe59f6090
    dcd 0xe3a08000
    dcd 0xe1a0400b
    dcd 0xe3a0590a
    dcd 0xe796a108
    dcd 0xe287004c
    dcd 0xe1a0100a
    bl func_ov000_02055b48
    dcd 0xe1a09000
    dcd 0xe1a01009
    dcd 0xe287004c
    bl func_ov000_02055bc4
    dcd 0xe5901004
    dcd 0xe59f0058
    dcd 0xe58d1004
    dcd 0xe5900000
    dcd 0xe2800901
    dcd 0xe5900b70
    dcd 0xe3500000
    dcd 0x0a000003
    dcd 0xe35a0015
    dcd 0x058d5000
    dcd 0x158d4000
    dcd 0xea000003
    dcd 0xe35a0015
    dcd 0x058db000
    dcd 0x13a0090a
    dcd 0x158d0000
    dcd 0xe1a01009
    dcd 0xe28d2000
    dcd 0xe287004c
    bl func_ov000_02055bfc
    dcd 0xe2888001
    dcd 0xe3580002
    dcd 0x3affffe0
    dcd 0xe28dd008
    dcd 0xe8bd8ff8
    dcd data_ov000_0205ac24
    dcd data_ov000_0205a6bc
}
