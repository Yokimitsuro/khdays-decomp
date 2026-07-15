/* func_ov026_0208e740 -- fetch the current selection's value, ov026. Resets input
 * (func_02030788), queries the active node (func_020315c0); returns node[1] or -1. */
extern void func_02030788(void);
extern int *func_020315c0(void);
int func_ov026_0208e740(void) {
    int *node;
    func_02030788();
    node = func_020315c0();
    if (node == 0) {
        return -1;
    }
    return node[1];
}
