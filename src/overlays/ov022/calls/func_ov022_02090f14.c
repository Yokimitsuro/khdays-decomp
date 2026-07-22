/* Close every loaded stream (0x1c8 bytes apart) and free the block. The count at
 * +0x19 is re-read on every iteration because closing can shorten the list.
 *
 * The entry guard is `i < count`, not `count > 0`. Comparing the zeroed index
 * against the count is what gives the ROM's signed `ble`; written as a direct
 * test on the unsigned count, mwcc knows it cannot be negative and emits `beq`. */
extern void func_ov022_02090cac(int stream);
extern void NNSi_FndFreeFromDefaultHeap(int block);

void func_ov022_02090f14(int self) {
    int i = 0;

    if (i < *(unsigned char *)(self + 0x19)) {
        int e = i;

        do {
            func_ov022_02090cac(*(int *)(self + 0xc) + e);
            i++;
            e += 0x1c8;
        } while (i < *(unsigned char *)(self + 0x19));
    }

    NNSi_FndFreeFromDefaultHeap(*(int *)(self + 0xc));
}
