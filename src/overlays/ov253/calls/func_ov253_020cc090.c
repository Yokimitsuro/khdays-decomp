/* func_ov253_020cc090 -- chain update: the +0x38c item's transform takes the +0x398 joint's
 * anchor and its +4 rotation while the actor is in kind 3 or 7 (otherwise a rotation of +0x44c
 * about data_02042264); then each of the four +0x3ac chains refreshes its three +0x58 segments
 * (start at joint i's anchor, +0xc direction to joint i+1, +0x18 length). */
typedef struct { int x, y, z; } Vec3;
struct vec4 { int a, b, c, d; };
struct Ov253Chain { int joints[4]; int f10; int segs[3]; int f20; };
struct Ov253Chains { char pad[0x3ac]; struct Ov253Chain chain[4]; };

extern void func_0202f188(struct vec4 *out, const Vec3 *axis, int angle);
extern void func_0203ca30(void *srt, const Vec3 *translation);
extern void func_0203c9d0(void *srt, const struct vec4 *rotation);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042264;

static inline void Ov253_ChainUpdate(struct Ov253Chain *chain) {
    int i;
    for (i = 0; i < 3; i++) {
        char *seg = (char *)chain->segs[i] + 0x58;
        *(Vec3 *)seg = *(Vec3 *)(chain->joints[i] + 0x14);
        VEC_Subtract((Vec3 *)(chain->joints[i + 1] + 0x14), (Vec3 *)seg, (Vec3 *)(seg + 0xc));
        *(int *)(seg + 0x18) = func_01ff8d18((Vec3 *)(seg + 0xc), (Vec3 *)(seg + 0xc));
    }
}

void func_ov253_020cc090(int a, char *self) {
    struct vec4 rot;

    if (!(*(signed char *)(self + 0x100 + 0xc6) != 7 && *(signed char *)(self + 0x100 + 0xc6) != 3)) {
        rot = *(struct vec4 *)(*(int *)(self + 0x398) + 4);
    } else {
        func_0202f188(&rot, &data_02042264, *(int *)(self + 0x44c));
    }
    func_0203ca30((void *)(*(int *)(self + 0x38c) + 0x30), (Vec3 *)(*(int *)(self + 0x398) + 0x14));
    func_0203c9d0((void *)(*(int *)(self + 0x38c) + 0x30), &rot);
    Ov253_ChainUpdate(&((struct Ov253Chains *)self)->chain[0]);
    Ov253_ChainUpdate(&((struct Ov253Chains *)self)->chain[1]);
    Ov253_ChainUpdate(&((struct Ov253Chains *)self)->chain[2]);
    Ov253_ChainUpdate(&((struct Ov253Chains *)self)->chain[3]);
}
