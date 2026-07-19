extern void OS_SPrintf(char *buf, char *fmt, char *code);
extern void *func_0201ef9c(void *path, int heap);
extern void func_ov002_02052308(void *dst, void *file, int slot, int arg);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

extern char *data_02042a70[];
extern char data_ov002_0207e870[];

/* Load one character's weapon model and pack it into the caller's table row.
 * data_ov002_0207e870 is "ba/ch/%s/wp.b.z" and data_02042a70 is the table of
 * two-letter character codes -- "ro" "ri" "go" "ax" "xi" "la" "sa" "so"
 * (Roxas, Riku, ..., Axel, Xion, Larxene, Saix, Sora) -- so `slot` indexes the
 * roster.  The archive file is transient: packed, then freed straight away.
 *
 * Takes THREE parameters.  Ghidra shows four; only r0-r2 are ever set up. */
void func_ov002_020522c8(void *dst, int slot, int arg) {
    char path[128];
    void *file;

    OS_SPrintf(path, data_ov002_0207e870, data_02042a70[slot]);
    file = func_0201ef9c(path, 6);
    func_ov002_02052308(dst, file, slot, arg);
    NNSi_FndFreeFromDefaultHeap(file);
}
