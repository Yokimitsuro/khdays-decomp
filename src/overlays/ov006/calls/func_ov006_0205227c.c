/* Mission Mode member-select: build the sprite cells for one screen layout.
 *
 * `mode` selects which screen is being entered (0/1 share the mission briefing layout,
 * 2/3 share the reward layout, 4 is the full member roster). Every cell is created
 * through the 0x02032444 interworking veneer -- despite its symbol name that thunk
 * tail-calls func_02032288, the cell allocator -- then given a display mode, an optional
 * fade step and a screen position.
 *
 * The context is reached two ways in the original: once up front through the scene
 * accessor (kept in a callee-saved register) and again through the overlay's cached
 * pointer, which has to be re-read after every call. Both name the same object.
 */

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
} MissionOffset;

typedef struct {
    MissionOffset entries[19];
} MissionOffsetTable;

typedef struct {
    int x;
    int y;
    int cell;
    int keep;
} MissionPlacementConfig;

typedef struct {
    s8 ids[6];
} MissionExtraIds;

typedef struct {
    MissionExtraIds ids;      /* +0x00 */
    u8 pad_0006[2];
    MissionOffset origin;     /* +0x08 */
} MissionSetupParams;

typedef struct {
    u8 pad_0000[0x78];
    u32 flags;                /* +0x78 */
    u8 pad_007c[0x10];
} MissionSlotEntry;           /* 0x8c */

typedef struct {
    u8 pad_0000[0x18];
    u32 flags;                /* +0x18 */
} MissionTween;               /* 0x1c */

typedef struct {
    u8 pad_0000[0x54];
    u8 sidePanel;                     /* 0x0054 */
    u8 pad_0055[0x4a37];
    u8 panel;                         /* 0x4a8c */
    u8 pad_4a8d[3];
    MissionSlotEntry entries[0x80];   /* 0x4a90 */
    u8 pad_9090[0x480];
    int pairIndex[4];                 /* 0x9510 */
    u8 unlockFlags;                   /* 0x9520 */
    u8 pad_9521[0x13];
    int pairState[4];                 /* 0x9534 */
    u8 pad_9544[0x6a];
    s8 offsetMap[19];                 /* 0x95ae */
    u8 pad_95c1[1];
    u16 selectedSlot;                 /* 0x95c2 */
    int cellBackdrop;                 /* 0x95c4 */
    int cellHeader;                   /* 0x95c8 */
    int cellBody;                     /* 0x95cc */
    int cellFrame;                    /* 0x95d0 */
    int cellTitle;                    /* 0x95d4 */
    int rowCells[4];                  /* 0x95d8 */
    int iconCells[7];                 /* 0x95e8 */
    int markCells[4];                 /* 0x9604 */
    MissionTween tweens[4];           /* 0x9614 */
    MissionTween tweensExtra[3];      /* 0x9684 */
    int cellTopBar;                   /* 0x96d8 */
    int cellCaption;                  /* 0x96dc */
    int cellFooter;                   /* 0x96e0 */
    int primaryCells[4];              /* 0x96e4 */
    int secondaryCells[4];            /* 0x96f4 */
    int cursorCells[4];               /* 0x9704 */
    int slotCells[19];                /* 0x9714 */
} Ov006MissionContext;

extern u8 data_0204c058[];
extern Ov006MissionContext *data_ov006_02056664;
extern const MissionSetupParams data_ov006_0205628c;
extern const MissionOffsetTable data_ov006_0205630c;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_02020400(int numerator, int denominator);
extern int WM_EndKeySharing_0x02032444(void *panel, int kind, int variant);
extern void func_02032494(void *panel);
extern void func_0203281c(void *panel, int cell, int mode);
extern void func_02032680(void *panel, int cell, int step);
extern void func_0203257c(void *panel, int cell, MissionOffset *pos);
extern void func_020325b8(void *panel, int cell, int order);
extern void func_020326a8(void *panel, int cell);
extern void func_020326cc(void *panel, int cell);
extern void func_02035f84(MissionTween *tween);
extern void func_ov006_02051fbc(void *panel, int cell, MissionPlacementConfig config);
extern void func_ov006_02054fb8(int slot, int selector);

