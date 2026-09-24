/* cd0e8 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern int func_ov107_020c8df0(int owner, void *box, int *hits);
extern int func_ov107_020c8f44(int owner, void *seg, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

int func_ov256_020cd0e8(int *node, void *sphere, void *box, void *seg, Vec3 *push, int bMask, int unused, int kind)
{
    int *state = (int *)node[1];
    int hits[4];
    long n;
    long i;

    if (sphere != 0) {
        n = func_ov107_020c8eb8(*state, sphere, hits);
    } else if (box != 0) {
        n = func_ov107_020c8df0(*state, box, hits);
    } else {
        n = func_ov107_020c8f44(*state, seg, hits);
    }
    if (n != 0) {
        for (i = 0; i < n; i++) {
            u8 bit = 1 << *(u16 *)(hits[i] + 2);

            if (bMask != 0 && (*((u8 *)state + 0x6a) & bit) != 0) {
                continue;
            }
            if (func_ov107_020ca918(hits[i], *state, *state, kind, push, 0) == 0) {
                continue;
            }
            if (bMask != 0) {
                *((u8 *)state + 0x6a) |= bit;
            }
            func_ov107_020c0b90(*state, 0, *(Vec3 *)(hits[i] + 0x190), 0);
        }
        if (bMask != 0) {
            if (*((u8 *)state + 0x6a) != 0) {
                return 1;
            }
        } else if (n != 0) {
            return 1;
        }
    }
    return 0;
}
