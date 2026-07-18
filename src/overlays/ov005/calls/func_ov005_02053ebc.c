/* func_ov005_02053ebc -- map logo element id (0x9/0xa/0xb) to a 0/1/2 slot
 * index, ov000. Returns -1 for anything else. */
int func_ov005_02053ebc(int id) {
    int slot = -1;
    switch (id) {
    case 0x9: slot = 0; break;
    case 0xa: slot = 1; break;
    case 0xb: slot = 2; break;
    }
    return slot;
}
