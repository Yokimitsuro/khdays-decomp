/* Throw tick of the ov218 actor: without a target (020cc900) the node ends. +0x14 accumulates the frame
 * rate; at 0.46 sound 0x135/4 plays once at the +8 point. At 0.6 the throw happens once (+0x40 bit 1):
 * the aim is the target's +0x190 point lifted by its radius, seen from the +0x39c hand and turned back
 * by the +0xc heading, and the first unguarded +0x394 partner is thrown at it (020cdff8, 30 % spin).
 * After the throw, once the partner holds no queued move, the second throw (+0x20) re-runs 020cd658;
 * then the next move is 4. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;
struct Ov218Actor { char pad[0x394]; int partners[2]; };

extern int func_ov218_020cc900(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern unsigned int func_02023eb4(int bound);
extern void func_ov218_020cdff8(int partner, void *hand, Vec3 *aim, int spin);
extern void func_ov218_020cd658(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov218_020cd404(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    Vec3 aim;
    int i;

    if (func_ov218_020cc900(node) < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[5] += *(int *)(node[0] + 0x2c);
    if (!(*((unsigned char *)state + 0x40) & 1) && state[5] >= 0x770) {
        func_ov107_020c5af8(*state, 0x135, 4, (void *)state[2]);
        *((unsigned char *)state + 0x40) |= 1;
    }
    if (!(*((unsigned char *)state + 0x40) & 2)) {
        if (state[5] < 0x990) {
            return;
        }
        if (*(int *)(*state + 0x390) == 0) {
            return;
        }
        aim = *(Vec3 *)(*(int *)(*state + 0x390) + 0x190);
        aim.y += *(int *)(*(int *)(*state + 0x390) + 0x80);
        VEC_Subtract(&aim, (Vec3 *)(*state + 0x39c), &aim);
        func_01ff8d18(&aim, &aim);
        {
            int turn = state[3] - func_020050b4(aim.x, aim.z);
            int idx = ANG2IDX(turn) * 2;

            MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
        }
        MTX_MultVec33(&aim, &rot, &aim);
        for (i = 0; i < 2; i++) {
            int partner = ((struct Ov218Actor *)*state)->partners[i];

            if ((((flags16 *)(partner + 0x60))->lo & 1) == 0) {
                func_ov218_020cdff8(partner, (void *)(*state + 0x39c), &aim, func_02023eb4(0x64) < 0x1e);
                break;
            }
        }
        *((unsigned char *)state + 0x40) |= 2;
        return;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (++state[8] < 2) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020cd658);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
