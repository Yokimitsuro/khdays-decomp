typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 bytes[1];
} MissionCellList;

typedef struct {
    u8 pad_000[8];
    MissionCellList cell_list;
} Ov006RootContext;

extern Ov006RootContext *data_ov008_02090fa4;
extern void *func_ov008_02055808(MissionCellList *list, u16 tag);
extern void func_ov008_02055874(MissionCellList *list, void *cell, int x, int y);
extern void func_ov008_0205589c(MissionCellList *list, void *cell);

void func_ov008_0207fa4c(u32 tag, int x, int y) {
    void *cell;

    cell = func_ov008_02055808(&data_ov008_02090fa4->cell_list, tag);
    func_ov008_02055874(&data_ov008_02090fa4->cell_list, cell, x, y);
    cell = func_ov008_02055808(&data_ov008_02090fa4->cell_list, tag);
    func_ov008_0205589c(&data_ov008_02090fa4->cell_list, cell);
}
