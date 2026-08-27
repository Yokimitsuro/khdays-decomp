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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

extern unsigned long long func_020031d4(void);
extern unsigned long long func_02020368(unsigned long long value,
                                        unsigned int divisor, int arg3);
extern int func_02030670(void);
extern void func_ov002_0206f788(int bFlag, u32 nElapsed);
extern int func_ov002_0206fb84(int nKind, void *pCmd);

void func_ov002_0206f25c(void)
{
    Ov002TickCtx *pCtx;
    Ov002TickCmd cmd;
    int nNow;

    pCtx = data_ov002_0207fa08;
    nNow = (int)func_02020368(func_020031d4() << 6, 0x82ea, 0);
    pCtx->nElapsed = pCtx->nElapsed + (nNow - pCtx->nLastMs);

    if (pCtx->nElapsed >= 1000 || func_02030670() == 0) {
        cmd.bFlag = 1;
        cmd.nElapsed = pCtx->nElapsed;
        if (func_02030670() == 0) {
            func_ov002_0206f788(cmd.bFlag, cmd.nElapsed);
            pCtx->nElapsed = 0;
        } else if (func_ov002_0206fb84(7, &cmd) != 0xffff) {
            pCtx->nElapsed = 0;
        }
    }

    pCtx->nLastMs = nNow;
}
