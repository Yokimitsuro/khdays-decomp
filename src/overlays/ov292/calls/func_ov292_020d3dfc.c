/* Walks the owner's point list up to the stored index and leaves that point in
 * the caller's slot at +0x1c, then clears the progress word at +0x28. The list
 * is the one the reloader fills; the walk stops early when the list is shorter
 * than the index. */
struct Vec3 { int x, y, z; };

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

void func_ov292_020d3dfc(char *state)
{
    struct Vec3 *point;
    int i;

    point = func_01fffd70(*(char **)state + 0x394);
    i = 0;
    while (point != 0) {
        *(struct Vec3 *)(state + 0x1c) = *point;
        if (i >= *(int *)(state + 0x34)) {
            break;
        }
        point = func_01fffd8c(*(char **)state + 0x394);
        i++;
    }
    *(int *)(state + 0x28) = 0;
}
