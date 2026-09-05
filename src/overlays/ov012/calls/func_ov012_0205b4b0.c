typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov012OpeningEvent {
    u32 nTriggerThreadDelta;
    u16 uHandlerIndex;
    u16 uArgument0;
    u16 uArgument1;
    u16 uArgument2;
} Ov012OpeningEvent;

extern int func_0202060c(int numerator, u32 denominator);
extern void G2x_SetBlendAlpha_(volatile u16 *pBlendControl, u32 planeA,
                               u32 planeB, int eva, int evb);

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_BLDCNT  (*(volatile u16 *)0x04000050)

int func_ov012_0205b4b0(void *pContext, u32 nThreadDelta,
                             Ov012OpeningEvent *pEvent) {
    char *context;
    int nBlendStep;
    u32 uRemainingBgPlaneMask;

    context = (char *)pContext;
    nBlendStep = func_0202060c(
        (nThreadDelta - pEvent->nTriggerThreadDelta) << 4,
        pEvent->uArgument1);
    uRemainingBgPlaneMask =
        *(u8 *)(context + 0x8bf0) & ~pEvent->uArgument0;

    if (uRemainingBgPlaneMask == 0) {
        if (nBlendStep >= 16) {
            REG_DISPCNT &= ~0x1f00;
            *(u8 *)(context + 0x8bf0) = 0;
            *(int *)(context + 0x8bf4) = -16;
            return 1;
        }
        *(int *)(context + 0x8bf4) = -nBlendStep;
        return 0;
    }

    if (nBlendStep >= 16) {
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) |
                      ((*(u8 *)(context + 0x8bf0) = uRemainingBgPlaneMask) << 8);
        REG_BLDCNT = 0;
        return 1;
    }

    G2x_SetBlendAlpha_(&REG_BLDCNT, pEvent->uArgument0,
                       uRemainingBgPlaneMask, 16 - nBlendStep, nBlendStep);
    return 0;
}
