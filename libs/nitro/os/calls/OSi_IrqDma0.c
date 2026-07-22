/* One of eight identical `ldr ip,=OSi_IrqCallback ; mov r0,#N ; bx ip` dispatch veneers. */
extern void *OSi_IrqCallback();

void *OSi_IrqDma0() {
    return OSi_IrqCallback(0);
}
