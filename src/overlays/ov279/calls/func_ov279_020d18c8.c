/* Swipe hit window of the ov279 enemy. The +0x50 timer advances by the
 * node's +0x2c speed; between 0.56 and 1.13 it queries a 0.28-radius sphere at the midpoint of the
 * two +0x394/+0x398 bone points, and every hit whose kind bit (1 << +2) is not yet in the +0x70
 * mask is pushed along the flattened unit direction from the +0x4c point (zero when degenerate):
 * a landed hit spawns effect 2 at the sphere, records the kind bit and fires reaction 0 mode 0x50
 * at the point. Once the owner's +0xad busy byte is clear, sub-state 8 is requested. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 c; int r; } Sphere;

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020c8eb8(int owner, Sphere *src, int *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int victim, int a, int b, int mode, Vec3 *push, int flags);
extern void func_ov107_020c0b90(int obj, int cmd, Vec3 v, int flag);
extern void func_ov107_020c5af8(int obj, int effect, int kind, void *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;

void func_ov279_020d18c8(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    Sphere sphere;
    Vec3 dir;
    int n;
    int i;

    state[0x14] += *(int *)(*node + 0x2c);
    if (state[0x14] > 0x900 && state[0x14] <= 0x1200) {
        VEC_Add((Vec3 *)(*(int *)(*state + 0x398) + 0x14), (Vec3 *)(*(int *)(*state + 0x394) + 0x14), &sphere.c);
        func_01ffa724(0x800, &sphere.c, &sphere.c);
        sphere.r = 0x900;
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            if ((*(unsigned char *)((char *)state + 0x70) & (1 << *(unsigned short *)(hits[i] + 2))) != 0) {
                continue;
            }
            VEC_Subtract((void *)(hits[i] + 0x74), (void *)state[0x13], &dir);
            dir.y = 0;
            if (func_01ff8d18(&dir, &dir) == 0) {
                dir = data_02042258;
            }
            func_01ffa724(0x1000, &dir, &dir);
            if (func_ov107_020ca918(hits[i], *state, *state, 0, &dir, 0) != 0) {
                func_ov107_020c0b90(*state, 2, sphere.c, 0);
                *(unsigned char *)((char *)state + 0x70) |= 1 << *(unsigned short *)(hits[i] + 2);
                func_ov107_020c5af8(*state, 0, 0x50, (void *)state[0x13]);
            }
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
