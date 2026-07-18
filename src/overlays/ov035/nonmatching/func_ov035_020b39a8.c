/* EQUIVALENT BUT NOT BYTE-EXACT -- 8 bytes, 2026-07-19.
 *
 * CUARTA familia con el residuo del ORDEN DE CARGA DEL POOL descrito en
 * src/overlays/ov033/nonmatching/func_ov033_020b350c.c (nota canonica): el ROM construye r3 (el
 * 4o argumento) y DESPUES carga la direccion de la tabla en r0; mwcc carga la tabla primero.
 * Con ov033, ov041_020b3698 y ov044_020b39ac ya son **16 funciones** bloqueadas por lo mismo.
 *
 * Aqui solo afecta a la PRIMERA de las dos llamadas (8 bytes): en la segunda el 4o argumento es
 * una cadena de derefs (`*(int *)(*(int *)(self + 0x2000 + 0x644) + 0x3c) + 0x28`), lo bastante
 * cara como para que mwcc la empiece antes de tocar el pool. **Eso es un dato nuevo y util**: la
 * ordenacion depende del COSTE del argumento, no es una regla fija del compilador. Sugiere que
 * la forma original del primer argumento produce un valor mas caro de lo que yo escribo.
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
