
#include "nitro/types.h"
#include "game/engine.h"

typedef struct Vec3
{
  int x;
  int y;
  int z;
} Vec3;
typedef struct 
{
  int m[9];
} Mtx33;
typedef struct 
{
  Vec3 pos;
  Vec3 axis[3];
  Vec3 half;
} Box;
struct CollisionResult
{
  int pad00;
  int pad04;
  int field08;
  int nAlong;
};
extern void ScaleVec3Fx12(int scale, Vec3 *v, Vec3 *d);
extern fx16 FX_Atan2(int x, int z);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(Vec3 *v, Mtx33 *m, Vec3 *d);
extern void VEC_Add(Vec3 *a, Vec3 *b, Vec3 *d);
extern int Ov107_CollectCapsuleOverlaps(int owner, Box *box, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int VEC_Normalize(Vec3 *v, Vec3 *d);
extern int Ov107_InvokeHitCallback(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void Ov107_BuildAndSendUpdate(int owner, int id, int mode, int at);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern struct CollisionResult *Collision_CastSphereEx(int collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern int VEC_Mag(Vec3 *v);
extern const short data_0203d210[];
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

/* Ov226_FlightTick -- flight tick of the ov226 wisp: bit 1 of the +4 object's +0x5c is cleared, the
 * +0x38 phase advances by the frame step times the +0x3c rate and on each wrap draws a new speed (+0x34),
 * rate and sway (+0x40); the +0x18 velocity is scaled along the +0x24 heading by |cos(phase)| * speed + 1/16
 * and swayed sideways by sin(phase) * sway rotated to the heading. A box around the +8 position (lifted by
 * 1.5, axis aligned, half extents the actor's +0x80 radius / 1.5 / radius) is swept: every hit that
 * accepts the push (away from the actor, flattened) plays effect 0 at the box and reaction 0x14c/8, and
 * any hit ends the flight. Otherwise the step since +0xc is probed against the scene (radius 0.1875): a
 * solid hit plays effect 0, reaction 0x14c/9 and ends the flight; past 30.0 travelled it ends too. */
void Ov226_FlightTick(int *node)
{
    int *state = (int *)node[1];
    Box box;
    int hits[4];
    Mtx33 mtx;
    Vec3 v;
    Vec3 push;
    int world = *(int *)(state[0] + 4);
    long i;
    long n;
    int centreY;
    int radius;
    struct CollisionResult *hit;

    *(int *)(state[1] + 0x5c) &= ~2;
    state[0xe] += *(int *)(node[0] + 0x2c) * state[0xf] / 0x1000;
    if (state[0xe] >= 0x10000) {
        state[0xe] &= 0xffff;
        state[0xd] = RandNextScaled(0x101) + 0x200;
        state[0xf] = RandNextScaled(0x10001) + 0x10000;
        state[0x10] = RandNextScaled(0x501) + 0x200;
    }
    {
        int speed = state[0xd];
        int c = data_0203d210[(state[0xe] >> 4) * 2 + 1];

        if (c < 0) {
            c = -c;
        }
        ScaleVec3Fx12((int)(((long long)c * speed + 0x800) >> 12) + 0x100, (Vec3 *)(state + 9), (Vec3 *)(state + 6));
    }
    {
        int sn = data_0203d210[(state[0xe] >> 4) * 2];

        v.x = (int)(((long long)sn * state[0x10] + 0x800) >> 12);
    }
    v.y = 0;
    v.z = 0;
    {
        unsigned int idx = (unsigned short)(((long long)FX_Atan2(state[9], state[0xb]) * 0x28be60db9391LL
                                             + 0x80000000000LL) >> 44) >> 4;

        MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    }
    MTX_MultVec33(&v, &mtx, &v);
    VEC_Add((Vec3 *)(state + 6), &v, (Vec3 *)(state + 6));
    box.pos = *(Vec3 *)state[2];
    box.axis[0] = data_02042270;
    box.axis[1] = data_02042264;
    box.axis[2] = data_02042258;
    radius = *(int *)(*state + 0x80);
    box.half.y = 0x17cc;
    centreY = box.pos.y;
    box.half.x = radius;
    box.half.z = *(int *)(*state + 0x80);
    box.pos.y = centreY + 0x17cc;
    n = Ov107_CollectCapsuleOverlaps(*(int *)(*state + 0x390), &box, hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
        push.y = 0;
        VEC_Normalize(&push, &push);
        if (
            Ov107_InvokeHitCallback(hits[i], *state, *(int *)(*state + 0x390), (u8)state[0x11], &push, 0) != 0) {
            func_ov107_020c0b90(*state, 0, box.pos, 0);
            Ov107_BuildAndSendUpdate(*state, 0x14c, 8, state[2]);
        }
    }
    if (n != 0) {
        *(u8 *)(*state + 0x1c7) = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)state[2], (void *)(state + 3), &v);
    *(Vec3 *)(state + 3) = *(Vec3 *)state[2];
    hit = Collision_CastSphereEx(*(int *)(world + 0x7c), (Vec3 *)state[2], &v, 0x300, 0);
    if (hit != 0 && hit->field08 == 0) {
        func_ov107_020c0b90(*state, 0, box.pos, 0);
        Ov107_BuildAndSendUpdate(*state, 0x14c, 9, state[2]);
        *(u8 *)(*state + 0x1c7) = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0xc] += VEC_Mag(&v);
    if (state[0xc] <= 0x1e000) {
        return;
    }
    func_ov107_020c0b90(*state, 0, box.pos, 0);
    *(u8 *)(*state + 0x1c7) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
