/*
 * Ov002_SubmitActorDraw - hand one bound actor to the geometry engine.
 *
 * Does nothing unless the actor is both live (flag bit 0) and has its sequence
 * registered (flag bit 3). Sends the same word three times as the 0x1b command
 * - the material triple, taken from +0x1c of the object at +0x28 - submits the
 * cached command block, applies the stored parameter when the node's bit 6 is
 * set, streams the twelve words at +0x10c as command 0x17, and runs the actor's
 * channels.
 *
 * ARM. Both guards are early returns so mwcc predicates them; the flag byte is
 * read once and both bits tested off that one load.
 */

extern void func_01ff9f00(unsigned int nCmd, const void *pSrc,
                          unsigned int nWords);   /* GX_SendFifoWords */
extern void func_0201571c(void);                  /* submit the cached block */
extern void func_01ffcec0(unsigned int nValue);
extern void func_020279e0(unsigned int *pChannels);

void func_ov002_02051cbc(unsigned char *pActor)
{
    unsigned int aMaterial[3];
    unsigned int nValue;

    if ((pActor[0] & 1) == 0) {
        return;
    }
    if ((pActor[0] & 8) == 0) {
        return;
    }

    nValue = *(unsigned int *)(*(int *)(pActor + 0x28) + 0x1c);
    aMaterial[0] = nValue;
    aMaterial[1] = nValue;
    aMaterial[2] = nValue;
    func_01ff9f00(0x1b, aMaterial, 3);
    func_0201571c();

    if ((*(unsigned short *)(pActor + 4) & 0x40) != 0) {
        func_01ffcec0(*(unsigned short *)(pActor + 0x108));
    }
    func_01ff9f00(0x17, pActor + 0x10c, 0xc);
    func_020279e0((unsigned int *)(pActor + 0x24));
}
