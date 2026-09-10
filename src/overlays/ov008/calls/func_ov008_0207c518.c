typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionState)(void);

typedef struct {
    void *resourceBase;
    u32 resourceValue;
    void *resourceData;
} MissionResourceRecord;

typedef struct {
    u8 pad_00[0x20];
    u32 sessionReady;
    u8 pad_24[0x0d];
    u8 messageStateFlag;
    u16 messageId;
    u16 messageVariant;
    u8 pad_36[0x2a];
    MissionResourceRecord resource;
} MissionMenuContext;

extern MissionMenuContext *data_ov008_02090fa0;
extern u16 data_ov008_02090d0c[8];

extern int func_ov008_0208187c(int selection);
extern int func_ov008_0207bc58(void);
extern void func_ov008_0207bcd8(void);
extern int func_02001030(void);
extern u16 OS_IsTickAvailable_0x01ff8138(void);
extern int func_ov008_0207b7b4(void);
extern void func_ov008_02081da0(void);
extern void *func_ov008_02055c84(void *resource, u32 index);
extern void func_ov008_02081ddc(void *text, int x, int y, u8 style,
                                int layer, int align, int visible);
extern void func_ov008_02081c0c(int visible);
extern void func_ov008_02081e08(void);

extern void func_ov008_0207c7c8(void);
extern void func_ov008_0207d5d8(void);
extern void func_ov008_0207c1cc(void);

MissionState func_ov008_0207c518(void)
{
    MissionState nextState = func_ov008_0207c7c8;
    u32 textSelector;
    u8 lineIndex;

    func_ov008_0208187c(-1);

    if (data_ov008_02090fa0->sessionReady == 0 &&
        func_ov008_0207bc58() != 0) {
        func_ov008_0207bcd8();
        return func_ov008_0207d5d8;
    }

    switch (func_02001030()) {
    case 8:
        return func_ov008_0207c1cc;
    case 0:
    case 9:
    case 10:
        func_ov008_0207bcd8();
        return func_ov008_0207d5d8;
    case 3:
        nextState = 0;
        goto draw_screen;
    case 4:
        if (data_ov008_02090fa0->sessionReady != 0) {
            if (OS_IsTickAvailable_0x01ff8138() != 1) {
                nextState = 0;
            }
        } else {
            if (OS_IsTickAvailable_0x01ff8138() == 0) {
                nextState = 0;
            }
        }
        goto draw_screen;
    default:
        break;
    }

    nextState = 0;

draw_screen:
    if (nextState != 0) {
        if (func_ov008_0207b7b4() > 0) {
            func_ov008_0208187c(func_ov008_0207b7b4());
        }
        data_ov008_02090fa0->messageStateFlag = 0;
        data_ov008_02090fa0->messageId = 0x40;
        data_ov008_02090fa0->messageVariant = 0;
    }

    func_ov008_02081da0();
    data_ov008_02090fa0->messageId = 0x40;
    if (data_ov008_02090fa0->sessionReady == 0) {
        data_ov008_02090fa0->messageVariant++;
        if (data_ov008_02090fa0->messageVariant > 0x3c) {
            data_ov008_02090fa0->messageVariant = 0;
            if (data_ov008_02090fa0->messageId == 0x34) {
                data_ov008_02090fa0->messageId = 0x40;
            } else {
                data_ov008_02090fa0->messageId = 0x34;
            }
        }
    }

    func_ov008_02081ddc(
        func_ov008_02055c84(&data_ov008_02090fa0->resource,
                            data_ov008_02090fa0->messageId),
        0xfa, 2, 1, 1, 1, 1);

    if (data_ov008_02090fa0->sessionReady != 0) {
        textSelector = 0x41;
    } else {
        textSelector = 0x42;
    }
    func_ov008_02081ddc(
        func_ov008_02055c84(&data_ov008_02090fa0->resource, textSelector),
        0x80, 0x60, 1, 1, 3, 1);

    for (lineIndex = 0; lineIndex < 4; lineIndex++) {
        func_ov008_02081ddc(data_ov008_02090d0c, 99,
                            lineIndex * 0x18 + 0x23, 1, 1, 0, 0);
    }

    if (data_ov008_02090fa0->sessionReady != 0) {
        func_ov008_02081c0c(0);
        func_ov008_02081ddc(
            func_ov008_02055c84(&data_ov008_02090fa0->resource, 0x43),
            0x80, 0x98, 1, 1, 3, 0);
    }

    func_ov008_02081e08();
    return nextState;
}
