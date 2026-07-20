/* FS_GetOverlayFileID: fills the two-word info block {&table, overlay->fileId (+0x18)}. */

typedef struct {
    int a;
    int b;
} FsOverlayInfo;

extern int data_02046334;

void FS_GetOverlayFileID(FsOverlayInfo *dst, int *overlay) {
    FsOverlayInfo info;
    info.a = (int)&data_02046334;
    info.b = overlay[6];
    *dst = info;
}
