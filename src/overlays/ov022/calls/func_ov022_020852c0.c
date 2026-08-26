typedef unsigned char u8;

typedef struct Ov022ModeContext {
    unsigned int flags0;
    unsigned int flags4;
    char pad_0008[0xe0];
    char subsystemE8[1];
    char pad_00e9[0x147];
    int value230;
} Ov022ModeContext;

extern u8 data_0204be04;
extern Ov022ModeContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern void *func_01fffde0(int index);
extern void func_ov002_02056a98(int mode);
extern void func_ov022_0208471c(void);
extern void func_02033b78(int handle, int mode);
extern void func_ov022_020847f0(void);
extern void func_ov022_020848bc(void *state, int mask);
extern void func_ov022_02086128(void *subsystem);

void func_ov022_020852c0(int enabled)
{
    Ov022ModeContext *context = NNSi_FndGetCurrentRootHeap();

    func_01fffde0(func_01fffe14());
    if (data_0204be04 == 0) {
        func_ov002_02056a98(enabled);
    }

    if (enabled == 0) {
        goto disabled;
    }
    if (enabled == 0) {
        return;
    }
    func_ov022_0208471c();
    context->flags0 |= 4;
    context->flags4 |= 2;
    func_02033b78(0, 5);
    context->value230 = 0;
    return;

disabled:
    func_ov022_020847f0();
    if (context->value230 == 0 && (context->flags0 & 4) != 0) {
        func_02033b78(0, 6);
    }
    context->flags0 &= ~4;
    func_ov022_020848bc(&context->flags4, 2);
    func_ov022_02086128(context->subsystemE8);
}
