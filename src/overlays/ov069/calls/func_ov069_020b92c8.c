#pragma opt_dead_assignments off
#pragma opt_loop_invariants off
/*
 * Ov000_MatchRecipeAndApply -- scan the recipe table for the recipe whose
 * ingredient list is satisfied by the tally in `groups`, then apply its result
 * and per-ingredient bonuses to the panel view.
 *
 * Phase 1 walks recipe entries 0x31..1 (openEntry/closeEntry), checking every
 * ingredient row against the tally with a per-recipe counters[10] usage map.
 * Phase 2 re-walks the matched recipe's 0x18 ingredient rows and folds each
 * matching row's fixed-point bonuses (>>12) into the view, bumping counters.
 *
 * MATCH NOTES (the register-colouring residue took ~200k variants to crack;
 * every element below is load-bearing -- see the commit message):
 *  - `k2 = entry->items[j].id;` is hoisted ABOVE the phase-1 guard: the ROM
 *    loads the id before its compares, and the unconditional def is also what
 *    demotes k2's phase-2 web toward the high callee-saved registers.
 *  - The dead stores `item = 0; j2 = 0; k2 = 0;` at the top never emit code,
 *    but with `#pragma opt_dead_assignments off` their webs order the register
 *    allocator's colouring: later store = deeper demotion, which is the only
 *    lever that reproduces retail's off=r7 / item=r8 / j2=sb / k2=sl split.
 *  - `for (off = j2 = 0; ...)` (j2 assigned first, off copied from it) gives
 *    retail's `mov sb,#0; mov r7,sb` init pair; the reversed chain differs.
 *  - `#pragma opt_loop_invariants off` keeps the phase-1 loop-invariant test
 *    materialisation exactly as retail schedules it.
 *  - `item` must be declared after `j2`.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef short              s16;

typedef struct Ov000RecipeIngredient {
    int id;
    int qty;
    int param;
    int paramB;
    int bonus0;
    int bonus1;
    int bonus2;
    int bonus3;
    int bonusWord;
    int bonus4;
} Ov000RecipeIngredient;

typedef struct Ov000RecipeEntry {
    u8                     pad_0000[0x14];
    int                    result;
    Ov000RecipeIngredient  items[0x18];
} Ov000RecipeEntry;

typedef struct Ov000TallyEntry {
    int id;
    int type;
    int total;
    int count;
    u8  pad_0010[0xcc];
} Ov000TallyEntry;

typedef struct Ov000PanelView {
    u8  pad_0000[0x2c];
    int comboFlag;
    u8  pad_0030[0x44];
    int resultId;
    u8  pad_0078[4];
    int signedBonus0;
    int signedBonus1;
    int signedBonus3;
    int signedBonus2;
    int bonusWord;
    int signedBonus4;
    u8  pad_0094[0x64];
    void (*openEntry)(Ov000RecipeEntry **slot, int type, int index, int mode);
    void (*closeEntry)(Ov000RecipeEntry **slot);
} Ov000PanelView;

extern u8   data_0204c240;
extern int  func_ov069_020b88c0(int out);
extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern int  func_ov069_020b88fc(Ov000TallyEntry *groups);
extern void func_ov069_020b8b98(Ov000PanelView *self, int id, unsigned int qtyA,
                                unsigned int qtyB, int flag);

int func_ov069_020b92c8(Ov000PanelView *self, Ov000TallyEntry *groups, int panelIndex,
                        int *flagsOut) {
    int off;
    int j;
    Ov000RecipeEntry *entry;
    int k;
    Ov000TallyEntry *gw;
    Ov000RecipeEntry *aux;
    int ok;
    u8 *cw;
    Ov000RecipeEntry *found;
    int kind;
    u8  counters[10];
    int ret;
    int k2;
    int j2;
    Ov000RecipeIngredient *item;
    int index;

    entry = 0;
    aux = 0;
    index = 0x31;
    item = 0;
    j2 = 0;
    k2 = 0;
    do {
        (*self->openEntry)(&entry, func_ov069_020b88c0((int)&kind), index, 0xe);
        if (entry != 0) {
            if (entry->items[0].id != groups[0].id) {
                (*self->closeEntry)(&entry);
            } else {
                MI_CpuFill8(counters, 0, 10);
                ok = 1;
                for (j = 0; j < 0x18; j++) {
                    k2 = entry->items[j].id;
                    if ((k2 >= 0 || entry->items[j].param != 0) &&
                        entry->items[j].qty != 0) {
                        for (k = 0; k < 10; k++) {
                            if (groups[k].id >= 0 && k2 == groups[k].id) {
                                if (counters[k] >= groups[k].count) {
                                    ok = 0;
                                } else {
                                    counters[k] = counters[k] + 1;
                                }
                                break;
                            }
                        }
                        if (k == 10) {
                            ok = 0;
                        }
                        if (ok == 0) {
                            break;
                        }
                    }
                }
                if (ok != 0) {
                    break;
                }
                (*self->closeEntry)(&entry);
            }
        }
        index = index - 1;
    } while (index > 0);

    if (flagsOut != 0) {
        *flagsOut = groups[1].id >= 0;
    }
    if (entry == 0) {
        return -1;
    }
    if (kind == 0 || kind == 0x13) {
        self->comboFlag = func_ov069_020b88fc(groups);
        if ((data_0204c240 & 4) != 0 || (data_0204c240 & 8) != 0) {
            self->resultId = self->comboFlag != 0 ? 0 : entry->result;
        } else {
            self->resultId = self->comboFlag != 0 ? 0x27 : entry->result;
        }
    } else {
        self->comboFlag = 0;
        self->resultId = entry->result;
    }

    found = entry;
    ret = found->result;
    if (found->items[0].param != 0) {
        (*self->openEntry)(&aux, 0x13, found->items[0].param, 0xe);
        func_ov069_020b8b98(self, found->items[0].param, found->items[0].paramB, 0, 0);
        (*self->closeEntry)(&aux);
    }
    self->signedBonus0 = self->signedBonus0 + (found->items[0].bonus0 >> 12);
    self->signedBonus1 = self->signedBonus1 + (found->items[0].bonus1 >> 12);
    self->signedBonus2 = self->signedBonus2 + (found->items[0].bonus2 >> 12);
    self->signedBonus3 = self->signedBonus3 + (found->items[0].bonus3 >> 12);
    self->bonusWord = self->bonusWord + found->items[0].bonusWord;
    self->signedBonus4 = self->signedBonus4 + (found->items[0].bonus4 >> 12);

    MI_CpuFill8(counters, 0, 10);
    for (off = j2 = 0; j2 < 0x18; j2++, off += 0x28) {
        if (*(int *)((char *)entry + off + 0x18) >= 0 ||
            *(int *)((char *)entry + off + 0x20) != 0) {
            item = (Ov000RecipeIngredient *)((char *)entry->items + off);
            gw = &groups[1];
            cw = &counters[1];
            for (k2 = 1; k2 < 10; k2++, gw++, cw++) {
                if (gw->id >= 0 && *cw < gw->count && item->id == gw->id) {
                    if (item->param != 0) {
                        (*self->openEntry)(&aux, 0x13, item->param, 0xe);
                        func_ov069_020b8b98(self, item->param, item->paramB, 0, 1);
                        (*self->closeEntry)(&aux);
                    }
                    self->signedBonus0 = self->signedBonus0 +
                        ((item->bonus0 * groups[k2].count) >> 12);
                    self->signedBonus1 = self->signedBonus1 +
                        ((item->bonus1 * groups[k2].count) >> 12);
                    self->signedBonus2 = self->signedBonus2 +
                        ((item->bonus2 * groups[k2].count) >> 12);
                    self->signedBonus3 = self->signedBonus3 +
                        ((item->bonus3 * groups[k2].count) >> 12);
                    self->bonusWord = self->bonusWord +
                        item->bonusWord * groups[k2].count;
                    self->signedBonus4 = self->signedBonus4 +
                        ((item->bonus4 * groups[k2].count) >> 12);
                    counters[k2] = counters[k2] + 1;
                    ret = entry->result;
                    break;
                }
            }
        }
    }
    (*self->closeEntry)(&entry);
    return ret;
}
