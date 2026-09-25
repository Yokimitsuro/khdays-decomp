/* func_ov253_020ccd00 -- rebuild the two carried work lists (+0x388 for the +0x384 owner and
 * +0x390 for the +0x38c owner): each is reset and cleared, seeded from the owner's +0x88 model,
 * given the ov107 pose picked by `idx` from the data_ov253_020d4894 / data_ov253_020d48c8
 * tables, then the owner list is re-initialised and finalised with `flag`. */
struct Ov253PoseTable { int w[13]; };

extern void func_0202a440(int list);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void func_02014b5c(int a, int b);
extern int func_ov107_020c9440(int self, int pose);
extern void func_0202a388(int list, int owner, int pose, int d);
extern void func_0203b9ac(int owner, int list);
extern void func_0203b9fc(int owner, int b, int c, int flag);
extern const struct Ov253PoseTable data_ov253_020d4894;
extern const struct Ov253PoseTable data_ov253_020d48c8;

typedef struct Ov253Carry {
    char pad000[0x384];
    int ownerA;         /* +0x384 */
    int listA;          /* +0x388 */
    int ownerB;         /* +0x38c */
    int listB;          /* +0x390 */
} Ov253Carry;     /* field access, not self + offset: it keeps the IR small enough that the
                     * last call's arguments are still scheduled, as in the ROM */

void func_ov253_020ccd00(Ov253Carry *self, int idx, int flag) {
    struct Ov253PoseTable tableA = data_ov253_020d4894;
    struct Ov253PoseTable tableB = data_ov253_020d48c8;
    int model;

    func_0202a440(self->listA);
    MI_CpuFill8((void *)self->listA, 0, 0x24);
    model = *(int *)(self->ownerA + 0x88);
    func_02014b5c(model + 0x20, *(int *)(model + 0x78));
    func_0202a388(self->listA, model, func_ov107_020c9440((int)self, tableA.w[idx]), 0xc);
    func_0203b9ac(self->ownerA, self->listA);
    func_0203b9fc(self->ownerA, 0, 0, flag);

    func_0202a440(self->listB);
    MI_CpuFill8((void *)self->listB, 0, 0x24);
    model = *(int *)(self->ownerB + 0x88);
    func_02014b5c(model + 0x20, *(int *)(model + 0x78));
    func_0202a388(self->listB, model, func_ov107_020c9440((int)self, tableB.w[idx]), 0xc);
    func_0203b9ac(self->ownerB, self->listB);
    func_0203b9fc(self->ownerB, 0, 0, flag);
}
