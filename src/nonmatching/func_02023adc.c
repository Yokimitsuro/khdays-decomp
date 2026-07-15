/* Per-frame object dispatcher (main frame loop calls func_02023adc(0)). Walks the
 * InstantiateClass object list (manager @ data_0204c058: [1]=current, [2]=frame counter,
 * [3]=list head) and for each live object calls its state fn at obj+0x14 (obj[5]); a
 * non-zero return replaces the state (next state). Sentinels: obj[5]==-1 dead passthrough,
 * ==-2 spawning (func_02023a4c unless flag bit0). `mode` non-zero ticks only flag-bit2 objects. */
extern int func_02023a4c(int *obj);
extern int func_0202362c(int arg);
extern char data_0204c058;

void func_02023adc(int mode) {
    int dead = -1, spawning = -2;
    int *mgr = (int *)&data_0204c058;
    int *obj;
    int *next;
    int token, ret;

    obj = (int *)mgr[3];
    mgr[1] = (int)obj;
    while (obj != 0) {
        if (obj[5] == spawning) {
            next = (int *)obj[3];
            if ((obj[0] & 1) == 0) {
                next = (int *)func_02023a4c(obj);
            }
        } else if (obj[5] == dead) {
            next = (int *)obj[3];
        } else {
            if (mode == 0 || (obj[0] & 4) != 0) {
                token = func_0202362c(obj[7]);
                ret = ((int (*)(void))((int *)mgr[1])[5])();
                func_0202362c(token);
                if (ret != 0) {
                    ((int *)mgr[1])[5] = ret;
                }
            }
            next = (int *)((int *)mgr[1])[3];
        }
        mgr[1] = (int)next;
        obj = next;
    }
    mgr[1] = 0;
    if (mode == 0) {
        mgr[2] += 1;
    }
}
