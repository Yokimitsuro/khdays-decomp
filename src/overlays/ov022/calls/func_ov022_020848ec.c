typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Ov022LowByte16 {
    unsigned short lowByte : 8;
    unsigned short highByte : 8;
} Ov022LowByte16;

typedef struct Ov022Candidate {
    char pad_0000[0x60];
    u16 flags60;
    char pad_0062[0x14a];
    u16 flags1ac;
    char pad_01ae[0x6a];
    s16 value218;
} Ov022Candidate;

typedef struct Ov022ListOwner {
    char pad_0000[0x80];
    char list80[4];
} Ov022ListOwner;

typedef struct Ov022ActorLink {
    char pad_0000[4];
    Ov022ListOwner *listOwner4;
} Ov022ActorLink;

typedef struct Ov022Actor {
    char pad_0000[0x4ec];
    Ov022ActorLink *link4ec;
} Ov022Actor;

typedef struct Ov022SelectionController {
    u32 flags0;
    u32 selectionFlags;
    int type;
    char pad_000c[0x14];
    int scanDistance;
    int selectedIndex;
    int selectedValue;
} Ov022SelectionController;

typedef struct Ov022RuntimeConfig {
    char pad_0000[0x0b];
    u8 enableSecondarySearchB;
} Ov022RuntimeConfig;

extern Ov022RuntimeConfig data_0204c248;
extern u8 data_0204c240;

extern Ov022SelectionController *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern void *func_ov022_020881f8(int index);
extern Ov022Actor *func_01fffde0(int index);
extern int func_ov022_02084a34(u32 *selectionFlags, int index, int distance);
extern int func_ov022_02084be8(u32 *selectionFlags, int index, int distance);
extern Ov022Candidate **func_01fffd70(void *list);
extern int func_ov022_02084d2c(u32 *selectionFlags, int index,
                               Ov022Candidate *candidate, int distance);
extern Ov022Candidate **func_01fffd8c(void *list);

int func_ov022_020848ec(void)
{
    Ov022SelectionController *context;
    int index;
    int result = 0;
    Ov022Actor *actor;
    Ov022ActorLink *link;
    Ov022ListOwner *listOwner;
    Ov022Candidate **slot;
    Ov022Candidate *candidate;

    context = NNSi_FndGetCurrentRootHeap();
    index = func_01fffe14();
    func_ov022_020881f8(index);
    actor = func_01fffde0(index);

    context->scanDistance = 0x1e000;
    context->selectedIndex = -1;
    context->selectedValue = result;

    if (func_ov022_02084a34(&context->selectionFlags, index, 0x1e000) !=
        0x1e000) {
        result = 1;
    }
    if (data_0204c248.enableSecondarySearchB != 0 &&
        (data_0204c240 & 4) != 0 &&
        func_ov022_02084be8(&context->selectionFlags, index, 0x1e000) !=
            0x1e000) {
        result = 1;
    }

    link = actor->link4ec;
    if (link == 0) {
        return result;
    }
    listOwner = link->listOwner4;
    if (listOwner == 0) {
        return result;
    }

    slot = func_01fffd70(listOwner->list80);
    candidate = slot == 0 ? 0 : *slot;
    while (candidate != 0) {
        if ((candidate->flags1ac & 2) == 0 &&
            (((Ov022LowByte16 *)&candidate->flags60)->lowByte & 1) != 0 &&
            candidate->value218 != 0 &&
            func_ov022_02084d2c(&context->selectionFlags, index,
                                candidate, 0x1e000) != 0) {
            result = 1;
        }

        slot = func_01fffd8c(listOwner->list80);
        candidate = slot == 0 ? 0 : *slot;
    }

    return result;
}

