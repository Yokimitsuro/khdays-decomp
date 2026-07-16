/* func_ov008_02084324 -- re-register the mission grid's 14 cell sprites, ov008.
 * Through the shared object manager (base+0xbfb0), re-adds the two header cells (base+0xc57c,
 * base+0xc580) and the 12 mission-slot cells (base+0xc584 + i*4) via func_02032450. */
extern void func_02032450(int *mgr, int obj);
extern int  data_ov008_02090fac;

void func_ov008_02084324(void) {
    int base = data_ov008_02090fac;
    int *cells = (int *)(base + 0xc57c);
    int *mgr = *(int **)(base + 0xbfb0);
    int i;
    func_02032450(mgr, cells[0]);
    func_02032450(mgr, cells[1]);
    i = 0;
    do {
        func_02032450(mgr, cells[i + 2]);
        i++;
    } while (i < 0xc);
}
