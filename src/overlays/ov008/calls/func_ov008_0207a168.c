/* func_ov008_0207a168 -- react to the boot scene's poll result, ov006.
 * Polls whether the launched sub-scene is still alive (Game_PollSceneAlive/func_02001030):
 * result 1 latches the title object's "advance" flag (base+0x49c); result 10 latches the
 * "abort" flag byte (base+0x4f0). Either transition returns the next state fn
 * (func_ov008_0207aac8); anything else stays (0). */
extern int  func_02001030(void);
extern int  data_ov008_02090f24;
extern void func_ov008_0207aac8(void);

void *func_ov008_0207a168(void) {
    void *result = 0;
    int r = func_02001030();
    switch (r) {
    case 1:
        *(int *)(data_ov008_02090f24 + 0x49c) = 1;
        result = (void *)func_ov008_0207aac8;
        break;
    case 10:
        *(char *)(data_ov008_02090f24 + 0x4f0) = 1;
        result = (void *)func_ov008_0207aac8;
        break;
    }
    return result;
}
