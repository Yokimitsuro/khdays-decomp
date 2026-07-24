/* func_ov000_0205a3e0 -- start a movie from the menu row the player picked.
 *
 * Formats the selected row's value into the frame's name buffer, tears the menu down,
 * publishes the scene block in data_ov000_0205ac3c, arms handler 0x20e9, sets the fade value,
 * loads ov024 (the MobiClip player) and opens the stream resource.  The stream interface at
 * ctx+0xd158 is filled in by func_ov024_020832c4 and then driven: initialize, open with the
 * resource, start.  Control moves on to func_ov000_0205a554, which waits for it to finish.
 *
 * The overlay id is the ADDRESS of a linker-absolute symbol (NitroSDK FS_OVERLAY_ID); dsd
 * emits `OVERLAY_24_ID = 24;` into arm9.lcf.  24 is an encodable ARM immediate, so written as
 * a plain integer the pool word disappears and the function is 4 bytes short.
 */
typedef unsigned char u8;
typedef unsigned int u32;
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
extern int OS_SPrintf(char *destination, const char *format, ...);
extern char data_ov000_0205abf8[];
extern void func_ov000_02059f50(void);
extern Ov000SceneContext *data_ov000_0205ac3c;
extern int func_020235a8(int handlerId);
extern void func_02020a90(int value);
extern void func_0201e470(int processor, FSOverlayID overlayId);
extern char data_ov000_0205ac00[];
extern void *func_02024ee8(const void *descriptor, int mode);
extern void func_0201f924(char *destination, const char *source);
extern void func_ov024_020832c4(Ov000StreamInterface *stream);
extern void func_ov000_0205a554(void);

Ov000StateFn func_ov000_0205a3e0(void) {
    Ov000SceneContext *ctx = NNSi_FndGetCurrentRootHeap();
    Ov000MovieFrame frame;

    OS_SPrintf(frame.formatted, data_ov000_0205abf8, ctx->rows[ctx->selectedRow].displayValue);
    func_ov000_02059f50();
    data_ov000_0205ac3c = ctx;
    func_020235a8(0x20e9);
    func_02020a90(0x100);
    func_0201e470(0, FS_OVERLAY_ID_ov024);
    ctx->resource = func_02024ee8(data_ov000_0205ac00, 0xf);
    frame.openParams.resource = ctx->resource;
    frame.openParams.enabled = 1;
    func_0201f924(frame.path, frame.formatted);
    func_ov024_020832c4(&ctx->stream);
    ctx->stream.initialize();
    ctx->stream.open(&frame.openParams);
    ctx->stream.start();
    return (Ov000StateFn)func_ov000_0205a554;
}
