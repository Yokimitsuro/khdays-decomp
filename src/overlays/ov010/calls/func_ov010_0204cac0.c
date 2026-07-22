/* Zero a 0xc-byte resource handle and bind it to a file loaded via func_0201ef9c
 * (Archive_LoadFile). The loaded file starts with {offset, count}; the handle ends
 * up as {file, count, file + offset}.
 *
 * The tail spent a long time one register away from the ROM (`off` coloured to r1
 * where the ROM used r2) and was parked as a proven two-colouring tie after five
 * mwcc build-lines, the -O matrix, typed-struct forms and the `register` axis all
 * failed to move it. Every one of those attempts varied the body. The actual cause
 * was the SIGNATURE: this function RETURNS the loaded ResFile, so r0 is reserved
 * for the result and `off` has to go somewhere else. Declaring it void let the
 * allocator reuse r0 and no rewriting of the body could ever undo that.
 */
extern void MI_CpuFill8(void *dest, int val, int size);

typedef struct {
    int offset;   /* payload starts this many bytes into the file */
    int count;
} ResFile;

typedef struct {
    ResFile *file;
    int count;
    char *payload;
} ResHandle;

extern ResFile *func_0201ef9c(char *name, int kind);

ResFile *func_ov010_0204cac0(ResHandle *h, char *name, int p3, int p4) {
    ResFile *res;
    int off;
    char *base;

    MI_CpuFill8(h, 0, 0xc);

    res = func_0201ef9c(name, 0xe);
    h->file = res;

    off = res->offset;
    h->count = res->count;

    base = (char *)h->file;
    base += off;
    h->payload = base;
    return res;
}
