typedef struct {
    int pad00;
    int aValues[3];                 /* +0x04, indexed by player minus one */
    int nExtra;                     /* +0x10 */
} Ov002AckArg;

extern char *const data_ov002_0207fa00;

extern int func_02030788(void);
extern int func_02030694(void);

/* Record this player's acknowledgement. The two values are only stored while
 * the session is not yet ready; the ready bit is raised either way. */
void func_ov002_0206c144(const Ov002AckArg *pArg)
{
    char *pRoot;
    char *pSlots;
    int nSelf;

    pRoot = data_ov002_0207fa00;
    pSlots = pRoot + 0x8bcc;

    nSelf = func_02030788();

    if (func_02030694() == 0) {
        char *pSlot = pSlots + nSelf * 0x2c;

        *(int *)(pSlot + 0x18) = pArg->aValues[nSelf - 1];
        *(int *)(pSlot + 0x1c) = pArg->nExtra;
    }

    *(unsigned char *)(pRoot + 0x8d9e) |= 1 << nSelf;
}
