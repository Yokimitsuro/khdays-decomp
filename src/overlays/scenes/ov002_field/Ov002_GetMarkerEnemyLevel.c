/* The level of the enemy a marker row spawns: the mission's level (the field root's +0x8bae) plus
 * the row's signed adjustment (+4), plus data_0204c254's +8 while bit 1 of data_0204c240 is set.
 * Capped at 0x78 (120) and floored at 1. Ov002_CreateActorFromMarker hands it to the actor's
 * stats loader, which reads that level's record. */
extern int Ov002_GetMissionLevel(void *self);

typedef struct {
    unsigned char bFlags;       /* +0 */
} Ov002LayoutFlags;

typedef struct {
    char pad0000[8];
    unsigned char bExtraRow;    /* +8 */
} Ov002LayoutMetrics;

extern Ov002LayoutFlags data_0204c240;
extern Ov002LayoutMetrics data_0204c254;

int Ov002_GetMarkerEnemyLevel(char *pRow) {
    int nLevel = Ov002_GetMissionLevel(pRow) + *(signed char *)(pRow + 4);

    if ((data_0204c240.bFlags & 2) != 0) {
        nLevel += data_0204c254.bExtraRow;
    }

    if (nLevel > 0x78) {
        nLevel = 0x78;
    }

    if (nLevel > 0) {
        return nLevel;
    }

    return 1;
}
