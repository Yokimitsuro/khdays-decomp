/* Walks the intrusive list at +0x18 and returns the first entry whose leading halfword
 * equals `key`, or NULL. */
extern unsigned short *NNS_FndGetNextListObject(void *list, void *obj);

unsigned short *func_ov005_0204ed5c(char *self, int key) {
    unsigned short *e = NNS_FndGetNextListObject(self + 0x18, 0);
    while (e != 0) {
        if (*e == key) {
            break;
        }
        e = NNS_FndGetNextListObject(self + 0x18, e);
    }
    return e;
}
