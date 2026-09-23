/* Detach hook of the ov254 enemy: unregisters its four effects (+0x468, +0x45c, +0x460, +0x464), the
 * sixteen +0x46c slots and the ten +0x4ac slots from the given list, then runs the base detach
 * (020c7c1c). */
extern void func_ov107_020c2b38(int list, int item);
extern void func_ov107_020c7c1c(char *self, int list);

void func_ov254_020cc754(char *self, int list)
{
    int i;

    func_ov107_020c2b38(list, *(int *)(self + 0x468));
    func_ov107_020c2b38(list, *(int *)(self + 0x45c));
    func_ov107_020c2b38(list, *(int *)(self + 0x460));
    func_ov107_020c2b38(list, *(int *)(self + 0x464));
    for (i = 0; i < 16; i++) {
        func_ov107_020c2b38(list, ((int *)(self + 0x46c))[i]);
    }
    for (i = 0; i < 10; i++) {
        func_ov107_020c2b38(list, ((int *)(self + 0x4ac))[i]);
    }
    func_ov107_020c7c1c(self, list);
}
