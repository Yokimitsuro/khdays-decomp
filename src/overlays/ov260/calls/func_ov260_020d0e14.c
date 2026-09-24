/* d0e14 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c8fd0(int owner, void *cyl, int *hits);
extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

int func_ov260_020d0e14(int *state, void *sphere, void *cyl)
{
    int hit = 0;
    int hits[4];
    Vec3 push;
    long i;
    long n;
    u8 bit;

    if (cyl != 0) {
        n = func_ov107_020c8fd0(*(int *)(*state + 0x390), cyl, hits);
    } else {
        if (sphere == 0) {
            return 0;
        }
        n = func_ov107_020c8eb8(*(int *)(*state + 0x390), sphere, hits);
    }
    for (i = 0; i < n; i++) {
        bit = 1 << *(u16 *)(hits[i] + 2);

        if ((*((u8 *)state + 0x48) & bit) != 0) {
            continue;
        }
        if (cyl != 0) {
            VEC_Subtract((void *)(hits[i] + 0x74), cyl, &push);
        } else {
            VEC_Subtract((void *)(hits[i] + 0x74), sphere, &push);
        }
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x800, &push, &push);
        push.y = 0x1000;
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x390), 6, &push, 0) == 0) {
            continue;
        }
        func_ov107_020c0b90(*(int *)(*state + 0x390), 7, *(Vec3 *)state[6], 0);
        *((u8 *)state + 0x48) |= bit;
        hit = 1;
        *(int *)(*state + 0x38c) = 1;
    }
    return hit;
}
