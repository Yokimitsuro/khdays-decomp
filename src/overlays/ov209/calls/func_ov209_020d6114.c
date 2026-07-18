/*
 * func_ov209_020d6114 -- x3. AI-state tick: wait a timer, flag, fire and push a fixed motion twice.
 * state[0x10] += owner_delta; while under 0x198 return. Once past: hw60.hi &= ~0x80 then hw60.hi |= 1;
 * set bit0 of the low byte of the word at *(state[0]+0x388)+8; fire attack 0 (020c9264). Push the const
 * vector data_02041dc8 through 020c0b90 twice (mode 0 then mode 1, flag 0). Clear state[0x10] = 0 and
 * hand off to the 020d442c state.
 */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int obj, int mode, struct vec3 v, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern struct vec3 data_02041dc8;
extern void func_ov209_020d624c(void);

void func_ov209_020d6114(int *self) {
    int *state = (int *)self[1];
    unsigned short *hw;
    unsigned int h;
    struct vec3 v;

    state[0x10] += *(int *)(*self + 0x2c);
    if (state[0x10] < 0x198) {
        return;
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 1 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    func_ov107_020c9264(*state, 0, 0);
    v = data_02041dc8;
    func_ov107_020c0b90(*state, 0, v, 0);
    func_ov107_020c0b90(*state, 1, v, 0);
    state[0x10] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov209_020d624c);
}
