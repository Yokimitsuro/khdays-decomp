/* func_ov000_0204ee24 -- boot: hand control to the anti-tamper selector, or to the fallback.
 *
 * Sets the display and mode configs, runs the boot-time setup, and (only when the boot request
 * at ctx+0x4c40 is pending) asks func_020235d0 for the selector value.  0x191 means "run the
 * protected path": clear the boot-mode state, load ov028 (DS Protect), and if all three of its
 * predicates pass, seed the elapsed field with 10000 and enter func_ov000_0204edcc; either way
 * ov028 is unloaded again.  Anything else falls back to func_02020a78(5, selector).
 * Always reports -2.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd emits
 * `OVERLAY_28_ID = 28;` into arm9.lcf, which is why 0x1c comes from the literal pool and is
 * kept in a callee-saved register across the load and the unload.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef u32 FSOverlayID;

extern u32 OVERLAY_28_ID[1];
#define FS_OVERLAY_ID_ov028 ((FSOverlayID)(u32) & (OVERLAY_28_ID))

typedef struct Ov000DisplayConfig {
    int enabled;
    int visible;
    int reserved0;
    int reserved1;
} Ov000DisplayConfig;

typedef struct Ov000ModeConfig {
    int enabledMode;
    int reserved;
} Ov000ModeConfig;

typedef struct BootModeState {
    u8 flags;
    u8 state;
    u16 elapsed;
    u16 resetWord;
} BootModeState;

typedef struct Ov000BootContext {
    u8 pad_0000[0x4c40];
    int bootRequestPending;
} Ov000BootContext;

extern Ov000BootContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_02031600(Ov000DisplayConfig *config);
extern void func_02031618(Ov000ModeConfig *mode, int arg);
extern void func_020305d8(void);
extern void func_ov000_020588ec(int a, int b);
extern int  func_020235d0(int a, int b);
extern void func_0201e470(int processor, FSOverlayID id);
extern int  func_ov028_0208b490(int a);
extern int  func_ov028_0208b120(int a);
extern int  func_ov028_0208b2e0(int a);
extern void func_ov000_0204edcc(void);
extern void func_0201e4a8(int processor, FSOverlayID id);
extern void func_02020a78(int a, int b);
extern BootModeState data_0204c240;

int func_ov000_0204ee24(void) {
    Ov000BootContext *ctx = NNSi_FndGetCurrentRootHeap();
    Ov000ModeConfig mode;
    Ov000DisplayConfig display;
    int selector = 0;

    display.enabled = 1;
    display.visible = 1;
    func_02031600(&display);
    mode.enabledMode = 1;
    mode.reserved = 0;
    func_02031618(&mode, 0);
    func_020305d8();
    func_ov000_020588ec(0, 0);
    if (ctx->bootRequestPending != 0) {
        selector = func_020235d0(0, 9);
    }
    if (selector == 0x191) {
        data_0204c240.resetWord = 0;
        data_0204c240.state = 0;
        func_0201e470(0, FS_OVERLAY_ID_ov028);
        if (func_ov028_0208b490(0) != 0 && func_ov028_0208b120(0) != 0 &&
            func_ov028_0208b2e0(0) != 0) {
            data_0204c240.elapsed = 0x2710;
            func_ov000_0204edcc();
        }
        func_0201e4a8(0, FS_OVERLAY_ID_ov028);
    } else {
        func_02020a78(5, selector);
    }
    return -2;
}
