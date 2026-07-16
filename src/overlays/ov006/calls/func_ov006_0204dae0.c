/* func_ov006_0204dae0 -- Mission Mode: is the pending scene transition finished?
 * The scene object at data_ov006_020565e4 carries a transition request at +0x28 and its
 * remaining-frames counter at +0x2c. Returns true only when a transition is pending and its
 * counter has run down to zero. */
extern int data_ov006_020565e4;

int func_ov006_0204dae0(void) {
    int *obj = *(int **)&data_ov006_020565e4;
    if (obj[0xa] != 0) {
        return obj[0xb] == 0;
    }
    return 0;
}
