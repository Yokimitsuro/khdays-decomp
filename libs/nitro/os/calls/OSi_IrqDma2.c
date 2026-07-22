/* See OSi_IrqDma0. */
extern void *OSi_IrqCallback();

void *OSi_IrqDma2() {
    return OSi_IrqCallback(2);
}
