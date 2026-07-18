/* EQUIVALENT BUT NOT BYTE-EXACT -- 18 bytes, 2026-07-18.
 *
 * El TAMAÑO y la ESTRUCTURA ya son correctos (80 B, mismos bloques en el mismo orden); lo que
 * queda es una cascada de una sola decision: el ROM materializa el `0` de retorno en r0 ANTES
 * de las comparaciones, asi que `obj + 0xa8` tiene que vivir en r2:
 *      add r2, r0, #0xa8 / cmp r1, #0x22 / mov r0, #0 / beq ... / cmp r1, #0x23 / beq ... / pop
 * mwcc deja `base` en r0 (que esta muerto) y materializa el 0 tarde con un `movne r0, #0`.
 *
 * Descartado (tools/bytedist.py):
 *   if/if con `return 0` al final .......................... size -4 (if-convierte el 2o test)
 *   idem con `void *r = 0;` y `return r` .................. size -4
 *   idem con base como `int` .............................. size -4
 *   if/else-if con retorno unico .......................... size -4
 *   switch con `default` PRIMERO .......................... 18  <- arregla el tamaño y el orden
 *   ...y ademas `void *r = 0;` devuelto en el default ..... 18
 *   ...y ademas `r` declarado ANTES que `base` ............ 18
 *   ...y ademas `default: break;` con `return r` al final .. size +4
 *   base tipado como `struct Outer *` (el tipo real del callee) .. 18
 *
 * La forma buena es el switch con default primero: fija el orden de bloques y el tamaño. Lo que
 * no he conseguido es forzar que el 0 ocupe r0 pronto; toda variante que lo intenta acaba
 * if-convirtiendo el segundo test o añadiendo una instruccion.
 *
 * Checklist hecho: arity de func_ov044_020b5110 confirmada = 2 desde su definicion
 * (`struct Outer *outer, int sel`), modo ARM. Familia de 4. */

struct Outer;
extern void func_ov044_020b5110(struct Outer *outer, int sel);
extern void func_ov044_020b3a90(void);
extern void func_ov044_020b3aa4(void);

void *func_ov044_020b3a2c(struct Outer *obj, int a) {
    struct Outer *base = (struct Outer *)((char *)obj + 0xa8);
    switch (a) {
    default:
        return 0;
    case 0x22:
        func_ov044_020b5110((struct Outer *)((char *)base + 0x2c00), 0x22);
        return (void *)func_ov044_020b3a90;
    case 0x23:
        func_ov044_020b5110((struct Outer *)((char *)base + 0x2c00), 0x23);
        return (void *)func_ov044_020b3aa4;
    }
}
