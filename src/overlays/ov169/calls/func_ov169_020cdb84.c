/* Acquire a target; on failure mark the owner state 2 and dispatch with no callback.
 * On success re-tag the owner, clear the two progress fields and re-issue the move
 * command with the stored vector, then dispatch with the continuation. */
struct vec { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_ov107_020c9264(int owner, int mode, int b);
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov169_020cdc20(void);

void func_ov169_020cdb84(int self) {
    int *obj = *(int **)(self + 4);
    int target = func_ov107_020cab14(*obj, 0);
    obj[3] = target;
    if (target == 0) {
        *(signed char *)(*obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*obj, 2, 0);
    obj[0x12] = 0;
    *(signed char *)((int)obj + 0x84) = 0;
    func_ov107_020c0b90(*obj, 0, *(struct vec *)obj[2], 0);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov169_020cdc20);
}
