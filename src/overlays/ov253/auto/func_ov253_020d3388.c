/* func_ov253_020d3388 -- clear the pending-request word at +0x3d0 of the owner and zero the first
 * word of every 0x38-byte record in the ctx[1] table (+0x90, count at +0x8c). The count is
 * re-read from memory on every iteration, which is what the ROM does. */
void func_ov253_020d3388(int self) {
    int *ctx = *(int **)(self + 4);
    int i;
    int off;
    *(int *)(ctx[0] + 0x3d0) = 0;
    if (*(int *)(ctx[1] + 0x8c) <= 0) {
        return;
    }
    i = 0;
    off = 0;
    do {
        *(int *)(*(int *)(ctx[1] + 0x90) + off) = 0;
        i = i + 1;
        off = off + 0x38;
    } while (i < *(int *)(ctx[1] + 0x8c));
}
