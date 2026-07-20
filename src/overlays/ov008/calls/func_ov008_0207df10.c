typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 bytes[1];
} MissionTextEngine;

typedef struct {
    u8 pad_0000[0x9400];
    MissionTextEngine engine;
} MissionTextBank;

typedef struct {
    u8 pad_000[0x36c];
    MissionTextBank bank;
} MissionAlternateTextLayout;

typedef struct {
    u8 pad_000[0x3b8];
    MissionTextBank bank;
} MissionDefaultTextLayout;

typedef union {
    MissionAlternateTextLayout alternate;
    MissionDefaultTextLayout normal;
} Ov006RootContext;

extern Ov006RootContext *data_ov008_02090fa4;
extern int func_ov008_0207de00(int color, int alternate);
extern void func_0202fa38(MissionTextEngine *engine, int x, int y,
                          int color, u32 flags, int text);

void func_ov008_0207df10(int text, int x, int y, int color,
                         int draw_shadow, int style, int alternate) {
    u32 flags = 0x200;
    MissionTextEngine *engine;
    int foreground;
    int shadow;

    switch (style) {
    case 1:
        flags = 0x821;
        break;
    case 2:
        flags = 0x411;
        break;
    case 3:
        flags = 0x412;
        break;
    }

    if (alternate != 0) {
        engine = &data_ov008_02090fa4->alternate.bank.engine;
    } else {
        engine = &data_ov008_02090fa4->normal.bank.engine;
    }

    foreground = func_ov008_0207de00(color, alternate);
    shadow = func_ov008_0207de00(2, alternate);
    if (draw_shadow != 0) {
        func_0202fa38(engine, x + 1, y + 1, shadow, flags, text);
    }
    func_0202fa38(engine, x, y, foreground, flags, text);
}
