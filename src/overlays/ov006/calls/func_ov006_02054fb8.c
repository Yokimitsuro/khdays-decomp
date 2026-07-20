typedef signed char s8;
typedef unsigned char u8;

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

extern const MissionOffsetTable data_ov006_0205630c;
extern Ov006RootContext *data_ov006_02056664;
extern void func_ov006_02051fbc(void *panel, int cell, ...);

void func_ov006_02054fb8(int slot, int selector) {
    MissionPlacementConfig config = {0, 0, 0, 0};
    MissionOffsetTable offsets = data_ov006_0205630c;

    if (selector == -1 || selector >= 19) {
        config.x = -48;
        config.y = -128;
    } else {
        s8 mapped = data_ov006_02056664->offset_map[selector];

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
    func_ov006_02051fbc(&data_ov006_02056664->panel,
                         data_ov006_02056664->primary_cells[slot],
                         config);
    config.keep = 1;
    func_ov006_02051fbc(&data_ov006_02056664->panel,
                         data_ov006_02056664->secondary_cells[slot],
                         config);
}
