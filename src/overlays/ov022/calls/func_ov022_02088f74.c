#pragma opt_dead_assignments off

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov022AnimationSlot {
    s8 active;
    u8 pad001[3];
    u16 resource[1];
    u8 pad006[0xae];
    int scaleZ;
    int scaleY;
    int scaleX;
    u8 pad0c0[0x4c];
    void *state;
    s8 kind;
    s8 subkind;
    u8 pad112[2];
} Ov022AnimationSlot;

typedef struct Ov022RootHeap {
    u8 countAndFlags;
    u8 pad001[11];
    Ov022AnimationSlot *slots;
    u8 pad010[0x10];
    u8 group;
} Ov022RootHeap;

typedef struct Ov022AnimationSetup {
    u32 resource;
} Ov022AnimationSetup;

extern Ov022RootHeap *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a634(int object, int resource, int mode, int group);
extern void func_ov022_020892f0(u16 *resource, int bindingIndex);

void func_ov022_02088f74(Ov022AnimationSetup *setup) {
    int offset;
    int i;
    Ov022RootHeap *heap;
    Ov022AnimationSlot *slot;
    int scale;

    i = 0;
    heap = 0;
    slot = 0;
    offset = 0;

    heap = NNSi_FndGetCurrentRootHeap();
    i = 0;
    if (0 < (int)(((u32)heap->countAndFlags << 24) >> 26)) {
        offset = 0;
        scale = 0x1000;
        do {
            int slotAddress;
            Ov022AnimationSlot *slots;

            slots = heap->slots;
            slotAddress = (int)slots + offset;
            slot = (Ov022AnimationSlot *)slotAddress;
            func_0202a634((int)slot->resource, setup->resource, 1,
                          heap->group);
            slot->scaleZ = slot->scaleY = slot->scaleX = scale;
            func_ov022_020892f0(slot->resource, 0);
            *(s8 *)((char *)slots + offset) = 0;
            slot->state = 0;
            slot->kind = -1;
            slot->subkind = -1;
            i++;
            offset += 0x114;
        } while (i < (int)(((u32)heap->countAndFlags << 24) >> 26));
    }
}
