#pragma thumb on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov022AnimationSlot Ov022AnimationSlot;

typedef struct Ov022AnimationSetup {
    u32 resource00;
    u32 slotCount04;
    u32 kind08;
    void *owner0c;
    u32 group10;
} Ov022AnimationSetup;

typedef struct Ov022AnimationRoot {
    u8 mode00 : 2;
    u8 slotCount00 : 6;
    u8 kind01 : 3;
    u8 initialized01 : 1;
    u8 localPlayer01 : 1;
    u8 flags01 : 3;
    char padding002[0x02];
    void *owner04;
    u16 value08;
    char padding00a[0x02];
    Ov022AnimationSlot *slots0c;
    char padding010[0x10];
    u8 group20;
} Ov022AnimationRoot;

typedef int (*Ov022SceneCallback)(void);

extern Ov022AnimationRoot *NNSi_FndGetCurrentRootHeap(void);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 size);
extern void func_ov022_02088f74(Ov022AnimationSetup *setup);
extern int func_02020a9c(void);
extern u8 data_0204be04;
extern int func_ov022_02088dec(void);

Ov022SceneCallback func_ov022_02088d18(Ov022AnimationSetup *setup)
{
    Ov022AnimationRoot *root;

    root = NNSi_FndGetCurrentRootHeap();
    root->slotCount00 = (u8)setup->slotCount04;
    root->kind01 = (u8)setup->kind08;
    root->owner04 = setup->owner0c;
    root->mode00 = 0;
    root->value08 = 0;
    root->initialized01 = 1;
    root->group20 = (u8)setup->group10;
    root->slots0c = NNSi_FndAllocFromDefaultExpHeap(root->slotCount00 * 0x114);
    func_ov022_02088f74(setup);

    if (func_02020a9c() == 0x2a) {
        root->localPlayer01 = data_0204be04;
    } else {
        root->localPlayer01 = 0;
    }

    return func_ov022_02088dec;
}
