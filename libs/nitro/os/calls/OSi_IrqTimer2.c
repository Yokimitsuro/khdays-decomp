/* See OSi_IrqDma0. */
extern void *OSi_IrqCallback();

void *OSi_IrqTimer2() {
    return OSi_IrqCallback(6);
}
