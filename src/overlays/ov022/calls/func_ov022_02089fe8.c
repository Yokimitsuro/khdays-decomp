/* func_ov022_02089fe8 -- publish one slot of the shared table and remember the request handle.
 * The table lives at +0x14 of the block held in data_ov022_020b2ea4. A slot is only published
 * when its handle is still 0xffff (free) and the input layer is idle (func_02030788). The
 * six-byte marshalling record carries the value, the kind byte, a random tag byte and the slot
 * index in a 3-bit field; func_02031384 hands it off and returns the handle to store back.
 *
 * The park called this an "address-CSE tie": the ROM recomputes `tbl + idx*2` for the guard and
 * again for the final store, where mwcc held it in one register and came out 4 bytes short. The
 * cause was not CSE -- it was that the table was modelled as an `int` plus hand-written byte
 * offsets. With `tbl += 0x14` and raw offsets, mwcc folds 0x14 into every immediate, keeps the
 * PRE-increment pointer live across the call and rebuilds `+0x14` afterwards, which costs a fifth
 * callee-saved register (the ROM pushes {r3,r4,r5,r6,r7,lr}, we pushed r8 as well).
 * Modelling the table as a struct of parallel arrays and indexing it -- `t->seq[idx]`,
 * `t->values[idx]`, `t->b08[idx]` -- gives the ROM's addressing for free: one base register,
 * `t + idx` shared by the two byte stores, and the `add rX, t, idx lsl #1` pair rematerialised
 * around the call exactly where the ROM has them. */
extern int func_02030788(void);
extern int func_02023eb4(int max);
extern int func_02031384(int a, void *buf, int c);
extern int data_ov022_020b2ea4;

struct Buf02089fe8 {
    unsigned short w0;
    unsigned char b2;
    unsigned char b3;
    unsigned char lo3 : 3;
    unsigned char mid3 : 3;   /* the slot index */
    unsigned char hi2 : 2;
    unsigned char pad5;
};

typedef struct {
    unsigned short values[4];              /* +0x00 */
    unsigned char  b08[4];                 /* +0x08 */
    unsigned char  b0c[4];                 /* +0x0c */
    char           pad10[0x9c - 0x10];
    unsigned short seq[4];                 /* +0x9c, 0xffff = slot free */
} Ov022Table;

void func_ov022_02089fe8(int idx, unsigned short param_2, unsigned char param_3) {
    int base = *(int *)&data_ov022_020b2ea4;
    struct Buf02089fe8 buf;
    Ov022Table *t;

    if (base == 0) return;
    if (func_02030788() != 0) return;

    t = (Ov022Table *)(base + 0x14);
    if (t->seq[idx] != 0xffff) return;

    buf.mid3 = idx;
    buf.w0 = param_2;
    buf.b2 = param_3;
    buf.b3 = (unsigned char)func_02023eb4(0xff);
    buf.lo3 = 0;

    t->values[idx] = param_2;
    t->b08[idx] = param_3;
    t->b0c[idx] = buf.b3;
    t->seq[idx] = (short)func_02031384(0xf, &buf, 6);
}
