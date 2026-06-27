typedef unsigned int u32;
typedef unsigned short u16;
typedef signed int s32;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern s32 func_020093e8(u32 a, u32 b, u32 c);

typedef void (*Callback)(u32, u32, u32);

struct Data {
    u32 unk00;
    Callback cb;
    u32 pad08[12];
    u16 unk38;
    u16 unk3a;
};

extern struct Data data_02046390;

typedef int BOOL;

void func_0200c5fc(void) {
    u32 ie = OS_DisableInterrupts();
    BOOL ok = func_020093e8(6, 0x3000200, 0) >= 0;
    if (!ok) {
        OS_RestoreInterrupts(ie);
        data_02046390.unk38 |= 4;
        if (data_02046390.cb != 0) {
            data_02046390.cb(2, 4, 0);
        }
        return;
    }
    data_02046390.unk3a |= 4;
    data_02046390.unk38 &= ~4;
    OS_RestoreInterrupts(ie);
}
