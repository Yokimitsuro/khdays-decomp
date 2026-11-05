/* One-shot filesystem init guarded by the flag at data_02046318. */
extern void FSi_InitRom(int priority);
extern int data_02046318[];

void FS_Init(int priority) {
    if (data_02046318[0] == 0) {
        data_02046318[0] = 1;
        FSi_InitRom(priority);
    }
}
