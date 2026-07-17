/*
 * func_ov210_020d2918 -- x3 (ov210/211/282). AI-state tick: rebuild the steer vector, and once the
 * sub-node at state[3] goes idle, transition.
 * factor = 020c9f48(*(*state+0x3b8), &w); build state[5..7] from *state+0xa0 (0202f384) and scale it
 * by factor (01ffa724). While the sub-node byte *(u8)state[3] is still set, return; once idle mark
 * *(*state+0x1c7)=0xf and hand off via 0203c634 (cb=0).
 */
extern int  func_ov107_020c9f48(int obj, void *out);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203c634(int self, int idx, int cb);

void func_ov210_020d2918(int *self) {
    int *state = (int *)self[1];
    int w[3];
    int factor;

    factor = func_ov107_020c9f48(*(int *)(*state + 0x3b8), w);
    func_0202f384((void *)(state + 5), (void *)(*state + 0xa0), w);
    func_01ffa724(factor, (void *)(state + 5), (void *)(state + 5));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    *(char *)(*state + 0x1c7) = 0xf;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
