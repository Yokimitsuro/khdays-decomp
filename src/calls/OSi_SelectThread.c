/* OSi_SelectThread: walks the thread list from the scheduler root (+0x2c) to the first thread
 * whose state (+0x64) is not 1 (runnable), following the link at +0x68. */

extern int data_0204430c;

int OSi_SelectThread(void) {
    int t = *(int *)((int)&data_0204430c + 0x2c);

    while (t != 0 && *(int *)(t + 0x64) != 1) {
        t = *(int *)(t + 0x68);
    }
    return t;
}
