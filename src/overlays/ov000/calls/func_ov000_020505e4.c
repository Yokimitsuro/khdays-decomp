typedef unsigned char u8;

typedef struct {
    int x;
    int y;
} OverlayVector;

typedef struct {
    u8 pad_0000[0x4c];
    u8 object_list[0x4a80];
    u8 position_shifted;
} OverlayContext;

extern OverlayContext *volatile data_ov000_0205ac24;
extern int *func_ov000_02055b48(void *list, int id);
extern OverlayVector *func_ov000_02055c40(void *list, int *entry);
extern void func_ov000_02055bfc(void *list, int *entry,
                                const OverlayVector *position);
extern void func_ov000_02055cb4(void *list, int *entry, int enabled);

void func_ov000_020505e4(int enabled, int mode) {
    OverlayContext *context = data_ov000_0205ac24;
    int *entry = func_ov000_02055b48(context->object_list, 16);
    OverlayVector position;

    if (enabled != 0) {
        position = *func_ov000_02055c40(context->object_list, entry);
        position.x += 0x8000;

        switch (mode) {
        case 0:
            position.y = 0x2c000;
            break;
        case 1:
            position.y = 0x50000;
            break;
        case 2:
            position.y = 0x74000;
            break;
        case 3:
            position.y = 0x84000;
            break;
        }

        if (data_ov000_0205ac24->position_shifted != 0 && mode < 3) {
            position.y -= 0x8000;
        }
    }

    func_ov000_02055bfc(context->object_list, entry, &position);
    func_ov000_02055cb4(context->object_list, entry, enabled);
}
