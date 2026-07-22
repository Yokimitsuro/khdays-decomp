/* Push the current scroll span to the view, but only when it changed: the span
 * is the head position minus the tail, and both it and the head are cached at
 * +0x20/+0x24. A zero head means there is nothing to show. */
extern int func_ov002_0206e33c(void);
extern int func_ov002_0206e2ec(void);
extern void func_ov002_02063b18(unsigned short head, unsigned short span);

extern char *data_ov002_0207f634;

void func_ov002_02064358(void) {
    char *ctx = data_ov002_0207f634;
    int head = func_ov002_0206e33c();
    int span = head - func_ov002_0206e2ec();

    if (head == 0) {
        return;
    }
    if (*(int *)(ctx + 0x20) == head && *(int *)(ctx + 0x24) == span) {
        return;
    }

    func_ov002_02063b18((unsigned short)head, (unsigned short)span);
}
