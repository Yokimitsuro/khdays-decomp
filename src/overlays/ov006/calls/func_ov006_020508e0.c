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
    u32 parametersReady;
    u32 singleRowMode;
    u32 menuState;
    u8 optionMask;
    u8 messageStateFlag;
    u16 messageId;
    u16 messageVariant;
    u8 pad_36[0x2a];
    MissionResourceRecord resource;
} MissionMenuContext;

extern MissionMenuContext *data_ov006_02056660;
extern u16 data_ov006_0205651c[8];

extern int func_ov006_0204fe74(void);
extern void func_ov006_0204fef4(void);
extern int func_02001030(void);
extern int func_ov006_02050090(void);
extern int func_ov006_0204fe4c(void);
extern int func_ov006_02051ab0(void);
extern int OS_IsTickAvailable(void);
extern int func_ov006_0204f674(void);
extern void func_ov006_02055a54(int state, int arg1, int arg2);
extern void func_02033b78(int bank, int sound);
extern int func_ov006_0204fe2c(void);
extern void func_ov006_0204fdf0(u8 value);
extern int func_ov006_0204fdd8(void);
extern void func_ov006_0204fdac(void);
extern void func_ov006_02056030(void);
extern void *func_ov006_0204d58c(void *resource, u32 index);
extern void func_ov006_0205606c(void *text, int x, int y, u8 style,
                                int layer, int align, int visible);
