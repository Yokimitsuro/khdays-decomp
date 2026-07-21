/* Links an item into the global manager's sorted list (data_ov107_020cbf1c + 4). */

extern int *func_01fffca8(int list, int stride, int max);
extern int *data_ov107_020cbf1c;

void func_ov107_020c9ac0(int item) {
    *func_01fffca8((int)data_ov107_020cbf1c + 4, 4, 100) = item;
}
