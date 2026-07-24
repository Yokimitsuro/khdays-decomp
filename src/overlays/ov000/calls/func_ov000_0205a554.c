/* func_ov000_0205a554 -- wait for the running sub-scene to finish, then go back to the menu.
 *
 * Polls the sub-scene's readyCallback (ctx+0xd16c); while it says "not yet" this reports 0 and
 * the state machine stays.  Once it fires: run the sub-scene teardown (ctx+0xd160), black out
 * the main screen, unload ov024, release the resource at ctx+0xd154, arm handler 0x20e9, reset
 * the input/audio state and re-enter the menu through func_ov000_02059e00, handing it the two
 * scene values as the start parameters.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd emits
 * `OVERLAY_24_ID = 24;` into arm9.lcf.  24 is an encodable ARM immediate, so spelled as a plain
 * integer the pool word disappears and the function comes out 4 bytes short.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef u32 FSOverlayID;
typedef void (*Ov000StateFn)(void);

extern u32 OVERLAY_24_ID[1];
#define FS_OVERLAY_ID_ov024 ((FSOverlayID)(u32) & (OVERLAY_24_ID))

typedef struct OverlayStartParams {
    u32 first;
    u32 second;
} OverlayStartParams;

typedef struct Ov000SceneContext {
    short secondValue;
    short firstValue;
    u8 pad_0004[0xd150];
    void *resource;
    u8 pad_d158[8];
    void (*teardownCallback)(void);
    u8 pad_d164[8];
    int (*readyCallback)(void);
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int brightness);
extern void func_0201e4a8(int processor, FSOverlayID overlayId);
extern int func_02024fd4(void *resource);
extern void func_020235bc(int handlerId);
extern void func_02020a90(int value);
extern void func_020208f0(void);
extern Ov000StateFn func_ov000_02059e00(const OverlayStartParams *params);

Ov000StateFn func_ov000_0205a554(void) {
    Ov000SceneContext *ctx = NNSi_FndGetCurrentRootHeap();
    OverlayStartParams params;

    if (ctx->readyCallback() == 0) {
        return 0;
    }
    ctx->teardownCallback();
    func_0201e374(-0x10);
    func_0201e4a8(0, FS_OVERLAY_ID_ov024);
    func_02024fd4(ctx->resource);
    params.first = ctx->firstValue;
    params.second = ctx->secondValue;
    func_020235bc(0x20e9);
    func_02020a90(0);
    func_020208f0();
    return func_ov000_02059e00(&params);
}
