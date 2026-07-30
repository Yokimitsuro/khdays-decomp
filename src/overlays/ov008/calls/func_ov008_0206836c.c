/* func_ov008_0206836c -- Ov008_BuildSaveSlotEntry (356 B, 12 relocs).
 * Populates the param_2-th 0x1c-byte menu entry (array at param_1+0x10) for a save slot. Clears
 * the entry, then maps the mode arg to entry->mode (0->1, 2->0, 4->2, else -1). Only mode 0 fills
 * the rest: it runs the Ov008IterFrame list walker (NNS_FndInitList / seed / collect / finalize)
 * to count the visible cells (entry->at2 = count+1), then reads save/game-state fields off
 * data_0204be18 -- *(obj+8), *obj (play time) -- and four GameState_GetField (func_020235d0)
 * queries (ids 9, 0x40a, 0xc4b, 0x44e), with the last stored as (result == 6). The mode arm uses
 * a switch so the compiler lays the four stores out of line (sparse cmp-chain) rather than
 * predicating them inline. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct NNSFndList {
    u16   numObjects;
    u16   offset;
    void *head;
    void *tail;
} NNSFndList;

typedef struct Ov008IterFrame {
    NNSFndList list;   /* 0x000 */
    u8 iter[0x100];    /* 0x00c */
    u8 buffer[0x1e0];  /* 0x10c */
} Ov008IterFrame;

typedef struct MenuEntry {
    u16 at0;     /* 0x00: game-state field 9 */
    u16 at2;     /* 0x02: visible cell count + 1 */
    int at4;     /* 0x04 */
    int at8;     /* 0x08 */
    int atc;     /* 0x0c: play time */
    int mode;    /* 0x10 */
    int at14;    /* 0x14 */
    int at18;    /* 0x18 */
} MenuEntry;

extern char *data_0204be18;
extern void  MI_CpuFill8(void *dst, int v, unsigned int n);
extern void  NNS_FndInitList(NNSFndList *list, int offset);
extern void  func_ov008_020533e4(void *self, int a);
extern void  func_ov008_020536ec(void *self, void *entries, NNSFndList *list, void *ids);
extern void  func_ov008_02053470(void *self, void *entries, NNSFndList *list);
extern void  func_ov008_0205393c(void *self, void *entries, NNSFndList *list);
extern void  WM_EndKeySharing_0x02053464(void *self);
extern int   func_020235d0(int id, int field);

void func_ov008_0206836c(int param_1, int param_2, int param_3)
{
    MenuEntry *entry = &((MenuEntry *)(param_1 + 0x10))[param_2];

    MI_CpuFill8(entry, 0, 0x1c);
    switch (param_3) {
    case 0:
        entry->mode = 1;
        break;
    case 2:
        entry->mode = 0;
        break;
    case 4:
        entry->mode = 2;
        break;
    default:
        entry->mode = -1;
        break;
    }
    if (param_3 != 0) {
        return;
    }
    {
        Ov008IterFrame f;

        NNS_FndInitList(&f.list, 0x28);
        func_ov008_020533e4(f.iter, 0);
        func_ov008_020536ec(f.iter, f.buffer, &f.list, data_0204be18 + 0xee0);
        func_ov008_02053470(f.iter, f.buffer, &f.list);
        entry->at2 = (u16)(*(int *)(f.iter + 0x78) + 1);
        func_ov008_0205393c(f.iter, f.buffer, &f.list);
        WM_EndKeySharing_0x02053464(f.iter);
        entry->at4 = *(int *)(data_0204be18 + 8);
        entry->at0 = (u16)func_020235d0(0, 9);
        entry->atc = *(int *)data_0204be18;
        entry->at8 = func_020235d0(0x40a, 2);
        entry->at18 = func_020235d0(0xc4b, 2);
        entry->at14 = (func_020235d0(0x44e, 3) == 6);
    }
}
