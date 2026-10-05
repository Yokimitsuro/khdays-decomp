extern void RigWork_Update(int a, int b, void *guard, void *buf);
extern int NNS_G3dRS;

/* Reentrancy guard: on the outermost call use a local 392-byte scratch buffer
   (published in the global guard); nested calls reuse the already-published one. */
void DispatchWithReentrantScratch(int param_1, int param_2, int param_3, int param_4) {
    char buffer[392];
    if (NNS_G3dRS == 0) {
        NNS_G3dRS = (int)buffer;
        RigWork_Update(param_1, param_2, &NNS_G3dRS, buffer);
        NNS_G3dRS = 0;
        return;
    }
    RigWork_Update(param_1, param_2, &NNS_G3dRS, (void *)NNS_G3dRS);
}
