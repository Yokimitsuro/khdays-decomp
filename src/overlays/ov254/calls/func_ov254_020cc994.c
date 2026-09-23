/* Draw pre-pass of the ov254 actor: effects that outlive their move are finished (the +0x4e4
 * sound outside move 4, the +0x514 / +0x504 effects outside moves 0xa / 7). The pieces follow
 * their parts: +0x3f8 takes the +0x414 part's transform moved 1.05 ahead and 0.44 down and
 * passes it on to the +0x3e4 part; +0x3f4 takes the +0x408 part's transform (on to +0x3e0) and
 * +0x404 the same raised 3.5 (on to +0x3f0). The +0x3fc / +0x400 capsules span the +0x418 ->
 * +0x41c and +0x420 -> +0x424 parts (on to +0x3e8 / +0x3ec). Finally the base pre-pass runs. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[4]; Vec3 trans; int pad[4]; } Srt;
typedef struct { Vec3 a; Vec3 d; int len; int r; } Capsule;
struct Piece { char pad[0x10]; Srt srt; };
struct Part { char pad[4]; Srt srt; };
struct CapPiece { char pad[0x58]; Capsule cap; };

extern void func_ov107_020cb100(int sub);
extern void func_0203c650(void *taskList, void *handle);
extern void func_0202f384(Vec3 *out, const Srt *m, const Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203ca30(Srt *t, const Vec3 *v);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_ov107_020c7ca4(char *self);

void func_ov254_020cc994(char *self)
{
    Srt xf;
    Vec3 off;
    Capsule *cap;

    if (*(signed char *)(self + 0x100 + 0xc6) != 4 && *(int *)(self + 0x4e4) != 0) {
        func_ov107_020cb100(*(int *)(self + 0x4e4));
        *(int *)(self + 0x4e4) = 0;
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 0xa && *(void **)(self + 0x514) != 0) {
        func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x514));
        *(void **)(self + 0x514) = 0;
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 7 && *(void **)(self + 0x504) != 0) {
        func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x504));
        *(void **)(self + 0x504) = 0;
    }
    ((struct Piece *)*(int *)(self + 0x3f8))->srt = ((struct Part *)*(int *)(self + 0x414))->srt;
    off.x = 0;
    off.y = -0x700;
    off.z = 0x10cd;
    func_0202f384(&off, &((struct Part *)*(int *)(self + 0x414))->srt, &off);
    VEC_Add(&((struct Part *)*(int *)(self + 0x414))->srt.trans, &off, &off);
    func_0203ca30(&((struct Piece *)*(int *)(self + 0x3f8))->srt, &off);
    ((struct Piece *)**(int **)(self + 0x3e4))->srt = ((struct Piece *)*(int *)(self + 0x3f8))->srt;
    xf = ((struct Part *)*(int *)(self + 0x408))->srt;
    ((struct Piece *)*(int *)(self + 0x3f4))->srt = xf;
    ((struct Piece *)**(int **)(self + 0x3e0))->srt = ((struct Piece *)*(int *)(self + 0x3f4))->srt;
    xf.trans.y += 0x37ff;
    ((struct Piece *)*(int *)(self + 0x404))->srt = xf;
    ((struct Piece *)**(int **)(self + 0x3f0))->srt = ((struct Piece *)*(int *)(self + 0x404))->srt;
    cap = &((struct CapPiece *)*(int *)(self + 0x3fc))->cap;
    cap->a = *(Vec3 *)(*(int *)(self + 0x418) + 0x14);
    VEC_Subtract((Vec3 *)(*(int *)(self + 0x41c) + 0x14), &cap->a, &cap->d);
    cap->len = func_01ff8d18(&cap->d, &cap->d);
    ((struct CapPiece *)**(int **)(self + 0x3e8))->cap = *cap;
    cap = &((struct CapPiece *)*(int *)(self + 0x400))->cap;
    cap->a = *(Vec3 *)(*(int *)(self + 0x420) + 0x14);
    VEC_Subtract((Vec3 *)(*(int *)(self + 0x424) + 0x14), &cap->a, &cap->d);
    cap->len = func_01ff8d18(&cap->d, &cap->d);
    ((struct CapPiece *)**(int **)(self + 0x3ec))->cap = *cap;
    func_ov107_020c7ca4(self);
}
