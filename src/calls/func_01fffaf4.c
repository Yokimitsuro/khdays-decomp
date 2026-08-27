typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AsyncMessage {
    int active00;
    void *data04;
    u16 size08;
} AsyncMessage;

extern int CARD_GetResultCode_0x0203065c(void);
extern u16 func_01fff988(void);
extern void func_01fffbf4(void);
extern int func_ov105_020be164(void (*callback)(void), AsyncMessage *message,
                              void *data, u16 size, u16 mask, int stride,
                              int zero);
extern void func_020307f0(void);
extern void func_02030d2c(void *data, u16 size);

int func_01fffaf4(AsyncMessage *message)
{
    int result;

    if (message->size08 == 0) {
        return 0;
    }

    switch (CARD_GetResultCode_0x0203065c()) {
    case 2:
        message->active00 = 1;
        result = func_ov105_020be164(func_01fffbf4, message,
                                    message->data04, message->size08,
                                    func_01fff988() & 0xfffe, 12, 0);
        if (result != 2) {
            func_020307f0();
        }
        func_02030d2c(message->data04, message->size08);
        break;
    case 1:
        func_02030d2c(message->data04, message->size08);
        break;
    case 3:
        message->active00 = 1;
        result = func_ov105_020be164(func_01fffbf4, message,
                                    message->data04, message->size08,
                                    0, 12, 0);
        if (result != 2) {
            func_020307f0();
        }
        break;
    }

    message->size08 = 0;
    return 1;
}
