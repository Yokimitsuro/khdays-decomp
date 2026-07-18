/*
 * func_ov008_0205a030 -- x3 (ov002/...). Advance or commit a widget's scroll, then clear the dirty
 * flag. Skip entirely unless *(s8)(param1+1) is set. Query the length n = 0202aef8(param1+4, 0): if the
 * target row param4 is still above it and the "no-wrap" bit (4) is clear, nudge the view 4 steps
 * (01fff774(param1+4, (u16)i, param4) for i in 0..3); otherwise, if *(param2+4) is idle, snap to it
 * with 0202a818(param1+4, param3). Always clear *(param2+4) = 0.
 */
extern int func_0202aef8(unsigned short *view, int b);
extern void func_01fff774(unsigned short *view, int step, int row);
extern void func_0202a818(unsigned short *view, int target);

void func_ov008_0205a030(int param1, int param2, int param3, int param4) {
    if (*(signed char *)(param1 + 1) != 0) {
        int n = func_0202aef8((unsigned short *)(param1 + 4), 0);
        if (param4 < n && (*(unsigned short *)(param1 + 4) & 4) == 0) {
            int i;
            for (i = 0; i <= 3; i++) {
                func_01fff774((unsigned short *)(param1 + 4), i & 0xffff, param4);
            }
        } else if (*(int *)(param2 + 4) == 0) {
            func_0202a818((unsigned short *)(param1 + 4), param3);
        }
        *(int *)(param2 + 4) = 0;
    }
}
