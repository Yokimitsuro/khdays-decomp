/* Packs the object's VRAM address and the caller's offset into a texture handle. */
unsigned func_ov107_020c9440(char *obj, unsigned offset) {
    unsigned mask = 0xfffffc;
    unsigned addr = *(unsigned *)(obj + 0x1a4);
    if (addr == 0) {
        return 0;
    }
    return (((addr + 0x8000) & mask) << 7 | 0x80000000) | (offset & (mask >> 15));
}
