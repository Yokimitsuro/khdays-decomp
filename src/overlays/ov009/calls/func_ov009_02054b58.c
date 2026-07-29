typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov009SummaryRow {
    u8 pad000[0x10];
    int state;
    u8 pad014[4];
    int selectedValue;
} Ov009SummaryRow;

typedef struct Ov009SaveContext {
    u8 pad000[0x14];
    Ov009SummaryRow rows[3];
} Ov009SaveContext;

extern int func_ov009_0204e440(void);
extern int func_ov009_020518fc(int manager, int id);
extern void func_ov009_02051bc4(int manager, int entry, int slot);
extern void func_ov009_02051b08(int manager, int entry, u16 value);
extern void func_ov009_02051a68(int manager, int entry, int visible);
extern const int data_ov009_020560a8[3][8];

void func_ov009_02054b58(Ov009SaveContext *ctx)
{
    int rowIndex;
    u32 itemIndex;
    int manager;
    int entry;
    int itemEntry;
    Ov009SummaryRow *row;

    manager = func_ov009_0204e440();
    rowIndex = 0;
    row = ctx->rows;
    do {
        entry = func_ov009_020518fc(manager, rowIndex + 1);
        func_ov009_02051bc4(manager, entry, 3);
        if (row->state == 1) {
            func_ov009_02051b08(
                manager,
                entry,
                (u16)(*(int *)((u8 *)ctx + 0x2c) + 2)
            );
        } else if (row->state == 2) {
            func_ov009_02051b08(manager, entry, 0);
        } else {
            func_ov009_02051b08(manager, entry, 1);
        }

        itemIndex = 0;
        do {
            itemEntry = func_ov009_020518fc(
                manager,
                data_ov009_020560a8[rowIndex][itemIndex]
            );

            switch (itemIndex) {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                if (row->state == 1) {
                    func_ov009_02051a68(manager, itemEntry, 1);
                } else {
                    func_ov009_02051a68(manager, itemEntry, 0);
                }
                break;
            default:
                func_ov009_02051a68(manager, itemEntry, 1);
                break;
            }
            itemIndex++;
        } while (itemIndex < 8);

        row++;
        ctx = (Ov009SaveContext *)((u8 *)ctx + 0x1c);
        rowIndex++;
    } while (rowIndex < 3);
}
