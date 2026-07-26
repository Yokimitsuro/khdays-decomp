/* func_02001054 -- make overlay 105 resident, at most once.
 *
 * data_027e0060 is the "already resident" latch: non-zero means someone got here first,
 * so the load is skipped. func_0200108c is the matching release.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol -- the NitroSDK FS_OVERLAY_ID
 * idiom, which dsd emits into arm9.lcf as `OVERLAY_105_ID = 105;`. Spelled as the plain
 * integer 105 the pool word disappears and the function comes out 4 bytes short, even
 * though 105 is perfectly encodable as an ARM immediate. A pooled small constant is the
 * tell: mwcc pools it because it is a relocation, not a literal. */
typedef unsigned int u32;
typedef u32 FSOverlayID;
typedef signed char s8;

extern u32 OVERLAY_105_ID[1];
#define FS_OVERLAY_ID_ov105 ((FSOverlayID)(u32) & (OVERLAY_105_ID))

extern s8 data_027e0060;

extern void func_0201e470(int target, FSOverlayID id);

void func_02001054(void)
{
    if (data_027e0060 != 0) {
        return;
    }
    func_0201e470(0, FS_OVERLAY_ID_ov105);
    data_027e0060 = 1;
}
