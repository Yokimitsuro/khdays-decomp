/* Refresh the result status message and configured title, then mark their buffer dirty. */
#pragma opt_propagation off
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct TileSurface { char data[60]; } TileSurface;
typedef struct Ov005TextTable { void *resource; int count; void *entries; } Ov005TextTable;
typedef struct Ov005Config { u16 sceneId, missionIndex; const u16 *resultTitle; } Ov005Config;
typedef struct Ov005ResultContext {
    char unknown00[0x4ae0];
    TileSurface textSurfaces[2];
    int activeTextBufferIndex;
    char unknown4b5c[24];
    int resultPhase;
    char unknown4b78[8];
    u8 dirtyTextBuffers;
    char unknown4b81[0xb7];
    Ov005TextTable menuText;
} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern void func_02030158(TileSurface *), func_020300f8(TileSurface *);
extern const u16 *func_ov005_0204e4f8(Ov005TextTable *, unsigned int);
extern void func_ov005_02056344(TileSurface *, const u16 *, int, int, int, unsigned int, int);
void func_ov005_020563b0(void) {
    Ov005Config *config = &data_ov005_0205b85c;
    TileSurface *surface = &data_ov005_0205b810->textSurfaces[0];
    const u16 *text;
    func_02030158(surface);
    text = func_ov005_0204e4f8(&data_ov005_0205b810->menuText,
                             data_ov005_0205b810->resultPhase < 2);
    func_ov005_02056344(surface, text, 147, 2, 241, 0x821, 1);
    func_020300f8(surface);
    surface = &data_ov005_0205b810->textSurfaces[1];
    func_02030158(surface);
    func_ov005_02056344(surface, config->resultTitle, 5, 0, 241, 0x209, 1);
    func_020300f8(surface);
    data_ov005_0205b810->dirtyTextBuffers |= 1 << data_ov005_0205b810->activeTextBufferIndex;
}
