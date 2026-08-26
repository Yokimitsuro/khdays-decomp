typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov022LowByte16 {
    unsigned short lowByte : 8;
    unsigned short highByte : 8;
} Ov022LowByte16;

typedef struct Ov022Candidate {
    char pad_0000[0x60];
    Ov022LowByte16 flags60;
    char pad_0062[0x117];
    u8 special179;
    char pad_017a[0x32];
    u16 flags1ac;
    char pad_01ae[0x6a];
    s16 field218;
    char pad_021a[0x12];
    char list22c[4];
} Ov022Candidate;

typedef struct Ov022IteratorNode {
    Ov022Candidate *item;
} Ov022IteratorNode;

typedef struct Ov022CandidateContainer {
    char pad_0000[0x80];
    char list80[4];
} Ov022CandidateContainer;

typedef struct Ov022ActorSelectionLink {
    char pad_0000[4];
    Ov022CandidateContainer *container4;
} Ov022ActorSelectionLink;

typedef struct Ov022Actor {
    char pad_0000[9];
    u8 index9;
    char pad_000a[0x4e2];
    Ov022ActorSelectionLink *selection4ec;
} Ov022Actor;

extern u8 data_0204c248[];
extern u8 data_0204c240;

extern void *func_ov022_020881f8(int index);
extern Ov022Actor *func_01fffde0(int index);
extern int func_020358f4(int index, int parameter);
extern int func_ov022_02084a34(u32 *selectionFlags, int index,
                               int bestDistance);
extern int func_ov022_02084be8(u32 *selectionFlags, int index,
                               int bestDistance);
extern Ov022IteratorNode *func_01fffd70(void *list);
extern int func_ov022_02084d2c(u32 *selectionFlags, int index,
                               Ov022Candidate *candidate, int bestDistance);
extern Ov022IteratorNode *func_01fffd8c(void *list);

int func_ov022_02084fe8(u32 *selectionFlags, int index)
{
    Ov022CandidateContainer *container;
    Ov022Actor *actor;
    int result = 0;
    int ready = 1;
    int bestDistance;
    Ov022IteratorNode *iterator;
    Ov022Candidate *candidate;

    func_ov022_020881f8(index);
    actor = func_01fffde0(index);
    bestDistance = 0x9000;
    if (func_020358f4(actor->index9, 0x55) != 0) {
        bestDistance = 0xd800;
    }

    {
        int scannedDistance =
            func_ov022_02084a34(selectionFlags, index, bestDistance);
        if (scannedDistance != bestDistance) {
            result = 1;
        }
    }

    if (data_0204c248[0x0b] != 0 && (data_0204c240 & 4) != 0) {
        {
            int scannedDistance =
                func_ov022_02084be8(selectionFlags, index, bestDistance);
            if (scannedDistance != bestDistance) {
                result = 1;
            }
        }
    }

    if (actor->selection4ec == 0) {
        ready = 0;
    } else {
        container = actor->selection4ec->container4;
        if (container == 0) {
            ready = 0;
        }
    }

    if (ready != 0) {
        iterator = func_01fffd70(container->list80);
        candidate = iterator == 0 ? 0 : iterator->item;
        while (candidate != 0) {
            if ((candidate->flags1ac & 2) == 0 &&
                (candidate->flags60.lowByte & 1) != 0 &&
                (candidate->flags1ac & 1) == 0 &&
                candidate->field218 != 0) {
                if (func_ov022_02084d2c(selectionFlags, index, candidate,
                                         bestDistance) != 0) {
                    result = 1;
                }
            }

            iterator = func_01fffd8c(container->list80);
            candidate = iterator == 0 ? 0 : iterator->item;
        }
    }

    return result;
}

