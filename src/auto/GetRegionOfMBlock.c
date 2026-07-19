typedef struct { int start, end; } Region;

/* The block header packs the distance back to its allocation base in bits 8..14 of the halfword
 * at +2; the payload starts 0x10 in and runs for the stored length. */
void GetRegionOfMBlock(Region *out, void *b) {
    int hdr = *(unsigned short *)((char *)b + 2);
    unsigned short back = (unsigned short)((hdr >> 8) & 0x7f);
    int payload = (int)b + 0x10;
    out->start = (int)b - back;
    out->end = *(int *)((char *)b + 4) + payload;
}
