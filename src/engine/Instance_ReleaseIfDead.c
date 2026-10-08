/* When the instance is marked dead (-2), releases it (if still live); returns whether it was dead.
 */

extern void VeneerTo_Obj_Destroy(int *arg);

int Instance_ReleaseIfDead(int *p) {
    int result = 0;
    if (p[5] == -2) {
        if (p[0] & 1) VeneerTo_Obj_Destroy(p);
        result = 1;
    }
    return result;
}
