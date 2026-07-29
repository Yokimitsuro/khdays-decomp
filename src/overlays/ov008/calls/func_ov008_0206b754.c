/* func_ov008_0206b754 -- Ov008_LoadSubScreenBg (164 B, 9 relocs).
 * Loads a sub-screen (engine B) menu background. When param_2 == 0 it first pokes the
 * shared object at data_0204be18 + 0xee0 (func_ov008_02053a90). It maps param_2 to an
 * archive subfile (func_ov008_0206b71c -> func_ov008_02050f08), unpacks it into a resource
 * cell (func_02024c94 with the -1,0,0 tail args), then uploads the sub-screen BG palette
 * (offset 0x80, 0x160 bytes, sourced from palette->data + 0x80) and BG3 character data
 * (offset 0x2000). The character size/data are read into locals before the palette upload
 * so they survive that call in callee-saved r5/r6. Finally frees the temp resource.
 * data_0204be18 is a char* global; `+ 0xee0` reads the pointer then adds the field offset. */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008PaletteBlock   { u8 pad_0000[0x08]; u32 size; void *data; } Ov008PaletteBlock;
typedef struct Ov008ScreenBlock    { u8 pad_0000[0x08]; u32 size; u8 data[1]; } Ov008ScreenBlock;
typedef struct Ov008ResourceCell {
    Ov008ScreenBlock    *screen;
    Ov008CharacterBlock *character;
    Ov008PaletteBlock   *palette;
} Ov008ResourceCell;

extern char *data_0204be18;
extern void  func_ov008_02053a90(void *anchor);
extern int   func_ov008_0206b71c(int arg);
extern u32   func_ov008_02050f08(int subfile);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void  func_02024c94(Ov008ResourceCell *cell, void *resource, int a, int b, int c);
extern void  GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void  GXS_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);

void func_ov008_0206b754(int param_1, int param_2)
{
    void *resource;
    Ov008ResourceCell cell;
    u32 charSize;
    void *charData;

    if (param_2 == 0) {
        func_ov008_02053a90(data_0204be18 + 0xee0);
    }
    resource = func_0201ef9c(func_ov008_02050f08(func_ov008_0206b71c(param_2)), 0xe);
    func_02024c94(&cell, resource, -1, 0, 0);
    charSize = cell.character->size;
    charData = cell.character->data;
    GXS_LoadBGPltt((char *)cell.palette->data + 0x80, 0x80, 0x160);
    GXS_LoadBG3Char(charData, 0x2000, charSize);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
}
