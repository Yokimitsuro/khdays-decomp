extern int FS_SeekFile(void *file, int offset, int origin);
extern int OS_UnlockByWord_0x0200ae4c(void *file, void *buf, int size);
extern void func_01ff8110(int r);

typedef struct Entry {
    int base;
    int size;
    int pad8;
    int padC;
} Entry;

typedef struct Tbl {
    int pad0;
    int pad4;
    int count;
    Entry entries[1];
} Tbl;

typedef struct G {
    char pad[0x34];
    char fs[0x50];              /* 0x34 file handle, 80 bytes -> ends at 0x84 */
    Tbl *tbl;                   /* 0x84 */
    int pad88;
    int pad8c;
    int chunk;                  /* 0x90 */
} G;

extern G *data_0204ad4c;

int func_0201b6f4(int idx, char *buf, int total, int off) {
    G *g = data_0204ad4c;
    Tbl *tbl = g->tbl;
    int copied;
    int chunk;
    Entry *e;
    int rem;
    int avail;
    int ret;
    int n;

    if ((unsigned)idx >= (unsigned)tbl->count) return -1;
    chunk = g->chunk;
    e = &tbl->entries[idx];
    if (chunk == 0) chunk = total;
    copied = 0;
    if (total > 0) {
        do {
            rem = total - copied;
            if (rem > chunk) rem = chunk;
            avail = e->size - off;
            if ((unsigned)rem > (unsigned)avail) rem = avail;
            if (rem == 0) break;
            ret = FS_SeekFile(&g->fs, e->base + off, 0);
            if (ret == 0) return -1;
            func_01ff8110(ret);
            n = OS_UnlockByWord_0x0200ae4c(&g->fs, buf, rem);
            if (n < 0) return n;
            copied += n;
            off += n;
            buf += n;
        } while (copied < total);
    }
    return copied;
}
