typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef void (*CardCommandCallback)(int result, int operation, int detail);

struct CardCommandBlock {
    u32 value00;
    u16 status04;
    u16 value06;
};

struct CardCommandContext {
    u8 pad00[4];
    CardCommandCallback callback04;
    u8 pad08[8];
    u16 status10;
    u16 parameter12;
    struct CardCommandBlock *blocks14;
    u16 blockCount18;
    u8 pad1a[0x1e];
    u16 errorFlags38;
    u16 commandFlags3a;
};

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int func_020093e8(int channel, int word, int flag);
extern struct CardCommandContext data_02046390;

void func_0200c4fc(int header, int parameter,
                   char *blocks, unsigned int count)
{
    void (*callback)(int, int, int);
    int i;
    int interruptState;
    int ok;
    int result;

    data_02046390.blocks14 = (struct CardCommandBlock *)blocks;
    data_02046390.status10 = 0;
    data_02046390.parameter12 = (short)parameter;
    data_02046390.blockCount18 = (short)count;

    for (i = 0; i < count; i++) {
        data_02046390.blocks14[i].status04 = 0;
    }

    interruptState = OS_DisableInterrupts();
    if (func_020093e8(6, (parameter & 0xff) | 0x100 | 0x2000000, 0) < 0) {
        ok = 0;
    } else {
        result = func_020093e8(6, header | 0x10000 | 0x1000000, 0);
        if (result < 0) {
            ok = 0;
        } else {
            ok = 1;
        }
    }

    if ((ok & 0xff) == 0) {
        OS_RestoreInterrupts(interruptState);
        data_02046390.errorFlags38 |= 2;
        callback = data_02046390.callback04;
        if (callback == 0) {
            return;
        }
        callback(1, 4, 0);
        return;
    }

    {
        data_02046390.commandFlags3a |= 2;
        data_02046390.errorFlags38 &= ~2;
    }
    OS_RestoreInterrupts(interruptState);
}
