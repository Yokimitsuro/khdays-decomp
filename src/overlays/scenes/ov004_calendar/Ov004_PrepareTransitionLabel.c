/* Draws the label of the target day when it has one (marking it unavailable otherwise). */

#include "nitro/types.h"

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
extern void *Ov004_GetVarRecordByIndex(Ov004LabelRecords *table, int index);
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void Text_DrawDirectional(void *self, int x, int y, int style, unsigned flags, const u16 *text);
extern int Text_UploadTileBuffer(Ov004LabelTiles *self);

void Ov004_PrepareTransitionLabel(void)
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
    Text_FormatUtf16(labelBuffer, 128, data_ov004_0205136c,
        Ov004_GetVarRecordByIndex(&data_ov004_02051384->labelRecords, found));
    Text_DrawDirectional(&data_ov004_02051384->labelTiles, 128, 18, 1, 0x10, labelBuffer);
    Text_UploadTileBuffer(&data_ov004_02051384->labelTiles);
    data_ov004_02051384->labelReady = 1;
}
