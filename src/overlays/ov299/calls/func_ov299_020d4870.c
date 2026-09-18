/* Flight tick of the ov299 projectile. The +0x10 vertical speed loses 0x60 x dt / 0x88 per
 * tick. A capsule from the previous +0x18 position towards the +4 position with the actor's
 * +0x80 radius is queried: any entity accepting a kind-0 hit pushed away from the actor at 0x800
 * (through the +0x390 item) ends the flight with effect 1 at the position, reaction 0x170/5 and
 * sub-state 0. Then every other ready actor of the scene's +0x80 list (not the +0x390 item, with
 * bits 0-2 of +0x1ac clear) whose active +0x22c shapes cross the capsule gets a kind-4 hit
 * packet (zero normal, the +0x390 item's +0x290 id and the actor's +0x258 id) through the +0x25c
 * source (only the first crossing shape of each actor is tried); an accepted hit ends the
 * flight the same way. Otherwise the +0x18 position
 * advances to the +4 position: a line cast (fff888) or a 0x300 sphere cast (fff8e8) against the
 * scene's +0x7c collision along the step stops at the contact (effect 1 there, reaction 0x170/6,
 * effect 2 too on a 0xd-typed surface) and, past 0x3c000 of +0x24 flight time, the flight ends
 * with effect 1 at the position. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

typedef struct Segment {
    Vec3 p0;
    Vec3 dir;
    int scale;
} Segment;

struct Capsule {
    Segment seg;
    int radius;
};

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

extern void VEC_Subtract(const void *a, const void *b, Vec3 *d);
extern void VEC_Add(const void *a, const void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020c8f44(int actor, struct Capsule *cap, int *out);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int actor, int effect, Vec3 at, int d);
extern void func_ov107_020c5af8(int actor, int id, int mode, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern int func_ov107_020c38ac(void *shape, Segment *seg, int flags);
extern int func_ov107_020c5cfc(int other, int source, struct HitPacket *packet);
extern int func_01fff888(void *collision, Vec3 *from, Vec3 *step, void *ignore);
extern int func_01fff8e8(void *collision, Vec3 *from, Vec3 *step, int radius, void *ignore);
extern void func_01ffd144(int t, Vec3 *v, Vec3 *d);
extern const Vec3 data_02041dc8;

void func_ov299_020d4870(int *node)
{
    int *state = (int *)node[1];
    struct Capsule cap;
    Vec3 last;
    Vec3 step;
    int hits[4];
    Vec3 push;
    int i;
    int nHits;
    int scene;
    int other;
    int *entry;
    int *shape;
    int hit;
    int rec;
    int res;

    scene = *(int *)(*state + 4);
    state[4] += *(int *)(*node + 0x2c) * -0x60 / 0x88;
    cap.seg.p0 = *(Vec3 *)(state + 6);
    VEC_Subtract((void *)state[1], state + 6, &cap.seg.dir);
    cap.seg.scale = func_01ff8d18(&cap.seg.dir, &cap.seg.dir);
    cap.radius = *(int *)(*state + 0x80);
    nHits = func_ov107_020c8f44(*state, &cap, hits);
    for (i = 0; i < nHits; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x800, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x390), 0, &push, 0) != 0) {
            func_ov107_020c0b90(*state, 1, *(Vec3 *)state[1], 0);
            func_ov107_020c5af8(*state, 0x170, 5, (void *)state[1]);
            *(u8 *)(*state + 0x1c7) = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    entry = func_01fffd70(scene + 0x80);
    other = entry == 0 ? 0 : *entry;
    if (other != 0) {
        do {
            if (other != *(int *)(*state + 0x390) && (((struct hw60 *)(other + 0x60))->lo & 1) != 0 &&
                (*(u16 *)(other + 0x1ac) & 1) == 0 && (*(u16 *)(other + 0x1ac) & 2) == 0 &&
                (*(u16 *)(other + 0x1ac) & 4) == 0) {
                for (shape = func_01fffd70(other + 0x22c); shape != 0; shape = func_01fffd8c(other + 0x22c)) {
                    if ((((struct w8 *)(shape + 2))->lo & 1) != 0 && func_ov107_020c38ac((void *)shape[0], &cap.seg, 0) != 0) {
                        struct HitPacket packet = {0};
                        packet.flagsLo = 4;
                        packet.normal = data_02041dc8;
                        packet.field_10 = *(u16 *)(*(int *)(*state + 0x390) + 0x290);
                        packet.field_14 = *(int *)(*state + 0x258);
                        packet.field_18 = shape;
                        if (func_ov107_020c5cfc(other, *(int *)(*state + 0x25c), &packet) != 0) {
                            func_ov107_020c0b90(*state, 1, *(Vec3 *)state[1], 0);
                            func_ov107_020c5af8(*state, 0x170, 5, (void *)state[1]);
                            *(u8 *)(*state + 0x1c7) = 0;
                            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                            return;
                        }
                        break;
                    }
                }
            }
            entry = func_01fffd8c(scene + 0x80);
            other = entry == 0 ? 0 : *entry;
        } while (other != 0);
    }
    VEC_Subtract((void *)state[1], state + 6, &step);
    last = *(Vec3 *)(state + 6);
    *(Vec3 *)(state + 6) = *(Vec3 *)state[1];
    hit = func_01fff888(*(void **)(scene + 0x7c), &last, &step, 0);
    if (hit != 0) {
        rec = *(int *)(hit + 4);
        func_01ffd144(*(int *)(hit + 0xc), &step, &step);
        VEC_Add(&step, &last, &last);
        func_ov107_020c0b90(*state, 1, last, 0);
        func_ov107_020c5af8(*state, 0x170, 6, &last);
        if (rec != 0 && *(u8 *)(rec + 0x83) == 0xd) {
            func_ov107_020c0b90(*state, 2, last, 0);
        }
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    res = func_01fff8e8(*(void **)(scene + 0x7c), &last, &step, 0x300, 0);
    if (res != 0 && *(int *)(res + 8) == 0) {
        func_01ffd144(*(int *)(res + 0xc), &step, &step);
        VEC_Add(&step, &last, &last);
        func_ov107_020c0b90(*state, 1, last, 0);
        func_ov107_020c5af8(*state, 0x170, 6, &last);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[9] += *(int *)(*node + 0x2c);
    if (state[9] < 0x3c000) {
        return;
    }
    func_ov107_020c0b90(*state, 1, *(Vec3 *)state[1], 0);
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
