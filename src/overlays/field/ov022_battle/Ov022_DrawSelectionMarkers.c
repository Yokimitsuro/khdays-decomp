/* Draws the lock-on markers of the current selection: positions the three marker sprites over the
 * focused target and animates them with the activation tween and the target's deadline. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov022SelectionPoint {
    int x;
    int y;
} Ov022SelectionPoint;

typedef enum Ov022EnabledState {
    OV022_ENABLED_FALSE = 0,
    OV022_ENABLED_TRUE = 1
} Ov022EnabledState;

typedef enum Ov022SpecialState {
    OV022_SPECIAL_FALSE = 0,
    OV022_SPECIAL_TRUE = 1
} Ov022SpecialState;

typedef struct Ov022DisplayRecord {
    char pad00[0x10];
    Ov022SelectionPoint point;
    Ov022SelectionPoint scale;
    char pad20[5];
    u8 active;
    char pad26[2];
    u16 offset;
    char pad2a[6];
} Ov022DisplayRecord;

typedef struct Ov022DisplayGroup {
    Ov022DisplayRecord records[3];
    char tween[0x1c];
} Ov022DisplayGroup;

typedef struct Ov022FocusObject {
    char pad000[0x19c];
    u8 kind;
} Ov022FocusObject;

typedef struct Ov022RootContext {
    int flags;
    char pad004[4];
    int mode;
    Ov022FocusObject *focus;
    char pad010[0x220];
    int activationState;
} Ov022RootContext;

#pragma pack(4)
typedef struct Ov022Actor {
    char pad0000[0x2aa4];
    u64 deadline;
    char pad2aac[8];
    u8 actionState;
} Ov022Actor;
#pragma pack()

extern Ov022RootContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov022_02083f0c(void);
extern void Ov002_ResetViewToDefault(void);
extern int Ov002_ResourceNodeCallback(Ov022DisplayRecord *record);
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int FX_Div(int numerator, int denominator);
extern void Ov002_ReaimActor();

void Ov022_DrawSelectionMarkers(void *state,
                         const Ov022SelectionPoint *point)
{
    Ov022DisplayGroup *group = state;
    Ov022RootContext *context = NNSi_FndGetCurrentRootHeap();
    int object;
    Ov022EnabledState enabled;
    Ov022SpecialState special;
    Ov022SelectionPoint scratch;

    if ((context->flags & 4) > 0) {
        enabled = OV022_ENABLED_TRUE;
    } else {
        enabled = OV022_ENABLED_FALSE;
    }
    special = OV022_SPECIAL_FALSE;
    object = func_ov022_02083f0c();

    if ((context->mode & 1) != 0) {
        Ov022FocusObject *focus = context->focus;
        if (focus != 0 && focus->kind == 0x6d) {
            special = OV022_SPECIAL_TRUE;
        }
    }

    group->records[0].point = *point;
    group->records[1].point = *point;
    group->records[0].offset -= 500;

    if (enabled == 0) goto first_inactive;
    if (context->activationState == 0) goto first_active;
    if (special == 0) goto first_inactive;
first_active:
    group->records[0].active = 1;
    group->records[1].offset += 500;
    goto first_done;
first_inactive:
    group->records[0].active = 0;
first_done:

    Ov002_ResetViewToDefault();
    Ov002_ResourceNodeCallback(&group->records[0]);

    if (enabled == 0) goto second_done;
    if (context->activationState == 0) goto second_update;
    if (special == 0) goto second_done;
second_update:
    Ov002_ResourceNodeCallback(&group->records[1]);
second_done:

    if (context->mode == 1) {
        Ov022Actor *actor = (Ov022Actor *)GetEntryField20ByIndex(QueryActiveStateOrDelegate());

        if (actor->actionState != 0 && actor->deadline >= OS_GetTick()) {
            int ratio;
            int scale;
            long long product;

            group->records[2].point = *point;
            ratio = FX_Div(
                (int)func_02020368((actor->deadline - OS_GetTick()) << 6, 0x82ea) << 12,
                0x02710000);
            if (ratio >= 0x1000) {
                ratio = 0x1000;
            }
            product = (long long)ratio * 0x1666;
            scale = (int)((product + 0x800) >> 12) + 0x214;
            scratch.y = scale;
            scratch.x = scale;
            group->records[2].scale = scratch;
            Ov002_ResourceNodeCallback(&group->records[2]);
        }
    }

    Ov002_ReaimActor(object, 0);
}
