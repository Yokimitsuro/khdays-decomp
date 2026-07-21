extern int NNSi_FndFreeFromDefaultHeap(int block);
/* Free the heap block at obj+0x2c and null it, if allocated. */
void func_ov015_0207fcd8(int obj) {
    if (*(int *)(obj + 0x2c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(obj + 0x2c));
        *(int *)(obj + 0x2c) = 0;
    }
}
