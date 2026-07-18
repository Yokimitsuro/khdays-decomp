/*
 * func_ov282_020d1b04 -- x3. AI-state entry: set the aim direction, notify, arm and dispatch.
 * target = acquire(*state, 0) -> state[4]. Direction state[0x11..0x13] = normalise(flatten_y(
 * target(+0x190) - state[1])), falling back to the const forward data_02042258 when there is no target
 * or the direction is degenerate. Copy the const pair data_020d46ec to a stack scratch and, if the
 * owner's callback *(state[0]+0x24) is set, invoke it as cb(state[0], &scratch, 4). Fire attack 8
 * (020c9264), set hw60.hi bit 0x40, clear state[0xb] and the *(u8)(state+0x64)/+0x67 flags, then hand
 * off to the 020d1c04 state.
 */
struct vec3 { int x, y, z; };
struct h2 { unsigned short a, b; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *in, void *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern struct vec3 data_02042258;
extern struct h2 data_ov282_020d4700;
extern void func_ov282_020d1c14(void);

void func_ov282_020d1b04(int *self) {
    int *state = (int *)self[1];
    struct h2 scratch;
    int v[3];
    void (*cb)(int, void *, int);
    int target = func_ov107_020cab14(*state, 0);

    state[4] = target;
    if (target == 0) {
        *(struct vec3 *)(state + 0x11) = data_02042258;
    } else {
        VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
        v[1] = 0;
        if (func_01ff8d18(v, (void *)(state + 0x11)) == 0) {
            *(struct vec3 *)(state + 0x11) = data_02042258;
        }
    }
    scratch = data_ov282_020d4700;
    cb = *(void (**)(int, void *, int))(*state + 0x24);
    if (cb != 0) {
        cb(*state, &scratch, 4);
    }
    func_ov107_020c9264(*state, 8, 0);
    {
        unsigned short *hw = (unsigned short *)(*state + 0x60);
        unsigned int h = *hw;
        /* hw60.hi |= 0x40 -- explicit-shift form (bitfield |= adds a redundant mask) */
        *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    state[0xb] = 0;
    *(char *)((int)state + 0x64) = 0;
    *(char *)((int)state + 0x67) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov282_020d1c14);
}
