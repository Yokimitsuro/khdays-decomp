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

extern MissionMenuContext *data_ov006_02056660;
extern u16 data_ov006_0205651c[8];

extern int func_ov006_02055b0c(int selection);
extern int func_ov006_0204fe74(void);
extern void func_ov006_0204fef4(void);
extern int func_02001030(void);
extern u16 OS_IsTickAvailable_0x01ff8138(void);
extern int func_ov006_0204fa58(void);
extern void func_ov006_02056030(void);
extern void *func_ov006_0204d58c(void *resource, u32 index);
extern void func_ov006_0205606c(void *text, int x, int y, u8 style,
                                int layer, int align, int visible);
extern void func_ov006_02055e9c(int visible);
extern void func_ov006_02056098(void);

extern void func_ov006_020508e0(void);
extern void func_ov006_02051884(void);
extern void func_ov006_020502e4(void);

MissionState func_ov006_02050630(void)
{
    MissionState nextState = func_ov006_020508e0;
    u32 textSelector;
    u8 lineIndex;

    func_ov006_02055b0c(-1);

    if (data_ov006_02056660->sessionReady == 0 &&
        func_ov006_0204fe74() != 0) {
        func_ov006_0204fef4();
        return func_ov006_02051884;
    }

    switch (func_02001030()) {
    case 8:
        return func_ov006_020502e4;
    case 0:
    case 9:
    case 10:
        func_ov006_0204fef4();
        return func_ov006_02051884;
    case 3:
        nextState = 0;
        goto draw_screen;
    case 4:
        if (data_ov006_02056660->sessionReady != 0) {
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
        if (func_ov006_0204fa58() > 0) {
            func_ov006_02055b0c(func_ov006_0204fa58());
        }
        data_ov006_02056660->messageStateFlag = 0;
        data_ov006_02056660->messageId = 0x40;
        data_ov006_02056660->messageVariant = 0;
    }

    func_ov006_02056030();
    data_ov006_02056660->messageId = 0x40;
    if (data_ov006_02056660->sessionReady == 0) {
        data_ov006_02056660->messageVariant++;
        if (data_ov006_02056660->messageVariant > 0x3c) {
            data_ov006_02056660->messageVariant = 0;
            if (data_ov006_02056660->messageId == 0x34) {
                data_ov006_02056660->messageId = 0x40;
            } else {
                data_ov006_02056660->messageId = 0x34;
            }
        }
    }

    func_ov006_0205606c(
        func_ov006_0204d58c(&data_ov006_02056660->resource,
                            data_ov006_02056660->messageId),
        0xfa, 2, 1, 1, 1, 1);

    if (data_ov006_02056660->sessionReady != 0) {
        textSelector = 0x41;
    } else {
        textSelector = 0x42;
    }
    func_ov006_0205606c(
        func_ov006_0204d58c(&data_ov006_02056660->resource, textSelector),
        0x80, 0x60, 1, 1, 3, 1);

    for (lineIndex = 0; lineIndex < 4; lineIndex++) {
        func_ov006_0205606c(data_ov006_0205651c, 99,
                            lineIndex * 0x18 + 0x23, 1, 1, 0, 0);
    }

    if (data_ov006_02056660->sessionReady != 0) {
        func_ov006_02055e9c(0);
        func_ov006_0205606c(
            func_ov006_0204d58c(&data_ov006_02056660->resource, 0x43),
            0x80, 0x98, 1, 1, 3, 0);
    }

    func_ov006_02056098();
    return nextState;
}
