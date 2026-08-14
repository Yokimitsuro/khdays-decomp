#pragma opt_strength_reduction off

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 cell[0x20];
} Ov003TileRow;

typedef struct {
    u8 pad_0000[2];
    u8 rowType_0002[8];
    u16 stat_000a[8][4];
    u8 pad_004a[0x17b8 - 0x4a];
    Ov003TileRow tileRows_17b8[24];
    u8 pad_1db8[8];
    u16 *sourceTilemap_1dc0;
} Ov003Context;

extern Ov003Context *data_ov003_0204f9a0;
extern void func_02013484(u16 *a0, u16 *a1, int a2, int a3, int a4,
                          int a5, int a6, int a7, int a8, int a9);
extern int func_ov003_0204cadc(int mode);
extern void func_ov003_0204d1c0(u16 *dst, u32 value);
extern void func_ov003_0204d264(u16 *dst, u32 value, int palette);

void func_ov003_0204d3b0(int row) {
    int i;
    int off = func_ov003_0204cadc(row);
    int col;
    int j;
    u16 tile;

    func_02013484(data_ov003_0204f9a0->tileRows_17b8[0].cell,
                  data_ov003_0204f9a0->sourceTilemap_1dc0, 0, 0, off,
                  3, 0x20, 0x18, 8, 0x12);

    data_ov003_0204f9a0->tileRows_17b8[3].cell[off + 1] =
        data_ov003_0204f9a0->tileRows_17b8[3].cell[off + 1] & 0xf000 |
        (data_ov003_0204f9a0->rowType_0002[row] * 2 + 1);
    data_ov003_0204f9a0->tileRows_17b8[3].cell[off + 2] =
        data_ov003_0204f9a0->tileRows_17b8[3].cell[off + 2] & 0xf000 |
        (data_ov003_0204f9a0->rowType_0002[row] * 2 + 2);

    i = 0;
    col = 0xc;
    do {
        if (i == 0) {
            func_ov003_0204d1c0(&data_ov003_0204f9a0->tileRows_17b8[12].cell[off + 2],
                                data_ov003_0204f9a0->stat_000a[row][0]);
        } else {
            func_ov003_0204d264(&data_ov003_0204f9a0->tileRows_17b8[col].cell[off + 4],
                                data_ov003_0204f9a0->stat_000a[row][i], 0xb);
        }
        i++;
        col += 2;
    } while (i < 4);

    tile = row * 0x24 + 0x100;
    j = 0;
    do {
        int k = 0;
        do {
            ((Ov003TileRow *)((u8 *)data_ov003_0204f9a0 + 0x18ba))[j].cell[off + k] =
                tile | (row + 1) * 0x1000;
            tile++;
            k++;
        } while (k < 6);
        j++;
    } while (j < 6);
}
