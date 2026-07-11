/* Walk the range list at (*obj)[0xc] (records {u16 lo, u16 hi, next at +4, data
 * at +8}); for lo<=key<=hi return &data[(key-lo)*3], else the default (*obj)+4. */
void *func_0201371c(void **obj, unsigned int key) {
    char *rec;
    char *base = (char *)*obj;
    rec = *(char **)(base + 0xc);
    while (rec != 0) {
        unsigned int lo = *(unsigned short *)rec;
        if (lo <= key && key <= *(unsigned short *)(rec + 2)) {
            return rec + 8 + (key - lo) * 3;
        }
        rec = *(char **)(rec + 4);
    }
    return base + 4;
}
