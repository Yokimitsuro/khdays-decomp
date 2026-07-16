/* func_ov236_020d1d98 -- ov236's move dispatcher. Its reset is the most involved of the family: a
 * loop over the two sub-objects at ctx[0]+0x3b0 that sets their visibility from the paired heights
 * at +0x3bc.
 *
 * Per slot:
 *   - bit 0 of the word at +0x3c0 forces bit 1 ON; otherwise a positive height clears it;
 *   - a positive height then sets bit 0, and a non-positive one clears bit 0 and sets bit 1.
 * So bit 1 is "hidden/other" and bit 0 is "shown", and the +0x3c0 flag overrides the height.
 *
 * The heights are SIGNED halfwords (ldrsh) and the +0x3c0 test is a SIGNED one-bit bitfield --
 * `lsl #0x1f ; asrs #0x1f` sign-extends it to 0/-1, which is `int b : 1`, not `unsigned`.
 *
 * Case 8 is out of order (after 11) rather than the usual case 3, and its body carries extra
 * code: it puts bit 0 of +0x1ae back after the reset cleared it. dumpdispatch flagged the body as
 * 28 bytes and I talked myself out of it -- it was right. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

typedef struct {
    char reserved[0x3b0];
    int slots[2];
    int reserved2;
    short heights[2];
    int useAlt : 1;
} Owner;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov236_020d2130(void);
extern void func_ov236_020d21fc(void);
extern void func_ov236_020d225c(void);
extern void func_ov236_020d228c(void);
extern void func_ov236_020d2300(void);
extern void func_ov236_020d2330(void);
extern void func_ov236_020d23e8(void);
extern void func_ov236_020d246c(void);
extern void func_ov236_020d2810(void);
extern void func_ov236_020d2d28(void);
extern void func_ov236_020d32b8(void);
extern void func_ov236_020d3394(void);
extern void func_ov236_020d36e4(void);

void func_ov236_020d1d98(int self) {
    int *ctx;
    int i;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;

        for (i = 0; i < 2; i++) {
            if (((Owner *)ctx[0])->useAlt) {
                ((B8 *)(((Owner *)ctx[0])->slots[i] + 8))->f |= 2;
            } else if (((Owner *)ctx[0])->heights[i] > 0) {
                ((B8 *)(((Owner *)ctx[0])->slots[i] + 8))->f &= ~2;
            }

            if (((Owner *)ctx[0])->heights[i] > 0) {
                ((B8 *)(((Owner *)ctx[0])->slots[i] + 8))->f |= 1;
            } else {
                ((B8 *)(((Owner *)ctx[0])->slots[i] + 8))->f &= ~1;
                ((B8 *)(((Owner *)ctx[0])->slots[i] + 8))->f |= 2;
            }
        }

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov236_020d2130);
            break;
        case 1:
            func_0203c634(self, 1, func_ov236_020d21fc);
            break;
        case 2:
            func_0203c634(self, 1, func_ov236_020d225c);
            break;
        case 3:
            func_0203c634(self, 1, func_ov236_020d228c);
            break;
        case 4:
            func_0203c634(self, 1, func_ov236_020d2300);
            break;
        case 5:
            func_0203c634(self, 1, func_ov236_020d3394);
            break;
        case 6:
            func_0203c634(self, 1, func_ov236_020d36e4);
            break;
        case 7:
            func_0203c634(self, 1, func_ov236_020d2330);
            break;
        case 9:
            func_0203c634(self, 1, func_ov236_020d23e8);
            break;
        case 10:
            func_0203c634(self, 1, func_ov236_020d246c);
            break;
        case 11:
            func_0203c634(self, 1, func_ov236_020d2810);
            break;
        case 8:
            /* Puts back the bit the reset just cleared -- move 8 is the one that needs it. */
            *(unsigned short *)(ctx[0] + 0x1ae) |= 1;
            func_0203c634(self, 1, func_ov236_020d2d28);
            break;
        case 12:
            func_0203c634(self, 1, func_ov236_020d32b8);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
