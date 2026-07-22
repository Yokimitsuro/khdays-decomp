/* Release the panel's pending entry: clear the handle's +4 and +0 around the
 * teardown. Does nothing when no context is installed -- but the handle is
 * fetched BEFORE the guard, which is why func_ov002_020636ac runs either way. */
extern int func_ov002_020636ac(void);
extern void func_ov002_02064328(void);

extern int data_ov002_0207f634;

void func_ov002_020646e0(void) {
    int ctx = data_ov002_0207f634;
    int *handle = (int *)func_ov002_020636ac();

    if (ctx == 0) {
        return;
    }

    handle[1] = 0;
    func_ov002_02064328();
    handle[0] = 0;
}
