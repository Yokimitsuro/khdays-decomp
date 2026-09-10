/* Draws one of the three mission-summary headings into the shared heading
 * surface. Multiplayer waits for the session-ready signal before touching the
 * surface; every accepted call brackets its draw with begin/submit. */
typedef unsigned char u8;

typedef struct Ov008MenuContext {
    u8 pad0000[0x1420];
    u8 headingSurface[0x3c];
    u8 pad145c[0x84];
    int multiplayerMode;
    u8 pad14e4[0x10];
    u8 textRecords[0x48];
} Ov008MenuContext;

extern Ov008MenuContext *func_ov025_02084afc(void);
extern int func_02030694(void);
extern void func_02030158(void *object);
extern void *func_ov025_02089894(void *records, int index);
extern void func_020301c8(void *object, int x, int y, int enabled,
                          unsigned int flags, const void *text);
extern void func_020300f8(void *object);
extern const u8 data_ov025_020b4d10[];

void func_ov025_0208e000(int headingMode)
{
    Ov008MenuContext *menuContext = func_ov025_02084afc();
    void *text;

    if (menuContext->multiplayerMode != 0 && func_02030694() == 0) {
        return;
    }

    func_02030158(menuContext->headingSurface);
    switch (headingMode) {
    case 0:
        func_020301c8(menuContext->headingSurface, 0x8e, 2, 1, 0x821,
                      data_ov025_020b4d10);
        break;
    case 1:
        text = func_ov025_02089894(menuContext->textRecords, 2);
        func_020301c8(menuContext->headingSurface, 0x8e, 2, 1, 0x821, text);
        break;
    case 2:
        text = func_ov025_02089894(menuContext->textRecords, 0);
        func_020301c8(menuContext->headingSurface, 0x8e, 2, 1, 0x821, text);
        break;
    }
    func_020300f8(menuContext->headingSurface);
}
