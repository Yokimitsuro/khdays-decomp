/* func_ov221_020d2574 -- the strafe tick: re-acquire the target, then either correct the distance
 * or settle on a facing.
 *
 * func_ov221_020d132c hands back the range and fills a direction vector; negative means give up,
 * and func_ov221_020d0d20 gets a veto too. Both bail through a plain c634 re-entry.
 *
 * With bit 1 of the flags byte at ctx[0]+0x17a clear, the range drives a correction along that
 * direction, folded onto the position at ctx+0x38:
 *   beyond 0xf000 -> push out by (range - 0x5000)
 *   inside 0x3800 -> pull in by -(range + 0x5000)
 * Either one hands off to func_ov221_020d27bc. In the band between, or with the flag set, it
 * falls through to the facing instead.
 *
 * The facing is `ctx[0x16] + 0x1922`, i.e. the stored angle plus a QUARTER TURN -- 0x1922 in Q12
 * radians is pi/2. It is then compared against the current heading (+0x50) by dotting the two
 * unit vectors out of data_0203d210: sinA*sinB + cosA*cosB is the cosine of the angle between
 * them, so a negative result means they point more than 90 degrees apart and the facing is
 * flipped by 0x3244 -- pi in Q12. (mwcc splits both constants; neither is an encodable
 * immediate.)
 *
 * See codegen-cracks.md for the Q12-radians -> sin/cos-table conversion, which runs twice here. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
} Flags17a;

extern int func_ov107_020cab14(int owner, int a);
extern int func_ov221_020d132c(int self, VecFx32 *dir);
extern void func_0203c634(int self, int action, void *cb);
extern int func_ov221_020d0d20(int self, int range);
extern void func_ov221_020d27bc(void);
extern void func_ov221_020d2384(int self, int angle);
extern short data_0203d210[];

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov221_020d2574(int self) {
    int *ctx;
    VecFx32 dir;
    int range;
    int facing;
    int idxA;
    int idxB;

    ctx = *(int **)(self + 4);
    *(int *)(ctx[0] + 0x3e8) = func_ov107_020cab14(ctx[0], 0);

    range = func_ov221_020d132c(self, &dir);
    if (range < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (func_ov221_020d0d20(self, range) != 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    *(VecFx32 *)((char *)ctx + 0x38) = *(VecFx32 *)ctx[2];

    if (((Flags17a *)(ctx[0] + 0x17a))->b1 == 0) {
        if (range > 0xf000) {
            *(int *)((char *)ctx + 0x38) += dir.x * (range - 0x5000) / 0x1000;
            ctx[0x10] += dir.z * (range - 0x5000) / 0x1000;
            func_0203c634(self, *(signed char *)(self + 0x20), func_ov221_020d27bc);
            return;
        }
        if (range < 0x3800) {
            *(int *)((char *)ctx + 0x38) += -dir.x * (range + 0x5000) / 0x1000;
            ctx[0x10] += -dir.z * (range + 0x5000) / 0x1000;
            func_0203c634(self, *(signed char *)(self + 0x20), func_ov221_020d27bc);
            return;
        }
    }

    facing = ctx[0x16] + 0x1922;
    idxA = (unsigned short)(((long long)ctx[0x14] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
           >> 4;
    idxB = (unsigned short)(((long long)facing * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;

    if (FX_Mul(data_0203d210[idxB * 2], data_0203d210[idxA * 2])
            + FX_Mul(data_0203d210[idxB * 2 + 1], data_0203d210[idxA * 2 + 1])
        < 0) {
        facing -= 0x3244;
    }
    func_ov221_020d2384(self, facing);
}
