typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*PMCallback)(u32 result, void *argument);

typedef struct PMData16 {
    u16 flag;
    u16 padding;
    u16 *buffer;
} PMData16;

typedef struct PXIContext {
    unsigned char reserved_00[0x1c];
    u32 locked;
    PMCallback callback;
    void *callbackArgument;
} PXIContext;

extern int PXIi_TryLock(void);
extern void PXIi_SendCommand(u32 command);
extern PXIContext data_020463cc;
extern PMData16 data_02046410[];

u32 PXIi_RequestCmd0x65(u16 channel, u16 *buffer,
                        PMCallback callback, void *callbackArgument)
{
    if (PXIi_TryLock() == 0) {
        return 1;
    }

    data_020463cc.callback = callback;
    data_020463cc.callbackArgument = callbackArgument;
    data_02046410[channel].flag = 0;
    data_02046410[channel].buffer = buffer;
    PXIi_SendCommand((channel & 0xff) | 0x03006500);
    return 0;
}
