#pragma opt_dead_assignments off
#pragma opt_loop_invariants off
/*
 * Ov008_MatchRecipeAndApply -- ov008 variant of Ov008_MatchRecipeAndApply
 * (func_ov000_020573e4): identical recipe-matching flow minus the
 * data_0204c240 result-override block. See that file for the full
 * explanation of the register-colouring levers (hoisted id load, the
 * dead-store demotion ladder under #pragma opt_dead_assignments off, the
 * `off = j2 = 0` init chain, and `item` declared after `j2`).
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef short              s16;

typedef struct Ov008RecipeIngredient {
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
} Ov008RecipeIngredient;

typedef struct Ov008RecipeEntry {
    u8                     pad_0000[0x14];
    int                    result;
    Ov008RecipeIngredient  items[0x18];
} Ov008RecipeEntry;

typedef struct Ov008TallyEntry {
    int id;
    int type;
    int total;
    int count;
    u8  pad_0010[0xcc];
} Ov008TallyEntry;

typedef struct Ov008PanelView {
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
    void (*openEntry)(Ov008RecipeEntry **slot, int type, int index, int mode);
    void (*closeEntry)(Ov008RecipeEntry **slot);
} Ov008PanelView;

extern int  func_ov008_02051b20(int out);
extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern int  func_ov008_02051b5c(Ov008TallyEntry *groups);
extern void func_ov008_02051df8(Ov008PanelView *self, int id, unsigned int qtyA,
                                unsigned int qtyB, int flag);

int func_ov000_020573e4(Ov008PanelView *self, Ov008TallyEntry *groups, int panelIndex,
                        int *flagsOut) {
    int off;
    int j;
    Ov008RecipeEntry *entry;
    int k;
    Ov008TallyEntry *gw;
    Ov008RecipeEntry *aux;
    int ok;
    u8 *cw;
    Ov008RecipeEntry *found;
    int kind;
    u8  counters[10];
    int ret;
    int k2;
    int j2;
    Ov008RecipeIngredient *item;
    int index;

    entry = 0;
    aux = 0;
    index = 0x31;
    item = 0;
    j2 = 0;
    k2 = 0;
    do {
        (*self->openEntry)(&entry, func_ov008_02051b20((int)&kind), index, 0xe);
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
        self->comboFlag = func_ov008_02051b5c(groups);
        self->resultId = self->comboFlag != 0 ? 0 : entry->result;
    } else {
        self->comboFlag = 0;
        self->resultId = entry->result;
    }

    found = entry;
    ret = found->result;
    if (found->items[0].param != 0) {
        (*self->openEntry)(&aux, 0x13, found->items[0].param, 0xe);
        func_ov008_02051df8(self, found->items[0].param, found->items[0].paramB, 0, 0);
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
            item = (Ov008RecipeIngredient *)((char *)entry->items + off);
            gw = &groups[1];
            cw = &counters[1];
            for (k2 = 1; k2 < 10; k2++, gw++, cw++) {
                if (gw->id >= 0 && *cw < gw->count && item->id == gw->id) {
                    if (item->param != 0) {
                        (*self->openEntry)(&aux, 0x13, item->param, 0xe);
                        func_ov008_02051df8(self, item->param, item->paramB, 0, 1);
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
