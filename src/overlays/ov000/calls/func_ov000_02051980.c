typedef unsigned char u8;

typedef struct {
    u8 pad_0000[0x4c];
    u8 object[1];
    u8 pad_004d[0x4a7f];
    u8 itemCountMinus3;
} Ov000SceneContext;

extern Ov000SceneContext *data_ov000_0205ac24;
extern int func_ov000_02055b48(int object, int id);
extern int func_ov000_02055bc4(int object, int entry);

int func_ov000_02051980(int selectedIndex, int movementXArg,
                        int movementYArg, ...) {
    int movementX;
    int context;
    int i;
    int *selectedPosition;
    int movementY;

    movementY = *(int *)&movementYArg;
    context = (int)data_ov000_0205ac24;
    selectedPosition = (int *)func_ov000_02055bc4(
        context + 0x4c,
        func_ov000_02055b48(context + 0x4c, selectedIndex + 1));
    i = 0;

    if (i < data_ov000_0205ac24->itemCountMinus3 + 3) {
        movementX = *(int *)&movementXArg;
        do {
            int *position = (int *)func_ov000_02055bc4(
                context + 0x4c,
                func_ov000_02055b48(context + 0x4c, i + 1));

            if (selectedPosition[0] - 0x2000 - movementX <
                    position[0] + 0xc4000 &&
                position[0] - 0x2000 <
                    selectedPosition[0] + 0xc4000 - movementX &&
                selectedPosition[1] + 0x2000 - movementY <
                    position[1] + 0x24000 &&
                ((volatile int *)position)[1] <
                    selectedPosition[1] + 0x24000 - movementY &&
                i != selectedIndex) {
                return 0;
            }

            i++;
        } while (i < data_ov000_0205ac24->itemCountMinus3 + 3);
    }

    return 1;
}
