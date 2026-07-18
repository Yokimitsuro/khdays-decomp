/* EQUIVALENT BUT NOT BYTE-EXACT -- 8 bytes, 2026-07-19.
 *
 * QUINTA familia con el residuo del orden de carga del pool (nota canonica en
 * src/overlays/ov033/nonmatching/func_ov033_020b350c.c). Con ov031, ov033, ov035, ov041_020b3698
 * y ov044_020b39ac van **24 funciones** bloqueadas por la misma decision de mwcc.
 *
 * Igual que en ov035: solo falla la PRIMERA de las dos llamadas. NO es por el coste del argumento
 * -- esa hipotesis esta descartada, ver la nota de ov035_020b39a8; el ROM simplemente usa los dos
 * ordenes en sitios distintos.
 *
 * ⚠ No hay NI UN call site casado de func_ov022_020b14a4 en todo el arbol (los dos que parecen
 * serlo son un asm_stub y otro park). Por eso nadie ha resuelto esto todavia: no hay precedente
 * del que copiar la forma. */

extern void func_ov022_020b15b0(int a, int b);
extern int func_ov022_020b14a4(int a, int b, int c, int d);
extern void func_ov022_020b1cec(int a, int b);
extern int data_ov039_020b55a4;
extern int data_ov039_020b55b4;

void func_ov039_020b3ca8(int self) {
    char *blk = (char *)(self + 0x2f8 + 0x2000);
    *(unsigned char *)(blk + 0x334) = 0;
    func_ov022_020b15b0(*(unsigned char *)(self + 9), 2);
    *(int *)(blk + 0x340) = func_ov022_020b14a4((int)&data_ov039_020b55a4,
                                                *(unsigned char *)(self + 9), 0,
                                                *(int *)(self + 0x20) + 4);
    *(int *)(blk + 0x344) = func_ov022_020b14a4((int)&data_ov039_020b55b4,
                                                *(unsigned char *)(self + 9), 1,
                                                *(int *)(*(int *)(self + 0x2000 + 0x644) + 0xc) + 0x28);
    func_ov022_020b1cec(self + 0xda0, 0xcd);
    *(unsigned char *)(blk + 0x334) |= 0xb;
}
