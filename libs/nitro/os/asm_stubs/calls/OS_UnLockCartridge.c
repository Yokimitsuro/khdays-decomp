/* NitroSDK original assembly: the legacy spelling of the cartridge unlock entry point,
 * forwarding the processor id unchanged to the modern implementation.
 *
 * Not a decompilation. No C reaches these bytes: the toolchain's interworking tail jump
 * is fixed at ip in ARM and r3 in Thumb across every compiler build, option, pragma,
 * declspec and source shape, and across every linker build for both veneer kinds. The r1
 * idiom is the SDK's hand-written signature, at four sites over the two processors, two
 * of which load lr from a literal pool and so are hand-written by construction.
 */

extern void OS_TryLockCartridge(int processor);

asm void OS_UnLockCartridge(int processor)
{
    ldr r1, =OS_TryLockCartridge
    bx  r1
}
