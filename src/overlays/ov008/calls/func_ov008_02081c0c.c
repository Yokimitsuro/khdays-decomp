typedef unsigned char u8;

typedef struct {
    unsigned pad_0 : 2;
    unsigned visible : 1;
    unsigned pad_3 : 29;
    u8 pad_04[0x88];
} MissionDrawSlot;

typedef struct {
    u8 pad_0000[0x7c];
    MissionDrawSlot draw_slots[136];
} MissionRenderer;

typedef struct {
    u8 pad_0000[0x4a8c];
    MissionRenderer renderer;
    u8 pad_9568[0x5c];
    int primary_slot;
    u8 pad_95c8[4];
    int linked_slot;
    int alternate_slot;
} Ov006RootContext;

extern Ov006RootContext *data_ov008_02090fa4;

void func_ov008_02081c0c(int visible) {
    int linked_slot;
    int alternate_slot;

    if (data_ov008_02090fa4 == 0) {
        return;
    }

    if (visible != 0) {
        int primary_slot = data_ov008_02090fa4->primary_slot;
        MissionRenderer *renderer = &data_ov008_02090fa4->renderer;

        if (renderer->draw_slots[primary_slot].visible != 0) {
            return;
        }
        if (primary_slot >= 0) {
            renderer->draw_slots[primary_slot].visible = 1;
        }

        linked_slot = data_ov008_02090fa4->linked_slot;
        if (linked_slot >= 0) {
            renderer->draw_slots[linked_slot].visible = 1;
        }

        alternate_slot = data_ov008_02090fa4->alternate_slot;
        if (alternate_slot >= 0) {
            renderer->draw_slots[alternate_slot].visible = 0;
        }
        return;
    }

    {
        int primary_slot = data_ov008_02090fa4->primary_slot;
        MissionRenderer *renderer = &data_ov008_02090fa4->renderer;

        if (renderer->draw_slots[primary_slot].visible == 0) {
            return;
        }
        if (primary_slot >= 0) {
            renderer->draw_slots[primary_slot].visible = 0;
        }

        linked_slot = data_ov008_02090fa4->linked_slot;
        if (linked_slot >= 0) {
            renderer->draw_slots[linked_slot].visible = 0;
        }

        alternate_slot = data_ov008_02090fa4->alternate_slot;
        if (alternate_slot >= 0) {
            renderer->draw_slots[alternate_slot].visible = 1;
        }
    }
}
