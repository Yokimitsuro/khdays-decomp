/* func_ov000_02057dc4 -- fold one panel into the running tally.
 *
 * RebuildViewAndCountCells (func_ov000_0205836c) calls this once per panel, after every
 * entry has been laid out, with that panel's 5x8 cell-pointer block, the 64-bit mask of
 * cells already accounted for, and an out-mask to fill in.
 *
 * It walks the 8 rows and 5 columns; a cell that is present and not already covered gets
 * its bit set in the out-mask and is folded in by type: type 0 hands the cell's payload to
 * func_ov000_02056b18, type 1 pushes each of the four non-empty value slots through
 * func_ov000_02056bac, and types 3, 5 and 6 push them through func_ov000_02056cb4 and then
 * add the cell's seven per-stat bonuses.  Every type -- including 2, 4 and anything out of
 * range -- then adds the cell's thirteen totals into the accumulator and clamps all
 * fourteen to 0x64000 (100.0 in the 12-bit fixed point these use).
 *
 * CODEGEN NOTE -- three shapes are load-bearing.
 *  - The guard on each value slot has to be a `volatile` read through a byte-offset row
 *    pointer, exactly the way the sibling func_ov000_02057138 does it.  The ROM loads the
 *    slot twice, once to test and once as the argument, and mwcc CSEs the pair away
 *    otherwise; `volatile` on the guard alone is a codegen device, not a claim about the
 *    field.  It also has to keep 0x34 as a per-access displacement -- folding it into the
 *    base turns the loop into a walking pointer and costs another register.
 *  - `row` must be initialised before `base` (hence the comma in the for-init).  mwcc emits
 *    the pair as `first = 0; second = first;`, so whichever the source sets first is the one
 *    that gets the literal store, and the two ended up in each other's stack slots.
 *  - Declaration order slotRow, row, col, base, i, cell is the one of 720 that colours the
 *    rest of the frame the ROM's way.
 *
 * Byte-identical in ov004/005/008/009/025/069.
 */
typedef unsigned char      u8;
typedef signed char        s8;
typedef unsigned short     u16;
typedef short              s16;
typedef unsigned long long u64;

typedef struct Ov000TallySlot {
    int a;
    u16 b;
    u16 c;
} Ov000TallySlot;

typedef struct Ov000GridCell {
    u8             pad_0000[0x14];
    int            param;
    int            type;
    u8             pad_001c[6];
    s16            id;
    u8             pad_0024[6];
    u8             bonusU;
    s8             bonusA;
    s8             bonusB;
    s8             bonusC;
    s8             bonusD;
    s8             bonusE;
    int            bonusWord;
    Ov000TallySlot slots[4];
    int            stats[13];
} Ov000GridCell;

typedef struct Ov000PanelView {
    u8  pad_0000[0x78];
    int unsignedBonus;
    int signedBonus0;
    int signedBonus1;
    int signedBonus3;
    int signedBonus2;
    int bonusWord;
    int signedBonus4;
    int stats[14];
    u64 cellMask[3];
} Ov000PanelView;

extern void func_ov000_02056b18(Ov000PanelView *self, int payload, int enabled, int reserved);
extern void func_ov000_02056bac(Ov000PanelView *self, int value, int reserved0, int enabled,
                                int reserved1);
extern void func_ov000_02056cb4(Ov000PanelView *self, int value, unsigned int tallyA,
                                unsigned int tallyB, int reserved);

void func_ov000_02057dc4(Ov000PanelView *self, Ov000GridCell **grid, u64 covered, u64 *out) {
    char *slotRow;
    int row;
    int col;
    int base;
    int i;
    Ov000GridCell *cell;

    for (row = 0, base = 0; row < 8; row++) {
        for (col = 0; col < 5; col++) {
            cell = grid[base + col];
            if (cell != 0 && (covered & (1ULL << (col + base))) == 0) {
                *out |= 1ULL << (col + base);
                switch (cell->type) {
                case 0:
                    func_ov000_02056b18(self, cell->param, 1, 0);
                    break;
                case 1:
                    for (i = 0; i < 4; i++) {
                        slotRow = (char *)cell + i * sizeof(Ov000TallySlot);
                        if (*(int volatile *)(slotRow + 0x34) != 0) {
                            func_ov000_02056bac(self, *(int *)(slotRow + 0x34), 0, 1, 0);
                        }
                    }
                    break;
                case 3:
                case 5:
                case 6:
                    for (i = 0; i < 4; i++) {
                        slotRow = (char *)cell + i * sizeof(Ov000TallySlot);
                        if (*(int volatile *)(slotRow + 0x34) != 0) {
                            func_ov000_02056cb4(self, *(int *)(slotRow + 0x34),
                                                *(u16 *)(slotRow + 0x38),
                                                *(u16 *)(slotRow + 0x3a), 0);
                        }
                    }
                    self->unsignedBonus = self->unsignedBonus + cell->bonusU;
                    self->signedBonus0 = self->signedBonus0 + cell->bonusA;
                    self->signedBonus1 = self->signedBonus1 + cell->bonusB;
                    self->signedBonus3 = self->signedBonus3 + cell->bonusD;
                    self->signedBonus2 = self->signedBonus2 + cell->bonusC;
                    self->bonusWord = self->bonusWord + cell->bonusWord;
                    self->signedBonus4 = self->signedBonus4 + cell->bonusE;
                    break;
                }
                self->stats[0] = self->stats[0] + cell->stats[0];
                self->stats[1] = self->stats[1] + cell->stats[1];
                self->stats[2] = self->stats[2] + cell->stats[2];
                self->stats[3] = self->stats[3] + cell->stats[3];
                self->stats[4] = self->stats[4] + cell->stats[4];
                self->stats[5] = self->stats[5] + cell->stats[5];
                self->stats[6] = self->stats[6] + cell->stats[6];
                self->stats[7] = self->stats[7] + cell->stats[7];
                self->stats[8] = self->stats[8] + cell->stats[8];
                self->stats[9] = self->stats[9] + cell->stats[9];
                self->stats[10] = self->stats[10] + cell->stats[10];
                self->stats[11] = self->stats[11] + cell->stats[11];
                self->stats[12] = self->stats[12] + cell->stats[12];
                for (i = 0; i < 14; i++) {
                    if (self->stats[i] > 0x64000) {
                        self->stats[i] = 0x64000;
                    }
                }
            }
        }
        base = base + 5;
    }
}
