/* Whether item `id` (below 0x400) is still available: its +0x810 stock count in the save
 * block minus one for every slot of the three 40-entry +0xee0 rows that already holds it. */
typedef unsigned char u8;
typedef unsigned short u16;

extern char *data_0204be18;

int func_ov069_020b8378(unsigned int id)
{
    u16 count;
    int i;
    int j;
    char *row;

    if (id >= 0x400) {
        return 0;
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
    return count != 0;
}
