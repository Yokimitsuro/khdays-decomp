/*
 * Banks the milliseconds since the last pass and reports them when there are
 * enough of them.
 *
 * The clock is the hardware tick count scaled to milliseconds the same way the
 * rest of the session does it. The gap since the previous stamp is added to the
 * running total every pass, and the report only goes out once a second has
 * banked - or straight away when the link says so.
 *
 * Reporting takes one of two roads: locally it goes to the handler directly,
 * and over the link it goes as a kind seven message, whose refusal leaves the
 * total banked for the next pass. The stamp moves forward either way.
 *
 * ARM.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov002TickCmd {
    u8 pad0;
    u8 bFlag;
    char pad2[2];
    u32 nElapsed;
} Ov002TickCmd;

typedef struct Ov002TickCtx {
    char pad0[4];
    int nLastMs;
    u32 nElapsed;
} Ov002TickCtx;

extern Ov002TickCtx *data_ov002_0207fa08;

extern unsigned long long OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern void Ov002_ApplyTimerCommand(int bFlag, u32 nElapsed);
extern int Ov002_BuildSessionCommand(int nKind, void *pCmd);

void Ov002_ReportElapsed(void)
{
    Ov002TickCtx *pCtx;
    Ov002TickCmd cmd;
    int nNow;

    pCtx = data_ov002_0207fa08;
    nNow = (int)func_02020368(OS_GetTick() << 6, 0x82ea);
    pCtx->nElapsed = pCtx->nElapsed + (nNow - pCtx->nLastMs);

    if (pCtx->nElapsed >= 1000 || Session_IsActive() == 0) {
        cmd.bFlag = 1;
        cmd.nElapsed = pCtx->nElapsed;
        if (Session_IsActive() == 0) {
            Ov002_ApplyTimerCommand(cmd.bFlag, cmd.nElapsed);
            pCtx->nElapsed = 0;
        } else if (Ov002_BuildSessionCommand(7, &cmd) != 0xffff) {
            pCtx->nElapsed = 0;
        }
    }

    pCtx->nLastMs = nNow;
}
