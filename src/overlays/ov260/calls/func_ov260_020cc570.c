/* Detach hook of the ov260 enemy: unregisters its two +0x42c / +0x430 effects and the fifteen
 * +0x434 slots from the given list, then runs the base detach (020c7c1c). */
extern void func_ov107_020c2b38(int list, int item);
extern void func_ov107_020c7c1c(char *self, int list);

void func_ov260_020cc570(char *self, int list)
{
    int i;

    func_ov107_020c2b38(list, *(int *)(self + 0x42c));
    func_ov107_020c2b38(list, *(int *)(self + 0x430));
    for (i = 0; i < 15; i++) {
        func_ov107_020c2b38(list, ((int *)(self + 0x434))[i]);
    }
    func_ov107_020c7c1c(self, list);
}
