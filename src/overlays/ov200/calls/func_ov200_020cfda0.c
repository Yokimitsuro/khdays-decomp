/*
 * func_ov200_020cfda0 -- x3. AI-state tick: orient toward the target, then transition on a timer.
 * If the sub-node *(state[0]+0x390) reports ready (020d0574), set state[9]=0x800, fold it into the
 * aim offset state[0xc..0xe] (VEC_Add), and clamp state[4]=0x400 when *(state[0]+0x13c) < 0x6000.
 * Build the look-at (0203cd7c from state[0xc], const data_02042264) -> quaternion state[0x25..0x28]
 * (0202ea48), then reset state[9..0xb] to the const data_02041dc8. Advance state[0x14] +=
 * owner_delta. At 0x2a80: notify callback *(state[0]+0x24)(state[0], &scratch, 4), fire attack 5
 * and hand off to 020cfef4. Otherwise, once past 0x59a6 and the sub-node 020d0540 reports idle,
 * fire attack 5 and hand off; else keep waiting.
 *
 * Parked as a "2-halfword read-order tie": the scratch pair lives at data_020d182c+4 and the ROM
 * reads the HIGH halfword (+6) before +4, where a struct assignment reads +4 first. It is not a tie
 * -- a whole-struct copy is what fixes the order. Assign the two members explicitly, high one
 * first, and the loads come out in the ROM's order.
 * The second half is that the ROM materialises `&scratch` BEFORE the copy (it fills the pool load's
 * use gap with it) while mwcc sinks it past the `cb != 0` branch, where it is first needed. Binding
 * it to a local pointer and copying THROUGH that pointer makes it live from the top of the block.
 */
struct vec3 { int x, y, z; };
struct h2 { unsigned short a, b; };
extern int  func_ov200_020d0574(int obj);
extern void VEC_Add(void *a, void *b, void *c);
extern void func_0203cd7c(void *out, void *a, int b, void *c);
extern void func_0202ea48(void *quat, void *mtx);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern int  func_ov200_020d0540(int obj);
extern int  data_02042264;
extern struct vec3 data_02041dc8;
extern struct h2 data_ov200_020d182c[];
extern void func_ov200_020cfef4(void);

void func_ov200_020cfda0(int *self) {
    int *state = (int *)self[1];
    struct h2 scratch;
    int v[9];
    void (*cb)(int, void *, int);

    {
        int s0 = *state;
        if (func_ov200_020d0574(*(int *)(s0 + 0x390)) != 0) {
            state[0xa] = 0x800;
            VEC_Add((void *)(state + 0xc), (void *)(state + 9), (void *)(state + 0xc));
            if (*(int *)(s0 + 0x13c) < 0x6000) {
                state[4] = 0x400;
            }
        }
    }
    func_0203cd7c(v, (void *)(state + 0xc), state[0x13], &data_02042264);
    func_0202ea48((void *)(state + 0x25), v);
    *(struct vec3 *)(state + 9) = data_02041dc8;
    state[0x14] += *(int *)(*self + 0x2c);
    if (state[0x14] >= 0x2a80) {
        struct h2 *ps = &scratch;
        ps->b = data_ov200_020d182c[1].b;
        ps->a = data_ov200_020d182c[1].a;
        cb = *(void (**)(int, void *, int))(*state + 0x24);
        if (cb != 0) {
            cb(*state, ps, 4);
        }
        func_ov107_020c9264(*state, 5, 0);
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020cfef4);
        return;
    }
    if (state[0x14] < 0x59a6) {
        return;
    }
    if (func_ov200_020d0540(*(int *)(*state + 0x390)) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 5, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020cfef4);
}
