extern void func_ov105_020be49c(int state);
extern int func_ov105_020bf4cc(unsigned int id);
extern char data_ov105_020c04c0[];
/* Enter state 1 and resolve the queued id (+10) into the active slot (+2), returning it. */
unsigned short func_ov105_020bf4a0(void) {
    func_ov105_020be49c(1);
    *(short *)(data_ov105_020c04c0 + 2) =
        func_ov105_020bf4cc(*(unsigned short *)(data_ov105_020c04c0 + 10));
    return *(unsigned short *)(data_ov105_020c04c0 + 2);
}
