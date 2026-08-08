/* Advance one ov088 actor node through its wind-up/attack state machine.
 *
 * Before dispatching it runs an entry guard: if the node is idle nothing is forced,
 * but otherwise -- unless the node is already in state 6, unless the actor's mode is
 * 0x2e, unless the 0x10000 flag is set, and unless 02095524 reports the build block
 * busy -- the node is pushed straight to state 6. A second flag, this one in the high
 * word, resets the node to idle outright.
 *
 * Then the state selects one of seven arms. Most of them just feed the elapsed time to
 * 0202a818 and advance on its result; state 3 also accumulates the time until it
 * reaches the node's ceiling, and state 5 waits for the actor to leave modes 0x2f/0x30
 * before either resetting or handing off to 020b6200.
 *
 * +0x2c2c is declared WHOLE for the reason established on 020b5d34: it is not an
 * encodable ARM immediate, so mwcc splits it and places the halves itself. */
extern int func_ov022_02095524(char *pBlock);
extern void func_ov088_020bafd8(char *pNode, int nKind, int nParam);
extern void func_ov088_020bafa0(char *pNode);
extern int func_0202a818(char *pAnim, int nDelta);

void func_ov088_020bb03c(char *self, char *pNode, int nDelta)
{
    int *pBlock = (int *)(self + 0x2c2c);
    int nKind;

    if (*(int *)(pNode + 4) != 0) {
        if (*(int *)(pNode + 4) != 6 && *(int *)(self + 0x6bc) != 0x2e
            && (*(unsigned long long *)(self + 0x464) & 0x10000ULL) == 0
            && func_ov022_02095524(self + 0x22f8) == 0) {
            func_ov088_020bafd8(pNode, 2, 0xf000);
            *(int *)(pNode + 4) = 6;
        }
        /* Reached both by falling through and by every early exit above, but NOT when
         * the node was idle on entry -- the entry branch jumps past it to the switch. */
        if ((*(unsigned long long *)(self + 0x464) & 0x4000000000ULL) != 0) {
            *(int *)(pNode + 4) = 0;
        }
    }

    switch (*(int *)(pNode + 4)) {
    case 0:
        break;

    case 1:
        if (func_0202a818(pNode + 8, nDelta) == 0) {
            return;
        }
        func_ov088_020bafd8(pNode, 1, 0);
        *(int *)(pNode + 4) = 2;
        break;

    case 2:
        func_0202a818(pNode + 8, nDelta);
        break;

    case 3:
        func_0202a818(pNode + 8, nDelta);
        *(int *)(pNode + 0x114) += nDelta;
        if (*(int *)(pNode + 0x114) < *(int *)(pNode + 0x110)) {
            return;
        }
        /* A default that is conditionally overwritten, not a ternary: the ROM sets the
         * kind to 2 unconditionally and only then upgrades it with a movne. */
        nKind = 2;
        if (*pBlock != 0) {
            nKind = 3;
        }
        func_ov088_020bafd8(pNode, nKind, 0);
        *(int *)(pNode + 4) = 4;
        break;

    case 4:
        if (func_0202a818(pNode + 8, nDelta) != 0) {
            *(int *)(pNode + 4) = 5;
        }
        break;

    case 5:
        /* A switch, not an `||`: written with `||` mwcc folds the two adjacent values
         * into a range check (sub #0x2f / cmp #1), where the ROM keeps the cmp/cmpne
         * chain. Same lever as in the ov030 handler of this family. */
        switch (*(int *)(self + 0x6bc)) {
        case 0x2f:
        case 0x30:
            return;
        }
        if (func_ov022_02095524(self + 0x22f8) == 0) {
            *(int *)(pNode + 4) = 0;
            return;
        }
        func_ov088_020bafa0(pNode);
        break;

    case 6:
        if (func_0202a818(pNode + 8, nDelta) != 0) {
            *(int *)(pNode + 4) = 0;
        }
        break;
    }
}
