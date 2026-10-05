/*
 * Ov002_UpdatePartyEntries - per-frame party/entry updater in the ov002 gameplay slice (dep of
 * the constructor Ov002_ConstructGameplayScene). No-op unless the pending slot at root-context+0x8bcc is
 * live (!= -1).
 *
 * Publishes a scaled timeout ((Ov002_GetTimeoutTicks()<<6)/0x82ea) into data_0204c4d8+0x14, then,
 * unless the phase at ctx+0x8bb4 is 0 or 3, walks the four 0x104-byte entries at gPartyMembers:
 * copies the 8-byte head into a scratch, recomputes its 4th halfword from Ov022_GetEntryField12 (or
 * the entry's +0xe field, gated on func_ov022_020886f8 and data_0204c240 & 4), writes the head
 * back, and - depending on the same flag - refreshes the entry (GetEntryField20ByIndex) and, if
 * Ov002_TestRosterSlotGroundRay reports it changed, notifies Ov002_FillRosterSlotDefaults.
 *
 * THUMB. The 64-bit divide is the runtime helper func_02020368(u64, divisor, 0) called directly
 * (the / operator would emit an unresolved _ll_sdiv). The head read/write are struct copies so
 * mwcc keeps the read and write cursors in separate registers (r7/r5, same address); with fp++
 * emitted between the two 0x104 increments the divide constant is re-materialized, matching the
 * original. state==0||3 is a materialized bool.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct { u16 a, b, c, d; } Head;

extern int  data_ov002_0207fa00;
extern unsigned long long Ov002_GetTimeoutTicks(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int  Ov022_GetEntryField12(int i);
extern int  func_ov022_020886f8(int i);
extern int  Ov002_TestRosterSlotGroundRay(int i);
extern void Ov002_FillRosterSlotDefaults(int i);
extern int  data_0204c4d8;
extern u16  gPartyMembers;
extern u8   data_0204c240;

void Ov002_UpdatePartyEntries(void)
{
    char *ctx = (char *)data_ov002_0207fa00;
    unsigned long long t;
    int i;
    Head buf;
    int flags[4];
    int *fp;
    char *rdp;
    char *wrp;

    if (*(int *)(ctx + 0x8bcc) == -1) return;
    t = Ov002_GetTimeoutTicks();
    *(int *)((char *)&data_0204c4d8 + 0x14) = (int)func_02020368(t << 6, 0x82ea);
    {
        int state = *(int *)(ctx + 0x8bb4);
        int done = 0;
        if (state == 0 || state == 3) done = 1;
        if (done != 0) return;
    }
    i = 0;
    fp = flags;
    rdp = (char *)&gPartyMembers;
    wrp = (char *)&gPartyMembers;
    for (; i < 4; i++) {
        if (GetEntryField20ByIndex(i) == 0) return;
        buf = *(Head *)rdp;
        buf.d = Ov022_GetEntryField12(i);
        *fp = 0;
        if (buf.d == 0) {
            buf.d = *(u16 *)(wrp + 0xe);
            *fp = 1;
        } else if (flags[0] != 0 && (data_0204c240 & 4) == 0 && func_ov022_020886f8(i) != 0) {
            buf.d = *(u16 *)(wrp + 0xe);
        }
        *(Head *)wrp = buf;
        if ((*fp == 0 && (data_0204c240 & 4) != 0) ||
            (flags[0] == 0 && (data_0204c240 & 4) == 0)) {
            GetEntryField20ByIndex(i);
            if (Ov002_TestRosterSlotGroundRay(i) != 0) {
                Ov002_FillRosterSlotDefaults(i);
            }
        }
        rdp += 0x104;
        fp++;
        wrp += 0x104;
    }
}
