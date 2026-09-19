/* Lunge tick: rebuilds the +0x18 step from the actor's +0xa0 pose transformed by the +0x3ac
 * sub-object's steer vector (scaled by its factor); once the +4 child's +0xad byte clears, pose
 * 4 (or 2 when bit 0 of +0x52 is clear) is requested and the node dispatches null. */
struct Bits52 { unsigned char b0 : 1; };
extern int  func_ov107_020c9f48(int obj, void *out);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203c634(int self, int idx, int cb);

void func_ov236_020d17b8(int *self) {
    int *state = (int *)self[1];
    int w[3];
    int factor;

    factor = func_ov107_020c9f48(*(int *)(*state + 0x3ac), w);
    func_0202f384((void *)(state + 6), (void *)(*state + 0xa0), w);
    func_01ffa724(factor, (void *)(state + 6), (void *)(state + 6));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (((struct Bits52 *)((char *)state + 0x52))->b0 != 0) {
        *(char *)(*state + 0x1c7) = 4;
    } else {
        *(char *)(*state + 0x1c7) = 2;
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
