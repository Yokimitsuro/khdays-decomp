/* Unlinks and clears the whole wave-archive chain under the sound mutex. */
extern void SNDi_UnlockMutex_0x020084f4(void);
extern void SNDi_UnlockMutex_0x02008508(void);
extern void DC_StoreRange(void *p, unsigned int len);

void SND_DestroyWaveArc(int **owner) {
    int *node;
    int zero;
    int len;
    int *next;
    SNDi_UnlockMutex_0x020084f4();
    node = (int *)owner[6];
    if (node != 0) {
        zero = 0;
        len = 8;
        do {
            next = (int *)node[1];
            node[0] = zero;
            node[1] = zero;
            DC_StoreRange(node, len);
            node = next;
        } while (next != 0);
    }
    SNDi_UnlockMutex_0x02008508();
}
