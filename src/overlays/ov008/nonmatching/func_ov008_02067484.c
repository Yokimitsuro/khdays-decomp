/* NONMATCHING: correct (-4B); switch-vs-if tie. The ROM emits a compare-chain switch with an
 * explicit b-to-default (every case breaks to commit); an if/else-if folds the no-match fall-
 * through, and a switch() makes mwcc pick a jump table instead. Mission-menu action confirm. */
/* func_ov008_02067484 -- confirm the selected mission-menu action, ov008.
 * When the active record is idle (rec+0x30 == 0), maps its pending action code (rec+0xa4) to a
 * transition: 2->1, 5->4, 7->0, via func_ov008_02063790; then commits the input latch. */
extern int  func_ov008_02050cd4(void);
extern void func_ov008_02063790(int rec, int mode);
extern void func_02033b78(int a, int b);

void func_ov008_02067484(int p1, int p2, int p3, int p4) {
    int rec = func_ov008_02050cd4();
    int action;
    if (*(int *)(rec + 0x30) != 0) {
        return;
    }
    action = *(int *)(rec + 0xa4);
    if (action == 2) {
        func_ov008_02063790(rec, 1);
    } else if (action == 5) {
        func_ov008_02063790(rec, 4);
    } else if (action == 7) {
        func_ov008_02063790(rec, 0);
    }
    func_02033b78(0, 3);
}
