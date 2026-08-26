typedef signed long long s64;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_01fffe14(void);
extern const VecFx32 *func_ov022_020881f8(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int func_ov022_02084668(const VecFx32 *position, const VecFx32 *basis,
                        int turn, int bound, int selectorId, int *newBound)
{
    VecFx32 delta;
    int candidateTurn;
    int result = 0;

    VEC_Subtract(position, func_ov022_020881f8(func_01fffe14()), &delta);
    candidateTurn = (int)(((s64)delta.x * basis->z + 0x800) >> 12) -
                    (int)(((s64)delta.z * basis->x + 0x800) >> 12);

    if (selectorId == 0x200) {
        if (candidateTurn > turn && candidateTurn < bound) {
            result = 1;
        }
    } else if (candidateTurn < turn && candidateTurn > bound) {
        result = 1;
    }

    *newBound = candidateTurn;
    return result;
}
