void func_ov008_02055910(int unused, unsigned char *request, int mode)
{
    unsigned short *header;
    unsigned short *tile;
    unsigned short modeBits;
    int row;
    int column;

    modeBits = (unsigned short)((unsigned int)mode << 12);
    for (row = 0; row < *(short *)(request + 0xc); row++) {
        header = *(unsigned short **)(*(int *)(request + 0x18) + 8);
        tile = (unsigned short *)((unsigned char *)header + 0xc)
             + (*(unsigned short *)(request + 6)
                + header[0] * (*(unsigned short *)(request + 8) + row) / 8);
        for (column = 0; column < *(short *)(request + 0xa); column++) {
            *tile = (unsigned short)(modeBits | (*tile & 0xfff));
            tile++;
        }
    }
}
