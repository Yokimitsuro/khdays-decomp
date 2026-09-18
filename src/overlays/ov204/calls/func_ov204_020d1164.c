/* func_ov204_020d1164: ported from a matched sibling family (same shape, constants and offsets adjusted). */
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int y);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov204_020d11fc(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov204_020d1164(int *node) {
    int *state = (int *)node[1];
    int local[3];
    func_ov107_020c9264(*state, 5, 0);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    if (state[0x10] != 0) {
        VEC_Subtract((void *)(state[0x10] + 400), (void *)state[8], local);
        int r = func_020050b4(local[0], local[2]);
        state[0xe] = r;
        state[0xd] = r;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov204_020d11fc);
}
