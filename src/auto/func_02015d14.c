/* Walk the node list (next at +0x10); for each node where arg2 is in range
 * (node[0x19]) and the entry halfword's bits 8-9 == 0x100 and a callback is
 * installed at +0xc, invoke cb(arg0, node, lowbyte). Return 1 if any fired. */
int func_02015d14(int arg0, unsigned char *node, int arg2) {
    int result = 0;
    if (node == 0) return 0;
    do {
        if ((unsigned int)arg2 < node[0x19]) {
            unsigned short v = *(unsigned short *)(node + arg2 * 2 + 0x1a);
            if ((v & 0x300) == 0x100) {
                void (*cb)(int, unsigned char *, int) =
                    *(void (**)(int, unsigned char *, int))(node + 0xc);
                if (cb != 0) {
                    cb(arg0, node, v & 0xff);
                    result = 1;
                }
            }
        }
        node = *(unsigned char **)(node + 0x10);
    } while (node != 0);
    return result;
}
