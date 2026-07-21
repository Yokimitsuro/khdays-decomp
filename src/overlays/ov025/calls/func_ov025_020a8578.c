extern int func_ov025_02084a8c(void);
extern void func_ov025_02088b1c(int block, unsigned short *out);
/* Query the current block's descriptor; unless its kind word reads 1, clear the caller's slot. */
void func_ov025_020a8578(int obj) {
    unsigned short desc[4];
    func_ov025_02088b1c(func_ov025_02084a8c(), desc);
    if (desc[2] != 1) {
        *(int *)(obj + 0x34) = 0;
    }
}