extern u16 func_ov006_0204fad0(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_ov006_0204fa30(void *destination);
extern void func_ov006_02055e9c(int visible);
extern void func_ov006_02055b0c(int selection);
extern u16 OS_IsTickAvailable_0x01ff8138(void);
extern int func_ov006_0204fa58(void);
extern void func_ov006_02056098(void);

extern void func_ov006_02051884(void);
extern void func_ov006_020502e4(void);
extern void func_ov006_02050e1c(void);

MissionState func_ov006_020508e0(void)
{
    MissionState nextState;
    int menuAction;
    int transitionReady;
    void *textRecord;
    u16 optionMask;
    u16 optionTextRows[44];
    u32 sourceRowIndex;
    u32 visibleRowIndex;
    u32 textId;

    nextState = 0;
    menuAction = 0;

    if (data_ov006_02056660->sessionReady == 0 &&
        func_ov006_0204fe74() != 0) {
        func_ov006_0204fef4();
        return func_ov006_02051884;
    }

    if (func_02001030() == 8) {
        return func_ov006_020502e4;
    }

    if (func_ov006_02050090() != 0) {
        func_ov006_0204fef4();
        return func_ov006_02051884;
    }

    if (func_ov006_0204fe4c() == 0) {
        menuAction = func_ov006_02051ab0();
    }

    transitionReady = 1;
    if (data_ov006_02056660->sessionReady != 0) {
        if (OS_IsTickAvailable() != 0) {
            transitionReady = 0;
        }
        if (data_ov006_02056660->messageStateFlag != 0) {
            transitionReady = 0;
        }
    }

    if (transitionReady != 0 && menuAction == 1) {
        if (data_ov006_02056660->sessionReady != 0) {
            data_ov006_02056660->singleRowMode = func_ov006_0204f674();
        }
        data_ov006_02056660->messageStateFlag = 4;
        func_ov006_02055a54(0xd, 1, 0);
        func_02033b78(0, 0x30);
        nextState = func_ov006_02050e1c;
    }

    switch (data_ov006_02056660->messageStateFlag) {
    case 0:
        if (func_ov006_0204fe2c() == 0 &&
            func_02001030() == 4 &&
            (data_ov006_02056660->sessionReady != 0 ||
             func_ov006_0204fe4c() == 0) &&
            menuAction == 3) {
            if (data_ov006_02056660->sessionReady == 0) {
                func_ov006_0204fdf0(1);
                data_ov006_02056660->messageStateFlag = 1;
            } else {
                func_02033b78(0, 3);
                data_ov006_02056660->messageStateFlag = 2;
            }
        }
        break;

    case 1:
        menuAction = func_ov006_0204fe2c();
        if (menuAction != 1) {
            break;
        }
        func_02033b78(0, 3);
        data_ov006_02056660->messageStateFlag = 2;
    case 2:
        if (func_ov006_0204fdd8() == 0) {
            func_ov006_0204fdac();
        }
        data_ov006_02056660->messageStateFlag = 3;
        break;

    case 3:
        if (func_ov006_0204fdd8() != 0) {
            nextState = func_ov006_020502e4;
        }
        break;
    }

    func_ov006_02056030();

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

    textRecord = func_ov006_0204d58c(
        &data_ov006_02056660->resource,
        data_ov006_02056660->messageId);
    func_ov006_0205606c(textRecord, 0xfa, 2, 1, 1, 1, 1);

    if (data_ov006_02056660->sessionReady != 0) {
        textId = 0x41;
    } else {
        textId = 0x42;
    }
    textRecord = func_ov006_0204d58c(
        &data_ov006_02056660->resource, textId);
    func_ov006_0205606c(textRecord, 0x80, 0x60, 1, 1, 3, 1);

    optionMask = func_ov006_0204fad0();
    MI_CpuFill8(optionTextRows, 0, 0x58);
    func_ov006_0204fa30(optionTextRows);

    visibleRowIndex = 0;
    sourceRowIndex = 0;
    do {
        if ((optionMask & (1 << sourceRowIndex)) != 0 &&
            *(u16 *)((u8 *)optionTextRows + sourceRowIndex * 0x16) != 0) {
            func_ov006_0205606c(
                (u8 *)optionTextRows + sourceRowIndex * 0x16, 99,
                visibleRowIndex * 0x18 + 0x23, 1, 1, 0, 0);
            visibleRowIndex = (visibleRowIndex + 1) & 0xff;
        }
        sourceRowIndex = (sourceRowIndex + 1) & 0xff;
    } while (sourceRowIndex < 4);

    while (visibleRowIndex < 4) {
        func_ov006_0205606c(
            data_ov006_0205651c, 99,
            visibleRowIndex * 0x18 + 0x23, 1, 1, 0, 0);
        visibleRowIndex = (visibleRowIndex + 1) & 0xff;
    }

    if (data_ov006_02056660->sessionReady != 0) {
        if (func_ov006_0204fe4c() == 0) {
            textRecord = func_ov006_0204d58c(
                &data_ov006_02056660->resource, 0x43);
            func_ov006_0205606c(textRecord, 0x80, 0x98, 1, 1, 3, 0);
            func_ov006_02055e9c(1);
        } else {
            func_ov006_02055e9c(0);
            textRecord = func_ov006_0204d58c(
                &data_ov006_02056660->resource, 0x43);
            func_ov006_0205606c(textRecord, 0x80, 0x98, 1, 1, 3, 0);
        }
    }

    func_ov006_02055b0c(-1);
    if (data_ov006_02056660->sessionReady != 0) {
        if (OS_IsTickAvailable_0x01ff8138() > 1) {
            func_ov006_02055b0c(func_ov006_0204fa58());
        }
    } else {
        if (OS_IsTickAvailable_0x01ff8138() != 0) {
            func_ov006_02055b0c(func_ov006_0204fa58());
        }
    }

    if (func_02001030() == 4 && func_ov006_0204fe4c() == 0) {
        if (data_ov006_02056660->sessionReady != 0) {
            textId = 0x45;
        } else {
            textId = 0x46;
        }
        textRecord = func_ov006_0204d58c(
            &data_ov006_02056660->resource, textId);
        func_ov006_0205606c(textRecord, 10, 0xb4, 1, 1, 0, 0);
    }

    func_ov006_02056098();
    return nextState;
}