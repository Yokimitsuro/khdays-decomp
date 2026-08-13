/* Script command: build a module object and file it in a slot.
 *
 * The first two operands give the slot and the kind. The third decides the argument block: when it
 * is zero the block starts blank, otherwise the low halfword and the byte above it come out of the
 * fourth operand word. The last byte is always cleared. The builder turns that into an object and
 * 0207643c stores it.
 *
 * The operand word is read twice on purpose, once for the halfword and once shifted for the byte,
 * which is what the original does; holding it in a local would be one load. The test is written
 * the non-zero way round so the copying arm falls through.
 *
 * Ghidra carries the block as Ov002ModuleSlotArg and the operands as OperandSlot.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

typedef struct {
    u16 wValue;
    u8 bHigh;
    u8 bZero;
} Ov002SlotArg;

extern int func_02021980(void *vm, char *operand);
extern int func_ov002_0207aea0(u16 kind, Ov002SlotArg *arg);
extern void func_ov002_0207643c(int slot, int handle);

int func_ov002_0207d48c(void *vm, char *table) {
    Ov002SlotArg arg;
    int slot = func_02021980(vm, table);
    int kind = func_02021980(vm, table + 8);

    if (*(s16 *)(table + 0x10) != 0) {
        arg.wValue = (u16)*(u32 *)(table + 0x14);
        arg.bHigh = (u8)(*(u32 *)(table + 0x14) >> 16);
    } else {
        arg.wValue = 0;
        arg.bHigh = 0;
    }
    arg.bZero = 0;
    func_ov002_0207643c(slot, func_ov002_0207aea0((u16)kind, &arg));
    return 1;
}
