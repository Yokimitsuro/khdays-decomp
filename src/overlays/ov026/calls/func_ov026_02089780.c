#pragma opt_dead_assignments off

typedef signed short s16;
typedef unsigned char u8;

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
extern int func_ov026_02085d7c(int *manager, unsigned int kind, int label, int x, ...);
extern Ov026WidgetEntry *func_ov026_0208427c(void *panel, int id);
extern int func_ov026_02084374(void *panel, Ov026WidgetEntry *cell);
extern void func_ov026_02084330(void *panel, Ov026WidgetEntry *cell, int value);
extern void func_ov026_02084488(void *panel, Ov026WidgetEntry *cell, int flag);

void func_ov026_02089780(void) {
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
        rows[i + 1] = func_ov026_02085d7c(handle, (unsigned int)cell,
                                          ((Ov026StatsState *)state)->rowLabel,
                                          0x30000, (top + 0x20) << 0xc);
        rows[i + 5] = func_ov026_02085d7c(handle, 8, 1,
                                          0x25000, (top + 0x24) << 0xc);
    }

    cell = func_ov026_0208427c(panelBase->widgetPanel, 6);
    func_ov026_02084330(panelBase->widgetPanel, cell,
                       func_ov026_02084374(panelBase->widgetPanel, cell));
    func_ov026_02084488(panelBase->widgetPanel, cell, 0);
}
