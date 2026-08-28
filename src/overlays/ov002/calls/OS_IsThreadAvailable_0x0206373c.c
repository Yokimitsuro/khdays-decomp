/* Global getter: `ldr r0,[pc,#4] ; ldr r0,[r0] ; bx lr` == `return the first of
 * the two caption scene slots at data_ov002_0207f62c;`
 *
 * Four matched caption routines fetch the scene here, treat a null one as
 * nothing to draw on, and pass it as the scene of every plot call.  Ghidra
 * models the pair as Ov002_CaptionSceneSlots, an Ov002CaptionScene *[2]; the
 * delink names the same address data_ov002_0207f62c.
 *
 * The name is misattributed -- the SDK identifier matched a SHAPE, not a
 * function, the same way the sibling getter at 0205f534 did. Trust the bytes. */
extern int data_ov002_0207f62c;

int OS_IsThreadAvailable_0x0206373c(void) {
    return data_ov002_0207f62c;
}
