/* Sweep the entity list on the manager at *(*self+4)+0xa8 and answer 1 as soon as one
 * live, targetable entity (bits 1 and 2 of *(e+0x40), bit 0 of the low byte at e+0x60)
 * sits inside self's six-plane bounding box and within *(self+0x28) + *(e+0x80) of
 * self's position at self+0x1c. Answer 0 if the list runs out. */
struct flags16 { unsigned short lo : 8; unsigned short hi : 8; };
struct flags32 { int bit0 : 1; int live : 1; int targetable : 1; };

extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern void VEC_Subtract(int *a, int *b, int *out);
extern int VEC_Mag(const int *v);

int func_ov107_020cb2dc(int self)
{
    int mgr = *(int *)(*(int *)self + 4);
    int *pe = func_01fffd70(mgr + 0xa8);
    int e = (pe == 0) ? 0 : *pe;

    while (e != 0) {
        struct flags32 *flags = (struct flags32 *)(e + 0x40);

        if (flags->live &&
            flags->targetable &&
            (((struct flags16 *)(e + 0x60))->lo & 1) != 0 &&
            *(int *)(self + 0x38) >= *(int *)(e + 0x84) &&
            *(int *)(self + 0x2c) <= *(int *)(e + 0x90) &&
            *(int *)(self + 0x3c) >= *(int *)(e + 0x88) &&
            *(int *)(self + 0x30) <= *(int *)(e + 0x94) &&
            *(int *)(self + 0x40) >= *(int *)(e + 0x8c) &&
            *(int *)(self + 0x34) <= *(int *)(e + 0x98)) {
            int mag;
            int dir[3];

            VEC_Subtract((int *)(self + 0x1c), (int *)(e + 0x74), dir);
            mag = VEC_Mag(dir);
            if (mag <= *(int *)(self + 0x28) + *(int *)(e + 0x80)) {
                return 1;
            }
        }
        pe = func_01fffd8c(mgr + 0xa8);
        e = (pe == 0) ? 0 : *pe;
    }
    return 0;
}
