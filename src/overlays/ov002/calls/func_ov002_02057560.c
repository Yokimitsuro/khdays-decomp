/* Resolve the request unless it is kind 0x2a, and only while
 * func_ov002_02062f28 reports the subsystem free. Reports 0 otherwise. */
extern int func_02020a9c(int req);
extern int func_ov002_02062f28(void);
extern int func_ov002_02054d4c(int req);

int func_ov002_02057560(int req) {
    int result = 0;

    if (func_02020a9c(req) == 0x2a) {
        return 0;
    }
    if (func_ov002_02062f28() == 0) {
        result = func_ov002_02054d4c(req);
    }
    return result;
}
