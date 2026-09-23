/* Draw pre-pass of the ov257 enemy (+0xc): the first +0x3b4 shape and the +0x3b8 shape take the
 * +0x3d4 part's pose and the +0x3bc shape the +0x3d8 part's; each of the four +0x3c0 segment
 * items gets a pose placed at its +0x3dc bone and turned to face its +0x3ec bone. While the kind
 * (+0x1c6) is not 0xc a running pair-6 effect is stopped; then the common draw handler runs. The
 * bone arrays are indexed as ((int *)self)[base + i] for the ROM's addressing. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { int w[11]; } Srt;
struct Part { char pad[0x10]; Srt pose; };
struct Rig { int pad; Srt srt; };

extern void func_0203c960(Srt *srt);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *a, const Vec3 *b);
extern void func_0203ca30(Srt *srt, const void *pos);
extern void func_0203c9d0(Srt *srt, const Quat *q);
extern void func_0203c650(int model, int handle);
extern void func_ov107_020c7ca4(char *self);
extern const Vec3 data_02042258;

void func_ov257_020cca38(char *self)
{
    Srt srt;
    Vec3 d;
    Quat q;
    int i;

    (**(struct Part ***)(self + 0x3b4))->pose = (*(struct Rig **)(self + 0x3d4))->srt;
    (*(struct Part **)(self + 0x3b8))->pose = (*(struct Rig **)(self + 0x3d4))->srt;
    (*(struct Part **)(self + 0x3bc))->pose = (*(struct Rig **)(self + 0x3d8))->srt;
    for (i = 0; i < 4; i++) {
        func_0203c960(&srt);
        VEC_Subtract((void *)(((int *)self)[0xfb + i] + 0x14), (void *)(((int *)self)[0xf7 + i] + 0x14), &d);
        func_01ff8d18(&d, &d);
        func_0202ed60(&q, &data_02042258, &d);
        func_0203ca30(&srt, (void *)(((int *)self)[0xf7 + i] + 0x14));
        func_0203c9d0(&srt, &q);
        ((struct Part **)self)[0xf0 + i]->pose = srt;
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 0xc && *(int *)(*(int *)(self + 0x400) + 0x34) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x400) + 0x34));
        *(int *)(*(int *)(self + 0x400) + 0x34) = 0;
    }
    func_ov107_020c7ca4(self);
}
