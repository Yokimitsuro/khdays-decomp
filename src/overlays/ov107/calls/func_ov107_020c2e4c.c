/* Calls each child entry's optional handler at +0x18 with `value`, then folds bit 0 of
 * `value` into self->field_40 (preserving the other bits). */
extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);

void func_ov107_020c2e4c(char *self, int value) {
    int p = func_01fffd70(self + 0x44);
    while (p != 0) {
        int e = *(int *)p;
        void (*fn)(int, int) = *(void (**)(int, int))(e + 0x18);
        if (fn != 0) {
            fn(e, value);
        }
        p = func_01fffd8c(self + 0x44);
    }
    *(int *)(self + 0x40) = (*(int *)(self + 0x40) & ~1) | (value & 1);
}
