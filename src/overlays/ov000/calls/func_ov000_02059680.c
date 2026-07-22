typedef unsigned char u8;
typedef signed short s16;

typedef struct {
    s16 limit;
    s16 cursor;
    u8 pad_04[0x5c];
    int changed;
} OverlaySelection;

extern void func_02033b78(int x, int y);
extern void func_ov000_02059d78(void);

void func_ov000_02059680(OverlaySelection *selection) {
    selection->cursor--;
    if (selection->cursor < 0) {
        selection->cursor = 27;
        if (selection->limit + 10 <= selection->cursor) {
            selection->limit = selection->cursor - 9;
            selection->changed = 0;
        }
    }

    if (selection->cursor < selection->limit) {
        selection->limit = selection->cursor;
        selection->changed = 0;
    }

    func_02033b78(0, 0);
    func_ov000_02059d78();
}
