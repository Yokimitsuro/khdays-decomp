typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

typedef enum BGSelect {
    BGSELECT_MAIN0,
    BGSELECT_MAIN1,
    BGSELECT_MAIN2,
    BGSELECT_MAIN3,
    BGSELECT_SUB0,
    BGSELECT_SUB1,
    BGSELECT_SUB2,
    BGSELECT_SUB3
} BGSelect;

typedef struct PaletteData {
    int format;
} PaletteData;

typedef struct ScreenData {
    u16 width;
    u16 height;
    u16 colorMode;
    u16 screenFormat;
} ScreenData;

extern int func_02024924(BGSelect bg, BOOL useExtended,
                         const PaletteData *palette);

static inline BOOL IsMainBG(BGSelect bg)
{
    return bg <= BGSELECT_MAIN3;
}

/* GBATEK: DISPCNT for the two engines; bit 30 selects extended palettes. */
#define REG_DISPCNT   (*(volatile u32 *)0x04000000)
#define REG_DB_DISPCNT (*(volatile u32 *)0x04001000)
#define DISPCNT_BG_EXT_PLTT 0x40000000

static inline BOOL IsBGUseExtPlttMain(void)
{
    return (REG_DISPCNT & DISPCNT_BG_EXT_PLTT) != 0;
}

static inline BOOL IsBGUseExtPlttSub(void)
{
    return (REG_DB_DISPCNT & DISPCNT_BG_EXT_PLTT) != 0;
}

static inline BOOL IsBGUseExtPltt(BGSelect bg)
{
    return IsMainBG(bg) ? IsBGUseExtPlttMain() : IsBGUseExtPlttSub();
}

int func_02024a6c(BGSelect bg, const PaletteData *palette,
                  const ScreenData *screen)
{
    u16 screenFormat = screen->screenFormat;

    if (screenFormat == 0 && screen->colorMode == 1) {
        return func_02024924(bg, IsBGUseExtPltt(bg), palette);
    }

    return func_02024924(bg,
                         palette->format != 3 && screenFormat != 1,
                         palette);
}
