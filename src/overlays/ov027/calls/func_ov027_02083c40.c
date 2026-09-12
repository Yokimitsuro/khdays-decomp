#pragma thumb on
extern void func_02013484(void *pScreenDst, void *pScreenData, int srcX, int srcY,
                          int dstX, int dstY, unsigned int dstW, unsigned int dstH,
                          int width, int height);

void func_ov027_02083c40(int table, int idx) {
    unsigned short *screenHeader = *(unsigned short **)(table + 0x54);
    int slot = table + idx * 0x18;
    func_02013484((void *)(screenHeader + 6), *(void **)(table + 4),
                  *(int *)(slot + 8), *(int *)(slot + 0xc),
                  *(int *)(slot + 0x10), *(int *)(slot + 0x14),
                  screenHeader[0], screenHeader[1],
                  *(int *)(slot + 0x18), *(int *)(slot + 0x1c));
}
