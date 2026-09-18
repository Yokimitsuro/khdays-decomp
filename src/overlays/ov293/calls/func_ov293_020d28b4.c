/* Chase tick of the ov293 enemy. Without a recorded hit actor (+0x3660 record) the actor
 * steers around the +8 point: the horizontal distance to it becomes a Q12 approach factor
 * (2 x inverse over 15.0, clamped), the aim angle away from the point is spread by a random
 * amount that widens as the factor approaches zero, and the +0x10 heading is set either way.
 * With one, the +4 target is that actor when its +4 owner matches, else the closest one; a
 * target sets the heading towards its +0x190 (from the actor's +0xb0) while none requests
 * sub-state 2 at speed 0x2000. The +0x14 turn step is 30 x dt / 10 and the +0x1c movement is
 * the +0xc facing scaled by 0x999. Past the +0x44 duration the state retires with request 2 at
 * speed 0x2000; otherwise a recorded hit actor within 4.0 requests sub-state 6.
 *
 * `+ (nFactor - nFactor)` on the RNG result emits the ROM's `add r0, r0, #0` (func_02023eb4
 * returns long long). FX_Inv is the reloc's own name for 01ff8a04. The record's actor is read
 * again through an `int *` view for the owner comparison (a field re-read is CSE'd). */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct { int nX; int nY; int nZ; } Vec3;

struct Ov293Owner {
    char pad000[4];
    int nOwner04;
};

struct Ov293HitRecord {
    int nKind;
    int pad04;
    struct Ov293Owner *pActor;  /* +0x08 */
};

struct State {
    char *pActor;
    int pTarget04;
    Vec3 *pPoint08;
    int nAngle0c;
    int nAngleTarget10;
    int nAngleStep14;
    int nSpeed18;
    Vec3 vMove1c;
    char pad28[0x18];
    int nElapsed40;
    int nDuration44;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Inv(int num, int den);
extern int func_02023eb4();
extern int func_020050b4(int x, int z);
extern int func_ov107_020cab14(char *actor, int mode);
extern void func_0203c634(struct Node *node, int slot, void *next);
extern void func_01ffa724(int scale, const Vec3 *src, Vec3 *dst);
extern struct Ov293HitRecord data_ov293_020d3660;
extern const short data_0203d210[];

void func_ov293_020d28b4(struct Node *node)
{
    struct State *st;
    Vec3 vToTarget;
    Vec3 vFacing;
    int nFactor;
    int nHalf;
    int nSpread;
    int nDist;

    st = node->pState;
    if (data_ov293_020d3660.pActor == 0) {
        VEC_Subtract((const Vec3 *)(st->pActor + 0x190), st->pPoint08, &vToTarget);
        vToTarget.nY = 0;
        nFactor = func_01ff8d18(&vToTarget, &vToTarget);
        nFactor = FX_Inv(nFactor, 0xf000);
        nFactor = nFactor * 2 - 0x1000;
        if (nFactor < -0x1000) {
            nFactor = -0x1000;
        }
        if (nFactor > 0x1000) {
            nFactor = 0x1000;
        }
        nHalf = 0x1000 - (nFactor < 0 ? -nFactor : nFactor);
        nSpread = nHalf * 2;
        if (nSpread < 0) {
            nSpread = -nSpread;
        }
        nSpread = (int)(((long long)(func_02023eb4(nSpread + 1) +
                                     (nFactor - nFactor) - nHalf) * 0x3244 +
                         0x800) >> 12);
        if (nFactor > 0) {
            st->nAngleTarget10 =
                (func_020050b4(-vToTarget.nX, -vToTarget.nZ) + 0x3244) - nSpread;
        } else {
            st->nAngleTarget10 =
                nSpread + (func_020050b4(vToTarget.nX, vToTarget.nZ) + 0x3244);
        }
    } else {
        if (((struct Ov293Owner *)((int *)&data_ov293_020d3660)[2])->nOwner04 == *(int *)(st->pActor + 4)) {
            st->pTarget04 = (int)data_ov293_020d3660.pActor;
        } else {
            st->pTarget04 = func_ov107_020cab14(st->pActor, 0);
        }
        if (st->pTarget04 != 0) {
            VEC_Subtract((const Vec3 *)(st->pTarget04 + 0x190), (const Vec3 *)(st->pActor + 0xb0), &vToTarget);
            nDist = func_01ff8d18(&vToTarget, &vToTarget);
            st->nAngleTarget10 = func_020050b4(vToTarget.nX, vToTarget.nZ);
        } else {
            st->nSpeed18 = 0x2000;
            *(u8 *)(st->pActor + 0x1c7) = 2;
            func_0203c634(node, node->bSlot, 0);
            return;
        }
    }
    st->nAngleStep14 = (*(int *)((char *)node->pScene + 0x2c) * 0x1e) / 10;
    {
        int nIdx = (u16)(int)(((long long)st->nAngle0c * 0x28be60db9391LL +
                              0x80000000000LL) >> 44) >> 4;
        vFacing.nX = data_0203d210[nIdx * 2];
        vFacing.nY = 0;
        vFacing.nZ = data_0203d210[nIdx * 2 + 1];
        func_01ffa724(0x999, &vFacing, &st->vMove1c);
        st->nElapsed40 += *(int *)((char *)node->pScene + 0x2c);
        if (st->nElapsed40 > st->nDuration44) {
            st->nSpeed18 = 0x2000;
            *(u8 *)(st->pActor + 0x1c7) = 2;
            func_0203c634(node, node->bSlot, 0);
            return;
        }
        if (data_ov293_020d3660.pActor == 0) {
            return;
        }
        if (nDist >= 0x4000) {
            return;
        }
        *(u8 *)(st->pActor + 0x1c7) = 6;
        func_0203c634(node, node->bSlot, 0);
    }
}
