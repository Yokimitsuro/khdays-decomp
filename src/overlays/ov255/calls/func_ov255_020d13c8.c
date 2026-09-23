/* Spawn of the second ov255 helper (0x18-byte state, kind 100; tick func_ov255_020d1464, second
 * callback func_ov255_020d14d4): it keeps the enemy and the part, stores the start point at +0xc,
 * places the part there and records at +8 whether the enemy's +0x50 mode is 1. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_0203ca30(void *srt, const Vec3 *pos);
extern void func_ov255_020d1464(void);
extern void func_ov255_020d14d4(void);

int func_ov255_020d13c8(char *self, int part, Vec3 *pos)
{
    int *out;

    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0x18, func_ov255_020d1464, func_ov255_020d14d4, &out);
    out[0] = (int)self;
    out[1] = part;
    *(Vec3 *)(out + 3) = *pos;
    func_0203ca30((void *)(out[1] + 4), pos);
    out[2] = *(int *)(out[0] + 0x50) == 1;
    return rc;
}
