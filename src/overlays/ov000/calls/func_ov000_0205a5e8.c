/* func_ov000_0205a5e8 -- wait for the launched scene to finish, then return to the menu.
 *
 * Which scene is running depends on ctx->transitionMode: mode 0 is the movie player (ov012),
 * anything else is ov011.  While that scene reports "still running" this returns 0 and the
 * state machine stays.  Once it is done: release the key-sharing handle, black out both
 * screens, unload whichever overlay was used, arm handler 0x20e9, and re-enter the menu
 * through func_ov000_02059e00 with the two scene values as start parameters.
 *
 * Both overlay ids are the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd
 * emits `OVERLAY_11_ID = 11;` / `OVERLAY_12_ID = 12;` into arm9.lcf.  Both are encodable ARM
 * immediates, so written as plain integers the two pool words vanish and the function comes
 * out 8 bytes short.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef u32 FSOverlayID;
typedef void (*Ov000StateFn)(void);

extern u32 OVERLAY_11_ID[1];
extern u32 OVERLAY_12_ID[1];
#define FS_OVERLAY_ID_ov011 ((FSOverlayID)(u32) & (OVERLAY_11_ID))
#define FS_OVERLAY_ID_ov012 ((FSOverlayID)(u32) & (OVERLAY_12_ID))

typedef struct OverlayStartParams {
    u32 first;
    u32 second;
} OverlayStartParams;

typedef struct Ov000SceneContext {
    short secondValue;
    short firstValue;
    u8 pad_0004[0xd134];
    int transitionMode;
    void *sharingHandle;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov012_0205b920(void);
extern int func_ov011_0205dc4c(void);
extern void *WM_EndKeySharing_0x02023ad0(void *handle);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void func_0201e4a8(int processor, FSOverlayID overlayId);
extern void func_020235bc(int handlerId);
extern int func_020208f0(void);
extern Ov000StateFn func_ov000_02059e00(const OverlayStartParams *params);

Ov000StateFn func_ov000_0205a5e8(void) {
    Ov000SceneContext *ctx = NNSi_FndGetCurrentRootHeap();
    OverlayStartParams params;

    if (ctx->transitionMode == 0) {
        if (func_ov012_0205b920() == 0) {
            return 0;
        }
    } else if (func_ov011_0205dc4c() == 0) {
        return 0;
    }
    WM_EndKeySharing_0x02023ad0(ctx->sharingHandle);
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    if (ctx->transitionMode == 0) {
        func_0201e4a8(0, FS_OVERLAY_ID_ov012);
    } else {
        func_0201e4a8(0, FS_OVERLAY_ID_ov011);
    }
    params.first = ctx->firstValue;
    params.second = ctx->secondValue;
    func_020235bc(0x20e9);
    func_020208f0();
    return func_ov000_02059e00(&params);
}
