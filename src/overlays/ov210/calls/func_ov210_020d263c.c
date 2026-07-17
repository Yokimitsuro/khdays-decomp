/*
 * func_ov210_020d263c -- x3 (ov210/211/282). AI-state tick: rebuild the steer vector; once the
 * sub-node at state[3] goes idle, fire and transition.
 * factor = 020c9f48(*(*state+0x3b8),&w); build state[5..7] from *state+0xa0 (0202f384), scale by
 * factor (01ffa724). While *(u8)state[3] set, return; once idle fire attack 0xc (flag 1), clear
 * state[0xb], kick the child (020c9ee8(*(*state+0x3b8),1,1)) and hand off to the 020d26e0 state.
 */
extern int  func_ov107_020c9f48(int obj, void *out);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int obj, int a, int b);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov210_020d26e0(void);

void func_ov210_020d263c(int *self) {
    int *state = (int *)self[1];
    int w[3];
    int factor;

    factor = func_ov107_020c9f48(*(int *)(*state + 0x3b8), w);
    func_0202f384((void *)(state + 5), (void *)(*state + 0xa0), w);
    func_01ffa724(factor, (void *)(state + 5), (void *)(state + 5));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xc, 1);
    state[0xb] = 0;
    func_ov107_020c9ee8(*(int *)(*state + 0x3b8), 1, 1);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov210_020d26e0);
}
