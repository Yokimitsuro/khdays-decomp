/* EQUIVALENT BUT NOT BYTE-EXACT -- 8 bytes (2 instrucciones), 2026-07-19.
 *
 * Tamaño, bloques y flujo correctos. Lo unico: el ROM carga el valor del `switch` en **r2** y
 * mwcc en **r0**. Los dos `cmp` heredan el registro y ahi estan los 8 bytes.
 *
 * Descartado (tools/bytedist.py):
 *   `switch (node[0])` directo ............................... 8  (este fichero)
 *   local `int st = node[0];` declarado despues de `r` ....... 8
 *   local `int st` declarado ANTES de `r` .................... 8
 *   `int r; r = 0;` en dos sentencias ........................ 8
 *   cola como `if (node[0] != 0) return r; return 1;` .... size -4
 *
 * Sospecha: el ROM reserva r0 porque es el registro de retorno y el valor de retorno (`r`, en r4)
 * se materializa al final; mwcc lo usa como scratch. No he encontrado forma de forzarlo.
 *
 * Familia de 4. Modo ARM. */

extern void func_ov046_020b4608(void);
extern int func_02030788(void);
extern void func_ov046_020b4504(int *node);
extern int func_0202a818(int a, int b);

int func_ov046_020b445c(int *node, int dt) {
    int r = 0;
    switch (node[0]) {
    default:
        break;
    case 1:
        node[0x43] += dt;
        if (node[0x43] >= 0xa000) {
            func_ov046_020b4608();
            node[0] = 2;
        }
        break;
    case 2:
        if (func_02030788() == 0) {
            func_ov046_020b4504(node);
        }
        if (func_0202a818((int)node + 4, dt) != 0) {
            node[0] = 0;
        }
        break;
    }
    if (node[0] == 0) r = 1;
    return r;
}
