/* Tick handler of the ov246 enemy. If flagged (+0x1c4 & 0xa) the +0x390 block's +0x24 effect is
 * released and, when idle (+0x1c7 == -1) in sub-state 2, 4, 6 or 7, sub-state 5 is forced.
 * Outside sub-states 6 and 7 the block's +4, +0xc and +0x3c effects and the +0x3a8 / +0x3a4
 * attachments are released. Then the segment from the +0x394 bone's +0x14 to the +0x398
 * bone's +0x14 (unit direction, length, radius 0x1800) is written into the +0x38c item's +0x58
 * and the base tick runs. */
typedef unsigned char u8;
typedef signed char s8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 origin; Vec3 dir; int nLength; int nRadius; } Segment;
typedef struct { char pad[0x58]; Segment seg; } Ov246Item;

extern void func_0203c650(int list, int node);
extern void func_ov107_020cb100(int sub);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c7ca4(int self);

void func_ov246_020d01c4(int self)
{
    Segment seg;

    if ((*(u8 *)(self + 0x1c4) & 0xa) != 0) {
        if (*(int *)(*(int *)(self + 0x390) + 0x24) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390) + 0x24));
            *(int *)(*(int *)(self + 0x390) + 0x24) = 0;
        }
        if (*(s8 *)(self + 0x1c7) == -1) {
            s8 cur = *(s8 *)(self + 0x1c6);
            if (cur == 2 || cur == 4 || (u8)(s8)(cur - 6) <= 1) {
                *(u8 *)(self + 0x1c7) = 5;
            }
        }
    }
    if (*(s8 *)(self + 0x1c6) != 6 && *(s8 *)(self + 0x1c6) != 7) {
        if (*(int *)(*(int *)(self + 0x390) + 4) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390) + 4));
            *(int *)(*(int *)(self + 0x390) + 4) = 0;
        }
        if (*(int *)(*(int *)(self + 0x390) + 0xc) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390) + 0xc));
            *(int *)(*(int *)(self + 0x390) + 0xc) = 0;
        }
        if (*(int *)(*(int *)(self + 0x390) + 0x3c) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390) + 0x3c));
            *(int *)(*(int *)(self + 0x390) + 0x3c) = 0;
        }
        if (*(int *)(self + 0x3a8) != 0) {
            func_ov107_020cb100(*(int *)(self + 0x3a8));
            *(int *)(self + 0x3a8) = 0;
        }
        if (*(int *)(self + 0x3a4) != 0) {
            func_ov107_020cb100(*(int *)(self + 0x3a4));
            *(int *)(self + 0x3a4) = 0;
        }
    }
    seg.nRadius = 0x1800;
    seg.origin = *(Vec3 *)(*(int *)(self + 0x394) + 0x14);
    VEC_Subtract((Vec3 *)(*(int *)(self + 0x398) + 0x14), &seg.origin, &seg.dir);
    seg.nLength = func_01ff8d18(&seg.dir, &seg.dir);
    (*(Ov246Item **)(self + 0x38c))->seg = seg;
    func_ov107_020c7ca4(self);
}
