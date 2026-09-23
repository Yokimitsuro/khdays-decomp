/* Placement of one ov255 ring item (only while its +0x50 mode is 1): at the given angle about the
 * forward axis turned by q, the item's +0x390 point sits 0.5 out from the centre plus the forward
 * axis, its +0x3a8 orientation faces along the cross of the forward and outward axes, the angle is
 * kept at +0x3b8 and bit 0 of the +0x60 high byte is raised. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *a, const Vec3 *b);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042258;
extern const short data_0203d210[];

void func_ov255_020d1710(char *item, Vec3 *at, void *q, int angle)
{
    Vec3 fwd;
    Vec3 side;
    Vec3 up;
    u16 hw;

    if (*(int *)(item + 0x50) != 1) {
        return;
    }
    func_0202f384(&fwd, q, &data_02042258);
    side.x = data_0203d210[ANG2IDX(angle) * 2];
    side.y = data_0203d210[ANG2IDX(angle) * 2 + 1];
    side.z = 0;
    func_0202f384(&side, q, &side);
    func_01ff8d18(&side, &side);
    VEC_CrossProduct(&fwd, &side, &up);
    func_0202ed60((Quat *)(item + 0x3a8), &data_02042258, &up);
    VEC_Add(at, &fwd, item + 0x390);
    func_01ffa724(0x800, &side, &side);
    VEC_Add(item + 0x390, &side, item + 0x390);
    *(int *)(item + 0x3b8) = angle;
    hw = *(u16 *)(item + 0x60);
    *(u16 *)(item + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
}
