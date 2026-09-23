/* Pick the live, targetable (+0x40 bit 1, +0x60 bit 0) entity of the actor's +4 manager list that
 * lies FARTHEST from it, measured as squared centre distance minus both squared radii (+0x80),
 * clamped at 0; the distance goes to `pDistSq` when both exist. Mirror of ov107 020cab14. */
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern void VEC_Subtract(int *a, int *b, int *out);

struct flags16 { unsigned short lo : 8; unsigned short hi : 8; };

static inline int FX_SqSum3(int a, int b, int c) {
    long long sum = (long long)a * a + (long long)b * b + (long long)c * c;
    return (int)((sum + 0x800) >> 12);
}

static inline int FX_Sq(int a) {
    return (int)(((long long)a * a + 0x800) >> 12);
}

char *func_ov259_020d15bc(char *actor, int *pDistSq)
{
    int best = 0;
    int bestDiff = best;
    int mgr = *(int *)(actor + 4);
    int *pe = func_01fffd70(mgr + 0xa8);
    int e = (pe == 0) ? 0 : *pe;

    while (e != 0) {
        if (((*(int *)(e + 0x40) << 0x1e) >> 0x1f) != 0 &&
            (((struct flags16 *)(e + 0x60))->lo & 1) != 0) {
            int delta[3];
            int diff;

            VEC_Subtract((int *)(e + 0x74), (int *)(actor + 0x74), delta);
            diff = FX_SqSum3(delta[0], delta[1], delta[2]) - (FX_Sq(*(int *)(actor + 0x80)) + FX_Sq(*(int *)(e + 0x80)));
            if (diff < 0) diff = 0;
            if (diff >= bestDiff) {
                bestDiff = diff;
                best = e;
            }
        }
        pe = func_01fffd8c(mgr + 0xa8);
        e = (pe == 0) ? 0 : *pe;
    }

    if (best != 0 && pDistSq != 0) {
        *pDistSq = bestDiff;
    }
    return (char *)best;
}
