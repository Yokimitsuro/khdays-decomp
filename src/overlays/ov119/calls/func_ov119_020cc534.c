/* Tick handler of the ov119 enemy (x3 with ov272/ov279). A flagged (+0x1c4 & 0xa), idle (+0x1c7 ==
 * -1) enemy outside sub-states 0, 1, 3, 4 and 0xb is forced into sub-state 4. Outside sub-state 7
 * the +0x3a8 block's +0x24 effect and the +0x3b0 reaction are released, outside 0xa its +0x1c
 * effect, and outside 9/0xa its +0x14 effect and the +0x3a4 effect are released and the +0x384
 * rig is shown (bit 1 of +0x5c cleared). The block's first item is shown in sub-states 5/6 and
 * hidden otherwise; a +0x3ac grab is let go (ov022 020ad8e0) outside sub-state 0xa. Then the
 * segment from the +0x39c bone's +0x14 to the +0x3a0 bone's +0x14 (unit direction, length, radius
 * 0x240) is written into the +0x38c item's and the +0x388 part's +0x58 and the base tick runs. */
typedef unsigned char u8;
typedef signed char s8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 origin; Vec3 dir; int nLength; int nRadius; } Segment;
typedef struct { char pad[0x58]; Segment seg; } Ov119Item;

extern void func_0203c650(int list, int node);
extern void func_ov107_020cb100(int sub);
extern void func_ov022_020ad8e0(int partner, int flag);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c7ca4(int self);

void func_ov119_020cc534(int self)
{
    Segment seg;

    if ((*(u8 *)(self + 0x1c4) & 0xa) != 0 && *(s8 *)(self + 0x1c7) == -1) {
        s8 cur = *(s8 *)(self + 0x1c6);
        if (cur != 0 && cur != 1 && cur != 3 && cur != 4 && cur != 0xb) {
            ((signed char *)self)[0x1c7] = 4;
        }
    }
    if (*(s8 *)(self + 0x1c6) != 7) {
        if (*(int *)(*(int *)(self + 0x3a8) + 0x24) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3a8) + 0x24));
            *(int *)(*(int *)(self + 0x3a8) + 0x24) = 0;
        }
        if (*(int *)(self + 0x3b0) != 0) {
            func_ov107_020cb100(*(int *)(self + 0x3b0));
            *(int *)(self + 0x3b0) = 0;
        }
    }
    if (*(s8 *)(self + 0x1c6) != 0xa && *(int *)(*(int *)(self + 0x3a8) + 0x1c) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3a8) + 0x1c));
        *(int *)(*(int *)(self + 0x3a8) + 0x1c) = 0;
    }
    if (*(s8 *)(self + 0x1c6) != 9 && *(s8 *)(self + 0x1c6) != 0xa) {
        if (*(int *)(*(int *)(self + 0x3a8) + 0x14) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3a8) + 0x14));
            *(int *)(*(int *)(self + 0x3a8) + 0x14) = 0;
        }
        if (*(int *)(self + 0x3a4) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3a4));
            *(int *)(self + 0x3a4) = 0;
        }
        *(int *)(*(int *)(self + 0x384) + 0x5c) &= ~2;
    }
    if (*(s8 *)(self + 0x1c6) == 5) {
        *(int *)(**(int **)(self + 0x3a8) + 0x5c) &= ~2;
    } else if (*(s8 *)(self + 0x1c6) == 6) {
        *(int *)(**(int **)(self + 0x3a8) + 0x5c) &= ~2;
    } else {
        *(int *)(**(int **)(self + 0x3a8) + 0x5c) |= 2;
    }
    if (*(int *)(self + 0x3ac) != 0 && *(s8 *)(self + 0x1c6) != 0xa) {
        func_ov022_020ad8e0(*(int *)(self + 0x3ac), 0);
        *(int *)(self + 0x3ac) = 0;
    }
    seg.nRadius = 0x240;
    seg.origin = *(Vec3 *)(*(int *)(self + 0x39c) + 0x14);
    VEC_Subtract((Vec3 *)(*(int *)(self + 0x3a0) + 0x14), &seg.origin, &seg.dir);
    seg.nLength = func_01ff8d18(&seg.dir, &seg.dir);
    (*(Ov119Item **)(self + 0x38c))->seg = seg;
    (**(Ov119Item ***)(self + 0x388))->seg = seg;
    func_ov107_020c7ca4(self);
}
