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

extern const Ov009ObjectConfig data_ov025_020b4060;
extern const char data_ov025_020b4e9c[];
extern const int data_ov025_020b40e8[3][8];
extern void WM_EndKeySharing_0x0209bccc(void);

extern int         func_ov025_02084d94(int index);
extern int         func_ov025_02084a7c(void);
extern void        func_ov025_020883f8(int object,
                                      const Ov009ObjectConfig *config);
extern void        func_ov025_0208832c(int object, const void *resource,
                                      int value);
extern void        func_ov025_02088430(int object, int value);
extern void        func_020327e0(int object, int value);
extern void        G2x_SetBlendAlpha_(volatile void *reg, int firstTarget,
                                     int secondTarget, int eva, int evb);
extern int        *func_ov025_0208843c(int object, int id);
extern void        func_ov025_020888b0(int object, int *entry);
extern Ov009Pair  *func_ov025_020884c8(int object, int *entry);
extern void        func_ov025_02088500(int object, int *entry,
                                      const Ov009Pair *position);
extern void        func_ov025_02088a38(int object, int *entry, int value);
extern void        func_ov025_0209b138(int enabled, int mode);
extern void        func_ov025_0208884c(int object, int *entry, int visible);
extern void        func_ov025_0209bb84(Ov009PageContext *context);
extern Ov009Pair  *func_ov025_02088544(int object, int *entry);

void func_ov025_0209a2bc(Ov009PageContext *context)
{
    Ov009ObjectConfig config = data_ov025_020b4060;
    Ov009Pair shiftedPosition;
    Ov009Pair finalPosition;
    int pageIndex;
    u32 itemIndex;
    int object;
    int *entry;
    Ov009Pair *position;

    config.resource = func_ov025_02084d94(3);
    object = func_ov025_02084a7c();
    func_ov025_020883f8(object, &config);
    func_ov025_0208832c(object, data_ov025_020b4e9c, 0x24);
    func_ov025_02088430(object, (int)WM_EndKeySharing_0x0209bccc);
    func_020327e0(object, 8);
    G2x_SetBlendAlpha_((volatile void *)0x04000050, 4, 0x10, 8, 8);

    entry = func_ov025_0208843c(object, 0x0b);
    func_ov025_020888b0(object, entry);
    entry = func_ov025_0208843c(object, 0x0d);
    func_ov025_020888b0(object, entry);

    context->pageTarget[0].x = 0x100000;
    context->pageTarget[1].x = 0x138000;
    context->pageTarget[2].x = 0x170000;

    for (pageIndex = 0; pageIndex < 3; pageIndex++) {
        for (itemIndex = 0; itemIndex < 8; itemIndex++) {
            entry = func_ov025_0208843c(
                object, data_ov025_020b40e8[pageIndex][itemIndex]);
            position = func_ov025_020884c8(object, entry);
            context->cellOffset[pageIndex][itemIndex].x = position->x;
            context->cellOffset[pageIndex][itemIndex].y = position->y;
            shiftedPosition = *position;
            shiftedPosition.x += 0x100000;
            func_ov025_02088500(object, entry, &shiftedPosition);
            func_ov025_020888b0(object, entry);
        }
    }

    entry = func_ov025_0208843c(object, 0x14);
    func_ov025_02088a38(object, entry, 2);
    entry = func_ov025_0208843c(object, 0x15);
    func_ov025_02088a38(object, entry, 2);

    func_ov025_0209b138(1, 0);

    entry = func_ov025_0208843c(object, 0x3c);
    func_ov025_02088a38(object, entry, 2);
    func_ov025_0208884c(object, entry, 0);

    func_ov025_0209bb84(context);

    entry = func_ov025_0208843c(object, 0x11);
    func_ov025_0208884c(object, entry, 0);

    entry = func_ov025_0208843c(object, 0x10);
    position = func_ov025_02088544(object, entry);
    finalPosition = *position;
    finalPosition.x += 0x8000;
    func_ov025_02088500(object, entry, &finalPosition);
}
