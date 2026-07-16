/* func_ov278_020d1d4c -- ov236's move dispatcher. Its reset is the most involved of the family: a
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
extern void func_ov278_020d20e4(void);
extern void func_ov278_020d21b0(void);
extern void func_ov278_020d2210(void);
extern void func_ov278_020d2240(void);
extern void func_ov278_020d22b4(void);
extern void func_ov278_020d22e4(void);
extern void func_ov278_020d239c(void);
extern void func_ov278_020d2420(void);
extern void func_ov278_020d27c4(void);
extern void func_ov278_020d2cdc(void);
extern void func_ov278_020d326c(void);
extern void func_ov278_020d3348(void);
extern void func_ov278_020d3698(void);

void func_ov278_020d1d4c(int self) {
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
            func_0203c634(self, 1, func_ov278_020d20e4);
            break;
        case 1:
            func_0203c634(self, 1, func_ov278_020d21b0);
            break;
        case 2:
            func_0203c634(self, 1, func_ov278_020d2210);
            break;
        case 3:
            func_0203c634(self, 1, func_ov278_020d2240);
            break;
        case 4:
            func_0203c634(self, 1, func_ov278_020d22b4);
            break;
        case 5:
            func_0203c634(self, 1, func_ov278_020d3348);
            break;
        case 6:
            func_0203c634(self, 1, func_ov278_020d3698);
            break;
        case 7:
            func_0203c634(self, 1, func_ov278_020d22e4);
            break;
        case 9:
            func_0203c634(self, 1, func_ov278_020d239c);
            break;
        case 10:
            func_0203c634(self, 1, func_ov278_020d2420);
            break;
        case 11:
            func_0203c634(self, 1, func_ov278_020d27c4);
            break;
        case 8:
            /* Puts back the bit the reset just cleared -- move 8 is the one that needs it. */
            *(unsigned short *)(ctx[0] + 0x1ae) |= 1;
            func_0203c634(self, 1, func_ov278_020d2cdc);
            break;
        case 12:
            func_0203c634(self, 1, func_ov278_020d326c);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
