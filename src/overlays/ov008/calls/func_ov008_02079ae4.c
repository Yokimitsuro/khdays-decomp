typedef signed char s8;
typedef unsigned char u8;

typedef struct {
    u8 field_0;
    unsigned char active : 1;
    unsigned char dirty : 1;
    unsigned char pad_flags : 6;
    s8 id;
    u8 pad_3[3];
} MissionIdEntry;

typedef struct {
    int header;
    MissionIdEntry entries[4];
} MissionIdGroup;

typedef struct {
    u8 pad_0000[0x4a8];
    MissionIdGroup current_group;
    MissionIdGroup previous_group;
} MissionContext;

typedef struct {
    MissionContext *context;
} Ov006Globals;

extern Ov006Globals data_ov008_02090f24;
extern int func_02023eb4(int bound);

void func_ov008_02079ae4(void) {
    int i = 0;
    int j;
    MissionIdEntry *current = data_ov008_02090f24.context->current_group.entries;
    MissionIdEntry *previous = data_ov008_02090f24.context->previous_group.entries;

    for (; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            MissionIdEntry *left = &current[i];
            MissionIdEntry *right = &current[j];

            if (right->id == left->id && left->active && right->active &&
                (right->id != previous[j].id || left->id != previous[i].id)) {
                int changed;

                if (right->id != previous[j].id) {
                    changed = j;
                } else {
                    changed = i;
                }
                current[changed].id = previous[changed].id;
                current[changed].dirty = 0;
            }
        }
    }

restart_duplicate_scan:
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            if (current[j].id == current[i].id && current[i].active &&
                current[j].active) {
                current[j].id = func_02023eb4(12);
                current[j].dirty = 0;
                goto restart_duplicate_scan;
            }
        }
    }

    data_ov008_02090f24.context->previous_group =
        data_ov008_02090f24.context->current_group;
}
