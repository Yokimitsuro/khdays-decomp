/* Launch an ov259 helper while it is live (+0x50 == 1): its +0xa0 pose turns from the rest axis
 * (data_02042240) to `dir`, it is placed at `pos` (020c5c54), the +0x0c handler is told (when +0x40
 * bit 1 allows it), +0x388 marks it busy and its +0x214 flight takes the direction and heading
 * (020d2904). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
struct Flags40 { int b0 : 1; int b1 : 1; };

extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202f4a4(Quat *q, Quat *out);
extern void func_0203c9d0(char *srt, Quat *q);
extern void func_ov107_020c5c54(char *actor, Vec3 *at);
extern void func_ov259_020d2904(int flight, Vec3 *dir, int heading);
extern const Vec3 data_02042240;

void func_ov259_020d26e0(char *self, Vec3 *pos, Vec3 *dir, int heading)
{
    Quat q;

    if (*(int *)(self + 0x50) != 1) {
        return;
    }
    func_0202ed60(&q, &data_02042240, dir);
    func_0202f4a4(&q, &q);
    func_0203c9d0(self + 0xa0, &q);
    func_ov107_020c5c54(self, pos);
    if (((struct Flags40 *)(self + 0x40))->b1 && *(void (**)(char *, int))(self + 0xc) != 0) {
        (*(void (**)(char *, int))(self + 0xc))(self, 0);
    }
    *(int *)(self + 0x388) = 1;
    func_ov259_020d2904(*(int *)(self + 0x214), dir, heading);
}
