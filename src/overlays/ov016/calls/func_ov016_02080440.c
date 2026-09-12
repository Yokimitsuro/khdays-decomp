typedef unsigned short u16;

typedef struct {
    char _0[0xe0];
    short slots[1];   /* +0xe0 */
} Ov002SlotTable;

typedef struct {
    char _0[0x12];
    u16 flags;          /* +0x12 */
    char _14[0x1c0 - 0x14];
    int accum;           /* +0x1c0 */
} Obj;

extern int func_ov002_0207687c(void);
extern void func_ov002_0207c67c(Ov002SlotTable *tbl, int param_2);

void func_ov016_02080440(Obj *self) {
    if ((self->flags & 4) != 0) {
        self->accum += func_ov002_0207687c();
        if (self->accum >= 0x1d000) {
            self->accum = 0x1d000;
        }
        func_ov002_0207c67c((Ov002SlotTable *)((char *)self + 0x2c), self->accum);
    }
}
