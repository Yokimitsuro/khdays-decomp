/* func_ov245_020cce48 -- animation gate for kinds 3 and 5: returns 1 while the +0x384 item is
 * still busy (+0xad); once it is idle, kind 3 records 9 (from sub-state 9) or 4 at +0x4d8 and
 * plays that pose (020c9264 with flag 1), kind 5 clears +0x4d8 to -1; returns 0. */
extern void func_ov107_020c9264(int actor, int pose, int flag);

int func_ov245_020cce48(int self) {
    if (*(signed char *)(self + 0x4d8) == 3 || *(signed char *)(self + 0x4d8) == 5) {
        if (*(unsigned char *)(*(int *)(self + 0x384) + 0xad) != 0) {
            return 1;
        }
        if (*(signed char *)(self + 0x4d8) == 3) {
            *(signed char *)(self + 0x4d8) = *(signed char *)(self + 0x1c6) == 9 ? 9 : 4;
            func_ov107_020c9264(self, *(signed char *)(self + 0x4d8), 1);
        } else {
            *(signed char *)(self + 0x4d8) = -1;
        }
    }
    return 0;
}
