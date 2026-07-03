extern int func_0202f55c();
extern int func_0203c9d0();

extern short data_0203d210[];
extern int data_0203d210_vec[];

typedef struct { int x, y, z; } Vec3;

typedef struct {
    int *base;          /* +0x00 */
    char sub[0x18];     /* +0x04 .. +0x1b (field8 = +0x04) */
    int f1c;            /* +0x1c */
    int f20;            /* +0x20 */
    int f24;            /* +0x24 */
    int f28;            /* +0x28 */
    Vec3 f2c;           /* +0x2c .. +0x37 */
    int f38;            /* +0x38 */
    int f3c;            /* +0x3c */
    int f40;            /* +0x40 */
} Mid;

void func_ov117_020cc8f8(int *obj)
{
    Mid *mid = (Mid *)obj[1];
    int sum;
    int idx;
    short *base;

    func_0202f55c((char *)mid + 8, mid->f28, (char *)mid + 8, (char *)mid + 0x18);
    func_0203c9d0(mid->base[0] + 0xa0, (char *)mid + 8);

    if (*((signed char *)(mid->base[0] + 0x100) + 0xc6) == 2 ||
        *((signed char *)(mid->base[0] + 0x100) + 0xc6) == 4) {

        sum = mid->f3c + *(int *)((char *)obj[0] + 0x2c);
        mid->f3c = sum;
        sum <<= 3;
        idx = (int)(((long long)sum * 0x28be60db9391LL + (0x800LL << 32)) >> 32);
        idx = (int)((unsigned)(idx << 4) >> 16) >> 4;

        *(int *)((char *)mid + 0x30) += data_0203d210[idx * 2] / 25;
    }

    if (mid->f40 > 0)
        mid->f40 -= *(int *)((char *)obj[0] + 0x2c);

    *(Vec3 *)((char *)mid->base[0] + 0xf0) = mid->f2c;
    mid->f2c = *(Vec3 *)&data_0203d210;
}
