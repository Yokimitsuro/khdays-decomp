typedef unsigned long long u64;
typedef void (*Ov004AlarmCallback)(void *arg);
typedef struct {
    unsigned char opaque0000[0xaf8];
    int transitionPhase;
    int opaque0afc;
    u64 lastTick;
    unsigned char opaque0b08[0x4a7c];
    int sourceSlotState;
} Ov004Context;
extern Ov004Context *data_ov004_02051384;
extern char OVERLAY_28_ID[];
extern u64 func_020031d4(void);
extern void func_0201e470(int processor, int overlayId);
extern void func_0201e4a8(int processor, int overlayId);
extern int func_ov028_0208b490(Ov004AlarmCallback callback);
extern int func_ov028_0208b040(Ov004AlarmCallback callback);
extern int func_ov028_0208b200(Ov004AlarmCallback callback);
extern void func_ov004_020500e8(void *arg);

void func_ov004_02050e44(void)
{
    Ov004Context *context = data_ov004_02051384;
    u64 elapsed = func_020031d4() - context->lastTick;
    if (elapsed <= 0x11942b)
        return;
    if (context->sourceSlotState != 2)
        return;
    func_0201e470(0, (int)OVERLAY_28_ID);
    if (func_ov028_0208b490(0))
        data_ov004_02051384->lastTick += elapsed + 0x7fd88;
    if (func_ov028_0208b040(func_ov004_020500e8)) {
        data_ov004_02051384->lastTick += elapsed + 0x3fec4;
        func_ov004_020500e8((void *)2);
    }
    if (func_ov028_0208b200(func_ov004_020500e8)) {
        data_ov004_02051384->lastTick += elapsed + 0x7fd88;
        func_ov004_020500e8((void *)1);
    }
    func_0201e4a8(0, (int)OVERLAY_28_ID);
    context = data_ov004_02051384;
    context->lastTick = func_020031d4();
    context->transitionPhase = 3;
}
