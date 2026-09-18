/* Marks game flag 0x20e1 according to whether the current item id (2021980) occupies any slot
 * of the save block's three 40-entry +0xee0 rows: set when found, cleared otherwise. Always 1. */
typedef unsigned short u16;

extern int func_02021980(void);
extern void func_020235a8(int flag);
extern void func_020235bc(int flag);
extern char *data_0204be18;

int func_ov069_020b8698(void)
{
    int id;
    int i;
    int j;
    char *row;

    id = func_02021980();
    row = data_0204be18;
    for (i = 0; i < 3; i++) {
        j = 0;
        {
            char *slot = row;
            for (; j < 0x28; j++) {
                if (id == *(u16 *)(slot + 0xee0)) {
                    func_020235a8(0x20e1);
                    return 1;
                }
                slot += 2;
            }
        }
        row += 0x50;
    }
    func_020235bc(0x20e1);
    return 1;
}
