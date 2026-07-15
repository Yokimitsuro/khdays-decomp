/* func_ov006_02054ab0 -- flush the dirty title cell buffers to VRAM, ov006.
 * For each of the 8 cell slots whose dirty bit is set in the object's mask byte (obj+0x9570),
 * enqueues a 0x600-byte GFX DMA from the slot's cell buffer (obj+0x94cc + slot*4) to the
 * slot's VRAM destination (data_ov006_020562b0[slot]). Clears the whole dirty mask afterward. */
extern void GFXi_EnqueueCommand(void *dst, int a, void *src, int size);
extern void *data_ov006_020562b0[];
extern int *data_ov006_02056664;

void func_ov006_02054ab0(void) {
    unsigned int i = 0;
    do {
        if (*(unsigned char *)((char *)data_ov006_02056664 + 0x9570) & 1 << i) {
            GFXi_EnqueueCommand(data_ov006_020562b0[i], 0,
                                ((void **)((char *)data_ov006_02056664 + 0x94cc))[i], 0x600);
        }
        i++;
    } while ((int)i < 8);
    *(unsigned char *)((char *)data_ov006_02056664 + 0x9570) = 0;
}
