/* Ov254_TickRoll -- roll tick of the ov254 enemy's ball. Below speed 1/16 the 64-bit hit mask and
 * the +0x4c skip flag clear. Otherwise, at speed 5/16 or more, every entity the owner's sphere meets
 * (other than the +4 target while +0x4c is set) is hit once per roll (kind-5 push 0.5 away on the
 * plane, reaction 0x16d mode 10 at the +0x18 point); then the first other ready actor of the world's
 * +0x80 list whose active shape meets the sphere is hit once too: an armoured one (+0x1ac bit 2 with
 * its bit 14) instead redirects the roll at the partner (the fall speed grows 0xd0 per 1.0 of
 * distance, clamped), any other gets a 0x2004 packet along the contact direction. A wall contact
 * reflects the velocity at 0.625 of its speed. The +0x30 clock starts the rumble pose at 8.0 and, at
 * 12.0 or when landed with +0x48 set, the ball bursts: a doubled sphere hits everything once more,
 * the velocity stops and the node moves back to state 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct Sphere { Vec3 pos; int radius; } Sphere;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };
struct Bits17a { u8 bit0 : 1, bit1 : 1; };

struct HitPacket {
    u32 flagsLo : 16;
    u32 flagsHi : 16;
    Vec3 normal;
    int field_10 : 16;
    int field_12 : 16;
    int field_14 : 16;
    int field_16 : 16;
    void *field_18;
    signed char field_1c;
    u8 pad01d[3];
    int field_20;
    u32 flags24Lo : 16;
    u32 flags24Hi : 16;
    int field_28;
};

typedef struct Ov254RollState {
    int pOwner;
    int pTarget;
    int field_08[4];
    Vec3 *pEffectAt;
    Vec3 vel;
    int field_28[2];
    int nClock;
    u32 aHitMask[2];
    u8 bRumble;
    u8 pad03d[3];
    int bRedirected;
    int field_44;
    int bBurstOnLanding;
    int bSkipTarget;
} Ov254RollState;

extern int VEC_Mag(const Vec3 *v);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *d);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020c8eb8(int actor, Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern int func_ov107_020c3504(void *shape, Sphere *sphere, int mode);
extern int func_ov107_020c5cfc(int other, int source, struct HitPacket *packet);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020d395c(int *node)
{
    Ov254RollState *state = (Ov254RollState *)node[1];
    Sphere sphere;
    int hits[4];
    long n;
    long i;
    int *shape;
    int other;
    int *entry;
    int world;
    int mag;
    int bLanded;

    sphere = *(Sphere *)(state->pOwner + 0x74);
    if (state->bBurstOnLanding != 0 && ((struct Bits17a *)(state->pOwner + 0x17a))->bit0) {
        bLanded = 1;
    } else {
        bLanded = 0;
    }
    mag = VEC_Mag(&state->vel);
    if (mag >= 0x100) {
        world = *(int *)(state->pOwner + 4);
        shape = 0;
        if (mag >= 0x500) {
            n = func_ov107_020c8eb8(*(int *)(state->pOwner + 0x394), &sphere, hits);
            for (i = 0; i < n; i++) {
                if (state->bSkipTarget == 0 || (void *)hits[i] != (void *)state->pTarget) {
                    u16 kind = *(u16 *)(hits[i] + 2);

                    if (((*(u64 *)state->aHitMask >> kind) & 1) == 0) {
                        Vec3 push;

                        *(u64 *)state->aHitMask |= (u64)1 << kind;
                        VEC_Subtract((Vec3 *)(hits[i] + 0x74), (Vec3 *)(state->pOwner + 0x74), &push);
                        push.y = 0;
                        func_01ff8d18(&push, &push);
                        func_01ffa724(0x800, &push, &push);
                        if (func_ov107_020ca918(hits[i], state->pOwner, *(int *)(state->pOwner + 0x394), 5, &push, 0) != 0) {
                            func_ov107_020c0b90(*(int *)(state->pOwner + 0x394), 0, *state->pEffectAt, 0);
                            func_ov107_020c5af8(state->pOwner, 0x16d, 10, state->pEffectAt);
                        }
                    }
                }
            }
        }
        entry = func_01fffd70(world + 0x80);
        other = entry == 0 ? 0 : *entry;
        while (other != 0) {
            if (other != state->pOwner && (((struct hw60 *)(other + 0x60))->lo & 1) != 0
                && (*(u16 *)(other + 0x1ac) & 3) == 0
                && ((*(u16 *)(other + 0x1ac) & 4) == 0 || (*(u16 *)other & 0x8000) != 0)) {
                for (shape = func_01fffd70(other + 0x22c); shape != 0; shape = func_01fffd8c(other + 0x22c)) {
                    if ((((struct w8 *)(shape + 2))->lo & 1) != 0 && func_ov107_020c3504((void *)shape[0], &sphere, 0) != 0) {
                        break;
                    }
                }
                if (shape != 0) {
                    break;
                }
            }
            entry = func_01fffd8c(world + 0x80);
            other = entry == 0 ? 0 : *entry;
        }
        if (other != 0) {
            u16 kind = *(u16 *)(other + 2);

            if (((*(u64 *)state->aHitMask >> kind) & 1) == 0) {
                *(u64 *)state->aHitMask |= (u64)1 << kind;
                if ((*(u16 *)(other + 0x1ac) & 4) != 0 && (*(u16 *)other & 0x4000) != 0) {
                    if (state->bRedirected == 0 && state->pTarget != 0) {
                        int len;

                        VEC_Subtract((Vec3 *)(*(int *)(state->pOwner + 0x394) + 0x74), (Vec3 *)(state->pOwner + 0x74), &state->vel);
                        len = func_01ff8d18(&state->vel, &state->vel);
                        func_01ffa724(0x1000, &state->vel, &state->vel);
                        for (; len > 0; len -= 0x1000) {
                            state->vel.y += 0xd0;
                        }
                        state->vel.y = state->vel.y > 0x7fff ? 0x7fff : (state->vel.y < -0x8000 ? -0x8000 : state->vel.y);
                        state->bRedirected = 1;
                    }
                } else {
                    struct HitPacket packet = {0};
                    int ok = 1;

                    if (other == *(int *)(state->pOwner + 0x394)) {
                        ok = state->pTarget;
                        packet.field_10 = *(u16 *)(*(int *)(state->pOwner + 0x394) + 0x2ae);
                    } else {
                        packet.field_10 = *(u16 *)(state->pOwner + 2);
                    }
                    if (ok != 0) {
                        VEC_Subtract((Vec3 *)(other + 0x74), (Vec3 *)(state->pOwner + 0x74), &packet.normal);
                        func_01ff8d18(&packet.normal, &packet.normal);
                        packet.flagsLo = 0x2004;
                        packet.field_14 = *(int *)(state->pOwner + 0x258);
                        packet.field_18 = shape;
                        if ((((struct w8 *)(shape + 2))->lo & 1) != 0 && func_ov107_020c5cfc(other, 0, &packet) != 0) {
                            if (other == *(int *)(state->pOwner + 0x394)) {
                                func_ov107_020c0b90(*(int *)(state->pOwner + 0x394), 4, *state->pEffectAt, 0);
                            } else {
                                func_ov107_020c0b90(*(int *)(state->pOwner + 0x394), 0, *state->pEffectAt, 0);
                            }
                            func_ov107_020c5af8(state->pOwner, 0x16d, 10, state->pEffectAt);
                        }
                    }
                }
            }
            state->bSkipTarget = 0;
        }
        if (((struct Bits17a *)(state->pOwner + 0x17a))->bit1) {
            Vec3 n;
            Vec3 back;
            Vec3 refl;
            int len;

            n = *(Vec3 *)(state->pOwner + 0x114);
            len = func_01ff8d18(&state->vel, &back);
            func_01ffa724(-0x1000, &back, &back);
            func_01ffa724(VEC_DotProduct(&back, &n) << 1, &n, &refl);
            VEC_Subtract(&refl, &back, &refl);
            func_01ffa724(FX_Mul(len, 0xa00), &refl, &state->vel);
            state->bSkipTarget = 0;
        }
    } else {
        state->aHitMask[0] = 0;
        state->aHitMask[1] = 0;
        state->bSkipTarget = 0;
    }
    state->nClock += *(int *)(*node + 0x2c);
    if (state->nClock >= 0x8000 && state->bRumble == 0) {
        func_ov107_020c9264(state->pOwner, 1, 1);
        state->bRumble = 1;
    }
    if (!bLanded && state->nClock < 0xc000) {
        return;
    }
    func_ov107_020c0b90(*(int *)(state->pOwner + 0x394), 4, *state->pEffectAt, 0);
    if (bLanded) {
        func_ov107_020c5af8(state->pOwner, 0x16d, 0xb, state->pEffectAt);
    }
    func_ov107_020c5af8(state->pOwner, 0x16d, 0xd, state->pEffectAt);
    sphere.radius <<= 1;
    n = func_ov107_020c8eb8(*(int *)(state->pOwner + 0x394), &sphere, hits);
    for (i = 0; i < n; i++) {
        Vec3 push;

        VEC_Subtract((Vec3 *)(hits[i] + 0x74), (Vec3 *)(state->pOwner + 0x74), &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x800, &push, &push);
        if (func_ov107_020ca918(hits[i], state->pOwner, *(int *)(state->pOwner + 0x394), 5, &push, 0) != 0) {
            func_ov107_020c0b90(*(int *)(state->pOwner + 0x394), 0, *state->pEffectAt, 0);
            func_ov107_020c5af8(state->pOwner, 0x16d, 10, state->pEffectAt);
        }
    }
    *&state->vel = data_02041dc8;
    *(u8 *)(state->pOwner + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
