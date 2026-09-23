/* Item message handler of the ov208 enemy (x3 with ov209/ov268). A kind-0 message, outside owner
 * mode 1, copies its 0x24 flag into bit 1 of the +0x384 sub-item's +0x5c. A "spawned" message
 * (kind 5) attaches the +0x398 pair named by its slot: slots 0/1 anchor it on the +0x38c/+0x390
 * part's +4 point (kind 0x17, flag 1); slots 2/3 take the +0x394 part's +0xa0 transform moved
 * 2.0 along its forward axis. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[4]; Vec3 trans; int pad[4]; } SrtTransform;
struct b2 { int b0 : 1, b1 : 1; };
struct Pair { int res; int handle; };

extern int func_ov107_020c09a0(int model, int res, int kind, void *at, int a, int b);
extern void func_0202f384(Vec3 *out, const SrtTransform *m, const Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203ca30(SrtTransform *t, const Vec3 *v);
extern int func_ov107_020c0794(int model, int res, int kind, int zero, SrtTransform *t);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov208_020d39d8(char *self, u8 *msg, int arg)
{
    SrtTransform t;
    Vec3 v;

    if (msg[2] == 0) {
        if (*(int *)(self + 0x50) != 1) {
            ((struct b2 *)(*(int *)(self + 0x384) + 0x5c))->b1 = msg[0x24];
        }
    } else if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
        case 1:
            ((struct Pair *)(self + 0x398))[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Pair *)(self + 0x398))[msg[3]].res, 0x17,
                                    (msg[3] == 0 ? (void *)(*(int *)(self + 0x38c) + 4) : (void *)(*(int *)(self + 0x390) + 4)), 0, 1);
            break;
        case 2:
        case 3:
            t = *(SrtTransform *)(*(int *)(self + 0x394) + 0xa0);
            v.x = 0;
            v.y = 0;
            v.z = 0x2000;
            func_0202f384(&v, &t, &v);
            VEC_Add(&v, &t.trans, &v);
            func_0203ca30(&t, &v);
            ((struct Pair *)(self + 0x398))[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Pair *)(self + 0x398))[msg[3]].res, 0x17, 0, &t);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
