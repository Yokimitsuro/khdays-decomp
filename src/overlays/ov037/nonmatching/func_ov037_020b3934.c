/* EQUIVALENT BUT NOT BYTE-EXACT -- 131 bytes con el TAMAÑO correcto, 2026-07-19.
 *
 * Misma familia que func_ov036_020b4b9c (iteracion 68, CASADA): construye una estructura de
 * parametros de 0x50 bytes en la pila y llama al creador de emisores. Toda la semantica esta
 * resuelta -- lo que falta es el ORDEN DE EMISION de los ~15 stores.
 *
 * ★ Lo que SI queda resuelto aqui y no hay que volver a derivar:
 *
 * 1. El tercer argumento de func_ov022_02091254 es un **handle empaquetado**:
 *      h = ((((obj + 0x8000) & 0xfffffc) << 7) | 0x80000000) | ((id + 0xbe) & 0x1ff)
 *    donde obj = *(int *)(self + 0x2bd0) e id = *(unsigned char *)(self + 0x918).
 *    (El ROM lo arma con lsls/ands/orrs repartidos; se lee entero en el poolmap.)
 *
 * 2. Los valores del struct, ya descifrados de los shifts:
 *      f00=1 f04=0 f0a=0x19a(short) f0c=0x333 f10=0x1000 f14=0xa000 f18=0x14000
 *      f1c=0 f20=0x7fffffff f28=0 f2c=0x100 f30=0x300 f34=0x100 f38=4 f4c=8(byte)
 *    0x100 y 0x300 los deriva mwcc de 0x19a y 0x333 con `subs`; en el fuente son literales.
 *
 * Probado: handle en un local (135), `self` tipado como struct (135), y reordenar los stores
 * segun donde el ROM hace cada `ldr [pc]` (crack de la iteracion 68) -> 131, mejora pero no basta.
 *
 * Lo que falta es puro trabajo de orden: hay que encontrar la permutacion de las 15 asignaciones
 * que reproduce la planificacion. En func_ov036_020b4b9c basto con mover UNA (`p.f20`); aqui hay
 * mas constantes derivadas y el efecto se propaga. Familia de 4. Modo THUMB. */

extern int NNSi_FndAllocFromDefaultExpHeap(int size);
extern void func_ov022_020911f0(int a, int b, int c);
extern int func_020358f4(int a, int b);
extern void func_ov022_02091254(int a, int b, int c, void *d);

typedef struct {
    int f00;
    int f04;
    char pad08[2];
    unsigned short f0a;
    int f0c;
    int f10;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
    int f2c;
    int f30;
    int f34;
    int f38;
    char pad3c[0x4c - 0x3c];
    unsigned char f4c;
    char pad4d[3];
} Params;

void func_ov037_020b3934(int self) {
    Params p;
    *(int *)(self + 0x2644) = NNSi_FndAllocFromDefaultExpHeap(0x30);
    func_ov022_020911f0(*(int *)(self + 0x2644), 0, 1);
    p.f00 = 1;
    p.f0a = 0x19a;
    p.f04 = 0;
    p.f10 = 0x1000;
    p.f0c = 0x333;
    p.f14 = 0xa000;
    p.f18 = 0x14000;
    p.f20 = 0x7fffffff;
    p.f30 = 0x300;
    p.f38 = 4;
    p.f1c = 0;
    p.f28 = 0;
    p.f2c = 0x100;
    p.f34 = 0x100;
    p.f4c = 8;
    if (func_020358f4(*(unsigned char *)(self + 9), 0x30) != 0) {
        p.f00 |= 1;
    }
    {
        int h = ((((*(int *)(self + 0x2bd0) + 0x8000) & 0xfffffc) << 7) | 0x80000000)
                | ((*(unsigned char *)(self + 0x918) + 0xbe) & 0x1ff);
        func_ov022_02091254(*(int *)(self + 0x2644), self, h, &p);
    }
}
