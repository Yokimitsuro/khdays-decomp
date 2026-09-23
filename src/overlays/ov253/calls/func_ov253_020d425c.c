/* Thrown-spear tick: the +0x24 travel grows by the +0x20 speed x the frame rate x 30 and the +8
 * velocity is the +0x14 heading at that speed. While not stuck (+0x44), the step segment from the +4
 * point (0.125 thick) sweeps the actor list on behalf of the +0x388 owner: the first valid target
 * (func_ov253_020cceb0) that accepts a 1/16 push along the flight (kind 2) stops the spear, the
 * owner's reaction 0x16b mode 6 fires at the +4 point and pose 2 is requested. Past 2.0 the flight
 * ray is also tested against the hit shapes (+0x144 list) of the stage's +0x80 objects that are
 * solid (+0x60 bit 0), not ghosted (bit 7) and not disabled (+0x1ac bit 2), with the same result.
 * Past 45.0, or once blocked/grounded (+0x17a bits 0, 1, 3), the owner's reaction mode 7 fires and
 * pose 2 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;
typedef struct { Vec3 p0; Vec3 dir; int nLength; } Ray;
typedef struct { u16 lo : 8; u16 hi : 8; } Hw60;
struct Bits17a { unsigned char b0 : 1, b1 : 1, b2 : 1, b3 : 1; };

extern const Vec3 data_02041dc8;
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_ov253_020cceb0(int owner, int hit);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern int func_ov107_020c36bc(int shape, Ray *ray, Vec3 *out);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov253_020d425c(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    Segment seg;
    int i;
    int n;

    state[9] += FX_Mul(state[8], *(int *)(node[0] + 0x2c) * 30);
    func_01ffa724(state[8], (Vec3 *)(state + 5), (Vec3 *)(state + 2));
    if (state[0x11] == 0) {
        seg.p0 = *(Vec3 *)state[1];
        seg.nLength = func_01ff8d18((Vec3 *)(state + 2), &seg.dir);
        seg.nRadius = 0x200;
        n = func_ov107_020c8f44(*(int *)(*state + 0x388), &seg, hits);
        for (i = 0; i < n; i++) {
            Vec3 push;

            if (func_ov253_020cceb0(*(int *)(*state + 0x388), hits[i]) == 0) {
                continue;
            }
            func_01ff8d18((Vec3 *)(state + 2), &push);
            func_01ffa724(0x100, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x388), 2, &push, 0) == 0) {
                continue;
            }
            *(Vec3 *)(state + 2) = data_02041dc8;
            func_ov107_020c5af8(*(int *)(state[0] + 0x388), 0x16b, 6, (void *)state[1]);
            *(u8 *)(*state + 0x1c7) = 2;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state[9] >= 0x2000) {
        int *link;
        int obj;
        int grid;
        Ray ray;
        int *sub;

        grid = *(int *)(*state + 4);
        ray.p0 = *(Vec3 *)state[1];
        ray.nLength = func_01ff8d18((Vec3 *)(state + 2), &ray.dir);
        for (link = func_01fffd70((void *)(grid + 0x80)); link != 0; link = func_01fffd8c((void *)(grid + 0x80))) {
            obj = *link;
            if ((((Hw60 *)(obj + 0x60))->lo & 1) == 0 || (((Hw60 *)(obj + 0x60))->lo & 0x80) != 0
                || (*(u16 *)(obj + 0x1ac) & 4) != 0) {
                continue;
            }
            for (sub = func_01fffd70((void *)(obj + 0x144)); sub != 0; sub = func_01fffd8c((void *)(obj + 0x144))) {
                if (func_ov107_020c36bc(*sub, &ray, 0) != 0) {
                    *(Vec3 *)(state + 2) = data_02041dc8;
                    func_ov107_020c5af8(*(int *)(state[0] + 0x388), 0x16b, 6, (void *)state[1]);
                    *(u8 *)(*state + 0x1c7) = 2;
                    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                    return;
                }
            }
        }
    }
    if (state[9] > 0x2d000 || ((struct Bits17a *)(*state + 0x17a))->b1 || ((struct Bits17a *)(*state + 0x17a))->b0
        || ((struct Bits17a *)(*state + 0x17a))->b3) {
        func_ov107_020c5af8(*(int *)(state[0] + 0x388), 0x16b, 7, (void *)state[1]);
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
