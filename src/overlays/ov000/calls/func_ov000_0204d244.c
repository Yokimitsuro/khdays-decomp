typedef unsigned char u8;

typedef struct {
    int values[3];
} OverlayCountTable;

typedef struct {
    u8 pad_0000[0x4c53];
    u8 second_locked;
    int first_extended;
} OverlayContext;

extern const OverlayCountTable data_ov000_0205a6b0;
extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_020362fc(void *input);
extern void func_02033b78(int first, int second);

int func_ov000_0204d244(void *input, int selection, int group) {
    OverlayCountTable counts = data_ov000_0205a6b0;
    int decrement = 0;
    int increment = 0;

    if (NNSi_FndGetCurrentRootHeap()->first_extended != 0) {
        counts.values[0] = 3;
    }
    if (NNSi_FndGetCurrentRootHeap()->second_locked == 0) {
        counts.values[1] = 1;
    }

    if ((func_020362fc(input) & 0x40) != 0) {
        decrement = 1;
    }
    if ((func_020362fc(input) & 0x80) != 0) {
        increment = 1;
    }
    func_020362fc(input);
    func_020362fc(input);

    if ((decrement != 0 || increment != 0) && counts.values[group] > 1) {
        func_02033b78(0, 0);
    }
    if (decrement != 0) {
        selection--;
    }
    if (increment != 0) {
        selection++;
    }
    if (selection < 0) {
        selection = counts.values[group] - 1;
    }
    if (selection >= counts.values[group]) {
        selection = 0;
    }
    return selection;
}
