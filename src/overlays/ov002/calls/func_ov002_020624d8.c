/* Load one archive file, push its character data to the sub engine's BG1 and
 * free the block again -- a one-shot upload that owns nothing afterwards.
 * func_02011988 decodes the block into the standard character header, source
 * pointer in word 5 and byte count in word 4. */
extern void *func_0201ef9c(const void *name, int kind);
extern int func_02011988(void *block, void *out);
extern void GXS_LoadBG1Char(void *src, unsigned int offset, unsigned int size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

extern char data_ov002_0207eccc[];

void func_ov002_020624d8(void) {
    int *chr;
    void *block = func_0201ef9c(&data_ov002_0207eccc, 0xe);

    func_02011988(block, &chr);
    GXS_LoadBG1Char((void *)chr[5], 0, chr[4]);

    if (block != 0) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
}
