extern void func_ov005_0204ecf0(int table);
extern char data_ov005_0205b814[];
extern char data_ov005_0205b838[];
/* Register both animation tables with the sequencer. */
void func_ov005_02058390(void) {
    func_ov005_0204ecf0((int)data_ov005_0205b814);
    func_ov005_0204ecf0((int)data_ov005_0205b838);
}
