/* Global getter: `ldr r0,[pc,#4] ; ldr r0,[r0] ; bx lr` == `return data_ov008_02090f0c;`
 * One of 12 byte-identical getters differing only in the pooled global.
 *
 * The name is misattributed -- the SDK identifier matched a SHAPE, not a function. Trust the bytes. */
extern int data_ov008_02090f0c;

int OS_IsThreadAvailable_0x02051aa0(void) {
    return data_ov008_02090f0c;
}
