/* func_ov038_020b4940 -- cabeza de una familia de 8 miembros (ov038/040/057/...).
 *
 * Semantica COMPLETA: tick de fin de accion del rig. Marca "listo" en los dos sub-bloques de
 * sonido (0x464/0x46c) si el gestor lo permite, pide el desplazamiento acumulado
 * (func_ov022_0209fe20), lo publica en +0x58 -- o levanta el flag de 64 bits 0x4000<<32 y lo
 * pone a cero cuando no hay componente vertical y el modo 4 esta libre --, aplana el vector en
 * Y y lo acumula en +0x498, corre el post-paso y llama al hook +0x668. El bit1 de +0x694 recoge
 * lo que devuelva: si esta puesto, levanta 0x20000<<32, avisa al nodo de +0x20, marca el bit 1
 * del sub-bloque de sonido, limpia los dos acumuladores de +0x498 y +0x698, levanta el flag 4 y
 * cierra la accion con func_ov022_020a35f4 (modo 0 con hook previo si el flag 4 esta puesto,
 * modo 2 si no).
 *
 * EMPATE: 13 bytes, un bloque entero desplazado UN registro (ROM r1/r2, mwcc r0/r1). El resto
 * de las 125 instrucciones casa exactamente.
 *
 * Cuatro arreglos que SI eran reales y quedan anotados porque valen para toda la familia:
 *   - Orden de las dos Vec3 de pila: la ultima declarada va al offset MAS BAJO.
 *   - La asignacion del campo de bits NO lleva `& 1` (el ROM enmascara con 0xff, o sea el ancho
 *     del contenedor, no el del campo).
 *   - El `ldr` del nodo +0x20 va DESPUES del `|=` de 64 bits, luego el local se declara sin
 *     inicializar y se asigna despues.
 *   - Los seis ceros van en orden DESCENDENTE de offset.
 *
 * Ejes agotados el 2026-07-19: los ceros como locales, como campos de Vec3, encadenados
 * (`a = b = c = 0`) en dos grafias, con el offset partido; el resultado del hook a un local;
 * `r` declarada en otro sitio; y **los 27 compiladores** (tools/allcc.py).
 *
 * ⚠ Este empate es la MISMA firma que func_ov181_020cd1e0, func_ov134_020cc448 y
 * func_ov043_020b5274: ver la entrada "el ROM salta el registro libre mas bajo" en
 * deferred-ties.md. Cuatro familias (26+20+10+8 = 64 funciones) dependen de una sola pregunta.
 */
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1; unsigned char b1 : 1; } Flags694;
typedef int (*Hook)(int obj);

extern int func_02030788(void);
extern void func_ov022_0209fe20(int obj, Vec3 *out);
extern int VEC_Add(void *a, void *b, void *d);
extern void func_ov038_020b44a8(int obj);
extern void func_0202af1c(int p);
extern int func_ov022_020a35f4(int obj, int mode);

int func_ov038_020b4940(int obj) {
    Vec3 q;
    Vec3 v;
    int r = 0;

    if (func_02030788() == 0) {
        *(unsigned long long *)(obj + 0x464) |= 0x10000LL;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(obj + 0x46c) |= 0x10000LL;
    }
    func_ov022_0209fe20(obj, &q);
    if (q.y != 0) {
        *(int *)(obj + 0x58) = q.y;
    } else if ((*(unsigned int *)(obj + 0x24) & 4) == 0) {
        *(unsigned long long *)obj |= 0x400000000000LL;
        *(int *)(obj + 0x58) = 0;
    }
    v = q;
    v.y = 0;
    VEC_Add((Vec3 *)(obj + 0x498), &v, (Vec3 *)(obj + 0x498));
    func_ov038_020b44a8(obj);
    ((Flags694 *)(obj + 0x694))->b1 = (*(Hook *)(obj + 0x668))(obj);
    if (((Flags694 *)(obj + 0x694))->b1) {
        int p;
        *(unsigned long long *)obj |= 0x2000000000000LL;
        p = *(int *)(obj + 0x20);
        if ((*(unsigned int *)p & 0x20) == 0) {
            func_0202af1c(p + 4);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(obj + 0x464) |= 2LL;
        }
    }
    if (((Flags694 *)(obj + 0x694))->b1) {
        *(int *)(obj + 0x4a0) = 0;
        *(int *)(obj + 0x49c) = 0;
        *(int *)(obj + 0x498) = 0;
        *(int *)(obj + 0x6a0) = 0;
        *(int *)(obj + 0x69c) = 0;
        *(int *)(obj + 0x698) = 0;
        *(unsigned long long *)obj |= 4LL;
        if ((*(unsigned int *)(obj + 0x24) & 4) != 0) {
            (*(Hook *)(obj + 0x664))(obj);
            r = func_ov022_020a35f4(obj, 0);
        } else {
            r = func_ov022_020a35f4(obj, 2);
        }
    }
    return r;
}
