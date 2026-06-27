extern void *func_02010ccc(void *p);
extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);

typedef struct {
    char _0[0x20];
    unsigned int flags;
    char _24[4];
    unsigned int size;
} X02010ce4;

void *func_02010ce4(X02010ce4 *p)
{
    void *out = func_02010ccc(&p->_24);

    if (out != 0) {
        unsigned char flags = p->flags;
        unsigned int size = p->size;

        if (flags & 1)
            INITi_CpuClear32_0x01ff86fc(0, out, size);
    }

    return out;
}
