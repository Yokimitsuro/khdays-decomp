/* func_ov023_02082c24 -- close the ov023 prompt: clear bit 0 and set bit 3 of the status halfword
 * the global at data_ov023_0208a780 points at, then TAIL-CALL func_ov023_02083a80 with the fixed
 * string at data_0204bdbc. The tail call is why the ROM ends in `bx ip` rather than `bl`: this
 * function is ARM and the callee is THUMB, so mwcc's interworking tail call loads the target from
 * the pool. Writing the call as the last statement of a void function is enough. */
extern void func_ov023_02083a80(const char *fmt);
extern int data_ov023_0208a780;
extern char data_0204bdbc[];

void func_ov023_02082c24(void) {
    unsigned short *p = *(unsigned short **)&data_ov023_0208a780;
    *p &= ~1;
    *p |= 8;
    func_ov023_02083a80(data_0204bdbc);
}
