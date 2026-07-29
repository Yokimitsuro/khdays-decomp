typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov009PageCursor {
    u8 pad000[0x14];
    u16 quantity;
    u8 pad016[6];
    int signedValue;
    u8 pad020[4];
    int state;
    int availability;
} Ov009PageCursor;

extern Ov009PageCursor *func_ov009_0204e4a8(void);
extern int func_ov009_02054e18(int part, int quantity);
extern void func_ov009_02054cac(int tag, int value);
extern const int data_ov009_020560a8[3][8];

void func_ov009_02054558(void)
{
    int parts[3] = {0, 0, 0};
    Ov009PageCursor *page = func_ov009_0204e4a8();
    int rowIndex = 0;

    do {
        if (page->state == 1) {
            int partIndex;
            int quantity = page->quantity;

            if (quantity > 999) {
                quantity = 999;
            }

            partIndex = 0;
            do {
                parts[partIndex] = func_ov009_02054e18(partIndex, quantity);
                partIndex++;
            } while (partIndex < 3);

            func_ov009_02054cac(data_ov009_020560a8[rowIndex][5], parts[0]);
            func_ov009_02054cac(data_ov009_020560a8[rowIndex][6], parts[1]);
            func_ov009_02054cac(data_ov009_020560a8[rowIndex][7], parts[2]);
            func_ov009_02054cac(data_ov009_020560a8[rowIndex][4], page->signedValue);
            func_ov009_02054cac(
                data_ov009_020560a8[rowIndex][3],
                -(page->availability == 0)
            );
        }

        rowIndex++;
        page = (Ov009PageCursor *)((u8 *)page + 0x1c);
    } while (rowIndex < 3);
}
