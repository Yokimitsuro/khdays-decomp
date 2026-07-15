/* func_ov000_02053054 -- map logo element id (0x18/0x19/0x1a) to a 0/1/2 slot
 * index, ov000. Returns -1 for anything else. */
int func_ov000_02053054(int id) {
    int slot = -1;
    switch (id) {
    case 0x18: slot = 0; break;
    case 0x19: slot = 1; break;
    case 0x1a: slot = 2; break;
    }
    return slot;
}
