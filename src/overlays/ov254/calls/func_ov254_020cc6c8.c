/* Attach hook of the ov254 enemy: registers its four effects (+0x468, +0x45c, +0x460, +0x464), the
 * sixteen +0x46c slots and the ten +0x4ac slots with the given list, then runs the base attach
 * (020c7b70). */
extern void func_ov107_020c2b20(int list, int item);
extern void func_ov107_020c7b70(char *self, int list);

void func_ov254_020cc6c8(char *self, int list)
{
    int i;

    func_ov107_020c2b20(list, *(int *)(self + 0x468));
    func_ov107_020c2b20(list, *(int *)(self + 0x45c));
    func_ov107_020c2b20(list, *(int *)(self + 0x460));
    func_ov107_020c2b20(list, *(int *)(self + 0x464));
    for (i = 0; i < 16; i++) {
        func_ov107_020c2b20(list, ((int *)(self + 0x46c))[i]);
    }
    for (i = 0; i < 10; i++) {
        func_ov107_020c2b20(list, ((int *)(self + 0x4ac))[i]);
    }
    func_ov107_020c7b70(self, list);
}
