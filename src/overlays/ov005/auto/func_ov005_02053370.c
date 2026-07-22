/* Entry `i` of the word table at +0x4bfc minus the signed byte at +0x4bfe, narrowed to a
 * signed char and clamped to at most 7. */
extern char *data_ov005_0205b80c;

int func_ov005_02053370(int i) {
    char *p = data_ov005_0205b80c + 0x3fc + 0x4800;
    int v = *(int *)(p + i * 4 + 8) - *(signed char *)(p + 2);
    v = (signed char)v;
    if (v > 7) {
        v = 7;
    }
    return v;
}
