/* Case-insensitive name lookup: scan this->entries[] (stride 0x18) for one whose
 * 8-byte name matches key, using the case-folding compare at 0x0201f7bc.
 * WM_EndKeySharing_0x0202019c is the (mislabeled) veneer to that compare. */
extern int WM_EndKeySharing_0x0202019c(void *a, void *b, int n);

typedef struct TableA {
    char _pad[0x76];
    unsigned short count;                    /* 0x76 */
    char _pad2[0x94 - 0x78];
    char *entries;                           /* 0x94 */
} TableA;

char *func_02028d90(TableA *this, void *key)
{
    int i = 0;
    if ((int)this->count > 0) {
        int off = 0;
        do {
            char *base = this->entries;
            if (WM_EndKeySharing_0x0202019c(base + off, key, 8) == 0)
                return base + off;
            i++;
            off += 0x18;
        } while (i < (int)this->count);
    }
    return 0;
}
