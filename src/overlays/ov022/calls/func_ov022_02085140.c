typedef unsigned char u8;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct SphereFx32 {
    VecFx32 center;
    int radius;
} SphereFx32;

typedef struct Ov022SelectionRecord {
    int distance;
    int unused;
    int kind;
} Ov022SelectionRecord;

typedef struct Ov022PartScanState {
    struct Ov022PartNode *part;
    VecFx32 *origin;
    int radius;
    int accepted;
} Ov022PartScanState;

typedef struct Ov022NodeFlags {
    unsigned int lowByte : 8;
    unsigned int rest : 24;
} Ov022NodeFlags;

typedef struct Ov022PartNode {
    void *item;
    char pad_0004[4];
    unsigned int flags8;
} Ov022PartNode;

typedef struct Ov022Candidate {
    char pad_0000[0x179];
    u8 special179;
    char pad_017a[0xb2];
    char traversal22c[1];
} Ov022Candidate;

typedef struct Ov022SelectorContext {
    int flags;
    char selectionState[4];
} Ov022SelectorContext;

extern Ov022SelectorContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern VecFx32 *func_ov022_020881f8(int index);
extern void *func_01fffde0(int index);
extern Ov022PartNode *func_01fffd70(void *list);
extern Ov022PartNode *func_01fffd8c(void *list);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern int func_ov107_020c3504(void *part, const SphereFx32 *sphere, int mode);
extern void func_ov022_0208484c(int *state, Ov022Candidate *candidate,
                                Ov022PartNode *part,
                                const Ov022SelectionRecord *record);

int func_ov022_02085140(Ov022Candidate *candidate)
{
    SphereFx32 sphere;
    Ov022SelectionRecord record;
    int result = 0;
    Ov022SelectorContext *context = NNSi_FndGetCurrentRootHeap();
    Ov022PartScanState scan;
    int special;

    scan.part = 0;
    scan.origin = 0;
    scan.radius = 0x1e000;
    scan.accepted = 0;
    if (candidate == 0) {
        return 0;
    }
    special = candidate->special179 == 1;
    scan.origin = func_ov022_020881f8(func_01fffe14());
    func_01fffde0(func_01fffe14());
    if (special != 0) {
        scan.radius = 0x7fffffff;
    }

    scan.part = func_01fffd70(candidate->traversal22c);
    while (scan.part != 0) {
        scan.accepted = 0;
        unsigned int flags = ((Ov022NodeFlags *)&scan.part->flags8)->lowByte;

        if ((flags & 2) == 0 && (flags & 1) != 0) {
            if (special != 0) {
                goto accept_part;
            }
            if (func_01ff8e94((VecFx32 *)((char *)scan.part->item + 4), scan.origin) >
                scan.radius) {
                goto next_part;
            }
            sphere.center = *scan.origin;
            sphere.radius = scan.radius;
            if (func_ov107_020c3504(scan.part->item, &sphere,
                                    scan.accepted) != 0) {
                scan.accepted = 1;
            }
            goto test_part;

accept_part:
            scan.accepted = 1;
test_part:
            if (scan.accepted != 0) {
                record.distance = func_01ff8e94(
                    scan.origin, (VecFx32 *)((char *)scan.part->item + 4));
                record.unused = 0;
                record.kind = 1;
                func_ov022_0208484c((int *)context->selectionState, candidate,
                                    scan.part, &record);
                result = 1;
            }
        }
next_part:
        scan.part = func_01fffd8c(candidate->traversal22c);
    }
    return result;
}
