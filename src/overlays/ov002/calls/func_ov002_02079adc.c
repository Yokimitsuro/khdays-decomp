/* func_ov002_02079adc -- rebind the actor model, cache the descriptor's "two-sided" bit and
 * pick the matching draw mode.
 * Binds the model resource for the actor's slot id (self[0x10]) into the renderer block at
 * +0x1c, then reads bit 0 of the descriptor flags for (id at +0x14, kind at +0x16) into the
 * two-sided flag at +0x1c2, and sets the draw mode at +0x1ce to 0 when it is set and 2 when
 * it is not.
 *
 * The two field offsets are one MUTATED index, not two constants: 0x1c2 is past the THUMB
 * immediate range so it lives in a register, and the ROM reaches 0x1ce by adding 0xc to it
 * (`adds r0,#0xc`). Any spelling that names 0x1ce -- directly, as 0x1c2 + 0xc, through a
 * pointer, or through a read-only index variable -- makes mwcc reload the second constant
 * from the pool and costs four bytes. */
extern int func_ov002_0207285c(int slot);
extern int func_020235d0(unsigned short id, unsigned char kind);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern void func_ov002_020798a0(void *self);

void func_ov002_02079adc(char *self) {
    func_0202ba9c(self + 0x1c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    {
        int off = 0x1c2;

        self[off] = (char)((unsigned int)((func_020235d0(*(unsigned short *)(self + 0x14),
                      (unsigned char)self[0x16]) & 0xfffe) << 0xf) >> 0x10 & 1);
        if (*(unsigned char *)(self + off) == 1) {
            off = off + 0xc;
            self[off] = 0;
        } else {
            off = off + 0xc;
            self[off] = 2;
        }
    }
    func_ov002_020798a0(self);
}
