/* Ground probe of the ov137 enemy's descent. With a +0x2c target that has a +0x18c body with a
 * +0x20 collision handle, the +0x1c/+0x24 x/z ease a tenth towards the target's +0xb0/+0xb8 and
 * the +0x20 height is cleared; from (x, +0x14, z) the given direction is cast against the
 * collision owner (+4 -> +0x7c), first as a swept cast ignoring the target's handle, then as a
 * plain ray. A hit sets the +0x20 height to the origin's y plus the scaled direction's y and
 * returns the hit normal -- the result's own +0x24 triple for a hit with the +8 flag, else its
 * plane's +0x14 triple. Returns 1 on a hit. */
typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad00[0x14];
    short x, y, z;
} PlaneS16;

struct Hit {
    int pad00;
    PlaneS16 *pPlane;
    int field08;
    int nAlong;
    char pad10[0x14];
    short nx, ny, nz;
};

extern struct Hit *func_01fff888(void *collision, Vec3 *origin, Vec3 *dir, void *ignore);
extern struct Hit *func_01fff920(void *collision, Vec3 *origin, Vec3 *dir);
extern void func_01ffd144(int scale, const Vec3 *v, Vec3 *out);

int func_ov137_020cdf9c(int *state, Vec3 *dir, Vec3 *out)
{
    int coll = *(int *)(*state + 4);
    Vec3 origin;
    Vec3 d;
    struct Hit *hit;
    int target = state[0xb];

    if (target == 0) {
        return 0;
    }
    if (*(int *)(target + 0x18c) == 0) {
        return 0;
    }
    if (*(int *)(*(int *)(target + 0x18c) + 0x20) == 0) {
        return 0;
    }
    state[7] += (*(int *)(target + 0xb0) - state[7]) / 10;
    state[9] += (*(int *)(target + 0xb8) - state[9]) / 10;
    state[8] = 0;
    origin.x = state[7];
    origin.y = state[5];
    origin.z = state[9];
    d = *dir;
    hit = func_01fff888(*(void **)(coll + 0x7c), &origin, &d, *(void **)(*(int *)(state[0xb] + 0x18c) + 0x20));
    if (hit != 0) {
        if (hit->field08 != 0) {
            func_01ffd144(hit->nAlong, &d, &d);
            state[8] = origin.y + d.y;
            out->x = hit->nx;
            out->y = hit->ny;
            out->z = hit->nz;
            return 1;
        }
        func_01ffd144(hit->nAlong, &d, &d);
        state[8] = origin.y + d.y;
        out->x = hit->pPlane->x;
        out->y = hit->pPlane->y;
        out->z = hit->pPlane->z;
        return 1;
    }
    hit = func_01fff920(*(void **)(coll + 0x7c), &origin, &d);
    if (hit == 0) {
        return 0;
    }
    func_01ffd144(hit->nAlong, &d, &d);
    state[8] = origin.y + d.y;
    out->x = hit->pPlane->x;
    out->y = hit->pPlane->y;
    out->z = hit->pPlane->z;
    return 1;
}
