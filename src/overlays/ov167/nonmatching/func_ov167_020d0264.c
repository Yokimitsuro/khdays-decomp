/* NONMATCHING: equivalent C, register-naming ties only (count=9 family, 312B).
 * All logic/sizes/offsets are byte-exact EXCEPT scratch-register names:
 * (1) part 2 loads (*(this+0x39c))->4 into r0 (mwcc) vs r1 (orig) for the
 *     `!=0` guard; (2) both 44-byte (11-word) struct copies use mwcc's memcpy
 *     convention dst->lr/src->ip, but the original uses dst->ip/src->lr. No C
 *     reordering (explicit dst-first/src-first pointers, blk as int[11] vs
 *     char[44], statement order) flips mwcc's inline-block-move register roles.
 * Semantics: if (0x1c4&0xa)&&0x1c7==-1 && state not in {0,1,3,0xc} set 0x1c7=0xc;
 * state!=8 && (*0x39c)->4 -> func_0203c650(*0x3c), clear it; state!=9 -> destroy
 * & null the two 0x3a0 slots; state!=8 && 0x3a8 -> destroy & null it; copy 44B
 * (*0x394+4)->(*0x398+0x10) then (*0x398+0x10)->(**0x388+0x10); func_ov107_020c7ca4. */
struct blk { int w[11]; };

struct A {
    char pad0[0x1c4];
    unsigned char f1c4;
    char pad1c5;
    signed char f1c6;
    signed char f1c7;
};

extern void func_0203c650(int p, int v);
extern void func_ov107_020cb100(int p);
extern void func_ov107_020c7ca4(int p);

void func_ov167_020d0264(int this_) {
    struct A *a = (struct A *)this_;
    int i;

    if ((a->f1c4 & 0xa) != 0 && a->f1c7 == -1) {
        int s = a->f1c6;
        if (s != 0 && s != 1 && s != 3 && s != 0xc)
            a->f1c7 = 0xc;
    }

    if (*(signed char *)(this_ + 0x1c6) != 8 &&
        *(int *)(*(int *)(this_ + 0x39c) + 4) != 0) {
        func_0203c650(*(int *)(this_ + 0x3c), *(int *)(*(int *)(this_ + 0x39c) + 4));
        *(int *)(*(int *)(this_ + 0x39c) + 4) = 0;
    }

    if (*(signed char *)(this_ + 0x1c6) != 9) {
        for (i = 0; i < 2; i++) {
            if (((int *)this_)[0xe8 + i] != 0)
                func_ov107_020cb100(((int *)this_)[0xe8 + i]);
            ((int *)this_)[0xe8 + i] = 0;
        }
    }

    if (*(signed char *)(this_ + 0x1c6) != 8 && *(int *)(this_ + 0x3a8) != 0) {
        func_ov107_020cb100(*(int *)(this_ + 0x3a8));
        *(int *)(this_ + 0x3a8) = 0;
    }

    {
        struct blk *pd = (struct blk *)(*(int *)(this_ + 0x398) + 0x10);
        *pd = *(struct blk *)(*(int *)(this_ + 0x394) + 4);
    }
    {
        struct blk *pd = (struct blk *)(*(int *)(*(int *)(this_ + 0x388)) + 0x10);
        *pd = *(struct blk *)(*(int *)(this_ + 0x398) + 0x10);
    }

    func_ov107_020c7ca4(this_);
}
