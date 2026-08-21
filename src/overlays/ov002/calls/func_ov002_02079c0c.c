typedef unsigned short u16;

extern int func_ov002_0207687c(void);
extern int func_ov002_0207c700(char *pElement, u16 *pTable, int nDelta,
                               int nFlag, int nLimit, int *pElapsed);
extern void func_ov002_02079824(char *pElement);
extern void func_ov002_020798a0(char *pElement);
extern void *func_ov002_02079b44(char *pElement);

/* Drive an element that is finishing.
 *
 * Only the finishing phase does anything here: the entry table is advanced by
 * the module scale against the owner's limit for the current mode. While that
 * still has work the element stays on this handler; once it is done the cycle
 * is restarted, the named bindings are re-applied and the element goes back to
 * the watching handler.
 */
void *func_ov002_02079c0c(char *pElement)
{
    char *pOwner;
    int nDelta;

    pOwner = *(char **)(pElement + 8);
    nDelta = func_ov002_0207687c();

    if (*(unsigned char *)(pElement + 0x1c1) != 2) {
        return 0;
    }

    if (func_ov002_0207c700(pElement, (u16 *)(pElement + 0x2c), nDelta, 0,
                            *(int *)(pOwner
                                     + *(signed char *)(pElement + 0x1ce) * 4
                                     + 0x70),
                            (int *)(pElement + 0x1d0)) == 0) {
        func_ov002_02079824(pElement);
        func_ov002_020798a0(pElement);
        return func_ov002_02079b44;
    }

    return 0;
}
