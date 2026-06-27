typedef struct Entry {
    int base;
    int size;
    void *pad8;
    int padC;
} Entry;

typedef struct Tbl {
    int pad0;
    int pad4;
    int count;
    Entry entries[1];
} Tbl;

typedef struct G {
    char pad[0x84];
    Tbl *tbl;
} G;

extern G *data_0204ad4c;

void *func_0201b7e0(unsigned int idx) {
    Tbl *tbl = data_0204ad4c->tbl;
    if (idx >= (unsigned int)tbl->count) return 0;
    return tbl->entries[idx].pad8;
}
