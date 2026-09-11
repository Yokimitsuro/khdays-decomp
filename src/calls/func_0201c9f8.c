typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    char pad000[0x124];
    u8 nameLen;                 /* 0x124 */
    char pad125[0x126 - 0x125]; /* 0x125 */
    char name[0x12c - 0x126];   /* 0x126..0x12b */
    void *buffer;                /* 0x12c */
    u32 bufferSize;              /* 0x130 */
    char pad134[0x174 - 0x134];
} Entry;

extern Entry data_0204b62c[4];

extern u8 *func_0201b640(u32 idx);
extern void *func_0201b9a0(void *heap, u32 size, void *fn, void *ctx, int extra);
extern void func_0201d0e0(Entry *p);
extern void func_0201d3c4(int key, int value, void *p);

int func_0201c9f8(void *heap)
{
    int i;
    u32 size;
    Entry *entry;
    int startIdx;
    int extra;
    int j;

    i = 0;
    entry = data_0204b62c;
    startIdx = i;
    extra = i;

    for (; i < 4; i++, entry++) {
        u8 *src = func_0201b640(i);
        if (src == 0) {
            continue;
        }

        entry->nameLen = src[0];
        for (j = startIdx; j < src[0]; j++) {
            entry->name[j] = src[j + 1];
        }

        if (heap != 0) {
            void *buf;
            size = entry->nameLen << 11;
            buf = func_0201b9a0(heap, size, (void *)func_0201d3c4, entry, extra);
            if (buf == 0) {
                return 0;
            }
            func_0201d0e0(entry);
            entry->buffer = buf;
            entry->bufferSize = size;
        }
    }

    return 1;
}
