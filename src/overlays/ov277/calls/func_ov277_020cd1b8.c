/* Slot event relay: after the base 020c8000 handling, event 3 forwards (0, arg) and event 4
 * forwards (1, arg) to the +0x1d8 hook of each of the two +0x400 parts. */
extern void func_ov107_020c8000(int self, int event, int arg);

void func_ov277_020cd1b8(int self, int event, int arg) {
    int i;
    func_ov107_020c8000(self, event, arg);
    if (event == 3) {
        int mode = 0;
        for (i = 0; i < 2; i++) {
            int part = (*(int **)(self + 0x400))[i];
            void (*hook)(int, int, int) = *(void (**)(int, int, int))(part + 0x1d8);
            if (hook != 0) hook(part, mode, arg);
        }
    } else if (event == 4) {
        int mode = 1;
        for (i = 0; i < 2; i++) {
            int part = (*(int **)(self + 0x400))[i];
            void (*hook)(int, int, int) = *(void (**)(int, int, int))(part + 0x1d8);
            if (hook != 0) hook(part, mode, arg);
        }
    }
}
