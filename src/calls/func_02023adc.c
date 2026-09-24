/*
 * Obj_UpdateAll - run one frame of the object registry (data_0204c058, head at [3]). Each object
 * is published as the current one ([1]) while it runs. An update callback of -2 marks an object
 * to destroy (Obj_Destroy, unless it is protected by flag 1), -1 an idle one; any other callback
 * runs inside the object's allocator arena (obj[7]) when the registry is not paused or the object
 * runs while paused (flag 4), and a non-zero return replaces the callback. The walk continues from
 * the current object's successor ([3]). Afterwards the current object is cleared and, unless
 * paused, the frame counter ([2]) advances.
 */

extern int  func_0202362c(int arena);      /* enter/leave scoped allocator arena */
extern int  func_02023a4c(int *obj);        /* Obj_Destroy: returns the successor */
extern int  data_0204c058[];

void func_02023adc(int paused)
{
    int *obj;
    int next;

    data_0204c058[1] = data_0204c058[3];
    obj = (int *)data_0204c058[1];
    while (obj != 0) {
        switch (obj[5]) {
        case -2:
            next = obj[3];
            if (!(obj[0] & 1)) {
                next = func_02023a4c(obj);
            }
            break;
        case -1:
            next = obj[3];
            break;
        default:
            if (paused == 0 || (obj[0] & 4)) {
                int arena = func_0202362c(obj[7]);
                int cb = ((int (*)(void))((int *)data_0204c058[1])[5])();

                func_0202362c(arena);
                if (cb != 0) {
                    ((int *)data_0204c058[1])[5] = cb;
                }
            }
            next = ((int *)data_0204c058[1])[3];
            break;
        }
        data_0204c058[1] = next;
        obj = (int *)next;
    }
    data_0204c058[1] = 0;
    if (paused == 0) {
        data_0204c058[2]++;
    }
}
