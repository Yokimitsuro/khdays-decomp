typedef unsigned short u16;
typedef struct { void *resource; unsigned count; unsigned char *records; } Ov004LabelRecords;
typedef struct { unsigned char opaque[64]; } Ov004LabelTiles;
typedef struct {
    unsigned char opaque0000[0x5554];
    int labelUnavailable;
    unsigned char opaque5558[0x34];
    Ov004LabelRecords labelRecords;
    int labelId;
    int labelReady;
    unsigned char opaque55a0[12];
    Ov004LabelTiles labelTiles;
} Ov004Context;
extern Ov004Context *data_ov004_02051384;
extern int data_ov004_020510cc[68];
extern u16 data_ov004_0205136c[];
extern void *func_ov004_0204caf8(Ov004LabelRecords *table, int index);
extern void func_020262a0(u16 *buffer, unsigned capacity, const u16 *format, ...);
extern void func_0202fa38(void *self, int x, int y, int style, unsigned flags, const u16 *text);
extern int func_0202f9f8(Ov004LabelTiles *self);

void func_ov004_02050a04(void)
{
    u16 labelBuffer[128];
    int found = -1;
    unsigned i;
    for (i = 0; i < 68; i++) {
        if (data_ov004_02051384->labelId == data_ov004_020510cc[i])
            found = i;
    }
    if (found < 0)
        data_ov004_02051384->labelUnavailable = 1;
    if (data_ov004_02051384->labelReady != 0)
        return;
    if (found < 0)
        return;
    func_020262a0(labelBuffer, 128, data_ov004_0205136c,
        func_ov004_0204caf8(&data_ov004_02051384->labelRecords, found));
    func_0202fa38(&data_ov004_02051384->labelTiles, 128, 18, 1, 0x10, labelBuffer);
    func_0202f9f8(&data_ov004_02051384->labelTiles);
    data_ov004_02051384->labelReady = 1;
}
