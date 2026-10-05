/* The player actor's item hand-over hook (pfnGiveItem, which Ov022_InitActor sets): the giver,
 * Ov017_ItemGivenStep, calls it with the item's spawn id, kind and key, and it passes them on
 * to Ov022_ApplyItemEffect for the actor kept at +0x18c. Only the first argument changes on the
 * way, as in the ROM's 16 bytes (load the actor into r0, branch with the caller's r1-r3). */

extern void Ov022_ApplyItemEffect(void *pActor, int nParam, unsigned int nKind, int nLevel);

void Ov022_OnItemGiven(char *pSub, int nSpawn, unsigned int nKind, int nKey) {
    Ov022_ApplyItemEffect(*(void **)(pSub + 0x18c), nSpawn, nKind, nKey);
}
