/* EQUIVALENT BUT NOT BYTE-EXACT -- 10 bytes, 2026-07-19.
 *
 * El ROM funde la multiplicacion y la suma en un **`mla`**:
 *     mov ip, #0x800 / mov r1, #0xcd / mla lr, r4, r1, ip
 * mwcc parte la operacion:
 *     mov r1, #0xcd / mul r1, r4, r1 / add lr, r1, #0x800
 * Todo lo demas (el clamp con `movgt`, el `rsb` del negado, los 10 stores del struct de
 * parametros, el override condicional) ya casa.
 *
 * Probado y descartado:
 *   `node[0x43] * 0xcd + 0x800` ......................... 10
 *   `0x800 + node[0x43] * 0xcd` (orden invertido) ....... 10
 *   multiplicacion y suma en sentencias separadas ....... 10
 *   constante 0x800 en un local con nombre .............. 10
 *   idem con el local declarado antes ................... 10
 *   negar en una sentencia aparte (`t = -t`) ............ 48 (peor)
 *
 * ★ PISTA del corpus (tools/find_insn.py 'mla '): hay **345 funciones casadas** con `mla`, y en
 * las que mire el sumando viene de **memoria** (`*(int *)((char *)&data_02047384 + 8) + arg0 *
 * 0x30` en func_02012844). Aqui el sumando es una constante inmediata, y mwcc parece preferir
 * `mul` + `add #imm` en ese caso. Si el original tenia ahi un valor leido de memoria (un campo
 * de configuracion en vez del literal 0x800), saldria el `mla` solo -- merece la pena mirar si
 * 0x800 aparece como campo en alguna estructura cercana.
 *
 * Familia de 4. Modo ARM. */

extern void func_ov022_02091324(int self, void *p);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    Vec3 vec;
    short f0c, f0e, f10, f12;
    int f14, f18, f1c, f20, f24, f28;
} Params;

void func_ov045_020b4630(int self, int *node, Vec3 *src) {
    Params p;
    int t = node[0x43] * 0xcd + 0x800;
    if (t > 0x1800) t = 0x1800;
    p.vec = *src;
    p.f14 = 0;
    p.f1c = 1;
    p.f20 = 0;
    p.f18 = 7;
    p.f24 = 0;
    p.f28 = 0;
    p.f12 = 0x1a00;
    p.f0c = 0;
    p.f10 = 0;
    p.f0e = -t;
    if (node[0x45] != 0) {
        p.f24 = 1;
        p.f12 = 0x1e00;
        p.f28 = 1;
    }
    func_ov022_02091324(self, &p);
}
