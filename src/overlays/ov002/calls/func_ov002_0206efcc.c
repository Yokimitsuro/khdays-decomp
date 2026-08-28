typedef signed short s16;

extern char *data_ov002_0207fa04;   /* the ov002 event context */

/* Closes the event an id names and lets go of its handle.
 *
 * Bit 12 of the id picks which of the context's two banks holds it, and the id
 * with that bit taken back off indexes that bank's handler array.  An id with
 * no handler there, or a handler with no hook at +8, is simply reported as
 * closed.
 *
 * Otherwise the hook is called as (handler, 1, 0).  An answer below zero
 * reports the event as still open and leaves the handles alone; on any other
 * answer, every one of the four handles that still holds this id is put back
 * to -1, the value they carry when idle.
 *
 * Ghidra models the context as Ov002EventContext: aHandles at +2, and
 * aBanks[2] of Ov002EventBank at +0xc, each bank starting with
 * Ov002EventHandler *aHandlers[32].
 */
int func_ov002_0206efcc(int nEventId)
{
    char *pCtx;
    char **ppHandlers;
    char *pHandler;
    int nIndex;
    int (*pfnAskClose)(char *pHandler, int nMode, int nArg);
    int i;

    pCtx = data_ov002_0207fa04;
    nIndex = nEventId;
    if ((nEventId & 0x1000) != 0) {
        ppHandlers = (char **)(pCtx + 0x12c);   /* aBanks[1].aHandlers */
        nIndex = nEventId & ~0x1000;
    } else {
        ppHandlers = (char **)(pCtx + 0xc);     /* aBanks[0].aHandlers */
    }
    pHandler = ppHandlers[nIndex];

    if (pHandler != 0) {
        pfnAskClose = *(int (**)(char *, int, int))(pHandler + 8);
        if (pfnAskClose != 0) {
            if (pfnAskClose(pHandler, 1, 0) < 0) {
                return 0;
            }
            for (i = 0; i < 4; i++) {
                if (nEventId == ((s16 *)pCtx)[i + 1]) {
                    ((s16 *)pCtx)[i + 1] = -1;
                }
            }
        }
    }
    return 1;
}
