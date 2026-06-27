extern void DC_InvalidateRange(void *addr, unsigned size);
extern char *data_02046280;

short func_02008d1c(int i, int j) {
    DC_InvalidateRange(data_02046280 + 0x20 + i * 0x24 + j * 2, 2);
    return *(short *)(data_02046280 + 0x20 + i * 0x24 + j * 2);
}
