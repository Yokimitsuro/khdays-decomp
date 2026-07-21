typedef struct { int x, y, z; } VecFx32;

extern void func_01ffa724(int scale, VecFx32 *dst, VecFx32 *src);
extern int func_ov107_020c9264(int obj, int a, int b);
extern int func_0203c634(int self, int idx, void *handler);
extern void func_ov278_020d1134(int self);

/* Reaction: kill vertical drift (Y=0), decay the aim vector to 3/4 scale, copy it into the
 * active velocity slot, then (unless the sub-target is locked) cancel action 0xf and re-arm the
 * follow-up reaction 020d1180. */
void func_ov278_020d10c8(int self) {
    int *node = *(int **)(self + 4);
    node[0x10] = 0;
    func_01ffa724(0xf00, (VecFx32 *)(node + 0xf), (VecFx32 *)(node + 0xf));
    *(VecFx32 *)(node + 6) = *(VecFx32 *)(node + 0xf);
    if (*(unsigned char *)(node[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*node, 0xf, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov278_020d1134);
}
