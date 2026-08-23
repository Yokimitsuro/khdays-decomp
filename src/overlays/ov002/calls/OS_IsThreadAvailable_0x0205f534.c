/* Global getter: `ldr r0,[pc,#4] ; ldr r0,[r0] ; bx lr` == `return data_ov002_0207eb24;`
 * The panel scene's request block, handed to whoever wants to fill it in.
 *
 * The name is misattributed -- the SDK identifier matched a SHAPE, not a function. Trust the bytes. */
extern int data_ov002_0207eb24;

int OS_IsThreadAvailable_0x0205f534(void) {
    return data_ov002_0207eb24;
}
