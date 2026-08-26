typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022ActorNode {
    char pad_0000[0x80];
    u16 angle80;
} Ov022ActorNode;

typedef struct Ov022Actor {
    char pad_0000[0x20];
    Ov022ActorNode *node20;
} Ov022Actor;

typedef struct Ov022Target {
    VecFx32 position;
} Ov022Target;

typedef struct Ov022TargetEntry {
    char pad_0000[4];
    struct Ov022TargetEntry *next4;
    char pad_0008[0x0a];
    u16 flags12;
} Ov022TargetEntry;

extern const short data_0203d210[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern VecFx32 *func_ov022_020881f8(int index);
extern Ov022Actor *func_01fffde0(int index);
extern int func_01fffe14(void);
extern void func_ov022_02088474(int index);
extern int func_ov002_02072754(void);
extern Ov022TargetEntry *func_ov002_02076688(u16 value);
extern Ov022Target *func_ov002_02076d24(Ov022TargetEntry *entry);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern int func_ov002_02076d68(Ov022TargetEntry *entry);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *vector);
extern void func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_ov022_02085b00(Ov022Actor *actor, Ov022Target *target,
                                VecFx32 *result, int mode);
extern int func_ov022_02085cc0(u32 *state, const VecFx32 *result);
extern void func_ov022_02084810(u32 *selectionFlags,
                                Ov022TargetEntry *entry,
                                const VecFx32 *result);

int func_ov022_02084a34(u32 *selectionFlags, int index, int bestDistance)
{
    VecFx32 direction;
    VecFx32 facing;
    VecFx32 resultPosition;
    VecFx32 targetHorizontal;
    VecFx32 originHorizontal;
    VecFx32 *origin;
    Ov022TargetEntry *entry;
    Ov022Target *target;
    Ov022Actor *actor;

    NNSi_FndGetCurrentRootHeap();
    origin = func_ov022_020881f8(index);
    actor = func_01fffde0(index);
    func_ov022_02088474(func_01fffe14());
    entry = func_ov002_02076688((u16)func_ov002_02072754());

    while (entry != 0) {
        int distance;
        int angle;
        int horizontalDistance;
        const short *table;

        target = func_ov002_02076d24(entry);
        if (target != 0 && (entry->flags12 & 8) != 0) {
            distance = func_01ff8e94(&target->position, origin);
            if (distance <= func_ov002_02076d68(entry)) {
                VEC_Subtract(&target->position, origin, &direction);
                if (VEC_Mag(&direction) != 0) {
                    func_01ff8d18(&direction, &direction);
                }

                angle = (u16)(actor->node20->angle80 - 0x8000);
                angle >>= 4;
                table = data_0203d210;
                facing.x = -table[angle << 1];
                facing.z = -table[(angle << 1) + 1];
                direction.y = 0;
                facing.y = 0;

                originHorizontal = *origin;
                targetHorizontal = target->position;
                originHorizontal.y = targetHorizontal.y = 0;
                horizontalDistance = func_01ff8e94(
                    &targetHorizontal, &originHorizontal);

                if (VEC_DotProduct(&facing, &direction) >= 0x800 ||
                    horizontalDistance <= 0x1000) {
                    func_ov022_02085b00(actor, target, &resultPosition, 2);
                    if (func_ov022_02085cc0(&selectionFlags[7],
                                            &resultPosition) != 0) {
                        func_ov022_02084810(selectionFlags, entry,
                                            &resultPosition);
                        bestDistance = resultPosition.x;
                    }
                }
            }
        }
        entry = entry->next4;
    }

    return bestDistance;
}

