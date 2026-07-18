/*
 * func_ov200_020d0008 -- x3. AI-state tick: orient toward the target, then transition on a timer or
 * once the sub-nodes free up. If *(state[0]+0x13c) < 0x4000, clamp state[4] = 0x200. Set state[0x18] =
 * 0x8f. Build the aim vector state[0xc]/[0xe] from *(state[2]+0x74)/+0x7c, feed it to the look-at
 * (0203cd7c with state[0x13] and const data_02042264) and store the orientation quaternion at
 * state[0x25..0x28] (0202ea48). Advance state[0x14] += owner_delta. If it reaches 0x3fc0: copy the
 * const pair at data_020d182c+0x10 to a scratch, notify the owner callback *(state[0]+0x24) as
 * cb(state[0], &scratch, 4), and hand off to 020d013c. Otherwise count the sub-nodes state[0]+0x390+i*4
 * (i=1,2) that report idle via 020d0540; if none are idle, or the timer is still under 0x800, keep
 * waiting; else hand off to 020d013c.
 *
 * NON-MATCHING: 4-byte read-order tie in the 2-halfword scratch copy (size-exact 308B, result and all
 * other codegen -- the look-at, quaternion, timer, node-count loop and callback -- byte-exact). The
 * const pair lives at data_020d182c+0x10; the ROM reads the HIGH halfword (+0x12) first then +0x10 and
 * stores each to the right slot, while mwcc (for the member/offset copy) reads +0x10 first. Both give
 * sp[0]=data[+0x10], sp[2]=data[+0x12] -- identical result, swapped load order. Tried: struct-member
 * copy, offset-cast copy, pointer-to-member copy, explicit reverse-order field copy; none read the high
 * halfword first (a base-symbol h2 copy does -- cf. func_ov210_020d1af4 -- but here it is at +0x10).
 */
struct h2 { unsigned short a, b; };
struct h2blk { char pad[0x10]; struct h2 hh; };
extern void func_0203cd7c(void *out, void *a, int b, void *c);
extern void func_0202ea48(void *quat, void *mtx);
extern void func_0203c634(int self, int idx, int cb);
extern int  func_ov200_020d0540(int obj);
extern int  data_02042264;
extern struct h2blk data_ov200_020d182c;
extern void func_ov200_020d013c(void);

void func_ov200_020d0008(int *self) {
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
        scratch = data_ov200_020d182c.hh;
        cb = *(void (**)(int, void *, int))(*state + 0x24);
        if (cb != 0) {
            cb(*state, &scratch, 4);
        }
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020d013c);
        return;
    }
    count = 0;
    for (i = 1; i < 3; i++) {
        if (func_ov200_020d0540(((int *)*state)[i + 0xe4]) == 0) {
            count++;
        }
    }
    if (count <= 0) {
        return;
    }
    if (state[0x14] < 0x800) {
        return;
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020d013c);
}
