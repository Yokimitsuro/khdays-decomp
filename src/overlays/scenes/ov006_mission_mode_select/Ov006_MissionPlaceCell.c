/* Places a menu cell: sets its slot entry unless it keeps the current one, then moves it to the
 * position (negative coordinates leave it at 0). */

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

extern void Slot_ForwardToEntry(int panel, int idx, int cell);
extern void Slot_ClearFlagBit1(int panel, int idx);
extern void Slot_SetPosition(int panel, int idx, UiLayoutPos *pos);

void Ov006_MissionPlaceCell(void *panel, int idx, MissionPlacementConfig config)
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
        Slot_ForwardToEntry((int)panel, idx, config.cell & 0xffff);
        Slot_ClearFlagBit1((int)panel, idx);
    }
    Slot_SetPosition((int)panel, idx, &pos);
}
