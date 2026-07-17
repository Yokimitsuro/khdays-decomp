/* Global getter: `ldr r0,[pc,#4] ; ldr r0,[r0] ; bx lr` == `return data_ov009_020563ec;`
 * One of 12 byte-identical getters differing only in the pooled global.
 *
 * The name is misattributed -- the SDK identifier matched a SHAPE, not a function. Trust the bytes. */
extern int data_ov009_020563ec;

int OS_IsThreadAvailable_0x0204ee00(void) {
    return data_ov009_020563ec;
}
