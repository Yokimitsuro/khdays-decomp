typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef u32 FSOverlayID;

extern u32 OVERLAY_302_ID[1];
#define FS_OVERLAY_ID_ov302 ((FSOverlayID)(u32)&OVERLAY_302_ID)

typedef struct Ov009ListConfig {
    u32 field0;
    u32 field4;
    u32 capacity;
} Ov009ListConfig;

typedef struct Ov009ObjectList {
    u32 words[9];
} Ov009ObjectList;

extern const Ov009ListConfig data_ov009_02056108;
extern const u16 data_ov009_02056114[60][2];

extern u32 func_020235d0(u32 field, int index);
extern void func_020235e8(u32 field, int index, u32 value);
extern void func_0201e470(int processor, int overlay);
extern void func_0201e4a8(int processor, int overlay);
extern void func_ov009_02055618(
    Ov009ObjectList *list,
    const Ov009ListConfig *config
);
extern void func_ov009_02055678(Ov009ObjectList *list);
extern int func_ov009_020556e4(
    Ov009ObjectList *firstList,
    Ov009ObjectList *secondList,
    int *result,
    int minimum,
    int maximum
);
extern int func_02025694(const u16 *bits, int index);
extern void func_02025640(u16 *bits, int index);

int func_ov009_020557dc(void)
{
    u8 *savedBits;
    int snapshotIndex;
    int changes = 0;
    u16 savedBitsStorage[4];
    int allowNotification = 1;
    Ov009ListConfig config = data_ov009_02056108;
    Ov009ObjectList firstList;
    Ov009ObjectList secondList;
    FSOverlayID overlayId;

    {
        savedBits = (u8 *)savedBitsStorage;
        snapshotIndex = changes;
        do {
            *(u16 *)savedBits = (u16)func_020235d0(
                (u32)(snapshotIndex + 0x40) * 16 + 0x40c,
                16
            );
            savedBits += 2;
            snapshotIndex++;
        } while (snapshotIndex < 4);
    }

    overlayId = FS_OVERLAY_ID_ov302;
    func_0201e470(0, overlayId);
    func_ov009_02055618(&firstList, &config);
    config.capacity = 6;
    func_ov009_02055618(&secondList, &config);

    {
        int rangeIndex;

        rangeIndex = 0;
        do {
            if (func_ov009_020556e4(
                    &firstList,
                    &secondList,
                    &allowNotification,
                    data_ov009_02056114[rangeIndex][0],
                    data_ov009_02056114[rangeIndex][1]
                ) != 0 &&
                func_02025694(savedBitsStorage, rangeIndex) == 0) {
                changes++;
                func_02025640(savedBitsStorage, rangeIndex);
            }
            rangeIndex++;
        } while (rangeIndex < 60);
    }

    func_ov009_02055678(&secondList);
    func_ov009_02055678(&firstList);
    func_0201e4a8(0, overlayId);

    if (changes != 0) {
        u32 difference = 0;
        u16 saved;
        int restoreIndex;

        savedBits = (u8 *)savedBitsStorage;
        restoreIndex = 0;
        do {
            u32 field = (u32)(restoreIndex + 0x40) * 16 + 0x40c;
            saved = *(u16 *)savedBits;
            savedBits += 2;
            u32 current = func_020235d0(field, 16);

            difference |= saved ^ (current & 0xffff);
            func_020235e8(field, 16, saved);
            restoreIndex++;
        } while (restoreIndex < 4);

        if (difference != 0 &&
            allowNotification != 0 &&
            func_020235d0(0x190f, 2) == 0) {
            func_020235e8(0x190f, 2, 1);
        }
    }

    return changes != 0;
}
