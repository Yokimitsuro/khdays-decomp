/* Dash tick: the +0x14 rate is 30 x frame step / 50, the +0x28 timer counts the frame step
 * down, and the +0x18 step is rebuilt from the actor's +0xa0 pose transformed by the +0x3ac
 * sub-object's steer vector (scaled by its factor). Once the +4 child's +0xad byte clears, pose
 * 0x14 plays (looping), the sub-object plays 7 and the node moves to 020d159c. */
extern int  func_ov107_020c9f48(int obj, void *out);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int sub, int a, int b);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov278_020d1550(void);

void func_ov278_020d1478(int *self) {
    int *state = (int *)self[1];
    int w[3];
    int factor;

    state[5] = *(int *)(self[0] + 0x2c) * 30 / 50;
    state[0xa] -= *(int *)(self[0] + 0x2c);
    factor = func_ov107_020c9f48(*(int *)(*state + 0x3ac), w);
    func_0202f384((void *)(state + 6), (void *)(*state + 0xa0), w);
    func_01ffa724(factor, (void *)(state + 6), (void *)(state + 6));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x14, 1);
    func_ov107_020c9ee8(*(int *)(*state + 0x3ac), 7, 1);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov278_020d1550);
}
