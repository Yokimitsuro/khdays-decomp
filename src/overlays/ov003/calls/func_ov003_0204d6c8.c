#pragma opt_strength_reduction off

/* Fill the three-row HUD tile grid for one layout slot. */
typedef struct Ov003Context {
    unsigned char pad_0000[0x17b8];
    unsigned short tilemap[0x18][0x20];
} Ov003Context;

extern Ov003Context *data_ov003_0204f9a0;
extern int func_ov003_0204cadc(int mode);

void func_ov003_0204d6c8(int mode, int palette)
{
    int base;

    base = func_ov003_0204cadc(mode);
    {
        const int start = base + 2;
        unsigned short tile = 0x54;
        int end;
        int column;
        int row = 0;

        mode = palette + 5;
        end = start;
        end += 4;
        do {
            column = start;
            if (column < end) {
                do {
                    unsigned short *dst =
                        &data_ov003_0204f9a0->tilemap[row][column];
                    *dst = tile++ | mode * 0x1000;
                    column++;
                } while (column < end);
            }
            row++;
        } while (row < 3);
    }
}
