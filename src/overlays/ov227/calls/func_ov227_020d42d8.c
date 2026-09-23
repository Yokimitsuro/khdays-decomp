/* Hit sweep of an ov227 part: the given sphere is queried against the owner's +0x38c body; every
 * target whose kind bit (1 << +2) is not yet in the +0x28 mask is pushed along the flattened unit
 * direction from the owner (hit kind 1) and, when that lands, records its kind bit. After any hit
 * reaction 0x14d mode 0x10 fires at the +4 point. Returns whether anything was hit. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 c; int r; } Sphere;

extern int func_ov107_020c8eb8(int body, Sphere *src, int *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int a, int b, int mode, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);

int func_ov227_020d42d8(int *part, Sphere *sphere)
{
    int hits[4];
    Vec3 dir;
    int n;
    int i;
    int hit;
    unsigned int mask;

    hit = 0;
    n = func_ov107_020c8eb8(*(int *)(*part + 0x38c), sphere, hits);
    for (i = 0; i < n; i++) {
        mask = (1 << *(unsigned short *)(hits[i] + 2)) & 0xff;
        if ((*(unsigned char *)((char *)part + 0x28) & mask) != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*part + 0x74), &dir);
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        if (func_ov107_020ca918(hits[i], *part, *(int *)(*part + 0x38c), 1, &dir, 0) != 0) {
            hit = 1;
            *(unsigned char *)((char *)part + 0x28) |= mask;
        }
    }
    if (hit != 0) {
        func_ov107_020c5af8(part[0], 0x14d, 0x10, (void *)part[1]);
    }
    return hit;
}
