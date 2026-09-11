typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct Ov009Pair {
    int x;
    int y;
} Ov009Pair;

typedef struct Ov009PageContext {
    int pageIndex;
    int fallbackPage;
    int activeState;
    u8 pad_00c[0x68 - 0x0c];
    Ov009Pair cellOffset[3][8];
    Ov009Pair pageTarget[3];
    Ov009Pair pageCurrent[3];
} Ov009PageContext;

typedef struct Ov009ObjectConfig {
    int resource;
    int field_04;
    int field_08;
    int field_0c;
} Ov009ObjectConfig;

extern const Ov009ObjectConfig data_ov008_0208f500;
extern const char data_ov008_020904d0[];
extern const int data_ov008_0208f588[3][8];
extern void WM_EndKeySharing_0x020698ec(void);

extern int         func_ov008_02050f84(int index);
extern int         func_ov008_02050c54(void);
extern void        func_ov008_02054744(int object,
                                      const Ov009ObjectConfig *config);
extern void        func_ov008_02054678(int object, const void *resource,
                                      int value);
extern void        func_ov008_0205477c(int object, int value);
extern void        func_020327e0(int object, int value);
extern void        G2x_SetBlendAlpha_(volatile void *reg, int firstTarget,
                                     int secondTarget, int eva, int evb);
extern int        *func_ov008_02054788(int object, int id);
extern void        func_ov008_02054c08(int object, int *entry);
extern Ov009Pair  *func_ov008_02054820(int object, int *entry);
extern void        func_ov008_02054858(int object, int *entry,
                                      const Ov009Pair *position);
extern void        func_ov008_02054d90(int object, int *entry, int value);
extern void        func_ov008_02068d58(int enabled, int mode);
extern void        func_ov008_02054ba4(int object, int *entry, int visible);
extern void        func_ov008_020697a4(Ov009PageContext *context);
extern Ov009Pair  *func_ov008_0205489c(int object, int *entry);

void func_ov008_02067edc(Ov009PageContext *context)
{
    Ov009ObjectConfig config = data_ov008_0208f500;
    Ov009Pair shiftedPosition;
    Ov009Pair finalPosition;
    int pageIndex;
    u32 itemIndex;
    int object;
    int *entry;
    Ov009Pair *position;

    config.resource = func_ov008_02050f84(3);
    object = func_ov008_02050c54();
    func_ov008_02054744(object, &config);
    func_ov008_02054678(object, data_ov008_020904d0, 0x24);
    func_ov008_0205477c(object, (int)WM_EndKeySharing_0x020698ec);
    func_020327e0(object, 8);
    G2x_SetBlendAlpha_((volatile void *)0x04000050, 4, 0x10, 8, 8);

    entry = func_ov008_02054788(object, 0x0b);
    func_ov008_02054c08(object, entry);
    entry = func_ov008_02054788(object, 0x0d);
    func_ov008_02054c08(object, entry);

    context->pageTarget[0].x = 0x100000;
    context->pageTarget[1].x = 0x138000;
    context->pageTarget[2].x = 0x170000;

    for (pageIndex = 0; pageIndex < 3; pageIndex++) {
        for (itemIndex = 0; itemIndex < 8; itemIndex++) {
            entry = func_ov008_02054788(
                object, data_ov008_0208f588[pageIndex][itemIndex]);
            position = func_ov008_02054820(object, entry);
            context->cellOffset[pageIndex][itemIndex].x = position->x;
            context->cellOffset[pageIndex][itemIndex].y = position->y;
            shiftedPosition = *position;
            shiftedPosition.x += 0x100000;
            func_ov008_02054858(object, entry, &shiftedPosition);
            func_ov008_02054c08(object, entry);
        }
    }

    entry = func_ov008_02054788(object, 0x14);
    func_ov008_02054d90(object, entry, 2);
    entry = func_ov008_02054788(object, 0x15);
    func_ov008_02054d90(object, entry, 2);

    func_ov008_02068d58(1, 0);

    entry = func_ov008_02054788(object, 0x3c);
    func_ov008_02054d90(object, entry, 2);
    func_ov008_02054ba4(object, entry, 0);

    func_ov008_020697a4(context);

    entry = func_ov008_02054788(object, 0x11);
    func_ov008_02054ba4(object, entry, 0);

    entry = func_ov008_02054788(object, 0x10);
    position = func_ov008_0205489c(object, entry);
    finalPosition = *position;
    finalPosition.x += 0x8000;
    func_ov008_02054858(object, entry, &finalPosition);
}
