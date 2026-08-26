typedef unsigned char u8;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022LowByte32 {
    unsigned int lowByte : 8;
    unsigned int rest : 24;
} Ov022LowByte32;

typedef struct Ov022Candidate {
    char pad_0000[0x179];
    u8 special179;
    char pad_017a[0xb2];
    char list22c[4];
} Ov022Candidate;

typedef struct Ov022PartNode {
    void *item;
    char pad_0004[4];
    u32 flags8;
} Ov022PartNode;

typedef struct Ov022OriginLimit {
    VecFx32 origin;
    int distance;
} Ov022OriginLimit;

extern VecFx32 *func_ov022_020881f8(int index);
extern void *func_01fffde0(int index);
extern Ov022PartNode *func_01fffd70(void *list);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern int func_ov107_020c3504(void *item, const Ov022OriginLimit *limit,
                               int mode);
extern void func_ov022_02085b00(void *actor, const VecFx32 *target,
                                VecFx32 *result, int mode);
extern int func_ov022_02085cc0(u32 *state, const VecFx32 *result);
extern int func_ov022_02084e7c(int index, const VecFx32 *position);
extern void func_ov022_0208484c(u32 *selectionFlags,
                                Ov022Candidate *candidate,
                                Ov022PartNode *node,
                                const VecFx32 *result);
extern Ov022PartNode *func_01fffd8c(void *list);

int func_ov022_02084d2c(u32 *selectionFlags, int index,
                         Ov022Candidate *candidate, int bestDistance)
{
    VecFx32 resultPosition;
    Ov022OriginLimit originLimit;
    int result = 0;
    Ov022PartNode *node;
    VecFx32 *origin;
    void *actor;

    origin = func_ov022_020881f8(index);
    actor = func_01fffde0(index);
    node = func_01fffd70(candidate->list22c);
    while (node != 0) {
        int valid = 0;

        if ((((Ov022LowByte32 *)&node->flags8)->lowByte & 2) == 0 &&
            (((Ov022LowByte32 *)&node->flags8)->lowByte & 1) != 0) {
            if (candidate->special179 != 1) {
                if (func_01ff8e94(
                        (VecFx32 *)((char *)node->item + 4), origin) >
                    bestDistance) {
                    goto next_node;
                }
                originLimit.origin = *origin;
                originLimit.distance = bestDistance;
                if (func_ov107_020c3504(node->item, &originLimit, 0) != 0) {
                    valid = 1;
                }
            } else {
                valid = 1;
            }

            if (valid != 0) {
                func_ov022_02085b00(
                    actor, (VecFx32 *)((char *)node->item + 4),
                    &resultPosition, 1);
                if (func_ov022_02085cc0(&selectionFlags[7],
                                        &resultPosition) != 0) {
                    if (candidate->special179 == 1 ||
                        func_ov022_02084e7c(
                            index, (VecFx32 *)((char *)node->item + 4)) != 0) {
                        func_ov022_0208484c(selectionFlags, candidate, node,
                                            &resultPosition);
                        result = 1;
                    }
                }
            }
        }

    next_node:
        node = func_01fffd8c(candidate->list22c);
    }

    return result;
}

