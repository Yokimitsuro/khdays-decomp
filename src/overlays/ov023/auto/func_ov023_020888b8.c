/* Hands the request over to the worker: stamps opcode 0x29 with its argument, raises the
 * pending bit and bumps the worker's request counter, then links the worker in. */
void func_ov023_020888b8(int *slot, char *worker, int arg) {
    *(int *)((char *)slot + 0x1a28) = 0x29;
    *(int *)((char *)slot + 0x1a28 + 0x10) = arg;
    *(int *)(worker + 0x1a28) |= 0x800;
    *(int *)(worker + 0x1a28 + 0x14) = *(int *)(worker + 0x1a28 + 0x14) + 1;
    *(char **)slot = worker;
}
