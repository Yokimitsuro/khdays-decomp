/*
 * NONMATCHING -- 164/164 size-exact, diff @0x14: two scheduling choices in the head. The ROM loads
 * `state = self[1]` AFTER both config halfwords and computes `&pt` (r1=sp+0) EARLY (before the strh
 * pair), holding it for the blx; mwcc loads state between the halfwords and defers `&pt` into the
 * `if (fp)` block. Everything below the blx (attack, the 0203cd7c/0202ea48 aim build, the handoff) is
 * byte-exact. A scheduling residue on the pt-pointer hoist -- attack only that.
 *
 * func_ov200_020cfcfc -- x3 (ov200/201/271). AI-state enter: notify the owner, fire, and set the
 * aim pose.
 * Copy the two config halfwords (data_ov200_020d182c +8/+0xa) into a scratch point and, if the owner
 * has a callback at *state+0x24, invoke it (fp(*state, &pt, 4)). Fire attack 4 (flag 1), clear the
 * timer state[0x14]. Refresh the owner (020ce8f0), build the aim matrix from state[0xc]/state[0x13]
 * and data_02042264 (0203cd7c) and apply it to state[0x25..] (0202ea48). Hand off to 020cfda0.
 */
struct pt { unsigned short a, b; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov200_020ce8f0(int self);
extern void func_0203cd7c(void *out, void *a, int b, void *c);
extern void func_0202ea48(void *a, void *b);
extern void func_0203c634(int self, int idx, int cb);
extern unsigned short data_ov200_020d182c[];
extern int data_02042264;
extern void func_ov200_020cfda0(void);

void func_ov200_020cfcfc(int *self) {
    int *state = (int *)self[1];
    struct pt pt;
    int buf[9];
    void (*fp)(int, void *, int);

    pt.a = data_ov200_020d182c[4];
    pt.b = data_ov200_020d182c[5];
    fp = *(void (**)(int, void *, int))(*state + 0x24);
    if (fp != 0) {
        fp(*state, &pt, 4);
    }
    func_ov107_020c9264(*state, 4, 1);
    state[0x14] = 0;
    func_ov200_020ce8f0((int)self);
    func_0203cd7c(&buf, (void *)(state + 0xc), state[0x13], &data_02042264);
    func_0202ea48((void *)(state + 0x25), &buf);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020cfda0);
}
