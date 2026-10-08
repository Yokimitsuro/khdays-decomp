/* After a delay, loads ov028 and runs its three DS Protect checks, arming the alarm when one fails,
 * then unloads it and moves on. */

#include "nitro/types.h"
#include "game/engine.h"

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
extern u64 OS_GetTick(void);
extern int Ov028_DSProt_DetectNotDummy(Ov004AlarmCallback callback);
extern int Ov028_DSProt_DetectFlashcart(Ov004AlarmCallback callback);
extern int Ov028_DSProt_DetectEmulator(Ov004AlarmCallback callback);
extern void Ov004_RearmIdleAlarm(void *arg);

void Ov004_RunDelayedProtectionChecks(void)
{
    Ov004Context *context = data_ov004_02051384;
    u64 elapsed = OS_GetTick() - context->lastTick;
    if (elapsed <= 0x11942b)
        return;
    if (context->sourceSlotState != 2)
        return;
    LoadOverlaySync(0, (int)OVERLAY_28_ID);
    if (Ov028_DSProt_DetectNotDummy(0))
        data_ov004_02051384->lastTick += elapsed + 0x7fd88;
    if (Ov028_DSProt_DetectFlashcart(Ov004_RearmIdleAlarm)) {
        data_ov004_02051384->lastTick += elapsed + 0x3fec4;
        Ov004_RearmIdleAlarm((void *)2);
    }
    if (Ov028_DSProt_DetectEmulator(Ov004_RearmIdleAlarm)) {
        data_ov004_02051384->lastTick += elapsed + 0x7fd88;
        Ov004_RearmIdleAlarm((void *)1);
    }
    UnloadOverlaySync(0, (int)OVERLAY_28_ID);
    context = data_ov004_02051384;
    context->lastTick = OS_GetTick();
    context->transitionPhase = 3;
}
