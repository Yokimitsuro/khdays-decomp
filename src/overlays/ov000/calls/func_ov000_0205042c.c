typedef unsigned char u8;

typedef struct {
    int position;
    int unknown_4;
} OverlayMarker;

typedef struct {
    u8 pad_0000[0x4c];
    u8 object_list[0x4abc];
    int selected_marker;
    u8 pad_4b0c[0x188];
    OverlayMarker markers[4];
} OverlayContext;

extern OverlayContext *volatile data_ov000_0205ac24;
extern const int data_ov000_0205a6bc[2];
extern int *func_ov000_02055b48(void *list, int id);
extern void func_ov000_02055cb4(void *list, int *entry, int enabled);

void func_ov000_0205042c(int position_enabled, int group_enabled,
                         int primary_enabled) {
    OverlayContext *context = data_ov000_0205ac24;
    int *entry;
    unsigned int i;

    entry = func_ov000_02055b48(context->object_list, 16);
    func_ov000_02055cb4(context->object_list, entry, primary_enabled);

    for (i = 0; i < 2; i++) {
        entry = func_ov000_02055b48(context->object_list,
                                    data_ov000_0205a6bc[i]);
        func_ov000_02055cb4(context->object_list, entry, group_enabled);
    }

    if (position_enabled != 0) {
        int marker;

        for (marker = 0; marker < 4; marker++) {
            OverlayContext *current = data_ov000_0205ac24;

            if (marker == current->selected_marker) {
                current->markers[marker].position = 0;
            } else {
                current->markers[marker].position = -0xf0000;
            }
        }
    } else {
        int marker;

        for (marker = 0; marker < 4; marker++) {
            data_ov000_0205ac24->markers[marker].position = 0;
        }
    }
}
