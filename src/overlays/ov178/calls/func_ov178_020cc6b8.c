/* Tick handler of the ov178 enemy (x3: ov178/179/180). If flagged (+0x1c4 & 0xa) and idle
 * (+0x1c7 == -1) and the current sub-state (+0x1c6) is not 0, 1, 3 or 12, force sub-state 12.
 * Unless in sub-state 8 the first effect of the +0x39c set is released, unless in 9 its two
 * others (+0x1c/+0x24) and the two +0x3a0 slots, and unless in 8 the +0x3a8 slot. Then the
 * 44-byte placement of +0x394 (+4) is copied into the +0x398 frame (+0x10) and from there into
 * the pool's first node (+0x10); finally the base tick runs.
 * The copies write their DESTINATION as a struct field through a typed pointer: that is what
 * puts the destination in ip and the source in lr (a cast destination gets the opposite; the
 * source spelling does not matter -- cf. func_ov119_020cbfc4). */
typedef struct { int w[11]; } Placement;
typedef struct { int pad; Placement placement; } Source;            /* +0x394 */
typedef struct { char pad[0x10]; Placement placement; } Frame;      /* +0x398 and the pool node */

extern void func_0203c650(int list, int node);
extern void func_ov107_020cb100(int sub);
extern void func_ov107_020c7ca4(int obj);

void func_ov178_020cc6b8(int self)
{
    int i;
    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0 &&
        *(signed char *)(self + 0x1c7) == -1) {
        signed char cur = *(signed char *)(self + 0x1c6);
        if (cur != 0 && cur != 1 && cur != 3 && cur != 0xc) {
            ((signed char *)self)[0x1c7] = 0xc;
        }
    }
    if (*(signed char *)(self + 0x1c6) != 8 && *(int *)(*(int *)(self + 0x39c) + 4) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x39c) + 4));
        *(int *)(*(int *)(self + 0x39c) + 4) = 0;
    }
    if (*(signed char *)(self + 0x1c6) != 9) {
        if (*(int *)(*(int *)(self + 0x39c) + 0x1c) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x39c) + 0x1c));
            *(int *)(*(int *)(self + 0x39c) + 0x1c) = 0;
        }
        if (*(int *)(*(int *)(self + 0x39c) + 0x24) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x39c) + 0x24));
            *(int *)(*(int *)(self + 0x39c) + 0x24) = 0;
        }
    }
    if (*(signed char *)(self + 0x1c6) != 9) {
        for (i = 0; i < 2; i++) {
            if (((int *)self)[0xe8 + i] != 0) {
                func_ov107_020cb100(((int *)self)[0xe8 + i]);
                ((int *)self)[0xe8 + i] = 0;
            }
        }
    }
    if (*(signed char *)(self + 0x1c6) != 8 && *(int *)(self + 0x3a8) != 0) {
        func_ov107_020cb100(*(int *)(self + 0x3a8));
        *(int *)(self + 0x3a8) = 0;
    }
    {
        Frame *frame = *(Frame **)(self + 0x398);
        Source *src = *(Source **)(self + 0x394);
        frame->placement = src->placement;
    }
    {
        Frame *node = *(Frame **)*(int *)(self + 0x388);
        Frame *frame = *(Frame **)(self + 0x398);
        node->placement = frame->placement;
    }
    func_ov107_020c7ca4(self);
}
