/* Creates the label and value cells of the four stat rows and places the panel widget. */

#pragma opt_dead_assignments off

#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x7000];
    u8 widgetPanel[0x4a84];
} Ov026StatsPanel;

typedef struct {
    u8 pad_0000[0x0e];
    s16 rowLabel;
    u8 pad_0010[0x530 - 0x10];
    Ov026StatsPanel panel;
    int *manager;
    u8 pad_bfb8[0xc4f4 - 0xbfb8];
    int rowCells[9];
} Ov026StatsState;

typedef struct Ov026WidgetEntry Ov026WidgetEntry;

extern char *data_ov026_02091368;
extern int Ov026_CreateMissionCell(int *mgr, unsigned int res, int slot, int xform, ...);
extern Ov026WidgetEntry *Ov026_FindEntryById(void *panel, int id);
extern int Ov026_GetEntryBlock2c(void *panel, Ov026WidgetEntry *cell);
extern void Ov026_ReleaseTwoSlotsEx(void *panel, Ov026WidgetEntry *cell, int value);
extern void Ov026_ReleaseTwoSlotsEx_2(void *panel, Ov026WidgetEntry *cell, int flag);

void Ov026_Stats_CreateRowCells(void) {
    Ov026StatsPanel *panelBase;
    Ov026WidgetEntry *cell;
    int top;
    int *rows;
    int *handle;
    int i;
    char *state;

    cell = 0;
    rows = 0;
    handle = 0;
    i = 0;
    state = 0;
    top = 0;
    state = *(char **)&data_ov026_02091368;
    rows = ((Ov026StatsState *)state)->rowCells;
    panelBase = &((Ov026StatsState *)state)->panel;
    handle = ((Ov026StatsState *)state)->manager;
    for (i = 0; i < 4; i++) {
        top = (i + 1) << 4;
        rows[i + 1] = Ov026_CreateMissionCell(handle, (unsigned int)cell,
                                          ((Ov026StatsState *)state)->rowLabel,
                                          0x30000, (top + 0x20) << 0xc);
        rows[i + 5] = Ov026_CreateMissionCell(handle, 8, 1,
                                          0x25000, (top + 0x24) << 0xc);
    }

    cell = Ov026_FindEntryById(panelBase->widgetPanel, 6);
    Ov026_ReleaseTwoSlotsEx(panelBase->widgetPanel, cell,
                       Ov026_GetEntryBlock2c(panelBase->widgetPanel, cell));
    Ov026_ReleaseTwoSlotsEx_2(panelBase->widgetPanel, cell, 0);
}
