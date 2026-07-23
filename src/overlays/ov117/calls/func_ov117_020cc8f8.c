/* func_ov117_020cc8f8 -- AI think tick: step the spline, push it to the render node, and while the
 * actor is in reaction state 2 or 4 advance its heading and drift.
 *
 * The heading step is `timer * 8` mapped through the Q12 sin/cos table at data_0203d210 (indexed
 * by the reciprocal-multiply of 0x28be60db9391), its sample divided by 25 and accumulated into
 * +0x30. The tail resets the state's own position vector from the shared zero vector at
 * data_02041dc8 and copies the previous one to the render node, advancing the state pointer with
 * a post-indexed load.
 *
 * Three things are load-bearing:
 *  - the field at +0 of the state block is the owner ADDRESS, not a pointer to it; modelling it as
 *    `int *` costs an extra `ldr` at each of the four uses.
 *  - the tail vector comes from data_02041dc8. Reading it from data_0203d210 (which the old note
 *    did) makes the two pool loads share one word and the literal pool comes out four bytes short.
 *  - the timer update is a compound assignment USED AS A VALUE, `sum = (mid->f3c += delta)`.
 *    Split into `sum = ...; mid->f3c = sum;` mwcc hoists the following literal-pool load one slot
 *    above the shift. */
extern int func_0202f55c();
extern int func_0203c9d0();

extern short data_0203d210[];
extern int data_02041dc8[];

typedef struct { int x, y, z; } Vec3;

typedef struct {
    int base;           /* +0x00 */
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
    func_0203c9d0(mid->base + 0xa0, (char *)mid + 8);

    if (*((signed char *)(mid->base + 0x100) + 0xc6) == 2 ||
        *((signed char *)(mid->base + 0x100) + 0xc6) == 4) {

        sum = (mid->f3c += *(int *)((char *)obj[0] + 0x2c));
        sum <<= 3;
        idx = (int)(((long long)sum * 0x28be60db9391LL + (0x800LL << 32)) >> 32);
        idx = (int)((unsigned)(idx << 4) >> 16) >> 4;

        *(int *)((char *)mid + 0x30) += data_0203d210[idx * 2] / 25;
    }

    if (mid->f40 > 0)
        mid->f40 -= *(int *)((char *)obj[0] + 0x2c);

    *(Vec3 *)((char *)mid->base + 0xf0) = mid->f2c;
    mid->f2c = *(Vec3 *)&data_02041dc8;
}
