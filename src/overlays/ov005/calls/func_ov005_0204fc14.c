/* func_ov005_0204fc14 -- lay out one panel entry and evaluate the group it forms.
 *
 * Called once per entry by RebuildViewAndCountCells (func_ov000_0205836c), which hands it
 * the 5x8 cell-pointer block of that entry's panel (0xa0 bytes) and the entry's view node.
 * The node describes where the item sits: cursorX/cursorY is the anchor cell, originX/originY
 * the top-left of its footprint, width/height the footprint box, and node->mask a 64-bit
 * shape mask, one bit per footprint cell, row stride 8.
 *
 * Pass 1 seeds group 0 from the anchor cell (its id, type, the four value slots) and records
 * the anchor's coordinate.  Pass 2 walks the footprint: every set mask bit marks the cell in
 * the panel's own 64-bit occupancy mask (self->cellMask[panelIndex], row stride 5), and every
 * footprint cell other than the anchor that actually holds an item gets tallied.  How it is
 * tallied depends on the anchor's type: type 4 only counts identical ids into the first free
 * of ten groups, everything else matches by type-1-vs-id, adds the coordinate to that group's
 * list and, for group 0 only, runs the value tally (func_ov005_0204f49c or 02057138).  A cell
 * that matches no existing group takes the first group whose id is still negative.
 *
 * The tail picks the evaluator by the anchor's type -- 4 goes to func_ov005_0204f7a8, 6 to
 * func_ov005_0204f1ec, everything else to func_ov005_0204f5e0, with bit 0 of node->flags set
 * when that last one succeeds.  Byte-identical in ov004/005/008/009/025/069.
 *
 * CODEGEN NOTE -- four shapes are load-bearing, and the last one is the interesting one.
 *  - The row counter has to be the SAME variable `i` the two setup loops use.  A separate `y`
 *    is a whole live range of its own and gets its stack slot before the compiler's temporaries;
 *    reusing `i` splits the range in three, so the row copy is spilled last and lands in the
 *    ROM's slot.  Nothing else about the function changes -- this was the final 23 bytes.
 *  - `entries` must be declared before `coords`: mwcc lays stack objects out in reverse
 *    declaration order.
 *  - The coordinate must be taken with a post-increment subscript (`&coords[n++]`).  Split into
 *    `cp = &coords[n]; n = n + 1;` mwcc decides `n` is an induction variable and strength-reduces
 *    the whole thing into a walking pointer, which the ROM does not do.
 *  - `slot = -1` has to come after the two coordinate stores, and the tail has to be written as
 *    `if (type != 4) { ...; return; } <type 4>` so the type-4 block lands at the end of the
 *    function the way the ROM has it.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef short              s16;
typedef unsigned long long u64;

typedef struct NNSFndLink {
    void *prev;
    void *next;
} NNSFndLink;

typedef struct NNSFndList {
    void *head;
    void *tail;
    u16   numObjects;
    u16   offset;
} NNSFndList;

typedef struct Ov000TallySlot {
    int a;
    u16 b;
    u16 c;
} Ov000TallySlot;

typedef struct Ov000TallyEntry {
    int             id;
    int             type;
    int             total;
    int             count;
    NNSFndList      list;
    Ov000TallySlot  slots[4];
    u8              pad_003c[0xa0];
} Ov000TallyEntry;

typedef struct Ov000TallyCoord {
    s16        x;
    s16        y;
    NNSFndLink link;
    u8         pad_000c[4];
} Ov000TallyCoord;

typedef struct Ov000GridCell {
    u8             pad_0000[0x18];
    int            type;
    u8             pad_001c[6];
    s16            id;
    u8             pad_0024[0x10];
    Ov000TallySlot slots[4];
} Ov000GridCell;

typedef struct Ov000ViewMask {
    u8  pad_0000[0x10];
    u64 bits;
} Ov000ViewMask;

typedef struct Ov000ViewNode {
    u8             pad_0000[4];
    int            flags;
    u16            matched;
    u16            panelIndex;
    u16            originX;
    u16            originY;
    u16            cursorX;
    u16            cursorY;
    u16            width;
    u16            height;
    int            resultA;
    int            resultB;
    u8             pad_0020[4];
    Ov000ViewMask *mask;
} Ov000ViewNode;

typedef struct Ov000PanelView {
    u8  pad_0000[0xcc];
    u64 cellMask[3];
} Ov000PanelView;

extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern void NNS_FndInitList(void *list, u16 offset);
extern void NNS_FndAppendListObject(void *list, void *obj);
extern void func_ov005_0204f49c(void *self, Ov000TallyEntry *entry, Ov000GridCell *cell);
extern void func_ov005_0204f4fc(void *self, Ov000TallyEntry *entry, Ov000GridCell *cell,
                                int flag);
extern void func_ov005_0204f1ec(void *self, Ov000TallyEntry *entries);
extern int  func_ov005_0204f5e0(void *self, Ov000TallyEntry *entries, int panelIndex);
extern int  func_ov005_0204f7a8(void *self, Ov000TallyEntry *entries, int panelIndex,
                                int *flags);

void func_ov005_0204fc14(Ov000PanelView *self, Ov000GridCell **grid, Ov000ViewNode *node,
                         int panel) {
    Ov000GridCell *cell;
    int i;
    int x;
    int slot;
    Ov000GridCell *other;
    int k;
    Ov000TallyCoord *cp;
    int n;
    int row;
    int match;
    Ov000TallyEntry entries[10];
    Ov000TallyCoord coords[10];

    cell = grid[node->cursorX + node->cursorY * 5];
    node->flags = 0;
    node->matched = 0;
    n = 0;
    slot = 1;
    MI_CpuFill8(coords, 0, 0xa0);

    for (i = 0; i < 10; i++) {
        MI_CpuFill8(&entries[i], 0, 0xdc);
        entries[i].id = -1;
        NNS_FndInitList(&entries[i].list, 4);
    }

    entries[0].id = cell->id;
    entries[0].type = cell->type;
    entries[0].count = 1;
    for (i = 0; i < 4; i++) {
        entries[0].slots[i].a = cell->slots[i].a;
        entries[0].slots[i].b = cell->slots[i].b;
        entries[0].slots[i].c = cell->slots[i].c;
    }
    if (cell->type == 1) {
        func_ov005_0204f49c(self, &entries[0], cell);
    } else {
        func_ov005_0204f4fc(self, &entries[0], cell, 0);
    }

    coords[0].x = node->cursorX;
    coords[0].y = node->cursorY;
    n = n + 1;
    NNS_FndAppendListObject(&entries[0].list, &coords[0]);

    for (i = 0; i < node->height; i++) {
        for (x = 0; x < node->width; x++) {
            if ((node->mask->bits & (1ULL << (x + i * 8))) != 0) {
                self->cellMask[node->panelIndex] |=
                    1ULL << (node->originX + x + (node->originY + i) * 5);
                row = node->originY + i;
                if (node->cursorY != row || node->cursorX != node->originX + x) {
                    other = grid[node->originX + (x + row * 5)];
                    if (other != 0) {
                        node->matched = node->matched + 1;
                        if (entries[0].type == 4) {
                            for (k = 0; k < 10; k++) {
                                if (entries[k].id == other->id) {
                                    entries[k].count = entries[k].count + 1;
                                    break;
                                }
                            }
                            if (k == 10) {
                                entries[slot].id = other->id;
                                entries[slot].type = other->type;
                                entries[slot].count = 1;
                                slot = slot + 1;
                            }
                        } else if (other->id >= 0) {
                            cp = &coords[n++];
                            cp->x = node->originX + x;
                            cp->y = node->originY + i;
                            slot = -1;
                            for (k = 0; k < 10; k++) {
                                if (entries[k].type == 1) {
                                    match = other->type == 1;
                                } else {
                                    match = other->id == entries[k].id;
                                }
                                if (match) {
                                    entries[k].count = entries[k].count + 1;
                                    if (k == 0) {
                                        if (entries[0].type == 1) {
                                            func_ov005_0204f49c(self, &entries[k], other);
                                        } else {
                                            func_ov005_0204f4fc(self, &entries[k], other, 1);
                                        }
                                    }
                                    NNS_FndAppendListObject(&entries[k].list, cp);
                                    break;
                                }
                                if (slot == -1 && entries[k].id < 0) {
                                    slot = k;
                                }
                            }
                            if (k == 10) {
                                entries[slot].id = other->id;
                                entries[slot].type = other->type;
                                entries[slot].total = entries[slot].total + other->slots[0].b;
                                entries[slot].count = 1;
                                if (other->type == 1) {
                                    func_ov005_0204f49c(self, &entries[slot], other);
                                } else {
                                    func_ov005_0204f4fc(self, &entries[slot], other, 0);
                                }
                                NNS_FndAppendListObject(&entries[slot].list, cp);
                            }
                        }
                    }
                }
            }
        }
    }

    if (entries[0].type != 4) {
        if (entries[0].type == 6) {
            func_ov005_0204f1ec(self, entries);
            node->resultA = -1;
            node->resultB = -1;
            return;
        }
        if (entries[0].count > 1) {
            node->flags = 1;
            func_ov005_0204f1ec(self, entries);
        }
        node->resultA = -1;
        node->resultB = func_ov005_0204f5e0(self, entries, node->panelIndex);
        if (node->resultB < 0) {
            return;
        }
        node->flags |= 1;
        return;
    }
    node->resultB = -1;
    node->resultA = func_ov005_0204f7a8(self, entries, node->panelIndex, &node->flags);
}
