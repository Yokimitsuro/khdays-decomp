/* func_ov043_020b5274 -- cabeza de una familia de 26 miembros (ov030..ov062).
 *
 * Semantica COMPLETA y verificada: para cada uno de los dos sub-nodos, publica el puntero del
 * bloque compartido (`slot`, en data_ov043_020b58e0 + 0x2e4 + 0x3000, zancada 0x24) en el campo
 * 0x130 de la fila correspondiente de la tabla `*(owner + 0x3c)` (zancada 0x1c8), notificando
 * antes a WM_EndKeySharing_0x020b15a4.
 *
 * EMPATE: reparto de registros, instruccion por instruccion identico (mismo tamaño, mismos
 * mnemonicos, mismos inmediatos). El ROM asigna r4=base r5=owner r6=i r7=row r8=off sb=slot;
 * mwcc reparte los seis de otra forma. Residuo minimo alcanzado: 10 bytes enmascarados.
 *
 * Ejes agotados el 2026-07-19 (esto NO es "un intento", es la busqueda completa):
 *   - 360 ordenes de declaracion (todas las permutaciones de las 6 locales con base antes de
 *     owner) -> mejor 13 bytes crudos / 10 enmascarados.
 *   - 4 formas del bucle: offset explicito+incremento, i*0x1c8, slot+i*0x24, y las dos a la vez.
 *   - Tipos: base/owner/row como int y como char*; store como row[0x4c] y como *(int*)(row+0x130).
 *   - Aridad de WM_EndKeySharing_0x020b15a4: 2 y 3 argumentos (r2 esta vivo en la llamada, era
 *     el sospechoso obvio de la checklist; con 3 empeora).
 *   - **Los 27 compiladores de tools/mwccarm/** (tools/allcc.py): 1.2 da +20/+24 bytes; TODOS
 *     los 2.0/3.0/dsi dan EXACTAMENTE el mismo residuo de 14. El eje del compilador no existe
 *     aqui, lo que refuerza la nota de reference/mwcc_build_hunt (retail = 3.0 >= 140).
 *
 * Es la sexta familia de la clase ya catalogada "residuo r7/sb con
 * WM_EndKeySharing_0x020b15a4" (deferred-ties.md). Lo nuevo aqui es que el eje del compilador
 * queda descartado con medida, no por analogia.
 */
extern int data_ov043_020b58e0;
extern void WM_EndKeySharing_0x020b15a4(int a, void *b);

void func_ov043_020b5274(int ctx) {
    int base = ctx + 0x2000;
    int owner = *(int *)(base + 0x644);
    int *row;
    int off = 0;
    char *slot = (char *)(data_ov043_020b58e0 + 0x2e4 + 0x3000);
    int i;
    for (i = 0; i < 2; i++) {
        row = (int *)(*(int *)(owner + 0x3c) + off);
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x640), slot);
        row[0x4c] = (int)slot;
        off += 0x1c8;
        slot += 0x24;
    }
}
