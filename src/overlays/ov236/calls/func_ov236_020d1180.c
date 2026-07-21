typedef struct { int x, y, z; } VecFx32;

extern void func_01ffa724(int scale, VecFx32 *dst, VecFx32 *src);
extern int func_0203c634(int self, int idx, void *handler);

/* Follow-up reaction: same aim-vector decay as 020d1114, then (unless locked) clear the retry
 * counter, set the actor's reaction state to 0xa, and re-arm the slot with no handler. */
void func_ov236_020d1180(int self) {
    int *node = *(int **)(self + 4);
    node[0x10] = 0;
    func_01ffa724(0xf00, (VecFx32 *)(node + 0xf), (VecFx32 *)(node + 0xf));
    *(VecFx32 *)(node + 6) = *(VecFx32 *)(node + 0xf);
    if (*(unsigned char *)(node[1] + 0xad) != 0) {
        return;
    }
    node[0x15] = 0;
    *(unsigned char *)(*node + 0x1c7) = 0xa;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
