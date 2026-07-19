/* func_ov134_020cc448 -- cabeza de una familia de 8 miembros (ov134/135/136/194/...).
 *
 * Semantica COMPLETA: si el objeto tiene puestos los flags 0xa, suelta el sonido retenido en
 * +0x3a4[0x14] y, cuando la fase secundaria (+0x1c7) esta libre (-1) y la principal (+0x1c6) no
 * es ninguna de {0,1,3,5,9}, fuerza la fase 5. Despues, salvo que la fase principal sea 8,
 * vuelve a soltar el handle retenido. Finalmente copia la pose de 11 palabras de +0x394[+4] a
 * los dos destinos (+0x38c, doble indireccion, y +0x390, simple) en su offset 0x10, y corre el
 * tick compartido func_ov107_020c7ca4.
 *
 * EMPATE: 20 bytes, TODO reparto de registros, instruccion por instruccion identico.
 *   - `ldr r1,[r0,#0x14]` (ROM) vs `ldr r0,[r0,#0x14]`: el ROM deja el puntero contenedor en r0
 *     y mete el valor en r1; mwcc lo pisa. Da igual como se escriba la prueba.
 *   - Las dos copias de pose: el ROM usa lr para el ORIGEN e ip para el DESTINO; mwcc al reves.
 *     El orden de computo es el mismo en los dos (origen primero), solo cambia que registro de
 *     scratch le toca.
 *
 * Ejes agotados el 2026-07-19: la copia como asignacion de struct, como `[0] = [0]`, y con
 * helper `inline` en los dos ordenes de parametros; la prueba con indice de array en vez de
 * cast; y **los 27 compiladores** (tools/allcc.py) -- todas las 2.0/3.0 dan 20 bytes y las dsi
 * cambian el tamaño (-4). Ninguna acierta.
 */
typedef struct { int w[11]; } Pose;

extern void func_0203c650(int h);
extern void func_ov107_020c7ca4(char *obj);

void func_ov134_020cc448(char *obj) {
    if ((*(unsigned char *)(obj + 0x1c4) & 0xa) != 0) {
        if (*(int *)(*(int *)(obj + 0x3a4) + 0x14) != 0) {
            func_0203c650(*(int *)(obj + 0x3c));
            *(int *)(*(int *)(obj + 0x3a4) + 0x14) = 0;
        }
        if (*(signed char *)(obj + 0x100 + 0xc7) == -1) {
            int m = *(signed char *)(obj + 0x100 + 0xc6);
            if (m != 0 && m != 1 && m != 3 && m != 5 && m != 9) {
                *(char *)(obj + 0x1c7) = 5;
            }
        }
    }
    if (*(signed char *)(obj + 0x100 + 0xc6) != 8 &&
        *(int *)(*(int *)(obj + 0x3a4) + 0x14) != 0) {
        func_0203c650(*(int *)(obj + 0x3c));
        *(int *)(*(int *)(obj + 0x3a4) + 0x14) = 0;
    }
    *(Pose *)(*(int *)*(int **)(obj + 0x38c) + 0x10) = *(Pose *)(*(int *)(obj + 0x394) + 4);
    *(Pose *)(*(int *)(obj + 0x390) + 0x10) = *(Pose *)(*(int *)(obj + 0x394) + 4);
    func_ov107_020c7ca4(obj);
}
