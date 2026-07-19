/* func_ov035_020b39a8 -- cabeza de una familia de 20 miembros (ov035/039/042/046/...).
 *
 * Semantica COMPLETA: limpia el byte de estado 0x334 del bloque en +0x22f8, avisa al gestor
 * (func_ov022_020b15b0, modo 2), registra dos handlers con func_ov022_020b14a4 -- uno con la
 * tabla ...4c30 sobre la lista de +0x20, otro con ...4c40 sobre la fila +0x3c del nodo de
 * +0x2644 -- guardandolos en 0x340/0x344, notifica 0xd3 al sub-bloque de +0xda0 y marca los
 * bits 0/1/3 del byte de estado.
 *
 * EMPATE (residuo: 8 bytes = DOS instrucciones intercambiadas, nada mas):
 *     ROM   ... ldrb r1,[r5,#9] ; add r3,r2,#4  ; ldr r0,[pc] ; mov r2,#0 ; bl
 *     mwcc  ... ldrb r1,[r5,#9] ; ldr r0,[pc]   ; add r3,r2,#4; mov r2,#0 ; bl
 * mwcc mete la carga del pool entre el `ldr r2` y su uso (separa el interlock); el ROM no.
 * ⚠ Curiosidad que descarta "esto es lo que hace siempre": en la SEGUNDA llamada, identica en
 * forma, el ROM SI pone la carga del pool antes del `add` -- y ahi casamos. La diferencia es que
 * alli r0 esta ocupado por una cadena de dos loads. O sea, es el planificador, no la fuente.
 *
 * Ejes agotados el 2026-07-19:
 *   - `char` -> `unsigned char` para el bloque: eso SI era un fallo real (el ROM usa ldrb y el
 *     offset 0x334 se sale del inmediato de ldrsb, lo que metia un `add` extra). De +4 a 8 bytes.
 *   - 18 variantes de fuente: simbolo como escalar vs array, 4o argumento como expresion / con
 *     cast a char* / hoisted a un local, y 3 firmas del callee (incluida la no especificada).
 *   - **Los 27 compiladores** (tools/allcc.py): todas las 2.0 y 3.0 dan EXACTAMENTE 8; las dsi
 *     dan 17 (barajan distinto, luego el eje existe) y las 1.2 ni compilan. Ninguna acierta.
 *   - Flags: -O4,p / -O4 / -O4,s / -O3,p / -O2,p -> los 5 dan 8. No es cuestion de nivel.
 *
 * Es la clase ya catalogada "orden de la carga del pool con func_ov022_020b14a4". Lo nuevo:
 * que las dsi den OTRO residuo demuestra que el planificador varia entre builds, asi que esta
 * clase apunta a la build de retail (3.0 >= 140) y no a un error de la fuente.
 */
extern int data_ov035_020b4c30;
extern int data_ov035_020b4c40;
extern void func_ov022_020b15b0(int id, int mode);
extern int func_ov022_020b14a4(void *tbl, int id, int idx, int p);
extern void func_ov022_020b1cec(void *p, int n);

void func_ov035_020b39a8(int ctx) {
    unsigned char *blk = (char *)(ctx + 0x2f8 + 0x2000);
    blk[0x334] = 0;
    func_ov022_020b15b0(*(unsigned char *)(ctx + 9), 2);
    *(int *)(blk + 0x340) = func_ov022_020b14a4(&data_ov035_020b4c30,
                                                *(unsigned char *)(ctx + 9), 0,
                                                *(int *)(ctx + 0x20) + 4);
    *(int *)(blk + 0x344) = func_ov022_020b14a4(&data_ov035_020b4c40,
                                                *(unsigned char *)(ctx + 9), 1,
                                                *(int *)(*(int *)(ctx + 0x2000 + 0x644) + 0x3c) + 0x28);
    func_ov022_020b1cec((void *)(ctx + 0xda0), 0xd3);
    blk[0x334] |= 0xb;
}
