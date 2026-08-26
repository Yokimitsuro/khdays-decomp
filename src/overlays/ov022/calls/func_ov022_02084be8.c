typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022Actor {
    char pad_0000[0x12];
    u16 flags12;
    char pad_0014[0x52];
    s16 group66;
    char pad_0068[0x3fc];
    u64 flags464;
} Ov022Actor;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern VecFx32 *func_ov022_020881f8(int index);
extern Ov022Actor *func_01fffde0(int index);
extern int func_ov022_020882f8(void);
extern int func_01fffe14(void);
extern void func_ov022_020ad44c(VecFx32 *out, Ov022Actor *actor);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern void func_ov022_02085b00(Ov022Actor *actor, const VecFx32 *target,
                                VecFx32 *result, int mode);
extern int func_ov022_02085cc0(u32 *state, const VecFx32 *result);
extern int func_ov022_02084e7c(int index, const VecFx32 *position);
extern void func_ov022_02084880(u32 *selectionFlags, Ov022Actor *candidate,
                                const VecFx32 *result);

int func_ov022_02084be8(u32 *selectionFlags, int index, int bestDistance)
{
    VecFx32 candidatePosition;
    VecFx32 resultPosition;
    int resultDistance = bestDistance;
    VecFx32 *origin;
    Ov022Actor *actor;
    int i;

    NNSi_FndGetCurrentRootHeap();
    origin = func_ov022_020881f8(index);
    actor = func_01fffde0(index);

    for (i = 0; i < func_ov022_020882f8(); i++) {
        Ov022Actor *candidate;

        if (i != func_01fffe14()) {
            candidate = func_01fffde0(i);
            if (candidate->flags12 != 0 &&
                candidate->group66 == actor->group66 &&
                (candidate->flags464 & 0x200000000ULL) == 0) {
                func_ov022_020ad44c(&candidatePosition, candidate);
                if (func_01ff8e94(&candidatePosition, origin) <= bestDistance) {
                    func_ov022_02085b00(actor, &candidatePosition,
                                        &resultPosition, 3);
                    if (func_ov022_02085cc0(&selectionFlags[7],
                                            &resultPosition) != 0 &&
                        func_ov022_02084e7c(index,
                                            &candidatePosition) != 0) {
                        func_ov022_02084880(selectionFlags, candidate,
                                            &resultPosition);
                        resultDistance = resultPosition.x;
                    }
                }
            }
        }
    }

    return resultDistance;
}

