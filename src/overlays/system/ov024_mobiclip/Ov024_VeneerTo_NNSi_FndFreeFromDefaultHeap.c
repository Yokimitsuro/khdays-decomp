/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to NNSi_FndFreeFromDefaultHeap. */
extern void *NNSi_FndFreeFromDefaultHeap();

void *Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(void *user_ptr) {
    return NNSi_FndFreeFromDefaultHeap(user_ptr);
}
