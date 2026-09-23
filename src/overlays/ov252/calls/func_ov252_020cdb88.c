/* Angle between the `dir` heading and `angle` (0203cd20 of the dot product of their unit vectors),
 * made positive when `absolute` is set. */
typedef struct { int x, y, z; } Vec3;

extern int func_020050b4(int x, int z);
extern int func_0203cd20(int cosine);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

int func_ov252_020cdb88(int *node, Vec3 *dir, int angle, int absolute)
{
    int heading = func_020050b4(dir->x, dir->z);
    int ia = ANG2IDX(angle) * 2;
    int ih = ANG2IDX(heading) * 2;
    int diff = func_0203cd20(FX_MUL(data_0203d210[ih], data_0203d210[ia]) +
                             FX_MUL(data_0203d210[ih + 1], data_0203d210[ia + 1]));
    int mag = diff < 0 ? -diff : diff;

    return absolute == 0 ? diff : mag;
}
