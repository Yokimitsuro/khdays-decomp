/* func_ov107_020c9074 -- store a value into a freshly reserved list cell, ov107.
 * Reserves the cell (func_01fffca8 on the pool @node+0x260) and writes val into it. */
extern int *func_01fffca8(void *pool, int, int);
void func_ov107_020c9074(char *node, int val) {
    *func_01fffca8(node + 0x260, 4, 0x64) = val;
}
