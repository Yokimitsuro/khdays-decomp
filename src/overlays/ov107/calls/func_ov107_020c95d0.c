/* Inserts a new 4-byte entry (auto id + 3 payload bytes) into the node's sorted list at +0xb0. */

extern unsigned char *func_01fffca8(int list, int stride, int max);

unsigned char func_ov107_020c95d0(int node, unsigned char a, unsigned char b, unsigned char c) {
    unsigned char *entry = func_01fffca8(*(int *)(node + 0xb0), 4, 100);
    int id = *(int *)(node + 0xac);

    *(int *)(node + 0xac) = id + 1;
    entry[0] = (unsigned char)id;
    entry[1] = a;
    entry[2] = b;
    entry[3] = c;
    return entry[0];
}
