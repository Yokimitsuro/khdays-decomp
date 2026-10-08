/* Ov023_CreateSceneTask -- slot 1 of the event scene's hook table: create the scene's task from
 * its class (data_ov023_0208a004: Ov023_SceneEnter / Ov023_SceneLeave) with the caller's argument
 * and keep the handle in data_ov023_0208a000 -- one task at a time. The same code as ov024's
 * and ov025's slot 1, with this overlay's globals. */
extern int InstantiateClass(void *desc, int arg);
extern int data_ov023_0208a004;
extern int data_ov023_0208a000;

void Ov023_CreateSceneTask(int arg) {
    data_ov023_0208a000 = InstantiateClass(&data_ov023_0208a004, arg);
}
