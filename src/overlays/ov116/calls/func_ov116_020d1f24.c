/* Three form choices here are load-bearing:
 *  - `target = obj[3] = f(...)` in THAT order: the ROM stores the raw call result
 *    (`str r0`) and keeps the copy for the test. The other order stores the copy.
 *  - the 16-byte copy uses int-pointer indices (`obj + 0x19` / `obj + 0x1d`), not byte
 *    offsets: the byte-offset spelling lets mwcc CSE the two `obj + 0x74` derivations
 *    into a callee-saved register (+r7 in the push list); the ROM recomputes each time.
 *  - `obj` is declared LAST. Declared first it takes r4 and target r5; the ROM has it
 *    the other way round.
 * tmp[9], not tmp[8], is what makes the frame 0x2c. */
struct vec { int x, y, z; };
struct quat { int x, y, z, w; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern void func_0203cd7c();
extern void func_0202ea48();
extern void VEC_Subtract();
extern void func_01ff8d18();
extern void func_01ffa724();
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern char data_02042264[];
extern struct vec data_02041dc8;
extern void func_ov116_020d2048(void);

void func_ov116_020d1f24(int self) {
    int tmp[9];
    int t;
    int target;
    int *obj = *(int **)(self + 4);

    target = obj[3] = func_ov107_020cab14(*obj, 0);
    if (target == 0) {
        *(signed char *)(*obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    func_0203cd7c(tmp, target + 0x74, obj[2], data_02042264);
    func_0202ea48((int)obj + 0x74, tmp);
    *(struct quat *)(obj + 0x19) = *(struct quat *)(obj + 0x1d);
    t = obj[0x12] + *(int *)(*(int *)self + 0x2c);
    obj[0x12] = t;
    if (t < 0x219a) {
        return;
    }
    VEC_Subtract(target + 0x74, obj[2], (int)obj + 0x38);
    func_01ff8d18((int)obj + 0x38, (int)obj + 0x38);
    func_01ffa724(0x300, (int)obj + 0x38, (int)obj + 0x38);
    func_ov107_020c0b90(*obj, 8, data_02041dc8, 1);
    *(signed char *)((int)obj + 0x86) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov116_020d2048);
}
