/* EQUIVALENT BUT NOT BYTE-EXACT -- "size -4", pero el caso es raro y merece leerse. 2026-07-18.
 *
 * **El flujo de instrucciones casa ENTERO**: 31 instrucciones, mismos registros, mismos offsets,
 * mismas constantes. Lo unico que falta son 4 bytes al final -- **una palabra del POOL LITERAL
 * que la funcion no referencia nunca**.
 *
 * El pool del ROM (offsets desde el inicio de la funcion):
 *     0x68  data_0204c240          <- ldr r0,[pc,#0x54]
 *     0x6c  data_ov044_020b5514    <- ldr r0,[pc,#0x4c]
 *     0x70  0x2c50                 <- ldr r2,[pc,#0x48]
 *     0x74  0x6bc                  <- ***NADIE LA CARGA***
 *     0x78  0x2ca8                 <- ldr r2,[pc,#0x34] y ldr r1,[pc,#0x28]
 *     0x7c  func_ov022_0209fb24    <- ldr r0,[pc,#0x18] (el valor de retorno)
 *
 * Recorri las seis instrucciones `ldr rX,[pc,#N]` calculando PC alineado a 4: ninguna cae en
 * 0x74. O sea que el fuente original produjo una constante 0x6bc que luego dejo de usarse (una
 * lectura muerta, una comprobacion eliminada) y mwcc dejo la entrada del pool.
 *
 * 0x6bc es el offset del campo "estado actual" de la entidad (ver Ov022_SetAnimState), asi que la
 * hipotesis razonable es que el original tenia ahi un acceso al estado que el optimizador se
 * comio. No he encontrado forma de escribir en C algo que emita la palabra del pool SIN emitir
 * tambien la instruccion que la carga.
 *
 * Descartado: `if (0 && *(int *)(base + 0x6bc))` (mwcc lo elimina del todo, pool incluido).
 * Una lectura `volatile` emitiria el `ldr`, que sobraria.
 *
 * ⚠ Antes de gastar mas tiempo aqui, comprueba si el TAMAÑO del simbolo es correcto: mwcc puede
 * emitir el pool al final de una funcion y que una vecina lo comparta. Si esos 4 bytes son de
 * otra funcion, este .c ya es correcto y el problema esta en los limites de symbols.txt.
 * ★ COMPROBADO Y DESCARTADO (2026-07-18). En THUMB los `ldr [pc,#imm]` solo alcanzan hacia
 * ADELANTE, asi que solo una funcion ANTERIOR podria estar usando esa palabra. Recorri todas las
 * funciones de ov044 que empiezan en los 0x400 bytes previos, desensamblandolas en ARM y en THUMB,
 * y calculando el destino de cada `ldr rX,[pc,#N]` con el PC alineado: **ninguna apunta a
 * 0x020b32a8**. La busqueda podia encontrarlo (imprime el objetivo y prueba los dos modos), asi
 * que el cero es evidencia: la palabra esta realmente huerfana y queda la hipotesis 1 -- el
 * fuente original tenia un acceso que el optimizador elimino.
 *
 * Familia de 4. Modo THUMB. */

extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov044_020b3314(int *ctx);
extern int func_0201ef9c(void *tbl, int n);
extern void func_0202a3cc(int a, int b, int c, int d);
extern void func_ov044_020b47d0(int a, int b);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
extern unsigned char data_0204c240;
extern int data_ov044_020b5514;

void *func_ov044_020b3234(int *ctx) {
    int base = NNSi_FndGetCurrentRootHeap();
    func_ov044_020b3314(ctx);
    if ((data_0204c240 & 4) == 0) {
        *(int *)(base + 0x2c50) = func_0201ef9c(&data_ov044_020b5514, ctx[0] + 7);
        func_0202a3cc(base + 0x2c2c, *(int *)(base + 0x20) + 4,
                      *(int *)(base + 0x2c50), ctx[0] + 7);
        *(int *)(base + 0x2ca8) = -1;
        (*(void (**)(int, int))(base + 0x2c50))(base, 0);
    }
    func_ov044_020b47d0(base, base + 0x2ca8);
    func_ov022_020a4798(base, 0x50, 0xd1);
    return (void *)&func_ov022_0209fb24;
}
