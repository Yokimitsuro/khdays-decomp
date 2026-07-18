/* EQUIVALENT BUT NOT BYTE-EXACT -- 8 bytes, 2026-07-19.
 *
 * CUARTA familia con el residuo del ORDEN DE CARGA DEL POOL descrito en
 * src/overlays/ov033/nonmatching/func_ov033_020b350c.c (nota canonica): el ROM construye r3 (el
 * 4o argumento) y DESPUES carga la direccion de la tabla en r0; mwcc carga la tabla primero.
 * Con ov033, ov041_020b3698 y ov044_020b39ac ya son **16 funciones** bloqueadas por lo mismo.
 *
 * Aqui solo afecta a la PRIMERA de las dos llamadas (8 bytes). La segunda casa -- pero NO por lo
 * que primero pense.
 *
 * ⚠ HIPOTESIS DESCARTADA (2026-07-19). Escribi que la ordenacion dependia del COSTE del cuarto
 * argumento (la segunda llamada usa una cadena de derefs y casa; la primera un simple
 * `*(int*)(self+0x20)+4` y falla). **Es falso.** Al leer el diff con cuidado: en la SEGUNDA
 * llamada el ROM tambien carga el pool ANTES del `add` -- coincide con mwcc por casualidad, no
 * porque el argumento sea caro. Y el park de ov031 (func_ov031_020b3830) tiene tres llamadas con
 * argumentos encadenados y **las tres** se intercambian.
 *
 * O sea: el ROM usa los dos ordenes en sitios distintos y mwcc siempre uno. Sigue sin haber
 * teoria util.
 *
 * ⚠ Y el metodo con el que llegue a la hipotesis tambien estaba mal: busque "call sites casados"
 * de func_ov022_020b14a4 y los dos que encontre eran **un asm_stub y otro park**. Es exactamente
 * la regla de SKILL.md sobre filtrar asm_stubs/nonmatching de cualquier cuenta de "esto se ha
 * hecho alguna vez". No hay ni un solo call site casado de esta rutina en todo el arbol.
 *
 * Probado ademas en esta ronda (todo lo anterior esta en la nota de ov033):
 *   tabla tipada como `const Tbl *` en vez de `(int)&data` .... 8  (el struct-typed no aplica aqui)
 *
 * Familia de 4. Modo ARM. */

extern void func_ov022_020b15b0(int a, int b);
extern int func_ov022_020b14a4(int a, int b, int c, int d);
extern void func_ov022_020b1cec(int a, int b);
extern int data_ov035_020b4c30;
extern int data_ov035_020b4c40;

void func_ov035_020b39a8(int self) {
    char *blk = (char *)(self + 0x2f8 + 0x2000);
    *(unsigned char *)(blk + 0x334) = 0;
    func_ov022_020b15b0(*(unsigned char *)(self + 9), 2);
    *(int *)(blk + 0x340) = func_ov022_020b14a4((int)&data_ov035_020b4c30,
                                                *(unsigned char *)(self + 9), 0,
                                                *(int *)(self + 0x20) + 4);
    *(int *)(blk + 0x344) = func_ov022_020b14a4((int)&data_ov035_020b4c40,
                                                *(unsigned char *)(self + 9), 1,
                                                *(int *)(*(int *)(self + 0x2000 + 0x644) + 0x3c) + 0x28);
    func_ov022_020b1cec(self + 0xda0, 0xd3);
    *(unsigned char *)(blk + 0x334) |= 0xb;
}
