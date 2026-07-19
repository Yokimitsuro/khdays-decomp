typedef struct {
    unsigned pad : 1;
    unsigned request : 1;
    int enabled : 1;
} Ov107Flags;

/* Sets the request bit, but only while the enabled bit is on. */
void func_ov107_020c1348(char *obj, unsigned request) {
    Ov107Flags *f = (Ov107Flags *)(obj + 0x40);
    if (f->enabled == 0) {
        request = 0;
    }
    f->request = request;
}
