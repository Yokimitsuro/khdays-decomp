/* Attack hit test of the ov238 actor: with a target (020d0878) the targets touching `sphere` (or else
 * `box`) are pushed (020ca918 with `push`, kind `kind`); unless `once` has already marked them in the
 * +0x2f mask. Each hit spawns effect `effect` 1.0 above the victim, offset for kind 0 by the push
 * turned by the +0x18 heading (a 0x180-deep push reaching 0.5 further). Returns whether anything was
 * hit (with `once`: whether the mask holds any hit). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern int func_ov238_020d0878(int *node);
extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern int func_ov107_020c8df0(int owner, void *box, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

int func_ov238_020d0910(int *node, void *sphere, void *box, Vec3 *push, int once, u16 effect, u16 kind)
{
    int *state = (int *)node[1];
    int hits[4];
    Mtx33 rot;
    Vec3 pos;
    Vec3 p;
    long n;
    long i;
    u8 bit;

    if (func_ov238_020d0878(node) != -1) {
        if (sphere != 0) {
            n = func_ov107_020c8eb8(*state, sphere, hits);
        } else {
            n = func_ov107_020c8df0(*state, box, hits);
        }
        for (i = 0; i < n; i++) {
            bit = 1 << *(u16 *)(hits[i] + 2);
            if (once != 0 && (*((u8 *)state + 0x2f) & bit)) {
                continue;
            }
            if (func_ov107_020ca918(hits[i], *state, *state, kind, push, 0) == 0) {
                continue;
            }
            pos = *(Vec3 *)(hits[i] + 0x190);
            if (kind == 0) {
                p = *push;
                if (push->z == 0x180) {
                    p.z += 0x800;
                }
                {
                    int idx = ANG2IDX(state[6]) * 2;

                    MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
                }
                MTX_MultVec33(&p, &rot, &p);
            }
            VEC_Add(&pos, &p, &pos);
            if (once != 0) {
                *((u8 *)state + 0x2f) |= bit;
            }
            pos.y += 0x1000;
            func_ov107_020c0b90(*state, effect, pos, 0);
        }
        if (once != 0) {
            if (*((u8 *)state + 0x2f) != 0) {
                return 1;
            }
        } else if (n != 0) {
            return 1;
        }
    }
    return 0;
}
