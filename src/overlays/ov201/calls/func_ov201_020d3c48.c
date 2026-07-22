/*
 * func_ov201_020d3c48 -- x3. AI-state tick: clamp, aim, and transition on a timer.
 * Clamp state[4]=0x200 while *(state[0]+0x13c) is under 0x4000, stamp state[0x18]=0x8f, take the
 * aim offset from the target (+0x74/+0x7c), build the look-at (0203cd7c, const data_02042264) and
 * convert it to the orientation quaternion (0202ea48). Advance state[0x14] += owner_delta; at
 * 0x3fc0 copy the const pair at data_020d182c+0x10 into a scratch, notify the owner callback
 * *(state[0]+0x24) as cb(state[0], &scratch, 4), and hand off to 020d013c. Otherwise count the
 * ready sub-nodes and keep waiting.
 *
 * Parked as a "4-byte read-order tie" in the 2-halfword scratch copy. Three separate source
 * choices decide those four bytes, and none of them is a compiler tie:
 *  - assign the two MEMBERS explicitly, high halfword first: a whole-struct copy always reads the
 *    low one first;
 *  - copy THROUGH a local pointer to the scratch, so `&scratch` is live from the top of the block;
 *    written as `&scratch` at the call it sinks below the `cb != 0` branch, where the ROM has it
 *    already materialised in the pool load's use gap;
 *  - reach the source as an ARRAY ELEMENT of the global, not as a member of a struct that starts
 *    at the global. A pointer to the member folds +0x10 into the literal pool (the reloc gets an
 *    addend and the ldrh offsets become 0/2); indexing keeps the ROM's `[r0,#0x10]` / `[r0,#0x12]`.
 * Its sibling func_ov200_020cfda0 needed the same three.
 */
struct h2 { unsigned short a, b; };
extern void func_0203cd7c(void *out, void *a, int b, void *c);
extern void func_0202ea48(void *quat, void *mtx);
extern void func_0203c634(int self, int idx, int cb);
extern int  func_ov201_020d4180(int obj);
extern int  data_02042264;
extern struct h2 data_ov201_020d546c[];
extern void func_ov201_020d3d7c(void);

void func_ov201_020d3c48(int *self) {
    int *state = (int *)self[1];
    struct h2 scratch;
    int v[9];
    void (*cb)(int, void *, int);
    int i, count;

    if (*(int *)(*state + 0x13c) < 0x4000) {
        state[4] = 0x200;
    }
    state[0x18] = 0x8f;
    state[0xc] = *(int *)(state[2] + 0x74);
    state[0xe] = *(int *)(state[2] + 0x7c);
    func_0203cd7c(v, (void *)(state + 0xc), state[0x13], &data_02042264);
    func_0202ea48((void *)(state + 0x25), v);
    state[0x14] += *(int *)(*self + 0x2c);
    if (state[0x14] >= 0x3fc0) {
        struct h2 *ps = &scratch;
        ps->b = data_ov201_020d546c[4].b;
        ps->a = data_ov201_020d546c[4].a;
        cb = *(void (**)(int, void *, int))(*state + 0x24);
        if (cb != 0) {
            cb(*state, ps, 4);
        }
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov201_020d3d7c);
        return;
    }
    count = 0;
    for (i = 1; i < 3; i++) {
        if (func_ov201_020d4180(((int *)*state)[i + 0xe4]) == 0) {
            count++;
        }
    }
    if (count <= 0) {
        return;
    }
    if (state[0x14] < 0x800) {
        return;
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov201_020d3d7c);
}
