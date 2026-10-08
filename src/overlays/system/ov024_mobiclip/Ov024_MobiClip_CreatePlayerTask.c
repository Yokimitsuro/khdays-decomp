/* Ov024_MobiClip_CreatePlayerTask -- slot 1 of the hook table Ov024_MobiClip_InstallStreamSourceVtbl
 * installs: create the movie player's task from its class (data_ov024_02093904:
 * Ov024_MobiClip_OpenPlayer / Ov024_TeardownPlayer) with the caller's argument and keep the
 * handle in data_ov024_02093900 -- one player at a time. */
extern int InstantiateClass(void *desc, int arg);
extern int data_ov024_02093904;
extern int data_ov024_02093900;

void Ov024_MobiClip_CreatePlayerTask(int arg) {
    data_ov024_02093900 = InstantiateClass(&data_ov024_02093904, arg);
}
