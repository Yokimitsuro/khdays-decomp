/* Publish a request into its slot of the shared table at *data_ov022_020b2ea4 + 0x14:
 * the 3-word payload goes to slot*0xc + 0x14, the 12-bit value to the parallel
 * 6-byte-stride table at +0x84, and the slot's used-byte at +0x10 is set.
 *
 * The slot and the value are BITFIELDS of the halfword at +2, and that is what the
 * match turns on. mwcc folds `idx & 7` to a single `and #7`, but the ROM emits the
 * shift pair `lsl #0x1d ; lsr #0x1d` and then REUSES the shifted intermediate at the
 * end (`add r0, base, ip lsr #29`); only a real bitfield read keeps that shape. The
 * second field, `(idx << 0x11) >> 0x14`, is the 12 bits above the slot.
 *
 * The last store also has to be written as a subscript on a `char *` base
 * (`((unsigned char *)base + slot)[0x10]`). Spelled as `base + slot + 0x10` mwcc
 * rematerialises the slot instead of reusing the shift, and spelled as
 * `((unsigned char *)(base + 0x10))[slot]` it folds the +0x10 into the wrong operand. */
typedef struct { int a; int b; int c; } Vec3w;

typedef struct {
    unsigned short wField00;
    unsigned short nSlot : 3;
    unsigned short nValue : 12;
} Ov022Request;

extern int data_ov022_020b2ea4;

void func_ov022_02089784(unsigned int *arg0) {
    Ov022Request *req = (Ov022Request *)arg0;
    int base = *(int *)&data_ov022_020b2ea4 + 0x14;
    unsigned int slot = req->nSlot;
    int e = slot * 0xc + base;

    *(unsigned short *)(slot * 6 + base + 0x84) = req->nValue;
    *(Vec3w *)(e + 0x14) = *(Vec3w *)arg0;
    ((unsigned char *)base + slot)[0x10] = 1;
}
