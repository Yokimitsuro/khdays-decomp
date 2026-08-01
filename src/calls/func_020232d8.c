/*
 * SubObject_SetupDraws - populate three sub-object draw entries of the active scene render context
 * (data_0204be08[1] holds the context; its draw-entry table starts at +0xc) and dispatch each,
 * via SubObject_ConfigDraw (func_02023340: writes an entry's draw parameters at
 * table + index*0x18 and calls SubObject_DispatchDraw). The three entries (slot 4, 0, 1) seed the
 * fixed draw layers of the scene.
 *
 * THUMB. func_02023340 takes eight arguments (four spilled to the stack).
 */

extern int  data_0204be08[];
extern void func_02023340(int table, int index, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);

void func_020232d8(void)
{
    int table = data_0204be08[1];

    func_02023340(table + 0xc, 4, 0, 0, 9, 0xb, 0xe, 2);
    func_02023340(table + 0xc, 0, 0xb, 3, 10, 0xd, 0xb, 2);
    func_02023340(table + 0xc, 1, 0x16, 3, 10, 0xf, 0xb, 2);
}
