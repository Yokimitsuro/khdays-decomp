/* Pick the nearest active slot mate: walks the +4 manager's +0xa8 list and, among the entries
 * with bit 1 of +0x40 set, keeps the one with the smallest squared distance from this actor's
 * +0xb0 pose whose +0x1b4 kind bucket (in this actor's +0x410 histogram) holds at most 0x3e7;
 * ties resolve by the bucket count. The winner's bucket is incremented and returned. */
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern void VEC_Subtract(int *a, int *b, int *out);

struct Flags40 { int b0 : 1; int b1 : 1; };

static inline int FX_SqSum3(int a, int b, int c) {
    long long sum = (long long)a * a + (long long)b * b + (long long)c * c;
    return (int)((sum + 0x800) >> 12);
}

char *func_ov244_020cd300(char *actor)
{
    int *counts = (int *)(actor + 0x410);
    int limit = 0x3e7;
    int best = 0;
    int bestDiff = best - 0x80000001;
    int kind;
    int mgr = *(int *)(actor + 4);
    int *pe = func_01fffd70(mgr + 0xa8);
    int e = (pe == 0) ? 0 : *pe;

    while (e != 0) {
        kind = *(unsigned char *)(e + 0x1b4);
        if (((struct Flags40 *)(e + 0x40))->b1 != 0) {
            int delta[3];
            int distSq;

            VEC_Subtract((int *)(actor + 0xb0), (int *)(e + 0xb0), delta);
            distSq = FX_SqSum3(delta[0], delta[1], delta[2]);
            if (distSq < bestDiff) {
                if (limit >= counts[kind]) {
                    bestDiff = distSq;
                    best = e;
                    limit = counts[kind];
                }
            }
        }
        pe = func_01fffd8c(mgr + 0xa8);
        e = (pe == 0) ? 0 : *pe;
    }
    if (best != 0) {
        counts[*(unsigned char *)(best + 0x1b4)]++;
    }
    return (char *)best;
}
