typedef unsigned int u32;
typedef u32 FSOverlayID;

/* 0x6b (107) is the ADDRESS of a linker-absolute symbol -- the NitroSDK FS_OVERLAY_ID
 * idiom, which dsd emits into arm9.lcf as `OVERLAY_107_ID = 107;`. Spelled as the plain
 * integer 107 the pool word disappears and the function comes out 4 bytes short, even
 * though 107 is perfectly encodable as an ARM immediate. */
extern u32 OVERLAY_107_ID[1];
#define FS_OVERLAY_ID_ov107 ((FSOverlayID)(u32) & (OVERLAY_107_ID))

extern void func_0201e470(int target, FSOverlayID id);

void func_02035d78(void)
{
    func_0201e470(0, FS_OVERLAY_ID_ov107);
}
