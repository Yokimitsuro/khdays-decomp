/* func_ov260_020cd2a0 -- attack sweep of the ov260 actor: collects the hits of the given cylinder,
 * sphere or segment (or, with none, a segment from the owner's +0x424 joint along its heading,
 * 0x1800 or 0x3000 long by the +0x470 flag, radius 0x400). Each hit not yet struck (bit of +0x79)
 * is pushed away flat at half strength (020ca918 with `kind`); an accepted hit spawns the impact
 * effect (7 for cylinder/sphere, 0 otherwise) at the sphere's scaled contact or the victim, and is
 * marked struck. Any hit sounds the attack (020cd148 mode 4). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

extern const Vec3 data_02042258;
extern int func_ov107_020c8fd0(int owner, void *cyl, int *hits);
extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern int func_ov107_020c8f44(int owner, void *seg, int *hits);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);

void func_ov260_020cd2a0(int *state, int kind, Vec3 *sphere, void *cyl, void *seg)
{
    int hits[4];
    Segment sweep;
    Vec3 push;
    Vec3 dir;
    long i;
    int effect = 7;
    long n;
    int hit = 0;
    u8 bit;

    if (cyl != 0) {
        n = func_ov107_020c8fd0(*state, cyl, hits);
    } else if (sphere != 0) {
        n = func_ov107_020c8eb8(*state, sphere, hits);
    } else if (seg != 0) {
        n = func_ov107_020c8f44(*state, seg, hits);
        effect = 0;     /* cleared after the query in each branch, as the ROM hoists it */
    } else {
        sweep.p0 = *(Vec3 *)(*(int *)(*state + 0x424) + 0x14);
        sweep.nLength = *(int *)(*state + 0x470) == 0 ? 0x1800 : 0x3000;
        sweep.nRadius = 0x400;
        func_0202f384(&sweep.dir, (void *)(*(int *)(*state + 0x424) + 4), &data_02042258);
        n = func_ov107_020c8f44(*state, &sweep, hits);
        effect = 0;
    }
    for (i = 0; i < n; i++) {
        bit = 1 << *(u16 *)(hits[i] + 2);

        if ((*((u8 *)state + 0x79) & bit) != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
        func_01ff8d18(&push, &dir);
        push.y = 0;
        if (func_01ff8d18(&push, &push) == 0) {
            push = data_02042258;
        }
        func_01ffa724(0x800, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *state, kind, &push, 0) == 0) {
            continue;
        }
        if (sphere != 0) {
            func_01ffa724(*(int *)((u8 *)sphere + 0xc), &dir, &dir);
            VEC_Add(&dir, &push, &dir);
            VEC_Add(&dir, sphere, &dir);
            func_ov107_020c0b90(*state, effect, dir, 0);
        } else {
            VEC_Add((void *)(hits[i] + 0x74), &push, &dir);
            func_ov107_020c0b90(*state, effect, dir, 0);
        }
        *((u8 *)state + 0x79) |= bit;
        hit = 1;
    }
    if (hit == 0) {
        return;
    }
    func_ov260_020cd148(*state, 4, state[4]);
}
