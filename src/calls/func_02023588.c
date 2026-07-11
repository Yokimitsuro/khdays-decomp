#pragma thumb on
extern int func_02025694(int bits, int index);
extern int data_0204be18;
/* Return whether bit `arg` is set in the bitset at *(data_0204be18)+0x10. */
int func_02023588(unsigned int arg) {
    if (func_02025694(data_0204be18 + 0x10, arg) != 0) {
        return 1;
    }
    return 0;
}
