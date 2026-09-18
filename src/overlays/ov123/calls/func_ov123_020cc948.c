/* Orientation tick of the ov123 enemy (and its byte-identical twin): unless bit 1 of the actor's
 * +0x1c4 flags is set, the +0x18 yaw is stepped towards the +0x1c target yaw by the +0x20 rate;
 * the yaw's rotation about world Y is composed with the orientation that tilts world Y onto the
 * actor's +0x124 normal and written to the +0xa0 quaternion; the +4 offset is handed to the
 * actor's +0xf0 vector and reset to the zero vector. */
extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(void *dst, void *src, int t);
extern void func_0202ed60(void *dst, void *src, int m);
extern void func_0202ef54(void *dst, void *a, void *b);
extern void func_0203c9d0(int a, void *b);

typedef struct { int x, y, z; } Vec3;

extern Vec3 data_02042264;
extern Vec3 data_02041dc8;

void func_ov123_020cc948(int *ctx) {
    int a[4];
    int b[4];
    int *s = (int *)ctx[1];
    if ((*(unsigned char *)(s[0] + 0x1c4) & 2) == 0) {
        s[6] = func_0203d040(s[6], s[7], s[8], 0);
    }
    func_0202f188(b, &data_02042264, s[6]);
    func_0202ed60(a, &data_02042264, s[0] + 0x124);
    func_0202ef54(a, a, b);
    func_0203c9d0(s[0] + 0xa0, a);
    {
        Vec3 *q = (Vec3 *)((char *)s + 0x4);
        *(Vec3 *)(s[0] + 0xf0) = *q;
        *q = data_02041dc8;
    }
}
