/* Global getter: `ldr r0,[pc,#4] ; ldr r0,[r0] ; bx lr` == `return data_ov002_0207eb24;`
 * One of 12 byte-identical getters differing only in the pooled global.
 *
 * The name is misattributed -- the SDK identifier matched a SHAPE, not a function. Trust the bytes. */
extern int data_ov002_0207eb24;

int OS_IsThreadAvailable_0x0205f534(void) {
    return data_ov002_0207eb24;
}
