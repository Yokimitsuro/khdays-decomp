/* func_ov023_0208402c -- rebuild the ov023 scene's sub-object at +0x87580.
 * Any existing one is torn down first, then a fresh instance of the class at
 * data_ov023_0208a748 is created and stored back into the same slot. */
extern void WM_EndKeySharing_0x02023ad0(void);
extern int func_02023930(void *classDesc, int arg);
extern int data_ov023_0208a784;
extern char data_ov023_0208a748[];

void func_ov023_0208402c(void) {
    if (*(int *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x87580) != 0) {
        WM_EndKeySharing_0x02023ad0();
    }
    *(int *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x87580) =
        func_02023930(data_ov023_0208a748, 0);
}
