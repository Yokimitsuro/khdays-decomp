/* EQUIVALENT BUT NOT BYTE-EXACT -- 7 bytes, 2026-07-18.
 *
 * SEXTA familia con el residuo r7 <-> sb descrito en
 * src/overlays/ov047/nonmatching/func_ov047_020b3b40.c (nota canonica). Ya van ov035, ov039,
 * ov042, ov046, ov047 y ov049: ~24 funciones bloqueadas por la misma decision del asignador.
 * No re-derivar aqui; hay ~70 formas descartadas en la nota canonica.
 *
 * Ojo al pool: `p` se construye con dos adds (#0x68 y #0x3400), asi que la constante en C es la
 * SUMA (0x3468). Escribir solo el primero da "size -4" y parece una instruccion perdida. */

extern void WM_EndKeySharing_0x020b15a4(int a, int b);
extern int data_ov046_020b4b40;

void func_ov046_020b3b7c(int self) {
    int i = 0;
    int p = *(int *)&data_ov046_020b4b40 + 0x3468;
    char *base = (char *)self + 0x2000;
    int obj = *(int *)(base + 0x644);
    int off = 0;

    do {
        int t = *(int *)(obj + 0xc) + off;
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), p);
        i = i + 1;
        *(int *)(t + 0x130) = p;
        off = off + 0x1c8;
        p = p + 0x24;
    } while (i < 2);
}
