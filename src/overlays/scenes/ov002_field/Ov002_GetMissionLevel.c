/* The mission's level, a signed byte the field root (data_ov002_0207fa00) keeps at +0x8bae
 * (Ov002_SelectTableEntry stores it): the base of each enemy's level (Ov002_GetMarkerEnemyLevel). */

extern int data_ov002_0207fa00;

int Ov002_GetMissionLevel(void) {
    return *(signed char *)(*(int *)&data_ov002_0207fa00 + 0x8bae);
}
