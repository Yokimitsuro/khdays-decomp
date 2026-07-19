/* EQUIVALENT BUT NOT BYTE-EXACT -- 7 bytes, 2026-07-19.
 *
 * Residuo: dos registros intercambiados al final -- el ROM tiene la tabla de trigonometria en
 * `ip` y `blk` (base+0xa4) en `r3`; mwcc los pone en `r3` y `lr`. Todo lo demas casa: el layout
 * de pila, la extension del angulo, el indice `>> 4`, los dos `ldrsh` de seno y coseno, las tres
 * llamadas y la copia final.
 *
 * ★ DOS COSAS QUE SI SE RESOLVIERON y conviene no volver a probar:
 * 1. **La funcion devuelve el Vec3 POR VALOR**, no por puntero de salida. Escrita como
 *    `void f(Vec3 *out, int self)` los dos parametros salian en registros intercambiados
 *    (r4/r5); con `Vec3 f(int self)` -- puntero oculto en r0 -- casan. Es la firma correcta.
 * 2. La direccion `base + 0xa4 + 0x2c00 + 0x124` hay que partirla en **dos locales**
 *    intermedios (crack de func_ov049_020b3a5c), o mwcc la pliega y salen 4 bytes de menos.
 *
 * Descartado para el residuo que queda: 24 permutaciones del orden de declaracion, leer el global
 * `base` mas tarde, mover el primer uso de `self` al principio, y dar nombre al puntero de la
 * tabla (`short *tbl = data_0203d210;`) declarado antes y despues de `blk`.
 *
 * Familia de 4. Modo ARM. */

extern void MTX_RotY33_(void *m, int s, int c);
extern void MTX_MultVec33(int m, void *v, void *out);
extern void VEC_Add(void *a, void *b, void *ab);
extern int data_ov035_020b4ca0;
extern short data_0203d210[];

typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;

Vec3 func_ov035_020b3c8c(int self) {
    Vec3 p;
    Vec3 v;
    MtxFx33 m;
    int base = *(int *)&data_ov035_020b4ca0;
    char *blk;
    char *blk2;
    unsigned short a;
    int i;
    blk = (char *)(base + 0xa4);
    blk2 = blk + 0x2c00;
    p = *(Vec3 *)(self + 0x8c + 0x400);
    a = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    i = a >> 4;
    MTX_RotY33_(&m, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
    MTX_MultVec33((int)(blk2 + 0x124), &m, &v);
    VEC_Add(&v, &p, &p);
    return p;
}
