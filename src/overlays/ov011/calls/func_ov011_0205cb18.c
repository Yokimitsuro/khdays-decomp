/* func_ov011_0205cb18 -- Ov011 title/menu per-frame tick (MATCHED, 648 B).
 * Dispatches the current sub-handler via stateTable[nMode](), then runs a fade
 * toggle keyed on scene-flags bit2 and the ARM7 lid bit (0x027fffa8 & 0x8000). For
 * nMode < 4 it ticks func_ov011_0205b340 and, once a frame threshold and a matched
 * pair of fields are reached, dispatches one of the four layout builders
 * (be38/c074/c190/c2fc); flags bit1 gates a 180-frame idle timer. Finally, if an
 * argument was passed and key 0x8 is held, it snapshots nMode into nPrevMode, forces
 * nMode = 4, records the frame timer into timerPair[0]/[1] and fires
 * func_02033fec(0, 0x1e). Increments the global frame timer each call.
 *
 * Three codegen cracks made this match:
 *   1. flags bits are read as materialised signed bits, `(flags << 0x1d) >> 0x1f`
 *      (bit2) / `(flags << 0x1e) >> 0x1f` (bit1) -- this is the ROM's `lsl; asr`
 *      and keeps the -1/0 value live for reuse (`faded < 0` gives `lsls; bmi`, short).
 *   2. the fade branch is an `else if` chain (fade-in first), which puts the fade-in
 *      block as the fall-through exactly like the ROM; the `||`/nested-`if` shape and
 *      the plain `if/else` both lay the blocks out the other way.
 *   3. the two timerPair stores go through a NAMED `u16 *tp = pScene->timerPair;`.
 *      Without it mwcc allocates the store value above the base and cannot merge the
 *      two globals reads; the named base flips the register order so the `ldm` that
 *      loads {nTimer, pScene} together is emitted -- the last 16 words of the residue.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int  u32;
typedef void (*Ov011StateFn)(void);

typedef struct Ov011Scene {
    int nSubState;
    int nMode;
    int nPrevMode;
    u8  pad_000c[0x23ac0 - 0x0c];
    int flags;
    int nArg;
    u16 pair23ac8[2];
    u8  pad_23acc[0x2cf4c - 0x23acc];
    u16 timerPair[2];
    u16 pad_2cf50;
    u16 field2cf52;
    u8  pad_2cf54[0x2cf84 - 0x2cf54];
} Ov011Scene;

typedef struct Ov011Globals {
    int         nTimer;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern Ov011StateFn data_ov011_0205e8b4[];
extern volatile u16 data_0204c190;

extern int  func_0201e428(void);
extern void func_0201e374(int brightness);
extern int  func_0201e438(void);
extern void func_0201e3cc(int brightness);
extern void func_02005630(void);
extern void func_0200566c(void);
extern int  func_0200d49c(int a);
extern void func_ov011_0205b340(void);
extern void func_ov011_0205be38(void);
extern void func_ov011_0205c074(void);
extern void func_ov011_0205c190(void);
extern void func_ov011_0205c2fc(void);
extern void func_02033fec(int a, int b);

Ov011StateFn func_ov011_0205cb18(void)
{
    int mode;
    int faded;
    int done;

    data_ov011_0205e8b4[data_ov011_0205e960.pScene->nMode]();

    faded = (data_ov011_0205e960.pScene->flags << 0x1d) >> 0x1f;
    if (faded == 0 && (int)(*(volatile u16 *)0x027fffa8 & 0x8000) >> 0xf != 0) {
        func_02005630();
        func_0200d49c(0);
        data_ov011_0205e960.pScene->flags |= 4;
    } else if (faded != 0 &&
               (int)(*(volatile u16 *)0x027fffa8 & 0x8000) >> 0xf == 0 &&
               func_0200d49c(1) != 0) {
        data_ov011_0205e960.pScene->flags &= ~4;
        func_0201e374(func_0201e428());
        func_0201e3cc(func_0201e438());
        func_0200566c();
    }

    mode = data_ov011_0205e960.pScene->nMode;
    if (mode == 5) {
        return 0;
    }
    if (mode == 6) {
        return (Ov011StateFn)-2;
    }
    if (mode < 4) {
        if (((data_ov011_0205e960.pScene->flags << 0x1e) >> 0x1f) == 0) {
            func_ov011_0205b340();
            if (((data_ov011_0205e960.pScene->flags << 0x1e) >> 0x1f) == 0 &&
                (u32)data_ov011_0205e960.nTimer >= data_ov011_0205e960.pScene->field2cf52 &&
                data_ov011_0205e960.pScene->pair23ac8[0] ==
                    data_ov011_0205e960.pScene->pair23ac8[1]) {
                switch (data_ov011_0205e960.pScene->nMode) {
                case 0: func_ov011_0205be38(); break;
                case 1: func_ov011_0205c074(); break;
                case 2: func_ov011_0205c190(); break;
                case 3: func_ov011_0205c2fc(); break;
                }
            }
        } else {
            if (data_ov011_0205e960.pScene->nArg == 0) {
                done = data_0204c190 & 1;
            } else {
                data_ov011_0205e960.pScene->nSubState++;
                done = data_ov011_0205e960.pScene->nSubState >= 0xb4;
            }
            if (done != 0) {
                data_ov011_0205e960.pScene->flags &= ~2;
            }
        }
        if (data_ov011_0205e960.pScene->nArg != 0 && (data_0204c190 & 8) != 0) {
            u16 *tp;
            data_ov011_0205e960.pScene->nPrevMode = data_ov011_0205e960.pScene->nMode;
            data_ov011_0205e960.pScene->nMode = 4;
            tp = data_ov011_0205e960.pScene->timerPair;
            tp[0] = (u16)data_ov011_0205e960.nTimer;
            tp[1] = (u16)(data_ov011_0205e960.nTimer + 0x1e);
            func_02033fec(0, 0x1e);
        }
    }

    data_ov011_0205e960.nTimer++;
    return 0;
}
