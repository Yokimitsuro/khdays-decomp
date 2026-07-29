typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov009ObjectTemplate {
    u32 words[5];
} Ov009ObjectTemplate;

typedef struct Ov009HeaderLimits {
    u16 first;
    u16 second;
} Ov009HeaderLimits;

typedef struct Ov009MenuContext {
    u8 subsystem0[0x4a80];
    u8 subsystem1[0x9500 - 0x4a80];
    u8 object9500[0x4c];
    u8 object954c[0x4c];
    void *graphicsObject;
    u8 pad_959c[0x95a4 - 0x959c];
    void *tileBuffers[7];
    u8 pad_95c0[0x95c0 - (0x95a4 + 7 * 4)];
    void *field_95c0;
    u8 pad_95c4[0x95d0 - 0x95c4];
    int tileGridWidth;
    int brightness;
    u8 brightnessTween[0x1c];
    u8 pad_95f4[0x9600 - 0x95f4];
    int pageAEnabled;
    int pageBEnabled;
    u8 pad_9608[0x9618 - 0x9608];
    int updateTaskPending;
    int blitPending;
    u8 pad_9620[0x9628 - 0x9620];
    int field_9628;
    int field_962c;
    u8 pad_9630[0x963e - 0x9630];
    u16 inputHeader;
    u8 pad_9640[0x9660 - 0x9640];
    u8 activeWidgetList[0x14];
    int subDisplayMode;
    u8 pad_9678[0x96b0 - 0x9678];
    void *primaryMessageContainer;
    void *secondaryMessageContainer;
    void *tertiaryMessageContainer;
} Ov009MenuContext;

extern const Ov009ObjectTemplate data_ov009_02055f58;
extern const Ov009HeaderLimits data_ov009_02055f54;
extern Ov009MenuContext *data_ov009_020563e4[2];
extern const char data_ov009_020562a4[];
extern const char data_ov009_020562b0[];
extern const char data_ov009_020562c0[];
extern const char data_ov009_020562e0[];

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 size);
extern void  MI_CpuFill8(void *destination, int value, u32 size);
extern void  func_0201e470(int mode, int overlayId);
extern void *func_02024ee8(const void *descriptor, int heapId);
extern int   func_02024e5c(void);
extern void  func_02024d68(void);
extern void *func_02023930(const void *descriptor, int value);
extern void  NNS_FndInitList(void *list, int linkOffset);
extern void  func_ov009_0204cb9c(void);
extern void  func_ov009_0204e660(void);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern void  MIi_CpuClear16(int value, void *destination, u32 size);
extern void  func_02035f84(void *tween);
extern void  func_ov009_02052230(
    void *object, const Ov009ObjectTemplate *objectTemplate);
extern void  func_ov009_02051470(void *object, int value);
extern void  func_ov009_0204cec0(int value);
extern void  func_02036298(
    u16 *inputHeader, const Ov009HeaderLimits *limits);
extern void  func_ov009_0204e328(int first, int second);
extern void  func_ov009_0204e5b4(int enabled);

static volatile u32 *const REG_DISPCNT_SUB =
    (volatile u32 *)0x04001000;

void func_ov009_0204dc00(void)
{
    Ov009ObjectTemplate objectTemplate = data_ov009_02055f58;
    Ov009HeaderLimits headerLimits = data_ov009_02055f54;
    int isModeOne;
    int index;

    data_ov009_020563e4[0] = 0;
    data_ov009_020563e4[1] =
        NNSi_FndAllocFromDefaultExpHeap(0x976c);
    MI_CpuFill8(data_ov009_020563e4[1], 0, 0x976c);

    data_ov009_020563e4[1]->pageAEnabled = 1;
    data_ov009_020563e4[1]->pageBEnabled = 1;

    func_0201e470(0, 0x12e);
    data_ov009_020563e4[1]->primaryMessageContainer =
        func_02024ee8(data_ov009_020562a4, 14);
    isModeOne = func_02024e5c() == 1;
    if (isModeOne == 0) {
        data_ov009_020563e4[1]->secondaryMessageContainer =
            func_02024ee8(data_ov009_020562b0, 14);
    }
    data_ov009_020563e4[1]->tertiaryMessageContainer =
        func_02024ee8(data_ov009_020562c0, 14);

    func_02024d68();
    data_ov009_020563e4[1]->graphicsObject =
        func_02023930(data_ov009_020562e0, 0);
    data_ov009_020563e4[1]->tileGridWidth = 0x40;
    data_ov009_020563e4[1]->field_9628 = 1;
    data_ov009_020563e4[1]->field_962c = 1;
    NNS_FndInitList(
        data_ov009_020563e4[1]->activeWidgetList, 4);

    data_ov009_020563e4[1]->brightness = -0x10000;
    data_ov009_020563e4[1]->blitPending = 1;
    func_ov009_0204cb9c();

    data_ov009_020563e4[1]->subDisplayMode =
        (*REG_DISPCNT_SUB & 0xe000) >> 13;
    func_ov009_0204e660();

    for (index = 0; index < 7; index++) {
        data_ov009_020563e4[1]->tileBuffers[index] =
            NNS_FndAllocFromDefaultExpHeapEx(
                data_ov009_020563e4[1]->tileGridWidth << 6, 2);
        MIi_CpuClear16(
            0,
            data_ov009_020563e4[1]->tileBuffers[index],
            data_ov009_020563e4[1]->tileGridWidth << 6);
    }

    func_02035f84(data_ov009_020563e4[1]->brightnessTween);
    func_ov009_02052230(
        data_ov009_020563e4[1]->object9500, &objectTemplate);
    func_ov009_02052230(
        data_ov009_020563e4[1]->object954c, &objectTemplate);
    func_ov009_02051470(data_ov009_020563e4[1]->subsystem0, 0);
    func_ov009_02051470(data_ov009_020563e4[1]->subsystem1, 0);
    func_ov009_0204cec0(0);
    func_02036298(
        &data_ov009_020563e4[1]->inputHeader, &headerLimits);
    func_ov009_0204e328(0, -1);
    data_ov009_020563e4[1]->field_95c0 = 0;
    func_ov009_0204e5b4(1);
    data_ov009_020563e4[1]->updateTaskPending = 1;
}
