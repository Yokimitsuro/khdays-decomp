/* Write a pair of halfwords into the display slot an object resolves to, on the local machine only.
 *
 * The object carries a packed key at 0x2d0. Its high byte picks a record in the array at context
 * +0x44, 0x18 bytes apiece, whose signed byte at 0x14 picks a list in the table at context +4. The
 * low byte of the key then indexes that list, four bytes an entry past a one-word header, and the
 * signed byte it finds picks a slot in the 0x10-byte array at the second table entry. The two
 * halfwords land at 0xa and 0xc of that slot.
 *
 * Ghidra carries the chain as Ov002SlotRecord, Ov002SlotList, Ov002SlotListEntry and
 * Ov002DisplaySlot.
 *
 * Two things the original codegen turns on. The third parameter is unused but must stay, or the
 * fourth moves into the wrong argument register. And the table pointer is declared before the key,
 * which is what settles the two into the registers the original uses.
 */

typedef unsigned short u16;
typedef unsigned int u32;

extern char *data_ov002_0207fa14;
extern short func_02030788(void);

void func_ov002_02073094(char *object, u16 first, int unused, u16 second) {
    char *ctx = data_ov002_0207fa14;

    if (func_02030788() == 0) {
        char *tables = *(char **)(ctx + 4);
        u32 key = *(u32 *)(object + 0x2d0);
        char *records = *(char **)(ctx + 0x44);
        int slot = *(signed char *)(records + ((key >> 8) & 0xff) * 0x18 + 0x14);
        char *list = *(char **)(tables + slot * 4 + 8);
        int index = *(signed char *)(list + (key & 0xff) * 4 + 4);
        char *entry = *(char **)(tables + 4) + index * 0x10;

        *(u16 *)(entry + 0xa) = first;
        *(u16 *)(entry + 0xc) = second;
    }
}
