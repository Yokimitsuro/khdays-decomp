typedef unsigned char u8;

typedef struct Ov000ProbeTemplate {
    void *reserved;
    const void *source8;
} Ov000ProbeTemplate;

extern void *NNS_FndAllocFromDefaultExpHeapEx(
    unsigned int size,
    unsigned int alignment
);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void MI_CpuCopy8(const void *source, void *destination, unsigned int size);
extern void MIi_CpuClearFast(int value, void *destination, unsigned int size);
extern int func_ov000_0205493c(
    unsigned int offset,
    void *buffer,
    unsigned int size
);
extern Ov000ProbeTemplate data_ov000_0205ab80;

int func_ov000_02054b1c(void) {
    int result = 1;
    u8 *buffer = NNS_FndAllocFromDefaultExpHeapEx(0x20, 0x20);
    int byteOffset = 0;
    int i;
    int lane;
    int group;
    int groupBase;

    for (i = 0; i < 4; i++) {
        MI_CpuCopy8(data_ov000_0205ab80.source8, buffer + byteOffset, 8);
        byteOffset += 8;
    }

    if (func_ov000_0205493c(0, buffer, 0x20) != 0) {
        result = 0;
    } else {
        MIi_CpuClearFast(0, buffer, 0x20);
        groupBase = 0;
        for (group = 0; group < 3; group++) {
            for (lane = 0; lane < 2; lane++) {
                if (func_ov000_0205493c(
                        (lane + groupBase) * 0x2018 + 0x20,
                        buffer,
                        0x20
                    ) != 0) {
                    result = 0;
                    goto done;
                }
            }
            groupBase += 2;
        }
    }

done:
    NNSi_FndFreeFromDefaultHeap(buffer);
    return result;
}
