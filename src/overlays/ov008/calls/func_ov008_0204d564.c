/* func_ov008_0204d564 -- menu per-frame input/state update, ov008. Picks the menu's
 * transition mode into heap[+0x2c] from the input sources (a queued transition
 * func_ov008_0207baf8, a pending sub-scene func_ov008_0204ed3c, or the shoulder scroll
 * func_02030640/func_020306b4) and mirrors the region flag into heap[+0x2a]. Finally, when
 * both stick axes are centered (func_02030640/func_02030670), commits via func_ov008_0204ec34. */
extern char *data_ov008_02090f00;
extern int   data_0204c240;
extern int   func_ov008_0207baf8(void);
extern int   func_ov008_0204ed3c(void);
extern int   func_ov008_0204cac0(void);
extern int   func_02030640(void);
extern int   func_020306b4(void);
extern int   func_02030670(void);
extern void  func_ov008_0204ec34(int);
void func_ov008_0204d564(void) {
    if (data_ov008_02090f00 == 0) {
        return;
    }
    if (func_ov008_0207baf8() != 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = 1;
        *(unsigned short *)(data_ov008_02090f00 + 0x2a) = *(unsigned short *)((char *)&data_0204c240 + 2);
        return;
    }
    if (func_ov008_0204ed3c() != 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = func_ov008_0204cac0();
        *(unsigned short *)(data_ov008_02090f00 + 0x2a) = *(unsigned short *)((char *)&data_0204c240 + 2);
    } else if (func_02030640() == 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = 0;
    } else if (func_020306b4() != 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = 0;
    }
    if (func_02030640() == 0) {
        return;
    }
    if (func_02030670() == 0) {
        return;
    }
    func_ov008_0204ec34(0);
}
