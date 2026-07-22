/* Accumulate elapsed time into the timer at +0x2c20 and, once it passes 0x384000, either raise
 * the level byte at +0x2c24 by 10 and restart the timer, or -- if the level has already caught
 * up with the current cap (func_020307f4(100)) -- run the two follow-up steps instead.
 *
 * Parked over the addressing split. It is real but it is not a tie: the SAME address is written
 * two ways in the source and mwcc splits each the way it is written. `self[0xb08]` gives
 * (self+0x2000)+0xc20; a pointer built as `(char *)self + 0xc20 + 0x2000` gives the other
 * order, and that pointer is what the level byte and the timer reset go through.
 *
 * The comparison is UNSIGNED and the call is on the LEFT: `cap > level`, not `level < cap`.
 * Written the other way round it comes out as a signed `bge` with the operands swapped. */
extern unsigned int func_020307f4(int scale);
extern void func_ov022_0209be44(int self);
extern void func_ov022_0209bec8(unsigned int *self);

struct Ov022LevelTail {
    unsigned int nTimer;        /* +0x2c20 */
    unsigned char bLevel;       /* +0x2c24 */
};

void func_ov022_0209be64(unsigned int *self, int dt) {
    struct Ov022LevelTail *t = (struct Ov022LevelTail *)((char *)self + 0xc20 + 0x2000);
    unsigned int v = self[0xb08];
    self[0xb08] = v + dt;
    if ((int)(v + dt) < 0x384000) {
        return;
    }
    if (func_020307f4(100) > t->bLevel) {
        t->bLevel += 10;
        t->nTimer = 0;
        return;
    }
    func_ov022_0209be44((int)self);
    func_ov022_0209bec8(self);
}
