/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap. */
extern void *Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap();

void *func_ov024_02085104(int arg0) {
    return Ov024_VeneerTo_NNSi_FndFreeFromDefaultHeap(arg0);
}
