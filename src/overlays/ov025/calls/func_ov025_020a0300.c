/* func_ov025_020a0300 -- draw the visible rows of the reports list, ov025. Up to ten rows from the
 * page's top entry are drawn through func_ov025_020a01f8 (x 0x50, or 0x10 in mission mode 1; y
 * 0x13 + 0x10 per row) between the surface begin/end calls. In report mode the row under the cursor
 * shows its read variant when the gate (+0xc0) or a held entry (+0x25c) allows it; in mission mode
 * entries with pending bits show the fallback text data_ov025_020b5270. The pRead lookup is written
 * twice on purpose (the test and the local): that is what gives the ROM's register assignment. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef struct Entry {
    u16 id:9;
    u16 flag9:1;
    u16 pending:6;
    u8 pad_02[0xa];
    struct Entry *pRead;
    void *image;
    u8 pad_14[0x2c];
} Entry;
typedef struct Page {
    s16 top;
    s16 cursor;
    s16 count;
    s16 field06;
    u8 pad_008[0x70];
    u8 surface[0x3c];
    u8 pad_0b4[0xc];
    int gate;
    u8 pad_0c4[0x124];
    Entry *entries;
    u8 pad_1ec[0x6c];
    int missionMode;
    void *held;
} Page;
extern Page *func_ov025_02084afc(void);
extern void func_02030158(void *surface);
extern void func_020300f8(void *surface);
extern void func_ov025_02084964(int slot);
extern void func_ov025_020a01f8(void *image,int x,int y,int z,unsigned flags,int pass);
extern char data_ov025_020b5270;
void func_ov025_020a0300(void)
{
    u16 i;
    int mission;
    Page *page = func_ov025_02084afc();
    u16 row;
    void *image;
    func_02030158(page->surface);
    i = 0;
    do {
        row = (u16)(page->top + i);
        if (row >= page->count) break;
        mission = page->missionMode;
        if (mission == 0) {
            int chosen = 0;
            int canRead = chosen;
            Entry *read = page->entries[row].pRead;
            if (page->entries[row].pRead != 0) {
                if (page->cursor == row) canRead = 1;
            }
            if (canRead) {
                if (page->gate != 0 || page->held != 0) chosen = 1;
            }
            if (chosen) image = read->image;
            else image = page->entries[row].image;
        } else {
            void *fallback = &data_ov025_020b5270;
            if (page->entries[row].pending != 0) image = fallback;
            else image = page->entries[row].image;
        }
        func_ov025_020a01f8(image, mission == 1 ? 0x10 : 0x50, i * 0x10 + 0x13, 2, 0x209, 1);
        i = (u16)(i + 1);
    } while (i < 10);
    func_020300f8(page->surface);
    func_ov025_02084964(9);
}
