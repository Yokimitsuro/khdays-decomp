extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);
extern int func_02039700(void *a, void *b, int c, int d, int e, int f);
extern int FX_Sqrt(int x);

typedef struct { int w[8]; } Blk32;

typedef struct {
    char pad0[4];
    void *owner;            /* +4 */
    char pad8[0x1d8 - 8];
    char *shape;             /* +0x1d8 */
} Entry;

int func_ov107_020c8df0(char *self, void *position, void **outArray)
{
    char *owner = *(char **)(self + 4);
    int count = 0;
    void *outerIt;
    Entry *cand;

    outerIt = (void *)func_01fffd70(owner + 0xa8);
    cand = !outerIt ? 0 : *(Entry **)outerIt;

    while (cand != 0) {
        if (cand->owner == *(char **)(self + 4)) {
            Blk32 blk = *(Blk32 *)(cand->shape + 0x78);
            int dist = func_02039700(&blk, position, 0, 0, 0, 0);
            int d = FX_Sqrt(dist);
            if (d <= blk.w[7]) {
                outArray[count] = cand;
                count++;
            }
        }
        outerIt = (void *)func_01fffd8c(owner + 0xa8);
        cand = !outerIt ? 0 : *(Entry **)outerIt;
    }

    return count;
}
