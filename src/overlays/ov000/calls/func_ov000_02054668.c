/* func_ov000_02054668 -- flush dirty logo BG layers to VRAM, ov000. For each of the 4
 * layers whose dirty bit (*data_ov000_0205ac28 +0x10) is set, queues its 0x800-byte
 * upload (GFXi_EnqueueCommand, dest from data_ov000_0205a838), then clears the dirty mask. */
extern void GFXi_EnqueueCommand(int dest, int a, int src, int size);
extern int  data_ov000_0205a838[];
extern int *data_ov000_0205ac28;
void func_ov000_02054668(void) {
    int i;
    for (i = 0; i < 4; i++) {
        int *base = data_ov000_0205ac28;
        if (*(unsigned char *)((char *)base + 0x10) & (1 << i)) {
            GFXi_EnqueueCommand(data_ov000_0205a838[i], 0, base[i], 0x800);
        }
    }
    *(unsigned char *)((char *)data_ov000_0205ac28 + 0x10) = 0;
}
