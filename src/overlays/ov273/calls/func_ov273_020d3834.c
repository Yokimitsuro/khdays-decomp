/* Retreat tick: decays the +0x5c speed by a fifth, rebuilds the forward unit vector from the
 * +0x38 rotation (transforming data_02042258), scales it by that speed into the +0xc velocity
 * and, unless the +8 flag byte is set, writes pose kind 5 into the actor's +0x1c7 and
 * dispatches with a null handler. */
struct Vec3 { int x, y, z; };
extern struct Vec3 data_02042258;
extern void func_0202f384(struct Vec3 *dst, void *xfm, struct Vec3 *src);
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *unit);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov273_020d3834(int *node) {
    int *state = (int *)node[1];
    struct Vec3 dir;
    state[0x17] = state[0x17] + -state[0x17] / 5;
    func_0202f384(&dir, state + 0xe, &data_02042258);
    func_01ff8d18(&dir, &dir);
    func_01ffa724(state[0x17], &dir, state + 3);
    if (*(unsigned char *)state[2] != 0) return;
    *(signed char *)(*state + 0x1c7) = 5;
    func_0203c634(node, *(signed char *)(node + 8), (void *)0);
}
