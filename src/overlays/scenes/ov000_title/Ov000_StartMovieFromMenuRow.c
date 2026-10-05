/* Ov000_StartMovieFromMenuRow -- start a movie from the menu row the player picked.
 *
 * Formats the selected row's value into the frame's name buffer, tears the menu down,
 * publishes the scene block in data_ov000_0205ac3c, arms handler 0x20e9, sets the fade value,
 * loads ov024 (the MobiClip player) and opens the stream resource.  The stream interface at
 * ctx+0xd158 is filled in by Ov024_MobiClip_InstallStreamSourceVtbl and then driven: initialize, open with the
 * resource, start.  Control moves on to Ov000_WaitSubSceneThenMenu, which waits for it to finish.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd
 * emits `OVERLAY_24_ID = 24;` into arm9.lcf.  24 is an encodable ARM immediate, so written as
 * a plain integer the pool word disappears and the function is 4 bytes short.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef u32 FSOverlayID;
typedef void (*Ov000StateFn)(void);

extern u32 OVERLAY_24_ID[1];
#define FS_OVERLAY_ID_ov024 ((FSOverlayID)(u32) & (OVERLAY_24_ID))

typedef struct Ov000RowDescriptor {
    int displayValue;
    u8 pad_0004[0x14];
} Ov000RowDescriptor;

typedef struct Ov000StreamOpenParams {
    void *resource;
    int enabled;
} Ov000StreamOpenParams;

typedef struct Ov000StreamInterface {
    void (*initialize)(void);
    void (*open)(const Ov000StreamOpenParams *params);
    void (*unused08)(void);
    void (*start)(void);
} Ov000StreamInterface;

typedef struct Ov000MovieFrame {
    char formatted[0x10];
    Ov000StreamOpenParams openParams;
    char path[0x80];
} Ov000MovieFrame;

typedef struct Ov000SceneContext {
    short secondValue;
    short selectedRow;
    u8 pad_0004[0x9674];
    Ov000RowDescriptor rows[18];
    u8 pad_9828[0x392c];
    void *resource;
    Ov000StreamInterface stream;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern char gOv000ZFmt[];
extern void Ov000_TeardownTitle(void);
extern Ov000SceneContext *data_ov000_0205ac3c;
extern char gOv000UiThrMPath[];
extern void *Msg_OpenContainerAndReadHeader(const void *descriptor, int mode);
extern void strcpy(char *destination, const char *source);
extern void Ov024_MobiClip_InstallStreamSourceVtbl(Ov000StreamInterface *stream);
extern void Ov000_WaitSubSceneThenMenu(void);

Ov000StateFn Ov000_StartMovieFromMenuRow(void) {
    Ov000SceneContext *ctx = NNSi_FndGetCurrentRootHeap();
    Ov000MovieFrame frame;

    OS_SPrintf(frame.formatted, gOv000ZFmt, ctx->rows[ctx->selectedRow].displayValue);
    Ov000_TeardownTitle();
    data_ov000_0205ac3c = ctx;
    GameState_SetFlag(0x20e9);
    StoreGlobalShortAt0(0x100);
    LoadOverlaySync(0, FS_OVERLAY_ID_ov024);
    ctx->resource = Msg_OpenContainerAndReadHeader(gOv000UiThrMPath, 0xf);
    frame.openParams.resource = ctx->resource;
    frame.openParams.enabled = 1;
    strcpy(frame.path, frame.formatted);
    Ov024_MobiClip_InstallStreamSourceVtbl(&ctx->stream);
    ctx->stream.initialize();
    ctx->stream.open(&frame.openParams);
    ctx->stream.start();
    return (Ov000StateFn)Ov000_WaitSubSceneThenMenu;
}
