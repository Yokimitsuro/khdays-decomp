/* func_ov000_0205a118 -- find the active logo touch/hit entry, ov000. Fills a local
 * 4-entry table (func_02024da4), scans it backwards for the entry whose f4==1 and
 * f6==0, and copies that 8-byte entry to *out. If none match, clears out[+4]. */
struct Entry { unsigned short v0, v1, f4, f6; };
extern int func_02024da4(struct Entry *table);
void func_ov000_0205a118(unsigned short *out) {
    struct Entry buf[4];
    struct Entry *found = 0;
    int i = func_02024da4(buf) - 1;
    while (i >= 0) {
        if (buf[i].f4 == 1 && buf[i].f6 == 0) {
            found = &buf[i];
            break;
        }
        i--;
    }
    if (found == 0) {
        out[2] = 0;
        return;
    }
    *(struct Entry *)out = *found;
}
