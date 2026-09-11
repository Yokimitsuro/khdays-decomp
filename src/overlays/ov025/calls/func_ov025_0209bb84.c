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

extern int func_ov025_02084a7c(void);
extern int func_ov025_0208843c(int manager, int id);
extern void func_ov025_02088a38(int manager, int entry, int slot);
extern void func_ov025_02088928(int manager, int entry, u16 value);
extern void func_ov025_0208884c(int manager, int entry, int visible);
extern const int data_ov025_020b40e8[3][8];

void func_ov025_0209bb84(Ov009SaveContext *ctx)
{
    int rowIndex;
    u32 itemIndex;
    int manager;
    int entry;
    int itemEntry;
    Ov009SummaryRow *row;

    manager = func_ov025_02084a7c();
    rowIndex = 0;
    row = ctx->rows;
    do {
        entry = func_ov025_0208843c(manager, rowIndex + 1);
        func_ov025_02088a38(manager, entry, 3);
        if (row->state == 1) {
            func_ov025_02088928(
                manager,
                entry,
                (u16)(*(int *)((u8 *)ctx + 0x28) + 2)
            );
        } else if (row->state == 2) {
            func_ov025_02088928(manager, entry, 0);
        } else {
            func_ov025_02088928(manager, entry, 1);
        }

        itemIndex = 0;
        do {
            itemEntry = func_ov025_0208843c(
                manager,
                data_ov025_020b40e8[rowIndex][itemIndex]
            );

            switch (itemIndex) {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                if (row->state == 1) {
                    func_ov025_0208884c(manager, itemEntry, 1);
                } else {
                    func_ov025_0208884c(manager, itemEntry, 0);
                }
                break;
            default:
                func_ov025_0208884c(manager, itemEntry, 1);
                break;
            }
            itemIndex++;
        } while (itemIndex < 8);

        row++;
        ctx = (Ov009SaveContext *)((u8 *)ctx + 0x1c);
        rowIndex++;
    } while (rowIndex < 3);
}
