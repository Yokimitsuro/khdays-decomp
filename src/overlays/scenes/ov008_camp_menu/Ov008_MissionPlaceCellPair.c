/* Places the slot's two cells at the offset its selector maps to, or off screen when the selector
 * is out of range. */

#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} MissionOffset;

typedef struct {
    MissionOffset entries[19];
} MissionOffsetTable;

typedef struct {
    int x;
    int y;
    int cell;
    int keep;
} MissionPlacementConfig;

typedef struct {
    u8 pad_0000[0x4a8c];
    u8 panel;
    u8 pad_4a8d[0x4b21];
    s8 offset_map[19];
    u8 pad_95c1[0x123];
    int primary_cells[4];
    int secondary_cells[4];
} Ov006RootContext;

extern const MissionOffsetTable data_ov008_0208fdc8;
extern Ov006RootContext *data_ov008_02090fa4;
extern void Ov008_MissionPlaceCell(void *panel, int idx, MissionPlacementConfig config);

void Ov008_MissionPlaceCellPair(int slot, int selector) {
    MissionPlacementConfig config = {0, 0, 0, 0};
    MissionOffsetTable offsets = data_ov008_0208fdc8;

    if (selector == -1 || selector >= 19) {
        config.x = -48;
        config.y = -128;
    } else {
        s8 mapped = data_ov008_02090fa4->offset_map[selector];

        if (mapped != 20) {
            config.x = offsets.entries[mapped].x;
            config.y = offsets.entries[mapped].y;
        } else {
            config.x = -48;
            config.y = -128;
        }
    }

    config.cell = 0;
    config.keep = 1;
    Ov008_MissionPlaceCell(&data_ov008_02090fa4->panel,
                         data_ov008_02090fa4->primary_cells[slot],
                         config);
    config.keep = 1;
    Ov008_MissionPlaceCell(&data_ov008_02090fa4->panel,
                         data_ov008_02090fa4->secondary_cells[slot],
                         config);
}
