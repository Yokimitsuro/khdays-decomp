/* ov088 actor: drive one update pass over the group's parts.
 *
 * Walks the group's parts (0x1c8 apart, count at +0x19) and dispatches each one by the
 * signed kind byte at +2: kind 0 is skipped, kind 2 goes to the kind-2 handler, and
 * anything else is called through the handler table at data_ov088_020bc274 indexed by
 * the kind.
 *
 * After the kind-2 handler runs, a part that has become kind 4 while the group's head
 * word is zero and nothing has fired yet triggers the one-shot: it plays 0xcb at the
 * part's +0xcc when bit 0 of the actor's +0x694 is set, arms the pair at +0x47a/+0x47b
 * unless 02030788 reports busy or flag 0x10000 is set, and latches the fired flag so
 * no later part repeats it.
 *
 * The actor's flag word at +0 is a 64-bit field, so the guard masks it as a long long
 * and truncates the result. Only the low half is ever needed here, and the same spelling
 * appears in the matching arming block of func_ov047_020b3c54.
 */
struct ActorBits {
    unsigned char bReady : 1;
};

extern void func_ov088_020bbc34(char *pGroup, char *pPart, int nArg);
extern void func_02033d0c(int nSound, int nVariant, char *pPos, int nOwner);
extern int func_02030788(void);

extern void (*data_ov088_020bc274[])(char *pGroup, char *pPart, int nArg);

void func_ov088_020bbadc(char *pGroup, int nArg)
{
    char *pPart;
    char *pActor = *(char **)(pGroup + 8);
    int bFired = 0;
    int i = 0;
    int nOff;
    void (**pTable)(char *, char *, int);

    if ((int)*(unsigned char *)(pGroup + 0x19) <= 0) {
        return;
    }
    pTable = data_ov088_020bc274;
    nOff = 0;
    do {
        pPart = *(char **)(pGroup + 0xc) + nOff;
        int nKind = *(signed char *)(pPart + 2);

        if (nKind != 0) {
            if (nKind != 2) {
                pTable[nKind](pGroup, pPart, nArg);
            } else {
                func_ov088_020bbc34(pGroup, pPart, nArg);
                if (*(signed char *)(pPart + 2) == 4 && *(int *)pGroup == 0
                    && bFired == 0) {
                    if (((struct ActorBits *)(pActor + 0x694))->bReady) {
                        func_02033d0c(0xcb, 0, pPart + 0xcc, 0);
                    }
                    if (func_02030788() == 0
                        && (int)(*(long long *)pActor & 0x10000) == 0) {
                        *(char *)(pActor + 0x47a) = 3;
                        *(char *)(pActor + 0x47b) = 0;
                    }
                    bFired = 1;
                }
            }
        }
        nOff += 0x1c8;
        i++;
    } while (i < (int)*(unsigned char *)(pGroup + 0x19));
}
