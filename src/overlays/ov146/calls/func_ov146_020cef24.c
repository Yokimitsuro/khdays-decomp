/* Update of the ov146 actor: in phase 1, while the effect shows (+0x38c), every live, unshielded entity
 * of the owner's scene list (other than the owner and its +0x3b8 partner) within 48.0 of the owner is
 * marked (+0x1c5 bit 4); when the effect state changes to off the marks clear. The +0x38c state is
 * remembered in +0x390 and the base update runs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;

extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c6980(void *obj, int arg2);

void func_ov146_020cef24(char *self, int arg)
{
    if (*(int *)(self + 0x50) == 1) {
        int grid = *(int *)(*(int *)(self + 0x388) + 4);
        int *it;
        char *e;
        Vec3 d;

        if (*(int *)(self + 0x38c) != 0) {
            it = func_01fffd70((void *)(grid + 0x80));
            e = it == 0 ? 0 : (char *)*it;
            while (e != 0) {
                char *owner = *(char **)(self + 0x388);

                if (e != owner && e != *(char **)(owner + 0x3b8) && (((flags16 *)(e + 0x60))->lo & 1) &&
                    !(*(u16 *)(e + 0x1ac) & 6)) {
                    VEC_Subtract((Vec3 *)(owner + 0x74), (Vec3 *)(e + 0x74), &d);
                    if (func_01ff8d18(&d, &d) <= 0x30000) {
                        *(u8 *)(e + 0x1c5) |= 0x10;
                    }
                }
                it = func_01fffd8c((void *)(grid + 0x80));
                e = it == 0 ? 0 : (char *)*it;
            }
        }
        if (*(int *)(self + 0x38c) != *(int *)(self + 0x390)) {
            if (*(int *)(self + 0x38c) == 0) {
                it = func_01fffd70((void *)(grid + 0x80));
                e = it == 0 ? 0 : (char *)*it;
                while (e != 0) {
                    char *owner = *(char **)(self + 0x388);

                    if (e != owner && e != *(char **)(owner + 0x3b8)) {
                        *(u8 *)(e + 0x1c5) &= ~0x10;
                    }
                    it = func_01fffd8c((void *)(grid + 0x80));
                    e = it == 0 ? 0 : (char *)*it;
                }
            }
            *(int *)(self + 0x390) = *(int *)(self + 0x38c);
        }
    }
    func_ov107_020c6980(self, arg);
}
