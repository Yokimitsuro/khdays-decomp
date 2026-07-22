/* Reset the four 0x30-byte decoder slots at the root heap and clear the active
 * pointer. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02050cf4(void *slot);

typedef struct {
    char bytes[0x30];
} Ov022DecoderSlot;

extern void *data_ov022_020b2e74;

void func_ov022_0208694c(void) {
    Ov022DecoderSlot *slots = (Ov022DecoderSlot *)NNSi_FndGetCurrentRootHeap();
    int i;

    for (i = 0; i < 4; i++) {
        func_ov002_02050cf4(&slots[i]);
    }

    data_ov022_020b2e74 = 0;
}
