/*
 * Ov002_SetSceneObjectsActive - toggle the gameplay scene's "active" state and broadcast it to
 * every registered scene object. Dep of the ov002 gameplay constructor func_ov002_020679d4.
 *
 * Sets (param_1 != 0) or clears bit0 of the flag byte at scene-manager->list+0x68, then walks the
 * 24 object lists held at scene-manager->list[0..0x17]; for each node in a list it invokes the
 * node's vtable method at *(node+8)+0x3c with (node, active) when that method pointer is non-null.
 * scene-manager = data_ov002_0207fa20; its +4 field ([1]) is the object-list container.
 *
 * ARM. The scene-manager global is referenced directly (as an array) rather than through a kept
 * base pointer: that makes mwcc re-load its pool address in each branch (so obj is recomputed per
 * branch and the arms stay branch-form, not predicated) and, in the loop, index the list with an
 * inline scaled load (ldr rN,[obj,i,lsl #2]) instead of a separate i*4 induction register. The
 * bit result is stored once after the merge (int temp, so no u8 and-#0xff truncation before strb).
 */

typedef unsigned char u8;
typedef void (*Fn)(int obj, int active);

extern int data_ov002_0207fa20[];

void func_ov002_020765f8(int param_1)
{
    int obj;
    int active;
    int i;
    int v;

    if (param_1 != 0) {
        obj = data_ov002_0207fa20[1];
        v = *(u8 *)(obj + 0x68) | 1;
        active = 1;
    } else {
        obj = data_ov002_0207fa20[1];
        v = *(u8 *)(obj + 0x68) & ~1;
        active = 0;
    }
    *(u8 *)(obj + 0x68) = v;
    for (i = 0; i < 0x18; i++) {
        int node = ((int *)data_ov002_0207fa20[1])[i];
        while (node != 0) {
            Fn fn = *(Fn *)(*(int *)(node + 8) + 0x3c);
            if (fn != 0) fn(node, active);
            node = *(int *)(node + 4);
        }
    }
}
