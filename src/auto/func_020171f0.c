/* Element accessor: table at obj+0xc, count at obj[0xd], stride word at obj[0x12].
 * Returns &record[index] (stride bytes each, +4 header) or NULL when out of range. */
void *func_020171f0(unsigned char *obj, unsigned int index) {
    unsigned char *tbl = obj + 0xc;
    if (tbl != 0 && index < obj[0xd]) {
        unsigned int off = *(unsigned short *)(obj + 0x12);
        unsigned short stride = *(unsigned short *)(tbl + off);
        return tbl + off + 4 + stride * index;
    }
    return 0;
}
