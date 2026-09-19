/* Recover tick of the ov125 enemy: the +0x2c timer accumulates the owner's +0x2c rate; once it
 * passes 0x2000 (once, latched in bit 1 of +0x34) the data_ov126_020d400c[2..3] message pair is
 * sent to the +0x24 hook (arg 4) and the +0x3c counter cleared. The +0xc speed drops to 0x200
 * while the +0x13c height is under 0x4000 and the look-at at +0x68 is rebuilt from the +4
 * target's +0x74 pose, the +0x24 anchor and data_02042264. Past 0x5000 the [0..1] pair is sent,
 * action 5/0 fired and the next state registered; between 0x800 and that, the same happens as
 * soon as the +0x390 aim node reports idle. */
struct b2 { unsigned char b0 : 1, b1 : 1; };

extern void func_0203cd7c(void *out, void *a, int b, void *c);
extern void func_0202ea48(void *a, void *b);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, void *cb);
extern int func_ov126_020d21d4(int node);
extern unsigned short data_ov126_020d400c[];
extern int data_02042264;
extern void func_ov126_020d1bb8(void);

void func_ov126_020d1a44(int *self) {
    int owner = *(int *)self[1];
    int *state = (int *)self[1];
    unsigned short pairA[2];
    unsigned short pairB[2];
    int buf[9];
    unsigned short *pp;
    void (*cb)();

    state[0xb] += *(int *)(self[0] + 0x2c);
    if (((struct b2 *)(state + 0xd))->b1 == 0 && state[0xb] >= 0x2000) {
        pp = pairA;
        pp[1] = data_ov126_020d400c[3];
        pp[0] = data_ov126_020d400c[2];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        state[0xf] = 0;
        *(unsigned char *)(state + 0xd) |= 2;
    }
    if (*(int *)(owner + 0x13c) < 0x4000) {
        state[3] = 0x200;
    }
    func_0203cd7c(buf, (void *)(state[1] + 0x74), state[9], &data_02042264);
    func_0202ea48(state + 0x1a, buf);
    if (state[0xb] >= 0x5000) {
        pp = pairB;
        pp[1] = data_ov126_020d400c[1];
        pp[0] = data_ov126_020d400c[0];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        func_ov107_020c9264(*state, 5, 0);
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), func_ov126_020d1bb8);
        return;
    }
    if (state[0xb] < 0x800) {
        return;
    }
    if (func_ov126_020d21d4(*(int *)(*state + 0x390)) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 5, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), func_ov126_020d1bb8);
}
