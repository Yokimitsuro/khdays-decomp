/* func_ov023_02089240 -- reset the four-word history block that ends at +0x15d8 of the object:
 * clear the newest two entries and shift the remaining pair down.
 * The base offset is held in a LOCAL and each access recomputed from it (`off - 0x10`, `off -
 * 0x14`, `off - 0x18`) -- that is what produces the ROM's `adds r0,r1,#0 ; subs r0,#N` pairs
 * instead of four separate pool constants. */
extern void func_ov023_02088da0(int obj, int a);

void func_ov023_02089240(int obj) {
    int off = 0x15d8;
    func_ov023_02088da0(obj, 0);
    *(int *)(obj + off) = 0;
    *(int *)(obj + off - 0x10) = 0;
    *(int *)(obj + off - 0x14) = *(int *)(obj + off - 0x10);
    *(int *)(obj + off - 0x18) = *(int *)(obj + off - 0x14);
}
