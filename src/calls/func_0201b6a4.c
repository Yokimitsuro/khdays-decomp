typedef struct {
    char _0[0x84];
    void *field_84;
} S_0201b6a4;

typedef struct {
    char _0[8];
    unsigned int count;
    char _c[4];   /* unused base of entries at +0xc with stride 16 */
} ArrayHdr;

extern S_0201b6a4 *data_0204ad4c;

int func_0201b6a4(unsigned int idx) {
    S_0201b6a4 *s = data_0204ad4c;
    ArrayHdr *h = (ArrayHdr *)s->field_84;
    if (idx >= h->count) return 0;
    return *(int *)((char *)h + (idx << 4) + 0xc);
}
