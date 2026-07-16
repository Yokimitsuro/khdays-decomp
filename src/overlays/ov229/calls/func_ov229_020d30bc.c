/* func_ov229_020d30bc -- the move dispatcher: play whatever move was queued at ctx[0]+0x1c7, then
 * clear the slot. This is the hub the whole ov228 state machine funnels through; the choosers
 * (func_ov228_020cf150, ...) park a move id here and this turns it into a c634 entry.
 *
 * -1 means nothing queued and the whole body is skipped -- but the slot is cleared either way,
 * which is why the early exit lands on the same store.
 *
 * Before dispatching, the id is copied to +0x1c6 (that copy, not the original, is what the switch
 * reads), the hw60 hi-byte is cleared of 0xc6, the halfword at +0x1ae drops bits 0-1, and bit 0
 * of the byte field at *(ctx[0]+0x3ac)+8 is set.
 *
 * The cases are dense 0..13, so mwcc builds a real jump table (`addls pc,pc,r1,lsl #2`). Case 3
 * is written out of order -- after case 11 -- because that is the block layout the ROM has; the
 * table is index-ordered but the blocks follow source order, so the position of case 3 is
 * observable. Do not tidy it into numeric order.
 *
 * The hw60 write HAS the `lsl#0x10 ; lsr#0x10` trunc pair, so it takes the bitfield form (see
 * codegen-cracks.md); the field at +8 is a byte-in-word, so it takes the `unsigned f : 8` form. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov229_020d3450(void);
extern void func_ov229_020d3544(void);
extern void func_ov229_020d3850(void);
extern void func_ov229_020d3a1c(void);
extern void func_ov229_020d3f20(void);
extern void func_ov229_020d4540(void);
extern void func_ov229_020d48f0(void);
extern void func_ov229_020d4b90(void);
extern void func_ov229_020d4d6c(void);
extern void func_ov229_020d5064(void);
extern void func_ov229_020d5694(void);
extern void func_ov229_020d5888(void);
extern void func_ov229_020d5970(void);
extern void func_ov229_020d5acc(void);

void func_ov229_020d30bc(int self) {
    int *ctx;
    int move;

    ctx = *(int **)(self + 4);
    move = *(signed char *)(ctx[0] + 0x1c7);
    if (move != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = move;
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov229_020d3450);
            break;
        case 1:
            func_0203c634(self, 1, func_ov229_020d3544);
            break;
        case 2:
            func_0203c634(self, 1, func_ov229_020d3850);
            break;
        case 4:
            func_0203c634(self, 1, func_ov229_020d3a1c);
            break;
        case 5:
            func_0203c634(self, 1, func_ov229_020d3f20);
            break;
        case 6:
            func_0203c634(self, 1, func_ov229_020d4540);
            break;
        case 7:
            func_0203c634(self, 1, func_ov229_020d48f0);
            break;
        case 8:
            func_0203c634(self, 1, func_ov229_020d4b90);
            break;
        case 9:
            func_0203c634(self, 1, func_ov229_020d4d6c);
            break;
        case 10:
            func_0203c634(self, 1, func_ov229_020d5064);
            break;
        case 11:
            func_0203c634(self, 1, func_ov229_020d5694);
            break;
        case 3:
            func_0203c634(self, 1, func_ov229_020d5888);
            break;
        case 12:
            func_0203c634(self, 1, func_ov229_020d5970);
            break;
        case 13:
            func_0203c634(self, 1, func_ov229_020d5acc);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
