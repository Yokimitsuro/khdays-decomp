/* func_ov000_02052fdc -- flush dirty logo sub-layers to VRAM, ov000. For each of the 3
 * layers whose dirty bit (*data_ov000_0205ac24 +0x4afa) is set, queues its 0x800-byte
 * upload (GFXi_EnqueueCommand, dest from data_ov000_0205a6c4), then clears the dirty mask. */
extern void GFXi_EnqueueCommand(int dest, int a, int src, int size);
extern int  data_ov000_0205a6c4[];
extern char *data_ov000_0205ac24;
void func_ov000_02052fdc(void) {
    int i;
    for (i = 0; i < 3; i++) {
        char *base = data_ov000_0205ac24;
        if (*(unsigned char *)(base + 0x4afa) & (1 << i)) {
            GFXi_EnqueueCommand(data_ov000_0205a6c4[i], 0, ((int *)(base + 0x4aec))[i], 0x800);
        }
    }
    *(unsigned char *)(data_ov000_0205ac24 + 0x4afa) = 0;
}
