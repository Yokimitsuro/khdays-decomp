/* Script opcode: take an item from the player. Operands: item id and amount. Ids outside
 * 1..0x3ff are ignored. The free stock is the +0x810 count minus one per slot of the three
 * 40-entry +0xee0 rows holding the id; the amount is subtracted while it fits, otherwise the
 * stock is emptied. */
typedef unsigned char u8;
typedef unsigned short u16;

extern int func_02021980(void *vm, unsigned short *pc);
extern char *data_0204be18;

int func_ov069_020b8604(void *vm, unsigned short *pc)
{
    int id;
    u16 count;
    int i;
    int j;
    char *row;
    u16 amount;

    id = func_02021980(vm, pc);
    if (id > 0 && id >= 0x400) {
        return 1;
    }
    row = data_0204be18;
    count = *(u8 *)(row + id + 0x810);
    for (i = 0; i < 3; i++) {
        j = 0;
        {
            char *slot = row;
            for (; j < 0x28; j++) {
                if (id == *(u16 *)(slot + 0xee0) && count != 0) {
                    count--;
                }
                slot += 2;
            }
        }
        row += 0x50;
    }
    amount = func_02021980(vm, pc + 4);
    if (count > amount) {
        *(u8 *)(data_0204be18 + 0x810 + id) -= amount;
    } else {
        *(u8 *)(data_0204be18 + id + 0x810) = 0;
    }
    return 1;
}
