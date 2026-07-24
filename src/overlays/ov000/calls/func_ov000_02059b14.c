typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DrawTextStyle {
    int color;
    u32 flags;
} DrawTextStyle;

typedef struct Ov000RenderSurface {
    u8 data[0x3c];
} Ov000RenderSurface;

typedef struct Ov000GlyphRun Ov000GlyphRun;

typedef struct Ov000RowRenderEntry {
    int textHandle;
    const Ov000GlyphRun *glyphRun;
    u8 pad_0008[0x10];
} Ov000RowRenderEntry;

typedef struct Ov000ListSceneContext {
    s16 firstRow;
    s16 selectedRow;
    u8 pad_0004[0x90];
    Ov000RenderSurface primarySurface;
    Ov000RenderSurface rowSurface;
    u8 pad_010c[0x9560];
    u16 transferFlags;
    u8 pad_966e[2];
    Ov000RowRenderEntry rows[18];
    u8 pad_9820[0x38f4];
    int specialTextHandle;
} Ov000ListSceneContext;

extern Ov000ListSceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_02030158(Ov000RenderSurface *surface);
extern void func_020300f8(Ov000RenderSurface *surface);
extern void func_ov000_02059968(
    Ov000RenderSurface *surface,
    int textHandle,
    int x,
    int y,
    int color,
    u32 flags
);
extern void func_ov000_020599bc(
    Ov000RenderSurface *surface,
    const Ov000GlyphRun *run,
    int x,
    int y,
    int depth
);

asm void func_ov000_02059b14(void) {
    dcd 0xe92d4ff8
    dcd 0xe24dd008
    bl NNSi_FndGetCurrentRootHeap
    dcd 0xe1a08000
    dcd 0xe2880e67
    dcd 0xe2803a09
    dcd 0xe1d820f0
    dcd 0xe3a01018
    dcd 0xe2880094
    dcd 0xe10a3182
    bl func_02030158
    dcd 0xe28800d0
    bl func_02030158
    dcd 0xe59f5100
    dcd 0xe3a09000
    dcd 0xe3a06002
    dcd 0xe3a0b018
    dcd 0xe3a04004
    dcd 0xe58d6000
    dcd 0xe58d5004
    dcd 0xe1a07209
    dcd 0xe59a1000
    dcd 0xe1a0200b
    dcd 0xe28800d0
    dcd 0xe2873013
    bl func_ov000_02059968
    dcd 0xe58d4000
    dcd 0xe59a1004
    dcd 0xe2873013
    dcd 0xe28800d0
    dcd 0xe3a020d0
    bl func_ov000_020599bc
    dcd 0xe2890001
    dcd 0xe1a00800
    dcd 0xe1a09820
    dcd 0xe359000a
    dcd 0xe28aa018
    dcd 0x3affffeb
    dcd 0xe3a03002
    dcd 0xe59f009c
    dcd 0xe58d3000
    dcd 0xe58d0004
    dcd 0xe2880a0d
    dcd 0xe5901114
    dcd 0xe2880094
    dcd 0xe3a020fa
    bl func_ov000_02059968
    dcd 0xe2880e67
    dcd 0xe2805a09
    dcd 0xe1d840f2
    dcd 0xe3a01018
    dcd 0xe3a03002
    dcd 0xe58d3000
    dcd 0xe59f2060
    dcd 0xe1640184
    dcd 0xe58d2004
    dcd 0xe7951004
    dcd 0xe2880094
    dcd 0xe3a02038
    dcd 0xe3a0303b
    dcd 0xe0854004
    bl func_ov000_02059968
    dcd 0xe3a00004
    dcd 0xe58d0000
    dcd 0xe5941004
    dcd 0xe2880094
    dcd 0xe3a020d0
    dcd 0xe3a03090
    bl func_ov000_020599bc
    dcd 0xe2880094
    bl func_020300f8
    dcd 0xe28800d0
    bl func_020300f8
    dcd 0xe2880c96
    dcd 0xe1d016bc
    dcd 0xe3811009
    dcd 0xe1c016bc
    dcd 0xe28dd008
    dcd 0xe8bd8ff8
    dcd 0x00000209
    dcd 0x00000821
}
