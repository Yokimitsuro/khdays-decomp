/* Fade in the sub-screen and start the first result-count animation. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Tween { char data[28]; } Tween;
typedef struct Ov005ResultTween { Tween tween; int value; char unknown20[12]; } Ov005ResultTween;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext {
    char unknown00[0x54];
    Ov005SpriteManager spriteManager;
    char unknown4ad4[0x88];
    long long startTick;
    char unknown4b64[16];
    int resultPhase;
    char unknown4b78[12];
    Ov005ResultTween resultTweens[4];
    int activeTweenIndex;
} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern void Ov005_SelectAndShowResultSprite(int, int);
extern void *Ov005_FindEntryById(Ov005SpriteManager *, int);
extern void Ov005_ReleaseTwoSlots_2(Ov005SpriteManager *, void *);
extern void Ov005_SetEntrySlotsVisible(Ov005SpriteManager *, void *, int);
#define REG_DISPCNT_SUB (*(volatile unsigned int *)0x04001000)
void Ov005_FadeInResultScreen(void) {
    u64 elapsed = OS_GetTick() - data_ov005_0205b810->startTick;
    int step = (int)func_02020368(elapsed, 0x7fd8);
    int tweenIndex, visibleId, releasedId;
    void *entry;
    if (step > 1) {
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1f00;
        SetMasterBrightnessSub(step - 16);
    }
    if (elapsed <= 0x7fd88) return;
    data_ov005_0205b810->startTick = OS_GetTick();
    SetMasterBrightnessSub(0);
    data_ov005_0205b810->resultPhase = 1;
    Ov005_ConfigureResultTweens();
    tweenIndex = data_ov005_0205b810->activeTweenIndex;
    Tween_Start(&data_ov005_0205b810->resultTweens[tweenIndex].tween);
    switch (tweenIndex) {
    case 1: releasedId = 32; visibleId = 31; break;
    case 2: releasedId = 47; visibleId = 46; break;
    case 3: releasedId = 62; visibleId = 61; break;
    default: return;
    }
    Ov005_SelectAndShowResultSprite(releasedId, 0);
    entry = Ov005_FindEntryById(&data_ov005_0205b810->spriteManager, releasedId);
    Ov005_ReleaseTwoSlots_2(&data_ov005_0205b810->spriteManager, entry);
    entry = Ov005_FindEntryById(&data_ov005_0205b810->spriteManager, visibleId);
    Ov005_SetEntrySlotsVisible(&data_ov005_0205b810->spriteManager, entry, 1);
}
