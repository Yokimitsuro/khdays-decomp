typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef struct Entry {
    u16 id:9;
    u16 flag9:1;
    u16 pending:6;
    u8 pad_02[0xa];
    struct Entry *pRead;
    u8 pad_10[0x30];
} Entry;
typedef struct Page {
    s16 top;
    s16 cursor;
    u8 pad_004[0xbc];
    int gate;
    u8 pad_0c4[0x124];
    Entry *entries;
    Entry current;
    u8 pad_22c[0x30];
    void *held;
} Page;
extern Page *func_ov025_02084afc(void);
extern void func_ov025_020a026c(void);
extern void func_ov025_020a06c0(void);
extern void func_ov025_020a0300(void);
extern void func_ov025_020a0428(void);
extern void func_ov025_0209f60c(int row);
void func_ov025_020a076c(void)
{
    Page *page = func_ov025_02084afc();
    Entry copy;
    Entry *read;
    int chosen;
    int canRead;
    func_ov025_020a026c();
    func_ov025_020a06c0();
    func_ov025_020a0300();
    func_ov025_020a0428();
    func_ov025_0209f60c(page->top);
    read = page->entries[page->cursor].pRead;
    chosen = 0;
    canRead = 0;
    if (read != 0 && page->entries[page->cursor].pending == 0) {
        canRead = 1;
    }
    if (canRead) {
        if (page->gate != 0 || page->held != 0) chosen = 1;
    }
    if (chosen) copy = *page->entries[page->cursor].pRead;
    else copy = page->entries[page->cursor];
    page->current = copy;
}
