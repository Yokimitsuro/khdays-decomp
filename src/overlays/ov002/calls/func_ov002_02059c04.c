/* Find the first entry in the context's list at +0x10 whose leading byte is the
 * 0xff empty marker. Returns it, or 0 when the list has none. */
extern void *NNS_FndGetNextListObject(void *list, void *from);

extern char *data_ov002_0207f61c;

void *func_ov002_02059c04(void) {
    char *ctx = data_ov002_0207f61c;
    unsigned char *node = NNS_FndGetNextListObject(ctx + 0x10, 0);

    while (node != 0) {
        if (*node == 0xff) {
            break;
        }
        node = NNS_FndGetNextListObject(ctx + 0x10, node);
    }

    return node;
}
