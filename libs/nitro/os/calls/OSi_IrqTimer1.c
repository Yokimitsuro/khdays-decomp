/* See OSi_IrqDma0. */
extern void *OSi_IrqCallback();

void *OSi_IrqTimer1() {
    return OSi_IrqCallback(5);
}
