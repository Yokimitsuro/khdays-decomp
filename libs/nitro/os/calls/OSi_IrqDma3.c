/* See OSi_IrqDma0. */
extern void *OSi_IrqCallback();

void *OSi_IrqDma3() {
    return OSi_IrqCallback(3);
}
