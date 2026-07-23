/* func_ov022_0209bf54 -- reset the actor's 0x2aa4 action block and re-seed it from the
 * per-actor table row at data_0204c3d8 + kind * 0x44 (kind = the byte at obj+9).
 * Row byte +0x31 selects the mode: 1 or 4 -> mode 1, 3 -> mode 2, anything else leaves
 * the block cleared. Row +0x30 and +0x32 supply the two parameters.
 *
 * The block pointer is UNSIGNED char: p[0xf] is read back into p[0xc], and the ROM's
 * plain ldrb there is what rules out a signed char (which costs a ldrsb with a register
 * offset in THUMB). */
extern int data_0204c3d8;

void func_ov022_0209bf54(int obj) {
    unsigned char b = *(unsigned char *)(obj + 9);
    unsigned char *p = (unsigned char *)(obj + 0x2aa4);
    int tbl = (int)&data_0204c3d8 + b * 0x44;
    char c;
    *(int *)p = 0;
    *(int *)(p + 4) = 0;
    p[0xf] = 0;
    p[0xc] = 0;
    p[0xd] = 0;
    *(int *)(p + 8) = 0;
    p[0x10] = 0;
    p[0x11] = 0;
    p[0xe] = 0;

    c = *(char *)(tbl + 0x31);
    if (c != 0) {
        switch (c) {
        case 1:
        case 4:
            p[0x11] = *(char *)(tbl + 0x30);
            p[0x10] = 1;
            p[0xf] = *(char *)(tbl + 0x32);
            p[0xc] = p[0xf];
            break;
        case 3:
            p[0x11] = *(char *)(tbl + 0x30);
            p[0x10] = 2;
            p[0xf] = *(char *)(tbl + 0x32);
            p[0xc] = p[0xf];
            break;
        }
    }
}
