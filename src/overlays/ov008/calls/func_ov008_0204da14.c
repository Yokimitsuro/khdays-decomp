/* func_ov008_0204da14 -- release the loaded menu UI container, ov008.
 * If the UI container is loaded (heap+0x608), detaches its root cell from the object manager
 * (func_02032428 on heap+0x60c), frees the container (func_02024fd4), and clears both the
 * container slot (heap+0x608) and the root-cell handle (heap+0x5044). */
extern void  func_02032428(int *mgr);
extern void  func_02024fd4(void *p);
extern char *data_ov008_02090f00;

void func_ov008_0204da14(void) {
    if (*(int *)(data_ov008_02090f00 + 0x608) == 0) {
        return;
    }
    func_02032428((int *)(data_ov008_02090f00 + 0x60c));
    func_02024fd4(*(void **)(data_ov008_02090f00 + 0x608));
    *(int *)(data_ov008_02090f00 + 0x608) = 0;
    *(int *)(data_ov008_02090f00 + 0x5044) = 0;
}
