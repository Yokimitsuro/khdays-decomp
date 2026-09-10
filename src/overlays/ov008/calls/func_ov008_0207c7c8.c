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

extern MissionMenuContext *data_ov008_02090fa0;
extern u16 data_ov008_02090d0c[8];

extern int func_ov008_0207bc58(void);
extern void func_ov008_0207bcd8(void);
extern int func_02001030(void);
extern int func_ov008_0207be38(void);
extern int func_ov008_0207bc30(void);
extern int func_ov008_0207d804(void);
extern int OS_IsTickAvailable(void);
extern int func_ov008_0207b3d0(void);
extern void func_ov008_020817c4(int state, int arg1, int arg2);
extern void func_02033b78(int bank, int sound);
extern int func_ov008_0207bc10(void);
extern void func_ov008_0207bbd4(u8 value);
extern int func_ov008_0207bbbc(void);
extern void func_ov008_0207bb90(void);
extern void func_ov008_02081da0(void);
extern void *func_ov008_02055c84(void *resource, u32 index);
extern void func_ov008_02081ddc(void *text, int x, int y, u8 style,
                                int layer, int align, int visible);
extern u16 func_ov008_0207b82c(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_ov008_0207b78c(void *destination);
extern void func_ov008_02081c0c(int visible);
extern void func_ov008_0208187c(int selection);
extern u16 OS_IsTickAvailable_0x01ff8138(void);
extern int func_ov008_0207b7b4(void);
extern void func_ov008_02081e08(void);

extern void func_ov008_0207d5d8(void);
extern void func_ov008_0207c1cc(void);
extern void func_ov008_0207cd04(void);

MissionState func_ov008_0207c7c8(void)
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

    if (data_ov008_02090fa0->sessionReady == 0 &&
        func_ov008_0207bc58() != 0) {
        func_ov008_0207bcd8();
        return func_ov008_0207d5d8;
    }

    if (func_02001030() == 8) {
        return func_ov008_0207c1cc;
    }

    if (func_ov008_0207be38() != 0) {
        func_ov008_0207bcd8();
        return func_ov008_0207d5d8;
    }

    if (func_ov008_0207bc30() == 0) {
        menuAction = func_ov008_0207d804();
    }

    transitionReady = 1;
    if (data_ov008_02090fa0->sessionReady != 0) {
        if (OS_IsTickAvailable() != 0) {
            transitionReady = 0;
        }
        if (data_ov008_02090fa0->messageStateFlag != 0) {
            transitionReady = 0;
        }
    }

    if (transitionReady != 0 && menuAction == 1) {
        if (data_ov008_02090fa0->sessionReady != 0) {
            data_ov008_02090fa0->singleRowMode = func_ov008_0207b3d0();
        }
        data_ov008_02090fa0->messageStateFlag = 4;
        func_ov008_020817c4(0xd, 1, 0);
        func_02033b78(0, 0x30);
        nextState = func_ov008_0207cd04;
    }

    switch (data_ov008_02090fa0->messageStateFlag) {
    case 0:
        if (func_ov008_0207bc10() == 0 &&
            func_02001030() == 4 &&
            (data_ov008_02090fa0->sessionReady != 0 ||
             func_ov008_0207bc30() == 0) &&
            menuAction == 3) {
            if (data_ov008_02090fa0->sessionReady == 0) {
                func_ov008_0207bbd4(1);
                data_ov008_02090fa0->messageStateFlag = 1;
            } else {
                func_02033b78(0, 3);
                data_ov008_02090fa0->messageStateFlag = 2;
            }
        }
        break;

    case 1:
        menuAction = func_ov008_0207bc10();
        if (menuAction != 1) {
            break;
        }
        func_02033b78(0, 3);
        data_ov008_02090fa0->messageStateFlag = 2;
    case 2:
        if (func_ov008_0207bbbc() == 0) {
            func_ov008_0207bb90();
        }
        data_ov008_02090fa0->messageStateFlag = 3;
        break;

    case 3:
        if (func_ov008_0207bbbc() != 0) {
            nextState = func_ov008_0207c1cc;
        }
        break;
    }

    func_ov008_02081da0();

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

    textRecord = func_ov008_02055c84(
        &data_ov008_02090fa0->resource,
        data_ov008_02090fa0->messageId);
    func_ov008_02081ddc(textRecord, 0xfa, 2, 1, 1, 1, 1);

    if (data_ov008_02090fa0->sessionReady != 0) {
        textId = 0x41;
    } else {
        textId = 0x42;
    }
    textRecord = func_ov008_02055c84(
        &data_ov008_02090fa0->resource, textId);
    func_ov008_02081ddc(textRecord, 0x80, 0x60, 1, 1, 3, 1);

    optionMask = func_ov008_0207b82c();
    MI_CpuFill8(optionTextRows, 0, 0x58);
    func_ov008_0207b78c(optionTextRows);

    visibleRowIndex = 0;
    sourceRowIndex = 0;
    do {
        if ((optionMask & (1 << sourceRowIndex)) != 0 &&
            *(u16 *)((u8 *)optionTextRows + sourceRowIndex * 0x16) != 0) {
            func_ov008_02081ddc(
                (u8 *)optionTextRows + sourceRowIndex * 0x16, 99,
                visibleRowIndex * 0x18 + 0x23, 1, 1, 0, 0);
            visibleRowIndex = (visibleRowIndex + 1) & 0xff;
        }
        sourceRowIndex = (sourceRowIndex + 1) & 0xff;
    } while (sourceRowIndex < 4);

    while (visibleRowIndex < 4) {
        func_ov008_02081ddc(
            data_ov008_02090d0c, 99,
            visibleRowIndex * 0x18 + 0x23, 1, 1, 0, 0);
        visibleRowIndex = (visibleRowIndex + 1) & 0xff;
    }

    if (data_ov008_02090fa0->sessionReady != 0) {
        if (func_ov008_0207bc30() == 0) {
            textRecord = func_ov008_02055c84(
                &data_ov008_02090fa0->resource, 0x43);
            func_ov008_02081ddc(textRecord, 0x80, 0x98, 1, 1, 3, 0);
            func_ov008_02081c0c(1);
        } else {
            func_ov008_02081c0c(0);
            textRecord = func_ov008_02055c84(
                &data_ov008_02090fa0->resource, 0x43);
            func_ov008_02081ddc(textRecord, 0x80, 0x98, 1, 1, 3, 0);
        }
    }

    func_ov008_0208187c(-1);
    if (data_ov008_02090fa0->sessionReady != 0) {
        if (OS_IsTickAvailable_0x01ff8138() > 1) {
            func_ov008_0208187c(func_ov008_0207b7b4());
        }
    } else {
        if (OS_IsTickAvailable_0x01ff8138() != 0) {
            func_ov008_0208187c(func_ov008_0207b7b4());
        }
    }

    if (func_02001030() == 4 && func_ov008_0207bc30() == 0) {
        if (data_ov008_02090fa0->sessionReady != 0) {
            textId = 0x45;
        } else {
            textId = 0x46;
        }
        textRecord = func_ov008_02055c84(
            &data_ov008_02090fa0->resource, textId);
        func_ov008_02081ddc(textRecord, 10, 0xb4, 1, 1, 0, 0);
    }

    func_ov008_02081e08();
    return nextState;
}