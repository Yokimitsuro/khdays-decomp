/*
 * Takes the session screen into or out of its active presentation.
 *
 * Going active, a part mask says which pieces to touch; going idle, every
 * piece is touched. The pieces are the installed activity hook, the broadcast
 * to the peers, the current slot's flag and the scene objects. The broadcast
 * splits: with the peer flag set the whole table is walked and the flag is
 * retired afterwards, and without it a single call carries the state.
 *
 * Whichever way it went, the game mode is settled last: leaving restores the
 * saved mode, or mode two when the global says so, and staying drops to mode
 * zero once the session itself has gone.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov002RootContext {
    char pad0000[0x8b4c];
    int nSlotToken;
    char pad8b50[4];
    int nExitCode;
    char pad8b58[0x40];
    void (*pNotify)(int);
    char pad8b9c[0x30];
    int nHandle;
} Ov002RootContext;

typedef struct Ov002Thread {
    char pad00[0x3c];
    int nWake;
} Ov002Thread;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_02023588(int nFlagId);
extern void func_020235bc(int nFlagId);
extern void func_ov022_0208808c(int a);
extern int func_ov022_020882f8(void);
extern void func_ov022_020888b8(int nIndex, int a);
extern int func_ov002_0207386c(void);
extern void func_ov002_02074054(int a);
extern Ov002Thread *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov002_020765f8(int a);
extern int func_02030670(void);
extern void func_02023c30(int a);
extern int func_02020a9c(void);

void func_ov002_0206aae4(int bLocal, int nMask)
{
    Ov002RootContext *pCtx;
    void (*pNotify)(int);
    Ov002Thread *pThread;
    int i;

    pCtx = data_ov002_0207fa00;
    if (pCtx->nSlotToken == -1 && func_02023588(0x20b5) == 0) {
        return;
    }
    if (func_02023588(0x20b5) != 0 && bLocal == 0) {
        return;
    }

    if (pCtx->nSlotToken != -1) {
        pNotify = pCtx->pNotify;
        if (pNotify != 0 && ((nMask & 1) != 0 || bLocal == 0)) {
            pNotify(bLocal);
        }
    }

    if (bLocal != 0 || pCtx->nHandle != -1) {
        if (pCtx->nHandle != -1 && ((nMask & 2) != 0 || bLocal == 0)) {
            if (func_02023588(0x20b6) != 0) {
                func_ov022_0208808c(0);
                i = 0;
                if (func_ov022_020882f8() > 0) {
                    do {
                        func_ov022_020888b8(i, bLocal);
                        i++;
                    } while (i < func_ov022_020882f8());
                }
                if (bLocal == 0) {
                    func_020235bc(0x20b6);
                }
            } else {
                func_ov022_0208808c(bLocal);
            }
        }

        if (func_ov002_0207386c() != -1
            && ((nMask & 4) != 0 || bLocal == 0)) {
            func_ov002_02074054(bLocal == 0 ? 1 : 0);
            if (bLocal == 0) {
                pThread = OS_IsThreadAvailable_0x020c9848();
                if (pThread != 0) {
                    pThread->nWake = 0x1000;
                }
            }
        }

        if ((nMask & 8) != 0 || bLocal == 0) {
            func_ov002_020765f8(bLocal);
        }
    }

    if (bLocal != 0) {
        if (func_02030670() != 0) {
            return;
        }
        func_02023c30(0);
        return;
    }

    if ((func_02020a9c() & 8) != 0) {
        func_02023c30(2);
        return;
    }
    func_02023c30((u8)pCtx->nExitCode);
}
