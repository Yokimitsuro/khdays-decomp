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
    u8 pad000[0x10];
    Ov009SummaryRow rows[3];
} Ov009SaveContext;

extern int func_ov008_02050c54(void);
extern int func_ov008_02054788(int manager, int id);
extern void func_ov008_02054d90(int manager, int entry, int slot);
extern void func_ov008_02054c80(int manager, int entry, u16 value);
extern void func_ov008_02054ba4(int manager, int entry, int visible);
extern const int data_ov008_0208f588[3][8];

void func_ov008_020697a4(Ov009SaveContext *ctx)
{
    int rowIndex;
    u32 itemIndex;
    int manager;
    int entry;
    int itemEntry;
    Ov009SummaryRow *row;

    manager = func_ov008_02050c54();
    rowIndex = 0;
    row = ctx->rows;
    do {
        entry = func_ov008_02054788(manager, rowIndex + 1);
        func_ov008_02054d90(manager, entry, 3);
        if (row->state == 1) {
            func_ov008_02054c80(
                manager,
                entry,
                (u16)(*(int *)((u8 *)ctx + 0x28) + 2)
            );
        } else if (row->state == 2) {
            func_ov008_02054c80(manager, entry, 0);
        } else {
            func_ov008_02054c80(manager, entry, 1);
        }

        itemIndex = 0;
        do {
            itemEntry = func_ov008_02054788(
                manager,
                data_ov008_0208f588[rowIndex][itemIndex]
            );

            switch (itemIndex) {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                if (row->state == 1) {
                    func_ov008_02054ba4(manager, itemEntry, 1);
                } else {
                    func_ov008_02054ba4(manager, itemEntry, 0);
                }
                break;
            default:
                func_ov008_02054ba4(manager, itemEntry, 1);
                break;
            }
            itemIndex++;
        } while (itemIndex < 8);

        row++;
        ctx = (Ov009SaveContext *)((u8 *)ctx + 0x1c);
        rowIndex++;
    } while (rowIndex < 3);
}
