typedef unsigned int u32;
typedef u32 FSOverlayID;

extern u32 OVERLAY_107_ID[1];
#define FS_OVERLAY_ID_ov107 ((FSOverlayID)(u32) & (OVERLAY_107_ID))

extern void func_0201e4a8(int target, FSOverlayID id);

void func_02035d90(void) {
    func_0201e4a8(0, FS_OVERLAY_ID_ov107);
}
