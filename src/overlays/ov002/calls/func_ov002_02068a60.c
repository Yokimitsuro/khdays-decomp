typedef unsigned char u8;

extern u8 data_0204be04;                /* the step is skipped while this is set */
extern u8 data_0204c240;                /* g_modeAndDayClock */

extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_0206ec54(int *pnEventId);  /* Ov002_PopAndDispatchEvent */
extern void func_ov002_0206f514(int nOn);       /* Ov002_SetSessionBusy */
extern int func_ov002_0206ed3c(int nEventId);    /* deliver, unless muted */
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cee0(int nArg0, int nArg1);
extern int func_ov002_0206efcc(int nEventId);   /* Ov002_CloseEvent */
extern void func_ov002_0206aae4(int nArg0, int nArg1);
extern void func_ov002_0206eaf8(void);
extern void func_02020878(int nOn);
extern void func_ov002_0206ed7c(void);
extern char *func_01fffde0(int nEntry);         /* the ov022 entry by index */
/* The second parameter is one the callee ignores: the ROM leaves the flags
   word it has just loaded in r1 across the call, which is how it shows up. */
extern int func_ov022_020886d0(int nEntry, int nFlags);
extern int func_ov022_020882e0(int nEntry);

extern void *func_ov002_02068c0c(void);
extern void *func_ov002_02068118(void);
extern void *func_ov002_02068d54(void);

/* One step of the session menu, handing back the state to run next, or null to
 * stay put.  Nothing happens at all while the hold flag is set.
 *
 * The arms are written 1, 2, 3, 0 because that is the order the ROM lays their
 * blocks down after the jump table.
 *
 * The last arm ends the session and rings off, unless the run is linked or the
 * local entry says otherwise.  Its index is held in nEntry rather than written
 * as a literal because the ROM materialises it before testing the flags word;
 * the pragma is what keeps that store, which is otherwise propagated into the
 * call and dropped.  func_ov002_0204d170 uses the same pair for the same
 * reason.
 */
#pragma opt_dead_assignments off
void *func_ov002_02068a60(void)
{
    char *pRoot;
    void *pNext;
    int nAnswer;
    int nEventId;
    int nFlags;
    int nEntry;

    pRoot = NNSi_FndGetCurrentRootHeap();
    pNext = 0;
    nEventId = -1;
    if (data_0204be04 != 0) {
        return pNext;
    }

    nAnswer = func_ov002_0206ec54(&nEventId);
    *(u8 *)(pRoot + 0x8b68) = 0x20;
    if (nAnswer != -1) {
        *(int *)(pRoot + 0x8b60) = -1;
    }

    switch (nAnswer) {
    case 1:
        if ((data_0204c240 & 4) == 0) {
            func_ov002_0206f514(1);
        }
        if (func_ov002_0206ed3c(nEventId) == 0) {
            *(int *)(pRoot + 0x8b60) = nEventId;
        }
        *(u8 *)(pRoot + 0x8b41) = 0xff;
        if (*(int *)(pRoot + 0x8b58) == 1) {
            func_ov002_0204cee0(func_ov022_02083f0c(), 1);
        }
        pNext = func_ov002_02068c0c;
        break;
    case 2:
        if (func_ov002_0206ed3c(nEventId) == 0
            && func_ov002_0206efcc(nEventId) == 0) {
            return 0;
        }
        func_ov002_0206aae4(0, 0);
        func_ov002_0206eaf8();
        func_ov002_0206f514(0);
        func_02020878(1);
        pNext = func_ov002_02068118;
        break;
    case 3:
        func_ov002_0206f514(1);
        func_ov002_0206ed7c();
        func_ov002_0206f514(0);
        pNext = func_ov002_02068d54;
        break;
    case 0:
        func_ov002_0206aae4(0, 0);
        func_ov002_0206f514(0);
        if ((data_0204c240 & 4) != 0
            || ((nFlags = *(int *)(func_01fffde0(0) + 0x464), nEntry = 0,
                 nFlags & 0x10000000) == 0
                && func_ov022_020886d0(nEntry, nFlags) == 0
                && func_ov022_020882e0(0) > 0)) {
            func_02020878(1);
        }
        pNext = func_ov002_02068118;
        break;
    }
    return pNext;
}
#pragma opt_dead_assignments on
