/* Whether every game flag of the set named by `id` is set: 0x25a covers flags 0x1444..0x144f,
 * 0x25b 0x1450..0x1460 and 0x25c 0x1461..0x1464; any other id (or any clear flag) gives 0. */
extern int func_02023588(int flag);   /* GameState_IsFlagSet */

int func_ov069_020b82a4(int id)
{
    int last;
    int flag;

    switch (id) {
    case 0x25a:
        flag = 0x1444;
        last = flag + 0xb;
        break;
    case 0x25b:
        flag = 0x1450;
        last = flag + 0x10;
        break;
    case 0x25c:
        flag = 0x1461;
        last = flag + 3;
        break;
    default:
        return 0;
    }
    for (; flag <= last; flag++) {
        if (func_02023588(flag) == 0) {
            return 0;
        }
    }
    return 1;
}
