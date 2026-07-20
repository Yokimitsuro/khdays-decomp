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

extern Ov006RootContext *data_ov006_02056664;
extern void *func_ov006_0204d434(MissionCellList *list, u16 tag);
extern void func_ov006_0204d4a0(MissionCellList *list, void *cell, int x, int y);
extern void func_ov006_0204d4c8(MissionCellList *list, void *cell);

void func_ov006_02053cdc(u32 tag, int x, int y) {
    void *cell;

    cell = func_ov006_0204d434(&data_ov006_02056664->cell_list, tag);
    func_ov006_0204d4a0(&data_ov006_02056664->cell_list, cell, x, y);
    cell = func_ov006_0204d434(&data_ov006_02056664->cell_list, tag);
    func_ov006_0204d4c8(&data_ov006_02056664->cell_list, cell);
}
