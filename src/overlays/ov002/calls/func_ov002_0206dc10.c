/* Answer whether the active module knows a key.
 *
 * Bit 1 of the global byte disables the query outright. Otherwise the module id
 * is a signed byte in the root context, resolved to a slot, and the key looked
 * up in that slot; a non-negative lookup answers 1.
 *
 * The nesting below is what the ROM's address arithmetic says the original
 * source had: it builds the pointer as base + 0x17c, then + 0x8c00, and leaves
 * + 6 in the load displacement. Those are three member boundaries, not an
 * arbitrary split -- writing the byte as one flat field at +0x8d82 instead
 * compiles to base + 0x8d00 with 0x82 in the displacement, which is one
 * instruction short and in the wrong place.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[6];
    signed char cModuleId;      /* +0x06 */
} Ov002ModuleEntry;

typedef struct {
    u8 pad0000[0x8c00];
    Ov002ModuleEntry entry;     /* +0x8c00 */
} Ov002ModuleTable;

typedef struct {
    u8 pad0000[0x17c];
    Ov002ModuleTable table;     /* +0x17c */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern u8 data_0204c240;

extern int func_ov002_02076468(int nModuleId);
extern int func_ov002_0207a23c(int nSlot, int nKey);

int func_ov002_0206dc10(int nKey) {
    Ov002ModuleEntry *pEntry = &data_ov002_0207fa00->table.entry;
    int nSlot;

    if ((data_0204c240 & 2) != 0) {
        return 0;
    }
    nSlot = func_ov002_02076468(pEntry->cModuleId);
    if (nSlot == 0) {
        return 0;
    }
    return func_ov002_0207a23c(nSlot, nKey) >= 0;
}
