/* NONMATCHING: semantics correct (236B, size matches), residual codegen ties: the
 * param_1/param_2/buf/size register assignment (r4/r6/r5) differs from mwcc's, and
 * the count*4 + ((count+1)/2)*4 size term truncates as `half<<16>>14` vs the ROM's
 * `half<<17>>15` (both == half*4, 1-off intermediate width). Left as the reference
 * decode of the on-disk header.
 *
 * Open db_<lang>.p2, read its 16-byte header, size a table buffer from the record
 * count (header high u16 & 0x1ff, +count*8 if the 0x8000 flag is set) plus 0x10,
 * allocate it, copy the header (overwriting [1]=param_2, [2]=file offset, [3]+=file
 * length), read the table block into buf+0x10, close, and return buf. */
extern void FS_InitFile(void *f);
extern void FSi_WaitForCardThread(void);
extern char *func_02024e6c(char *path);
extern void FS_OpenFile(void *f, char *path);
extern void OS_UnlockByWord_0x0200ae4c();
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int size, int align);
extern void FS_CloseFile(void *f);
struct hdr4 { unsigned int a, b, c, d; };
unsigned int *func_02024ee8(char *param_1, unsigned int param_2, void *param_3, int param_4) {
    unsigned int hdr[4];
    char file[0x48];
    unsigned short count;
    unsigned int sz;
    unsigned int *buf;
    FS_InitFile(file);
    FSi_WaitForCardThread();
    FS_OpenFile(file, func_02024e6c(param_1));
    OS_UnlockByWord_0x0200ae4c(file, hdr, 0x10);
    count = *(unsigned short *)((char *)hdr + 2) & 0x1ff;
    sz = count * 4;
    sz = (unsigned short)(sz + (unsigned short)((count + 1) / 2) * 4);
    if (*(unsigned short *)((char *)hdr + 2) & 0x8000) {
        sz = (unsigned short)(sz + count * 8);
    }
    buf = (unsigned int *)NNS_FndAllocFromDefaultExpHeapEx((unsigned short)(sz + 0x10), 4);
    *(struct hdr4 *)buf = *(struct hdr4 *)hdr;
    buf[1] = param_2;
    buf[2] = *(unsigned int *)(file + 8);
    buf[3] = buf[3] + *(unsigned int *)(file + 0x24);
    OS_UnlockByWord_0x0200ae4c(file, buf + 4, sz, buf[3]);
    FS_CloseFile(file);
    return buf;
}
