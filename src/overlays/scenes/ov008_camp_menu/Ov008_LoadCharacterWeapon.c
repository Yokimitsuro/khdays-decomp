extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Archive_LoadFile(void *path, int heap);
extern void Ov008_PackTableRow(void *dst, void *file, int slot, int arg);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

extern char *data_02042a70[];
extern char gOv008BaChWpPathFmt[];

/* Load one character's weapon model and pack it into the caller's table row.
 * gOv008BaChWpPathFmt is "ba/ch/%s/wp.b.z" and data_02042a70 is the table of
 * two-letter character codes -- "ro" "ri" "go" "ax" "xi" "la" "sa" "so"
 * (Roxas, Riku, ..., Axel, Xion, Larxene, Saix, Sora) -- so `slot` indexes the
 * roster.  The archive file is transient: packed, then freed straight away.
 *
 * Takes THREE parameters.  Ghidra shows four; only r0-r2 are ever set up. */
void Ov008_LoadCharacterWeapon(void *dst, int slot, int arg) {
    char path[128];
    void *file;

    OS_SPrintf(path, gOv008BaChWpPathFmt, data_02042a70[slot]);
    file = Archive_LoadFile(path, 6);
    Ov008_PackTableRow(dst, file, slot, arg);
    NNSi_FndFreeFromDefaultHeap(file);
}
