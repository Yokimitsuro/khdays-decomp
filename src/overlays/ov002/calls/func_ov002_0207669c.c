typedef struct {
    unsigned char pad0000[0x1fc];
    unsigned int dwActiveMask;
} Ov002ListTable;

typedef struct {
    unsigned char pad0000[4];
    Ov002ListTable *pTable;
} Ov002ListRoot;

extern Ov002ListRoot data_ov002_0207fa20;

void func_ov002_0207669c(unsigned int bitIndex)
{
    if (bitIndex == 0xffff) {
        data_ov002_0207fa20.pTable->dwActiveMask = -1;
    } else {
        data_ov002_0207fa20.pTable->dwActiveMask |= 1 << bitIndex;
    }
}
