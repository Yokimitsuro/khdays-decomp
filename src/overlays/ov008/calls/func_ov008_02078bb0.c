/* func_ov008_02078bb0 -- Ov008_LoadMenuSubBg2 (152 B, 8 relocs).
 * Loads a sub-screen BG2 character bank for the menu. Fetches two contexts (02050cec for the
 * archive base, 02050c3c for the cell-list), and returns early if param_1 is 0. Builds a packed
 * archive-subfile handle for subfile 0x30 from ctx->archiveBase (the standard NDS archive-handle
 * formula), unpacks it (func_02011988 resolves the character block), uploads the block as BG2
 * characters at offset 0x4f40, frees the temp resource, and attaches a descriptor
 * (data_ov008_02090b58) to the cell-list context. Character-block layout matches the loader family
 * (size at +0x10, data at +0x14). */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008MenuContext { u8 pad_0000[0x34]; u32 archiveBase; } Ov008MenuContext;

extern u8 data_ov008_02090b58[];
extern Ov008MenuContext *func_ov008_02050cec(void);
extern void *func_ov008_02050c3c(void);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void  func_02011988(void *resource, Ov008CharacterBlock **block);
extern void  GXS_LoadBG2Char(const void *source, u32 offset, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  func_ov008_02055534(void *ctx, void *desc);

#define OV008_ARCHIVE_MASK 0x00fffffc
#define OV008_SUBFILE(base, index) \
    (((((u32)(base) + 0x8000) & OV008_ARCHIVE_MASK) << 7) | 0x80000000 | (index))

void func_ov008_02078bb0(int param_1)
{
    Ov008MenuContext *ctx1 = func_ov008_02050cec();
    void *ctx2 = func_ov008_02050c3c();
    void *resource;
    Ov008CharacterBlock *block;

    if (param_1 == 0) {
        return;
    }
    resource = func_0201ef9c(OV008_SUBFILE(ctx1->archiveBase, 0x30), 0xe);
    func_02011988(resource, &block);
    GXS_LoadBG2Char(block->data, 0x4f40, block->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
    func_ov008_02055534(ctx2, data_ov008_02090b58);
}
