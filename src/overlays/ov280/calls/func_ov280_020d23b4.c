/* Lunge tick of the ov280 enemy (variant of ov231/ov232's). The +0x30
 * velocity is the +0x388 part's +0x2c vector turned by the heading, halved. The +0x28 timer
 * accumulates the owner's rate; past 0xff0 reaction +0x50 mode 9 fires once (+0x4c) at the +8
 * point. Between 0x1298 and 0x2b90 the target is re-acquired (func_ov280_020d0628) and a probe
 * segment from the +0xc point lifted 5.13 along data_02042240 (length 2.0, radius 4.81) hits kind 2
 * candidates towards the heading lifted 2.0 (func_ov280_020d0890); on a hit reaction 0/0x51 fires at
 * the owner's +0x74 point. Past 0xff0 a pending +0x54 flag spawns effect 4 at the origin once. When
 * the +0x10 idle byte clears, sub-state 2 is requested and the tick ends. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

extern void func_ov280_020d06bc(void *out, int *self, Vec3 *vec);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov280_020d0628(int *node);
extern int func_ov280_020d0890(int *self, int kind, void *query, void *pt, int flags);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02042240;
extern const Vec3 data_02041dc8;

void func_ov280_020d23b4(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Segment seg;
    Vec3 v;

    func_ov280_020d06bc(&v, node, (Vec3 *)(*(int *)(*state + 0x388) + 0x2c));
    *(Vec3 *)(state + 0xc) = v;
    func_01ffa724(0x800, (Vec3 *)(state + 0xc), (Vec3 *)(state + 0xc));
    state[0xa] += *(int *)(*node + 0x2c);
    if (state[0xa] >= 0xff0 && *((unsigned char *)state + 0x4c) != 0) {
        *((unsigned char *)state + 0x4c) = 0;
        func_ov107_020c5af8(*state, *(short *)((char *)state + 0x50), 9, (void *)state[2]);
    }
    if (state[0xa] >= 0x1298 && state[0xa] < 0x2b90) {
        func_ov280_020d0628(node);
        dir.x = data_0203d210[ANG2IDX(state[6]) * 2];
        dir.y = 0x2000;
        dir.z = data_0203d210[ANG2IDX(state[6]) * 2 + 1];
        seg.p0 = *(Vec3 *)state[3];
        seg.p0.y += 0x5210;
        seg.dir = data_02042240;
        seg.nLength = 0x2000;
        seg.nRadius = 0x4cef;
        if (func_ov280_020d0890(node, 0, &seg, &dir, 2) != 0) {
            func_ov107_020c5af8(*state, 0, 0x51, (void *)(*state + 0x74));
        }
    }
    if (state[0xa] >= 0xff0 && state[0x15] != 0) {
        func_ov107_020c0b90(*state, 4, data_02041dc8, 0);
        state[0x15] = 0;
    }
    if (*(unsigned char *)state[4] != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
