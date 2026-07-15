/* func_ov006_0204e300 -- react to the boot scene's poll result, ov006.
 * Polls whether the launched sub-scene is still alive (Game_PollSceneAlive/func_02001030):
 * result 1 latches the title object's "advance" flag (base+0x49c); result 10 latches the
 * "abort" flag byte (base+0x4f0). Either transition returns the next state fn
 * (func_ov006_0204ecdc); anything else stays (0). */
extern int  func_02001030(void);
extern int  data_ov006_020565e4;
extern void func_ov006_0204ecdc(void);

void *func_ov006_0204e300(void) {
    void *result = 0;
    int r = func_02001030();
    switch (r) {
    case 1:
        *(int *)(data_ov006_020565e4 + 0x49c) = 1;
        result = (void *)func_ov006_0204ecdc;
        break;
    case 10:
        *(char *)(data_ov006_020565e4 + 0x4f0) = 1;
        result = (void *)func_ov006_0204ecdc;
        break;
    }
    return result;
}
