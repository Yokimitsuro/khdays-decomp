/* Message handler. 0x21 turns the actor to face its stored heading and hands
 * over to the per-frame step; 0x22 and 0x23 forward the message to the slot
 * dispatcher and hand over to their own steps; anything else is refused.
 *
 * Outside mission mode, bit 8 of the 64-bit field at self+0 FORCES the message
 * to 0x21. Three things make that come out right, all of them the ov049
 * sibling's: the bit test is a 64-bit AND, so the mask lands on the low word
 * and zero on the high one; the returned pointer is initialised to zero before
 * the gate, so the same zero serves as the comparison operand; and the dispatch
 * is a switch, which puts the comparisons and the shared epilogue first.
 *
 * Two things differ from that sibling. The heading is only computed when it is
 * non-zero on either axis, and the vector is copied whole before being
 * flattened rather than assembled field by field.
 *
 * The slots pointer holds the FULL 0x2cb0 offset. That is not an ARM immediate,
 * so the compiler splits it into 0xcb0 plus 0x2000 by itself and hoists the
 * first half above the gate. Splitting it in the source instead -- holding
 * self+0xcb0 and writing blk+0x2000 at each call -- compiles to the same
 * instructions with two registers permuted. Hold the offset the code means,
 * not the encoding.
 */
typedef struct { int x, y, z; } Vec3;

extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern void func_ov030_020b54dc(char *slots, int msg);
extern unsigned char data_0204c240;
extern void func_ov030_020b38a4(void);
extern void func_ov030_020b3e64(void);
extern void func_ov030_020b3e44(void);

void *func_ov030_020b375c(char *self, int msg) {
    void *next = 0;
    char *slots = self + 0x2cb0;
    Vec3 d;
    unsigned short a;
    unsigned int *node;

    if ((data_0204c240 & 4) == 0) {
        if ((*(long long *)self & 0x100) != 0) {
            msg = 0x21;
        }
    }

    switch (msg) {
    case 0x21:
        (*(void (**)(char *, int))(self + 0x664))(self, 0x1b);
        *(int *)(self + 0x58) = 0;
        if (*(int *)(self + 0x47c) != 0 || *(int *)(self + 0x484) != 0) {
            d = *(Vec3 *)(self + 0x7c + 0x400);
            d.y = 0;
            if (VEC_Mag(&d) != 0) {
                func_01ff8d18(&d, &d);
            }
            a = (unsigned short)FX_Atan2(d.x, d.z);
            node = *(unsigned int **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(unsigned short *)((char *)node + 0x80) = a + 0x8000;
                *(unsigned short *)((char *)node + 4) |= 0x20;
            }
        }
        return (void *)&func_ov030_020b38a4;
    case 0x22:
        func_ov030_020b54dc(slots, 0x22);
        return (void *)&func_ov030_020b3e64;
    case 0x23:
        func_ov030_020b54dc(slots, 0x23);
        next = (void *)&func_ov030_020b3e44;
        break;
    }
    return next;
}
