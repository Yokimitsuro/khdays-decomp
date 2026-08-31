typedef unsigned short u16;
typedef unsigned long long u64;
typedef long long s64;
typedef struct { short nSin, nCos; } FxSinCos;
typedef struct { unsigned char opaque[0x4a38]; } Ov004SpriteManager;
typedef struct {
    unsigned char opaque0000[0xaf8];
    int transitionPhase;
    int opaque0afc;
    u64 lastTick;
    int fadeLevel;
    Ov004SpriteManager slotManager;
    int spriteSlotIds[3];
    unsigned char opaque5550[0x10];
    int startValueFx12, valueDeltaFx12, currentValueFx12, targetValueFx12;
    int tweenStepFx16, tweenDone, tweenProgressFx16;
    unsigned char opaque557c[8];
    int sourceSlotFlagSet;
} Ov004Context;
extern Ov004Context *data_ov004_02051384;
extern const FxSinCos data_0203d210[4096];
extern void func_ov004_020506cc(int valueFx12);
extern void func_020326a8(Ov004SpriteManager *manager, int slotIndex);
extern u64 func_020031d4(void);
extern void func_0201e374(int brightness);

void func_ov004_02050c60(void)
{
    int easeWeight = 0;
    Ov004Context *context;
    if (!data_ov004_02051384->tweenDone) {
        data_ov004_02051384->tweenProgressFx16 += data_ov004_02051384->tweenStepFx16;
        if (data_ov004_02051384->tweenProgressFx16 > 0x10000)
            data_ov004_02051384->tweenProgressFx16 = 0x10000;
        easeWeight = data_0203d210[(u16)(data_ov004_02051384->tweenProgressFx16 / 2 - 0x4000) >> 4].nSin + 0x1000;
        data_ov004_02051384->currentValueFx12 = data_ov004_02051384->startValueFx12 +
            (int)(((s64)easeWeight * data_ov004_02051384->valueDeltaFx12 + 0x800) >> 12) / 2;
        if ((data_ov004_02051384->valueDeltaFx12 > 0 && data_ov004_02051384->currentValueFx12 >= data_ov004_02051384->targetValueFx12) ||
            (data_ov004_02051384->valueDeltaFx12 < 0 && data_ov004_02051384->currentValueFx12 <= data_ov004_02051384->targetValueFx12)) {
            data_ov004_02051384->currentValueFx12 = data_ov004_02051384->targetValueFx12;
            data_ov004_02051384->tweenDone = 1;
        }
    }
    func_ov004_020506cc(data_ov004_02051384->currentValueFx12);
    if (easeWeight >= 0x1fe8 && !data_ov004_02051384->sourceSlotFlagSet) {
        func_020326a8(&data_ov004_02051384->slotManager, data_ov004_02051384->spriteSlotIds[0]);
        data_ov004_02051384->sourceSlotFlagSet = 1;
    }
    if (data_ov004_02051384->tweenDone) {
        if (!data_ov004_02051384->sourceSlotFlagSet) {
            func_020326a8(&data_ov004_02051384->slotManager, data_ov004_02051384->spriteSlotIds[0]);
            data_ov004_02051384->sourceSlotFlagSet = 1;
        }
        context = data_ov004_02051384;
        context->lastTick = func_020031d4();
        context->transitionPhase = 2;
        func_0201e374(0);
    }
}
