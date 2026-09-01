typedef struct {
    int x;
    int y;
} UiLayoutPos;

typedef struct {
    int x;
    int y;
    int cell;
    int keep;
} MissionPlacementConfig;

extern void func_020325ec(int panel, int idx, int cell);
extern void func_020326cc(int panel, int idx);
extern void func_0203257c(int panel, int idx, UiLayoutPos *pos);

void func_ov006_02051fbc(int panel, int idx, MissionPlacementConfig config)
{
    UiLayoutPos pos;

    pos.x = 0;
    pos.y = 0;
    if (config.x >= 0) {
        pos.x = config.x << 12;
    }
    if (config.y >= 0) {
        pos.y = config.y << 12;
    }
    if (config.cell >= 0 && config.keep == 0) {
        func_020325ec(panel, idx, config.cell & 0xffff);
        func_020326cc(panel, idx);
    }
    func_0203257c(panel, idx, &pos);
}
