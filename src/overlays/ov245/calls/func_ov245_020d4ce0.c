/* Per-frame update of the ov245 enemy's claws: outside move 1 the +0x3b8 scene link is released
 * (0203c650 on the +0x3c scene) and the +0x3ac effect freed (020cb100). Each claw (the +0x38c part,
 * then the one *+0x388 points to) copies the +0x394 body transform into its +0x10 transform and is
 * pulled back along its +0x64 direction by its +0x70 reach, turned by that transform. The base
 * update (020c7ca4) follows. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } SrtTransform;

extern void func_0203c650(int scene, int link);
extern void func_ov107_020cb100(int effect);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern void func_0203ca30(void *srt, const Vec3 *t);
extern void func_ov107_020c7ca4(char *self);

static inline int ClawPart(char *self, int first)
{
    return first ? *(int *)(self + 0x38c) : **(int **)(self + 0x388);
}

static inline SrtTransform *ClawXf(char *self, int first)
{
    return first ? (SrtTransform *)(*(int *)(self + 0x38c) + 0x10) : (SrtTransform *)(**(int **)(self + 0x388) + 0x10);
}

void func_ov245_020d4ce0(char *self)
{
    Vec3 v;
    int k;
    int part;
    char *xf;

    if (*(signed char *)(self + 0x100 + 0xc6) != 1) {
        if (*(int *)(self + 0x3b8) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3b8));
            *(int *)(self + 0x3b8) = 0;
        }
        if (*(int *)(self + 0x3ac) != 0) {
            func_ov107_020cb100(*(int *)(self + 0x3ac));
            *(int *)(self + 0x3ac) = 0;
        }
    }
    for (k = 0; k < 2; k++) {
        int first = k == 0;

        part = ClawPart(self, first);
        xf = (char *)ClawXf(self, first);
        *(SrtTransform *)xf = *(SrtTransform *)(*(int *)(self + 0x394) + 4);
        func_0202f384(&v, xf, (Vec3 *)(part + 0x64));
        func_01ffa724(*(int *)(part + 0x70), &v, &v);
        VEC_Subtract(xf + 0x10, &v, &v);
        func_0203ca30(xf, &v);
    }
    func_ov107_020c7ca4(self);
}
