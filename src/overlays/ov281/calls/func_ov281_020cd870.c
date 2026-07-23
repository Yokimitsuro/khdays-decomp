/* Wind up the charge: once the accumulator passes 0x555 the launch effect fires exactly once
 * (guarded by the byte at +0x3c) and the aim is re-issued every frame at strength 0x800. When
 * the range query comes back empty, or the sub-object reports it is done, the action byte goes
 * to 2 and the think callback is dropped.
 *
 * Matched byte-exact 2026-07-23, first compile. One of four byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern void func_ov107_020c0b90(int obj, int a, VecFx32 v, int d);
extern void func_ov281_020ccae4(int *state, int a, int b, int p, int q);
extern int func_ov107_020cab14(int obj, int a);
extern void func_0203c634(void *node, int idx, void *cb);
extern VecFx32 data_02041dc8;

void func_ov281_020cd870(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];

    state[6] = state[6] + *(int *)((int)owner + 0x2c);
    if (*(unsigned char *)((int)state + 0x3c) == 0 && state[6] >= 0x555) {
        func_ov107_020c0b90(state[0], 1, data_02041dc8, 0);
        *(unsigned char *)((int)state + 0x3c) = 1;
    }
    if (state[6] >= 0x555) {
        func_ov281_020ccae4(state, 0, 0, *(int *)(state[0] + 0x3ac) + 0x14, 0x800);
    }
    state[2] = func_ov107_020cab14(state[0], 0);
    if (state[2] == 0) {
        *(char *)(state[0] + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(char *)(state[0] + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
