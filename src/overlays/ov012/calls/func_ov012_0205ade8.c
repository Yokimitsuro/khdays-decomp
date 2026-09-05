typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SpriteResSet {
    int words[3];
} SpriteResSet;

extern int data_ov012_0205cb20;
extern char data_ov012_0205cac0[];
extern int data_ov012_0205c2d0;
extern char data_ov012_0205cadc[];
extern int data_ov012_0205caf4;
extern char data_ov012_0205cae8[];
extern u32 OVERLAY_24_ID[1];
#define FS_OVERLAY_ID_ov024 ((u32)&OVERLAY_24_ID)

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e470(int processor, int overlayId);
extern void func_ov012_0205ad1c(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_0202f7fc(void *dst, const void *path);
extern void GX_LoadBGPltt(const void *src, int offset, int size);
extern void GXS_LoadBGPltt(const void *src, int offset, int size);
extern void *func_02024ee8(const void *path, int heapId);
extern void *func_0201ef9c(u32 archiveEntry, int heapId);
extern u32 func_02024e5c(void);
extern void func_02024fd4(void *header);
extern void func_02024c94(SpriteResSet *set, void *archive, int character,
                         int screen, int palette);
extern void func_02020aa8(int slot, const void *table);
extern void func_02020c7c(void *dst, const void *path, void *unused,
                         void *workspace);
extern void func_ov012_0205b618(void);

void *func_ov012_0205ade8(int alternateMode) {
    char *root;
    void *header;
    u32 archiveEntry;
    int paletteIndex;
    int resourceIndex;
    int screenIndex;
    u32 rawKeys;
    u16 keys;
    char *workspace;
    SpriteResSet *nextSet;

    root = (char *)NNSi_FndGetCurrentRootHeap();
    func_0201e470(0, FS_OVERLAY_ID_ov024);
    func_ov012_0205ad1c();
    data_ov012_0205cb20 = (int)root;
    *(u16 *)(root + 0) = 0;
    *(u16 *)(root + 2) = 0;
    if (alternateMode == 0) {
        *(u16 *)(root + 2) |= 0x10;
    }
    *(int *)(root + 0x8be8) = -1;
    *(int *)(root + 0x8bd8) = *(int *)(root + 0x8bdc) = 0;
    workspace = root + 0x198;
    *(u8 *)(root + 0x8be0) = 0;
    *(u8 *)(root + 0x8bf0) = 0;
    MI_CpuFill8(workspace + 0x8400, 0, 0x5a4);
    func_0202f7fc(root + 0x8b40, data_ov012_0205cac0);
    GX_LoadBGPltt(&data_ov012_0205c2d0, 0x1a0, 0x20);
    GXS_LoadBGPltt(&data_ov012_0205c2d0, 0x1a0, 0x20);
    *(void **)(root + 0x85a4) = root + 0x8b4c;
    header = func_02024ee8(data_ov012_0205cadc, 0xe);
    archiveEntry = (((u32)header + 0x8000) & 0x00fffffc) << 7 | 0x80000000;
    *(void **)(root + 0x8bf8) = func_0201ef9c(archiveEntry, 0xe);
    *(void **)(root + 0x8bfc) =
        func_0201ef9c(archiveEntry | (func_02024e5c() & 0x1ff), 0xe);
    func_02024fd4(header);

    resourceIndex = 0;
    paletteIndex = 0;
    screenIndex = 0;
    do {
        func_02024c94((SpriteResSet *)(root + 0x8c00 + resourceIndex * 12),
                      *(void **)(root + 0x8bf8), screenIndex, screenIndex,
                      paletteIndex);
        nextSet = (SpriteResSet *)(root + 0x8c00 + (resourceIndex + 1) * 12);
        resourceIndex += 2;
        func_02024c94(nextSet,
                      *(void **)(root + 0x8bf8), screenIndex + 1,
                      screenIndex + 1, -1);
        if (paletteIndex < 13) {
            nextSet = (SpriteResSet *)(root + 0x8c00 + resourceIndex * 12);
            resourceIndex++;
            func_02024c94(nextSet,
                          *(void **)(root + 0x8bfc), paletteIndex,
                          paletteIndex, -1);
        }
        paletteIndex++;
        screenIndex += 2;
    } while (paletteIndex < 14);

    func_02020aa8(3, &data_ov012_0205caf4);
    func_02020c7c(root + 4, data_ov012_0205cae8, 0, root + 0x8598);
    *(u16 *)(root + 2) |= 1;
    *(u8 *)(root + 0x8be1) = 0;
    rawKeys = *(volatile u16 *)0x04000130 | *(volatile u16 *)0x027fffa8;
    keys = (rawKeys ^ 0x2fff) & 0x2fff;
    *(int *)(root + 0x8bec) = keys & 8;
    return (void *)func_ov012_0205b618;
}