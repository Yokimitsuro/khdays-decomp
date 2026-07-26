/* func_0200108c -- release overlay 105 if this module is the one holding it.
 *
 * The mirror image of func_02001054: the same data_027e0060 latch, cleared instead of
 * set, and the same linker-absolute FS_OVERLAY_ID pool word. See that file for why the
 * id cannot be spelled as the integer 105. */
typedef unsigned int u32;
typedef u32 FSOverlayID;
typedef signed char s8;

extern u32 OVERLAY_105_ID[1];
#define FS_OVERLAY_ID_ov105 ((FSOverlayID)(u32) & (OVERLAY_105_ID))

extern s8 data_027e0060;

extern void func_0201e4a8(int target, FSOverlayID id);

void func_0200108c(void)
{
    if (data_027e0060 == 0) {
        return;
    }
    func_0201e4a8(0, FS_OVERLAY_ID_ov105);
    data_027e0060 = 0;
}
