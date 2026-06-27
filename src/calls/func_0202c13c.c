extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void *func_02028df0(void *entry, void *arg1);

typedef struct {
    unsigned short pad0;
    unsigned short count;
    void **entries;
} S5;

extern S5 *func_0202bfa0(void *arg);

extern unsigned char *data_0204c208;

void func_0202c13c(void *arg0, void *arg1, const void *src, unsigned int size) {
    S5 *s;
    int i;
    void *entry;
    unsigned int off;
    unsigned char *dst;

    s = func_0202bfa0(arg0);
    i = 0;
    if ((int)s->count <= 0) {
        return;
    }
    do {
        if (s->entries[i] != 0) {
            entry = func_02028df0(s->entries[i], arg1);
            if (entry != 0) {
                off = *(unsigned int *)(data_0204c208 + 0xa1cc);
                dst = data_0204c208 + 0x61cc + off;
                *(unsigned int *)(data_0204c208 + 0xa1cc) = off + size;
                MI_CpuCopy8(src, dst, size);
                *(void **)((unsigned char *)entry + 0x10) = dst;
                return;
            }
        }
        i++;
    } while (i < (int)s->count);
}
