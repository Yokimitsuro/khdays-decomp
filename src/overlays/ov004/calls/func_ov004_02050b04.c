typedef unsigned long long u64;
typedef struct {
    unsigned char opaque0000[0xaf8];
    int transitionPhase;
    int opaque0afc;
    u64 lastTick;
    int fadeLevel;
    unsigned char opaque0b0c[0x4a54];
    int startValueFx12;
    int valueDeltaFx12;
    int currentValueFx12;
    int targetValueFx12;
    int tweenStepFx16;
    int tweenDone;
    int tweenProgressFx16;
} Ov004Context;
extern Ov004Context *data_ov004_02051384;
extern void func_0201e374(int brightness);
extern u64 func_020031d4(void);
extern long long func_02020400(int numerator, int denominator);

void func_ov004_02050b04(void)
{
    int distance;
    Ov004Context *context;
    data_ov004_02051384->fadeLevel++;
    if (data_ov004_02051384->fadeLevel > 16)
        data_ov004_02051384->fadeLevel = 16;
    func_0201e374(data_ov004_02051384->fadeLevel - 16);
    if (data_ov004_02051384->fadeLevel < 16)
        return;
    data_ov004_02051384->lastTick = func_020031d4();
    func_0201e374(0);
    data_ov004_02051384->tweenStepFx16 = 0;
    data_ov004_02051384->tweenProgressFx16 = 0;
    data_ov004_02051384->tweenDone = data_ov004_02051384->startValueFx12 == data_ov004_02051384->targetValueFx12;
    context = data_ov004_02051384;
    if (!context->tweenDone) {
        distance = context->valueDeltaFx12 >> 12;
        if (distance < 0)
            distance = -distance;
        if (distance <= 2)
            context->tweenStepFx16 = (int)func_02020400(0x10000, distance * 30);
        else if (distance <= 10)
            context->tweenStepFx16 = (int)func_02020400(0x10000, distance * 9);
        else if (distance <= 30)
            context->tweenStepFx16 = (int)func_02020400(0x10000, distance * 4);
        else
            context->tweenStepFx16 = (int)func_02020400(0x10000, distance);
    }
    data_ov004_02051384->transitionPhase = 1;
}
