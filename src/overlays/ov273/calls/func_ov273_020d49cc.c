/* Sweep pass tick: slerps the +0x20 pose towards the +0x30 target by 30/40 of the frame step and
 * copies it to +0x40; the +0xc velocity is the pose forward (data_02042258) scaled by the +0x1c
 * speed. The +0x7c timer runs; once the forward turns away from the +0x70 mark (or the timer
 * passes 5.0) the +0x18 travel accumulates the speed, and past 6.0 the velocity is kept at
 * +0x64, the travel resets and the +0x80 pass counter advances: the fifth pass raises bit 2 of
 * the actor's +0x394 and flags 0x1c in its +0x60 high byte and moves the node to 020d10b0,
 * any other clears the +0x84 byte and moves to 020d0f14. Otherwise the common 020d1364 step
 * runs. */
struct v3 { int x, y, z; };
struct m4 { int w[4]; };
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0202f384(void *out, void *rotation, void *in);
extern void func_01ffa724(int s, void *v, void *d);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern int  VEC_DotProduct(void *a, void *b);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov273_020d4fa4(int *state);
extern struct v3 data_02042258;
extern void func_ov273_020d4cf0(void);
extern void func_ov273_020d4b54(void);

void func_ov273_020d49cc(int *self) {
    int *state = (int *)self[1];
    struct v3 dir;
    struct v3 fwd;

    func_0202f55c(state + 8, *(int *)(self[0] + 0x2c) * 30 / 40, state + 8, state + 0xc);
    *(struct m4 *)(state + 0x10) = *(struct m4 *)(state + 8);
    func_0202f384(&fwd, state + 8, &data_02042258);
    func_01ffa724(state[7], &fwd, state + 3);
    VEC_Subtract(state + 0x1c, (void *)state[1], &dir);
    func_01ff8d18(&dir, &dir);
    state[0x1f] += *(int *)(self[0] + 0x2c);
    if (VEC_DotProduct(&fwd, &dir) < 0 || state[0x1f] > 0x5000) {
        state[6] += state[7];
        if (state[6] > 0x6000) {
            *(struct v3 *)(state + 0x19) = *(struct v3 *)(state + 3);
            state[6] = 0;
            state[0x20]++;
            if (state[0x20] == 5) {
                *(int *)(*state + 0x394) |= 4;
                {
                    unsigned short *p = (unsigned short *)(*state + 0x60);
                    unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
                    hi |= 0x1c;
                    *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
                }
                func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d4cf0);
                return;
            }
            *((unsigned char *)state + 0x84) = 0;
            func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d4b54);
            return;
        }
    }
    func_ov273_020d4fa4(state);
}
