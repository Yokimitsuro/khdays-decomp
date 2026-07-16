/* func_ov024_02084650 -- MobiClip: open stream slot `idx` and give it a fresh state block.
 * The FSFile for each slot lives inline at the head of data_ov024_02093a48, stride 0x48
 * (sizeof FSFile); the slot's 0x58-byte state block is heap-allocated and its pointer parked in
 * data_ov024_02093a3c[idx]. A slot that fails to open gets a NULL pointer rather than a block,
 * and either way the caller is handed whatever ended up in the slot.
 * Note this pins the head of the work block: three slots at 0x48 each = 0xd8, which is exactly
 * where the ITCM save area starts (see func_ov024_0208455c). */
extern int func_02024e6c(int path);
extern int FS_OpenFile(void *file, int name);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int size, int align);
extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);
extern char data_ov024_02093a48[];
extern int data_ov024_02093a3c[];

int func_ov024_02084650(int idx, int path) {
    if (FS_OpenFile(data_ov024_02093a48 + idx * 0x48, func_02024e6c(path)) == 0) {
        data_ov024_02093a3c[idx] = 0;
    } else {
        data_ov024_02093a3c[idx] = (int)NNS_FndAllocFromDefaultExpHeapEx(0x58, 0x20);
        MI_CpuFill8((void *)data_ov024_02093a3c[idx], 0, 0x58);
    }
    return data_ov024_02093a3c[idx];
}