void func_ov006_0205227c(int mode)
{
    MissionPlacementConfig config = {0, 0, 0, 0};
    MissionOffset pos;
    MissionExtraIds extra;
    MissionOffsetTable offsets;
    Ov006MissionContext *ctx;
    int step;
    int fade;
    int handle;
    int selector;
    u8 i;

    ctx = (Ov006MissionContext *)NNSi_FndGetCurrentRootHeap();

    switch (data_0204c058[0]) {
    case 1:
        step = 20;
        break;
    case 0:
        step = 30;
        break;
    case 2:
        step = 60;
        break;
    }
    fade = func_02020400(0x3c000, step);

    if (ctx == 0) {
        return;
    }

    func_02032494(&data_ov006_02056664->sidePanel);
    func_02032494(&data_ov006_02056664->panel);

    switch (mode) {
    case 0:
    case 1:
        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 0, 0);
        data_ov006_02056664->cellBackdrop = handle;
        config.x = 0x38;
        config.y = 0x98;
        config.cell = 0;
        config.keep = 1;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellBackdrop, 0);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellBackdrop, config);

        for (i = 0; i < 4; i++) {
            handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 2, 0);
            data_ov006_02056664->rowCells[i] = handle;
            config.y = i * 0x18 + 0x28;
            config.x = 0x80;
            config.cell = 0;
            config.keep = 0;
            func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->rowCells[i], 1);
            func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->rowCells[i], config);
        }

        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 1, 0);
        data_ov006_02056664->cellTitle = handle;
        config.x = 0x80;
        config.y = 0x28;
        config.cell = 0;
        config.keep = 1;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellTitle, 1);
        func_02032680(&data_ov006_02056664->panel, data_ov006_02056664->cellTitle, fade);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellTitle, config);

        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 5, 0);
        data_ov006_02056664->cellHeader = handle;
        config.x = 0xf8;
        config.y = 0xa8;
        config.cell = 0;
        config.keep = 0;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellHeader, 1);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellHeader, config);

        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 4, 0);
        data_ov006_02056664->cellFrame = handle;
        config.x = 0x80;
        config.y = 0x98;
        config.cell = 0;
        config.keep = 0;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellFrame, 1);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellFrame, config);

        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 3, 0);
        data_ov006_02056664->cellBody = handle;
        config.x = 0x80;
        config.y = 0x98;
        config.cell = 0;
        config.keep = 1;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellBody, 1);
        func_02032680(&data_ov006_02056664->panel, data_ov006_02056664->cellBody, fade);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellBody, config);
        return;

    case 2:
    case 3:
        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 0, 0);
        data_ov006_02056664->cellBackdrop = handle;
        config.x = 0x38;
        config.y = 0x98;
        config.cell = 0;
        config.keep = 1;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellBackdrop, 0);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellBackdrop, config);

        for (i = 0; i < 4; i++) {
            handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 0, 1);
            data_ov006_02056664->rowCells[i] = handle;
            config.y = i * 0x18 + 0x28;
            config.x = 0x88;
            config.cell = i;
            config.keep = 0;
            func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->rowCells[i], 1);
            func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->rowCells[i], config);
        }

        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 5, 0);
        data_ov006_02056664->cellHeader = handle;
        config.x = 0xf8;
        config.y = 0xa8;
        config.cell = 0;
        config.keep = 0;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellHeader, 1);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellHeader, config);

        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 4, 0);
        data_ov006_02056664->cellFrame = handle;
        config.x = 0x80;
        config.y = 0x98;
        config.cell = 0;
        config.keep = 0;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellFrame, 1);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellFrame, config);

        if (data_ov006_02056664->cellFrame >= 0) {
            ctx->entries[data_ov006_02056664->cellFrame].flags &= ~4;
        }

        handle = WM_EndKeySharing_0x02032444(&data_ov006_02056664->panel, 3, 0);
        data_ov006_02056664->cellBody = handle;
        config.x = 0x80;
        config.y = 0x98;
        config.cell = 0;
        config.keep = 1;
        func_0203281c(&data_ov006_02056664->panel, data_ov006_02056664->cellBody, 1);
        func_02032680(&data_ov006_02056664->panel, data_ov006_02056664->cellBody, fade);
        func_ov006_02051fbc(&data_ov006_02056664->panel, data_ov006_02056664->cellBody, config);
        return;

    case 4:
        handle = WM_EndKeySharing_0x02032444(&ctx->sidePanel, 0, 0);
        ctx->cellBackdrop = handle;
        config.x = 0;
        config.y = 0x24;
        config.cell = 0;
        config.keep = 0;
        func_0203281c(&ctx->sidePanel, ctx->cellBackdrop, 1);
        func_ov006_02051fbc(&ctx->sidePanel, ctx->cellBackdrop, config);

        handle = WM_EndKeySharing_0x02032444(&ctx->sidePanel, 1, 0);
        ctx->cellHeader = handle;
        config.x = 0x48;
        config.y = 0x24;
        config.cell = 0;
        config.keep = 0;
        func_0203281c(&ctx->sidePanel, ctx->cellHeader, 1);
        func_ov006_02051fbc(&ctx->sidePanel, ctx->cellHeader, config);

        for (i = 0; i < 4; i++) {
            handle = WM_EndKeySharing_0x02032444(&ctx->sidePanel, 2, 0);
            (&ctx->cellBody)[i] = handle;
            config.y = i * 0x10 + 0x3e;
            config.x = 0xa0;
            config.cell = 0;
            config.keep = 0;
            func_0203281c(&ctx->sidePanel, (&ctx->cellBody)[i], 1);
            func_ov006_02051fbc(&ctx->sidePanel, (&ctx->cellBody)[i], config);
            func_02035f84(&data_ov006_02056664->tweens[i]);
        }

        for (i = 0; i < 3; i++) {
            handle = WM_EndKeySharing_0x02032444(&ctx->sidePanel, 3, 0);
            (&ctx->rowCells[1])[i] = handle;
            config.y = i * 0x10 + 0x3e;
            config.x = 0xfd;
            config.cell = 0;
            config.keep = 0;
            func_0203281c(&ctx->sidePanel, (&ctx->rowCells[1])[i], 1);
            func_ov006_02051fbc(&ctx->sidePanel, (&ctx->rowCells[1])[i], config);
            func_02035f84(&data_ov006_02056664->tweensExtra[i]);
        }

        for (i = 0; i < 7; i++) {
            handle = WM_EndKeySharing_0x02032444(&ctx->sidePanel, 4, 0);
            ctx->iconCells[i] = handle;
            if (i < 4) {
                config.x = 0xa0;
                config.y = i * 0x10 + 0x3e;
            } else {
                config.x = 0xfd;
                config.y = (i - 4) * 0x10 + 0x3e;
            }
            config.cell = 0;
            config.keep = 0;
            func_ov006_02051fbc(&ctx->sidePanel, ctx->iconCells[i], config);
            func_02035f84(&data_ov006_02056664->tweens[i]);
        }

        for (i = 0; i < 4; i++) {
            handle = WM_EndKeySharing_0x02032444(&ctx->sidePanel, 0, 1);
            ctx->markCells[i] = handle;
            switch (i) {
            case 0:
                config.x = 8;
                config.y = 0xa0;
                break;
            case 1:
                config.x = 0x88;
                config.y = 0xa0;
                break;
            case 2:
                config.x = 8;
                config.y = 0xb5;
                break;
            case 3:
                config.x = 0x88;
                config.y = 0xb5;
                break;
            default:
                config.x = 0;
                config.y = 0;
            }
            config.keep = 0;
            config.cell = i;
            func_ov006_02051fbc(&ctx->sidePanel, ctx->markCells[i], config);
        }

        handle = WM_EndKeySharing_0x02032444(&ctx->panel, 0xe, 1);
        ctx->cellCaption = handle;
        config.x = 0x84;
        config.y = 0xa8;
        config.cell = 0;
        config.keep = 0;
        func_ov006_02051fbc(&ctx->panel, ctx->cellCaption, config);
        func_0203281c(&ctx->panel, ctx->cellCaption, 0);
        if (ctx->cellCaption >= 0) {
            ctx->entries[ctx->cellCaption].flags &= ~4;
        }

        handle = WM_EndKeySharing_0x02032444(&ctx->panel, 0, 1);
        ctx->cellTopBar = handle;
        config.x = 0x80;
        config.y = 0xc;
        config.cell = 0;
        config.keep = 0;
        func_ov006_02051fbc(&ctx->panel, ctx->cellTopBar, config);
        func_0203281c(&ctx->panel, ctx->cellTopBar, 1);

        handle = WM_EndKeySharing_0x02032444(&ctx->panel, 0, 0);
        ctx->cellFooter = handle;
        config.x = 0xf8;
        config.y = 0xa8;
        config.cell = 0;
        config.keep = 0;
        func_ov006_02051fbc(&ctx->panel, ctx->cellFooter, config);

        pos = data_ov006_0205628c.origin;
        for (i = 0; i < 4; i++) {
            ctx->primaryCells[i] = WM_EndKeySharing_0x02032444(&ctx->panel, i + 5, 1);
            ctx->secondaryCells[i] = WM_EndKeySharing_0x02032444(&ctx->panel, i + 1, 1);
            ctx->cursorCells[i] = WM_EndKeySharing_0x02032444(&ctx->panel, i + 9, 1);
            func_0203257c(&ctx->panel, ctx->cursorCells[i], &pos);
            ctx->pairIndex[i] = i;
            ctx->pairState[i] = 0;
            func_ov006_02054fb8(i, ctx->pairIndex[i]);
            if (i == data_ov006_02056664->selectedSlot) {
                func_020326a8(&ctx->panel, ctx->primaryCells[i]);
            } else {
                func_020326cc(&ctx->panel, ctx->primaryCells[i]);
            }
            func_020326a8(&ctx->panel, ctx->cursorCells[i]);
            func_020325b8(&ctx->panel, ctx->primaryCells[i], (0x80 - i) & 0xff);
            func_020325b8(&ctx->panel, ctx->secondaryCells[i], (100 - i) & 0xff);
            func_0203281c(&data_ov006_02056664->panel, ctx->primaryCells[i], 1);
            func_0203281c(&data_ov006_02056664->panel, ctx->secondaryCells[i], 0);
            pos.y += 0x8000;
        }

        extra = data_ov006_0205628c.ids;
        data_ov006_02056664->offsetMap[0] = 1;
        data_ov006_02056664->offsetMap[1] = 2;
        data_ov006_02056664->offsetMap[2] = 3;
        data_ov006_02056664->offsetMap[3] = 4;
        data_ov006_02056664->offsetMap[4] = 5;
        data_ov006_02056664->offsetMap[5] = 6;
        data_ov006_02056664->offsetMap[6] = 7;
        data_ov006_02056664->offsetMap[7] = 0xb;
        data_ov006_02056664->offsetMap[8] = 0xc;
        data_ov006_02056664->offsetMap[9] = 0xd;
        data_ov006_02056664->offsetMap[10] = 0xe;
        data_ov006_02056664->offsetMap[11] = 0xf;
        data_ov006_02056664->offsetMap[12] = 0x10;
        if ((data_ov006_02056664->unlockFlags & 1) != 0) {
            data_ov006_02056664->offsetMap[13] = extra.ids[0];
        }
        if ((data_ov006_02056664->unlockFlags & 8) != 0) {
            data_ov006_02056664->offsetMap[16] = extra.ids[1];
        }
        if ((data_ov006_02056664->unlockFlags & 0x10) != 0) {
            data_ov006_02056664->offsetMap[17] = extra.ids[2];
        }
        if ((data_ov006_02056664->unlockFlags & 0x20) != 0) {
            data_ov006_02056664->offsetMap[18] = extra.ids[3];
        }
        if ((data_ov006_02056664->unlockFlags & 4) != 0) {
            data_ov006_02056664->offsetMap[15] = extra.ids[4];
        }
        if ((data_ov006_02056664->unlockFlags & 2) != 0) {
            data_ov006_02056664->offsetMap[14] = extra.ids[5];
        }

        i = 0;
        offsets = data_ov006_0205630c;
        do {
            ctx->slotCells[i] = WM_EndKeySharing_0x02032444(&ctx->panel, i + 1, 0);
            selector = i;
            if (selector == -1 || selector >= 19) {
                config.x = -48;
                config.y = -128;
            } else {
                s8 mapped = data_ov006_02056664->offsetMap[selector];

                if (mapped == 20) {
                    config.x = -48;
                    config.y = -128;
                } else {
                    config.x = offsets.entries[mapped].x;
                    config.y = offsets.entries[mapped].y;
                }
            }
            config.cell = 1;
            config.keep = 0;
            func_ov006_02051fbc(&ctx->panel, ctx->slotCells[i], config);
            func_0203281c(&data_ov006_02056664->panel, ctx->slotCells[i], 2);
            i++;
        } while (i < 0x13);
        break;

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    }
}
