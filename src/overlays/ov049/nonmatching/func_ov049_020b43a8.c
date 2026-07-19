/* EQUIVALENT BUT NOT BYTE-EXACT -- size -4, 2026-07-19.
 *
 * Bucle sobre entradas de paso 0x1c8 con despacho por tabla. Toda la logica casa; falta UNA
 * instruccion y esta en la asignacion de registros del despacho:
 *   ROM : ldr r2,[pc] (base de la tabla) / ldr r3,[r2, r3, lsl #2] / mov r0,sl / mov r1,r6 / ...
 *   mio : ldr r3,[r0, r7, lsl #2] / mov r0,sl / mov r2,sb / blx r3   <- r1 ya trae `e`, sobra un mov
 *
 * ★ Lo que SI se resolvio (no volver a probarlo):
 *   forma inicial con `int obj` y offsets crudos ............... size +4
 *      (mwcc hoistea `obj + 0x47a` y `obj + 0x47b` fuera del bucle y desborda `arg` a la pila)
 *   ★ `obj` tipado como struct con campos f47a/f47b ............ size -4  <- quita el hoisting
 *   ternario `obj->f47b = cond ? 1 : 0` ....................... size -8 (peor)
 *   constante 1 en un local (`signed char one = 1`) ........... size -4
 *   idem con `int one` y cast ................................. size -4
 *   idem declarando y asignando por separado (crack it. 89) ... size -4
 *
 * El acumulador NO va en el fuente: su init (`mov r8, r7`) cae DESPUES del test de salida, asi
 * que se indexa con `i * 0x1c8` (regla de la iteracion 60).
 *
 * Familia de 4. Modo ARM. */

extern int func_02030788(void);
extern void *data_ov049_020b4c48[];

typedef struct {
    int flags;
    char pad4[0x47a - 4];
    signed char f47a;
    signed char f47b;
} Obj;

void func_ov049_020b43a8(int self, int arg) {
    int i;
    Obj *obj = *(Obj **)(self + 8);
    for (i = 0; i < (int)*(unsigned char *)(self + 0x19); i++) {
        int e = *(int *)(self + 0xc) + i * 0x1c8;
        int t = *(signed char *)(e + 2);
        if (t == 0) continue;
        if (t == 2 && *(int *)(e + 4) == 0 && func_02030788() == 0 &&
            (obj->flags & 0x10000) == 0) {
            obj->f47a = 3;
            if (*(int *)(*(int *)(e + 0x138)) & 0x200) {
                obj->f47b = 1;
            } else {
                obj->f47b = 0;
            }
        }
        (*(void (**)(int, int, int))&data_ov049_020b4c48[t])(self, e, arg);
    }
}
