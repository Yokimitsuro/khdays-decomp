/* Sweep tick of an ov254 helper's attack: the +0xc timer accumulates the frame rate and pose 1
 * loops once the +4 item's +0xad byte clears. Until armed (+0x20, set at 0x1980) nothing else
 * happens. Armed, the +0x388 shape's box (lowered to a half-height of 8.0) is swept through the
 * +0x390 owner's hit list (020c8df0); each hit part k (< 4) whose +0x10 cooldown ran out is pushed
 * away from the helper (flattened, 3.0 across, 1.0 up, +x when on top) through 020ca918 and, if
 * that lands, knocks the owner back at the part (mode 0), restarts the cooldown (0x198) and flags
 * the owner's +0x4e0 hit. The other cooldowns run down. With a hit, reaction 0x16d/0xc (strong,
 * +0xa8 of the item) or 0/0x50 fires at the box. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis[3]; int ext[3]; } Box;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c8df0(int owner, Box *box, int *hits);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const Vec3 data_02042258;

void func_ov254_020d26e4(int *node)
{
    int *state = (int *)node[1];
    Box box;
    int hits[4];
    Vec3 d;
    Vec3 fallback;
    int nHits;
    long i;
    unsigned int k;
    u8 bit;
    u8 hitMask = 0;

    state[3] += *(int *)(node[0] + 0x2c);
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 1, 1);
    }
    if (*((u8 *)state + 0x20) == 0) {
        if (state[3] >= 0x1980) {
            *((u8 *)state + 0x20) = 1;
        }
        return;
    }
    box = *(Box *)(**(int **)(*state + 0x388) + 0x94);
    box.pos.y += box.ext[1] - 0x8000;
    box.ext[1] = 0x8000;
    nHits = func_ov107_020c8df0(*(int *)(*state + 0x390), &box, hits);
    i = 0;
    if (nHits > 0) {
        fallback = data_02042258;
        do {
            k = *(u16 *)(hits[i] + 2);
            bit = 1 << k;
            if (k < 4 && state[4 + k] <= 0) {
                VEC_Subtract((Vec3 *)(hits[i] + 0x74), (Vec3 *)(*state + 0x74), &d);
                d.y = 0;
                if (func_01ff8d18(&d, &d) == 0) {
                    d = fallback;
                }
                func_01ffa724(0x3000, &d, &d);
                d.y = 0x1000;
                if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x390), 4, &d, 0) != 0) {
                    func_ov107_020c0b90(*(int *)(*state + 0x390), 0, *(Vec3 *)(hits[i] + 0x74), 0);
                    state[4 + k] = 0x198;
                    hitMask |= bit;
                    *(int *)(*(int *)(*state + 0x390) + 0x4e0) = 1;
                }
            }
        } while (++i < nHits);
    }
    for (i = 0; i < 4; i++) {
        if ((hitMask & (1 << i)) == 0) {
            state[4 + i] -= *(int *)(node[0] + 0x2c);
            if (state[4 + i] < 0) {
                state[4 + i] = 0;
            }
        }
    }
    if (*(int *)(*(int *)(*state + 0x390) + 0x4e0) == 0) {
        return;
    }
    if (*(u8 *)(state[1] + 0xa8) != 0) {
        func_ov107_020c5af8(*state, 0x16d, 0xc, &box);
    } else {
        func_ov107_020c5af8(*state, 0, 0x50, &box);
    }
}
