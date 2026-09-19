/* Aimed attack wait tick of the ov246 enemy: the +0x18 direction takes the owner's +0xa0 basis
 * turned by the +0x39c aim (9f48) and scaled by its reach. The +0x3c timer accumulates the
 * owner's rate: in phase 0 (+0x54) past 0x22aa the data_ov246_020d30e0[8..9] message pair goes
 * to the +0x24 hook (arg 4), phase 1 begins and reaction 0x158 mode 6 fires at the +0x398
 * bone's +0x14; in phase 1 past 0x23bb the +0x3a0 emitter is launched (func_ov246_020d1adc)
 * from that bone along the sine/cosine of the +0xc heading and phase 2 begins. Once the +4
 * item is idle (+0xad) the +0x44 delay is re-armed to a random value in [+0x224, +0x228],
 * sub-state 2 is queued and the state ends. */
typedef struct { int x, y, z; } Vec3;

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

extern int func_ov107_020c9f48(int aim, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *basis, const Vec3 *v);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov246_020d1adc(int emitter, void *at, Vec3 *dir);
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern unsigned short data_ov246_020d30e0[];
extern short data_0203d210[];

void func_ov246_020d178c(int *node)
{
    int *state = (int *)node[1];
    Vec3 aim;
    Vec3 dir;
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    unsigned short idx;
    int reach;
    int lo;
    int diff;

    reach = func_ov107_020c9f48(*(int *)(*state + 0x39c), &aim);
    func_0202f384((Vec3 *)(state + 6), (char *)*state + 0xa0, &aim);
    func_01ffa724(reach, (Vec3 *)(state + 6), (Vec3 *)(state + 6));
    state[0xf] += *(int *)(node[0] + 0x2c);
    if (*(unsigned char *)((char *)state + 0x54) == 0 && state[0xf] > 0x22aa) {
        pp = pair;
        pp[1] = data_ov246_020d30e0[9];
        pp[0] = data_ov246_020d30e0[8];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        *(unsigned char *)((char *)state + 0x54) = 1;
        func_ov107_020c5af8(*state, 0x158, 6, (void *)(*(int *)(*state + 0x398) + 0x14));
    } else if (*(unsigned char *)((char *)state + 0x54) == 1 && state[0xf] > 0x23bb) {
        idx = FX_RadToIdx(state[3]);
        dir.x = data_0203d210[(idx >> 4) * 2];
        dir.y = 0;
        dir.z = data_0203d210[(idx >> 4) * 2 + 1];
        func_ov246_020d1adc(*(int *)(*state + 0x3a0), (void *)(*(int *)(*state + 0x398) + 0x14), &dir);
        *(unsigned char *)((char *)state + 0x54) = 2;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    diff = *(int *)(*state + 0x228) - lo;
    if (diff < 0) {
        diff = -diff;
    }
    state[0x11] = lo + func_02023eb4(diff + 1);
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
