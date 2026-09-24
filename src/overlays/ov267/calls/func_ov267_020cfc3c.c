/* Bone callback of the ov266 serpent rig: each probed bone (02016320) drives a part.
 * - Bone +0x58c: its point goes to +0x508, the +0xa0 transform is copied to +0x520 and moved to the
 *   point 2.0 behind the +0xa0 transform.
 * - Bone +0x598: the +0xa0 transform is copied to +0x54c at the bone; with bone +0x59c too, the two
 *   +0x4d8 / *+0x4cc parts aim from the first bone to the second (direction +0x64, point 1.5 along
 *   it at +0x58, reach +0x70 = distance - 3.0).
 * - Bones +0x5a0 / +0x5a4 place the +0x10 transforms of the *+0x4d0 / +0x4dc and *+0x4d4 / +0x4e0 parts.
 * While in mode 1 with the +0x3c8 object's bit 1 clear, bone +0x590 roots the sixteen-segment tail:
 * each segment points from the running point towards the +0x4f0 target (height quartered), its yaw
 * limited to 0x86 per link, and once a link folds back past the first one the rest keeps the last
 * orientation; the +0x3cc orientations ease towards it (rate +0x580 growing along the tail), the
 * +0x38c segment transforms take the point, the orientation and the +0x57c length, and the point
 * walks to the next link. The tail end goes to the +0x5d4 object, whose +0xc hook runs when bit 1
 * of its +0x40 flags is set.
 * Codegen: built with `opt_common_subs off` (push/pop scoped) and `obj` declared before the tail
 * locals; with CSE on the tail loop's i/seg registers swap (r8/r6). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { int m[9]; Vec3 t; } Mtx43;
typedef struct { int x, y, z, w; } Quat;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int b0 : 1; int b1 : 1; } Flag2;
struct Ov266 {
    char pad000[0x38c];
    int segs[16];           /* +0x38c */
    Quat quats[16];         /* +0x3cc */
};

extern int func_02016320(int a, Mtx43 *out, int b, int bone);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void func_0203ca30(void *srt, const Vec3 *t);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern int func_01ff8d18(const Vec3 *v, void *out);
extern void func_01ffa724(int scale, const void *v, void *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern int func_020050b4(int x, int z);
extern int func_ov267_020cfc08(int a, int b);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202f55c(Quat *out, int t, Quat *a, Quat *b);
extern void func_0203c9d0(void *srt, Quat *q);
extern void func_0203ca50(void *srt, int x, int y, int z);
extern void func_0203cc64(Vec3 *out, void *srt, void *in);
extern void func_ov107_020c5c54(int obj, Vec3 *v);
extern const short data_0203d210[];
extern const Vec3 data_02042258;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

#pragma push
#pragma opt_common_subs off
void func_ov267_020cfc3c(int rig, char *self)
{
    Mtx43 probe;
    Vec3 first;
    Vec3 pos;
    Quat quat;
    Quat saved;
    Vec3 root;
    Vec3 span;
    Vec3 dir;
    Mtx33 mtx;
    int k;
    int part;
    int len;
    int obj;
    int i;
    int blocked;
    int weight;
    int ang;
    int prev;
    int seg;

    if (func_02016320(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x58c)) != 0) {
        *(Vec3 *)(self + 0x508) = probe.t;
        *(SrtTransform *)(self + 0x520) = *(SrtTransform *)(self + 0xa0);
        pos.x = 0;
        pos.y = 0;
        pos.z = -0x2000;
        func_0202f384(&pos, self + 0xa0, &pos);
        VEC_Add(&pos, self + 0xb0, &pos);
        func_0203ca30(self + 0x520, &pos);
    }
    if (func_02016320(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x598)) != 0) {
        root = probe.t;
        *(SrtTransform *)(self + 0x54c) = *(SrtTransform *)(self + 0xa0);
        func_0203ca30(self + 0x54c, &root);
        if (func_02016320(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x59c)) != 0) {
            VEC_Subtract(&probe.t, &root, &span);
            for (k = 0; k < 2; k++) {
                part = k == 0 ? *(int *)(self + 0x4d8) : **(int **)(self + 0x4cc);
                len = func_01ff8d18(&span, (void *)(part + 0x64));
                func_01ffa724(0x1800, (void *)(part + 0x64), (void *)(part + 0x58));
                VEC_Add((void *)(part + 0x58), &root, (void *)(part + 0x58));
                *(int *)(part + 0x70) = len - 0x3000;
            }
        }
    }
    if (func_02016320(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x5a0)) != 0) {
        func_0203ca30((void *)(**(int **)(self + 0x4d0) + 0x10), &probe.t);
        func_0203ca30((void *)(*(int *)(self + 0x4dc) + 0x10), &probe.t);
    }
    if (func_02016320(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x5a4)) != 0) {
        func_0203ca30((void *)(**(int **)(self + 0x4d4) + 0x10), &probe.t);
        func_0203ca30((void *)(*(int *)(self + 0x4e0) + 0x10), &probe.t);
    }
    if (*(int *)(self + 0x50) != 1) {
        return;
    }
    if (((Flag2 *)(*(int *)(self + 0x3c8) + 0x5c))->b1) {
        return;
    }
    if (func_02016320(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x590)) == 0) {
        return;
    }
    blocked = 0;
    pos = probe.t;
    for (i = 0; i < 16; i++) {
        seg = ((struct Ov266 *)self)->segs[i];
        weight = *(int *)(self + 0x580) + i * (*(int *)(self + 0x580) * 5) / 16;
        VEC_Subtract(self + 0x4f0, &pos, &dir);
        dir.y = dir.y * 0x400 / 0x1000;
        func_01ff8d18(&dir, &dir);
        if (i == 0) {
            first = dir;
        }
        if (blocked != 0 || (i != 0 && VEC_DotProduct(&dir, &first) <= 0)) {
            blocked = 1;
            quat = saved;
        } else {
            ang = func_020050b4(dir.x, dir.z);
            if (i != 0) {
                int diff = func_ov267_020cfc08(ang, prev);

                if ((diff < 0 ? -diff : diff) >= 0x86) {
                    unsigned int idx;

                    ang = diff > 0x86 ? prev + 0x86 : prev - 0x86;
                    idx = ANG2IDX(ang);
                    dir.x = 0;
                    dir.z = 0x1000;
                    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
                    MTX_MultVec33(&dir, &mtx, &dir);
                }
            }
            prev = ang;
            func_0202ed60(&quat, &data_02042258, &dir);
            saved = quat;
        }
        func_0202f55c(&quat, weight, &((struct Ov266 *)self)->quats[i], &quat);
        ((struct Ov266 *)self)->quats[i] = quat;
        func_0203ca30((void *)(seg + 0x30), &pos);
        func_0203c9d0((void *)(seg + 0x30), &quat);
        func_0203ca50((void *)(seg + 0x30), 0x1000, 0x1000, *(int *)(self + 0x57c));
        func_0203cc64(&pos, (void *)(seg + 0x30), self + 0x4fc);
    }
    func_ov107_020c5c54(*(int *)(self + 0x5d4), &pos);
    obj = *(int *)(self + 0x5d4);
    if (((Flag2 *)(obj + 0x40))->b1 && *(void (**)(int, int))(obj + 0xc) != 0) {
        (*(void (**)(int, int))(obj + 0xc))(obj, 0);
    }
}

#pragma pop
