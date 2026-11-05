/* Ov008_BuildBadgeMask -- the badges mission file nFile has: walks the list of the missions' rows (menu
 * +0x4d4) and, for each of the file's rows whose kind (+0x18) is not 0, sets bit kind - 1: bit 0
 * the ordeal badge, 1 the blazon, 3 the unity badge. The mask is byte-wide. */
extern unsigned short *Ov008_FindNextMissionEntry(int list, int node);

unsigned int Ov008_BuildBadgeMask(int pMenu, unsigned int nFile) {
    unsigned int mask = 0;
    unsigned short *n;
    for (n = Ov008_FindNextMissionEntry(pMenu + 0x4d4, 0); n != 0;
         n = Ov008_FindNextMissionEntry(pMenu + 0x4d4, (int)n)) {
        if (*n == nFile) {
            int nKind = *(int *)((char *)n + 0x18);
            if (nKind != 0) {
                mask = (mask | 1 << (nKind - 1)) & 0xff;
            }
        }
    }
    return mask;
}
