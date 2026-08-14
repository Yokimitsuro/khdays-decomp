#pragma opt_propagation off

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 type;
    u16 id;
} Ov025Message;

typedef struct {
    u8 pad_0000[0x209c];
    u32 currentMessageId;
} Ov025Page;

extern Ov025Page *func_ov008_02050cd4(void);
extern int func_020343cc(Ov025Message **messageSlot);

int func_ov008_0205ca8c(Ov025Message **messageSlot) {
    Ov025Page *page = func_ov008_02050cd4();
    unsigned int id = (*messageSlot)->id;
    int handled = 1;

    if (id == page->currentMessageId) {
        *messageSlot = 0;
        return handled;
    }

    switch (id) {
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x1b:
        *messageSlot = 0;
        return handled;
    }

    return func_020343cc(messageSlot);
}

