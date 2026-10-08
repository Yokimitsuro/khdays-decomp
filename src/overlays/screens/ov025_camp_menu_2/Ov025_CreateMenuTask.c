/* Slot 1 of the scene hooks: create the camp menu's task from its class (data_ov025_020b49c4:
 * Ov025_AllocContextAndGetHandler / Ov025_MenuExit) with the argument and keep its handle. */

extern int InstantiateClass();
extern int data_ov025_020b49c4;
extern int data_ov025_020b49c0;

void Ov025_CreateMenuTask(int arg0) {
    data_ov025_020b49c0 = InstantiateClass(&data_ov025_020b49c4, arg0);
}
