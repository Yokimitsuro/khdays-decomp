/* Steps the selection tween and, when the schedule is enabled, records the time and moves to the
 * elapsed gate. */

#include "nitro/types.h"

typedef void (*Ov022Callback)(void);

typedef struct Ov022ControllerFlags {
    unsigned int bit0 : 1;
    unsigned int bit1 : 1;
    unsigned int scheduleEnabled : 1;
    unsigned int rest : 29;
} Ov022ControllerFlags;

typedef struct Ov022SelectionController {
    u8 pad000[0xc4];
    s32 scheduledHandle0c4;
    u8 pad0c8[0x118];
    u8 tween1e0[0x18];
    Ov022ControllerFlags flags1f8;
} Ov022SelectionController;

extern u8 data_0204be04;
extern Ov022SelectionController *NNSi_FndGetCurrentRootHeap(void);
extern void Tween_Sample(void *tween, s32 *value);
extern void func_ov022_02086d0c(int enabled);
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern void func_ov022_02086d60(s32 value);
extern void Ov022_ElapsedGate(void);

Ov022Callback Ov022_StepSelectionSchedule(void)
{
    Ov022SelectionController *context = NNSi_FndGetCurrentRootHeap();
    Ov022Callback callback = 0;
    s32 value;

    if (data_0204be04 != 0) {
        return callback;
    }

    Tween_Sample(context->tween1e0, &value);
    if (context->flags1f8.scheduleEnabled != 0) {
        func_ov022_02086d0c(0);
        value = 0x10000;
        context->scheduledHandle0c4 =
            (s32)func_02020368(OS_GetTick() << 6, 0x82ea);
        callback = Ov022_ElapsedGate;
    }

    func_ov022_02086d60(value);
    return callback;
}
