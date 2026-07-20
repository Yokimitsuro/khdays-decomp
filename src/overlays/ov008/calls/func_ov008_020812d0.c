typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad_0000[0x4a8c];
    u8 renderer;
    u8 pad_4a8d[0x4a7b];
    int entry_count;
    s8 initial_selection;
    u8 pad_950d[3];
    int selections[5];
    int enabled[4];
    u8 pad_9534[0x1ac];
    int initial_cell;
    u8 pad_96e4[0x30];
    int cells[19];
} Ov006RootContext;

extern Ov006RootContext *NNSi_FndGetCurrentRootHeap(void);
extern Ov006RootContext *data_ov008_02090fa4;
extern void func_020325ec(void *renderer, int cell, int value);
extern void func_020326cc(void *renderer, int cell);
extern void func_ov008_02080d28(int slot, int selection);

void func_ov008_020812d0(void) {
    Ov006RootContext *context = NNSi_FndGetCurrentRootHeap();
    int i;

    if (context == 0) {
        return;
    }

    if (data_ov008_02090fa4->initial_selection >= 0 &&
        data_ov008_02090fa4->initial_selection <= 3) {
        func_020325ec(&context->renderer,
                      data_ov008_02090fa4->initial_cell,
                      (u16)data_ov008_02090fa4->initial_selection);
        func_020326cc(&context->renderer,
                      data_ov008_02090fa4->initial_cell);
    }

    for (i = 0; i < 19; i++) {
        func_020325ec(&context->renderer, context->cells[i], 1);
        func_020326cc(&context->renderer, context->cells[i]);
    }

    for (i = 0; i < data_ov008_02090fa4->entry_count; i++) {
        int selection = context->selections[i];

        if (selection >= 0 && selection < 19) {
            int cell;

            if (context->enabled[i] == 0) {
                continue;
            }
            cell = context->cells[selection];
            func_020325ec(&context->renderer, cell, 0);
            func_020326cc(&context->renderer, cell);
        }
        func_ov008_02080d28(i, data_ov008_02090fa4->selections[i]);
    }
}
