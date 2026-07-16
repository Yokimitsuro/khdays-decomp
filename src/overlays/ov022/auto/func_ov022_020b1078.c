/* Validate the header at obj (magic 0xfeff at +4, 0x10 at +0xc, 1 at +0xe); if OK,
 * follow obj+obj[0x10] and return that record's [9] byte (or 0 if its [8] is set). */
int func_ov022_020b1078(unsigned char *obj) {
    if (obj == 0) return 0;
    if (!(*(unsigned short *)(obj + 4) == 0xfeff
          && *(unsigned short *)(obj + 0xc) == 0x10
          && *(unsigned short *)(obj + 0xe) == 1)) {
        return 0;
    }
    {
        unsigned char *p = obj + *(int *)(obj + 0x10);
        return p[8] != 0 ? 0 : p[9];
    }
}
