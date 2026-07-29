typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov009SaveContext {
    int variant;
    u8 pad_004[0x8 - 0x4];
    int state;
    u8 pad_00c[0x68 - 0x0c];
    int pending;
    u8 pad_06c[0x240 - 0x06c];
    int blocked;
} Ov009SaveContext;

extern void func_ov009_02052b58(Ov009SaveContext *element, int oldVariant,
                                int newVariant);
extern void func_02033b78(int bank, int event);
extern u16 data_0204c18c;

/* Commit the pressed form of a two-state menu element. State 0 changes the
 * visible variant to 2 when no directional input is held; states 1 and 6
 * clear the pending flag. Both paths acknowledge the input latch. */
void func_ov009_02053804(Ov009SaveContext *element)
{
    int variant = element->variant;

    if (element->blocked != 0) {
        return;
    }

    switch (element->state) {
    case 0:
        if (data_0204c18c & 0xe0) {
            return;
        }
        if (variant == 2) {
            return;
        }
        element->variant = 2;
        func_ov009_02052b58(element, variant, 2);
        func_02033b78(0, 0);
        break;

    case 1:
    case 6:
        if (element->pending == 0) {
            return;
        }
        element->pending = 0;
        func_02033b78(0, 0);
        break;
    }
}
