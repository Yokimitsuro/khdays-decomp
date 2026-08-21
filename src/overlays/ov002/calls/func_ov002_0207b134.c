typedef unsigned short u16;

extern int func_ov002_0206b758(void);
extern int func_ov002_0206b828(void);
extern int func_ov002_02072754(int nHandle);
extern int func_01ff8e94(void *pA, void *pB);

/* Decide whether an actor is close enough to trigger a spare entry.
 *
 * Only the local player counts, and only while the guard allows it. The actor
 * must be on its feet, must be showing something, must hold a real slot, and
 * that slot must be the entry's own bucket. What is left is a distance test
 * against the actor's position.
 */
int func_ov002_0207b134(char *pEntry, char *pActor)
{
    int nFlags;

    if (func_ov002_0206b758() != 0 && func_ov002_0206b828() == 0) {
        nFlags = *(int *)(pActor + 0x464);
        if ((nFlags & 0x10000000) != 0 || (nFlags & 0x8000000) != 0
            || *(u16 *)(pActor + 0x12) == 0) {
            return 0;
        }

        if (*(short *)(pActor + 0x66) >= 0
            && *(unsigned char *)(pEntry + 0x10)
                   == func_ov002_02072754(*(short *)(pActor + 0x66))) {
            if (func_01ff8e94(pEntry + 0x1c, pActor + 0x48c) <= 0xc00) {
                return 1;
            }
        }
    }

    return 0;
}
