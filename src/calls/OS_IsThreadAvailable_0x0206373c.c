/* Global getter: `ldr r0,[pc,#4] ; ldr r0,[r0] ; bx lr` == `return data_ov002_0207f62c;`
 * One of 12 byte-identical getters differing only in the pooled global.
 *
 * The name is misattributed -- the SDK identifier matched a SHAPE, not a function. Trust the bytes. */
extern int data_ov002_0207f62c;

int OS_IsThreadAvailable_0x0206373c(void) {
    return data_ov002_0207f62c;
}
