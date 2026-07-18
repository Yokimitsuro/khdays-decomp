/* EQUIVALENT BUT NOT BYTE-EXACT -- 19 bytes, 2026-07-18.
 *
 * MISMO residuo que src/overlays/ov033/nonmatching/func_ov033_020b350c.c (nota canonica):
 * orden de emision en el setup de argumentos. El ROM construye r3 (el 4o argumento) y DESPUES
 * carga la direccion del pool en r0; mwcc carga el pool primero. Aqui pasa en las DOS llamadas a
 * func_ov022_020b14a4, por eso son 19 bytes y no 8.
 *
 * TERCERA familia con esta forma -- ov033_020b350c, ov041_020b3698 y esta -- o sea **12
 * funciones** bloqueadas por la misma decision. La busqueda de corpus (0 precedentes en ~13.000
 * funciones casadas) esta en la nota de ov033; no repetirla por instancia.
 *
 * Lo demas casa: los offsets, el `|= 0xb`, las dos direcciones de tabla, el `+0x2dc +0x2c00`
 * partido en dos adds. */

extern void func_ov022_020b15b0(int a, int b);
extern int func_ov022_020b14a4(int a, int b, int c, int d);
extern void func_ov022_020b1cec(int a, int b);
extern int data_ov044_020b558c;
extern int data_ov044_020b559c;

void func_ov044_020b39ac(int self) {
    char *blk = (char *)(self + 0x2f8 + 0x2000);
    *(unsigned char *)(blk + 0x334) = 0;
    func_ov022_020b15b0(*(unsigned char *)(self + 9), 2);
    *(int *)(blk + 0x340) = func_ov022_020b14a4((int)&data_ov044_020b558c,
                                                *(unsigned char *)(self + 9), 0,
                                                *(int *)(self + 0x20) + 4);
    *(int *)(blk + 0x344) = func_ov022_020b14a4((int)&data_ov044_020b559c,
                                                *(unsigned char *)(self + 9), 1,
                                                self + 0x2dc + 0x2c00);
    func_ov022_020b1cec(self + 0xda0, 0xd1);
    *(unsigned char *)(blk + 0x334) |= 0xb;
}
