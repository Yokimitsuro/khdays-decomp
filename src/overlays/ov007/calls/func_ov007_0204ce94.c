typedef struct {
    char pad00[0x74];
    unsigned short *src;
    int cursor;
    unsigned short line[1];
} LineBuf;

void func_ov007_0204ce94(LineBuf *b) {
    int idx = b->cursor;
    unsigned short *base = b->src;
    unsigned short s = base[idx];
    int n = 0;

    if (s != 0) {
        do {
            if (base[b->cursor] == 10) {
                b->cursor = b->cursor + 1;
                break;
            }
            b->cursor = b->cursor + 1;
            b->line[n] = b->src[idx];
            n++;
            idx = b->cursor;
            base = b->src;
            s = base[idx];
        } while (s != 0);
    }
    b->line[n] = 0;
}
