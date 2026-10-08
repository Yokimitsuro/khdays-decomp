/* Slot 1 of the scene hooks: create the game-over scene's task from its class
 * (data_ov027_02083ef8: Ov027_InitScene / Ov027_ExitScene) and keep its handle at +4 of the
 * state. */

extern int InstantiateClass(void *cls, int arg0);
extern int data_ov027_02083ef8;
extern int data_ov027_02083ee0;

void Ov027_CreateSceneTask(int arg0) {
    *(int *)((char *)&data_ov027_02083ee0 + 4) = InstantiateClass(&data_ov027_02083ef8, arg0);
}
