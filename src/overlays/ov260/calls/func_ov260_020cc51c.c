/* Attach hook of the ov260 enemy: registers its two +0x42c / +0x430 effects and the fifteen
 * +0x434 slots with the given list, then runs the base attach (020c7b70). */
extern void func_ov107_020c2b20(int list, int item);
extern void func_ov107_020c7b70(char *self, int list);

void func_ov260_020cc51c(char *self, int list)
{
    int i;

    func_ov107_020c2b20(list, *(int *)(self + 0x42c));
    func_ov107_020c2b20(list, *(int *)(self + 0x430));
    for (i = 0; i < 15; i++) {
        func_ov107_020c2b20(list, ((int *)(self + 0x434))[i]);
    }
    func_ov107_020c7b70(self, list);
}
