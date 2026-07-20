typedef void (*SceneCallback)(void);

extern int func_02001030(void);
extern void func_ov105_020bf928(void);
extern void func_ov006_0204ecdc(void);

SceneCallback func_ov006_0204ed64(void) {
    SceneCallback callback = 0;

    switch (func_02001030()) {
    case 0:
    case 3:
        break;
    case 1:
        callback = func_ov006_0204ecdc;
        break;
    default:
        func_ov105_020bf928();
        break;
    }

    return callback;
}
