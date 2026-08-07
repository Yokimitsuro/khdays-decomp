# ★★ EN MWCC 3.0/139 SOLO LA **LECTURA** `volatile` MATA EL CSE, EL **GUARDADO** NO
*(27/07, medido sobre func_ov011_0205ac40)*

El dispositivo estandar del proyecto para forzar que el compilador recargue un global
(el par `CTX` / `CTXV` de `func_ov008_0204f930`) usa una **lectura** cualificada `volatile`.
Cabia pensar que un **guardado** `volatile` serviria de barrera y mataria el CSE de las
lecturas posteriores -- seria mas barato, porque un `str volatile` sigue siendo un `str` y no
anade ninguna instruccion.

**No funciona.** Medido en cinco combinaciones (guardado volatile en el campo `resource`, en
el campo `enabled`, en los dos, en el primer elemento de una copia, y `resource`+copia): las
cinco dan **exactamente el mismo tamano que la forma plana**, o sea el guardado volatile **no
invalida** el valor del global que mwcc lleva cacheado en un registro.

**Regla practica**: si necesitas que un global se relea, tienes que tocar **el sitio de
LECTURA**, no meter una barrera antes. Y el coste es siempre de una instruccion por lectura
forzada, asi que la aritmetica es predecible: N lecturas forzadas = N instrucciones mas.

# ★★★ MWCC EMITE LOS STORES EN ORDEN DE FUENTE ESTRICTO -- LAS CARGAS NO
*(27/07, medido sobre func_ov011_0205ac40 con una rejilla lineal, no por intuicion)*

**Regla**: mwccarm sube cargas por encima de stores con total libertad (es como esconde la
latencia), pero **nunca reordena un store respecto a otro store**. La posicion de un
guardado en el codigo emitido la decide UNICAMENTE donde esta la sentencia en la fuente.

**Como se midio, y por que la medida vale**: partiendo la copia de seis elementos y metiendo
el guardado de otro campo detras del elemento N, el numero de palabras que difieren sale
**exactamente N+1** (N=1 -> 2 palabras, N=6 -> 7). Una recta perfecta. Eso descarta que sea
el planificador: si lo fuera, la posicion emitida no seguiria la de la fuente.

**Uso practico**: si te falta un store DELANTE de un grupo de stores, no busques palancas de
planificacion -- mueve la sentencia. Y al reves: si un store tuyo sale demasiado pronto o
demasiado tarde y las cargas de alrededor ya casan, el residuo es de FUENTE, no de codegen,
y se arregla en una linea.

⚠ **El caso limite**: en esa misma funcion el punto N=0 (el store delante de los seis)
es el orden de la ROM, y es el unico que **no** es size-exact: sale 464 B, un `ldr` corto,
porque mwcc se guarda la direccion del pool del global en un registro en vez de
rematerializarla con un segundo `ldr rX,[pc]`. O sea el orden correcto de stores y la
recarga del pool compiten por la misma decision del asignador. Cerrado por compilacion:
las 42 ordenaciones size-exact de los seis bloques con el store delante (mejor 15 palabras),
la siembra del puntero destino en las 5 posiciones, un puntero origen con nombre en las 6,
0-2 locales extra, temporales `u8`/`int` subiendo 1..6 de las cargas por encima del store, y
el argumento de la llamada escrito en linea en vez de por el local (19-32 palabras).

# ★★★ LOS PRAGMAS `opt_*` DE MWCCARM 3.0/139 SON ACEPTADOS E IGNORADOS
*(27/07, barrido exhaustivo sobre func_ov011_0205ac40)*

Extraje los 82 nombres tipo `opt_*` / `peephole` / `scheduling` / `register_coloring` del
propio `mwccarm.exe` y los probe TODOS, en `on` y en `off`, comparando el binario emitido
contra el de la version sin pragma. **Solo UNO cambia la salida: `optimize_for_size on`**
(y `optimization_level N`, que ya sabiamos). Todos los demas -- incluidos
`#pragma scheduling off`, `#pragma peephole off`, `#pragma register_coloring off`,
`#pragma opt_propagation off`, `#pragma opt_lifetimes off` -- se aceptan sin aviso y no
tocan nada.

⚠ **Consecuencia, y es una regla general**: el argumento *"puse `#pragma X off`, la
salida no cambio, luego X no es la causa"* **NO ES VALIDO con este compilador**. Es
exactamente el mismo error que ya se corrigio en `port-play-order.md` para
`func_ov000_02059b14`. Un pragma inerte no es evidencia negativa: es ausencia de
evidencia. Si necesitas cerrar el eje del planificador o del asignador, ciérralo por
principio o por construccion, nunca por un pragma.
Herramienta: `build/try/ov011/pragac.py` (compara el md5 del texto emitido, asi que un
pragma ignorado no se puede confundir con un eje probado).

# ★★★ EL `add rX, sp, #K` DE UNA COPIA A PILA SALE DE UN PUNTERO DESTINO CON NOMBRE
*(27/07, func_ov011_0205ac40; el precedente casado es func_ov019_0207fa94)*

**Sintoma**: la ROM materializa la direccion de un objeto de pila en un registro
(`add r5, sp, #8`) y guarda a traves de el (`strb rA,[r5]`, `[r5,#1]`...), y tu C sale
exactamente 4 bytes corto porque mwcc pliega la direccion en el modo de direccionamiento
(`strb rA,[sp,#8]`, `[sp,#9]`...).

**Regla**: una **asignacion de struct** (`*(Name *)frame.path = src;`) SIEMPRE pliega la
direccion. Medido en cinco grafias -- puntero tipado, `void *`, dos punteros,
`(char *)&frame + 8`, `&frame.openParams + 1` -- las cinco a 464 B. Lo que la materializa
es un **puntero destino con nombre mas asignaciones elemento a elemento**:

```c
u8 *pDst = frame.path;          /* como sentencia, no como inicializador */
pDst[0] = src[0];  ...  pDst[5] = src[5];
```

Dos detalles que tambien son obligatorios:
- **el origen tiene que ser `unsigned`**. Con `-char signed`, leer elemento a elemento de
  un `char[]` emite `ldrsb`; la ROM tiene `ldrb`. Declara el extern como `u8 []`. (Con la
  asignacion de struct no se nota, porque la copia de bloque ya es byte-a-byte sin signo;
  el bug aparece justo cuando pasas a la forma elemento a elemento.)
- **el `pDst = ...` va pegado a la copia**. Barrido de las 5 posiciones alrededor de las
  sentencias vecinas: cualquier otra posicion pierde entre 10 y 22 instrucciones. La
  posicion del puntero ORIGEN, en cambio, es completamente inerte (mwcc lo rematerializa).

Barrido de respaldo: 720 ordenes de los seis elementos (el directo 0..5 es el mejor),
16 encuadres de la copia, y `memcpy` / `__builtin_memcpy` / `strcpy`, que **mwccarm NO
inlinea** -- los tres emiten un `bl`.

# ★★ UNA LECTURA `volatile` DE UN GLOBAL FUERZA LA RECARGA QUE LIBERA r0
*(27/07, func_ov011_0205ac40)*

**Sintoma**: la ROM calcula la direccion del argumento de una llamada ANTES de un bloque
de copia (le da r0, y el puntero de la copia se va a r1); nosotros la calculamos DESPUES,
porque el puntero de la copia se quedo con r0 y esa dependencia WAR ancla toda la cadena
por debajo de la copia.

Sacar la direccion a un local con nombre la sube -- pero entonces mwcc reutiliza el valor
del global que sigue vivo en un registro y **desaparecen los dos `ldr` de la recarga**
(la funcion queda 8 bytes corta). Leer el global a traves de un lvalue cualificado
`volatile` fuerza la recarga Y conserva la subida:

```c
pStream = &((volatile Ov011Globals *)&data_ov011_0205e960)->pScene->stream;
```

Es una **palanca de codegen, no una afirmacion semantica**: si encuentras una grafia mas
limpia que produzca los mismos dos `ldr`, es mejor. Pero el mecanismo -- *el global se
recarga porque el asignador anticipa que el registro cache se va a machacar* -- es real y
vale para cualquier residuo donde la ROM recarga un global que tu tienes cacheado.

# ★★★ UN AGREGADO QUE ESCAPA BLOQUEA LA SUBIDA DE CARGAS -- SEPARA LO QUE NO ESCAPA
*(25/07, aislado con reproduccion minima en func_ov000_02050ec4)*

**Sintoma**: la ROM tiene `ldr rD,[base,#n] ; str rS,[sp,#m] ; cmp rX,rD` y tu C emite
`str ; ldr ; cmp`. Parece que "mwcc no sube cargas sobre stores", o que "el cmp va
pegado a su operando". Las dos lecturas son el sintoma, no la causa.

**Causa**: en algun punto de la funcion pasas `&w.campo` a un callee. Ese escape expone
**todo el agregado** por direccion, asi que mwcc ya no puede probar que el store a la
pila no aliasa con la carga por puntero, y se niega a reordenarlos. Da igual que el
escape este 100 bytes mas abajo y dentro de otro bucle: **una sola llamada basta**.

**Fix**: saca de la struct el miembro que NO escapa y declaralo como local propia cuya
direccion nunca se toma; deja en la struct que escapa solo lo que de verdad se pasa.
Si ese miembro tiene que seguir viviendo en memoria, `volatile` lo consigue sin
reintroducir el escape.

**Como se aisla** (metodo, no solo este caso): escribe una **reproduccion minima** con
los ingredientes (bucle, puntero a contexto, agregado en pila, condicion) y hazla crecer
hacia la funcion real pieza a pieza hasta que la forma se rompa. El paso que la rompe es
el disparador. Aqui la biseccion fue limpia: con `put(obj,entry,(Pair*)g_ctx)` sale la
forma de la ROM y con `put(obj,entry,&w.mv)` no. Barrer variantes de la funcion entera
nunca lo habria encontrado -- ya se habian compilado 1152 sin acercarse.
⚠ Y ojo con lo que descarta: el offset del campo NO interviene (barrido 0…0x4B08, todo
igual), ni la presion de registros, ni el bucle interior, ni los flags de planificacion.

# ★ VOLATILE: CALIFICADOR DE CAMPO vs CAST (25/07, medido en func_ov000_02050ec4)

Los dos pinchan el acceso, pero **NO cuestan lo mismo**:

- `*(volatile int *)&obj->campo` (CAST): rompe la CSE de la direccion base. Si el
  struct se estaba indexando con una base compartida, mwcc deja de compartirla y te
  come instrucciones -- en ec4, **+28 bytes** por pinchar una sola lectura del par.
- `struct { int x; volatile int y; }` (CAMPO CUALIFICADO): mismo efecto de orden,
  **coste cero**, porque el direccionamiento sigue siendo el de miembro normal.

Si necesitas fijar el orden de accesos dentro de un objeto indexado, **crea un tipo
hermano con el campo cualificado** en vez de castear en el punto de uso. El offset y
el tamano no cambian, asi que no toca el layout.

⚠ Lo que el volatile NO te da: mwcc **acopla el `cmp` a la materializacion de su
operando**. Si pinchas la lectura para que suba, el `cmp` sube con ella. No hay forma
(probada: operador coma en ambos ordenes de operando) de subir la carga y dejar el
`cmp` abajo.

---

# ★★ READBACK FORZADO CON LECTURA VOLATILE (25/07, func_ov000_02050ec4)

**Sintoma**: la ROM guarda un campo de un objeto local en la pila y MAS TARDE lo
recarga (`str rX,[sp,#N]` ... `ldr rY,[sp,#N]`), mientras tu C guarda desde un
temporal y mwcc reusa el registro del temporal en vez de recargar. Te faltan
exactamente 4 bytes (una instruccion) y por lo demas el stream es correcto.

**Fix (mejor)**: calificar el CAMPO/array como `volatile` dentro del struct local:
`volatile int cur[2];`. Eso hace DOS cosas a la vez -- fuerza la recarga (recuperas los
4 bytes) y ancla cada acceso a su posicion en el fuente, lo que ademas ordena
correctamente pares load/store vecinos. En ec4 bajo el residuo de 4 desajustes de
mnemonico a 2, cosa que la variante de solo-lectura NO conseguia.
⚠ Contrapartida: un store volatile es BARRERA, asi que ninguna carga podra subir por
encima de el. Si tu residuo necesita justo eso, no podras tenerlo todo.

**Fix (minimo)**: pinchar SOLO LA LECTURA con volatile en la expresion que la consume:

```c
int cy = obj->pair[i].y;      /* la lectura del par sigue siendo normal */
w.cur[1] = cy;                /* el store sigue siendo normal          */
...
w.mv.y = (target[i].y - *(volatile int *)&w.cur[1]) / 4;   /* <- recarga */
```

**Lo que NO funciona** (medido, no repetir): volatile del lado del STORE
(`((volatile int *)w.cur)[1] = cy` sigue 4 bytes corto); un cast no-volatile
(`((Pair *)&w)->y`, mwcc propaga a traves del cast); alias por puntero
(`int *cp = w.cur; cp[1]`); copia de struct; meter cur/mag/mv en un `int[6]`
contiguo y escapar `&v[4]` (mwcc sigue promocionando v[0..3]).

**Por que el temporal es necesario igualmente**: leer los dos campos del par en
DOS temporales antes de tocar nada es lo que hace que mwcc emita los dos `ldr`
ADYACENTES y pueda diferir el store del segundo, que es la forma de la ROM. Con
asignacion directa campo a campo se recarga solo, pero las cargas dejan de ser
adyacentes porque mwcc reusa el registro base como destino de la segunda.
O sea: temporales para la ADYACENCIA + volatile para la RECARGA. Hacen falta los dos.

**Corolario de medicion**: cuando llegues a este nivel, ordena por
`python tools/posdiff.py <func> <cands...>` y mira `mnemonic-mismatch`, NUNCA una
distancia de edicion sobre el texto completo -- esta ultima puntua un renombrado de
registro igual que una instruccion distinta y te hace optimizar el candidato
equivocado (paso: el "mejor" por edicion tenia 24 desajustes de mnemonico, el
"peor" tenia 4).

---

# 2026-07-25 (port-first) -- DOS cracks nuevos del scroll-ticker ov000 (func_ov000_02050ec4)

## A VALUE IN A PARAMETER'S REGISTER MEANS THE SOURCE REUSES THAT PARAMETER

*(2026-07-26. This closed func_ov000_0205474c and its twin func_ov000_020530cc after
they had resisted for days at 2 instructions.)*

Both functions clip a tile region and then either copy rows or clear them. The clear
loop's counter sits in **sl**, and sl is the register the FIRST PARAMETER arrives in.
That is not a coincidence and it is not a register-allocation tie:

```c
int func_ov000_0205474c(int nRequest, int bCopy)      /* an int, not a pointer */
{
    Ov000BlitRequest *req = (Ov000BlitRequest *)nRequest;   /* cast locally */
    ...
    } else {
        nRequest = 0;                       /* the PARAMETER is the counter */
        if (h > 0) {
            do { MIi_CpuClear16(...); nRequest++; dy++; } while (nRequest < h);
        }
    }
```

The request pointer arrives as a plain integer, is cast to the struct in a local, and
once the clear path no longer needs it the original source counts the rows IN THE
PARAMETER ITSELF. The copy loop's counter meanwhile shares r4 with `bCopy`, the second
parameter -- the same trick one register along.

**How much this cost by not seeing it:** written the obvious way, with a separate local
counter, the function stops two instructions from matching and NOTHING closes it --
27 compiler builds, 13 optimisation levels, every legal pragma, every backend flag
(-constpool, -sdatathreshold, -rostr, -pic, -profile, -interworking, -char, -enum,
-inline), -proc (arm946e/v5te/arm9ej/arm926ej are bit-identical, all others worse),
-ipa, -lang, and roughly 2,500 compiled source variants including an EXHAUSTIVE sweep
of declaration order crossed with block scope. Every one of those is a negative in the
record above, and every one of them was looking in the wrong place.

**The general rule, and it is cheap to apply:** when a residue is "one value is in the
wrong register", ask WHOSE register that is. If it belongs to a parameter, or to any
variable that should already be dead, the source is reusing it. Two supporting facts
make this easy to check:

- the corpus is decisive here. In 13,000 matched functions there is **not one**
  `mov sl,#0` hoisted above a branch, and only nine have an sl loop counter at all --
  so "the counter is in sl" was never going to come out of an ordinary local;
- mwccarm hands out callee-saved registers by DECLARATION RANK, and a parameter ranks
  after every local. A counter in a high register with no declaration order able to
  put it there is the tell.

Related, from the same pair: the twin returns **void** where its pair returns int (its
tail leaves r0 holding the object base rather than the mask, and its dirty byte is at
0x4afa rather than 0x10). Declaring it int costs seven extra mismatches. Two callers
already matched as `return func_ov000_020530cc(...)` do NOT make the callee non-void --
that is the callers' shape, in their own translation units.


## THE ov000 SCHEDULING RESIDUE -- four functions, one shape, everything else closed

*(2026-07-25/26.)* Four independent ov000 functions now sit byte-exact except for a
small INSTRUCTION-SCHEDULING difference, and they all fail the same way: **the ROM
emits an instruction EARLIER than we do.**

| function | residue | what is misplaced |
|---|---|---|
| func_ov000_0205474c | 2 | the clear loop's `mov sl,#0` belongs before the `ble` |
| func_ov000_02059b14 | 6 | `add r5,r0,#0x9000` (second half of a base address) 6 slots early |
| func_ov000_02058e88 | 5 | a computed handle stored to [sp] immediately, not 4 slots later |
| func_ov000_02058a40 | 12 | three address setups front-loaded to hide load-use latency |

Everything OUTSIDE the source text is now closed, measured on all four:

- **27 compiler builds** (every 2.0/3.0 gives an identical residue);
- **13 optimisation levels** via tools/allopt.py;
- **every legal pragma**, including sweeps aimed at the specific transformation;
- **-proc**: arm946e, v5te, arm9ej and arm926ej are BIT-IDENTICAL (one v5TE class) and
  every other processor is far worse -- so the scheduling model itself is confirmed;
- **every backend flag**: -constpool/-noconstpool, -sdatathreshold, -rostr, -nopic,
  -noprofile, -interworking on/off, -char signed/unsigned, -enum int/min, -inline
  off/all/on -- all bit-identical;
- **-ipa** off/function/file (identical; `program` defers codegen to link time and
  emits an empty .text, which is not how this tree builds);
- **-lang** c/c99/ec++ (identical).

`mwccarm -opt display` reports "Backend-specific optimizer options: no extra
backend-specific optimizations", and the ARM backend`s own option list contains no
scheduling switch at all. So the scheduler is not reachable from the command line,
and per the skill it is a source-shape problem -- but no source shape found so far
moves it in any of the four. That is the open question, and four cases is a much
better bench than the one this started with.

**UPDATE 2026-07-31: func_ov008_020590b4 is a FIFTH instance of this exact class**
(the ov008 twin of func_ov000_02058a40, same display/VRAM setup). Byte-exact except the
Sub DISPCNT RMW (0x04001000) block: mwcc reserves r0 for the trailing
GX_SetBankForSubOBJExtPltt(0) arg and hoists `mov r0,#0` into the ldr-value->and load-use
stall, displacing mask/result off r0; the ROM keeps mask/result in r0 and materialises the
0 after the str (the INVERSE direction to the other four -- here mwcc emits EARLIER, not the
ROM). Confirmed by diagnostic (a void trailing call removes the hoist). ~58 source forms
tried (mask pool/bic, struct/absolute/local/static-const pointers, mask- and value-
accumulators, eval/decl order, temps, register, return types, arg reuse). Best form is the
mask-accumulator (`unsigned int r=0xFFCFFFEF; r&=SUB_DISPLAY->dispcnt; r|=0x10; r|=0x200000;
SUB_DISPLAY->dispcnt=r;`) which fixes addr->r2 and value->r1 (residue @0x121, 6 instrs).
Best candidate: build/try/590b4_best.c. Same toolchain-closed conclusion as the other four.
Classified platform-replaced (pure DS display/VRAM bring-up); candidate preserved for a
future scheduler crack, not parked/nonmatching.


## A. STRUCT-POR-VALOR reproduce el `add rN,sp,#off; ldm rN,{r1,r2}` de una llamada VARIADICA

★ **PLANTILLA CASADA CONFIRMADA (iter-5): `src/calls/func_0201df84.c`.** Es el patron exacto,
byte-exact:
```c
typedef struct { unsigned int arc; unsigned int file_id; } FSFileID;
extern void func_0201b7c0(FSFileID *id);              /* rellena via PUNTERO (&id escapa)   */
extern int  FS_OpenFileFast(void *file, FSFileID id); /* recibe el struct POR VALOR -> ldm  */
...
    FSFileID id;                              /* struct local en pila                        */
    func_0201b7c0(&id);                       /* &id escapa                                  */
    if (!FS_OpenFileFast(r5 + 0x5c, id)) ...  /* pasar POR VALOR -> add rN,sp; ldm rN,{r1,r2}*/
```
Solo **3 funciones casadas** en todo el corpus tienen `ldm rX,{r1,r2}` (01fffd0c, 0201b168,
0201df84); es un shape RARO. El de 0201df84 es identico al de `func_ov000_02050ec4` (`w.mv`
rellenado + `&w.mv` a 02055bfc + pasado por valor a 02051980). **Conclusion para 02050ec4: el
idiom NO es el residuo** -- esta confirmado correcto; el residuo son las 4 regiones de scheduling
de una funcion grande (253 insns), invariante en 12 builds 3.0 / todos los flags / ~50 formas /
120+ permutaciones. Ver state.md.


Sintoma: la ROM llama a una funcion y materializa dos args con
`add r2,sp,#0x10; ldm r2,{r1,r2}` (carga un PAR contiguo de pila en r1,r2), y la callee abre con
`push {r0,r1,r2,r3}` (homing de args -> es VARIADICA, lee `*(int*)&argN`). Pasar los args como
DOS ESCALARES a la variadica NO reproduce el ldm: mwcc los deja en registros.

**El caller reproduce el ldm SOLO si declaras la callee tomando un struct de 2 int POR VALOR y
pasas un struct RESIDENTE EN PILA:**
```c
extern int func_cb(int page, Vec2 step);   /* NO (int,int,int,...) en el caller */
func_cb(i, w.mv);                            /* w.mv es un miembro de un struct con &tomada */
```
El struct de 2 int ocupa r1:r2 (AAPCS), y como vive en pila mwcc lo carga con
`add rN,sp,#off; ldm rN,{r1,r2}`. Es ABI-identico a `(int,int)` en r1,r2, asi que la callee
variadica los lee igual. El caller y la callee se compilan por separado (delinking), asi que el
prototipo del caller puede diferir del de la definicion mientras la ABI coincida.
(Cerro el `ldm` y el `sub sp,#0x18` de `func_ov000_02050ec4`.)

## B. `contador = 0;` ANTES de una mascara `& ~0xfff` -> mwcc reusa el cero con `sub`

Sintoma: `x & ~0xfff` (= `& 0xfffff000` = `& -0x1000`) sale como `mov rM,#0x1000; rsb rM,rM,#0`
(2 insns) cuando la ROM lo hace en 1: `sub r0, rJ, #0x1000` reutilizando un registro que YA vale 0
(el contador de un bucle recien inicializado).

**Inicializa el contador del bucle a 0 ANTES de calcular la mascara** (saca el `j=0` del `for`):
```c
int by,bx; j = 0;
by = base->y & ~0xfff;   /* mwcc: sub r0,rJ,#0x1000  con rJ=0 */
bx = base->x & ~0xfff;
for (; j < 8; j++) { ... }
```
Si `j` (=0) esta vivo justo antes, mwcc forma `-0x1000` restando de ese cero en vez de
materializarlo. Bajo el edit-distance de `func_ov000_02050ec4` de 53 a 33 de golpe.

Nota: los empates de scheduling puro de esa funcion (difiere-store del par leido delante, y el
`ldm` px/py->r4,r5 vs ldr px->r1,py->r0 de la cola) NO cedieron a: ~50 formas de expresion,
struct all-Pair, pragmas (opt_schedule/peephole/reorder = no-op), 27 builds (coinciden),
declperm (sin efecto), ni flags -O. Son regalloc del toolchain retail; siguen abiertos en
`build/try/f838/ec4_BEST.c`.

# 2026-07-24 (sesion port-first) -- CUATRO cracks nuevos del frente ov000/panel

## 1. Cadena de `if/else if` vs `switch`: la ROM saca TODOS los `cmp` delante

Sintoma: la funcion sale **4 bytes corta POR CADA despacho**, y en la ROM ves
`cmp #0/beq A ; cmp #1/beq B ; cmp #2/beq C ; <epilogo>` seguido de los cuerpos, mientras
la tuya emite `cmp #0/bne L1 ; <A> ; L1: cmp #1/bne L2 ; <B> ; L2: cmp #2/addne sp...`.

**Es un `switch`, no una cadena de `if`.** mwcc emite todas las comparaciones de un `switch`
por delante y luego los cuerpos; la cadena de `if` funde el ultimo test con el retorno
predicado y ahorra exactamente una rama por despacho. Con 3 despachos son 12 bytes.
(`func_ov000_0204cc90`.) Si los casos son densos 0..N mwcc puede llegar a emitir
`addls pc,pc,r0,lsl #2` + tabla de saltos (`func_ov000_02057dc4`, casos 0..6 con 3/5/6
compartiendo cuerpo) -- eso tambien es un `switch` y no se consigue con `if`s.

⚠ Y el orden de los cuerpos NO es el orden de los `case`: si la ROM pone el primer caso al
FINAL de la funcion, la fuente es una guarda invertida
(`if (t != 4) { ...resto...; return; } <caso 4>`), no un switch. (`func_ov000_02057850`.)

## 2. Las dos mitades de un par de campos se emiten en ORDEN INVERSO al de la fuente

`position.x = A; position.y = B;` produce `mov r0,B ; mov r1,A ; str r0,[sp,#4] ; str r1,[sp]`.
Si la ROM guarda **y** antes que **x**, escribe **x** antes que **y** en la fuente.
(`func_ov000_0204cc90`.)

## 3. Una escritura MMIO mata todos los loads cacheados que la cruzan

`*dispcnt = (*dispcnt & ~0x1f00) | 0x300;` es una escritura a traves de un puntero, asi que
mwcc tiene que asumir que puede aliasar `ctx->counter` y lo **recarga**. Si la ROM reutiliza
el valor que ya habia cargado el `if`, calcula el local ANTES de la escritura. Una instruccion.
(`func_ov000_0204e270`.)

## 4. `x -= 1` ata un puntero al campo; `x = x - 1` no

Una asignacion compuesta evalua el lvalue UNA vez, asi que mwcc se ata un puntero al campo y
carga/almacena por el con desplazamiento 0. `x = x - 1` recalcula la direccion en cada lado y
llega al mismo byte por DOS bases distintas (`+0x4c00` para el `ldrsb`, `+0x4000` para el
`strb`). Ocho bytes. (`func_ov000_0204e5b0`.)

## 5. ★ Cuando SOLO difiere la NUMERACION de los slots de pila: busca una variable reusada

`func_ov000_02057850` quedo con tamano exacto, stream de instrucciones exacto y **23 bytes**
de diferencia que eran unicamente `[sp,#4]` <-> `[sp,#0x10]`. La causa: el contador de filas
del bucle principal era una variable propia (`y`), y eso es UN rango de vida que recibe su
slot antes que los temporales del compilador. En la ROM es **la misma `i`** que usan los dos
bucles de inicializacion: reusarla parte el rango en tres y el ultimo trozo se derrama el
ultimo, que es donde la ROM lo tiene. Nada mas cambia.

Corolario general: **el orden de declaracion NO es el unico eje de coloreado.** Reusar (o
dejar de reusar) una variable entre bucles disjuntos mueve tanto los registros callee-saved
como los slots de derrame, y a veces es lo unico que queda.

## 6. La guarda `volatile` para forzar una recarga -- y por que hay que buscarla en el corpus

`func_ov000_02057dc4` necesitaba que la ROM cargara `slot->a` DOS veces (una para el test y
otra como argumento) donde mwcc hace CSE. Siete experimentos (temporales, `continue`, puntero
al slot, campo tipado como puntero, contador aparte, `while`, cast) no lo forzaron.
**La respuesta estaba escrita en la cabecera de la hermana ya casada `func_ov000_02057138`**:
`*(int volatile *)(row + 0x34)` en la guarda -- y manteniendo 0x34 como DESPLAZAMIENTO por
acceso, porque plegarlo en la base convierte el bucle en un puntero que camina.
Es el recordatorio mas caro de la regla "grepea el arbol casado antes de experimentar".

## 7. ★★ Punteros que CAMINAN explicitos: mismo codigo, distinto grafo de interferencias

`func_ov000_020573e4` estaba a 42 bytes de puro coloreado. Reescribir la condicion del bucle
interno contra dos punteros propios --

    gw = &groups[1];  cw = &counters[1];
    for (k = 1; k < 10; k++) {
        if (gw->id >= 0 && *cw < gw->count && item->id == gw->id) { ... break; }
        gw = gw + 1;  cw = cw + 1;
    }

-- en lugar de `groups[k]`/`counters[k]` **no cambia ni una instruccion** (mwcc ya generaba
esos walkers por reduccion de fuerza) y aun asi baja el residuo de 42 a **19 bytes**: con los
walkers declarados, el valor de retorno cae en el registro bajo que la ROM le da, y con el
arrastra `found` y todo el scratch de la cola.

Leccion: cuando el residuo es SOLO coloreado y el orden de declaracion esta agotado, **declara
explicitamente los temporales que el compilador ya estaba creando**. No cambia el codigo
generado; cambia quien compite con quien.

⚠ Y no lo generalices a todos: hacer lo mismo con el walker de la OTRA fase de la misma
funcion (`g` sobre `groups` en la fase 1) sube el residuo de 19 a 34. Hay que probarlos uno
a uno.

## 8. ★★★ BARRE LOS `#pragma` DE OPTIMIZACION -- no para usarlos, para SABER QUE PASE es

`func_ov000_020573e4` llevaba ~120 experimentos de forma, 40.320 ordenes de declaracion, 12
builds y 17 juegos de flags atascada en 19 bytes de puro coloreado. Un barrido de **35 pragmas
de mwcc** lo partio en dos al primer intento:

    #pragma opt_loop_invariants off     ->  la FASE 1 pasa a ser EXACTA (7 bytes -> 0)

No cambia ni una instruccion: cambia a que registro va cada valor en el bucle interno. O sea que
esos 7 bytes los causaba el pase de invariantes de bucle, y ninguna reescritura del bloque los
iba a mover -- por eso 18 escrituras del test y 8 estructuras del bucle daban todas 7.

★★★ **MEDIDO 2026-07-24: el pragma cambia CINCO instrucciones y NADA mas, y ninguna es un hoist.**
Diffeando la salida con y sin el pragma, las unicas diferencias son los dos temporales de la fase 1
con los registros intercambiados: el pase encuentra exactamente los mismos invariantes, los saca
igual, y aun asi el coloreado sale distinto. Leccion general: **a -O4, un pase que no tiene nada
nuevo que hacer sigue perturbando el asignador**, asi que un pragma puede arreglar un residuo de
coloreado sin que el codigo se mueva ni un byte -- y por eso el barrido vale como diagnostico
incluso cuando estas seguro de que "ese pase aqui no hace nada".

★★ **SACA LOS NOMBRES DEL BINARIO, NO DE LA MEMORIA.** La tabla completa de pragmas esta en
`mwccarm.exe` alrededor del string `opt_lifetimes`; un regex saca **78** nombres
(`opt_scalarizeliveranges`, `opt_marknonregtemps`, `opt_moveinvariantsinaddressexpr`,
`opt_transformcounterloops`, `opt_markvariablecounterloops`, `opt_repositioncode`,
`opt_serializeassignments`, `loopinvariantmax`, ...), muchos de ellos sin documentar en `-help`:

    d=open("tools/mwccarm/3.0_patch4/mwccarm.exe","rb").read()
    i=d.find(b'opt_lifetimes'); seg=d[i-3000:i+3000]
    names=re.findall(rb'[a-z][a-z0-9_]{3,60}\x00', seg)

Barrerlos todos en `off` y en `on` son ~300 compilaciones y unos minutos. Ojo: `register_coloring`
y `scheduling` **no existen** como pragmas (estaban en la lista de arriba por inercia); los que si
existen y apuntan al asignador son `opt_lifetimes`, `opt_scalarizeliveranges` y `opt_marknonregtemps`.

**Uselo primero como DIAGNOSTICO.** Cuando el residuo sea solo coloreado y el orden de
declaracion este agotado, barre los pragmas: te dice el pase responsable, y con eso sabes si
buscar una reescritura (si es CSE/propagacion/reduccion de fuerza, que si dependen de la fuente)
o si el eje es otro. Pragmas que valieron la pena en el barrido: `opt_loop_invariants`,
`opt_common_subs`, `opt_propagation`, `opt_strength_reduction`, `opt_dead_code`,
`optimize_for_size`, `opt_level N`, `register_coloring`, `scheduling`, `peephole`.

**Y son legitimos en el arbol**: ya hay `#pragma thumb on` en 49 ficheros y `#pragma opt_level 1`
en uno. Un pragma de optimizacion es un dispositivo de matching como `volatile`, no una trampa --
pero documenta en la cabecera del `.c` QUE pase estas apagando y por que, igual que con `volatile`.

⚠ Los flags de linea de comando NO sirven para esto: el build usa un juego unico para todo el
arbol, y ademas barrer los 17 mas plausibles (`-O4` a secas, `-O3,p`, `-opt space/speed`,
`-ipa file`, `-inline on/off`, `-enum min`, `-char unsigned`, sin `-gccext`, sin `-interworking`)
no movio ni un byte.

---

# 2026-07-24 (tarde 2) -- ***  FS_OVERLAY_ID: la "constante pequena en el pool" NO es un empate

Sintoma: la funcion sale **4 bytes corta** y la ROM carga del pool un valor que ES un inmediato
codificable (12, 24, 0x6a...), donde mwcc emite `mov r1,#0xc` / `movs r1,#0x6a`.

**No es un literal: es la DIRECCION de un simbolo absoluto del linker.** El idiom de NitroSDK es

    #define FS_EXTERN_OVERLAY(name) extern u32 SDK_OVERLAY_ ## name ## _ID[1]
    #define FS_OVERLAY_ID(name)     ((u32) & (SDK_OVERLAY_ ## name ## _ID))

y `dsd` emite en `build/arm9.lcf` una linea por overlay: `OVERLAY_12_ID = 12;`. Tomar una
DIRECCION obliga a mwcc a poner una palabra en el pool; la ROM ya esta enlazada, asi que esa
palabra vale 12 y **no apunta a ninguna seccion**, asi que dsd no registra reloc ahi. Por eso
parece un literal.

    typedef unsigned int u32;
    typedef u32 FSOverlayID;
    extern u32 OVERLAY_12_ID[1];
    #define FS_OVERLAY_ID_ov012 ((FSOverlayID)(u32) & (OVERLAY_12_ID))
    ...
    func_0201e4a8(0, FS_OVERLAY_ID_ov012);     /* descargar overlay */
    func_0201e470(0, FS_OVERLAY_ID_ov024);     /* cargar overlay    */

**Callees que toman un overlay id**: `func_0201e470` (load), `func_0201e4a8` (unload),
`FS_LoadOverlay`, `FS_UnloadOverlay`.

Cerro de una vez: `func_ov022_02083bd8` (aparcada DOS veces como
"pool-of-encodable-immediate tie", la segunda con la ausencia de reloc tomada como PRUEBA de que
0x6a era literal -- justo al reves), `func_ov000_0204f404`, `0204f47c`, `0205a4d4`, `0205a5e8`,
`0205a3e0`, `0205a554`. Cinco de ellas **a la primera compilacion**.

⚠ **`verify_idx.py` decia `relocs difieren`** en ese C, porque nuestro objeto tiene UN reloc mas
que la ROM. Arreglado: acepta un reloc nuestro sin pareja si apunta a un simbolo absoluto de
`arm9.lcf` y la palabra de la ROM vale eso. **`func_ov001_0204ce40` llevaba tiempo en `calls/`
con el gate en 306 mientras verify_idx la llamaba no-matching** -- una herramienta que contradice
al gate es como se tira un fuente correcto.

**Como detectarlo**: barre el pool de la funcion buscando palabras SIN reloc cuyo valor sea un id
de overlay valido (0..407 en `arm9.lcf`), y mira si entre los callees hay uno de carga/descarga.

# 2026-07-24 (tarde) -- DOS CRACKS NUEVOS, los dos rompen "empates de asignacion de registros"

## A. ★★★ EL CERO DE RETORNO NO SE PREDICA: guarda POSITIVA + reasignacion redundante

Sintoma (dos funciones gemelas, ov006_0204e35c y ov008_0207a1c4, ambas aparcadas meses como
"register-placement tie"):

    ROM : ldr r1,[pc] ; mov r0,#0 ; ldr r1,[r1] ; ldr r1,[r1,#0x49c] ; cmp r1,#0 ; popne
    mio : ldr r0,[pc] ; ldr r0,[r0] ; ldr r0,[r0,#0x49c] ; cmp r0,#0 ; movne r0,#0 ; popne

La ROM materializa el 0 ANTES de la guarda (y el planificador lo mete en el hueco load-use del
`ldr` del pool) y pasa la cadena de punteros por r1. mwcc calcula la guarda en r0 y predica el
resultado. **NO es el asignador: son dos formas de fuente, y hacen falta LAS DOS.**

    /* NO */                                  /* SI */
    if (blocked) return 0;                    Handler next = 0;
    if (call()) return handler;               if (!blocked) {
    obj->failed = 1;                              if (call()) return handler;
    return 0;                                     obj->failed = 1;
                                                  next = 0;      /* <-- redundante, y OBLIGATORIO */
                                              }
                                              return next;

1. **La guarda tiene que ser POSITIVA** (`if (!blocked) { ... }` envolviendo el cuerpo, con un
   solo `return next;` al final). Escrita como salida temprana `if (blocked) return 0;`, mwcc
   convierte el return en `movne r0,#0`, asi que el cero nunca existe como instruccion que el
   planificador pueda mover, y la cadena se queda con r0.
2. **La rama de fallo tiene que REASIGNAR `next = 0;`.** Es redundante en C, pero es lo que
   obliga a mwcc a emitir el segundo `mov r0,#0` de la cola en vez de compartir el de arriba:
   sin ella la funcion sale **4 bytes corta**.

Encontrado grepeando el corpus casado: `find_insn.py --seq 'mov r0, #0' 'ldr r1, \[r1\]'` cae en
`func_ov002_02051318`, que ya tenia el idiom ("resultado nulo declarado el primero, guarda en su
propio registro"). ⚠ Ese analogo es una HOJA (`bxne lr`); el nuestro tiene una llamada, y ahi el
truco de la reasignacion es lo que suple el partido de rango de vida.

## B. ★★★ UN `|=` POR SENTENCIA ROTA EL ACUMULADOR; UNA SOLA EXPRESION LO MANTIENE

`func_02012c2c` (+ gemela `func_02012ca8`, carve de hueco). Empaquetado de BGxCNT:

    ROM : orr r0,r0,r6,lsl#14 ; ldrh r2,[r3] ; orr r0,r0,r1,lsl#2 ; orr r0,r0,r5,lsl#13
    mio : orr r2,r0,r6,lsl#14 ; ldrh r0,[r3] ; orr r1,r2,r1,lsl#2  ; orr r2,r1,r5,lsl#13

Con la cadena escrita como sentencias

    packed  = a << 0xe;
    packed |= b << 8;
    packed |= c << 2;
    packed |= d << 0xd;

cada resultado parcial es un valor propio y mwcc le da un registro nuevo: el acumulador rota
r0 -> r2 -> r1 -> r2 y de paso empuja el `ldrh` al r0 que la ROM deja libre. Con **una sola
expresion**

    packed = (a << 0xe) | (b << 8) | (c << 2) | (d << 0xd);

el acumulador se queda en r0 durante los tres `orr` y el `ldrh` cae en r2, como la ROM.
**Regla general: si el residuo es "las mismas instrucciones pero el acumulador va cambiando de
registro", junta la cadena en UNA expresion** (y al reves: si la ROM rota y tu no, partela).
El orden de la fuente sigue importando -- aqui el `|` va con el operando de `<<0xe` PRIMERO para
que la canonicalizacion conmutativa de mwcc emita el `<<8` primero, como la ROM.

# 2026-07-24 -- ★★★ EL CORPUS DE `staging/*.handoff.md` (52 funciones ov000 + ov003/CRACKS.md)

**NO LO HABIA LEIDO NUNCA.** Mi barrido de staging buscaba solo `func_*.c`; los handoffs son el
sitio donde los carriles pares escriben POR QUE caso cada funcion. Son 52 ficheros en
`staging/ov000/*.handoff.md`, cada uno con una seccion `## Decisive fix`, mas
`staging/ov003/CRACKS.md` y `staging/AGENTS.md`. Leelos ANTES de pelearte con un residuo:
es un corpus de ~50 residuos ya resueltos, con el cambio de fuente exacto que los cerro.

    grep -h -A4 '^## Decisive fix' staging/ov000/*.handoff.md
    awk '/^## Experiments/{f=1;next}/^## /{f=0}f' staging/ov000/func_ov000_XXXX.handoff.md

## Frecuencia de lo que REALMENTE cierra un residuo (contado sobre los 52)

| lever | ficheros | 
|---|---|
| **orden de declaracion de locales** | **17 / 52** |
| **vida de un cache: variable local vs releer el global** | **28 / 52** |
| dispatch en forma de `switch` | 16 / 52 |
| se rindieron y emitieron ARM autoritativo | 13 / 52 |
| aliasing por tipos (puntero vs `int`, tags de struct distintos) | 3 / 52 |
| copiar la forma de una hermana ya casada del corpus | 5 / 52 |

## 1. ★ ORDEN DE DECLARACION -- el lever numero uno, y es por PAREJAS concretas

No es "barre los ordenes y mira el tamano". Los handoffs identifican **la pareja** que rota:
- `02051470`: "Declaring `display` before `offset` fixed `r4/r5`. Declaring `digit` before `value`
  fixed `r8/sb`" -- DOS parejas independientes, una por ciclo de registros.
- `0204cac0`: ordenar los locales como `object, mode, j` da `object=r7, mode=r8, j=sb`.
- `020506d0`: "Declaring `slot` before `selectionGroup`" cerro un swap completo `r8`/`r9`.
- `02054b1c`, `02051b98`, `020532f0`, `0204d358` (structs de pila: **orden inverso**), `0204e1dc`.

⚠ **Mi error en `func_ov003_0204d55c`**: barri 6 ordenes de 4 escalares, sali "sin efecto", y lo
di por cerrado. El corpus dice que la pareja decisiva suele ser OTRA (punteros, structs de pila) y
que el sintoma es un **ciclo/rotacion de registros**, no un cambio de tamano. Si tu residuo es una
rotacion, esto es lo primero, no lo ultimo.

## 2. ★ VIDA DEL CACHE -- ni cachear todo ni releer todo: cachear el PRIMER uso

28 de 52. La forma que gana casi nunca es "local para todo" ni "global en linea en todos lados":
- `020535b4`: cachear el contexto para toda la funcion daba 340 B (corto). **Restringir el local a
  la PRIMERA llamada y deletrear cada acceso posterior a traves del global** restauro las recargas,
  la vida del registro y el schedule -> 396 B byte-exact.
- `02053928`: al reves -- repetir el componente `+0x37c` en seis usos daba 440 B; **cachear
  exactamente ese intermedio** reprodujo la vida de r4 y quito seis instrucciones -> 416 B.
- `020537fc`: `volatile` de mas costaba 8 B; quitarlo dejo a mwcc reutilizar UN deref.
- `0204ef84`: guardar el resultado en un local y asignar el campo despues hacia que mwcc
  reutilizara la direccion; **asignar el campo directamente en las dos ramas** dejo que hiciera
  tail-merge y rematerializara la direccion -> +4 B exactos.

⚠ Esto es exactamente la brecha B de d55c (base de tabla izada vs recargada) y yo solo probe los
dos extremos. **Prueba el punto medio: cachea para el primer uso, global en linea para el resto.**

## 3. Aliasing por TIPOS rota registros sin cambiar nada mas

- `0204e1dc`: representar origen y destino con **tags de struct de 2 bytes DISTINTOS** cambio el
  coloreado por alias y roto los cursores a `ip`/`lr`/`r4` sin tocar tamano ni flujo.
- `02053b0c`: pasar de tipos puntero a `int` escalar dio el "register web" correcto; y el alias de
  profundidad de puntero resulto **independientemente load-bearing**.

## 4. Formas de expresion con precedente

- `0204ebe4`: `(frame - 0x28) * -2` daba el tamano pero programaba `lsl` antes de la negacion;
  **`(-(frame - 0x28)) << 1`** emitio el `sub; rsb; lsl` de la ROM.
- `02051980`: guarda explicita alrededor de un `do` + asignar dentro de la guarda, para que la carga
  ocurra solo en el camino tomado.
- `02051c48`: dimensionar el agregado copiado a `0x1cac` cambio el contador de copia de inmediato
  encodable a **carga de pool**, que era lo que la ROM hacia.
- `020512b8`: locales explicitos de mascara baja/alta fuerzan la presion de registros del objetivo.

## 5. De `staging/ov003/CRACKS.md` (mismo overlay que d55c)

- ★ **"Declara un valor PRIMERO para darle el registro bajo, pero ASIGNALO EL ULTIMO para controlar
  el orden de instrucciones"** -- declaracion y asignacion son levers SEPARABLES. Nunca lo probe.
- Punteros invariantes sostenidos: su orden de registro sigue el orden de DECLARACION.
- `idx = i*STRIDE` como VARIABLE compartida si varios punteros lo reusan.
- Direcciones como `int` (`(int)root`) -> `mla` / `mul` compartido por el stride.
- Guarda de bucle: `if(0<(int)n){do{...}while(i<(int)n);}`; descendente `if(i>=0){do{...}while(i>=0);}`
  (test de signo; NO escribas `-1<i`, materializa el -1).
- Aridades ov003 confirmadas: `func_ov003_0204d1c0(u16*,uint)`, `func_ov003_0204d264(u16*,uint,int)`.

## 6. Y el handoff de ov003 YA diagnosticaba d55c

`staging/ov003/HANDOFF.md`: *"d55c (4B + frame: mixed halfword ptr arith + **register-pressure
spill**; struct-wrapped version in staging)"*. Es exactamente lo que yo redescubri solo doce
pasadas despues como "yo sostengo 9 valores callee-saved y la ROM 8". **Media jornada de trabajo
que un `grep` de treinta segundos habria ahorrado.**

# 2026-07-24 -- CRACKS DE METODO: como MEDIR un residuo (de func_ov003_0204d55c)

Doce pasadas sobre una funcion sin casarla, pero los cracks de metodo salen intactos y valen para
cualquier residuo. **Tres veces cambio la metrica y tres veces cambio cual era la mejor forma.**

## 1. NO ordenes las variantes por TAMANO. Cuenta la instruccion que persigues.

Estuve dos pasadas llamando "mejor forma" a c1 (356 B) porque era la mas cercana en bytes. Cuando
conte los `mul` -- que es de lo que iba el residuo -- c1 tenia **cero** y a1 (352 B, "peor" en
tamano) tenia **3, como la ROM**. El orden por bytes no era ruidoso: estaba ANTICORRELACIONADO.
Toda la rama c1/d1/d2/e2/f1-f3 eran callejones disfrazados de progreso.

## 2. La metrica global es la DISTANCIA DE HISTOGRAMA, no la alineacion por indice.

Alineacion por indice = fragil (una instruccion insertada desplaza todo). Histograma agnostico de
registros = cuantas instrucciones estan simplemente MAL, sin importar el orden:

```python
RE=re.compile(r'\b(r\d+|sb|sl|fp|ip|lr)\b')
def k(i): return i.mnemonic+' '+RE.sub('R', i.op_str)
cr, cm = Counter(k(i) for i in ROM), Counter(k(i) for i in MINE)
dist = sum((cr-cm).values()) + sum((cm-cr).values())
print('ROM tiene y falta:', (cr-cm).most_common(10))
print('sobra en la mia :', (cm-cr).most_common(10))
```
En d55c: la forma con MEJOR alineacion (exact=25/91) generaba **54 instrucciones equivocadas**;
otra con alineacion peor (exact=8) generaba **38**. La ventaja de la primera era que el planificador
cuadraba por casualidad. El `(cr-cm)` / `(cm-cr)` ademas te dice *que* rasgo falta, en terminos
contables, y convierte "difiere el schedule" en una lista de la compra.

## 3. Cuando barras un espacio, puntualo con TODAS las metricas, no con la que persigues.

Barrido de 24 permutaciones, ordenado por `exact`: dos empataban arriba. Puntuado ademas por
histograma, **una de ellas era estrictamente mejor** -- y llevaba tres pasadas en disco sin verse.

## 4. ★ EL PRESUPUESTO DE REGISTROS: compara las asignaciones callee-saved

ARM tiene 8 callee-saved. Si la ROM mantiene 8 valores vivos y tu 9, **ese noveno es el bug y
cascadea**: no queda registro para otra cosa, y eso cambia bases de direccionamiento por toda la
funcion. En d55c yo cacheaba una base de tabla en un registro; la ROM no la cachea, y con ese
registro libre sostiene el offset de byte. Los dos "huecos" que trataba como independientes eran
**el mismo bug**. Como verlo:

```python
for i in DISASM[:24]:
    if i.mnemonic in ('mov','add','ldr','lsl') and i.op_str.split(',')[0].strip() in CALLEE_SAVED:
        print(i.mnemonic, i.op_str)   # hazlo con la ROM y con la tuya, y ponlos en dos columnas
```
Sintoma tipico: **cada rasgo que arreglas cuesta ~20 bytes**. Eso no es que el rasgo sea caro, es
que lo estas anadiendo sin liberar antes el registro, y mwcc paga el derrame en otro sitio.

## 5. `mla` vs `mul`+`lsl`: el puntero en DOS PASOS

`grid[row * K + col]` -> mwcc funde la base y el `+col` en **`mla` con el stride en bytes**.
La ROM suele partirlo: `mul` por K (elementos) -> `lsl #1` (escala) -> `add` base -> `add` offset.
Para forzarlo, puntero intermedio y que muera en la rama:
```c
unsigned short *p = grid + row * 0x1a;   /* mul 0x1a, lsl #1, add base */
... p[col] ...                            /* add del offset, separado */
```
Cachear UN puntero antes del `if` no vale: mwcc elimina un `mul` por CSE. **Uno por rama.**

## 6. Reduccion de fuerza: la variable de induccion MATA el `mul`

`row = 5; ... row += 2;` -> mwcc reduce `row*K` a su propia induccion y el `mul` DESAPARECE.
`row = col * 2 + 5;` derivado en el cuerpo -> mwcc emite `mov rT,#K; mul`.
**mwcc no hace reduccion de segundo orden sobre una induccion derivada.** El `mov sb,#5`/`add sb,#2`
de la ROM es su PROPIA reduccion de `col*2+5`, no una variable del fuente.

## 7. Puntero de VIDA CORTA vs VIDA LARGA

`add rX, sp, #N` + stores por ese registro = puntero de **vida corta**, muere enseguida, coge un
scratch. Si lo declaras a nivel de funcion vive todo el rato, necesita un callee-saved, y si no hay
**crece el marco** (0xc -> 0x10) y mueve los offsets de pila. Sintoma: tu `add rX, sp, #8` donde la
ROM tiene `add rX, sp, #4`. Declaralo con ambito de BLOQUE, uno por sitio de uso.

## 8. Ghidra renderiza direcciones como ARITMETICA ENTERA -- eso NO es la forma del fuente

`iVar5 + iVar9 * 0x34 + iVar8` es lo que hacen las INSTRUCCIONES, no lo que se escribio.
Transcribirlo fielmente puntuo mucho peor en todas las variantes (404 B / 360 B / 388 B) que la
reconstruccion con punteros tipados. Confirma la regla 5b desde el otro lado: Ghidra es para
SEMANTICA y NOMBRES, no para la forma del C.

## 9. Cuenta `ldrsh` contra `ldrh`

Un `short (*)[4]` emite `ldrsh`; la ROM cargaba con `ldrh` en los dos usos. Cambiar el tipo a
`unsigned short` quito el `ldrsh` sin coste. La puntuacion de alineacion no se movio -- **era una
mejora real que ninguna metrica posicional detecta.** Un motivo mas para no guiarse por un numero.

# EL PAR DE HALFWORDS DE 4 BYTES: NO ERA UN EMPATE (2026-07-23)

`deferred-ties.md` tenia una clase entera -- "empate de orden de lectura de 2 halfwords" -- que
bloqueaba ~15 funciones. **No es un empate: son DOS formas distintas y hay que elegir por lo que
hace la ROM**, que se lee en dos instrucciones:

**Caso A -- la ROM lee DESCENDENTE y MATA el registro base en la segunda carga**
(`ldrh r2,[r0,#0xa] ; ldrh r0,[r0,#8] ; strh r2,[sp,#2] ; strh r0,[sp]`):

```c
Pair *pp = &p;                 /* liga un puntero AL DESTINO */
pp->b = tabla[N].b;            /* la mitad ALTA primero */
pp->a = tabla[N].a;
...
cb(obj, pp, 4);                /* y pasa ESE puntero, no &p */
```
Cerro `ov117_020cd494`, `ov210/211/282_020d32a0`, `ov185_020d0efc` x4.

**Caso B -- la ROM lee ASCENDENTE pero mete OTRA carga en medio del par**
(`ldrh ; ldrh ; ldr r4,[r5,#4] ; strh ; strh`):

```c
struct Blk { unsigned short pad[N]; Pair p; };   /* global con TIPO DE STRUCT */
extern struct Blk tabla;
state = (int *)self[1];        /* la otra carga va ANTES */
p = tabla.p;                   /* asignacion de struct = UNA unidad para el planificador */
```
La copia deja de ser dos accesos sueltos, asi que el planificador no puede partirla y la carga
de `state` cae exactamente en el hueco. Leido como `tabla[N].a` / `tabla[N].b` el planificador
parte el par y la carga se va un hueco antes o dos despues. Cerro `ov200/201/271_020cff54`,
`ov200/201/271_020cfcfc`, `ov236/278_020d29b8`.

⚠ El caso que NO cae con ninguna de las dos (`ov141/142/...` x7, 180 B) se diferencia en que el
pool base se carga MUY pronto (el planificador lo mete en el hueco de un `ldr` anterior) y aun
asi la ROM lo mata en la segunda carga. Ahi el residuo son 2 registros. Sigue abierto.
  - RE-CONFIRMADO 2026-07-23 (noche) en `func_ov141_020cd2b0`. Forma mas cercana = **struct copy**
    `buf = data.v` (Caso B), NO el campo-a-campo del Caso A: da AMBAS cargas primero Y el pool en
    r2 (como la ROM); solo falla la DIRECCION (asc vs desc) y el kill del base en la 2a carga. El
    Caso A (campo-a-campo desc) sale peor: intercala y deja el pool en r1 porque `&buf` se
    materializa tarde. La raiz es que la ROM materializa `&buf` (r1) PRONTO (para el arg del cb),
    reservando r1 -> el pool cae en r2 y el flag 0x1ae en r3; mwcc lo hace tarde. Pasar `pp` al cb
    en vez de `&buf` lo empeora (mete `&buf` en callee-saved, +12B). Mejor forma en
    `build/try/cd2b0_best.c`. Probadas 6 formas (struct copy, campo-a-campo asc/desc, dos locales,
    ptr-al-destino, *pp=copy). Residuo = 2 registros + direccion. Sigue abierto.

# ★★ QUE OPERANDO FUSIONA EL `add`: ESCRIBE EL PAR DE SHIFTS EXPLICITO (2026-07-24)

Sintoma: la ROM hace `lsl rA,rX,#N ; lsl rB,rY,#M ; add rD,rB,rA lsr #K` (materializa un termino y
**fusiona** el shift del otro) y tu C hace `lsl ; lsr ; add rD,rD,rY lsl #M` (materializa el termino
entero y fusiona el otro). Los dos tienen el mismo numero de instrucciones: solo cambia **cual de
los dos shifts se fusiona**.

Causa: si escribes el termino con casts (`(unsigned short)(h * 2) * 2`), mwcc **pliega la cadena
entera** y la materializa, y entonces le sobra el otro operando para fusionarlo.
✅ Escribe el par de shifts **explicito y con el cast de anchura delante**:
`((((unsigned int)h) << 17) >> 15)` -> mwcc emite el `lsl` y **fusiona el `lsr` en el `add`**,
exactamente como la ROM. En `func_02024ee8` esto movio el primer diff de 0x50 a 0x65 y de paso
coloco `count` en r2 y arreglo donde cae el `tst`.

⚠ Sirve para elegir la fusion, **no** para elegir el registro: queda un intercambio r0/r1 en los
dos `lsl` (la ROM desplaza el termino EN SITIO, `lsl r0,r0,#0x11`, y mwcc lo mueve a otro registro).

⚠⚠ **Y las dos cosas estan ACOPLADAS en mwcc** (aislado en microtest, 2026-07-24): cuando mwcc
**fusiona** el `lsr` en el `add`, **mueve** el valor desplazado a un registro nuevo; cuando **no**
lo fusiona, lo desplaza **en sitio**. No se ha encontrado forma de fuente que de las dos a la vez.
La ROM SI tiene las dos: `lsl r0,r0,#0x11` (en sitio) + `add r0,r1,r0,lsr#15` (fusionado). Visto de
otra manera: mwcc siempre hace que **Rd aliase con Rn** (el operando plano) y la ROM hace que
**Rd aliase con Rm** (el operando desplazado). Ese es el residuo de 3 instrucciones que queda en
`func_02024ee8`.
Probado sin exito para eso: local intermedio para el half, `h <<= 17` en sitio, partir el `add`,
invertir el orden de los operandos, `count << 2` explicito, `(unsigned)count * 4`, local para
`count*4`. Ver tambien el crack de "avanzar un puntero en sitio" justo debajo -- es el mismo eje y
ahi si se pudo.

# ★★ AVANZAR UN PUNTERO: EN SITIO vs REGISTRO NUEVO (2026-07-24)

Sintoma: todo casa menos que dos registros estan intercambiados alrededor de un puntero derivado.

- `base = (char *)(*(int *)&g + 0x400);` (UNA expresion) -> mwcc carga el puntero en rX y deja la
  suma en un **rY nuevo**; lo siguiente que necesite registro cae en rX. 
- ✅ `base = (char *)*(int *)&g;` y en la linea siguiente `base += 0x400;` -> mwcc **actualiza rX en
  sitio** (`ldr rX,[rX]` / `add rX,rX,#0x400`) y deja rY libre.

Mismo numero de instrucciones; solo cambia la eleccion de registro. Cerro `func_ov008_0207b8a8`
(junto con un argumento perdido). ⚠ Ojo con el tipo: partirlo con `int base` en vez de `char *base`
mete casts y sube 8 B -- el puntero tiene que ser puntero en las dos lineas.

# ★★★ LA COPIA DE STRUCT MUERTA: RESUELTO -- copiala PALABRA A PALABRA (2026-07-23, noche)

**CERRADO. Cerro `func_ov149_020cfad8` + 4 gemelas (ov150/153/154/155), 296 B, un park de
"empate de presion de registros".** Dos cracks, los dos reutilizables:

**Crack 1 -- copia de struct muerta -> struct de UNA palabra.** Si la ROM guarda algo en una copia
de pila que nadie lee, tienes un problema de dos caras:
- `v.x = w[0]` (escalar, o via temporal) -> mwcc **elimina** el store muerto. Sales CORTO.
- `v = *(struct vec *)p` (3 palabras) -> **sobrevive** (mwcc no elimina copias de struct) pero se
  emite `ldm`/`stm` en bloque y luego **recarga las 3 componentes juntas** para operarlas -> las
  tiene vivas a la vez -> 8 callee-saved. Sales LARGO.
- ✅ `*(struct w1 *)&v.x = s[0];` con `struct w1 { int v; };` -> **las dos cosas**: sobrevive a la
  eliminacion Y se emite como `ldr`/`str` suelto que mwcc **fusiona** con el uso siguiente. Una
  carga por componente, se opera desde ese registro, y despues se guarda en la copia muerta --
  exactamente lo que hace la ROM. Todo en scratch.

**Crack 2 -- no caches un puntero a un buffer de pila.** `p = (unsigned char *)&m; p[5] = ...`
deja `p` en un registro y direcciona `[p, #5]`. Indexar `m` directamente en CADA uso
(`((unsigned char *)&m)[5] = ...`) lo pliega a `[sp, #0x11]`. Es la regla 5b (duplica el lookup,
no lo caches) aplicada a un buffer local, no a una tabla.

Formas probadas antes de dar con ella: copia de struct de 3 palabras + pack desde v (300),
temporal unico (284), relleno componente a componente + pack desde v (284), copia de struct +
pack desde `node[1]` (308). Ninguna build cambiaba nada (sweep 27: 2.0 y 3.0 dan 300).

## (historico) el analisis que llevo hasta ahi

`func_ov149_020cfad8` (x5, 296 B) empaqueta un vec3 en un mensaje. La ROM guarda ademas el vector
en una copia de pila `v` que **NUNCA se lee** (sp+0/+4/+8, muerta). Mecanismo aislado:

- **mwcc NO elimina una copia de struct muerta, pero SI elimina stores escalares muertos.** Por eso
  `v = *(struct vec *)node[1];` conserva los 3 stores (296) y CUALQUIER forma escalar
  (`v.x = w[0]`, o un temporal `t`) los borra -> **284 B, 12 menos**. Comprobado en 3 formas.
- Pero la copia de struct se emite como **bloque `ldm`/`stm`**, y despues mwcc **recarga las 3
  componentes a la vez** (`ldr sl,[sp]; ldr r7,[sp,#4]; ldr ip,[sp,#8]`) para empaquetarlas juntas
  -> tiene las 3 vivas a la vez -> **8 callee-saved (r3..sl) y 300 B**.
- La ROM emite la MISMA copia muerta **componente a componente y FUSIONADA con el empaquetado**:
  `ldr lr,[r0]` (una sola carga), empaqueta desde `lr`, y **despues** `str lr,[sp]`. Cada palabra
  vive en scratch (lr/r12/r3) y muere en su store -> solo `{r3,r4,lr}` en el push.
- Empaquetar leyendo `node[1]` directamente en vez de `v` mantiene la copia pero duplica las cargas
  -> **308**. Es el "interleaving" que ya estaba descartado en la nota del park.

Asi que el residuo es exactamente **bloque-vs-componente en una copia de struct muerta**. Ninguna
build lo cambia (sweep: 2.0 y 3.0 dan 300). Formas probadas: copia de struct + pack desde v (300),
temporal unico (284), relleno componente a componente + pack desde v (284), copia de struct + pack
desde `node[1]` (308). Mejor forma = la del park. Sigue abierto.

# `flags |= 1` NO ES `flags = flags | 1` (2026-07-23)

Con `unsigned short flags = 0;`, mwcc **pliega** `flags = flags | 1` a `mov #1` y se come la
truncacion a 16 bits; con `flags |= 1` conserva `orr` + `lsl #0x10 / lsr #0x10`, que es lo que
tiene la ROM. Tres instrucciones de diferencia por un signo de igual. (`ov022_020922a4`.)

# VEC_Set otra vez: tres cargas contiguas -> un ldm (2026-07-23)

El truco de ov294 se repite en toda la veta de handlers. Sintoma: la ROM hace
`ldm rX,{r0,r2,r3} ; add r2,r2,#K ; str ; str ; str` y tu C hace `ldm`+`stm` y luego recarga la
palabra del medio. Cura: `VEC_Set(&v, p->x, p->y + K, p->z)` con VEC_Set `static inline`.
Cerro `ov185/186/187_020ced78`, `ov117_020cca64`, `ov185_020d04cc` x4, `ov215_020d2568`(no).

# Codegen-crack catalog (distilled)

When `verify_idx` DIFFERE on a pure SHAPE difference (same semantics), rewrite the
C to steer mwccarm 3.0/139. Find the symptom below → apply the C form. Diff tools:
`python tools/diffdis.py <c> <name>` (ARM) / `tdiff.py` (THUMB), or compile-and-diff
from `tools/`: `import match; o=match.compile_c(path,thumb); b,r=match.text_relocs(o)`
then capstone-disasm. capstone shows small offsets as `#4` not `#0x4` (regex must
accept both). This is the distilled 80%; the exhaustive archive is memory
`project_khdays_codegen_steering` + `reference_c634_handler_cracks`.

## Bitfields (the #1 crack — model packed fields as real bitfield structs)

A read-modify-write compiling to `ldrb/ldrh; lsl#N; lsr#M; <op>; bic; and; orr;
strb/strh` is a **bitfield**, not a flat mask. A flat `(*p&~M)|K` expression
COLLAPSES (mwcc folds it, func comes out short). Model it:

- **hw60 halfword hi/lo byte**: `struct hw60 { unsigned short lo:8, hi:8; };`
  - `->hi &= ~K` → the `ldrh; lsl#0x10; lsr#0x18; bic #K; …; bic #0xff00; orr…; strh`
    form. Write `&= ~K` (bic), NOT `&= K'` (and). Matches K=1/0x40/0x80. Confirmed.
  - `->lo & 1` (low-byte bit test) → `ldrh; lsl#0x18; lsr#0x18; tst #1`. The
    `(unsigned char)*(u16*)p & 1` CAST collapses it to `ldrb; tst` — DON'T cast.
  - `->hi |= K` — do NOT use the `hi:8` bitfield here (its write-back adds a redundant 16-bit mask,
    +8B). Use the **explicit-shift** form instead (same shape as the `&= ~K` reinsert, cf.
    func_ov123_020cd484), which matches `lsl#0x10;lsr#0x18;orr #K;bic #0xff00;lsl#0x18;orr…lsr#16`:
    ```c
    unsigned short *hw = (unsigned short *)(p + 0x60);
    unsigned int h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | K) << 0x18) >> 0x10);
    ```
    Confirmed K=0xcc (func_ov210_020d1584 x3, 2026-07-18). The `->lo` counterpart uses `<<0x18>>0x18`.
- **byte-in-word field** (`ldr; lsl#0x18; lsr#0x18; <op>; bic #0xff; and #0xff; orr;
  str`): `struct b8 { unsigned f:8; };` then `->f |= K` / `->f &= ~K`. Matches when
  the ROM already emits the lsl/lsr (e.g. `*(*(owner+8)+0x3ac)+8` byte |= 2).
- **low-nibble** (`ldrb; bic #0xf; [orr #K]; strb`): `struct nib { unsigned char
  lo:4, hi:4; };` then `->lo = K` (K=0 → just bic; K=3 → bic+orr).
- **signed-nibble state machine** (`lsl#0x1c/#0x18; asr#0x1c` reads):
  `struct nibs { int lo:4, hi:4; };` (SIGNED int fields). `->lo`/`->hi` sign-extend
  the nibble; `->hi = 0` = `bic #0xf0`; `->hi = -1` = `bic #0xf0; orr #0xf0`;
  `->lo = ->hi` = single RMW. Matched the ov200/201/271 `switch(->lo)` dispatchers.
- **N-bit low field** (`ldrb; lsl#(32-n); lsr#(32-n); …; and #0xff; bic; orr; strb`):
  `struct { unsigned char f:N, rest:8-N; }` + `->f |= K`.
- **bit-N read** (`ldrb; lsl#(31-N); lsr#0x1f; cmp #1`): `struct { unsigned char
  bN:1; …}` + `->bN == 1` (or `== 0`). Bit0 = `<<31>>31`.
- **bitfield STORE `->bit = (cond)`** keeps the redundant `and #1` mask (mwcc
  converts-to-bool then masks): `struct { unsigned int bN:1; }` + `->bN = (flag!=0)`.
  A flat `(*p&~1)|((cond)&1)` folds the `&1` away. If the ROM reads with `ldrsb` +
  `lsl#24;asr#24` (signed bool), declare the container `signed char`.
- **13-bit field in a halfword** (`ldrh; lsl#0x10; lsr#0x13`): `struct { unsigned
  short _lo:3; unsigned short id:13; }` → `->id`. **3-bit byte selector**
  (`ldrb; lsl#0x1d; lsr#0x1d`): `->sel` of `struct{unsigned char sel:3,kind:3;}`.

Poison to avoid: a narrowing `(unsigned char)`/`(unsigned short)` cast lets mwcc
collapse the extract. The `(unsigned)(x<<N)>>N` cast-after-shift form SURVIVES only
when mwcc can't bound the value; when the source is a `ldrb`/`ldrh` it CAN bound it
and collapses to `and` — so use the bitfield struct there.

## Division / fixed-point by constant (write the literal `/D`)

mwcc does NOT fold `(x*C)/C`. Write the natural `v / D`; it regenerates the
reciprocal-multiply magic byte-exact. Derive D from the pool magic M and the
`asr #s` shift: **`D ≈ 2^(32+s) / M`**. Watch for the sign-correction `add`:

- `asr #1`, no correction, M=0x66666667 → **/5**.
- `asr #3`, WITH an `add rHi,base,rHi` correction (M≥2^31), M=0x88888889 → **/15**.
- `asr #3`, NO correction (M<2^31), M=0x66666667 → **/20**.
- `asr #0` (result is just the smull high word + `+ (x>>31)`), M=0x55555556 → **/3**.
- `(x*30)/D` and `(x*30)/20` etc. do NOT fold (overflow-unsafe) — keep the literal
  `* 30 / D`. `x*6` is WRONG for a /D that reduces (mwcc folds to plain mul).

The div block has an internal reg/schedule tie no C steers — it MATCHES only when
the surrounding allocation lines up. If ONLY the ~14-byte div block differs → tie.

**64-bit fixed-point scale**: use a `(long long)` intermediate. e.g.
`dst -= (int)((((long long)m << 7) + 0x800) >> 12)` where `m = a * K` (32-bit mul).

## ★★ `add rD, rN, rM, <shift>`: quien se lleva rD lo decide la VIDA de rN (2026-07-24)

mwcc asigna **rD = rN** siempre que rN muera en el propio `add`. Si la ROM tiene
**rD == rM** (el operando desplazado), el fuente tiene que mantener **rN vivo despues del
add** -- entonces mwcc no puede reutilizar su registro y cae en el de rM.

    ROM : lsl r0,r0,#0x11 ; lsl r1,r2,#2 ; add r0, r1, r0, lsr #15   (rD == rM)
    mwcc: lsl r1,r0,#0x11 ; lsl r0,r2,#2 ; add r0, r0, r1, lsr #15   (rD == rN)

Basta con darle a rN **un uso mas despues del add** (en `func_02024ee8`, escribir el
`count*8` del if como `c4*2` en vez de `count*8`): la instruccion sale byte-identica a la
ROM. ⚠ Efecto colateral: mwcc trata entonces rN como valor de vida larga y **adelanta su
calculo** varios huecos, y la variable de la que derivaba puede morir antes y perder su
registro. Sirve cuando la ROM tambien reusa ese valor; si la ROM lo rematerializa desde
otro sitio, arreglas el `add` y rompes el uso posterior.
Medido en `build/try/24ee8/` (mech_c4live.c) y en `build/try/24ee8/FINDINGS.txt`.

## ★★★ `x >= 1` en vez de `x != 0`: la palanca que ROMPE la predicacion del cortocircuito (2026-07-24)

Sintoma: la ROM tiene ramas de verdad y bloques `mov rX,#0` fuera de linea donde mwcc emite
una cadena predicada `cmp ; ldrbne ; cmpne ; moveq rX,#0 ; beq`. Clasico en guardas del tipo
`if (p == 0 || p->count == 0) return 0;`.

**mwcc NORMALIZA a `!= 0` todas estas formas y entonces PREDICA el cortocircuito**:
`== 0`, `!= 0`, `> 0`, `<= 0`, `0 < x`, `!(x <= 0)`, con o sin cast a unsigned, anidadas,
con `goto`, con `else if`, o con la variable cacheada en un local. **Conserva la comparacion
relacional -- y con ella las ramas -- solo si la escribes `x >= 1`, `x < 1` o `1 <= x`.**
Cerro 36 bytes de golpe en `func_ov005_02050d64` (200/236 -> 224, y con las otras tres
palancas -> 236/236 exacto). Ver `build/try/0d64/FINDINGS.txt`.

⚠ **Efecto secundario**: `>= 1` sale como `cmp rX,#1 ; blo`, y si la ROM tiene `cmp rX,#0 ; bls`
NO hay forma suelta de conseguirlo: medido, mwcc **nunca** emite `cmp #0 ; bls` para una
comparacion aislada. En las 15.285 funciones casadas las 34 apariciones de `cmp rX,#0 ; bls`
son **todas** la guarda de viaje-cero de un `for (i = 0; i < n; i++)` con `n` unsigned. Si ves
ese par en la ROM, la fuente original casi seguro tiene un BUCLE ahi, no un `if`.

## ★ Una variable de 16 bits declarada `unsigned short` impide que mwcc funda el truncado en el `add`

`unsigned int v; v = (unsigned short)e;  ... out = c + v;` -> mwcc emite `lsl v,#0x10` y luego
**funde** el `lsr` en el consumidor: `add r2, r3, r0, lsr #16` (una instruccion menos).
Declarando `unsigned short v;` el par `lsl #0x10 ; lsr #0x10` se materializa entero y el `add`
sale suelto. Vale los 4 bytes exactos cuando el park sale CORTO y el residuo esta en un
truncado a 16 bits. (func_ov005_02050d64.)

## ★★★ Un PUNTERO LOCAL arriba del todo para forzar un callee-saved mas (2026-07-24)

Sintoma: el `push` de la ROM lleva UN callee-saved mas que el tuyo (`push {r4,r5,r6,lr}`
contra `push {r3,r4,r5,lr}` -- el r3 es relleno de alineacion, no un registro usado), y en la
ROM hay un `ldr rX,[pc]` de un OFFSET grande cargado ANTES de las llamadas y conservado hasta
el final de la funcion.

Causa: con la expresion escrita en linea en su punto de uso (`*(unsigned char *)(self + 0x918)`
al final), mwcc calcula el offset tarde y no necesita un tercer callee-saved. La ROM lo
materializa al principio, asi que su asignador reparte los registros de otra forma **en toda la
funcion**.

Palanca: declara un PUNTERO LOCAL al objeto arriba del todo y usalo en el punto de uso:

    unsigned char *idp = (unsigned char *)(self + 0x918);
    ...
    ... (*idp + 0xbe) & 0x1ff ...

En `func_ov037_020b3934` (THUMB, 184 B, familia de 4) esto arreglo el `push` y **46 de las 72
diferencias de golpe** (72 -> 26). Es el efecto contrario al de la regla 5b (no caches punteros):
alli cachear cuesta un callee-saved de mas, aqui es justo lo que hace falta. **El `push` de la
ROM te dice cual de las dos quiere**: cuenta sus callee-saved antes de decidir.

## ★ El orden de los stores a un struct de pila se LEE del ensamblador, no se busca

mwcc emite los stores independientes en ORDEN DE FUENTE (microtest en `state.md`), asi que
cuando un park diga "hay que encontrar la permutacion de las N asignaciones", no hay que buscar:
se transcribe la secuencia de offsets del `str [sp,#N]` de la ROM y se escribe el fuente en ese
orden. En `func_ov037_020b3934` eran 15 campos y el park llevaba meses con la nota.

## ★★★ `volatile` en un PARAMETRO DE PILA para que mwcc lo relea en vez de cachearlo (2026-07-24)

Sintoma: la ROM RELEE un parametro de su hueco de pila entrante en cada uso
(`ldr r3,[sp,#0x20]` dos veces) y recalcula la expresion; mwcc lo carga una vez, cachea el
resultado en un callee-saved de mas y sale MAS CORTO. El park tipico dice "ninguna forma C
des-cachea esto".

Palanca: declarar el parametro `volatile` (o leerlo por `*(volatile T *)&param` en cada uso).
Cada lectura vuelve a memoria, desaparece el valor cacheado y **con el desaparece el
callee-saved extra**, asi que el `push` y el frame se alinean con los de la ROM.

En `func_02034fc4` (THUMB) esto valio 90 -> 100 bytes exactos y 45 -> 6 diferencias.
⚠ Fijate en el FRAME, no solo en el push: mwcc empujaba 6 registros (24 B) y reutilizaba el
hueco de relleno de r3 como area de argumentos salientes; la ROM empuja 5 (20 B) + `sub sp,#4`.
Es el mismo tamano de frame con otro reparto, y por eso el park lo leia como "-10 bytes" en vez
de "un registro de mas". **Cuando el park salga CORTO y la ROM tenga un `sub sp,#N` que tu no
tienes, cuenta los callee-saved antes que nada.**

## ★★★ El par `adds`/`adcs` de SUMA DE 64 BITS CON CERO -- receta completa (2026-07-24)

Sintoma: la ROM copia dos palabras con una suma de 64 bits explicita
(`movs r2,#0 ; movs r1,#0 ; adds r2,r2,rLo ; ldr r3,[..] ; adcs r3,r1`) y tu C emite una
copia pelada (8 bytes corta). Es el primo de 64 bits del artefacto `add r0,r0,#0` de la RNG.
Cerro `func_02034918` (116 B, THUMB) contra un park que decia "no C form reproduces the
ROM's add-with-zero pair".

Hacen falta **tres cosas a la vez**; cada una por separado deja residuo:

```c
long long acc = 0;                    /* (1) DOS sentencias: la suma en su propia linea */
acc = acc + (unsigned int)elem[0]     /* (2) mitad a mitad, NO *(long long *)elem       */
          + ((unsigned long long)(unsigned int)elem[1] << 32);   /* (3) las dos SIN SIGNO */
rec = *rec_out;
*(int *)(rec + 0x10) = (int)acc;                              /* dos stores de 32 bits, */
*(int *)(rec + 0x14) = (int)((unsigned long long)acc >> 32);  /* no uno de 64           */
```

- **(1)** `0LL + e`, `e + 0`, o un `long long z = 0;` inicializado en su propia declaracion se
  pliegan y la suma desaparece. Solo `acc = 0;` seguido de `acc = acc + ...` sobrevive.
- **(2)** con `*(long long *)elem` mwcc materializa UN registro a cero y lo reutiliza como
  destino del `adcs`, asi que sale un solo `movs #0` en vez de dos.
- **(3)** con la mitad baja CON SIGNO, mwcc la extiende a la palabra alta (`asrs rX,rY,#0x1f`)
  y la suma gana una instruccion.
- **El destino**: `*(long long *)(dst + 0x10) = acc` hace que mwcc construya una segunda base
  para la palabra alta (`adds r1,r0,#0 ; adds r1,#0x10 ; str r3,[r1,#4]`), +4 bytes. Dos stores
  de `int` salen `str r2,[r0,#0x10] ; str r3,[r0,#0x14]` como la ROM.

⚠ Generaliza al resto de la familia de "artefactos de copia": **la forma que NO se pliega es
siempre la de dos sentencias con un acumulador nombrado**, y las mitades hay que deletrearlas
por separado para que el compilador no colapse el cero.

## ★★ Los DOS lavados de cero NO son intercambiables (2026-07-24)

El catalogo ya tenia `(char *)0 + x` para el `add rD,rS,#0`. Hay una segunda forma, para
cuando la ROM tiene el cero en un REGISTRO (`mov r6,#0 ; add ip, r6, rX, lsl #12`):

    int zero = 0;                                   /* mov r6, #0            */
    w = (int)((char *)0 + zero) + a * 0x1000 + ...; /* add ip, r6, rA, lsl#12 */

`(char *)zero + x` a secas NO vale: mwcc pliega `zero` y sale `lsl` + `add rD,rS,#0`.
Hace falta el lavado APLICADO A LA VARIABLE (`(char *)0 + zero`), no a la expresion.
Y para el lavado EN SITIO (`add r5,r5,#0`, Rd==Rn) hay que reusar la propia variable:

    v = (int)((char *)0 + e->f14);   /* add rV, rF14, #0 */
    v = (int)((char *)v + p[2]);     /* add rV, rV, rP2  -- el cast a char* fija Rn=v */

Las dos aparecen en `func_ov022_020a2230`, una para cada mitad del calculo.

## ★★ `x / 4` con signo: escribe la DIVISION, no la expresion a mano

`(v + ((unsigned int)(v >> 1) >> 0x1e)) >> 2` parece la traduccion literal de
`asr #1 ; add ; asr #2`, pero la suma con un `unsigned` hace unsigned todo el resultado y
el desplazamiento final sale `lsr` donde la ROM tiene `asr`. `v / 4` sobre un `int` emite
los tres pasos exactos. Mismo argumento para `/ 2` (`add rX,v,v,lsr #31 ; asr #1`).
**Si en un park ves `lsr` donde la ROM tiene `asr` (o al reves) en una division por potencia
de dos, el bug es la promocion a unsigned de la expresion escrita a mano.**

## ★★ Romper un `stm sp, {rA, rB}` de argumentos salientes: es el ORDEN DE MATERIALIZACION

`stm` exige registros ASCENDENTES. Si la ROM emite dos `str` sueltos donde tu sacas un `stm`,
lo unico que hace falta es que el valor de `[sp,#0]` acabe en un registro **mas alto** que el
de `[sp,#4]`. En `func_ov045_020b476c` la ROM tiene 2 en r2 y 0xa en r1 (descendente, no
fusionable) y mwcc tenia 2 en r0 y 0xa en r2.

Se consigue **reordenando las asignaciones de esas constantes** en el fuente (alli, escribir
`f3c = 2;` antes de `f4c = 0xa;`), no izandolas a locales ni moviendo los stores junto a la
llamada -- las dos cosas estaban probadas en el park y ninguna toca el problema, porque lo que
decide es en que orden se MATERIALIZAN, no donde esta el store. Vale los 4 bytes exactos.

⚠ **Y el corolario del caso contrario**: transcribir el orden de stores de la ROM tal cual
funciona en `func_ov037_020b3934` pero NO en `func_ov045_020b476c`. Alli, poner `d[0].f38 = 5;`
en la posicion que ocupa en la ROM hace que mwcc derive el 0x3e1 vecino del 5 recien
materializado y el resultado sale OCHO bytes corto. La ROM tambien deriva, pero por su cuenta;
en cuanto el fuente pone las dos constantes juntas, mwcc se ahorra mas de la cuenta.

## ★★★ `volatile` = "no lo guardes en un registro" -- las DOS caras (2026-07-24)

Dos parks distintos cerraron el mismo dia con la misma palabra clave, en direcciones opuestas.
El sintoma comun: **el park describe correctamente una decision de asignacion que no sabe pedir.**

**Cara A -- la ROM RELEE un parametro de pila y tu lo cacheas.**
`func_02034fc4`: la ROM hace `ldr r3,[sp,#0x20]` en cada uso; mwcc lo carga una vez y cachea el
resultado en un callee-saved de mas. Palanca: declarar el parametro `volatile`
(`int f(..., volatile int index, int keep)`) o leerlo por `*(volatile int *)&index`. Cada lectura
vuelve a memoria, desaparece el valor cacheado y **con el, el callee-saved extra**: el `push`
pasa de 6 a 5 registros + `sub sp,#4` y el frame cuadra. 90 -> 100 bytes exactos.

**Cara B -- la ROM DERRAMA un local a la pila y tu lo dejas en un registro.**
`func_ov221_020d4020`: la ROM hace `str r2,[sp]` / `ldr r1,[sp]`; mwcc guardaba el valor en un
callee-saved. Palanca: `volatile int saved;`. 500 -> 504 bytes exactos y el `push` cuadra.
⚠ **Cuenta las lecturas.** Con `volatile` CADA lectura vuelve a memoria. Si la ROM carga una vez
y el fuente lee dos veces, copia a un temporal NO volatil en el punto de uso:
`{ int s = saved; if (s >= 0) { ... f(owner, s) ... } }`. Sin eso sobran 4 bytes.

**Como reconocerlo**: mira el `push` antes que nada. Un callee-saved de mas o de menos con el
mismo tamano de frame es casi siempre esto, no "el asignador eligio distinto".

## ★★★ Forzar que mwcc RECARGUE del pool en vez de cachear en callee-saved (2026-07-24)

Sintoma: la ROM carga la MISMA palabra de pool varias veces y su prologo no tiene callee-saved
(`push {r3,lr}`); mwcc la cachea y empuja `{r3,r4,r5,lr}`. Tipico de funciones que tocan un
global de escena alrededor de varias llamadas. Cerro `func_ov006_0204f2f4` contra una nota que
decia "not steerable from C".

Tres palancas, y hacen falta las tres:

1. **Deletrear cada GRUPO de accesos distinto.** Mira el desensamblado: la ROM comparte la base
   dentro de un grupo y la recarga entre grupos. Escribe un grupo por deletreo:
   `*(char **)&sym`, `((char **)&sym)[0]`, `*(char **)((char *)&sym)`, `((int *)&sym)[1]`.
   Con una sola macro para todos, mwcc guarda una copia viva y gasta un callee-saved.
2. ★★ **La direccion de una FUNCION se des-CSEa comparandola como PUNTERO A FUNCION.**
   `(void (*)(void))state == func_x` en los tests y `(int)&func_x` como argumento son la misma
   direccion escrita de dos formas: mwcc deja de unificarlas y recarga la palabra de pool.
   `(int)func_x` y `(int)&func_x` NO bastan -- son identicos para el compilador.
3. **Un unico `return 0` compartido, alcanzado con `goto`.** Varios `return 0;` sueltos se
   predican uno a uno (`movne r0,#0 ; popne`); una etiqueta con >=2 predecesores no se puede
   convertir a predicado, que es justo lo que da las ramas a un bloque de salida unico.

⚠ Y en la misma funcion: el test de bit 0 escrito `(x << 0x1f) >> 0x1f` **se pliega entero a
`tst r0,#1`** cuando el resultado solo se testea. Para conservar el `lsl #0x1f ; lsrs #0x1f` de
la ROM hace falta una lectura de bitfield de verdad: `((Bits8 *)p)->b0`.

## ★★ Una carga de 64 bits hay que direccionarla por `char *` (2026-07-24)

`*(long long *)(obj + 0x464)` hace que mwcc **parta la base para la mitad alta**
(`add r2,r0,#0x64` + `ldr r0,[r2,#0x404]`, +4 bytes) aunque los dos offsets (0x464 y 0x468)
sean perfectamente codificables en un `ldr` de ARM. Con el cast a `char *` en la direccion --
`*(long long *)((char *)obj + 0x464)` -- emite las dos cargas directas `[r0,#0x464]` /
`[r0,#0x468]` de la ROM. En `func_ov022_020ad4e8` eso valio los 4 bytes **y** el callee-saved
extra que el split arrastraba.

## ★★ El valor absoluto de un delta: `if/else` de verdad, no "asigna y corrige"

    ad = d; if (0x8000 < d) ad = 0x10000 - d & 0xffff;    /* mwcc PREDICA todo el bloque */
    if (0x8000 < d) { ad = 0x10000 - d & 0xffff; } else { ad = d; }   /* movle + ble como la ROM */

La primera forma cuesta ademas DOS callee-saved de mas, porque los tres pasos predicados
(`rsbhi/lslhi/lsrhi`) alargan las vidas. Y ⚠ **el delta y su absoluto son `int`**: con
`unsigned` los tests salen `movhi`/`rsbhi` donde la ROM tiene `movgt`/`rsbgt`.

## Conditional block layout (negate to flip which block is inline)

mwcc makes the condition's **fall-through** the inline block and branches the other
out-of-line. If the ROM lays the SMALL/early block as fall-through and the BIG block
as the branch target but you got the opposite, **negate the condition and swap**:

- `if(cond){big}else{small}` → mwcc puts big first. To get small-first (ROM),
  write `if(!cond){small; …}else{big}` or guard-return `if(!cond){small; return;} big;`.
  De-Morgan the `&&`/`||`. (Fixed 020d1ea8, 020d00bc.)
- `if(a<6||8<a){BODY}else{CHECK}` puts BODY inline; ROM's in-range form needs
  `if(6<=a && a<=8){CHECK}else{BODY}`.
- ★★ **MEDIDO 2026-07-24: el umbral de if-conversion de mwcc 3.0/139 -O4,p es EXACTAMENTE 3.**
  Bloque de 1/2/3 instrucciones -> predicado; de 4 en adelante -> rama real. Medido con
  `build/try/ef9c/probe9.py` (bloque sintetico de N sumas independientes). No lo mueve NINGUNA
  opcion del compilador: probados -O0..-O4 con `,p`/`,s`, `-opt no{peephole,scheduling,cse,
  propagation,deadcode,lifetimes,global,strength,loopinvariants}`, `-opt space/speed`, 8 valores
  de `-proc`, 15 `#pragma` (incluido `optimize_for_size`, `scheduling off`, `peephole off`) y las
  27 builds de `tools/mwccarm/`. Solo -O0/-O1 ramifican, y ahi cambia todo lo demas.
  **Consecuencia practica**: si la ROM RAMIFICA sobre un bloque de <=3 instrucciones, el bloque
  tenia >=4 al convertir y encogio despues; no lo arregla ninguna reescritura de la guarda.
  Verificado inutil sobre ese sintoma (~100 experimentos compilados en `func_0201ef9c`):
  if anidado, De Morgan, `else if`, `goto` a una o dos etiquetas, `do{}while(0)` con `break` y con
  `continue`, `switch(1)`, `for(;;)`+`break`, ternario, `<=0x7f` vs `<0x80`, `(unsigned)` en la
  comparacion, `register`, `volatile` en la tabla, puntero intermedio, `p = tbl + c` en una o dos
  sentencias, casts `(char *)`/`(int)`, indice via local / `&0x7f` / `*1` / `/1`, tabla como
  struct o como puntero global, `static inline`, stores muertos a local y a array local.
  **Lo que SI ramifica** (y es el diagnostico correcto cuando encaja): meter la sentencia
  siguiente DENTRO del bloque para que llegue a 4 instrucciones -- p.ej. `if (rango) { if
  (tbl[c]==K) f=1; } else { if (c==K) f=1; }` da el `bge` exacto de la ROM. ⚠ Pero mwcc **no
  hace cross-jumping**: duplica la cola comun en vez de fusionarla (+3 instrucciones), asi que
  solo sirve si la ROM tambien tiene la cola duplicada.

- **Predicate vs branch**: mwcc predicates a short (≤3-instr) block. To force a real
  branch, put the COMPUTING block as the taken branch:
  `if(cond_that_computes){…}else{x=0;}`. Or invert so the CALL is the early return:
  `if(cond){advance(); return;} store;` predicates the fall-through `store`;
  `if(!cond){store; return;} advance();` BRANCHES instead.
- **★ Early-return guard → `if/else` to force an OUT-OF-LINE exit block** (ov024 TCM cache
  getters 02086620/0208669c/0208670c/0208677c, all 4 fixed by this, 2026-07-16).
  Symptom: **exactly 8 bytes (2 instrs) short**, and the ROM has a tiny exit block sitting
  *after* the main body with a `b` jumping over it to the common tail:
  `cmp; bcc OUT; …body…; b TAIL; OUT: ldr r0,[pool]; pop; TAIL: …`
  while mwcc predicates it inline (`ldrlo r0,[pc]; poplo {r3,pc}`) and needs no `b`.
  The guard-return form `if(!room) return src; …body…` predicates. Writing the SAME logic as
  `if(room){ …body… } else { return src; }` reproduces the ROM's layout exactly.
  Generalises to any `if(bad) return CONST;` guard whose exit block is ~2 instructions —
  the early-return form is what invites predication, the else-form forbids it.
- **Small `switch` forces branch-form** for scattered multi-return equality dispatch:
  rewrite `if(x==A)return f(A); if(x==B)…` as `switch(x){case A: return f(A); …}
  return dflt;`. mwcc lays case bodies in SOURCE ORDER and does not dedup them — emit
  cases in the order the ROM's bodies appear. Does NOT help bit-AND guards.
- **Ternary / conditional-value order**: `x!=0 ? A : B` emits `movne A; moveq B`; the
  ROM often wants `moveq B; movne A` → flip to `x==0 ? B : A`. A `(signed char)(x==0?
  0:2)` cast = `lsl#0x18; asr#0x18` after the cond-move.
- **switch case ORDER = mwcc body layout.** Match the compiled order (read the ROM's
  branch targets); reorder source cases, don't fight it.
- **`goto`/double-negation defeats range-opt** for `x==A||x==A+1` (contiguous run):
  `if(!(x!=A && x!=B && …)){ if(inner){body; return 1;} } return 0;` keeps the
  `cmp; cmpne; …` cascade AND shares the trailing `return 0`. (Consecutive case
  values like `s==7||s==8` that mwcc range-reduces to `(unsigned)(s-7)<=1` are
  otherwise a TIE — see deferred-ties.md.)

## ★★ Q12 radians -> 16-bit angle -> sin/cos table (SOLVED and byte-verified, 2026-07-16)
Appears in at least three undone families (`func_ov137_020cd2d8` ×7, `func_ov228_020d01e8` ×6,
`func_ov228_020d0cb0` ×6). ROM shape — a 64-bit multiply, a rounding add, three shifts, two
`ldrsh`:
```
ldr r0,[pc] ; ldr r1,[pc]          ; 0x60db9391 / 0x000028be
umull r12,r3,r2,r0 ; mla r3,r2,r1,r3 ; mov r1,r2,asr #0x1f ; mla r3,r1,r0,r3
adds r0,r12,#0x0 ; adc r0,r3,#0x800
mov r0,r0,lsl #0x4 ; mov r0,r0,lsr #0x10 ; mov r0,r0,asr #0x4
mov r3,r0,lsl #1 ; add r0,r3,#1 ; mov r3,r3,lsl #1 ; mov r0,r0,lsl #1
ldrsh r3,[r12,r3] ; ldrsh r0,[r12,r0]      ; r12 = data_0203d210
```
The C that reproduces it **exactly** (verified: the whole conversion is byte-identical):
```c
idx = (unsigned short)(((long long)rad * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
sin = data_0203d210[idx * 2];
cos = data_0203d210[idx * 2 + 1];
```
Why each piece:
- `0x28be60db9391` = **65536/(2π) = 10430.3784 in .32 fixed point** — radians to a full turn.
  The `umull` + two `mla` are mwcc's signed 32×64 multiply by it.
- `+ 0x80000000000` is `0x800 << 32`, i.e. rounding — that is the `adds`/`adc #0x800` pair (the
  `adds …,#0` looks dead but is the low half of a 64-bit add; carry is always 0).
- `>> 44` = take the high word, then `>> 12`.
- The **`(unsigned short)` cast is what emits `lsl #4 ; lsr #16`** (a 16-bit angle), and the
  following `>> 4` becomes **`asr`** — not `lsr` — because a `u16` promotes to *signed* int.
  That asr-on-a-zero-extended-value is the tell that the cast is there.
- `data_0203d210` is sin/cos interleaved, 4096 entries × 2 halfwords (looks like the NitroSDK
  `FX_SinCosTable_`; confirm before naming it that).

## ★ Pin a store ahead of a computation: READ THE FIELD BACK instead of reusing the local
*(ov221 020d34cc, 2026-07-16 — worth a 7-member family, and it was the only diff)*

Symptom: right size, right instructions, but a `str` to a field lands on the wrong side of a
following computation. The ROM had `ldr r2,[pc] ; str ip,[r4,#0x70] ; smull …` — the store filling
the pool-load's delay slot — while mwcc emitted `ldr r3,[pc] ; lsr … ; smull … ; str ip,[r4,#0x70]`.
Source order was already store-then-divide; mwcc's scheduler simply sank the store.

Fix: create a real dependency by reading the value back **through the field**:
```c
ctx[0x1c] = speed;
steps = ctx[0x1c] / 136;   /* not `speed / 136` -- the reload pins the store first */
```
mwcc cannot sink the store past a load of the same location, so it stays put. Cheap to try, and
it is the natural source form anyway when the field is the thing being described.
General shape: when a store must precede something and source order alone is not enough, make the
next statement *depend* on the stored location rather than on the register that fed it.

## ★ Post-indexed `ldr rD,[base],#N`: WALK the pointer in the source, don't offset it
*(ov158 020ccdf0, 2026-07-16 — worth a 4-member family)*

ROM shape: `ldr r0,[r4],#0x18` — one instruction that reads `*ctx` AND advances `ctx` to `+0x18`,
where the advanced pointer is then the base for the following `ldm`/`stm`. The natural form
```c
owner = ctx[0];
*(Vec3 *)(owner + 0xf0) = *(Vec3 *)((char *)ctx + 0x18);   /* ldr r0,[r4] ; add r3,r4,#0x18 */
```
costs the extra `add` (+4 B). mwcc only emits the post-index if the source actually MOVES the
pointer:
```c
owner = *ctx;
ctx = (int *)((char *)ctx + 0x18);   /* -> ldr r0,[r4],#0x18 */
*(Vec3 *)(owner + 0xf0) = *(Vec3 *)ctx;
*(Vec3 *)ctx = data_...;
```
Safe when it is the pointer's last use — say so in a comment, since it reads like a bug otherwise.
Diagnostic: right size minus 4, and the ROM has a writeback `[rN],#imm` where you emitted a
separate `add`.

## ★★ Two traps that MASQUERADE as irreducible scheduler noise
*(ov000 020585e8, 2026-07-17 — a 6-member family. Both cost real time; neither is a tie.)*

**1. A wrong return type reserves r0.** Declaring a function `int` when the ROM's is `void` makes
mwcc hold r0 for the return value, so it uses r1 for scratch *everywhere* — ~30 diffs of the form
`mov r1,#1 ; str r1,[sl,#0xec]` vs `mov r0,#1 ; str r0,[sl,#0xec]`. Check the ROM: if nothing sets
r0 before `pop {…,pc}`, it is `void`. A wall of r0/r1 swaps with correct structure means this.

**2. An extra local for a value mwcc would hoist itself.** Writing
```c
unsigned short pageIdx;      /* WRONG — invents a variable the source doesn't have */
pageIdx = page;
… node->page = pageIdx;
```
instead of just `node->page = (unsigned short)page;` left SEVEN adjacent-instruction swaps spread
across the function, every one of which read like unfixable scheduling. mwcc hoists the
loop-invariant conversion into a stack slot on its own; the explicit local perturbs the schedule
around it. **If the diff is several 2-instruction swaps in unrelated places, suspect one wrong
source form rather than N scheduler ties** — real scheduling ties are local, not scattered.

## ★★ Consecutive stores through `ctx[0]` RELOAD it every time — that is ALIASING, use a local
*(ov235 020cd1f0, 2026-07-17)*

```
ROM:  ldr r2,[r4] ; str r3,[r2,#0x64] ; str r1,[r2,#0x68] ; str r3,[r2,#0x6c]
mine: ldr r1,[r4] ; str r3,[r1,#0x64] ; ldr r1,[r4] ; str r2,[r1,#0x68] ; ldr r1,[r4] ; str …
```
`*(int *)(ctx[0] + 0x64) = 0;` three times in a row makes mwcc re-read `ctx[0]` before each store:
a store through `ctx[0]` could alias `*ctx` itself, so the compiler is not allowed to keep the
value. Nothing about the addressing is wrong — this is alias analysis, and no struct or offset
form fixes it.

Fix: pull it into a local, which says the base is fixed for the run of stores.
```c
owner = ctx[0];
*(int *)(owner + 0x64) = 0;
*(int *)(owner + 0x68) = 0x1800;
*(int *)(owner + 0x6c) = 0;
```
★ Only for a RUN of stores. A single store, or reads, do not trigger it — and the ROM happily
reloads `ctx[0]` for the *next* unrelated field, so do not widen the local's scope past the run
or you will lose that reload.

## ★★ `const` on a read-only global TABLE is load-bearing — it reschedules the loads
*(ov158 020cc9e8 and its 6 twins, 2026-07-17 — the other half of the aliasing lever above)*

Reading a global table and storing the results through a **pointer parameter**:
```c
out->x = data_0203d210[idx * 2];
out->y = 0;
out->z = data_0203d210[idx * 2 + 1];
```
```
ROM:  ldrsh r1,[r2,r1] ; lsl r0,r0,#1 ; ldrsh r0,[r2,r0] ; str r1,[r6] ; mov r1,#0 ; str r1,[r6,#4] ; str r0,[r6,#8]
mine: ldrsh r2,[r3,r1] ; mov r1,#0 ; lsl r0,r0,#1 ; str r2,[r6] ; str r1,[r6,#4] ; ldrsh r0,[r3,r0] ; str r0,[r6,#8]
```
Same instruction COUNT and a correct function — the ROM issues **both loads before any store**,
mwcc sinks the second load past two stores. It reads exactly like irreducible scheduler noise, and
reordering the assignments, hoisting `s`/`c` into locals, and moving `out->y = 0` around all fail
(the store-reorder variants even change the size).

**The fix is one word — declare the table `const`:**
```c
extern const short data_0203d210[];   /* NOT `extern short data_0203d210[];` */
```
That alone took 412/412-but-permuted to MATCH, and with it 6 twins via dedupprop.

Why: with a non-`const` table mwcc must consider that the stores through `out` might *write* the
table, so the second load is pinned after them and the register pressure that follows forces the
`mov #0` early and pushes the table base to r3. `const` tells it the table cannot change, so both
loads hoist together and sin reuses r1 for the zero. **`const` is not decoration on an extern —
it is an aliasing fact that changes the schedule.** Both spellings exist in the tree
(`extern short data_0203d210[]` vs `extern const short data_0203d210[]`); when a global-table
reader is permuted only in load/store ORDER, try `const` before concluding anything.

Generalise: this and the `ctx[0]`-reload crack above are the same lever seen from both ends —
**when a diff is about the ORDER of loads vs stores, it is alias analysis, not the scheduler.**
Ask what the compiler is being forced to assume, and say the true thing (`const`, or a local).

## ★★ Load + store to the SAME >0xff byte address: use a struct field, not a cast
*(ov212 020cdd08 + ov266/ov267, 2026-07-17)*

`ldrsb` has an 8-bit offset so `+0x1c7` must split; `strb` has a 12-bit one so it must not. When
BOTH happen at the same address, mwcc CSEs the address and builds a **second partial base**:
```
ROM:  add r0,r2,#0x100 ; ldrsb r0,[r0,#0xc7] ; ... ; strbeq r1,[r2,#0x1c7]
mine: add r0,r3,#0x100 ; ldrsb r2,[r0,#0xc7] ; add r0,r3,#0xc7 ; ... ; strbeq r1,[r0,#0x100]
```
i.e. it splits 0x1c7 for the store too, just with the halves swapped (+4 B). An `owner` local does
not help — the base was already shared; it is the *address* being CSEd, not the base.

**The tell that it is CSE and not an addressing rule:** the same function's OTHER `+0x1c7` stores
emit `strb r1,[r0,#0x1c7]` directly and match fine. They differ only in not sharing an address with
a load. So mwcc can emit the direct form — the CSE is what stops it.

Fix: give the slot a struct field so each access picks its own addressing mode.
```c
typedef struct { char pad0[0x1c7]; signed char queued; } Owner;
Owner *owner = (Owner *)ctx[0];
q = owner->queued;          /* split base, as the ROM */
owner->queued = -1;         /* strb [base,#0x1c7], as the ROM */
```
Keep the plain casts for the stores that share no address with a load — mixing the two spellings in
one function is correct here, not an inconsistency.

## ★★★ "reload once, then reuse": PARTIAL volatile — mark only the FIRST read
*(func_0201a124, 2026-07-17 — kills a whole documented tie class)*

The ROM loads the same pointer twice and reuses the second; mwcc CSEs all uses into one:
```
ROM:  ldr r3,[r0] ; cmp r3,#0 ; ldrne r3,[r0] ; ldrbne r0,[r3,#0x2c] ; ... ; add r0,r3,#0x1c
mine: ldr r3,[r0] ; cmp r3,#0 ;                 ldrbne r0,[r3,#0x2c] ; ... ; add r0,r3,#0x1c
```
Marking the lvalue `volatile` is the obvious idea and it **overshoots** — every read reloads, so
you get three loads instead of two. That is where the old write-up stopped: *"Forcing the re-read
with a `volatile` lvalue makes the field/tail-call reads BOTH reload (3 loads → too long) and does
not reproduce the original's 'reload once, then reuse' shape."*

**Mark only the read you want isolated.** A volatile read cannot be CSE'd with anything; plain reads
still CSE with each other:
```c
if (*(char *volatile *)obj != 0 &&                      /* volatile: never CSE'd     */
    *(unsigned char *)(*(char **)obj + 0x2c) != 2) {    /* plain: CSEs with the next */
    func_0201e144(*(char **)obj + 0x1c, arg1 << 8, arg2);
}
```
Two loads, "reload once then reuse", byte-exact.

★ **volatile is a per-lvalue CSE barrier, not a per-object switch** — so it can express *any* split
of N uses into groups, not just all-or-nothing. The old note called this "the same re-read-vs-CSE
class as the wcscpy/strcat main helpers (see deferred list)", so **that whole class is worth
re-testing** with a partial volatile before believing it.

## ★★ `int i = 0;` as a DECLARATION-INITIALISER is emitted up front — make it a statement
*(ov022 02086e80 + 020b0ff8, 2026-07-17 — both had been parked as register-coloring ties)*

A loop counter initialised in its declaration gets its `mov rN, #0` hoisted above everything that
precedes the loop:
```
ROM:  bl f ; adds r5,r0,#0 ; bl g ; bl h ; movs r4,#0 ; <loop>     <- i = 0 after the calls
mine: movs r5,#0 ; bl f ; adds r4,r0,#0 ; bl g ; bl h ; <loop>     <- i = 0 hoisted
```
Fix — declare it bare and assign it as a **statement**, where the ROM does:
```c
int i;
int *p = (int *)NNSi_FndGetCurrentRootHeap();
func_0201ef58(func_02030d10(8));
i = 0;                    /* NOT `int i = 0;` at the top */
do { ... } while (i < 4);
```
★ **The register swap that follows is a SYMPTOM, not a second problem.** Both of these carried
write-ups blaming exactly that — "walking-base/counter r4<->r5 coloring swap", "the
call-result-parks-in-r4 limit" — and both swaps vanished once the `movs` moved. Only then does
declaration order matter: declare `i` before `p` to get the ROM's i→r4 / p→r5.

Sibling of the "declaration-initialisers so they are read before the zeroing" note in
`func_ov158_020ce288` — **decl-init vs statement is a placement lever in both directions.** Read the
ROM to see which one you want.

## ★★ `func_02020400` is the DIVIDE helper and returns BOTH results — declare it `long long`
*(ov212 020d1850 + ov266/ov267, 2026-07-17)*

**The tell: the ROM does `bl func_02020400` and then reads r1.**
```
ldm r4, {r0, r2} ; ldr r1, [r0, #0x8c] ; add r0, r2, #1
bl func_02020400 ; str r1, [r4, #4]          <- r1 AFTER a call?!
```
That looks like a decode error — a `bl` clobbers r0-r3. It isn't: func_02020400 is the runtime
divide (mwcc/NitroSDK `_s32_div_f` convention) and returns **quotient in r0, remainder in r1**,
which C sees as a packed `long long`.
```c
extern long long func_02020400(int num, int den);
q = (int)(func_02020400(a, b));          /* low word  = QUOTIENT  */
r = (int)(func_02020400(a, b) >> 32);    /* high word = REMAINDER */
```
So the ring-buffer wrap `i = (i + 1) % cap` is `ctx[1] = (int)(func_02020400(ctx[1]+1, cap) >> 32);`
and it falls out byte-exact.

⚠ **Five files in the tree declare it `extern int func_02020400(int, int)`** and only
`func_ov003_0204d1c0.c` gets it right. The `int` form is fine while you only want the quotient, so
the wrong declaration survives everywhere — **don't copy an extern from a neighbouring file here,
and if you see a store of r1 after this call, that is the modulo, not a bug.**

Generalises: **a ROM reading r1 straight after a `bl` means the callee returns 64 bits.** Same
reasoning already applies to `func_02023eb4` (the RNG) — see deferred-ties.md.

## ★★ A pooled constant used TWICE (once scaled): hold it in a LOCAL, don't spell the literal
*(ov185 020d11f4, 2026-07-17)*

The Q12 angle wrap `if (a > PI) a -= 2*PI;` with PI = 0x3244 (pooled — not an ARM immediate):
```
ROM:  ldr r0,[pc] ; str r1,[r4,#0x60] ; cmp r1,r0 ; ldrgt r1,[r4,#0x60]
                  ; subgt r0,r1,r0,lsl #1 ; strgt r0,[r4,#0x60]        <- ONE pool entry, predicated
mine: ldr r0,[pc] ; str r1,[r5,#0x60] ; cmp r1,r0 ; ble skip ; ldr r1,[r5,#0x60]
                  ; ldr r0,[pc] ; add r0,r1,r0 ; str r0,[r5,#0x60]     <- TWO pool entries, branch
```
Written as the literal `0x3244 * 2`, mwcc constant-folds it to 0x6488, finds that isn't encodable
either, and **pools it a second time** — then the block is too big to if-convert, so it branches
instead of predicating. **+12 bytes from one literal.**

Fix — bind the constant to a local and scale *that*:
```c
pi = 0x3244;
if (ctx[0x18] > pi) { ctx[0x18] = ctx[0x18] - pi * 2; }
```
Now `pi` is a *value* already sitting in the register the `cmp` loaded, so mwcc reuses it with a
barrel shift (`sub r0,r1,r0,lsl #1`), the block shrinks, and predication comes back.

★ Generalises: **when the ROM derives a constant from another pooled constant with a shift
(`, lsl #N` on a pool-loaded register), the source held it in a variable.** Two spellings of the
same literal are two pool entries; one variable is one. Watch for this wherever a pooled Q12 value
(0x1922 = pi/2, 0x3244 = pi) is used both bare and scaled.

## ★ `x += f() + k` in one statement allocates the result over the WRONG register
*(same function)*

```
ROM:  add r2,r5,r0 ; ldr r1,[r4,#0x4c] ; add r1,r1,r2     <- result takes the FIELD's register
mine: add r1,r5,r0 ; ldr r2,[r4,#0x4c] ; add r1,r2,r1     <- result takes the SUM's register
```
Same operand order, same instruction count, pure r1/r2 swap. Split the sum out:
```c
sum = func_02023eb4(d + 1) + lo;
ctx[0x13] += sum;
```
Sibling of the `x = (obj[i] += v)` crack below — both are about *which* value's register the result
lands in. When a `+=` differs only by a register swap, try moving the RHS into its own statement.

## ★★ Contiguous value test: use a `switch`, NOT an `||` chain
*(ov212 020ce50c, 2026-07-17 — unblocked a 3-member family)*

Symptom: the ROM has an explicit compare chain and you emit a range check (4 bytes short).
```
ROM:  cmp r1,#6 ; cmpne r1,#7 ; cmpne r1,#8 ; bne <else>
mine: sub r1,r1,#6 ; lsl/asr ; and #0xff ; cmp r1,#2 ; …ls/…hi
```
`if (m == 6 || m == 7 || m == 8)` gets **range-optimised** because the values are contiguous. Two
things that do NOT help: reordering them (`6, 8, 7` — mwcc sorts the set), and a shared store fed
by both arms. Writing it `!= && != && !=` fixes the compares but swaps the arms, so the short one
gets if-converted instead of branched — the two forms are mutually exclusive.

**A small dense `switch` gives the compare chain AND the right arm order:**
```c
switch (m) {
case 6: case 7: case 8:  p->f |= 8;      break;
default:                 p->f = other;   break;
}
```
Corollary worth knowing: mwcc range-optimises `||` chains but NOT few-case switches, and it *will*
build a full jump table for a switch of 8+ dense labels (ov259 020cdef8 does exactly that for
`case 10..17`, where a range test would have been three instructions). So the switch/if choice in
the source is observable in both directions.

## ★★★ MODEL IT AS A STRUCT — the single highest-yield lever for addressing diffs
*(ov000 0205721c, ov000 020552b4, ov208 020d0138, ov257 020cd370, ov255 020cd134 — five confirmations)*

Whenever the diff is in how an address is FORMED — a base hoisted out of a loop, an offset split
into two `add`s, a scaled index turned into a walking pointer — the answer is usually that the ROM's
source had a real struct there and `*(T *)(base + 0xNNN)` does not reproduce it. Raw pointer
arithmetic is an *expression* mwcc will hoist, strength-reduce and re-associate; a struct field
access is an *addressing mode* it just emits.

Confirmed three ways:
| symptom | fix |
|---|---|
| `add r4,r5,#0xc ; ldr r0,[r4,#0x400]` hoisted out of a loop, where the ROM has `ldr r0,[r5,#0x40c]` | make it a field: `((Obj *)self)->table` |
| `i * 8` strength-reduced to a walking offset, where the ROM has `ldr r0,[r0,r4,lsl #3]` | make the table an array of 8-byte structs: `->table[i].obj` |
| the whole >0xfff offset split wrong | two structs, one per base — mwcc picks the base from the INSTRUCTION's offset width (ldr 12-bit, ldrh/strh 8-bit), so `Screen` at +0x4000 reaches +0xa70 but the halfword at +0x4a78 needs `NavState` at +0x4a00 |
| a partial address (`add r1,r3,#0xc6`) hoisted out of a switch, where the ROM writes `strb r1,[r2,#0x1c6]` in the body | a field with TWO writers: mwcc CSEs the address across them. `((Owner *)ctx[0])->cur` (ov257 020cd370, ov255 020cd134). Every other dispatcher matched with the raw form — one writer does not trigger it |

Mechanism behind that last row, worked out on ov255 020cd134 (2026-07-16): the switch READS the id
with `ldrsb`, whose immediate is only 8-bit, so the base `ctx[0]+0x100` must be materialised; case 1
then WRITES the same field, and mwcc reuses that split by hoisting `ctx[0]+0xc6` to reach the store
as `[rN,#0x100]`. The ROM keeps `ctx[0]` itself live and stores straight to `[rN,#0x1c6]` — strb's
12-bit immediate covers it. Giving the store its own struct base kills the hoist. **The size tell is
exactly 4 bytes / one instruction**; with the raw form ov255 came out 4 over, with the struct exact.

★ The tell that it is worth doing: mwcc gets it RIGHT outside the loop and wrong inside (0x40c is a
perfectly good ldr offset — it only splits it once loop-invariant hoisting gets involved).

It also happens to be the right thing for the port: a named field beats `*(int *)(self + 0x40c)`.

## ★ `lsr` vs `asr` tells you the variable's signedness — read the shift, not the decompiler
*(func_ov210_020d114c, 2026-07-17 — worth 8 bytes across three packs)*

Ghidra renders the words as `int`/`uint` interchangeably, but the ROM does not: a right shift of an
`unsigned` is `lsr`, of an `int` it is `asr`. Three `lsr`s in a byte-packing block meant the source
held the value in an `unsigned int`, and declaring it `int` cost one extra instruction per pack.
Same family as the `ldrsb`/`ldrb` tell for fields (SKILL.md) — the instruction carries the type.

## ★★ A struct/vec copy with swapped ldm/stm base regs: write it FIELD-TO-FIELD
*(func_ov208_020cfc04 x3 + rescued func_ov022_0209d3a0, 2026-07-17 — a twice-parked "unbreakable tie")*

Symptom: a whole-struct copy `*(T *)(p + A) = *(T *)(p + B)` is byte-exact EXCEPT the two base
addresses land in the wrong registers — the ROM computes the SRC base into the low reg (r0 / lr),
mwcc computes the DST base first. `add r0,p,#B` vs `add r1,p,#B`, then `ldm`/`stm` follow. On
`ov022_0209d3a0` this was ruled "unbreakable" TWICE: src-local, dst-local, both orders, and a
`T tmp=*src; *dst=tmp;` temp were ALL byte-identical to the raw double-cast.

**The fix is neither a local nor a temp — it is the ACCESS FORM.** The raw double-cast
`*(T*)a = *(T*)b` and the field-to-field `obj->dst = obj->src` compile to DIFFERENT base-register
orders, and the field form is the ROM's. Put both members in one struct at their real offsets:
```c
typedef struct { char p0[0xB]; T src; char p1[A-B-sizeof(T)]; T dst; } Obj;
((Obj *)p)->dst = ((Obj *)p)->src;                 /* ROM order; the *(T*)a=*(T*)b form is reversed */
```
Proven on a 3-word vec3 copy (ov022, diff@0x28) and an 11-word matrix copy (ov208, diff@0xd, lr/ip).
Try this FIRST on any struct-copy base-order diff before believing the tie. Related still-parked:
`ov212_020d1bfc` (the note that pointed here).

## ★ Don't CACHE a value the ROM re-reads — read the field fresh at each use
*(func_ov208_020d1e84 x3, 2026-07-17 — worth the whole family)*

Mirror of the entry below. A function that acquires a value, stores it, and later passes it to a
call: `int t = acquire(); state[4] = t; ... f(t + 0x190, ...)`. Caching `t` makes mwcc keep it live
across the whole body (in a callee-saved register → an EXTRA entry in the push list, e.g. `r7`), and
the function comes out a couple of instructions short with the wrong `push`. The ROM instead just
**re-reads `state[4]`** at the use site (it equals `t`, and no aliasing call sits between). Write the
use as `f(state[4] + 0x190, ...)`, NOT the cached local. The tell: same code, but your `push` has one
more register than the ROM and the size is a hair short. (mwcc will re-read the field as long as no
intervening call could alias it; here the only writes between are to other slots.)

## ★ Assign a hoisted local AFTER the call whose argument it duplicates
*(func_ov125_020cd27c, 2026-07-17 — worth exactly the last 4 bytes)*

`owner = (int *)ctx[0]; ... f(ctx[0], &d);` makes mwcc CSE the two, keep `owner` in a callee-saved
register and pass it with an extra `mov r0, r4`. The ROM just loads `ctx[0]` **twice** — once for
the call, once into the register it keeps. Moving the local's assignment to *after* the call
reproduces that: the value is still live afterwards so it still gets a callee-saved register, but
the call now loads its own copy.

★ The tell: an extra `mov rN, rM` immediately before a `bl`, where the ROM has a plain `ldr`.

## ★★ Declaration order IS the callee-saved allocation order (r4, r5, r6, r7, r8)
*(ov000 0205721c, 2026-07-17 — a 6-member family; measured exactly, not inferred)*

Symptom: every instruction matches, but two registers are swapped. Don't hunt for a cause — it is
the declaration order, and the mapping is direct. Measured on a function with 5 long-lived locals:

| declaration order | allocation |
|---|---|
| `slot, i, j, acc, …, ok` | slot=r4, i=r5, j=r6, acc=r7, ok=r8 |
| `ok, slot, i, j, acc, …` | ok=r4, slot=r5, i=r6, j=r7, acc=r8 |
| `ok, i, j, acc, …, slot` | ok=r4, i=r5, j=r6, acc=r7, slot=r8 ✔ (the ROM) |

So: read the ROM's r4..r8 assignment off the disassembly, then declare the locals **in that order**.
Locals that end up in fp or on the stack do not consume a slot, so ignore them when counting.
This took three tries only because the first two were guesses; reading the map off first makes it
one edit.

## ★ Jump tables: the case ORDER in the source is observable
*(ov228 020cf47c, 2026-07-17 — matched first try, ×5)*

Dense cases (0..N) give a real table: `cmp r1,#N ; addls pc,pc,r1,lsl #2` followed by N+1 `b`
entries in INDEX order, then the case bodies. The `b` at the `addls`+4 slot is the default.

The table is index-ordered, but **the bodies are laid out in SOURCE order** — so if the ROM's
bodies are not in numeric order, the source's `case` order is not either, and you must reproduce
it. In 020cf47c case 3's body sits between case 11's and case 12's, so the source really is
`case 0,1,2,4,5,6,7,8,9,10,11,3,12,13` (someone added case 3 late). Read the branch targets off
the table and order the cases to match; do not tidy them into numeric order.

## ★★ A counter's TYPE decides whether mwcc folds it — and folding silently flips branch->predicate
*(ov231 020cdaa8, 2026-07-17 — a 5-member family)*

Symptom: two structurally identical `if` blocks, and the ROM emits the SAME code for both, but
yours matches the second and not the first — the first comes out short AND predicated:
```
ROM  (both blocks): cmp r0,#0 ; beq skip ; add r0,r6,#1 ; mvn r1,#0 ; strb r1,… ; and r6,r0,#0xff
mine (1st block):   cmp r0,#0 ; mvnne r0,#0 ; strbne r0,… ; movne r6,#1
mine (2nd block):   matches the ROM exactly
```
Cause: with `int count = 0;` right above, mwcc knows the value at the FIRST block and folds
`(count + 1) & 0xff` to the constant `1` — which also shrinks the block enough to trip
if-conversion, costing the `beq` too (so you lose 2 instructions, not 1). At the second block the
value is unknown, so nothing folds and you get the branch for free.

Fix: declare it `unsigned char count;` and write `count++`. The u8 mask is not foldable the same
way, both blocks emit `add`/`and #0xff`, and the branch comes back on its own. **Do not chase the
predication directly** — it is a symptom of the fold, not an independent problem.

Related, same function: a two-way constant select emits its arms in condition order, so
`f() == 0 ? -1 : 1` gives `mvneq r0,#0 ; movne r0,#1` while `f() != 0 ? 1 : -1` gives them
reversed. Match the ROM's first predicated instruction.

## ★★ Aggregate INITIALISER != field assignments; and declaration order fixes the init order
*(ov231 020cd920, 2026-07-17 — a 5-member family; took two steps, both worth knowing)*

**Step 1 — the address materialises.** Zeroing a stack struct field-by-field stores against `sp`;
the ROM computes the struct's address into a register and stores through it (one instruction more,
so the size is short):
```
mine: mov r1,#0 ; str r1,[sp,#0xc] ; str r1,[sp,#0x10] ; str r1,[sp,#0x14]
ROM:  add r2,sp,#0xc ; mov r1,#0 ; str r1,[r2] ; str r1,[r2,#4] ; str r1,[r2,#8]
```
The fix is the **aggregate initialiser** — `VecFx32 offset = {0, 0, 0};`. Things that do NOT work
(each cost a compile): an explicit `VecFx32 *p = &offset;` pointer local, and a `static inline
VEC_Set(VecFx32 *p, …)` helper — mwcc folds the pointer straight back to `sp` in both.

**Step 2 — the initialiser then runs too early.** With `int *ctx; … ctx = *(int **)(self+4);` as a
statement, the zeroing is emitted BEFORE `mov r5,r0 ; ldr r4,[r5,#4]`. The ROM has ctx first, so
give ctx its own initialiser and put it ahead of the struct's:
```c
int *ctx = *(int **)(self + 4);      /* runs first */
VecFx32 offset = {0, 0, 0};          /* then this */
VecFx32 pt;                          /* still reverse decl order: pt@sp+0, offset@sp+0xc */
```
Declaration-initialisers run in declaration order, so this is a free lever on emission order that
plain assignments do not give you.

## ★★ Three shapes that show up together in decision trees (all proven on ov228 020cf150, ×5)
A 480 B AI decision tree with only 4 relocs went byte-exact once these three were right. They
recur, so check for all three whenever a function is mostly `cmp`/`mov?`/`strb?` chains:

**1. Ternary store → ONE `strb`; the ROM wants a store per arm.**
```
mine: movlt r1,#6 ; movge r1,#8 ; strb r1,[r0,#0x1c7]     <- p->f = c ? 6 : 8;
ROM:  movlt r1,#6 ; strblt r1,[r0,#0x1c7] ; movge r1,#8 ; strbge r1,[r0,#0x1c7]
```
Write the `if/else` with the assignment duplicated in each arm.

**2. Two `return 0` paths SHARE one exit block.** `return X != -1;` emits `movne/moveq/pop`. If
the ROM has `movne r0,#1 ; popne ; mov r0,#0 ; pop`, the zero-return is shared with an earlier
guard's branch target — so write the last one as a fall-through:
```c
if (guardOk) {            /* the guard tested the POSITIVE way, so `return 0` lands out-of-line */
    ...
    if (X != -1) return 1;
}
return 0;                 /* one block, branched to from the guard AND fallen into from above */
```

**3. Indexed base address — the C form decides, but ONLY inside a loop does it strength-reduce.**
For `ldr rX,[base + i*4]` with a constant field offset, pick by what the ROM emits:
| ROM | write |
|---|---|
| `add r0,r2,r1,lsl #2 ; ldr r0,[r0,#0x3c0]` | **in a loop:** `((int *)base)[i + 0xf0]` (fold into the word index) · **outside one:** `*(int *)(base + n * 4 + 0x3c0)` |
| `add r2,r3,#0x3c0` hoisted, `ldr r0,[r2,r1,lsl #2]` | `((int *)(base + 0x3c0))[i]` |
| `add r2,r2,#4` walking pointer | `*(int *)(base + i * 4 + 0x3c0)` **with i a loop induction variable** |

★ The strength-reduction to a walking pointer only happens when the index is a **loop induction
variable** (ov228 020cf150). With an index that is not — e.g. a field read, ov231 020ce210 — the
same `*(int *)(base + n*4 + off)` source gives the fold instead. And there, the word-index form
(`((int *)base)[n + 0xe3]`) does NOT fold: it emits `add r0,r0,#0xe3 ; ldr r0,[r1,r0,lsl #2]`.
So the two forms swap roles depending on whether you are in a loop. Measure; don't assume.

★★ **The SAME array, indexed by the SAME `i`, can need BOTH forms in one function** (ov228 020d1a9c
x4, 2026-07-17). A `do{}while` scans `((int*)*state)[i+0xf0]` at the LOOP-CONDITION site — that must
be the fold form (`add r0,base,i,lsl#2 ; ldr [r0,#0x3c0]`) or it strength-reduces to a walking
pointer. But the SAME node access on the BREAK path (the `if`-body that runs once then `break`s,
here feeding a call arg) is a single use, so it takes the outside-loop byte-offset spelling
`*(int *)(*state + i*4 + 0x3c0)`; the fold form there instead collapses to one indexed load
`ldr [r0,r3,lsl#2]` (mwcc precomputes `r3=i+0xf0`) and loses the ROM's two-add shape. Write the two
occurrences differently even though they are the same value — the loop body and the break path are
different scheduling contexts.

★★ **When the offset is NOT a multiple of the element size, the fold is IMPOSSIBLE — declare the
array as a STRUCT MEMBER** *(2026-07-17, ov212 020ce36c ×3 and 020d1200 ×3, both matched on the
first try with this)*. `((T *)base)[i + K]` only exists when `off / sizeof(T)` is a whole number.
It usually is (`0x4cc / 4 == 0x133`), and then the fold is the answer — but:
- `0x3cc` with a **16-byte** element is `60.75`, and
- `0x40` with a **12-byte** vec3 is `5.33`.
There the two losing forms are the only ones people reach for:
| form | result |
|---|---|
| `*(T *)(base + i * 16 + 0x3cc)` | mwcc strength-reduces into a **second byte-offset induction variable** — +8 B *and* an extra register in the push list |
| `((T *)(base + 0x3cc))[i]` | pre-offset base: hoists the `add` out of the loop, wrong shape |
| **`((struct Ctx *)base)->mats[i]`** | ✅ the ROM's **two-add** form: `add r1,r0,ip,lsl #4 ; add r4,r1,#0x3cc` |
```c
struct Ctx { char pad[0x3cc]; struct blk16 mats[16]; };   /* the array AT its real offset */
((struct Ctx *)*self)->mats[i] = src;
```
The tell is the ROM keeping the **base** in the walking register and re-adding the field offset
every iteration (`mov lr,r3` + `add r5,lr,#0x40` inside the loop, `add lr,lr,#0xc` at the foot).
A pre-offset walking pointer (`add lr,r3,#0x40`) is exactly **1 instruction short**. Generalises the
`[i + 0x133]` rule: *index from the object base, and let the STRUCT carry the offset* — the fold is
just the special case where the offset happens to divide.

## ★★ A 0 that later BECOMES a flag is ONE variable, not two constants
*(ov038 020b34f0 ×4, 2026-07-17 — matched the moment this was spelled right)*

Symptom: everything matches, **including the register mapping**, but the PUSH LIST is wrong —
the ROM saves one more callee-saved register than you do (and pushes r3 for alignment where
the ROM does not, or vice versa).

Cause: the ROM has a single value that starts at 0, gets stored, and is then conditionally
overwritten with the flag — so it is **live across a call** and earns a callee-saved register.
Writing the two uses as independent constants leaves both as scratch temps: same size, same
instruction count, wrong push list.
```c
/* ✗ same size, both scratch */            /* ✅ one value, callee-saved (r8) */
*p = 0;                                    int flag = 0;          /* OUTSIDE the guard */
f(self, 0xc8, 4);                          *p = flag;
g(self, q, mode == 0x32);                  f(self, 0xc8, 4);
                                           if (mode == 0x32) flag = 1;
                                           g(self, q, flag);
```
The ROM's tell is the pair `mov r8,#0` … `moveq r8,#1` on the SAME register, with a `bl`
between them. Where the `mov r8,#0` sits relative to the guard tells you the variable's scope:
here it is emitted before the `cmp`, i.e. initialised outside the mode-changed `if`.

**Read the push list as a fact about live ranges, not as noise.** It is the cheapest signal in
the diff: one extra pushed register = one value you have modelled as two, or vice versa. Same
lesson from the other side in `ov127_020ccb10`, where a pointer declared in the prologue was
hoisted INTO a callee-saved register (+1 in the push list) and had to be scoped to its block.

## ⛔ Declaration order does NOT drive allocation when every value is live throughout
*(measured three independent times on 2026-07-17 — record this before re-permuting anything)*

The decl-order entries in this file are real: reordering declarations cracked
`TickTagTrackerNodes`, and `func_ov212_020cc54c`'s aggregates obey "first-declared = highest
address" exactly. But the rule has a boundary, and three functions hit it the same day:

| function | what differs | decl orders tried | result |
|---|---|---|---|
| `ov048_020b34cc` (×4) | a 3-way callee-saved rotation (ROM `id=r5 mode=r6 self=r7`) | 4 | **byte-IDENTICAL** |
| `ov038_020b4234` (×4) | `self` in r7 vs the ROM's r6 | 4 + naming both zero temps | **byte-IDENTICAL** |
| `ov000_02057dc4` (×7) | four spilled scalars in different stack slots | 5 | **byte-IDENTICAL** |

The pattern: **declaration order reaches AGGREGATE stack layout and values with distinct,
short live ranges. It does not reach a permutation among scalars that are all live across the
whole function** — there the allocator orders by its own criteria and the source cannot name
them. `ov000_02057dc4` adds the corollary: **spill SLOTS are not decl-order driven either**
(that rule is for aggregates; spilled scalars are the allocator's business).

So when a diff is "N registers rotated, everything else identical", permuting declarations is
already a measured dead end — go looking for something that changes how many values are live
or for how long. Do NOT read this as "it is a compiler tie": three of that day's four cracks
came out of functions filed under exactly that label.

## ★★★ A `pop` INSIDE a table slot means there is NO `default:` and NO `case 0:`
*(SOLVED 2026-07-17 on ov041 020b40f8 ×4; the same shape gates ov034/046/048 and most of the
enemy-overlay dispatchers)*

`tools/switchorder.py` prints **"INLINE IN THE TABLE SLOT"** when a jump-table slot holds a
real instruction instead of a branch:
```
addls pc, pc, r0, lsl #2
pop {r4, r5, r6, pc}      <- the out-of-range fall-through
pop {r4, r5, r6, pc}      <- case 0's SLOT: a bare epilogue, no branch
b   #0x90                 <- case 1
```
**That is not a peephole you have to coax — it is what mwcc emits when the case simply is not
written.** Omit `default:` and omit the returning `case 0:`; let both fall through the table to
the function's implicit end. The slot then holds the epilogue itself.

Measured on ov041 (ROM = 300 B):
| source form | result |
|---|---|
| **no `default:`, no `case 0:`** | **300 — MATCH** |
| `case 0:` merged with `default: return;` | 304 |
| `case 0: return;` and `default: return;` separate, either order | 308 |

Corollary that comes with it: **what looks like a tail after the switch is often the last
case's body, with earlier cases falling INTO it.** ov041's "tail" is state 2's body and `case 1`
falls through to it with no `break`. If the switch has no default and code appears to follow it,
suspect that first.

`func_ov022_020b1c4c` (matched long ago) says it in its own comment: *"State 0 (and anything
above 4) falls through the jump table to the shared return, so it needs no case label."*

★★ **HOW THIS WAS FOUND, because the method matters more than the crack.** A minimal reproducer
said mwcc *never* inlines the pop — every table slot came out as `b`. That was a FALSE NEGATIVE
and it would have been recorded as "a compiler-version difference". What settled it was scanning
the corpus for the positive form: **of 343 matched real-C functions containing a dense switch,
333 have branch-only tables and 10 have an inline slot** — proof mwcc can do it, and ten worked
examples to read. When a reproducer says "the compiler cannot", grep the matched corpus for the
shape before believing it.

## ★★★ Dense switch: the DISASSEMBLY HANDS YOU THE SOURCE ORDER of the cases
*(ov005 0205b100 ×4, 2026-07-17 — 476/476 bytes and 119/119 instructions on the FIRST compile)*

A dense switch compiles to `cmp rX,#N ; addls pc,pc,rX,lsl #2` followed by one branch per
case value. Two different orders are in play and conflating them is why these look hard:
- the **jump table** is indexed by the case VALUE, so its order is forced and tells you nothing;
- the **case bodies** are laid out in **source order**.

So: read each table entry's target address, sort the targets, and you have recovered the order
the cases were written in. It is frequently NOT 0,1,2,… For 0205b100 the bodies came out in the
order of the *remap functions they call* (02058988, 02058bb4, 02058de0 … = RemapCharCode00, 01,
02 …), which is the case sequence
`1, 6, 17, 18, 7, 8, 9, 10, 16, 11, {0,14,19}, 3, 5, 12, 4, 13, 2, 15, default`.
Written in that order the entire 476-byte layout — table, bodies, shared bodies and the
fall-through default — was byte-exact immediately.

Recipe (capstone): collect `b` targets in `[table_start, table_start + 4*(N+1))`, map
`case_value = (offset - table_start) / 4`, then order the case labels by target address. Cases
sharing a target share a body (`case 0: case 14: case 19:`); the `b` before the table is the
`default`.

**This is the lever for the 9 dense dispatchers `genmove.py` refuses** (ov185/186/187, ov237,
ov245 020ccfa8, ov253 ×2, ov254, ov258) — they were filed as "each carries extra code; hand
work", but the layout half is mechanical once you read the order off the table.

## ★★★ `(int)&local` CSEs the address; the REAL POINTER TYPE rematerialises it
*(ov212 020cfeb4 ×3, 2026-07-17 — matched the moment the extern was fixed)*

Symptom: a stack address passed to **two or more calls** gets hoisted into a callee-saved
register once (`add r5,sp,#0` … `mov r2,r5` per call), where the ROM recomputes
`add r2,sp,#0` at every call site. Costs 4 B per extra call **and an extra register in the
push list** (`{r3,r4,r5,r6,lr}` vs the ROM's `{r4,r5,lr}`).

Cause: **the extern's parameter type**, which is a free choice you are making without noticing:
```c
extern void f(int obj, int a, int b, int c);        /* ✗ caller writes (int)&v -> CSE  */
extern void f(int obj, int a, struct vec3 *v, int c); /* ✅ caller writes &v -> remat   */
```
An `int` parameter forces an explicit `(int)&v` cast at the call, and mwcc treats that
integer-valued expression as a common subexpression worth keeping in a register. Given the
pointer type it rematerialises the frame address per call, exactly like the ROM.

⚠ **The callee's own definition does not have to agree, and here it does not:** the matched
`func_ov212_020d0a48` spells that parameter `int b`. It matches on its own side either way,
because the type is invisible in the callee's code — the same reason a callee cannot settle its
own arity. **The caller's extern is what steers the caller.** So when a diff is "an address is
cached where the ROM recomputes it", look at how you declared the callee, not at the loop.

## ★★ `max = min + extent`: derive it from the STRUCT MEMBER, not from the local
*(ov301 020cbfc4, 2026-07-17 — took a 396 B miss to an instruction-perfect 408/408)*

Symptom: the ROM materialises a constant at **runtime** with a two-`add` chain off a pooled
literal (`ldr r6,[pc,..] ; add r0,r6,#0xd3 ; add r2,r0,#0x1d00`), while your C emits ONE clever
instruction (`rsb r2,r6,#0xf00`) and comes out short. Each such value costs you 4 bytes.

Cause: mwcc **constant-folds `local + K` when the local is an initialised constant**, then
materialises the folded literal by whatever 1-instruction derivation it can find from another
live constant. Reading the value back **off the struct member you just stored** does not fold:
```c
struct blk6 s;               /* a bounding box: 3 (min, max) pairs */
s.a = iVar1;  s.b = 0x17;  s.c = uVar4;
s.d = s.a + 0x1dd3;          /* ✅ runtime add-chain, matches   */
s.e = s.b + 0x1c27;          /*    (s.d = iVar1 + 0x1dd3 folds  */
s.f = s.c + 0xd64;           /*     to 0xee9 and loses 4 bytes) */
```
Measured both ways per field: spelling `s.d` or `s.f` off the local is −4 B each; spelling the
result as a plain literal (`s.e = 0x1c3e`) is the same bug in its most obvious form.

**Recognising it is the useful half:** a struct of `{a, b, c, a+da, b+db, c+dc}` is a min/max
extent pair, and the ROM builds the max from the min *as stored*. When you see paired pooled
literals plus short `add` chains with non-encodable deltas, reach for this before touching
declaration order.

## ★ `call() - expr`: mwcc evaluates the NON-call operand first — split it into two statements
*(ov228 020cfc4c, 2026-07-17 — a 6-member family)*

Symptom: a load is hoisted **above a `bl`** into a callee-saved register, where the ROM reloads it
*after* the call into a scratch register. Same instruction count, so the size still matches.
```
mine: add r0,sp,#0 ; ldr r6,[r4] ; mov r1,r0 ; bl f ; ldr r2,[r6,#0x3bc] ; ldr r3,[r6,#0x4a0]
ROM:  add r0,sp,#0 ; mov r1,r0 ; bl f ; ldr r3,[r4] ; ldr r2,[r3,#0x3bc] ; ldr r3,[r3,#0x4a0]
```
Cause: in `x = f(...) - (a + b);` mwcc evaluates the right-hand operand **first**, so the loads for
`a`/`b` are emitted before the call — and since they must then survive it, they land in
callee-saved registers. Fix — force the call to go first by splitting the statement:
```c
range = func_01ff8d18(&d, &d);
range -= *(int *)(ctx[0] + 0x4a0) + *(int *)(*(int *)(ctx[0] + 0x3bc) + 0x80);
```
Do NOT waste a compile blaming a cached local first (a `target` local was the obvious suspect here
and removing it changed nothing — the operand order was the whole story).

## ★ Stack-local LAYOUT: STRUCT locals lay out in pure REVERSE decl order
*(ov000 02058928, 2026-07-16; ov228 020d1ecc + 020d1240, 2026-07-17)*

**Diagnostic (reliable): `sub sp,#N` is right but every `add rN,sp,#imm` is wrong.**

| decl order | observed memory order | source |
|---|---|---|
| `MtxFx33 mtx; VecFx32 d` | `d@0, mtx@0xc` = **2, 1** | ov228 020d1ecc |
| `VecFx32 vec; Anchor a; MtxFx33 mtx` | `mtx@0, a@0x24, vec@0x34` = **3, 2, 1** | ov228 020d1240 |
| `char list[0xc]; char state[0x100]; char work[0x1e0]` | `list@0, work@0xc, state@0x1ec` = **1, 3, 2** | ov000 02058928 |

**For struct locals it is pure reverse** — two independent cases (2 locals and 3 locals), so
declare them back-to-front and the frame comes out right first time:
```c
MtxFx33 mtx; Anchor anchor; VecFx32 vec;   /* -> vec@sp+0, anchor@sp+0xc, mtx@sp+0x1c */
```
The one case that does NOT fit is the `char` arrays (1, 3, 2), so the array rule is something
else — treat that row as unexplained rather than as a competing rule. If a flip does not fix it,
the frame is telling you something else is wrong; do not permute blindly past the first retry.

For several big stack buffers, mwcc puts the **first** declared local at `sp+0` and then lays the
remaining ones out **backwards**. With
```c
char list[0xc]; char state[0x100]; char work[0x1e0];   /* decl 1,2,3 */
```
you get `list@sp+0`, `work@sp+0xc`, `state@sp+0x1ec` — i.e. memory order 1, 3, 2.
The ROM wanted `list@0, state@0xc, work@0x10c`, so the source must declare
```c
char list[0xc]; char work[0x1e0]; char state[0x100];   /* decl 1,3,2 -> memory 1,2,3 */
```
**Diagnostic:** every `add rN, sp, #imm` is wrong but the prologue's `sub sp,sp,#N` is right — the
frame is the correct SIZE, the offsets are just permuted. Read the ROM's offsets, sort the buffers
by them, then write the decls as first-then-reversed. (Do not confuse with the register decl-order
crack below; this one is about frame offsets.)

## Register / declaration order

- **Which local lands in r1 vs r2 follows DECLARATION ORDER.** If the diff is a pure
  reg swap between a `flag`/`ready` local and a cached `int obj=*(owner)`, declare
  `int flag=0;` BEFORE `int obj=…;` (the ROM inits the flag reg first). Rescued
  020d04b0 (r3↔ip swap). Try this on ANY flag/obj reg-swap before deferring.
- **Predicated-flag guard: declare the flag local FIRST.** For `int ok=0; if(cond)
  ok=1; if(!ok) return;` (ROM = `mov r2,#0` upfront, `moveq r2,#1` in the cond, `cmp;
  popeq`), if mwcc emits a merge-`mov r,#0` + extra `beq` at the a==0 join instead of
  hoisting the zero-init (+4B), declare `ok` as the VERY FIRST local — before the
  `owner`/other locals it guards on. Then mwcc emits `mov r2,#0` before the loads and
  the a==0 branch skips straight to the test. Fixed ov237_020d03e0.
- **result-var declared BEFORE a call → callee-saved across the `bl`.** When the ROM
  inits a return value before a call and finalizes after, declare + default it before
  the call so it lands in r4/r5; decl order among callee-saved locals picks r4 vs r5.
- **Pre-load a 2nd-call arg into a local before the 1st call** to force it into a
  callee-saved reg (the ROM keeps it in r6 across the 1st call). e.g.
  `int save=*(b+0x460); f(…); g(save);` matched the emitter-feed handlers.
- **Cached pointer locals fix arg-reload regalloc**: `int *va=(int*)p4;` then `va[0]`
  holds the pointer in a callee-saved reg vs reloading a stack arg each use.
- **Struct-wrap frame locals to control stack slot order** (HIGH YIELD for loops that
  pass `&buf`/`&count` at fixed sp offsets): pack ALL frame locals into ONE
  `struct { int pt[2]; int count; int rect[4]; } f;` in memory order — struct members
  ARE laid out in declaration order, so the block lands contiguous with matching
  offsets.
- **Multiple simultaneously-live temps take callee-saved regs in REVERSE decl order.**
  When two+ locals are all live across the same call(s) and none is used before the
  others (e.g. header offsets `b=buf[1]`, `c=buf[2]` both added to `buf` at later call
  sites), mwcc assigns the LAST-declared to the LOWEST free callee-saved reg. To get
  `b→r6, c→r7` (b used first), declare `c` BEFORE `b`: `int a=buf[0], c=buf[2], b=buf[1];`.
  mwcc still emits the loads in address order, so only the reg assignment flips.
  Fixed LoadAndInitResourceSections. (Contrast the r1/r2 arg case above = FORWARD order.)
- **Force a redundant in-`if` reload with `*(volatile T*)`**: when the ROM reloads a
  field it just stored (`str; cmp; ldreq; addeq; streq` — a `x++; if(x==1) x++;`
  skip-value where the second `x` is re-read) and mwcc CSEs it (−4B), write only that
  RHS read as `*(volatile int*)(p+off)`: `if (*(int*)(p+off)==1) *(int*)(p+off) =
  *(volatile int*)(p+off) + 1;`. Forces the ldr without touching the store. Fixed the
  ov256_020ce778 c634 handler. (Full `volatile` on the lvalue over-reloads elsewhere —
  volatile-cast ONLY the one read that must reload.)
- **obj reload vs CSE**: the ROM reloads `*(owner)` after a store to `*(owner)+off`
  (can't prove non-alias) but CSEs it within a run with no intervening store. Write
  `*(int*)owner` fresh at each "section" and let mwcc CSE/reload naturally; cache
  `int obj=*(owner)` only where the ROM keeps it in one reg across uses.

## Offset / addressing (ldrsb/ldrsh split at >0xff)

- **★ Base beyond 0xfff: hold it in a POINTER local, and the pointer type is load-bearing.**
  *(ov024 02082e04 — worth 24 B then 12 B more, 2026-07-16.)* A control block at `player+0x8000`
  with fields at `+0xbd8…+0xbe8`. The ROM keeps `add r2,r4,#0x8000` and addresses
  `str r1,[r2,#0xbd8]` (0xbd8 < 0xfff, so it encodes fine).
  - Writing `*(int *)(player + 0x8bd8) = 2;` (one folded constant) makes mwcc materialise the
    whole address for every **STORE** — `add r0,r4,#0x3d8 ; add r2,r0,#0x8800 ; str r1,[r2]` —
    while still folding the **LOADS** correctly (`ldr r0,[r2,#0xbd8]`). That store/load asymmetry
    is the tell. **+24 B.**
  - Splitting it into a local helps but is not enough if the local is an `int`:
    `int ctl = player + 0x8000; *(int *)(ctl + 0xbd8) = 2;` still splits the stores
    (`add r1,r2,#0x3d8 ; str r2,[r1,#0x800]`) because mwcc picks the base's register for the
    stored constant and has to save the address. **+12 B.**
  - `char *ctl = (char *)(player + 0x8000);` — a real **pointer** — gets the ROM's single
    `str r1,[r2,#0xbd8]`. Instant right size.
  Rule: when the ROM holds `base + 0x…000` in a register and uses ≤0xfff offsets off it, model
  that base as a `char *` local. Don't fold, and don't use an integer.

  ⚠ **But the two forms can be MIXED in one function — count the derivations first.**
  *(ov024 02082960, 2026-07-16.)* The ROM there derives `player + 0x8000` **twice**: once into r1
  (kept for the counter loads AND its store) and again into r0 (`add r0,r0,#0x8000 ; ldrb
  r0,[r0,#0xbe2]`) for one byte read — even though r1 already held that exact address. Using the
  `ctl` local for everything is one instruction *cheaper* than the ROM and lands 4 B short; the
  matching source keeps `ctl` for the counter and leaves the byte read FOLDED
  (`*(u8 *)(player + 0x8be2)`). So: count `add rN, base, #0x…000` occurrences in the ROM and give
  each one its own source form. A redundant-looking derivation is a fact about the source, not
  noise to optimise away.

- `ldrb`/`ldrh`/`strb`/`strh` take a 12-bit offset (≤0xfff); the SIGNED
  `ldrsb`/`ldrsh`/`ldrd` take only 8-bit (≤0xff). A signed-byte read at offset >0xff
  splits (`add base,#0x100; ldrsb [.,#rem]`). **Dest signedness matters on a copy**:
  `*(signed char*)dst = *(signed char*)src` keeps the ROM's split ldrsb;
  `*(unsigned char*)dst = *(signed char*)src` lets mwcc collapse to a single `ldrb`
  (−4B). Match the ROM's signedness on both sides.
- **struct-field form forces a DIRECT strb at large offset** (store must stay direct
  even when a nearby read splits the base): `((struct{signed char _pad[0x1c7]; signed
  char f;}*)*state)->f = K;` un-hoists the split base. Needed for `state[0x1c6/0x1c7]`
  const stores in dispatchers.
- **`x <= N` beats `x < N+1`** and **`x >= N` beats `x > N-1`** when N is
  ARM-encodable but the neighbour isn't (avoids a pool load). e.g. `mag <= 0x1800`
  not `< 0x1801`; `X >= 0x2000` not `> 0x1fff`.
- **`(x & K) <= 0`** (signed) forces `and; cmp; movle` where `== 0` gives the short
  `tst; moveq`.
- **`int neg = -1; if(x==neg)`** forces `mvn r?,#0; cmp` over the 1-instr `cmn r?,#1`.
  Deriving `-1` from a live `0` (`sub r5,r1,#1`) or `1` (`sub r5,r3,#2`) also happens
  — writing `=0/=1` then `=-1` in sequence lets mwcc derive it.

## Loops (index vs induction pointer)

- **Array-subscript keeps index addressing; offset-arithmetic strength-reduces to a
  pointer walk.** `((int*)(base+K))[i]` → the ROM's `add rN, base, i, lsl#2; ldr
  [rN,#K]` (i stays a live counter). `*(int*)(base + i*4 + K)` strength-reduces to an
  induction pointer (`add ip,ip,#4` each iter, +4B). BUT this SR is sometimes an
  unsteerable tie (see deferred-ties.md) — check both forms.
  **Re-confirmed 2026-07-16 on ov024 0208589c** (6-iteration plane-pointer refresh), worth 8 B
  there and it IS steerable: `*(int *)(base + i*4 + K)` gave `mov r4,r5` + `add ip,ip,#4`;
  `((int *)(base + K))[i]` gave the ROM's `add r3,r5,r4,lsl#2 ; ldr r1,[r3,#0xac]` with `i` alive
  in r4.
  ⚠ **…but it is CONTEXT-DEPENDENT, not a law** (ov024 020859d4, same day, a simpler 6-iteration
  ring-cursor loop). There the subscript form yielded the *opposite*: `add r3,r5,#0xac` hoisted
  out of the loop + `ldr [r3,r4,lsl#2]` — right size, wrong half of the addressing mode. All three
  forms measured: subscript → hoisted base + register offset; `base + i*4 + K` → induction (+4 B);
  a `static inline` slot helper → induction (+4 B). None produced the ROM's shape. So: try all
  three and MEASURE; do not assume the subscript form wins because it did last time. Same function: reach the parallel arrays as `slot_base + 0x70/0x78/0x80` (one derived
  base + immediate offsets, the ROM's shape) rather than `ctx + 0x70 + slot*4` (three bases +
  register-offset loads, +12 B) — a `static inline` returning the base reproduces the ROM's
  once-per-statement re-derivation.
- Pair with `unsigned short` loop limit for a `ldrh` bound, `if(x>=K)break;` (not a
  mid-loop `return`, so it branches to the shared epilogue).
- **Struct-pointer beats raw-cast in a reload-per-iter loop** (THUMB especially).
  When a loop reloads two+ base fields each iter (`ldr [ctx,#0x10]` base, `ldr
  [ctx,#0x34]` count — reloaded because the in-loop call may mutate `*ctx`), raw
  `*(int*)(ctx+0x34)` lets mwcc hoist `ctx+0x34` into a persistent pointer reg and
  SPILL `ctx` to the stack (+8B, extra callee-saved). Cast ctx to a `struct *` ONCE
  and use real field access (`ctx->count`, `ctx->items[i]`) → forces `[base,#imm]`
  immediate-offset addressing, keeps ctx in one reg (r5), i in r6, `i*stride`
  induction in r4. Element passed to the callee lands in r1 for free (the field-read
  address reg) — declare the callee `(ctx, element)` even if Ghidra shows one arg, so
  the live element ptr is reused as arg2 (no extra `mov`). Fixed the
  SweepReleasePendingElements / SweepFreeElementBuffers THUMB families.

## Types / misc

- **`int` not `unsigned char` for a counter/accumulator** — a byte local emits a
  spurious `and #0xff` after every `++`.
- **`long long` return** for a two-word `ldr r2,[p,#K]; ldr r1,[p,#K+4]; mov r0,r2`
  tail: `return *(long long*)(p+K);`.
- **64-bit OR/AND**: `*(u64*)p |= 0x200000000LL` → `orr low,#0; orr high,#2`. Read
  the ROM to see which half carries the real immediate; bit N≥32 = `1LL<<N`. The
  lone `orr rX,#0` / `and rX,#0` next to a real one is the OTHER half of a 64-bit op
  (NOT a dead `|0` macro).
- **Atomic struct copy defeats dead-store elimination**: when the ROM keeps a store
  immediately overwritten before any read, model the fill as an aggregate copy:
  `struct hpair{u16 a,b;} buf = *(struct hpair*)&data; buf.a = X;` — mwcc won't DSE
  the `.a` half across the struct copy. (Two scalar assigns let -O4 kill the dead one.)
- **`const`-qualify a shared read-only global** so mwcc hoists its `ldm` past later
  stores and holds it in regs across the body. Never a local `struct v = data;` (stack
  round-trip).
- **Tail-call veneer** (`ldr ip,[pc]; …; bx ip`, no frame): `return TARGET(args)` (or
  `void`). Cross-section/overlay veneers ARE C-matchable at -O4 -interworking. Don't
  add pass-through args it doesn't use. If the veneer writes fields first, forwarding
  args may add a frame → use the tail-call-passthrough trick (declare extra params,
  forward them, to keep the frame + `bl`).
- **Declare callees/wrappers with FEWER args**: Ghidra's `g(a, extraout_r1, c)` =
  leftover registers. Declare `g` and the wrapper with ONLY the args the ROM
  explicitly `mov`s into r0-r3 before the `bl` (forwarding extras grows the frame).

## List-walk families (ov004/005/008/009/025/026 WalkRecords + FindBestRecord)

- **Callee arg count from `mov r0-r3` count**: the decompiler invents trailing
  args from leftover live regs. If the ROM sets up only r0,r1 before `bl callee`,
  declare `callee(a,b)` — extra args add `mov r2,..; mov r3,..` before the call.
- **Loop-counter vs count vs flag register permutation = declaration order.** When
  several ints (loop index `i`, an accumulator/`found` flag, the loop bound `count`)
  are simultaneously live, mwcc assigns callee-saved regs in DECLARATION order. Two
  proven fixes on byte-identical siblings: `WalkRecords` wanted i→r5,added→r6,
  count→r7 → declare `int i; unsigned short added; int count=*p++;`. `FindBestRecord`
  wanted found→r5,bestSub→r6,count→r7,i→lr → declare `int i; int found=0; short
  *bestSub=0; ushort *best=0; int count=*p++;` (i FIRST even though it's the counter;
  the master-`mov rX,#0` zero-source is the first 0-init local). When you're down to a
  pure {r5,r6,lr} rotation, permute the decl order — it's not a tie.
- **Elide a redundant `count>0` guard**: `if(count>0){ for(i=0;i<count;i++) ... }`
  emits TWO `cmp count,#0; ble`. Drop the outer `if` — the `for`-entry test IS the
  guard. Put a loop-invariant like `param_3+1` INLINE in the body (not a pre-loop
  `lim` local) so mwcc hoists it to just after the entry `ble` (matches the ROM,
  which computes it inside the guarded region, not before the guard).
- **Post-inc count load**: `int count = *param_2++;` = `ldrh rC,[p],#2` (count held
  in a reg, param_2 now = first record; the loop bound is NOT re-read from memory).

## Fixed-point ctor / index-fill (ov000/002/005/006/008/009/025/026 BuildTagTracker)

- **64-bit scale = umull + mla**: `((u64)a * K) + hi*K` where the compiler adds a
  32-bit `hi*K` to the HIGH word of the umull → `umull lo,hi_r,a,K; mla hi_r,hi,K,hi_r`.
  Write: `u64 prod=(u64)a*K; u32 hi = p7*K + (u32)(prod>>32);` then split
  `n[3]=(hi<<26)|((u32)prod>>6); n[4]=hi>>6;`. The one constant K is pooled once (r0)
  and reused by both the umull and the mla.
- **`|` operand order picks base vs barrel-shift**: `(hi<<K) | (lo>>M)` — mwcc makes
  the FIRST operand a standalone shift and the SECOND the barrel-shift inside `orr`.
  If the ROM computes `lsr lo,#M` standalone and folds `hi<<K` into the orr, write
  `(hi<<K) | (lo>>M)` (NOT `(lo>>M)|(hi<<K)`), i.e. put the barrel-shift operand first.
- **Array-index beats induction-var to force re-read**: a loop body doing
  `*(T*)(p + i*S) = f(...)` gets strength-reduced by -O4 to a walking pointer + an
  i*S counter (extra callee-saved reg). If the ROM instead re-derives `[base, i<<k]`
  every iteration AND re-loads `base` from memory after the call, write `((T*)base)[i]`
  and `((u16*)param_3)[i]` — the array-index form keeps `i` as the sole induction var
  and re-reads the (possibly call-aliased) base each pass.

## ★ hw60: the redundant `lsl#0x10;lsr#0x10` TELLS YOU WHICH FORM TO WRITE (both proven 2026-07-16)
Do not guess — look for the `lsl #0x10 ; lsr #0x10` pair (an `& 0xffff`) between the hi-byte op
and the reassemble. It is the discriminator, and both cases are real in the ROM:

| ROM has the trunc pair? | write |
|---|---|
| **no** | the explicit extract/reassemble (below). `func_ov206_020cd464` — `hi \|= 6` |
| **yes** | the **bitfield** form: `struct {u16 lo:8, hi:8;}; p->hi &= ~0x82;` — `func_ov206_020cd9c4` |

Two functions in the SAME overlay, four instructions apart in shape, needing opposite forms. Both
matched first try once the pair was read off the disassembly. `bic` vs `orr` in the hi-byte op is
just `&= ~K` vs `\|= K` and does not affect the choice.

**Confirmed again 2026-07-17 on `func_ov231_020cf578` (×5) — the two forms sit BACK TO BACK in one
function**: `hi |= 1` with no trunc pair (explicit extract/reassemble) immediately followed by
`hi &= ~0x8c` with the trunc pair (bitfield). Matched first try. So this is not an
overlay/build-line quirk: the pair is a per-write property, and reading it off the disassembly is
the whole trick. Never infer the form from the operator or from what the neighbouring write used.

## hw60 hi-byte `|= K` STANDALONE (AimAtTargetAndDispatch ov137/138/158/159/160/246/247)
The `struct hw60{u16 lo:8,hi:8;}; ->hi |= K` bitfield form MATCHES when it's the 2nd+
op in a chain (the prior write establishes the 0-0xff range), but a STANDALONE `->hi
|= K` adds a redundant `lsl#0x10;lsr#0x10` (& 0xffff) trunc (+8B). Fix: write the
explicit extract/reassemble the ROM uses:
`u16 v = *(u16*)(base+0x60); *(u16*)(base+0x60) = (u16)((v & ~0xff00) | (((((u32)v<<0x10)>>0x18 | K)<<0x18)>>0x10));`
KEY: use `v & ~0xff00` (NOT `v & 0xff`) for the lo-byte keep — mwcc emits `bic #0xff00`
for the former (matches) but `and #0xff` for the latter (1-instr diff). The reassemble
`((hi|K)<<0x18)>>0x10` inherently truncates hi to 8 bits so no extra mask is needed.
Also here: `x*30/10` (signed) = `mul #0x1e; lsr#0x1f; smull 0x66666667; add r1,hi,asr#2`
(magic /10, don't hand-fold to *3 — the x*30 intermediate can overflow).

## ★ The same discriminator works on a u32 LO byte — count the ops, not the width
*(ov221 020d4828 + its ov222/224/225 twins, 2026-07-17)*

The hw60 table above is about a **u16** and its `lsl#0x10;lsr#0x10` pair. The identical question
comes up for a **u32** whose low byte is a flag set, and the discriminator is the same idea: does
the ROM keep work that mwcc would fold away?

```
ROM:  ldr r1,[r2,#8] ; lsl r0,r1,#0x18 ; lsr r0,r0,#0x18 ; orr r0,r0,#1
                     ; bic r1,r1,#0xff ; and r0,r0,#0xff ; orr r0,r1,r0 ; str r0,[r2,#8]
```
Two things there are redundant to a human: the `lsl/lsr` pair *is* `and #0xff`, and the second
`and #0xff` cannot change anything after `orr #1` on an already-masked byte. Writing the extract by
hand —
```c
w = *(u32 *)(p + 8);
*(u32 *)(p + 8) = (w & ~0xff) | (((w << 0x18) >> 0x18 | 1) & 0xff);   /* WRONG (-8 B) */
```
— lets mwcc fold the shifts to `and r0,r1,#0xff` and drop the mask entirely. **Keeping both is the
signature of a real bitfield**, so write one:
```c
typedef struct { u32 lo : 8; u32 rest : 24; } FlagsW;
((FlagsW *)(p + 8))->lo |= 1;                                          /* MATCH */
```
mwcc emits the shift-pair extract *and* the field-width truncation because the bitfield's width is
part of the type, not something it re-derives and folds.

★ **The rule, and it is the opposite of the u16 case above — do not pattern-match the width.**
For hw60's u16, the trunc pair present ⇒ bitfield, absent ⇒ explicit form. Here, for a u32 lo byte,
the extract pair present ⇒ bitfield. What actually generalises is the *question*: **write the form
whose redundancy the compiler is obliged to keep.** Hand-written arithmetic gets folded; a bitfield
access does not. So ask "is the ROM doing work I could optimise away?" — if yes, the source said it
in a way that forbade the optimisation. Both functions here are in the same 296 B function, one
u16 and one u32, and they need *opposite* forms.

## Compound `+=` returns-value to reuse the field's register (ChargeTimerThenFire ov221-227)
`x = obj[i] + v; obj[i] = x;` may put `x` in a FRESH reg, leaving a scheduling slot
(load-use stall) unfilled — so a later-needed constant like a call's `0` arg gets
scheduled LATE instead of hoisted into the stall (symptom: `add r2,r1,r0` where the ROM
has `mov r2,#0`, with a cascading t/flag register swap). Fix: `x = (obj[i] += v);` — the
compound-assign VALUE keeps `x` in obj[i]'s own register (r1), freeing the other reg so
mwcc hoists `mov r2,#0` into the dependent-load stall and the allocation matches.
Also: two-way constant select compiles to `movne A; moveq B` — write `flag ? A : B`
(order: the `!=`/ne value is the ternary's true-branch). Inverting a `t<K` guard to
`t>=K` puts the ELSE block at the end (matches a ROM `blt end` forward branch).

## `static inline` helper for repeated hw60 |= K ops (SetChargeFlagsAndDispatch ov228-249)
When a handler does the standalone hw60 `->hi |= K` explicit-form edit MULTIPLE times
(e.g. |=0x40, |=0x80, |=0xe), factor it into a `static inline void hw60_or(int base,
unsigned int k){ u16 v=*(u16*)(base+0x60); *(u16*)(base+0x60)=(u16)((v & ~0xff00) |
(((((u32)v<<0x10)>>0x18 | k)<<0x18)>>0x10)); }`. With `-inline on,noauto` it open-codes
each call site EXACTLY like the ROM's repeated inline sequence (must be `static inline`,
not plain `static` — the latter emits a real function + `bl`). Cleaner than pasting the
6-line block N times and byte-identical.

## Vec/struct passed BY VALUE to a callee (the sub-sp/ldm/stm dance) (ov228-249 Push*)
When a 3-int vector is a call argument (e.g. `func(owner, mode, vec, flag)`), the ROM
loads it and does a `sub r3,sp,#8; ldm src,{r0,r1,r2}; stm r3,{...}; ldm r3,{r2,r3}`
shuffle (part in r2/r3, part on the outgoing stack). Model the param as a
`struct vec{int x,y,z;}` passed BY VALUE — `func(owner, mode, *(struct vec*)(base+off),
flag)` — and it open-codes that exact dance. Works whether the source is `owner+0x494`
(a field) or a shared constant global (`data_02041dc8` — passing a const struct by
value avoids the scheduling tie you'd get storing it into obj first).

## switch case block layout = SOURCE order; compares stay value-sorted (InitSubsystemObject)
A small `switch(x){case A: …; case B: …}` with no jump table emits the compare chain in
VALUE order (`cmp #0;beq / cmp #1;beq / …`) but lays the case BODIES in SOURCE order.
If the ROM's block layout is e.g. case1, case0, case2, write the cases `1,0,2`. A var
assigned only inside the cases can be left uninitialized (matches the ROM's default
fall-through with a garbage register). NOTE the `mode:arm` field in build/func_index.json
is unreliable for these overlay funcs — several are THUMB; if the ARM disasm is garbage,
re-disasm THUMB and verify with `--thumb`.

## Reverse decl order to place the RETURN value in a high callee-saved reg (FindMinListValue)
When a value is the function's return AND lives across calls, the ROM often keeps it in
the HIGHEST callee-saved reg (r6) while the loop counter/others take r4/r5. mwcc assigns
r4,r5,r6 in DECLARATION order, so to get `min->r6, count->r5, i->r4` declare them
`i; count; min;` (reverse) and ASSIGN `min` first. Combine with `for(i=0;i<count;…)`
(not `if+do-while` — gives the `bls` entry-guard, not `beq`) and `(int)min > val`
(not `val < min` — fixes the `cmp` operand order).

## Small-veneer / setter cracks (ForwardVecToOwner, SetTwoVecsAndFlag, SpawnAndLinkNode, UpdateSlotCache)
- **Params 2-4 as a `struct vec` param**: a wrapper that forwards a 3-int vector to a
  callee (by value or by &v) — declare the vec as a struct-by-value PARAMETER, not 3
  ints. mwcc homes r0-r3 (`push {r0,r1,r2,r3}`) and re-passes/&-takes it, matching the
  ROM. Two vecs -> two struct params (2nd lands on the caller stack, block-copied via
  ldm/stm to the dest field).
- **RETURN the callee's result to reserve r0**: when a void-looking fn ends right after
  `bl callee` with the entry/out-pointer re-read into r1/r2/r3 (never r0), the ROM is
  actually RETURNING the callee's result (r0 stays live). Declare the fn `int` and
  `return spawn;` — otherwise mwcc frees r0 and shifts every following access down one
  register (off-by-one diff through the whole body). Capturing-but-not-returning gets
  DCE'd; you must actually return it.
- **Cache a re-read value in a local to flip ip<->lr**: a 2-byte ip/lr swap on a value
  loaded once and reused (`*param_2` compared then stored) can flip by binding it to a
  named local (`int key = *param_2;`) — changes mwcc's temp-register pick to match.
- **Re-read a global inline (don't cache) when a store/call may alias**: `*(int*)(g +
  i*8 + 0xc)` accessed several times with a field store or `bl` between — write `g`
  inline each time (mwcc keeps `&g` in a reg, re-loads `[.]`), don't hoist to a local,
  or you'll drop the ROM's re-reads.

## Arithmetic-shift bit test to force PREDICATION (InvokeHookAndRearm ov245/254/283)
When the ROM predicates a small block guarded by a bit test (`asrs r0,#0x1f; ldrne …`)
but your `if ((x << 0x1e) < 0) {...}` BRANCHES (`lsls; bpl`), change the guard to the
arithmetic-shift value form `if ((x << 0x1e) >> 0x1f) {...}` — the signed `>>0x1f`
compiles to `asrs` (shift-into-sign, sets flags) and mwcc then predicates the block
(reversed from the usual "force a branch" case). Also: a call that forwards ALL its
incoming params to a callee (`f(param_1,param_2,param_3,param_4)` where those are still
in r0-r3) emits NO arg setup before the `bl` — declare the callee with as many args as
you pass, it costs nothing.

## Session 2026-07-15 — confirmed cracks (scene-system carves)

- **Local declaration order steers callee-saved register webs.** When two long-lived values
  (e.g. a param held across calls and a call-result held across calls) land in the *swapped*
  callee-saved regs (r4↔r5), reorder the local declarations. RunClassConstructor (func_02023960)
  matched only with `int def, saved, token;` (not `token, saved, def;`) — flips which web gets r4.
- **K&R prototype for variable arg-count calls.** A callee invoked with a *different* number of
  args at different sites (one site sets r1, another leaves it) → declare it with an empty
  prototype `extern void f();` and call `f(1,0)` vs `f(1)`. mwcc passes exactly the args given,
  no spurious `mov r1`. (BootTask calls StoreGlobalPairAt10 with 2 args in one case, 1 in others.)
- **Absolute-address global (no reloc).** High-RAM constants dsd does NOT relocate (e.g.
  0x027ffc20) → `*(int *)0x027ffc20`. mwcc bakes the literal into the pool; no reloc needed.
- **Force loop-invariant constants into registers.** If the ROM hoists compare constants into
  regs across a loop (`mvn r6,#0; sub r7,r6,#1` for -1/-2), declare them as locals
  `int dead=-1, spawning=-2;` and compare against those, not immediates — else mwcc uses inline
  `cmn`/`cmp #imm` and the register pressure (hence allocation) diverges. (func_02023adc.)
- **do-while-with-guard beats top-tested while to avoid predication.** `if(p){do{...}while(p2)}`
  keeps the first body deref unconditional; the `while(p&&field)` top-test form makes mwcc
  predicate the field load (`ldrne/cmpne`, +4B). (list-find family ov005/009/025/026.)
- **`unsigned char flag` → `ands rN,rM,#0xff`.** A 0/1 comparison result passed on/tested as a
  byte compiles to `ands ...,#0xff` (mask+setflags); plain `int` gives `cmp #0`. (FrameStep.)
- **Pool-dedup tie (do NOT chase):** the retail build emits a *separate* pool word for each
  textual reference to the same global address; our mwcc coalesces them (`mov rN,r4`). One
  redundant `ldr rN,[pc]` short → route to nonmatching (see deferred-ties). (FrameStep func_020115b8.)
- **Independent absolute MMIO pointer vs folded `p-N` offset.** When the ROM computes a second
  register base for a nearby MMIO reg via `sub ip,rBase,#N` and uses `[ip]` (not `[rBase,#-N]`),
  the source declared it as an INDEPENDENT absolute pointer (`vu32 *subd=(vu32*)0x04001000;`), not
  as arithmetic off the first (`(vu32*)(sub-5)`). The derived form lets mwcc fold the constant
  offset into the load/store addressing (`[r1,#-0xa]`, one instr fewer); the absolute form makes
  mwcc materialize+hold it (deriving `sub ip,r1,#0xa` when a near value is already live).
  (func_ov000_0204d7c8 sub-display DISPCNT vs BG1CNT.)
- **Loop-local callee-saved register numbers follow DECLARATION order.** For several pointers/
  counters live across a call inside a loop (all land in r6/r7/r8…), mwcc numbers them in source
  declaration order, NOT first-use order. ROM had i=r6,tbl=r7,slot=r8 → declare `int i; char *tbl;
  u32 *slot;` in that order (even though tbl is materialized first). (func_ov000_0204d7c8 8-entry
  resource loop.)
- **SDK 64-bit ratio/divide helper is an EXPLICIT call, not `/`.** `x / 0x82ea` on a u64
  makes mwcc emit its own `_ll_udiv` runtime symbol (reloc name mismatch vs the ROM's
  `func_02020368`). The ROM calls the SDK helper directly: declare
  `extern unsigned long long func_02020368(unsigned long long v, unsigned int d, int);`
  and call it. Return type u64 (both r0:r1 used downstream). (func_ov000_0204d560, and the
  existing func_0201cbe8 pattern.)
- **`adds` from a truncated 64-bit add.** ROM `adds rN,r0,#K` (flags set, unused) where you
  expected `add` = the low half of a 64-bit `+K` whose high-word `adc` was dead-code-
  eliminated by a cast to u32. Do the add in 64-bit *before* narrowing:
  `(unsigned int)(u64val + 0x7d0)`, not `(unsigned int)u64val + 0x7d0`. (func_ov000_0204d560.)
- **Array-index form kills strength-reduction of `base+const+i*4`.** When the ROM keeps the
  index (`add r0,base,i,lsl#2; add #C; ldr [r0,#c04]`, i live for the count) but your
  `*(T*)((char*)base + C + i*4)` makes mwcc create an advancing pointer + redundant offset
  induction var (+2 instr, wider push), rewrite as `((T*)base)[K + i]` (K = C/sizeof(T)). The
  array subscript keeps i as the sole induction variable. (func_ov000_0204d208; the h[0x1301+i]
  object-table loop.)
- **Per-branch RMW vs shared load/store (bit set/clear if/else).** ROM re-loads and re-stores
  the field in BOTH the set (`orr`) and clear (`bic`) branches; a cached `int *p = &field;`
  makes mwcc share one load + predicated op + one store (-1 branch worth of instrs). Drop the
  pointer local and write the field expression (`*(int*)(obj+OFF)`) directly in each branch.
  (func_ov023_02088ee8/02089370.)
- **Force a post-call global re-read by extracting the call result to a local.** When the ROM
  re-loads a global pointer (`ldr =&g; ldr rN,[rN]`) AFTER a call, but your inline
  `g->field = ... f() ...` makes mwcc hold `g` in a callee-saved reg across the call (-2 instr
  per site), assign the call to a local first: `unsigned char v = f(); g->field = ...v...;`.
  The sequence point makes mwcc treat the global access as after the call → re-read.
  (func_ov008_0204dd24 menu state; heap bitfield writes around func_020235d0/func_0207bb14.)
- **1-bit / N-bit field read = declare the actual bitfield struct.** `if (obj->flag)` where flag
  is `unsigned f:1` compiles to `ldrb; lsl#0x1f; lsrs#0x1f` (extract+flags), NOT `tst #1`. A plain
  `(x & 1)` gives tst. Declare `struct { char pad[OFF]; unsigned f:1; }` and access `->f`. For a
  high nibble, `(unsigned)x << 24 >> 28` reproduces `lsl#0x18; lsr#0x1c` (bhs compare), vs `>>4`
  giving `asr`. (func_ov008_0204dd24.)
- **Don't materialize a reused base+offset pointer into a named local — inline it** when the
  ROM's scheduler fills mul-latency by ordering the store VALUE (`rsb`) before the store
  ADDRESS (`add`). Holding `char *e = base + idx*STRIDE;` and using `e`/`(int)e` makes mwcc
  compute the address early (right after the mul result lands) and schedule the value after;
  writing `*(int*)((char*)base + idx*STRIDE + 0xc) = val;` and `(int)base + idx*STRIDE` inline
  lets it front-load the independent value negation into the mul shadow → matches. Also: a
  0x8c-byte (non-pow2·4) struct stride wants `idx * 0x8c` on a `char*` (gives `mul #0x8c`+plain
  `add`, offset reused across two bases) NOT `base[idx*0x23+..]` (gives `mul #0x23`+`lsl#2`+`#3`).
  (func_020325b8.)
- **Two-way if/else-if block layout: invert the first test to pick which block goes inline.**
  `if(a==X){A}else if(a==Y){B}` normally emits A inline (fall-through) then B out-of-line. If the
  ROM instead tests X first but places the Y-block inline and the X-block out-of-line
  (`cmp #X; beq Xfar; cmp #Y; bne end; <B>; b end; Xfar: <A>`), write it as
  `if(a!=X){ if(a==Y){B} } else {A}` — the `!=X` puts B on the fall-through and A behind the
  beq. A `switch` costs +1 instr here. (func_ov008_0204dc48 menu confirm, action 7 vs 8.)
- **Write the comparison the way the ROM generates it.** `if (-1 < (int)x)` compiles to
  `cmp x,#-1; ...le` (mvn + `ble`); the ROM's `cmp x,#0; blt` comes from `if ((int)x >= 0)` /
  `if ((int)x < 0)`. Likewise mwcc lowers `if (x > 0xb)` to `cmp #0xc; movge`, so to match a
  `cmp #0xc; movge` clamp write `if (x >= 0xc)` directly. Pick the C relational that yields the
  ROM's immediate. (func_ov008_020698f8 sign gate; func_ov008_0205bea0 slot clamp.)
- **Explicit result variable vs `return expr==0`.** The ROM pattern `mov r5,#0; ... ; mov r5,#1;
  return r5` (a flag defaulted then set inside the if) comes from `int r=0; if(cond){...; r=1;}
  return r;`, NOT `return cond==0` (which recomputes the boolean at the end). (func_ov008_0206fa1c.)
- **Shared `(char)` cast at return, not an early constant return.** For `int f(){ ... = (cond) ?
    -1 : g(); return (char)sel; }` the ROM sign-extends (`lsl#0x18; asr#0x18`) once for BOTH arms.
  Writing `char sel; if(cond) sel=-1; else sel=g(); return sel;` makes mwcc early-return the -1
  constant (skipping the cast). Use `int sel` + `return (char)sel;` so both arms fall to the cast.
  (func_ov006_0204fa58.)
- **Anchor pointer for consecutive big offsets.** When the ROM holds `base+BIGOFF` in a reg and
  reads neighbours via small immediates (`[r4]`, `[r4,#4]`, `[r4,#8+i*4]`), don't write three
  separate `*(int*)(base+0xc57c)`, `+0xc580`, `+i*4+0xc584` (mwcc recomputes each big offset).
  Declare `int *cells = (int*)(base+0xc57c);` and use `cells[0]`, `cells[1]`, `cells[i+2]`.
  (func_ov008_02084324 grid re-register.)
- **Word-table copy: a struct assignment gives `ldm/stm`; per-element locals give `ldr/str`.**
  To copy an N-word global table onto the stack as the ROM does (`ldm r6!,{r0-r3}; stm ip!,{..};
  subs; bne`), declare `struct T { int w[N]; };` and `struct T t = global;` — a single struct
  copy lowers to the ldm/stm loop. Reading `a=src[0]; b=src[1]; ...` unrolls to individual
  loads/stores (much larger). (func_ov008_0205c580 20-word config copy.)
- **Backward for-loop for scan-from-newest, holding n-1 separately.** `for(i=n-1;i>=0;i--){ if
  (buf[i].flag==0){use buf[i];return;} } use buf[n-1];` matches the ROM's `subs; bmi; ... bpl`
  scan. Keep the "fallback = last entry" as its own local `int n1 = f()-1;` used at both the loop
  start and the fallback, so mwcc holds n-1 in one reg and the counter in another (the ROM does
  `subs ip,r0,#1; mov r3,ip`). Also index 8-byte entries via `struct E{u16 w[4];}; buf[i].w[3]`
  to get `[r,#6]` off a `lsl#3` stride, not `buf[i*4+3]`. (func_ov008_02055d24, func_ov000_0205a118.)
- **Sorted list insert = a for-loop, not while+null-check-inside.** `for(n=GetNext(l,0); n; n=
  GetNext(l,n)){ if(key(item)<key(n)){Insert(l,n,item);return;} } Append(l,item);` matches
  `movs r1,r0; beq append; ...` (single up-front null test via the for-init). A `while(1){ if
  (n==0){append;return;} ... }` reorders the null test into the loop body. (func_ov008_0205e868.)

- **Array-subscript idiom to fix the base/index register of `ldr Rt,[Rbase,Rindex,lsl#N]`.**
  For `*(T*)(base + index*stride)` mwcc may put the *index* in the base register and the *table
  base* in the index register (one-byte reg-swap diff on the load, e.g. `ldr r0,[r2,r0,lsl#3]`
  vs ROM `ldr r0,[r0,r2,lsl#3]`). Reordering the `+` operands does NOT fix it. Instead declare a
  typed entry `struct E { T f; ... };` sized to `stride` and write `table[index].f` — the
  array-subscript forces `Rbase = table`, `Rindex = index`. (ov008 0205_1500 12-func dispatch
  family: `data_0209009c[index[0]].obj` gave the ROM's `ldr [r0,r2,lsl#3]`.)
- **Speculative-load structure: hoist a side-effect-free method/pointer load ABOVE its guard.**
  When the ROM computes a vtable method pointer *unconditionally* and only branches the call
  (`ldr method; ...; beq skip; bl`), writing `if(p) r=f(load(),p);` branches over the load
  (too small). Hoist it: `void *m = load(); if(p) r=f(m,p);` — and nest the second guard
  (`if(r==0){ void *m2=load2(); if(q) r=f(m2,q); }`) rather than `if(r==0 && q)`, so the second
  load is also unconditional within the `r==0` block. (same 0205_1500 family.)

- **Test-a-single-bit-and-branch via `(x << k) >> 0x1f`.** ROM `lsl#k; movs r,r,lsr#0x1f; ldm{eq|ne}`
  (extract bit 31-k to bit0, set flags, conditional early-return) does NOT come from
  `-1 < (int)(x<<k)` / `(int)(x<<k) < 0` — those emit a signed `cmp`. Write the extraction
  literally: `(((unsigned)x << k) >> 0x1f)`. Polarity: `== 0` → `...eq` (return if bit CLEAR);
  bare truthiness `!= 0` → `...ne` (return if bit SET). (ov008 02059a54 family: k=0x1a `==0`,
  k=0x1b `!=0`.)

- **Force per-call truncation of a wide arg (defeat `& 0xffff` CSE).** When the ROM recomputes
  `param & 0xffff` (`mov rN,arg,lsl#16; mov rN,rN,lsr#16`) before EACH of several calls but mwcc
  CSEs the masked value into one callee-saved reg, declare the *callee's* parameter as
  `unsigned short` and pass the raw `param` — the implicit narrowing conversion re-emits the
  truncation at every call site, keeping the raw value (not the masked one) live. (ov008 0206fe50:
  two `func_02055808(owner, param_2)` calls with a `unsigned short tag` prototype.)

- **Compound assignment `+=` picks the ROM's commutative operand order.** For a read-modify-write
  the ROM often emits `add Rd, Rloaded, Rarg` while the expanded `x = x + y` gives the swapped
  `add Rd, Rarg, Rloaded` (same value, different encoding — a 1-byte diff). Writing `x += y`
  puts the loaded value in Rn and matches. Reordering the source operands (`y + x`) does NOT
  help — mwcc normalises. (ov008 0205e790: `*(u8*)(counters+row) += delta`.)
- **Clamp upper bound: `>= N+1` vs `> N`.** ROM `cmp #0xc; movge r,#0xb` comes from
  `if (v >= 0xc) v = 0xb;`, not from `if (0xb < v) v = 0xb;` (which gives `cmp #0xb; movgt`).
  Pair with the `<= N` rule for `cmp #N; bhi/ble`. (ov008 0205bf04.)

- **Search loop returning "the node or 0": single-exit `for` + `break`, never two returns.**
  `for (n = First(); n != 0; n = Next(n)) { if (match) break; } return n;` — on normal exit `n` is
  already 0, so the one `return n` covers both cases and matches the ROM. Writing `return n;`
  inside the loop **plus** a trailing `return 0;` adds an extra exit block (+4 B); a
  `while(1){ if(!n) return 0; if(match) break; n=Next(n); }` is worse (+8 B). (ov008 0205fdac;
  0206e05c is the same shape with an ordinal out-param.)
- **Reuse the zero: declare the flag local right before the stores that share it.** The ROM often
  keeps one `mov rN,#0` and uses it for both a struct field store and a later flag. `int f = 0;`
  placed *before* an intervening call makes mwcc hoist it into the call's argument instead;
  declare it uninitialised, then `f = 0; p[a] = f; p[b] = f;` after the call. (ov008 0206a23c.)

- **Search loop with a COMPOUND condition: `if (n) do {...} while (n);`, not a `for`.** When the ROM
  shows `movs r1,r0; beq end; <test> bgt end; ... ; movs r1,r0; bne loop` (the pointer test fused
  into `movs` at BOTH ends), write
  `n = First(); if (n != 0) { do { if (test) break; n = Next(n); } while (n != 0); } return n;`.
  A `for (n = First(); n != 0 && test; n = Next(n)) {}` gets rotated by mwcc into a bottom-tested
  loop with an entry `b` (+4 B). Note this differs from the simple single-exit `for` crack above,
  which is right when the loop body holds the only test. (ov025 0208a2bc.)

- **`mla` grouping: parenthesise the base the ROM folds into the accumulate operand.**
  `a * K + base + C` lets mwcc compute `(a*K + base)` then `add #C`; the ROM instead does
  `add rN, base, #C` first and folds it straight into `mla rD, a, K, rN`. Write
  `a * K + (base + C)` to force the ROM's grouping. (ov025 02090ffc: `page*0xc + (obj + 0x304)`.)

- **Small dispatch: `switch` puts both arms out-of-line; `if/else if` inlines the first.**
  ROM shape `cmp #0; beq L1; cmp #1; beq L2; b tail; L1: ...; L2: ...; tail:` (both call blocks
  after the tests, plus an explicit `b` to the tail) comes from a `switch (v) { case 0: ...; break;
  case 1: ...; break; }`. An `if (v==0) {...} else if (v==1) {...}` makes mwcc inline the first
  arm and is 4 B short. Applies even with only two cases and no jump table.
  (ov000 0204ef34 boot dispatcher.)

## MMIO neighbour register: address it as its own absolute constant, NOT as pointer arithmetic
*(found on ov000 0204ef84 — worth 8 bytes there, applies to every MMIO block)*

When a function touches two registers in the same block (e.g. `REG_BG0CNT_SUB` at 0x04001008 and
`REG_DISPCNT_SUB` at 0x04001000), do **not** reach the second one by arithmetic off a pointer to
the first:

```c
volatile unsigned short *bg = (volatile unsigned short *)0x04001008;
*(volatile unsigned int *)(bg - 4) = ...;      /* BAD */
```
`bg` is a compile-time constant, so mwcc constant-folds `bg - 4` into the *new* constant
0x04001000 — which is not an encodable immediate — and materialises it from scratch:
`mvn r2,#7 ; add ip,r2,#0x4000000 ; add ip,ip,#0x1000` (3 instructions, and it perturbs regalloc).

Write the absolute address instead:
```c
*(volatile unsigned int *)0x04001000 = ...;    /* GOOD */
```
mwcc then notices 0x04001000 == (pool constant 0x04001008) − 8 and emits the ROM's
`sub lr, r1, #8` (1 instruction), reusing the existing pool entry. Counter-intuitive: the *less*
"structured" C is the one that matches.

## Derived MMIO values: use the ROM's actual arithmetic sign
Constants equal mod 2^16 are NOT interchangeable. ROM `sub r12,r0,#0x3a00` (0x4004 − 0x3a00 =
0x0604) — writing the algebraically-identical `base + 0xc600` makes mwcc emit `add r2,r0,#0xc600`
plus an `rsb`/`mov` fixup. Read the sign off the disassembly and mirror it: `base - 0x3a00`.

## `& 0xfffc` on a u16 materialises a constant — use `& ~3`
On a `unsigned short` load the value is zero-extended, so `x & 0xfffc` is `& 0x0000fffc` →
`bic` with 0xffff0003 → not encodable → mwcc materialises the mask in a register (seen as a
gratuitously clever `rsb r3,r0,#0x14000` reusing a nearby constant). `x & ~3` is `& 0xfffffffc`
→ the encodable `bic r2,r2,#3` the ROM uses. Same rule for any "clear the low bits of a u16" mask.

### ★ The MMIO pool-vs-derive knob is BIDIRECTIONAL (this is the important part)
mwcc decides which MMIO address goes in the literal pool and which is derived from it by an
`add`/`sub` **based on how you write them in C**. This is a knob you control, not a tie:

| You write | mwcc does |
|---|---|
| `p[k]` / `p + k` (arithmetic off a pointer) | pools `p`, derives the other → `p` wins the register |
| `*(vu16 *)0xABS` (its own absolute constant) | free to pool whichever address is used *more*, and derive the rest |

So when the ROM pools X and derives Y, write **Y as an absolute constant** and let mwcc find the
derivation. When the ROM derives Y from X, write **Y as arithmetic off X**.

Proven both directions:
- ov000 0204ef84 — wrote DISPCNT_SUB absolute → mwcc emitted the ROM's `sub lr,r1,#8`.
- ov006 0205454c (title ctor, 816B) — **had been filed as a "proven r1/r2 register-allocation
  tie"**. It was not. The sub-BG1 reg (0x0400100a) was written `bg1[0x800]`, forcing bg1 to be
  pooled. Rewritten as `*(vu16 *)0x0400100a`, mwcc pooled bgs2 (0x0400100c) and derived
  0x0400100a from it — the ROM's exact r1/r2 assignment. Instant MATCH.

**Lesson: an "r1/r2 tie" in a block of MMIO accesses is a prime suspect for this knob, not a real
tie. Try flipping every address in the block absolute↔derived before routing to nonmatching/.**

### ★ It applies to plain .bss/.data globals too — and the base must be a LIVE LOCAL
*(ov024 0208455c, arena reservation, 172 B — MATCHed after this, 2026-07-16)*

Two globals `0x02093a48` and `0x0209ba48` exactly `0x8000` apart. The ROM loads the first into
`r4` in the prologue and reaches the second as `add r1,r4,#0x8000` — **while also keeping the
second in the pool** and using the pooled form for the first store and the compare. Both forms,
same function.

Writing `data_ov024_02093a48 + 0x80d8` does NOT get you the derived form: it is a link-time
constant, so mwcc folds it into its own pool entry (reloc + addend) and never materialises a base.
The knob is to make the base a **live local pointer**:
```c
char *base = data_ov024_02093a48;     /* now mwcc pools THIS and derives off it */
*(unsigned int *)(base + 0x80d8) = …; /* -> add r1,r4,#0x8000 ; str r0,[r1,#0xd8] */
MIi_CpuCopy32(…, base + 0xd8, …);     /* -> add r1,r4,#0xd8                       */
data_ov024_0209ba48[0x36] = …;        /* absolute where the ROM pools it          */
```
**Liveness is the whole trick**: `base` must still be live at the LAST derived use. If it dies
early, mwcc recycles r4 for the next local, the tail falls back to pool loads, and the prologue
pushes one register fewer. Here `push {r3,r4,r5,lr}` + `dtcmFree` in r5 only appeared once base
was referenced right to the end. Symptom of getting this wrong: right structure, 4 B short,
`ldr rN,[pc,…]` where the ROM has `add rN,r4,#imm`.

### ★ Pin the call order with a temp when two calls feed one expression
Same function: the ROM calls `OS_GetArenaLo(4)` **before** `OS_GetDTCMAddress()`, then computes
`(dtcm + 0x4000) - lo`. Written folded —
`OS_GetDTCMAddress() + 0x4000 - OS_GetArenaLo(4)` — mwcc evaluates left to right and calls them
the other way round. A temp for the second operand fixes the order without touching the
arithmetic:
```c
lo = (unsigned int)OS_GetArenaLo(4);
free = (unsigned int)OS_GetDTCMAddress() + 0x4000 - lo;
```
Generally: when two calls feed one expression and the ROM's call order is "backwards", hoist the
later operand into a temp. (Note the opposite default elsewhere — in `a - f()` mwcc will happily
call `f()` first to avoid spilling a load; read the disassembly, don't assume a rule.)

## Boolean return: preset the flag, don't let mwcc pick moveq/movne
ROM shape `mov r0,#1 ; cmp ; cmpne ; movne r0,#0` (preset 1, conditionally clear) vs mwcc's
`cmp ; cmpne ; moveq r0,#1 ; movne r0,#0` for `return a == b || x == 0;`. Write the preset out
explicitly and invert the condition:
```c
int ok = 1;
if (a != b && x != 0) ok = 0;
return ok;
```
(ov006 0204fc78.)

## ldrh/strh have only an 8-bit offset — a big struct offset means the source held a sub-pointer
`ldrh r1,[r2,#8]` where the field is at obj+0x434 tells you the ROM formed a base
(`add r0,obj,#0x2c ; add r2,r0,#0x400` = obj+0x42c) and indexed off it. mwcc will happily emit
`ldr r0,[r2,#0x430]` (ldr allows 12 bits) and `add r1,r2,#0x434` for the halfword, which will not
match. Recover the original by declaring the sub-struct and pointing at it:
```c
struct KeyBlock { int f0; int raw; unsigned short packed; };
struct KeyBlock *kb = (struct KeyBlock *)((char *)obj + 0x42c);
cfg.rawkeys = kb->raw;          /* -> ldr r1,[r2,#4]  */
cfg.packed  = kb->packed;       /* -> ldrh r1,[r2,#8] */
```
Rule of thumb: **an 8-bit-limited ldrh/strh reaching a >0xff field is a reliable tell that the
source used a pointer to an inner struct.** (ov006 0204e0c4.)

## Dense switch, empty cases: `break;` not `return;`
In a jump-table switch (`cmp r0,#N ; addls pc,pc,r0,lsl#2` + a table of one-instruction slots),
a case whose only job is to leave the function must be written `break;`, with the function ending
right after the switch:
```c
switch (state) {
...
case 1:
    break;          /* -> table slot holds 'ldmia sp!,{r3,pc}' inline, like the ROM */
case 3:
    break;
default:
    stop();
    return;
}
```
Writing `case 1: return;` (or merging `case 1: case 3: return;`) makes mwcc build one shared
epilogue block and branch to it, so those table slots become `b <epilogue>` instead of the return
itself. Everything else in the function matches either way — this is worth exactly one word per
empty case, and it is the difference between MATCH and 128/136. (ov006 0204db2c.)

Note the case ORDER also drives block layout: the ROM emitted its 9/10 block before its case-0
block, so the source listed `case 9/10` first. If the table is right but the blocks after it are
in the wrong order, permute the cases.

## `movs Rd,Rm,lsr #n` (shift sets the flags): write the truncation as an explicit shift
When the ROM tests a narrowed value it fuses the flag-set into the shift:
```
mov  r0,r0,lsl #0x10
movs r1,r0,lsr #0x10     <- r1 = (u16)r0 AND sets Z
```
A `(unsigned short)` cast does NOT get you this — mwcc emits `lsr r1,r0,#16` then a separate
`cmp r1,#0` (+1 instruction). Write the narrowing as the shift expression itself and mwcc fuses:
```c
unsigned int raw, row;
...
row = (raw << 16) >> 16;      /* not (unsigned short)raw */
if (row == 0) { ... }
dst->row = (unsigned char)row;
```
(ov006 0204fcd8.)

## Predicated if/else: try BOTH branch orders before believing it won't predicate
Same function: `if (row != 0) dst = A; else dst = B;` compiled to `cmp ; beq ; ... ; b`, while
`if (row == 0) dst = B; else dst = A;` — the same program — compiled to the ROM's
`ldrne/ldrne/addne/bne` predicated block. Flipping the sense of the test is free; always try it
before concluding mwcc refuses to if-convert.

### Same lever for NON-predicated if/else with calls in both arms (else-inline layout)
When both arms are too big to predicate (each makes a call / several stores), mwcc still picks
which arm is the *fall-through* (inline) vs the *jumped-to* block, and that choice follows source
order: the THEN arm is emitted inline, the ELSE arm is jumped to. The ROM frequently has it the
other way (else inline, then jumped, i.e. `cmp; beq <far-then>; <else inline>; b end`). Fix: write
the condition with the opposite sense and SWAP the two bodies, e.g. `if (q()!=0){B}else{A}` instead
of `if (q()==0){A}else{B}`. Both are the same program; the swap makes mwcc lay A inline as the far
block and B inline as fall-through — matching the ROM. Two independent instances of this in
func_ov008_0205b230 (Ov008_MainMenu_StateTick): the `a84c()` 7-vs-3 store pair and the
`GetCtxField967c()` InitObjectWithList-vs-b19c call both needed `!=`+swapped bodies. Combine with a
`switch` (not if/else-if) for a >=2-way state dispatch to get the forward-jump table layout.

## Variadic functions: `stmdb sp!,{r0,r1,r2,r3}` is the tell
A prologue that pushes ALL FOUR argument registers and an epilogue that does a bare
`add sp,sp,#0x10` after the register restore means the function is **variadic** — that push
builds the contiguous argument array va_arg walks. The named params stay in r0/r1; everything
past them is read from the spilled block at fixed sp offsets.

mwcc has no `stdarg.h` on our include path. These APCS macros compile and reproduce the ROM's
prologue exactly:
```c
typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)&(last) + sizeof(last))
#define va_arg(ap, type)   (*(type *)(((ap) += sizeof(type)) - sizeof(type)))
#define va_end(ap)         ((void)0)
```
Read each `va_arg` **at the point of use**, not all up front — a run of consecutive va_arg reads
gets merged into an `ldmib`, which the ROM does not do. (ov006 02051fbc, first variadic found.)

## Sign of a value: predicate BOTH arms, don't negate-then-add
ROM `addeq rD,pred,diff` / `subne rD,pred,diff` vs mwcc's `rsbne diff,diff,#0` + `add`. Write the
two arms out instead of negating a temporary:
```c
if (code & 8) state[0] = state[0] - diff;   /* -> subne */
else          state[0] = state[0] + diff;   /* -> addeq */
```
(ov024 02086800, worth 2 instructions.)

## Hold a loaded byte in a SIGNED int to get `asr` on the high nibble
`nibble = (unsigned)code >> 4` emits `lsr`; the ROM emits `asr`. A zero-extended byte in a signed
`int` shifts arithmetically with the same result:
```c
int code = *(unsigned char *)(src + i);   /* NOT unsigned char / unsigned int */
nibble = code >> 4;                       /* -> asr */
```
(ov024 02086800.)

## `if (n <= 0)` vs `if (n < 1)`
Identical programs, different encodings: `cmp r2,#0` vs `cmp r2,#1`. Read the immediate off the
ROM and mirror it. (ov024 02086800.)

## Small constant-select: `switch` puts arms OUT of line, `if/else if` predicates them inline
The companion to the ov000 0204ef34 entry above, in the opposite direction. ov006 020521a0 selects
a flags word from a style id. The ROM emits:
```
cmp r12,#1 ; mov r4,#0x200 ; beq OUT1
cmp r12,#2 ; beq OUT2
cmp r12,#3 ; ldreq r4,[pool] ; b JOIN
OUT1: ldr r4,[pool] ; b JOIN
OUT2: ldr r4,[pool]
```
i.e. the first two arms live out of line and only the last is predicated. Written as
`if (s==1) f=A; else if (s==2) f=B; else if (s==3) f=C;` mwcc predicates ALL THREE inline
(`ldreq/beq` x3) — 12 bytes short. Written as a preset plus a `switch`:
```c
unsigned int flags = 0x200;
switch (style) {
case 1: flags = 0x821; break;
case 2: flags = 0x411; break;
case 3: flags = 0x412; break;
}
```
it matches instruction-for-instruction.

**Rule: if the ROM branches to out-of-line arms, reach for `switch`; if it inlines the first arm
and pushes the rest out, reach for `if/else if`.** Both directions are now proven.


## ★ Bitfield reads are NOT hand-written shifts (2026-07-17, paid 10 functions)

mwcc constant-folds a hand-written bit test but never folds a bitfield read. This is
the single highest-yield crack found so far.

| source | mwcc emits |
|---|---|
| `(((unsigned)b << 0x1f) >> 0x1f)` | `and r0, r0, #1` / `tst r0, #1` — **folded** |
| `(((unsigned)b << 0x1e) >> 0x1f)` | `lsl #0x1e; lsr #0x1f` — kept (2 ops either way) |
| `((struct F *)p)->bit0` where `struct F { unsigned char bit0:1, bit1:1; };` | `lsl #0x1f; lsrs #0x1f` — **never folded** |

So a ROM that shows `lsl #0x1f; lsrs #0x1f` is reading a **bitfield**, and a
hand-transcribed shift can never match it. Bits are allocated **LSB-first**: the
first-declared field is bit 0. Writing a bitfield from a plain `char` also re-emits
the `and #0xff` narrowing that an `int`/`unsigned char` source folds away — that is
where a stray double-`and` comes from.

This one change simultaneously fixed a `tst` fold, a `cmp` operand order and a missing
reload in `TickTagTrackerNodes`, and rescued two long-parked files whose write-ups both
blamed the compiler (`ov025/020896fc` "our compiler is smarter", `ov008/02055b64`
"instruction-selection tie"). **If a diff shows `lsl/lsr` vs `tst`, stop and try the
bitfield before writing anything down as a tie.**

## ★ A loop-body local can never win an early callee-saved register

Declaration order IS the register allocator: mwcc hands out r4, r5, r6 … in the order
locals are **declared**. A variable declared inside the loop body is therefore always
allocated *after* every outer local, no matter how heavily it is used.

`TickTagTrackerNodes` wanted `i=r4, e=r5, now=r6/r8`. With `int e` declared inside the
`for` body, `now` (an outer local) always took r4 and the result was a stable 3-way
register rotation across ~44 instructions — a picture-perfect "register allocation tie".
**Hoisting `e` out of the loop** and ordering the block `saved, prev, swap, i, e, now,
get` made it byte-exact. Permuting only the outer decls had bottomed out at 47 bytes;
the variable that had to move was the one that was not in the permutation set.

Corollary: when a diff is *only* a register permutation and the instruction sequence is
identical, the answer is always declaration order — but remember to include the
loop-body and block-scope locals in the search.

## Don't hand-simplify an expression the ROM did not simplify

`func_ov008_02055b64` was parked for an "instruction-selection tie": the ROM reused a
zero register both to clear a half-word and as the index of a deref, `ldr [r0, r2]`.
The author had transcribed `*(int *)(*(int *)(p + 0x2c) + *(u16 *)(p + 4) * 4)` as
`**(int **)(p + 0x2c)` — correct C, because `p+4` had just been set to 0. The ROM's
"reused zero register" **was that index**. Written out in full: instant match.

A constant that the ROM materialises into a register is load-bearing. Transcribe the
expression, not your evaluation of it.

## Runtime helpers (confirmed)

- `func_0202060c(int a, int b)` → `long long`: **divmod**. quotient = low word,
  remainder = `>> 32`. `x % y` therefore compiles to `bl func_0202060c` + use of r1.
- `func_02020374(u64 a, u64 b)` → `u64`: **64-bit modulo** (r0/r1 = a, r2/r3 = b).
- `func_020031d4(void)` → `u64`: tick counter (OS_GetTick shape).
- `func_02020400` → divide helper, quotient r0 / remainder r1 (declare `long long`).


## ★ 32-bit bitfield containers: `lsr #0x10` with no paired `lsl` is the tell

An `unsigned int lo:16, hi:16;` container is loaded ONCE and each field extracted into
its destination register **in place**:

```
ldr r0, [r5]          ; the container word, stays live
lsl r1, r0, #0x10
lsr r1, r1, #0x10     ; ->lo   (two regs total, no temp)
lsr r0, r0, #0x10     ; ->hi   (top field: NO lsl -- this is the giveaway)
```

Any source built from `u32 f = *p;` + `(unsigned short)f` needs a **third** register for
the intermediate and lands `lo` one register higher, cascading into the instruction
schedule. That looks exactly like a register-permutation tie and is not one. On
`func_ov294_020d1c4c`, casting vs masking, `int`/`uint`/`u16` for the field, inner vs
outer scope and **all 720 declaration orders** were stuck at 8 diffs; the container
matched first try.

Rule: **a bare `lsr rX, rX, #N` whose value is never `lsl`-ed first is a bitfield's top
field**, not a shift you can write by hand.

## ★ Sub-object pointers: a hoisted `add rX, base, #imm` is a variable, not the scheduler

`add r2, r4, #0x100` appearing early, in its own register, filling an unrelated
`ldr`->`str` delay, and staying live until a much later `ldrh [r2, #0xae]` = the source
holds a **pointer to a sub-object**:

```c
struct Body *b = (struct Body *)(param_1 + 0x100);   /* declared at the top */
...
b->flags |= 0x10;
```

`*(u16 *)(param_1 + 0x1ae)` produces the same two instructions (0x1ae is not an ARM
immediate, and 0xae fits an ldrh displacement) but computes the add **at the point of
use**, so it can never be hoisted. This is why the split looks like a scheduling
artifact. `func_ov294_020d1a24` was parked as "register-pressure driven, not
source-steerable; confirmed unreproducible across all 26 mwcc generations"; the struct
pointer put the add in the ROM's exact slot and register on the first try.

## ★ Bitfield writes and `char`: where a stray `and #0xff` comes from

Writing a bitfield from an `unsigned char`/`char` local re-emits the narrowing that an
`int` source folds away, and a bitfield **increment** emits the whole chain:

```
lsl/lsr (extract) ; add #1 ; and #0xff ; bic #1 ; and #1 ; orr
```

That `and #0xff` is the unsigned-char arithmetic of the bitfield itself -- not a stray
intermediate to be explained away. Two parked files blamed the compiler for it.


## ★ `teq` = `(a ^ b) == 0`, and it is how you defeat if-conversion

mwcc spells equality two different ways and they optimise differently:

| source | mwcc emits | if-converted into the preceding branch? |
|---|---|---|
| `if (a == b)` | `cmp a, b` | **yes** — becomes `cmpne`, and the guard's `beq` disappears |
| `if ((a ^ b) == 0)` | `teq a, b` | **no** — the guard keeps its own `cmp`/`beq` |

So **a `teq` in the ROM is not a compare, it is an XOR-against-zero in the source**,
and writing it as `==` costs you the 4 bytes of the branch mwcc then folds away.
`func_ov000_02056354` was parked as an "if-conversion tie ... resisted nested-if,
flag-first-decl, and explicit goto restructuring" — every one of those attacks the
predication, which was the symptom. The `teq` was printed in the diff the whole time.

Generally: **when mwcc merges two tests you want kept apart, change how the second
test is spelled, not how the blocks are nested.**

## A live r0 across a call site means the callee takes an argument

`ldr r1, [base, #off]; blx r1` where r0 holds something from the preceding compare is
not a register preference — r0 is the **argument** and the pointer went to r1 because
r0 was occupied. Same for a load that lands in r1 when r0 was free (`ldrne r1, [r0,
#0x28]` keeps r0 = the object alive). Declaring the callback `void (*)(void)` lets mwcc
reuse r0 for the pointer and the diff looks like an allocator tie.

Corollary of the arity lesson: check the *callback* prototypes too, not just the
`extern` ones. Two call sites of the same callback can pass different arguments — that
is evidence for the argument, not against it.

## Declaration order is not a universal key

It cracked `TickTagTrackerNodes` and did nothing at all for `func_ov000_02056354` (all
6 permutations, identical output). Use it when the instruction *sequence* already
matches and only registers differ; if sizes differ, the cause is upstream.


## ★ The "hw60" class is a BITFIELD (retires the deferred note)

The `+0x60` config half-word that shows up all over the object code as a wall of shifts
is `struct { unsigned short lo : 8, hi : 8; }`. mwcc's canonical read-modify-write of a
width-8 field at offset 8 in a 16-bit container is:

```
lsl #16 ; lsr #24              read   (lsl 32-off-w, lsr 32-w)
bic #0x40                      the op
lsl #16 ; lsr #16              the intermediate is unsigned short (the FIELD's type)
bic lr, #0xff00                clear the field in the container
lsl #24 ; orr lr, r3 lsr #16   re-insert (lsl 32-w, lsr 32-w-off)
```

`cfg->hi &= ~0x40;` emits every one of those, **byte-identical** to the hand-written
`(x & ~0xff00) | ((((x<<16)>>24) & ~0x40) << 24 >> 16)` transcription. So spell hw60
sites as bitfields: same bytes when it works, and readable either way. Verified on
`func_ov181_020ce664` (228/228, only the `bic` slot left).

Container width matters: `unsigned int lo:8, hi:8` on the same address compiles 8 bytes
SHORTER (mwcc uses `ldr`/`str` and cheaper masking), so the container type is
recoverable from the size alone.

## Two scheduler walls that source form does not reach (2026-07-17)

Both are "instruction stream identical, ONE thing in the wrong slot", and both survived
every source lever that works elsewhere:

- `func_ov000_020552b4` (656/656, x6): scratch-register swap r1/r2. 16 spellings ruled
  out including flipping `&`, volatile on either operand, temps, and all 24 declaration
  orders. Pointer variables for the struct bases are PROVEN WRONG (592 B).
- `func_ov181_020ce664` (228/228, x6): `bic lr, lr, #0xff00` hoisted early by mwcc,
  late in the ROM. 7 spellings + all 6 tail statement orders ruled out.

These are the current best evidence that a real codegen difference may exist somewhere.
They are still NOT proven ties -- but unlike every write-up retired today, the ruled-out
lists in those two files are specific, reproducible, and worth trusting as a starting
point. **Do not re-run what they already list.**


## ★ A variable's USE COUNT picks its register -- so don't factor out what the ROM repeated

When the instruction stream is identical and the registers rotate, look for a local
whose use count your transcription changed. mwcc hands out scratch registers roughly
by use count (most-used gets the lowest), so introducing a tidy local where the original
repeated the expression re-orders the whole allocation.

`func_ov137_020cee94`: `dst` was used twice (the vector copy target AND the call
argument). Writing the copy through the expression instead --

```c
*(struct vec *)(obj + 5) = *(struct vec *)(*obj + 0x394);   /* not: *(struct vec *)dst = ... */
func_01ffa724(obj[8] = 0x1000, dst, (unsigned int *)(obj + 2));
```

-- drops `dst` to one use and the r3/ip/lr rotation disappears. 16 diffs -> 0.

Note this is NOT the declaration-order lever: that one governs the callee-saved
r4..r8. Values living in caller-saved registers (r0-r3, ip, lr) are ordered by use
count and live range instead, and no amount of declaration shuffling reaches them.
Check the push list to know which lever you are even allowed to pull.

## ★ `x = k` used as a value: an assignment-expression gives the constant a live range

```c
func(obj[8] = 0x1000, ...);        /* ROM: mov ip,#0x1000 early; mov r0,ip; str ip */
obj[8] = 0x1000; func(0x1000, ...) /* mwcc: mov r0,#0x1000 at the use -- 4 B SHORTER */
```

Split into two statements, mwcc rematerialises the constant at the point of use and
reuses r0 for both the store and the argument -- one instruction shorter than the ROM.
As a single assignment-expression the value gets a real live range, is materialised
early (the scheduler drops it into the nearest load-use stall) and then has to be moved
into r0 for the call.

So **a ROM that is one instruction LONGER than your C, around a constant used twice, is
an assignment-expression.** Same tell as the arity lesson: the ROM being "worse" is
information, not noise.


## ★★ The DESTINATION's signedness decides how -1/0xff is materialised
*(func_ov022_020b1bb4 + func_ov022_0208a790, 2026-07-18)*

ROM: `mov r1, #0` … `sub r0, r1, #1` — it derives 0xff from the zero it already has.
mwcc from `*(unsigned char *)p = 0xff;` emits `mov r0, #0xff` instead.

**Write it as a signed store of -1**: `*(signed char *)p = -1;`. With a signed destination mwcc
reuses the zero register; with an unsigned one it materialises the constant. Same bytes stored,
different codegen. `= -1` on an *unsigned* char field does **not** work — it folds straight back to
`mov #0xff`, so this is about the pointer's type, not the literal you write.

## ★★★ A STORE USED AS A CALL ARGUMENT: `f(obj[8] = K, …)`
*(func_ov149_020cfe6c, 2026-07-18)*

ROM: `mov ip, #0x500` materialised early, then `mov r0, ip` for the argument **and**
`str ip, [r3,#0x20]` for the store — one materialisation, two uses. Writing them as two
statements (`obj[8] = 0x500;` then `f(0x500, …)`) is 4 B short, and so is a shared
`int k = 0x500;` local.

```c
func_01ffa724(obj[8] = 0x500, dst, (unsigned int *)(obj + 2));
```

The assignment-expression *as the argument* is what ties them together. Same family of trick as
the chained `v = i = 0`: **when the ROM uses one register for a value that appears in two places,
the source usually joins them into one expression, not two statements.**

## ★★★★ STRUCT TYPES vs POINTER CASTS change SCHEDULING — the "scheduling wall" is often style
*(func_ov147_020ce2d0, 2026-07-18. This one reframes a whole class of parks.)*

Two C versions, **identical size, identical instructions, identical registers** — and only the
position of one `ldm` differs. The cast-based version schedules the vec3 load at the END; the ROM
hoists it above the hw60 block. No statement reordering, pointer hoisting, extra local or
declaration permutation moved it (four attempts, all recorded in the old park note).

What moved it was rewriting the function with **struct types and named fields** instead of pointer
casts, and reloading the base explicitly before each block:

```c
struct D { char pad0[8]; unsigned int f8 : 8; };
struct C { char pad0[0x60]; unsigned short f60; char pad62[0x326]; struct D *f388; };
struct B { struct C *p0; char pad4[4]; struct Vec3 v8; };

struct B *b = a->b;
c = b->p0;  x = c->f60;  c->f60 = …;      /* reload before each block */
c = b->p0;  x = c->f60;  c->f60 = …;
d = b->p0->f388;  d->f8 = d->f8 & ~1;
b->v8 = data_02041dc8;                     /* mwcc hoists this ldm on its own */
```

**Why this matters far beyond one function:** eight of the ten family heads parked that day were
filed as "scheduling" or "register colouring", i.e. as compiler-internal and therefore hopeless.
At least one of them was not — it was the source style. **Before filing anything as a scheduling
tie, rewrite it in the struct-typed house form and re-measure.**

**How to find the house form for a shape you are stuck on:** `tools/find_insn.py --seq` for the
instruction pair you cannot produce, then read the C of a matched hit — ideally one in the same
overlay. Here `func_ov149_020cfd84` was one of 52 hits and gave the whole style, including the
detail that the `hi &= ~1` case wants the explicit spelling with an extra `(unsigned short)` cast
rather than the bitfield.

## ★★ After a STRUCT COPY, a later "field = source.field + x" is really "field += x"
*(func_ov147_020cd20c, 2026-07-18)*

Ghidra shows six separate field assignments; the ROM has two `ldm`/`stm` pairs — **whole-struct
copies** — followed by fixups. And the fixups add to the **already copied** value:

```c
b = *(struct vec *)(*obj + 0x3d8);      /* ldm/stm */
a = *(struct vec *)(t + 0x74);          /* ldm/stm */
b.y = b.y + base;                       /* NOT `*(int *)(*obj + 0x3dc) + base` */
a.y = a.y + base;
```

Re-reading the source field costs 4 B — the copy already put it there. **Tell:** an `ldr` from the
*destination* struct's stack slot right before the add (`ldr r6,[sp,#0x10]`), where you expected a
load from the source object.

Two more from the same function: **no cached `owner` local** (the ROM re-reads `*obj` each time and
caching it was 8 B short — the opposite of the usual instinct), and the declaration order of the
two vec3s decides which lands at sp+0.

## ★★ WRITE THE EARLY EXIT AS THE POSITIVE CASE to control block ORDER
*(func_ov117_020ccdf4, 2026-07-18)*

Same size, same instructions, wrong **order** — only the branch targets reveal it:

```c
/* emits the two blocks the wrong way round: */     /* matches: */
if (d > 0x1000 && d < thresh) {                     if (d <= 0x1000 || d >= thresh) {
    …rand path…                                         state = 2; dispatch(); return;
} else {                                            }
    state = 2; dispatch(); return;                  …rand path…
}
```

The ROM leaves the *early-exit* block as the fall-through right after the tests. Writing the
condition in its negated, early-return form puts it there. **This is the block-ORDER knob, distinct
from the predication knob** (the one-case `switch` / ternary levers below) — a diff whose sizes
match but whose `b<cond>` targets differ is telling you about order, not predication.

## ★★★ ONE wrong constant FORM can poison instructions far downstream
*(func_ov147_020cc00c, 2026-07-18)*

`x < 0x4801` and `x > 0x4800` are the same test, but **0x4801 is not an ARM immediate**, so mwcc
loads it from the pool — and then, having that register live, it **derives later constants from
it**:

```
ROM : cmp r0,#0x4800 … ldrgt r0,[pc,#0x74] ; mvnle r0,#0x10c0
mine: ldr r1,[pc] ; cmp r0,r1 … subgt r0,r1,#0x3740 ; rsble r0,r1,#0x3740
```

The diff read as **three independent problems** (a comparison and two constants) and was **one**.

**Rule: when a diff shows several wrong instructions clustered together, look for a single wrong
form upstream before treating them as separate.** The usual culprit is a constant that cannot be
an immediate (`> K-1` vs `>= K`, `<= K` vs `< K+1`) — check whether the ROM's form fits in an
8-bit rotated immediate and yours does not.

⚠ Corollary hit the same day: **changing a comparison without swapping its blocks inverts the
semantics**, and the *size does not change*, so only the branch polarity in the disassembly
catches it.

## ★★ ARITY FROM THE FN-POINTER'S REGISTER on a forwarding indirect call
*(func_ov022_0209145c, 2026-07-18)*

```
push {r3, lr} ; cmp r0,#0 ; popeq ; ldr r2,[r0,#0x20] ; blx r2 ; pop
```

**No argument setup before the `blx`** — so the arguments are already in place, i.e. the function
**forwards its own parameters**, and the pointer lands in the first register they leave free:

| parameters forwarded | pointer register |
|---|---|
| 2 (r0, r1) | **r2** |
| 1 (r0) | r1 |
| 0 | r0 |

So `void f(int self, int a) { … (*(void (**)(int,int))(self + 0x20))(self, a); }` matches, while the
one-parameter version puts the pointer in r1 and the no-parameter one in r0. **The absence of
argument setup is the evidence** — read the pointer's register to recover the arity. Easy to miss
because there is nothing on screen to notice.

## ★★★ REUSE THE PARAMETER — the original overwrites its own argument
*(func_020169f8 + 4 siblings, 2026-07-18 — 5 functions from one crack)*

Symptom: every instruction matches, but one register is consistently wrong and **the whole
downstream allocation shifts with it**. Here the `mla` wrote to r1 in the ROM and r0 in mine, and
r1 is the register the `idx` **parameter** arrived in.

The original does not give the computed value a fresh local — it **assigns back over the
parameter**:

```c
void f(int obj, unsigned int idx, unsigned int val, int slot) {
    …
    idx = idx * *(unsigned short *)(base + off) + (base + off + 4);   /* elem, in idx */
    …
    if (idx != 0) { result = container + *(int *)idx; goto done; }
```

A fresh `int *elem` makes mwcc allocate the *dead `obj`* register (r0) instead, and everything
after moves. **The parameter's register is only free because the parameter is dead — the ROM's
allocator reuses it, and the only way to tell mwcc to do the same is to reuse the variable.**

**How to spot it:** the wrong register is one an argument arrived in (r0–r3), and that argument is
dead by that point. It reads like macro-generated accessor code, and there is usually a whole
family of them.

★★ **It is NOT "always reuse the parameter" — decide per value.** `func_ov022_020915bc` needed
*both* treatments in one 10-line function:

```c
arg0 = *(int *)(arg1 + 4);   /* loaded field REUSES the unused parameter (ROM puts it in r0) */
pp   = *(int **)(arg1 + 0x138);
sum  = arg0 + arg2;          /* the sum takes a FRESH local that inherits arg2's dead r2 */
```

Writing `arg2 = arg0 + arg2` instead makes mwcc canonicalise to `add r2,r2,r0` (destination
operand first), while the ROM has `add r2,r0,r2` — which is what a *new* value inheriting r2 looks
like. So: **read which register the ROM gives each value, then choose reuse-the-parameter or
fresh-local to match.** A destination that is also a source is the tell for the canonicalised form.

★ **This came out of a census, not a guess.** Of 365 parks, **17 are pure register permutations**
(same instruction stream, only register fields differ), and **`r1 → r0` accounts for 7 of them** —
five of those being one 30-instruction shape. Ranking the permutations by frequency is what
pointed at the parameter. Do that again before treating a coloring difference as unbreakable:

```python
# same mnemonics + same operand shape, only register fields differ -> collect the ROM->mwcc map
if all(norm(a) == norm(b) for a, b in zip(rom, mine)):  # norm() blanks register names
    ...
```

Also ruled out for this one, so don't repeat: swapping the multiply's operand order (mwcc
canonicalises it), and declaring `elem` earlier/later/at function scope.

## ★★★ A DEAD predicated instruction in the ROM is a source construct you have not written
*(func_ov008_02077f1c and func_02014bb0, 2026-07-18)*

When a conditional branch `b<cond> X` lands on an instruction at `X` predicated with the
**opposite** condition, that instruction can never execute — it is reached only via the branch that
proves it false. **Do not read it as compiler noise.** mwcc emits it because the source contains a
test there, and it reuses the still-live flags instead of re-comparing. Two different causes so far:

- **A genuinely duplicated test** (`func_ov008_02077f1c`): the original checks
  `*(int *)(p + 0x180) != 0` a second time right after the block that already returned on it. The
  dead `popne {r3,pc}` at +0x34 is that check. Dropping it compiles 4 B short.
- **A `while` loop's entry test** (`func_02014bb0`): the dead `beq` at +0x60 *is* the `while`
  condition. A `do/while` has no entry test and loses the instruction.

**Detector** (cheap, one pass over `func_index.json`): disassemble in the right mode, find every
`b<cond>` whose target instruction carries `OPP[cond]`, and check the target has no other
predecessor. It found exactly 1 park across 372 — low yield, but the one it found matched.

### ★★ …and the `while` case needs two more things to line up
`func_02014bb0` only matched when **all three** held. Each alone reads as a scheduling tie:

1. **`while`, not `do/while`** — supplies the dead entry test.
2. **The loop walks the variable that was ALREADY tested** (`next`), not a fresh copy (`cur = next`).
   A new variable makes mwcc re-compare (`cmp` + `beq`, 8 B) instead of reusing the live flags (4 B).
3. **The loop-invariant value is declared INSIDE the body.** `np` is invariant, and mwcc hoists it
   to just after the entry test — which is where the ROM has it. Declaring it *before* the loop
   schedules the load ahead of the compare and shifts everything.

Point 3 is the counter-intuitive one: **hoisting an invariant by hand puts it in the wrong place.**
Let mwcc hoist it — write it where it is used.

## ★★★ GUARD POLARITY — test for the SUCCESS case, not the failure case
*(func_ov123_020cc6e8, 2026-07-18. This was in the memory archive but **not** in this file, which
is why it cost a fresh derivation — if a crack is only in memory, distil it here.)*

ROM: `movne r0,#0 ; bxne lr` — a real early exit — then the body **unconditional**.
mwcc from a failure-first guard predicates the entire tail instead (`moveq`/`strbeq`/`moveq`),
landing 4 B short:

```c
/* short by one instruction: */          /* matches: */
if (slot != -1) return 0;                if (slot == -1) {
slot = 6;                                    slot = 6;
return 1;                                    return 1;
                                         }
                                         return 0;
```

Both spellings are the same logic; only which case is the `if` changes. The `goto` form
(`if (bad) goto no; … no: return 0;`) also matches, but the inverted `if` reads better — prefer it.

**Tell:** the ROM has a conditional `bx`/`pop` *plus* an unconditional body, while you emit a
predicated body and no early exit. Try this before the single-case switch — it is one edit, and on
this function the switch *overshot* by 4 B while inverting the guard hit it exactly. Note also that
the ROM materialised `-1` with `mvn r1,#0` and compared register-to-register; that is normal for
-1 (ARM cannot encode it as a `cmp` immediate) and is **not** a signal to introduce a variable —
doing so here made it 4 B shorter, not longer.

## ★★★ An early exit that never writes r0 = a BARE `return;` in a value function
*(func_ov008_0206f914 + func_ov008_02074150, 2026-07-18 — both matched at once)*

ROM: `popeq {r4,r5,r6,r7,r8,pc}` on the guard path, with **no `mov r0, …` before it**, in a
function whose normal exit does `mov r0, r5`. Any `return <expr>;` you write there compiles an
extra `moveq r0, rN` and lands 4 B long.

```c
int *f(int *param_1, …) {
    …
    if (param_1 == 0 || param_2 == 0 || param_4 == 0) {
        return;              /* ⚠ deliberate: no value */
    }
    …
    return (int *)result;
}
```

**This is a bug in the original game code, not a codegen trick** — on that path the caller reads
whatever is left in r0 (in practice `param_1`, which arrives there and is never clobbered, so it
happens to behave). mwcc accepts it. **Comment it where you use it**, or a future cleanup will
"fix" it and silently break the match.

**Tell:** the guard's `popeq`/`bxeq` sets no return value while the function's real exit does. Look
for the *absence* of a `mov r0` rather than for a wrong one — an absence is easy to read past.

## ★★ `return a && b;` BRANCHES; the ROM predicates — use a ternary
*(func_ov022_02093008 + func_ov022_02094174, 2026-07-18)*

`return f(a) && cond;` makes mwcc branch over the second test (`beq` + `mov`), where the ROM
predicates it (`moveq r0,#0` / `movne r0,#0`). Rewrite:

```c
return func_02092ff0(a) == 0 ? 0 : *(int *)(a + 0x958) == 0;
```

⚠ **This is the OPPOSITE direction from the one-case-switch lever below.** `&&` predicates too
little here and too much there — read the diff to see which way you are actually fighting before
reaching for either.

## ★★ Return the ACCUMULATOR VARIABLE, not the literal it holds
*(func_ov022_02090308, 2026-07-18)*

Same `&&` shape, but the ternary alone still landed 4 B short. The ROM keeps an accumulator in a
callee-saved register **across the call** (`mov r4,#0` … `moveq r0,r4` … `movne r4,#1` …
`mov r0,r4`). What forces that is returning the *variable* on the early path:

```c
int result = 0;
if (func_02030694() == 0) return result;      /* NOT `return 0;` */
if ((*arg0 & 0x100) != 0) result = 1;
return result;
```

`return 0;` lets mwcc fold the variable away and re-materialise the constant. Same family as the
caller-return-type crack: **a value you keep referring to is a value the compiler must keep live.**

## ★★★ A one-case `switch` forces a real branch where mwcc if-converts — 3 functions
*(func_ov022_0208acc4, func_ov008_02068588, func_ov008_020685d0 — 2026-07-18)*

**This is now the go-to lever for "the ROM branches where mwcc predicates", and it is worth
reaching for early** — it paid three times in one session on two different shapes:

- **two chained guards**: `if (a) return; if (b) return;` — mwcc if-converts the *second* guard
  into the first (`ldreq`/`cmpeq`, 4 B short) where the ROM emits **two separate**
  `popne {r3,pc}`. Wrapping the first guard in `switch (x) { case 0: … break; }` restores both.
- **a compound condition**: see below.

```c
switch (*(int *)(p + 0x23c)) {
case 0:
    if (*(int *)(p + 4) != 0) return;    /* second guard stays a real branch */
    …
    break;
}
```

⚠ **The switch fixes predication, not block ORDER.** On `func_01ffa1b8` the same trick produced
the right size but emitted the two arms the other way round (`bne` + copy-block where the ROM has
`beq` + the small block); putting the small arm in `case 4` and the rest in `default` then
overshot by 4 B, and a `goto` form undershot by 4. Order and predication are separate knobs —
check the diff for which one you are actually fighting. That one is still open.

## ★★ A one-case `switch` forces a real branch where `&&` if-converts
*(func_ov022_0208acc4, 2026-07-18)*

ROM: `cmp r0,#0xa ; bne … ; cmp r1,#2 ; moveq r1,#1` — branch on the first test, predicate the
second. Both `if (a == 10 && b == 2)` and the nested-if spelling let mwcc if-convert **both** tests
into a `cmp`/`cmpeq` chain (20 B vs the ROM's 24 B):

```c
switch (arg0) {
case 10:
    if (arg1 == 2) arg1 = 1;
    break;
}
```

**The tell was that the ROM is one instruction LONGER than the natural C** — the same signal as the
assignment-expression note further down. When the ROM looks "worse", it is describing a source
construct you have not written yet. `if (a != 10) return b;` overshoots (28 B) and a `goto` lands
back on 20 B; the switch is what fits.

## ★ A `> 0` guard on an unsigned field: read it into an `int` first
*(func_ov008_02055ba4, 2026-07-18)*

ROM: `ldrh r1,[r6,#2]` (unsigned load) then `ble` (**signed** branch). Comparing the `u16` load
directly lets mwcc prove it non-negative and collapse `> 0` into `!= 0` → `beq`. Assign to an int
first and the signed compare survives:

```c
int n = *(unsigned short *)(p + 2);
if (n > 0) { do { … } while (i < (int)*(unsigned short *)(p + 2)); }
```

Note the loop condition still re-reads the field directly — the ROM re-loads it each iteration, so
do **not** reuse `n` there. Unsigned load + signed branch in the same function is the fingerprint.

## ★ Chained `v = i = 0` when the ROM COPIES a zero instead of materialising it
*(func_0203b9ac, 2026-07-18)*

ROM: `mov ip, #0` … `mov r2, ip`. Mine: `mov ip, #0` … `mov r2, #0`. One instruction, right size.
Two separate `= 0` initialisers each materialise their own constant; a **chained assignment makes
the second value a copy of the first**, which is exactly what the ROM shows:

```c
int i, v;
v = i = 0;                     /* NOT `int i = 0; int v = 0;` */
do { ...; ((int *)base)[i + 3] = v; i = i + 1; } while (i < 5);
```

**Tell:** a `mov rA, rB` in the ROM where you emit `mov rA, #K` and rB already holds K. The ROM is
telling you the two values share an origin in the source.

## ★ Opposite signedness on two byte reads in the SAME function
*(func_ov202_020cd4a0 + func_ov203_020d4d20, 2026-07-18 — both matched at once)*

The guard read is `ldrb` (unsigned) and the call argument is `ldrsb` (signed), in one 13-instruction
function. Getting the pair backwards costs the match, and **fixing the wrong one of the two looks
like progress** — the size goes right and you get a plausible one-byte diff, which reads as a
regalloc tie. Check every byte read separately against the disassembly; do not assume a function
has one convention.

## ★★★ THE CALLER'S OWN RETURN TYPE holds a register live -- 24 functions (2026-07-18)

*(c5c0 out-param family: ov131/132/133, ov161-166, ov181-184, ov202/203, ov250/251, ov022, ...)*

**Symptom.** 16 instructions, 72/72 B, everything identical except the ROM loads a stack
out-param into **r1** (`ldr r1,[sp,#8]` / `str r4,[r1]`) where mwcc uses **r0**. Two bytes.

**Cause.** The ROM's function is not `void` -- it **returns the result of the call it just
made**. That keeps r0 live from the `bl` to the `pop`, so the out-param load cannot have r0
and is forced into r1. It costs **zero extra instructions** (the value is already in r0 and
the epilogue is a plain `pop {...,pc}`), which is exactly why the size was right all along
and why nobody suspected the signature.

```c
int f(int this_) {                      /* NOT void */
    int *entry;                         /* no initialiser -- see the 2026-07-17 note */
    int rc = func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x10, cb1, cb2, &entry);
    *entry = this_;
    return rc;                          /* <- this is the whole crack */
}
```

**Why it survived so long, and this is the transferable part.** The park note was the most
thorough in the project: 27 mwcc builds, 44 flag combinations, all 16 `-opt` toggles, both
`-lang` modes, 13 source spellings, 5 out-param shapes, plus "all 24 instances in the ROM use
r1, so it is not noise" and "every mechanical lever is spent". **Every one of those levers
varied the CALLEE's declaration or the out-param's shape. Not one varied the caller's own
signature.** The list was long and it was all on one axis -- and its length is precisely what
made it persuasive.

So, generalising: **a function's return type is part of its register allocation.** When a
value returned by a call is still sitting in r0 at the point where the ROM avoids r0, ask
whether the enclosing function returns it. Add to the pre-park checklist: *is our `void`
actually `void`?* A discarded return value frees r0; a propagated one reserves it.

⚠ **It does NOT generalise beyond this shape.** The same transformation was applied
mechanically to all 144 remaining parks at <=20 bytes off, trying every discarded call in
each: **0 hits.** The tryer was self-tested against the known positive first (it finds it),
so that zero is a real negative, not a broken search. Do not re-run that sweep.

★★★ **ARRAY LOOKUPS: index the array, don't rebuild the address — and DUPLICATE the lookup.**
*(2026-07-20, `func_ov029_020b2ee0`. Closed ov029 at 2/2 after the function had been parked as an
unbreakable register-allocation tie with ~19 source spellings, all 12 compilers on the 2.0/3.0
line, and 10 extra flag sets ruled out.)*

**→ The three rules live at the END of this file** ("Si estas casteando punteros, la C esta mal"),
written by the user with the root cause: *deriving the byte offset BECAUSE THE ROM DOES IT* is
transcribing the ROM's shape into C, which this file already warns against elsewhere. Do not read
this block and that one as two findings; they are one, and that one is the fuller statement.

What this entry adds is the **process** lesson, because it invalidated a park that looked airtight:
~19 source spellings, all 12 mwcc builds on the 2.0/3.0 line, 10 extra flag sets, and an explicit
"STRUCT TYPING: six formulations tried, none match". **That last line had already tried plain
indexing — but kept the cached `g` pointer, so only half the idiom was ever applied, and the whole
axis got recorded as closed.** When a park says "N formulations tried", ask whether the N were
independent or whether one unexamined decision rode along in all of them. Retraction in
`deferred-ties.md`.

★★★ **A STRUCT CAN BE LOAD-BEARING FOR THE MATCH, not just documentation.**
*(2026-07-20, `func_ov008_0208b9e8` x3.)* The struct rule was added to SKILL.md for the port's
sake; this is the case where it paid in bytes.

The ROM re-reads the global on every use:

```
str r0,[r1,#8]      ; ctx.thread = alloc()
str r5,[r0,r3]      ; first store via the returned pointer
ldr r2,[r1,#8]      ; RELOADS ctx.thread
str r6,[r2,r0]
ldr r2,[r1,#8]      ; RELOADS again
```

Written with a plain `char *` global and hand-built offsets, mwcc keeps the alloc result in r0 and
CSEs every reload away — **4 bytes short**. Declaring the real types and going through them,
`ctx.thread->paramC = c`, forces the reload each time and matches:

```c
typedef struct { unsigned char osThread[0x2c0]; int paramA, paramC, paramB, pad; } CardThreadBlock;
typedef struct { unsigned char n, slot, pad[2]; int result; CardThreadBlock *thread; } CardTransferCtx;
```

Why: through `ctx.thread->f`, each access is a load from a *global* the compiler will not assume is
unchanged across the intervening stores. Through `p + 0x2c0` on a cached pointer, there is nothing
to reload. **So "write the struct" and "don't hand-CSE" are the same rule seen twice** — and note
the direction is the OPPOSITE of the ov029 case, where the fix was to stop caching. The invariant
is not "always reload" or "always cache": it is *say what the object is and let mwcc decide*.

★★ **A worked misdiagnosis worth copying (2026-07-20, `func_ov008_0208be4c` x3 family).**
Two separate wrong theories, both plausible, both burned experiments. The order that would have
been faster is exactly the pre-park checklist's order:

1. **Size 4 over.** Real cause: the ROM *shares* its exit block (`beq` to the same
   `movs r0,#1; pop` the tail uses) and my C duplicated it. Fix: move the main path INSIDE the
   `if` so the early return falls into the shared tail. (Already catalogued; recognise it by a
   `b*` whose target is the function's own final instruction pair.)
2. **Then one extra instruction — the ROM had `adds r0, r1, #0`, a register copy.** I read that as
   the `add rX,rY,#0` copy artifact and spent **8 experiments** on copy recipes and pool-load
   scheduling. Wrong. **It was ARITY**: the callee takes THREE args and the third is the `0x2018`
   sitting in r2 — which I had dismissed as leftover from the `muls`. *A constant still live in a
   register at the `bl` is an argument until the tree proves otherwise;* `grep`ing the callee's
   definition settled it in one command.
3. **Then only `ctx` in r1-vs-r2.** Declaration-order permutation (all 6) did nothing. Real cause:
   **hand-CSE.** I had written `ctx = data_global;` and used `ctx[...]`; the ROM writes the global
   out at every use. Removing the local moved it to r1 and matched.

So: **arity before scheduling, and "am I caching something the ROM re-reads?" before declaration
order.** Both were already rules; the cost came from trusting a shape diagnosis over a cheap check.

★ **SECOND SHAPE, found 2026-07-19 on `func_0202e8ec` (THUMB, 88 B) — `return <CONSTANT>;`,
where the constant is ALSO stored.** The sweep above only ever tried *propagating a discarded
call's result*, which is why it missed this: here nothing is returned from a call at all.

Tell: the function ends `ldr rA,[pc]; movs r0,#K; strb r0,[rA]; pop` — i.e. the ROM leaves the
**stored constant** sitting in **r0** at the `pop`. As `void`, mwcc instead hoists the pool load
into the THUMB load-delay slot ahead of the preceding store and swaps the pair:

```
ROM   movs r1,#0 ; str r1,[r5] ; ldr r1,[pc,#4] ; movs r0,#1 ; strb r0,[r1]
void  movs r1,#0 ; ldr r0,[pc,#8] ; str r1,[r5] ; movs r1,#1 ; strb r1,[r0]
```

Declaring `int f(...)` and ending `*g = 1; return 1;` matches byte-exact: **r0 is reserved for
the return value, so the 1 must live there, which forces the pool address into r1 and leaves no
free register to hoist into.** One source change fixes the register pair *and* the ordering.

Generalised tell, worth more than the instance: **when the last thing the ROM does before `pop`
is materialise a small constant into r0 and consume it, suspect the function returns that
constant.** Ruled out first, all still diff at the same byte: `int` returns on every callee,
`volatile` on the out-param, indexed vs deref global form, a local pointer, reordering the two
tail statements, and spelling the boolean as an explicit `if/else` (that one goes +4 bytes).

## ★ The build sweep, re-run on GOOD inputs (2026-07-17) -- `tools/build_sweep.py`

The old tie-suite conclusion ("all builds fail identically, retail is likely 3.0 >=140")
was drawn from sources that today's work proved were full of ordinary bugs -- so the
evidence for it was worthless even though the conclusion may be right. Re-ran it on the
four cases whose C is PROVEN correct (identical size AND identical instruction stream,
one caller-saved slot apart): ov000_020552b4, ov181_020ce664, ov206_020cd464,
ov185_020d11f4.

Result, across all 27 builds we have:

- **No build matches any of the four.**
- **All twelve 2.0/* builds + 3.0_136_patched + 3.0_patch4 produce BYTE-IDENTICAL
  output** on all four (17 / 27 / 44 / 112 bytes off, the same numbers everywhere).
  So within the set we have, "which point release" is not a question that has any
  traction -- the codegen simply does not vary across that whole range.
- 1.2/* and dsi/* are the wrong era entirely (sizes off by 8-70 B).
- 3.0_136 fails to compile (unpatched licence).

So the conclusion survives contact with correct inputs, and now rests on something.
Either these four need a build we do not have, or they are still a source problem --
and given the 18-0 record on parked files, do not assume the former.

**Use `tools/build_sweep.py <func> [...]` before ever claiming "unreproducible across
N mwcc generations" again.** Only feed it sources already proven correct; sweeping
doubtful C is what made the original tie-suite meaningless.

⚠ TRAP (hit on the tool's first run): `glob("src/**/calls/<name>.c")` also matches
`src/overlays/ovNNN/asm_stubs/calls/<name>.c`, and an asm stub reproduces the ROM under
ANY compiler -- the whole sweep came back MATCH and meant nothing. The tool now skips
`/asm_stubs/`. Same trap as the shadowing bug: a check that cannot fail is not evidence.

⚠⚠ TRAP #2, and it invalidates any THUMB sweep run before 2026-07-18: **the tool compiled
every build in ARM.** On a THUMB function that gives `size N` on all 27 builds -- i.e. the
sweep reports *"no compiler in existence reproduces this"* about C that is a PERFECT match.
Verified on `func_02020974` (2 B THUMB): 27/27 `size 4` before the fix, 27/27 `MATCH` after.
**994 THUMB functions have real C**, so this was ~8% of the corpus. Fixed -- the mode now
comes from `symbols.txt` and is echoed as a `# <func>: thumb|arm` header line.

Alcance real, comprobado antes de afirmarlo (regla "state the positive form first"): de los
421 parks, 334 mencionan compilador/build, y 44 de esos son THUMB. Pero **ese 334 es el
regex sobre-casando** -- "mwcc 3.0/139" aparece en casi toda nota. Inspeccionadas, las notas
THUMB son de clase "regalloc/coloring swap", no barridos. Como el tool es del 2026-07-17,
**no consta ningun park apoyado en un sweep**: el bug no invalido nada retroactivamente, solo
estaba armado para el siguiente THUMB que se barriera. No repitas ese censo.
(De paso: esos 44 estan etiquetados con la clase que SKILL.md dice que no es un diagnostico
-- "coloring swap" es como se ve un argumento perdido. Es una veta, no parte de esto.)

Note the shape both traps share, because it is the thing to check in the NEXT tool: each
one made the sweep return a **uniform** answer across all 27 builds, and uniformity is
exactly what a clean, trustworthy result looks like here. When a sweep comes back perfectly
uniform, ask what would make it uniform *for a reason unrelated to the compiler*.
The four-case result above stands: it was re-run on ARM functions, whose mode was right.


---

## A "dead self-store" `field[1] = field[1]` is the HIGH WORD of a 64-bit field op
*(func_ov022_0209a68c, 2026-07-17 -- rescued a "not reproducible without the header's 0-flag macro" park)*

**Symptom.** The ROM writes a field back to itself through an identity ALU op that mwcc's -O4
deletes: `orr rHi,rHi,#0 ; str rHi,[base,#4]` next to a real `orr rLo,#0x200 ; str rLo,[base]`, or
on the clear side `and rHi,rHi,#0xffffffff` sharing its `mvn` with the low word's `~0x200`:

```
ldr r1,[r4] ; ldr r0,[r4,#4] ; orr r1,r1,#0x200 ; str r1,[r4] ; orr r0,r0,#0 ; str r0,[r4,#4]
mvn r1,#0 ; ldr r3,[r4] ; sub r0,r1,#0x200 ; ldr r2,[r4,#4] ; and r0,r3,r0 ; str r0,[r4] ; and r0,r2,r1 ; str r0,[r4,#4]
```

Both loads come out FIRST (paired), then both modify-stores -- the fingerprint of a single
double-word operation, and the `mvn` shared between `~0x200` (low) and `~0` (high) is the clincher.

**Crack.** It is one 64-bit `|=` / `&=` on the pair, not two 32-bit ops. `field[1]=field[1]` and
`|= 0` are both eliminated (size comes out ~8 bytes short); the 64-bit form keeps the high word
because mwcc will not drop half of a double-word op:

```c
*(unsigned long long *)base |= 0x200;                    /* low |= 0x200, high |= 0 */
*(unsigned long long *)base &= ~(unsigned long long)0x200;/* low &= ~0x200, high &= ~0 */
```

The size tell before the fix is **short, not over** (the eliminated stores), which distinguishes it
from an arity/phantom-arg miss. (This function ALSO had a dropped trailing arg -- see the arity
rules -- so it read as a pure "dead store" only because two bugs stacked.)

## Dead compare chain => a switch whose cases have EMPTY bodies

**Symptom.** A compare whose flags nobody reads, usually chained with `cmpne` and ending in an
*unconditional* branch:

```
cmp r5, #0x2e ; beq <body> ; cmp r5, #0x2f ; cmpne r5, #0x30 ; b <next>
```

The last two compares are dead. **No `if` can produce that** -- an `if` reads the flags it sets.

**Crack.** They are switch cases with nothing in them but a `break`:

```c
switch (mode) {
case 0x2e: if (...) reinit(self); break;
case 0x2f:
case 0x30: break;           /* <- the dead compares */
}
```

mwcc emits the compare chain, then finds those cases' body IS the fall-through and folds the
`beq` into the unconditional `b`, stranding the compares. Proven byte-exact on
`func_ov036_020b352c` (204 B, x4).

WARNING: **Ghidra deletes the evidence.** It renders the whole head as a plain
`if (mode == 0x2e && ...)` and drops the empty cases entirely, because they have no effect. The
disassembly is the only place they exist -- which is the "decompile is not a source of truth" rule
in its purest form: here the decompiler is not wrong about BEHAVIOUR, only about SHAPE, and the
shape is what you are matching.

Related, same family: `case 0x2e: break;` as the FIRST arm of a sparse chain
(`func_ov041_020b3530`) -- a real empty case that is tested and branches to the exit. If you drop
it because "it does nothing", the chain reorders.

## Arity, the OTHER direction: a PHANTOM argument invented in the caller

The skill already warns that a DROPPED trailing argument does not change the size. The mirror bit
just as hard (2026-07-17, cost a `nonmatching/` write-up and blocked 28 functions):

`func_ov046_020b3508` was parked on the story that `020521a4` takes FIVE arguments and that the
ROM's `push {r3, r4, r5, r6, r7, lr}` was homing `param_4` into the arg5 slot for free -- a trick
mwcc would not reproduce. It takes **four**. Its `push` of r3 is **stack alignment**: 5 saved regs
plus lr is odd, so mwcc pushes a scratch register to keep sp 8-aligned.

**Read the callee's own prologue. It settles arity in ten seconds:**

| callee | prologue | verdict |
|---|---|---|
| `020521a4` | 64 B, `push {r3,r4,r5,r6,r7,lr}`, never reads `[sp,#0x18]` | **4 args** -- the r3 push is padding |
| `02052024` | `push {...9 regs}` + `sub sp,#4`, then `ldr r0,[sp,#0x28]` | **5 args** -- reads the incoming stack slot |

The positive form: **a function that takes a 5th argument MUST load it from
`[sp, #4*(pushed regs) + frame]`.** No such load => no 5th argument. And in the CALLER: a call with
a stack argument needs an outgoing area, so it must show either `sub sp,#4` or a `str rX,[sp]`. The
ROM had neither -- the tell was sitting in the write-up's own quoted disassembly, read backwards.

Corollary that also bit here: **never infer arity from the caller's push list.** `push {r3,...}` is
three different things depending on context -- alignment padding, a callee-saved save, or an
outgoing stack-arg slot -- and only the callee can tell you which.

And the general lesson, since this is the second parked write-up in two days to die this way:
**a confident nonmatching/ write-up is not evidence.** This one named the exact instructions, drew
the ROM-vs-mine comparison, cited a rule from this very file, and was wrong at the root. When a
write-up says "mwcc will not do X", check that X is what the ROM is even doing.

## The `020a46f8` trap: args set ABOVE the branch

`020a46f8` takes 2 args; Ghidra prints `func_0x020a46f8()`. The ROM sets `r0`/`r1` *before* the
conditional branch because they are shared with the OTHER arm's call (`020a384c(self, mode)`), so
they do not look like this call's setup and Ghidra's dataflow drops them. **When a call's args
appear to come from nowhere, look above the nearest branch for a shared setup.**


## Consecutive `||` gets RANGE-OPTIMISED; the compare chain needs a switch

**Symptom.** The ROM tests three consecutive values with a four-instruction chain:

```
cmp r8, #0x2e ; cmpne r8, #0x2f ; cmpne r8, #0x30 ; bne <skip>
```

and the obvious C gives you three instructions instead:

```c
if (mode == 0x2e || mode == 0x2f || mode == 0x30) { ... }
    -> sub r0, r8, #0x2e ; cmp r0, #2 ; bhi <skip>
```

**No ordering of the `||` chain prevents the range optimisation** -- measured on 0x2e/0x2f/0x30,
0x2f/0x30/0x2e and 0x2e/0x30/0x2f: byte-identical. Do not spend compiles permuting it.

**Crack.** A SWITCH with the cases sharing one body:

```c
switch (mode) {
case 0x2e:
case 0x2f:
case 0x30:
    ...
    break;
}
```

`if (x != A && x != B && x != C) { } else { ... }` gives the same chain, if a switch does not fit.
An `else if` ladder does NOT (it gives `cmp;bne;cmp;bne;cmp`). Proven on `func_ov044_020b3634`.

Note the interaction with the "dead compare chain" entry above: both come from a switch, and
together they say the same thing -- **mwcc's `cmp/cmpne/...` chain is a switch fingerprint.**
An `if` produces it only in the negated-and form.

## `((int *)p)[N]` vs `*(int *)(p + 4*N)`: identical address, different addressing mode

They are the same C value and they do NOT compile the same **under predication**:

```c
if (cond) { *(int *)(self + 0x6bc) = mode; }   ->  add r0, sb, #0x2bc      (UNCONDITIONAL!)
                                                   moveq r1, r8
                                                   streq r1, [r0, #0x400]
if (cond) { ((int *)self)[0x1af] = mode; }     ->  moveq r0, r8
                                                   streq r0, [sb, #0x6bc]
```

The offset (0x6bc) fits imm12 either way -- this is not an encoding limit. The cast-and-offset
form makes mwcc materialise a base address and hoist it OUT of the conditional; the index form
folds into the store's addressing mode and stays predicated. One instruction, and it was the last
one blocking `func_ov044_020b3634` (x4).

**Plain loads fold either way**, which is why this only ever shows up on a conditional store --
and why the same file can have `ldr r1, [sb, #0x6bc]` looking perfectly fine two lines above the
split store. **When a diff is one hoisted `add` in front of a predicated store, try the index
spelling.** Ghidra's `param_1[0x1af]` rendering is the hint, and this is one of the rare places
its array-index output should be transcribed literally rather than normalised to a byte offset.


## ** `ldm` to load + individual `str`s to store => it is VEC_Set, not a struct copy

**Symptom.** The ROM groups three loads and refuses to group the three stores:

```
ldr r2,[r0,#4] ; ldm r2,{r2,r3,ip} ; add r3,r3,#0x900
str r2,[sp] ; str r3,[sp,#4] ; str ip,[sp,#8]
```

Note this is **SUBOPTIMAL**, and that is the whole point: after the `add`, all three words are in
registers and an `stm` would have been legal and one instruction cheaper. Whenever the ROM leaves
an obvious merge on the table, stop trying to steer the merge and ask why the merge is not there
to make.

**Every copy spelling fails, and correctly so.** `stk = *p; stk.y += 0x900;` gives `ldm+stm` and
then a re-load to bump y. Field-wise gives three `ldr`/`str` pairs and no `ldm`. Fifteen spellings
were burned on this across three sessions (see the history in `func_ov294_020d1f94`), including
by-value (mwcc passes a 12-byte struct in r1/r2/r3, not by hidden reference) and three separate
locals (12 bytes SHORT, and unsound -- it relies on unrelated locals being laid out consecutively).

**Crack.** The block is a `VecFx32` and the ROM builds it with the SDK's `VEC_Set` inline:

```c
struct Vecx32 { int x, y, z; };
static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x; vec->y = y; vec->z = z;
}
...
VEC_Set(&stk, p->x, p->y + 0x900, p->z);
```

Both halves fall out for the right reasons: **the three ARGUMENTS are three adjacent loads off
`p`** -- mwcc groups those into the `ldm` -- and **the inline's body is three separate field
stores**. There is no copy for mwcc to optimise, so there is nothing to merge. Proven byte-exact
on `func_ov294_020d1f94` (x3).

This is the `-inline on,noauto` line in SKILL.md paying off literally: only `inline`-marked
functions inline, and the SDK's `static inline` helpers reproduce codegen that open-coding cannot.
`VEC_Set` lives in `sdk/include/fx.h` and had never been used in a matched file before this one.
**Source files here do not `#include`** -- they are self-contained, so copy the inline's exact body
into the file.

### The generalisable part: ask the CALLEE what the block IS

This was found by asking what `ov107_020c5c54` does with the pointer rather than spelling the copy
an eleventh way. It hands it to `0203ca30`, which writes the three words to +0x10/+0x14/+0x18 and
clears a bit at +0x28 -- i.e. it is a 3D vector going into a node's transform. **Once it is a
VecFx32 and not "three ints", VEC_Set is the obvious way to write it, and the shape stops being a
puzzle.**

So: **when a block of words is built on the stack and passed to a callee, decompile the callee
before choosing how to build it.** The SDK has an inline for most of these
(`VEC_Set`/`VEC_Add`/`MTX_*`), the inlines have shapes open-coding cannot reach, and the callee is
what tells you which type you are holding. Other stack-block builders in the ROM are worth
re-examining with this lens -- `sdk/include/fx.h` is full of unused `static inline`s.


## ** Ghidra normalises comparisons to constants ARM cannot encode

**Symptom.** Four extra instructions and two pool entries, from C that looks like a faithful
transcription of the decompiler:

```c
if (t > 0x32f) ...              ->  ldr r0, [pc, #..] ; cmp r1, r0 ; ble ...   (mine, 3 instr)
if (t >= 0x330) ...             ->  cmp r0, #0x330 ; blt ...                   (ROM, 2 instr)
```

Ghidra prints `0x32f <` and `< 0x881`. Those are the same conditions as `>= 0x330` and `<= 0x880`
-- but **0x32f and 0x43f are not ARM immediates and 0x330/0x440/0x880 are**, so the decompiler's
spelling forces mwcc to build the constant in a pool. `func_ov239_020cd224` lost 4 instructions
and two pool words to exactly this.

**Crack.** Read the immediate off the `cmp` and write the comparison on that side of the
off-by-one. The ROM's `cmp r0, #0x330 ; blt` IS the source's `>= 0x330`; the ROM's
`cmp r0, #0x880 ; bgt` IS `<= 0x880`.

Ghidra normalises every comparison to a canonical form (`<` with an adjusted constant), which is
correct C and destroys the encodability information. **The `cmp`'s immediate is the source's
constant.** This is the same class as the pool-label trap: the decompiler is right about
behaviour and wrong about shape, and the disassembly is where the shape lives.

Cheap rule of thumb: an ARM immediate is an 8-bit value rotated by an even amount. `0x330`
(0x33 ror 28) and `0x880` (0x88 ror 28) encode; `0x32f` and `0x87f` do not. **If Ghidra hands you
a comparison against a constant ending in `f`, suspect this before writing it down.**


## ** SDK-vein triage: stack-vector + branches match, heap-vector straight-line ties

After matching 14 functions off the VEC_Set/FX_Mul/Q12 cracks and parking 3, a clean split emerged
and it is worth using to pick candidates:

- **MATCH readily**: members with real control flow (a switch, multiple exits) AND whose scratch
  vectors are STACK locals. The branches give mwcc's scheduler room, and a stack destination lets
  it hoist the sin/cos table loads freely (no aliasing with a global). ov188, ov202/203, ov215/217
  all matched at exact size on the first or second compile.
- **TIE at near-exact size**: small straight-line members whose vector is written to PERSISTENT
  memory (a struct field at `state+N`). mwcc will not hoist the cos load above a store through a
  heap pointer -- it cannot prove `state+N` and `data_0203d210` do not overlap -- so the VEC_Set
  schedules one instruction differently than the ROM. ov214_020ce928 (the same VEC_Set that
  matched in ov188 on the stack), ov162, ov142 all parked here, all one reorder from exact.

**So when triaging this vein, prefer functions that (a) have a branch and (b) build their vector on
the stack.** The heap-destination straight-line ones are register/schedule ties -- real, catalogued
in deferred-ties.md, and not worth repeated single-function effort until that class is understood.
The tell for the tie before you even compile: the ScaleVec3Fx12/VEC_Set destination is a field of
the object (`piVar5 + 8`) rather than a `local_NN` on the stack.


## ** Parameter homing: read a register-passed vector through a POINTER, not the params

**Symptom.** A function opens with `push {r0, r1, r2, r3}` (homing ALL register args to the stack)
and the ROM later RE-READS those slots (`ldr r1, [sp, #0x4c]`), where the obvious C keeps the
value in a register and adds a `mov`.

**Why.** When a register-passed argument's ADDRESS is taken -- e.g. a vector arrives in r1/r2/r3
and `&arg` is passed to `VEC_*`/`normalise`/`atan2` -- mwcc homes it to the stack with that opening
push so the pointer has something to point at. The homed slots are then the canonical location,
and every subsequent use RE-LOADS from them.

**Crack.** Access the homed data through a POINTER, so mwcc reloads from the homed slots instead
of keeping a register copy:
```c
int f(int *self, int vx, int vy, int vz, int flag) {   /* vector in r1-r3 */
    int *v = &vx;                    /* homes {vx,vy,vz} contiguously */
    mag = normalise(v, v);
    idx = Q12(atan2(v[0], v[2]));     /* v[0], v[2] -- NOT vx, vz */
    ...
}
```
Writing `atan2(vx, vz)` with the bare params keeps mwcc's values in callee-saved registers and
costs a `mov` (one instruction over). `v[0]`/`v[2]` force the `ldr [sp,#...]` reloads the homing
set up. Proven byte-exact on `func_ov147_020ccb30` (x5, a Y-rotation helper).

Relies on the three vector params being homed contiguously, which the `push {r1,r2,r3}` guarantees
here -- so `&vx` legitimately addresses `{vx,vy,vz}`. This is the register-arg mirror of the
stack-struct spawn: the address escaping to a callee is what forces the memory layout, and the C
must then treat that memory as the source of truth.

## switch forces forward-branch dispatch (2026-07-18, func_ov185_020ce21c x3)

A small multi-case dispatch on one value (`msg[3]` == 0 / == 1, each with its own block) where the ROM
emits `cmp #0; beq case0; cmp #1; beq case1; b default` with case0/case1 as SEPARATE forward-branch
blocks. Writing it as `if (v==0){A} else if (v==1){B}` makes mwcc INLINE the first case as the
fall-through (`cmp #0; bne skip; A...`), which is -4B and wrong. **Write an explicit `switch (v) { case
0: A; break; case 1: B; break; }`** — mwcc then emits the forward-branch chain matching the ROM.
(Distinct from the two-equality `&&` guard tie in deferred-ties.md: that is one `if` with two
conditions and stays predicated; this is one value with multiple cases and a `switch` cracks it.)

## Loop base-address hoist: fold a big offset into the ldr displacement (2026-07-18)

Symptom: inside a loop, `*(T*)(base + BIG)` (or `*(u8*)(base+BIG)`) that the ROM reads with a plain
`ldr/ldrb [base, #BIG]` displacement compiles to an EXTRA `add rX, base, #partial` hoisted before the
loop, and mwcc then reads `[rX, #rest]`. Costs one instruction (+4B) and often an extra callee-saved
register. Cause: **BIG is a valid load displacement (<0x1000) but is NOT an encodable ARM ADD
immediate** (8-bit rotated). Examples that bite: 0x40c, 0x19e. mwcc does loop-invariant code motion of
the *address* `base+BIG`, splitting it into `base+partial` (encodable) + a leftover ldr displacement,
and hoists the add out of the loop. The ROM never needs the add -- the ldr displacement covers BIG
directly -- so it keeps `base` (self) in one register and reads `[self, #BIG]` every iteration.

Crack: express it as an indexed load so the offset folds into the ldr displacement and there is no
address to hoist:
  `*(struct slot **)(self + 0x40c)`  ->  `((struct slot **)self)[0x40c / 4]`
  `*(unsigned char *)(self + 0x19e)` ->  `((unsigned char *)self)[0x19e]`
mwcc then emits `ldr [self, #0x40c]` / `ldrb [self, #0x19e]` directly, no hoisted add, and the callee-
saved set shrinks to the ROM's. Proven on func_ov208_020d05c4 and func_ov185_020ce178 (both x3).
This is the same family as the array-index-vs-induction crack: prefer `((T*)base)[k]` over
`*(T*)(base + k*sizeof)` whenever you want mwcc to use scaled/displacement addressing instead of
materialising a pointer.

## Byte/word call-arg loaded inside the `if` instead of before the guard (2026-07-18)

Symptom: `if (cb != 0) cb(node, *(u8*)(self+K));` -- the ROM loads the byte arg BEFORE `cmp cb,#0`
(scheduled up), mwcc loads it inside the taken branch. Size matches; a 4-byte diff at the schedule
point. Crack: hoist the arg into a local computed just before the callback pointer is read:
  `b = ((u8*)self)[K];  cb = *(...)(node+0x1f0);  if (cb) cb(node, b);`
mwcc then materialises `b` ahead of the `cmp`. The local is NOT lifted out of the loop because the
intervening calls may alias it. Proven on func_ov185_020ce178.

## by-value vec3/struct param -> entry `stmdb sp!,{r0,r1,r2,r3}` spill (2026-07-18)

Symptom: the function starts by homing ALL incoming registers (`stmdb sp!,{r0,r1,r2,r3}`), then loads
the homed slots back with `ldmia`/`stmia` block copies and passes a pointer INTO the home area to a
callee. Cause: the C takes a small struct BY VALUE (e.g. `struct vec3 { int x,y,z; }` in r1,r2,r3
after `self` in r0) and (a) block-copies it into a field, (b) passes `&v` to a helper. mwcc homes the
struct param so its address can be taken. Crack: declare the by-value struct param.
  `void f(int *self, struct vec3 v) { *(struct vec3*)(self+6) = v; g(self+0xc, &basis, &v); }`
`self+6` (int* arith) = self+0x18; the whole thing reduces to the ROM's spill + two ldmia/stmia
copies + the `&v` (=home) argument. Proven byte-exact on func_ov208_020d3cc8 (x3).

## pass-through trailing param reserves its register (tail calls) (2026-07-18)

Symptom: a tiny function is byte-exact EXCEPT the one scratch register is r3 in the ROM and r2 in
mwcc's output (or vice-versa). If the function ends in a tail call `bx r12` to a helper, the ROM is
preserving a trailing param (r2) to forward it -> its scratch is pushed to r3. Fix: declare the extra
pass-through param and forward it, even if the body never reads it.
  `void f(int self, int node, int arg3){ ...; g(self, node, arg3); }`  (g's 3-arg form exists elsewhere)
mwcc then reserves r2 for arg3 and colors the temp r3, matching. Proven on func_ov208_020d3ba8 (x3).
This is the tail-call twin of the "dropped trailing zero-arg moves a constant to the wrong register"
rule: a preserved-but-unused trailing param changes register coloring without changing size.

## variadic va_start with the ROM's `bic` alignment (2026-07-18)

Variadic forwarders (`stmdb sp!,{r0,r1,r2,r3}` prologue) whose va_start emits THREE instructions
`add r3,sp,#N; bic r3,r3,#3; add r3,#4` (not the plain `add;add`) need the alignment baked into the
macro. mwcc has no stdarg.h on this include path -- inline the APCS macros. Use:
  typedef char *va_list;
  #define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))   // aligns &last down, +4
The plain `((char*)&(last)+sizeof(last))` form is ONE instruction short (no bic) -> 4-byte size gap.
Use the `& ~3` form when the ROM shows the bic. Proven byte-exact on func_ov002_0205287c (x3). (cf.
func_ov006_02051fbc note -- variadic prologue reproduces with these macros; only that one's body has a
separate register/memory reload tie.)

## force a non-coalesced reload with a volatile read (loop-carried CSE tie) (2026-07-18)

Symptom: a loop is ONE ldrh/ldr short. The ROM re-loads `*p` at the top of each iteration; mwcc 3.0/139
proves that value equals the previous iteration's loop-condition load (`while(*p)` / pre-indexed
`ldrh r1,[p,#2]!`) across the back-edge and reuses it -- eliminating the top load. This is the
"smarter compiler" tie (cf. func_ov006_02051fbc). Crack: force the top read to be a distinct load with
a volatile cast:
  `unsigned short c = *(volatile unsigned short *)p;`   // was `*p`
mwcc then emits the redundant `ldrh` the ROM kept; behaviour is identical (p's target isn't really
volatile -- document it as a matching device in the file). Proven byte-exact on func_ov008_020681b0
(x3, a UTF-16 text-draw loop). Only reach for this when the ONLY diff is a missing per-iteration
reload of a value also used by the loop condition.

## search-loop block order: put the "found" handler INSIDE the loop (2026-07-18)

A list/search loop `find node==target, then act on it` where the ROM lays out `cmp; bne <advance>` with
the FOUND/exit block as the fall-through and the list-advance block out-of-line at the end. Writing it
as `while(node!=target){advance}` gives TWO compares (132 vs 128); writing `for(;;){ if(node==target)
break; advance; }` gives one compare but SWAPS the blocks (advance inline, found out-of-line) -> byte
diff at the branch. Crack: move the found-handler INSIDE the loop, before the advance, ending in
return:
  for (;;) {
      if (node == target) { act_on(node); return; }
      node = advance(node);
      if (node == 0) return;
  }
mwcc then makes the found block the fall-through after `cmp; bne <advance>` and places the advance
out-of-line -- matching the ROM. Proven byte-exact on func_ov008_02050d50 (x3, an NNS_Fnd list
remove+free).

## switch value-select: default block FIRST + explicit case 0 sharing it (2026-07-18)

A value-select `x = pick(variant)` where the ROM tests `cmp #0/#1/#2` in order and places the DEFAULT
(fall-through) block immediately after the compare chain -- both `beq #0` and the fall-through land on
it with NO extra branch. An if/goto chain gets PREDICATED (`moveq r6,#k`) -> too short. A plain
`switch(1,2,default)` omits the #0 test -> too short. `switch` with case 0 and default LAST -> an extra
`b` to reach default (+4). The match: force the shared default block to be laid FIRST by listing it
first, with an explicit `case 0` sharing it:
  switch (variant) {
  case 0:
  default: x = 0x2c000; break;
  case 1:  x = 0x50000; break;
  case 2:  x = 0x74000; break;
  }
mwcc then emits `cmp#0 beq DEF; cmp#1 beq; cmp#2 beq; DEF: mov...; b end; case1..; case2..; end`, with
DEF reached by both the #0 branch and the fall-through. Proven byte-exact on func_ov008_02067970 (x3).
(Extends the "switch forces forward-branch dispatch" crack with case-ORDER control.)

## byte-loop over an int* struct: alias the base as char* up front (2026-07-18)

A `for(i..) { ((unsigned char*)ctx)[i+K] ... }` byte loop where `ctx` is an `int*` used elsewhere:
mwcc emits the per-iteration cast as a SEPARATE induction pointer (`mov r2,ctx; ... add r2,#1`), one
instruction more than the ROM, which keeps the counter `i` and recomputes `add r1,ctx,i; ldrb [r1,#K]`.
The recompute vs induction hinges on the cast: casting `int*`->`char*` inside the loop spawns a new
pointer. Crack: declare a char* alias of the base ONCE, before the loop, and index it:
  unsigned char *cb = (unsigned char *)ctx;
  for (i = 0; i < N; i++) { if (cb[i+K]) cb[i+K]--; }
mwcc then reuses the base register and recomputes `add r1,cb,i; ldrb [r1,#K]` per iteration (counter
`i` kept), matching the ROM. Only needed when the base is used after the loop (so it stays live) and is
a different pointer type than the loop element. Proven byte-exact on func_ov208_020d14c4 (x3).

## dedicated loop index to fix cross-loop register coloring (2026-07-18)

When a function has two (or more) loops and you reuse ONE function-scope `int i` for both, mwcc may
colour that shared index into a late/high callee-saved register in the SECOND loop, swapping it with
the loop-body pointer vs the ROM (e.g. ROM j=r7/node=r8; mwcc i=r8/node=r7 -- every body access
differs). Fix: give the second loop its OWN local index declared just before it:
  } else if (...) { int count=0; int j; for (j=0;j<4;j++){ int node=arr[j]; ... } }
mwcc then allocates count->r6, j->r7, node->r8 in order, matching the ROM. Proven byte-exact on
func_ov185_020ce59c (x3). Reach for this when two loops are otherwise correct but the later loop's
index and body-pointer registers are swapped.

## bit0 toggle: read the bit as a 1-bit bitfield (not (x<<31)>>31) (2026-07-18)

Flipping bit 0 of a byte and using the new bit: the ROM extracts bit 0 via `mov r0,b,lsl#0x1f; mov
r0,r0,lsr#0x1f` (shift pair). Writing `(((unsigned)b << 0x1f) >> 0x1f)` in C gets FOLDED by mwcc to
`and r0,b,#1` (one instruction) -- too short. Use a 1-bit bitfield read, which mwcc never folds:
  struct b1 { unsigned char lo : 1; unsigned char hi : 7; };
  unsigned char nb = (b & ~1) | ((((struct b1*)&b)->lo + 1) & 1);   // flip bit0
  int pick = ((struct b1*)&nb)->lo ? A : B;                         // use new bit0
Each `->lo` emits `lsl#0x1f; lsr#0x1f`. (cf. the bitfield-vs-shift note; same principle as the
flags16 `->lo` low-byte extract.) Seen in func_ov185_020ce40c.

## 24-bit big-endian byte-pack from message bytes (CONCAT13/12/11 + >>8) (2026-07-18)

Message handlers decode 3 consecutive bytes into a sign-extended 24-bit value. Ghidra shows
`x = CONCAT13(msg[a], CONCAT12(msg[a+1], CONCAT11(msg[a+2], (byte)x))); y = x >> 8;`. The ROM writes
the 3 bytes into the HIGH 3 bytes of a stack word (low byte left as garbage) then reads it as a SIGNED
int and `asr #8`. Reproduce with a struct whose byte 0 is an uninitialised pad:
  struct triple { signed char pad; signed char x0, x1, x2; };
  struct triple t;
  t.x2 = msg[a]; t.x0 = msg[a+2]; t.x1 = msg[a+1];      // stores land off3, off1, off2
  int val = *(int *)&t >> 8;                             // ldr; asr #8, sign from msg[a]
Do NOT initialise `pad` -- the ROM leaves it garbage (it is shifted out). The store ORDER x2,x0,x1
matches the ROM's `strb off3; strb off1; strb off2`. This is the key to the ov208/210 message-handler
class (each has 3 packs feeding a 0203ca30 transform, then a jump-table switch). Verified codegen; first
use pending on func_ov208_020d03e8.

## `-1` byte store: `mvn r0,#0` needs a SIGNED dest (not unsigned char)
Symptom: ROM materialises the byte value 0xff via `mvn r0,#0` (= 0xffffffff, low byte stored by
`strb`), but your C gives `mov r0,#0xff`. mwcc build 139 NARROWS a `-1`/`~0`/`0xffffffff` literal to
0xff (→ `mov #0xff`) when the store destination is `unsigned char`, but KEEPS it as -1 (→ `mvn #0`)
when the destination is `signed char` (or plain `char`, since `-char signed`). So:
```c
signed char *out;   // NOT unsigned char*
out[i] = -1;        // -> mvn r0,#0 ; strb
```
For a `short` (halfword) store mwcc emits `mvn`+`strh` regardless of signedness -- only the byte case
is signedness-sensitive. Proven byte-exact on func_ov002_02051d6c (BuildPanelIdSummary x3,
ov002/008/025): flipping the out param from `unsigned char*` to `signed char*` was the last of 4
fixes. Corollary: choose the pointer's signedness to match the field's real type -- it changes both the
loads (ldrb vs ldrsb) AND the `-1`-store encoding.

## Loop `i*K` index: struct-array subscript kills the strength-reduction second IV
Symptom: ROM computes `base + i*K` inline each iteration with a shifted-register add
(`add r2, base, r3, lsl #7` for K=0x80) while reloading `base` from memory; your C spawns a SECOND
induction variable (`add r3, r3, #0x80` plus its `mov r3,i` init = +2 instructions). Writing the
access as an arithmetic offset `*(T*)(base + i*0x80 + 3)` triggers mwcc's strength reduction. Fix:
express it as an array subscript through a correctly-sized struct so the scale is folded into the
addressing, not an IV:
```c
struct rec { unsigned char b[0x80]; };
out[i] = ((struct rec *)base)[i].b[3];   // -> add r2, base, i, lsl #7 ; ldrb [r2,#3]
```
Proven on func_ov002_02051d6c copy loop. (Same family as the array-subscript vs induction-pointer
crack already noted -- this is the "element stride is a power of two, base reloaded" variant.)

## u16 high-byte `hi |= K` RMW: write it EXPLICITLY, not as a `unsigned short hi:8` bitfield
Symptom: a `*(u16)` whose HIGH byte gets OR'd with a constant. The ROM does exactly (7 ops):
`ldrh; lsl#16; lsr#24; orr #K; bic #0xff00; lsl#24; orr rDst,rLow,rHi,lsr#16; strh`. A
`struct{unsigned short lo:8,hi:8;}; p->hi |= K;` bitfield ADDS a redundant `lsl#16;lsr#16` (it
re-masks to the 16-bit container width) -> +1 insn. Write the insert explicitly and DEFER the final
`>>16` into the OR so mwcc fuses it as a barrel shift:
```c
unsigned short v = *(unsigned short *)(p);
unsigned int hi = (((unsigned)v << 16) >> 24 | K) << 24;   /* byte in bits 24..31 */
*(unsigned short *)(p) = (v & ~0xff00) | (hi >> 16);       /* orr rDst, v&~0xff00, hi, lsr#16 */
```
Use `v & ~0xff00` (NOT `v & 0xff`) to get the ROM's `bic #0xff00` instead of `and #0xff`. Do NOT add
a `(unsigned short)` cast on the result -- the `strh` truncates, and the cast reintroduces a mask.
Proven on func_ov228_020d2078. (The INT-container low-byte `lo:8 |= K` bitfield DOES match as a plain
`struct{unsigned int lo:8,hi:24;}` -- the `and #0xff` insert mask is the correct container width
there; only the u16-high-byte case needs the explicit form.)

## `short` loop counter passed to an int arg: use `int` + `(short)cast`, not a `short` local
Symptom: a small signed loop counter (e.g. 3,2,1) passed to an `int` parameter. The ROM sign-extends
at the USE (`mov r2,rN,lsl#16; mov r2,r2,asr#16`) and decrements RAW (`sub rN,rN,#1`). A `short local`
makes mwcc keep the value PRE-sign-extended across the loop (an extra `lsl#16 ... asr#16` per iter, +1
insn). Fix: declare it `int` and cast at the call site -- `func(..., (short)sVar4, ...)`.
## ...and post-decrement `(short)v--` schedules the decrement into the call's arg-setup
The ROM often decrements the counter WITHIN the following call's argument setup (right after computing
`(short)v`, before the `bl`), not after the call returns. Writing `v--;` as its own statement after the
call schedules it after the `bl` (+reorder mismatch). Fold it into the arg: `func(..., (short)v--, ...)`
-- post-decrement uses the current value for the arg and emits the `sub` in the setup block. Both proven
on func_ov008_02067b0c (RenderTimeDigits x3): the signed `/10` came free from int-promotion of an
`unsigned short` (`x % 10`, `x / 10` -> smull magic 0x...*, `asr#2`, `+ (x>>31)`).

## ★★★ A BIT-0 TEST: `lsl #31 / lsrs #31` is a BITFIELD, and the CONTAINER TYPE picks ldr vs ldrb

Symptom: the ROM tests one bit with
```
ldrb r2, [r5, #0x694]
lsl  r1, r2, #0x1f
lsrs r1, r1, #0x1f
popeq {...}          <- early exit when clear
```
`(*(unsigned char *)(p + 0x694) & 1) == 0` gives `tst`/`ands` — ONE instruction where the ROM
has two, so it comes out **4 bytes short** and reads like a missing instruction. The `lsl`/`lsr`
pair is the bitfield signature:
```c
typedef struct { unsigned char b0 : 1; } Flags;
if (!((Flags *)(self + 0x694))->b0) return;
```
★ **The container type is not cosmetic.** `unsigned b0 : 1;` (word container) emits **`ldr`** and
leaves you 1 byte off — a single differing byte that is easy to misread as noise. `unsigned char
b0 : 1;` emits **`ldrb`** and matches. Same for `unsigned short` → `ldrh`. **Read the ROM's load
width and size the bitfield container to it.**
(func_ov038_020b3a6c, 2026-07-18: `& 1` → size -4, word bitfield → 1 byte, byte bitfield → MATCH.
Family of 4.)

## ★★ A 12-BYTE `ldm`/`stm` COPY: struct-typed FIELDS control the address ORDER

`ldm r1, {r0,r1,r2} / stm ip, {r0,r1,r2}` is a 3-word struct assignment. Writing it as
`*(Vec3 *)(node + 0xa8) = *(Vec3 *)(self + 0x904);` gets the copy right but computes the
DESTINATION address first, where the ROM computes the SOURCE first — 6 bytes, two swapped adds.

Hoisting the source into a local (`Vec3 *src = ...;` before the statement, or a whole block
earlier) does **not** move it: 6 either way. What does: **typing the destination parameter as a
struct pointer and writing the copy as a field assignment.**
```c
void f(int self, Node *node) {
    ...
    node->vec = *(Vec3 *)(self + 0x104 + 0x800);   /* MATCH */
}
```
This is the same "struct types vs pointer casts change SCHEDULING" family as
func_ov147_020ce2d0 — and it is worth re-reading that entry, because the lesson keeps recurring:
**when a residue is two swapped address computations, the fix is usually a type, not a reordering.**
Reordering statements is the instinct and it is the wrong axis.
(func_ov041_020b439c, 2026-07-18: 6 bytes across 4 reordering variants → MATCH on the struct form.
Family of 4.)

## ★★★★★ UN ARGUMENTO PERDIDO SE DISFRAZA DE "el temporal esta en otro registro"

`func_ov041_020b3c10`, 2026-07-18. Residuo de **3 bytes**: el ROM hace el test de bitfield en r2,
mwcc en r1. Todo lo demas identico. Parecia el empate de asignacion mas puro que se puede ver.

No lo era. El callee `func_ov041_020b3d84` toma **DOS** argumentos, y yo lo habia declarado con
uno. El ROM mantiene r1 intacto **porque r1 es el segundo argumento, vivo hasta la llamada**; con
la declaracion mala, r1 quedaba libre y mwcc lo usaba de scratch. Añadir el argumento → MATCH.

Esto refina la regla que ya estaba escrita ("un argumento perdido no cambia el TAMAÑO"): tampoco
cambia el numero de instrucciones ni el flujo. **El unico sintoma puede ser que un temporal
cualquiera este en otro registro** — que es exactamente la firma que uno clasifica como empate
del asignador y aparca.

Regla practica: cuando el residuo sea "un registro distinto para un temporal" y haya una llamada
cerca, **greppea la arity de TODOS los callees antes de escribir la nota del park**:
```
grep -rh "func_XXXX(" src/ --include=*.c | grep -v extern | sort -u
```
Cuesta diez segundos. En este caso la definicion real estaba en el arbol con su firma completa.

## ★★★★ `switch` con `default` PRIMERO: fija el ORDEN DE BLOQUES y evita la if-conversion

Sintoma: el ROM prueba dos valores con **saltos reales** y deja la salida por defecto en la
caida, con los bloques DESPUES:
```
cmp r0, #1 / beq bloque1 / cmp r0, #2 / beq bloque2 / pop   <- salida por defecto
bloque1: ... / pop
bloque2: ... / pop
```
Una cadena `if (x==1) {...} if (x==2) {...}` sale **4 bytes corta**: mwcc if-convierte el segundo
test (`movne r0, #0` y similares). Un `switch` normal (casos primero, `return 0` al final) tambien
falla. Lo que reproduce el layout es poner el **`default` EL PRIMERO**:
```c
switch (x) {
default:
    return;                 /* o `return 0;` */
case 1:
    ...; return;
case 2:
    ...; return;
}
```
Descubierto peleando func_ov044_020b3a2c (que sigue aparcada por otro motivo: no consigo que el
`0` de retorno ocupe r0 antes de las comparaciones). **El hallazgo transfirio inmediatamente**:
func_ov047_020b3950 estaba en `size -4` con la cadena de ifs y casó a la primera con esta forma.
Familia de 4.

Moraleja de proceso: una funcion aparcada puede dejar un crack aprovechable aunque ella misma no
case. Al escribir la nota del park, **anota explicitamente que SI funciono**, no solo lo que fallo.

## ★★★★ El ROM RE-EXTIENDE en cada llamada → el `short` esta en el PROTOTIPO, no en el cast

Sintoma: el mismo `lsl #0x10 / asr #0x10` (o `lsl/lsr` para unsigned) aparece **una vez por call
site**, en vez de una sola vez con el resultado guardado:
```
lsl r1, r4, #0x10 / asr r3, r1, #0x10 / bl f      <- primera llamada
lsl r1, r4, #0x10 / asr r3, r1, #0x10 / bl f      <- segunda, recalculado
```
Escribir `f(..., (short)idx)` en los dos sitios NO lo reproduce: mwcc hace CSE, extiende una vez
y guarda el resultado en un registro callee-saved (**size -4**). Declarar el parametro de la
funcion como `short idx` tampoco (**size -8**, la extiende en el prologo).

Lo que funciona es poner el tipo en el **prototipo del callee** y pasar el `int` tal cual:
```c
extern void func_0202accc(int a, int b, int c, short d);   /* <- aqui */
...
func_0202accc(obj + 4, 0, obj + 0xe4, idx);
func_0202accc(obj + 4, 2, obj + 0xe4, idx);
```
Asi la conversion es parte de **cada llamada** y mwcc la rematerializa en r3 (caller-saved) en vez
de mantenerla viva. (func_ov038_020b3fe8, 2026-07-18, familia de 4.)

## ★★★ Inicializa-y-asigna-condicionalmente vs booleano: `mov #0` ANTES del test

`loud = (*p & 0x200) != 0;` genera **dos** predicadas (`movne r1,#1 / moveq r1,#0`).
El ROM suele hacer `mov r1, #0` ANTES del `tst` y solo `movne r1, #1` despues — es decir:
```c
int loud = 0;
if (*p & 0x200) loud = 1;
```
Trece bytes de diferencia en func_ov047_020b3bfc, MATCH con la segunda forma.

## ★★★ Orden de bloques: NIEGA la condicion cuyo cuerpo va AL FINAL

Si el ROM prueba `x == K` y **salta hacia adelante** al cuerpo, dejando otra rama en la caida,
el cuerpo de `K` esta fisicamente despues. Reproducelo negando:
```c
if (a != 0x21) {
    if (a == 0x22) cb = &otro;      /* la rama que va en la caida */
} else {
    ...                              /* el cuerpo que va al final */
    cb = &este;
}
```
`if (a == 0x21) {...} else if (a == 0x22) {...}` da el layout inverso y 41 bytes de residuo con
el tamaño ya correcto — la señal de que lo unico mal es el ORDEN. (func_ov045_020b3b3c, familia de 4.)

## ★★★★★ El acumulador `off` que se inicializa DESPUES del guard = deja que mwcc lo INVENTE

Sintoma muy concreto. El ROM abre asi un bucle sobre entradas de paso fijo:
```
ldrb r0, [r6, #0x19] / mov r4, #0 / cmp r0, #0 / pople {...}   <- salida temprana
mov r5, r4                                                      <- off = 0, DESPUES del guard
mov r7, #6 / ...
```
Con un acumulador explicito (`for (i = 0, off = 0; ...; i++, off += 0x1c8)`) los registros salen
bien pero mwcc coloca el `mov r5, r4` **antes** del `cmp`: 12 bytes de residuo, y ninguna
reordenacion del fuente lo mueve. Probadas y descartadas 9 formas: `off` en el bloque interno,
ambos al principio, `off = i` tras el guard, `off = 0` tras el guard, `for (off = 0; ; )` con
break, guard como `== 0`, sentencias sueltas antes/despues...

Lo que casa es **no escribir el acumulador**: indexar y dejar que mwcc haga la reduccion de
fuerza y coloque el init de SU induccion donde el ROM lo tiene.
```c
for (i = 0; i < (int)*(unsigned char *)(self + 0x19); i++) {
    int e = *(int *)(self + 0xc) + i * 0x1c8;      /* <- sin `off` */
    ...
}
```
(func_ov039_020b45c0 y func_ov045_020b4900, 2026-07-18: 16 -> 12 -> MATCH.)

★ Es la contrapartida de la entrada vieja "array-index vs induction var": **cuando el init del
acumulador aparece DESPUES del test de salida, el acumulador no esta en el fuente.** Y de paso:
ese `cmp`+`pople` no es un `if` de guarda escrito a mano, es el **test de entrada del bucle** que
mwcc saca fuera — escribirlo como `if (n <= 0) return;` separado da peor asignacion de registros.

## ★★★★★ PRINCIPIO: si el residuo es de asignacion/planificacion, sospecha de una VARIABLE QUE SOBRA

Tres veces en una sola sesion (2026-07-18) el arreglo fue **borrar** un local del fuente, no
moverlo ni retiparlo:

| funcion | variable que sobraba | sintoma |
|---|---|---|
| func_ov039_020b45c0 | el acumulador `off` | su init salia ANTES del test de salida (12 B) |
| func_ov045_020b4900 | idem | idem |
| func_ov034_020b3c04 | `int k = idx.a[i];` | mwcc lo mantenia vivo en un callee-saved extra (`sl`), la lista del `push` crecia y el `add` no se recalculaba (size -4) |

El patron comun: **un local le da a mwcc una razon para reservar un registro callee-saved**, y a
partir de ahi la asignacion entera se desvia. El ROM, sin ese local, recalcula la direccion en un
caller-saved despues de cada llamada.

Como reconocerlo:
- La **lista de registros del `push` no coincide** (mia mas larga que la del ROM) → tengo un valor
  vivo de mas. Es el indicador mas rapido que existe: se lee en la primera linea del diff.
- Un `add`/`ldr` que el ROM **repite** y yo hago una sola vez.
- El init de un acumulador colocado antes del guard cuando el ROM lo pone despues.

Antes de barrer ordenes de declaracion (que es el instinto y cuesta muchas compilaciones),
**prueba a escribir la expresion inline en cada uso**. En func_ov034_020b3c04 nueve variantes de
orden no movieron nada y borrar `k` casó a la primera.

## ★★★★ Locales en la PILA: mwcc los coloca en orden INVERSO al de declaracion

Cuando una funcion arma una estructura de parametros en la pila y le pasa el puntero a otra, el
residuo puede ser simplemente que **los dos locales estan intercambiados de sitio**:
```
add r0, sp, #0     / add lr, sp, #0xc     <- ROM: el Vec3 en sp+0, los Params en sp+0xc
add r0, sp, #0x2c  / add lr, sp, #0       <- mio: al reves
```
Todos los `strh`/`str` salen entonces con offsets desplazados y el diff parece enorme (15 bytes
aqui) cuando lo unico mal es el LAYOUT.

Regla: **el ultimo declarado ocupa el offset mas bajo**. Si el ROM pone el buffer A en `sp+0` y
el B despues, declara `B` primero y `A` al final:
```c
Params p;      /* acaba en sp+0xc */
Vec3   v;      /* acaba en sp+0    */
```
(func_ov036_020b41e8, 2026-07-18: 15 bytes -> MATCH solo con intercambiar las dos declaraciones.
Familia de 4.)

Como reconocerlo en un vistazo: los `add rX, sp, #N` del prologo tienen **los mismos numeros que
el ROM pero asignados al reves**.

## ★★★★★ Las DOS formas de la extension de signo -- cuenta cuantas veces extiende el ROM

Complementa la entrada de func_ov038_020b3fe8. Hay dos codegen distintos y la eleccion depende de
**cuantas veces** aparece el `lsl #0x10 / asr #0x10`:

| el ROM extiende... | forma en C |
|---|---|
| **una vez** al principio, guardado en un callee-saved | parametro **`int`** + `(short)x` en el uso → mwcc lo CSEa |
| **en cada llamada**, en un caller-saved (r3) | el **prototipo del callee** lleva `short` y pasas el `int` |

★ Y la trampa que engloba a las dos: **declarar el PARAMETRO como `short` no genera ninguna
extension**. El ABI de ARM asume que el llamador ya extendio, asi que mwcc se limita a copiar el
registro. Es la opcion que parece obvia y es la unica que no sirve para ninguno de los dos casos.
(func_ov048_020b4050: `short idx` daba size -4 por la extension que faltaba.)

## ★★★★ El struct-typed tambien impide el HOISTING de direcciones invariantes

Otra cara del mismo crack. Escribir `self + 0x24c` dentro de un bucle hace que mwcc suba la
direccion a un callee-saved (loop-invariant hoisting); si hay varias, la lista del `push` engorda
-- en func_ov048_020b4050 paso de **6 a 10 registros** y sobraban instrucciones.

Con campos de struct (`self->anim`) mwcc las **recalcula dentro del bucle**, que es lo que hace el
ROM. Sintoma rapido, otra vez: **la lista del `push` mas larga que la del ROM**.

## ⚠ Una palabra del POOL que nadie carga: revisa los LIMITES del simbolo antes de pelear

func_ov044_020b3234 (THUMB, 2026-07-18) casa **entero** -- 31 instrucciones, mismos registros,
mismas constantes -- y aun asi sale `size -4`. Lo que falta es una **entrada del pool literal que
la propia funcion no referencia**: recorriendo las seis instrucciones `ldr rX,[pc,#N]` con el PC
alineado a 4, ninguna cae en ese offset.

Dos explicaciones posibles, y conviene descartar la segunda ANTES de gastar compilaciones:
1. El fuente original tenia un acceso que el optimizador elimino, dejando la constante huerfana.
2. **El tamaño del simbolo esta mal**: mwcc emite el pool al final de una funcion y una vecina
   puede compartirlo, asi que esos 4 bytes pueden pertenecer a otra funcion. Si es eso, tu `.c`
   ya es correcto y el problema esta en `symbols.txt`, no en el codigo.

Ninguna forma en C emite una palabra de pool SIN emitir tambien el `ldr` que la carga (un
`if (0 && ...)` se elimina entero; un acceso `volatile` añade la instruccion). Asi que si el
flujo de instrucciones ya casa y solo sobra pool, **el problema probablemente no esta en tu C**.

## ★★★★★ Bitfield `|= K`: CASTEA LA CONSTANTE al ancho del campo para quitar la truncacion

Sintoma: en una funcion con varias operaciones de bitfield empaquetado, unas casan y otra sale
**+8 bytes** con un par `lsl #0x10 / lsr #0x10` (o `#0x18`) de mas antes de mezclar el campo.

La logica del ROM es exacta y vale la pena entenderla:
- `hi &= ~1` **necesita** truncar: `~1` es 0xFFFFFFFE y ensucia los bits altos.
- `hi |= 0x82` **no** necesita: 0x82 no puede salirse de 8 bits.

mwcc no hace esa deduccion si la constante es un `int`. La forma que la reproduce es **castear la
constante al ancho del campo**:
```c
((struct hw60 *)(p))->hi |= (unsigned char)0x82;   /* MATCH */
((struct hw60 *)(p))->hi |= 0x82;                  /* +8: trunca de mas */
```
Descartado por el camino (func_ov123_020cda50, 2026-07-19): `hi = hi | 0x82` (+8), temporal
`unsigned char t = hi; hi = t | 0x82;` (+12), campo como `unsigned char` plano (-20, rompe la
extraccion), y **cambiar el contenedor del bitfield a `unsigned int`** (8 bytes -- era mi
hipotesis y estaba equivocada; el contenedor no es lo que importa, es el tipo del OPERANDO).

★ Generaliza: cuando el ROM NO trunca y tu si, mira si la constante puede desbordar el campo.
Si no puede, dilo con un cast.

## ★★★ Un offset que el ROM parte en dos `add` y mwcc pliega: mete un LOCAL intermedio

`add r2, r4, #0xfc / add r2, r2, #0x2c00 / add r0, r2, #4` -- el ROM llega a base+0x2d00 en TRES
pasos. Escribir `base + 0xfc + 0x2c00 + 4` deja que mwcc lo pliegue en un solo `add r0, r4,
#0x2d00` (0x2d00 SI es un inmediato ARM valido), y salen 8 bytes de menos.

La forma que lo reproduce es dar nombre al paso intermedio:
```c
char *blk = (char *)(base + 0xfc + 0x2c00);
func_0202a634((int)(blk + 4), ...);          /* MATCH */
```
(func_ov049_020b3a5c, 2026-07-19.)

⚠ Ojo a la asimetria con el principio "borra el local que sobra": **aqui el local hace falta**.
La diferencia es observable en el ROM antes de escribir nada -- si la direccion llega en varios
`add` encadenados, hubo un valor intermedio con nombre; si llega en uno, no lo hubo.

## ★★★ Structs de parametros grandes: la asignacion del valor CARGADO DEL POOL va TEMPRANA

Al rellenar una estructura de parametros en la pila (decenas de `str [sp, #N]`), el orden del
fuente **si** manda, pero no de forma literal: mwcc mantiene el orden relativo de los stores
baratos y **sube la CARGA** de los valores que vienen del pool literal, dejando su store donde
toque.

Sintoma: todo casa menos un tramo donde los stores salen desplazados un par de posiciones.

En func_ov036_020b4b9c (THUMB, 152 B) el ROM hacia `ldr r2,[pc]` (=0x7fffffff) justo despues del
store de `f24`, pero `str r2,[sp,#0x20]` diez instrucciones mas tarde. Escribir la asignacion
`p.f20 = 0x7fffffff;` en su posicion "logica" (tarde) daba 21 bytes; **moverla justo detras de
`p.f24`** -- donde el ROM hace la CARGA, no el store -- casa a la primera.

Regla: cuando un campo se rellena con una constante que no cabe en un inmediato, **coloca su
asignacion donde el ROM hace el `ldr [pc]`**, no donde hace el `str`.

## ⚠ `mla` (multiplicar-acumular): mwcc solo lo emite cuando el SUMANDO NO es un inmediato

Sintoma: el ROM hace `mov ip, #K2 / mov r1, #K1 / mla lr, r4, r1, ip` y mwcc parte la operacion
en `mul` + `add #K2` (10 bytes de residuo en func_ov045_020b4630).

Formas descartadas: `a * K1 + K2`, `K2 + a * K1`, las dos operaciones en sentencias separadas,
K2 en un local con nombre (antes y despues de la declaracion del resultado).

★ El corpus tiene **345 funciones casadas con `mla`**, y en las que mire el sumando venia de
**memoria**, no de un literal:
```c
return *(int *)((char *)&data_02047384 + 8) + arg0 * 0x30;   /* func_02012844: sale mla */
```
Hipotesis razonable: con un sumando inmediato mwcc prefiere `mul` + `add #imm`, que es igual de
corto en su modelo. **Si te topas con esto, comprueba si la constante del ROM podria ser en
realidad un campo leido de memoria** -- ahi es donde estaria la diferencia, no en como escribes
la expresion.

## ★★★ DOS bucles seguidos: el original usa DOS juegos de variables, no uno reutilizado

Sintoma: el primer bucle casa y en el segundo los registros del contador y del puntero salen
**intercambiados** (8 bytes tipicos).

Reutilizar `i`/`q` en los dos bucles es lo natural al escribir C y es lo que rompe la asignacion.
Declarar un segundo juego (`j`/`r`) lo arregla:
```c
int i;  char *q;
char *r;  int j;                      /* <- segundo juego, y su orden tambien importa */
for (i = 0, q = p;        i < 6; i++, q += 0x120) { ... }
for (j = 0, r = p + 0x12c; j < 6; j++, r += 0x120) { ... }
```
(func_ov046_020b3974, 2026-07-19: 34 -> 8 -> MATCH. El orden `char *r; int j;` casa y
`int j; char *r;` se queda en 8.)

Encaja con lo que ya sabiamos de func_ov042_020b3d34, donde el ROM tambien usaba r3 y r8 para dos
bucles distintos. **Cuando veas dos bucles con registros distintos para el mismo papel, el fuente
tiene dos variables.**

## ★★★ El acumulador, resumido: MIRA DONDE SE INICIALIZA (tres casos ya vistos)

Tres funciones, tres respuestas distintas, y el ROM lo dice siempre antes de compilar:

| ROM | significado | forma en C |
|---|---|---|
| el init del acumulador cae **DESPUES** del test de salida | lo invento mwcc (reduccion de fuerza) | **no lo escribas**: indexa `base + i * K` (func_ov039_020b45c0) |
| el init cae **ANTES** del bucle, junto a las demas inicializaciones | esta en el fuente | escribelo: `for (i = 0, q = p; ...; i++, q += K)` (func_ov042_020b3d34, func_ov046_020b43bc) |
| hay **dos** bucles con registros distintos para el mismo papel | hay dos juegos de variables | declara `i`/`q` y `j`/`r` (func_ov046_020b3974) |

★ En func_ov046_020b43bc el detalle fino: el ROM **carga** por `[r0, #0x128]` (el puntero base)
pero **guarda** el otro registro (`moveq r4, r3`), o sea que el fuente usa dos expresiones para la
misma direccion -- `if (*(int *)(arr + 0x128) == 0) slot = q;`. Sin el acumulador explicito, mwcc
lo resuelve con un `addeq` predicado y salen 8 bytes de menos.

## ★★★ Asignar a un BITFIELD de 1 bit: NO enmascares tu (`& 1` sobra)

`((Flags *)(p))->b1 = (unsigned char)r & 1;` emite un `and r0, r0, #1` **de mas**: la propia
asignacion al bitfield ya trunca (el ROM hace `and #0xff` + `lsl #0x1f` y descarta el resto).
La forma correcta es dejar que el bitfield haga su trabajo:
```c
((Flags *)(self + 0x694))->b1 = (unsigned char)r;    /* MATCH */
```
(func_ov049_020b39a8, 2026-07-19: +12 con `& 1`, +8 sin el, MATCH al arreglar tambien el return.)

## ★★★ Un `return` dentro de un `if` anidado cuando el ROM CAE al final

Si el ROM termina con un `mov r0, #0` compartido al que llegan todos los caminos, escribir
`if (cond) return 0;` dentro del bloque genera un epilogo predicado de mas (`movne`/`popne`).
Invierte la condicion y anida:
```c
if (func_02030788() == 0) {          /* en vez de `if (...) return 0;` */
    ...
}
```
Ojo: esto NO contradice la entrada de `deferred-ties.md` sobre salidas unicas. Alli el ROM
**saltaba** a un `pop` compartido y no habia forma de evitar el `popne`; aqui el ROM **cae** a un
valor de retorno comun, y la estructura del fuente si lo controla. **Mira si el final del ROM
calcula algo (cae) o solo hace `pop` (salta).**

## ★★★★★ Un LOCAL QUE NO USAS desaparece: si el ROM lo rellena, es un ARGUMENTO

Sintoma brutal (`size -32`): escribi dos structs locales, uno se rellenaba desde una tabla y
ajustaba un campo... y **nunca lo usaba**. mwcc lo elimino entero y con el las 8 instrucciones que
lo rellenaban.

El ROM si lo rellenaba, asi que tenia que usarse en algun sitio. Estaba en **r3, vivo desde un
`add r3, sp, #0` varias instrucciones antes de la llamada**: era el cuarto argumento.

```
add r3, sp, #0      <- r3 = &b
ldm/stm             <- rellena b
mov r0, r6 / mov r1, r5 / bl f     <- r3 sigue vivo: f(self, node, &a, &b)
```

★ Es la version "por arriba" de la trampa del argumento perdido (que normalmente da size 0 o -4).
Regla: **si mwcc borra codigo que el ROM tiene, busca donde deberia usarse ese valor** -- casi
siempre es un argumento que no declaraste. Y mira los registros vivos ANTES de la llamada, no solo
los que se cargan justo al lado.
(func_ov049_020b4464, 2026-07-19: -32 -> 4 -> MATCH.)

## ★★★★ Dos parametros en registros INTERCAMBIADOS: quiza devuelve un STRUCT POR VALOR

Sintoma: los dos primeros parametros aparecen en registros callee-saved cruzados respecto al ROM
(`mov r5, r1 / mov r4, r0` en el ROM, al reves en el tuyo), y no hay orden de declaracion ni
reordenacion de sentencias que lo mueva.

Causa posible: la funcion **devuelve un struct por valor**. En el ABI de ARM eso pasa un puntero
oculto en r0 y desplaza los parametros reales, asi que declararla como
`void f(Vec3 *out, int self)` produce la asignacion cruzada aunque el codigo sea equivalente.
```c
Vec3 f(int self) { ...; return p; }      /* r0 = puntero oculto, r1 = self */
```
(func_ov035_020b3c8c, 2026-07-19: con el puntero de salida explicito los registros no encajaban
de ninguna forma; con retorno por valor encajan y solo queda otro residuo menor.)

Como reconocerlo: la funcion termina copiando un struct **al buffer apuntado por el primer
parametro** y no lo usa para nada mas. Eso es un retorno por valor, no un parametro de salida.

## ★★★★ Si el ROM CONSERVA una truncacion que mwcc pliega: separa DECLARACION de INICIALIZACION

Sintoma: el ROM hace `orreq r0, r6, #1 / lsleq r0, r0, #0x10 / lsreq r6, r0, #0x10` (calcula y
trunca a 16 bits) y mwcc emite un simple `moveq r6, #1` -- **8 bytes de menos**, porque sabe que
la variable vale 0 y pliega la operacion entera.

Escribir `unsigned short f = 0; ... f = f | 1;` no basta: mwcc sigue plegando. Tampoco
`int f = 0;` con cast explicito, ni `(unsigned short)((int)f | 1)`.

Lo que funciona es **declarar sin inicializar y asignar en una sentencia aparte**:
```c
unsigned short f;
f = 0;              /* <- sentencia, no inicializador */
...
f |= 1;             /* mwcc ya no pliega: emite el or y la truncacion */
```
(func_ov036_020b3e44, 2026-07-19: size -8 con todas las formas de inicializador, MATCH separando.)

★ Encaja con el patron general de la sesion: **el inicializador le da a mwcc informacion que la
asignacion no le da.** Vale la pena probarlo siempre que el ROM haga trabajo que parece
innecesario sobre un valor que tu tienes por constante.

## ★★★ `mov rX, r0` tras una llamada: el resultado se guarda ANTES de operar con el

Sintoma: el ROM hace `bl f / mov r3, r0 / sub ip, r3, #K` y mwcc emite `bl f / sub r7, r0, #K`
-- una instruccion de menos (`size -4`).

El `mov` extra no es ruido: significa que el fuente **guarda el resultado en una variable** y
calcula el derivado en otra sentencia.
```c
int r = f(...);          /* mov r3, r0 */
int lim = r - 0x9000;    /* sub ip, r3, #0x9000 */
```
Escribirlo en una sola expresion (`int lim = f(...) - 0x9000;`) deja a mwcc usar r0 directamente.
(func_ov039_020b44fc, 2026-07-19: size -4 -> MATCH.)

★ Es el mismo principio que la entrada del offset partido en varios `add`: **cada paso intermedio
que el ROM materializa corresponde a una variable con nombre en el fuente.** Cuando sobra un
`mov`/`add` en el ROM, casi siempre falta un local en tu C; cuando sobra en el tuyo, sobra el
local.

## `ldr rX, [rY], #N` post-indexado -> avanza el puntero DE VERDAD en el fuente

**Sintoma:** una instruccion de mas al final; el ROM hace `ldr r0,[r4],#0x10` y tu sacas
`ldr r0,[r4]` + un `add r3,r4,#0x10` aparte.

**Causa:** escribiste los dos accesos como expresiones independientes desde la misma base
(`*(T*)(base)` y `*(T*)((char*)p + 0x10)`), asi que mwcc materializa `p+0x10` en su propio
registro. El post-indexado solo aparece cuando el **puntero mismo** avanza.

**Forma que casa** (func_ov147_020cce70, familia CommitTrailTransform x5, 2026-07-19):

```c
int owner = *s;                      /* ldr r0, [r4], #0x10 -- la lectura */
s = (int *)((char *)s + 0x10);       /* ...y el avance, fusionados */
*(Vec3 *)(owner + 0xf0) = *(Vec3 *)s;
*(Vec3 *)s = data_02041dc8;
```

Es el mismo principio general ya anotado ("cada paso intermedio que el ROM materializa es un
local"), aplicado al reves: aqui el ROM **no** materializa el paso, asi que no debe haber una
expresion aparte -- tiene que ser una reasignacion del puntero.

## Bucle: el ROM salta al TEST primero y mwcc lo rota -> `goto` explicito

**Sintoma:** una instruccion de menos; el ROM tiene `b <test>` antes del cuerpo y mwcc entra
directo al cuerpo (rotacion de bucle, porque puede probar que `0 < 5` se cumple).

**Lo que NO funciona:** ninguna grafia de bucle lo evita. Probados y todos rotan igual --
`for`, `while`, `i * 4`, `i << 2`, `((int*)base)[i]`, `short i`, `unsigned`, helper `inline`,
constante `~0` en vez de `-1`.

**Lo que casa** (func_ov038_020b327c, familia de 16, 2026-07-19):

```c
    i = 0;
    goto test;
body:
    *(int *)(obj + i * sizeof(int) + 0x514) = -1;
    i++;
test:
    if (i < 5) {
        goto body;
    }
```

Es el crack de "goto range-opt" ya catalogado, aplicado a la rotacion. Escribir el orden de
bloques a mano es la unica palanca cuando el optimizador y el ROM discrepan en la ENTRADA al
bucle.

## `i * sizeof(T)` en vez de `i * N` mata la variable de induccion

⚠ **Generaliza a cualquier zancada potencia de dos**: usa el tipo cuyo `sizeof` da la zancada.
Zancada 4 -> `i * sizeof(int)`; zancada 8 -> `i * sizeof(long long)` (medido en
func_ov253_020cc9fc, 2026-07-19). Lo que cambia no es el numero: es que el operando pasa a ser
`unsigned`, y con eso mwcc recalcula `lsl` en cada vuelta en vez de mantener un acumulador.

## `i * sizeof(int)` en vez de `i * 4` mata la variable de induccion

Misma funcion. Con `i * 4` mwcc reduce la fuerza y mantiene un `k += 4` en un callee-saved
extra (que ademas cambia el `push`); con `i * sizeof(int)` recalcula `lsls r1,r3,#2` cada vuelta,
como el ROM. La aritmetica es identica: lo que cambia es que el operando pasa a ser `unsigned`.

## Un campo de struct que NADIE lee puede ser la unica prueba del layout original

Misma funcion: `sub sp,#0x18` (ROM) vs `#0x10`, y de paso el `push {r3,...}` de relleno que mwcc
mete para alinear. La causa era que el bloque de parametros tiene **cinco** campos y el codigo
solo escribe tres. Los dos muertos no generan ni una instruccion, pero reservan los 8 bytes.

⚠ Solo sobreviven si la direccion de la struct **escapa** (aqui se pasa `&params`). Rellenar con
`int pad[2]` NO vale: mwcc recorta la cola no usada salvo que sean campos con nombre de una
struct cuya direccion se toma. Barrer 3/4/5/6 campos y mirar el prologo cuesta cuatro
compilaciones y es lo que lo resolvio.

## Puntero vs entero en una suma: quien va primero en el `add`

**Sintoma:** un solo byte de residuo, `add r1, r1, r3` (ROM) contra `add r1, r3, r1` (tuyo).
Cambiar el orden de los operandos en C **no hace nada**: mwcc canonicaliza `a + b`.

**Causa:** con aritmetica de PUNTEROS mwcc pone siempre el puntero primero. El ROM lo pone
segundo, luego en el original la expresion era **entera**.

**Forma que casa** (GetRegionOfMBlock, 2026-07-19): tipar los campos como `int` y castear el
puntero, en vez de hacer aritmetica de punteros:

```c
typedef struct { int start, end; } Region;      /* no void* */
int payload = (int)b + 0x10;
out->end = *(int *)((char *)b + 4) + payload;   /* entero + entero */
```

## Funciones del SDK con sufijo `_` = ensamblador escrito a mano

`MTX_Identity43_`, `MTX_Identity44_`, `G2x_SetBlendBrightness_`, `GXx_SetMasterBrightness_`...
El sufijo de subrayado es la convencion de NitroSDK para las variantes en ensamblador. Se
reconocen porque emiten `stm rN!, {...}` con valores construidos en registros, y **mwcc no
genera `stm` para asignaciones escalares** -- solo para copias de struct completas. No se pueden
escribir en C; dejalas como stub y no gastes intentos (2026-07-19, comprobado en MTX_Identity43_:
12 `str` por mucho que se escriba con `*p++`).

## El extractor de bits NO siempre es un campo de bits

`ldrh` + `asr #8` + `and #0x7f` + `lsl #0x10` + `lsr #16` NO es `unsigned short x : 7`. Un campo
de bits sale como `lsl #0x11` + `lsr #25` (dos instrucciones). Las cinco de arriba son:
cargar a un `int` (por eso `asr` y no `lsr`), desplazar, enmascarar, y **asignar a una variable
`unsigned short`** (ese es el par lsl/lsr de 16). Ver GetRegionOfMBlock.

## Fusion de colas: si el ROM repite el codigo comun, hazlo ASIMETRICO

**Sintoma:** el ROM tiene las dos ramas completas y tu sacas `beq X; b Y` con el cuerpo comun
factorizado fuera. mwcc ha hecho *tail merging*: las dos ramas terminaban igual y las ha unido.

**Forma que casa** (func_ov002_02052308, 2 miembros, 2026-07-19): **cambia el ORDEN de las
sentencias comunes en una de las ramas**. Aqui las dos hacen `row += 0x34` y un `strh` a +0x18;
en la rama larga el ROM avanza el puntero ANTES del store y en la corta despues:

```c
if (mode != 2) {
    *(short *)(out + 0x18) = (short)*(const int *)(row + 0x30);
    row += 0x34;                 /* despues */
} else {
    out[0x13] = (char)(*(const int *)(row + 0x30) >> 12);
    row += 0x34;                 /* ANTES: esto es lo que rompe la fusion */
    *(short *)(out + 0x18) = 0xb33;
}
```

Sacar el `row += 0x34` fuera del `if` (lo natural) da el mismo resultado que tenerlo dos veces al
final: mwcc factoriza igual. La asimetria es la unica senal.

## Reasignar el PARAMETRO libera su registro

Cuando el ROM sobreescribe r0 con `self[1]` y tu lo dejas en r2, el fuente reasignaba el
parametro: `self = (int *)self[1];`. No siempre basta (ver func_ov241_020d0c5c, que sigue
empatado), pero es lo primero que hay que probar cuando el diff dice "el ROM usa el registro del
argumento y yo no".

## Un store predicado donde el ROM materializa el valor: mete un local

**Sintoma:** el ROM hace `movgt ip, r4` (poner 0 en un registro) y **un solo** `str` despues;
tu sacas `strgt` + `str` -- dos stores predicados.

**Causa:** escribiste el destino en las dos ramas. mwcc predica cada store.

**Forma que casa** (func_ov223_020d5024, 3 miembros, 2026-07-19): calcula en un local y guarda
una vez fuera del `if`.

```c
int scaled;
if (v > 0x1800) {
    scaled = 0;
} else {
    scaled = row[1] * (0x1800 - v) / 0x1800;
}
row[1] = scaled;        /* UN store */
```

Es el caso simetrico del crack de "retornos completos por rama" (G2_GetBG2ScrPtr, donde hacia
falta lo CONTRARIO: repetir la expresion entera en cada rama). La senal que los distingue esta en
el desensamblado: **cuenta los stores del ROM**.

## Divisor con desplazamiento: la magia no dice el divisor entero

`0x2aaaaaab` + `asr #10` NO es `/6`: es `/(6 << 10)` = `/0x1800`. El multiplicador magico fija el
factor impar y el desplazamiento la potencia de dos. Mirar solo la constante del pool y escribir
`/6` deja un residuo enorme que parece otra cosa.

## ★ El artefacto de copia `add rX, rY, #0` -- RECETA (2026-07-19)

Llevaba en el archivo como "artefacto sin receta" (la nota del RNG). La receta es:
**inicializar una variable A PARTIR de otra que ya vale lo mismo**, y hacerlo en una sentencia
separada de la declaracion.

Casa (func_ov025_020b0818, THUMB):

```c
unsigned i;                     /* declarada SIN inicializar, y la primera */
int found = 0;
char *cur = (char *)hdr[1];
unsigned count = (unsigned)hdr[4];
i = (unsigned)found;            /* <- esto es `adds r3, r4, #0` */
```

Detalles que importan, medidos:
  - `unsigned i = (unsigned)found;` en la declaracion NO vale (6 bytes de residuo): la asignacion
    tiene que ir **despues de todas las declaraciones**.
  - El orden de las otras declaraciones decide que registro toca a cada una; hubo que barrer las
    24 permutaciones para bajar de 17 a 2 bytes, y solo entonces la copia explicita cerro los 2.

Sintoma que lo delata: el ROM hace `movs rA, #0` y justo despues `adds rB, rA, #0` en vez de un
segundo `movs rB, #0`. Si ves dos ceros y solo un `movs`, es esto.

## Ancho del contenedor de un campo de bits: mira el par de desplazamientos

Un `and rX, rX, #0xff` tuyo contra un `lsl #0x18` + `lsr #0x18` del ROM significa que el original
lee un **campo de bits**, no un cast. Y el ancho del CONTENEDOR se deduce del par:

| ROM | contenedor + campo |
|---|---|
| `ldrb` + `lsl #0x1f` + `lsr #0x1f` | `unsigned char b : 1` |
| `ldrh` + `lsl #0x18` + `lsr #0x18` | `unsigned short b : 8` (el contenedor es de 16 bits) |
| `ldr` + `lsl #0x10` + `lsr #0x18` | `unsigned b : 8` en la parte alta de un contenedor de 32 |

⚠ Un `unsigned char b : 8` NO vale cuando el ROM hace `ldrh`: hay que declarar el contenedor del
tamaño que el ROM carga. En func_ov253_020cceb0 probar `unsigned char` daba -8 bytes y
`unsigned short low : 8; unsigned short high : 8;` cerro el hueco.

## Dos `if` anidados que mwcc funde: mete un booleano intermedio

**Sintoma:** el ROM tiene un booleano en un registro y un salto, y tu sacas una sola cadena de
condicionales predicados (`cmpne` encadenados) mas corta.

**Forma que casa** (func_ov026_020850e4): materializa el resultado del primer `if` en su propia
variable y ramifica sobre ella.

```c
int opaque = 1;
int plain;
plain = opaque;                  /* copia -> `mov r2, r1` */
if (entry != 0 && entry[5] != 1) {
    plain = 0;
}
if (plain == 0) {                /* el salto que mwcc no queria hacer */
    if (entry[6] != 2) {
        opaque = 0;
    }
}
```
Con `if (a && b) { if (c) ... }` directo, mwcc encadena `cmpne` y sale 16 bytes mas corto.

## `return;` sin valor en una funcion que devuelve algo

**Sintoma:** el ROM salta directamente al `pop`/`bx lr` **sin poner nada en r0**, y tu emites
`movs r0, #0` antes de salir.

No es un error de lectura: el fuente original tiene un `return;` pelado en una funcion declarada
con tipo de retorno. mwcc lo acepta (con aviso) y deja r0 como estuviera. Visto en
func_ov022_02082c90 (2026-07-19): la salida por el flag de bloqueo no fija el valor de retorno.

Escribelo tal cual y deja un comentario diciendo que es intencionado, o el siguiente que lo lea
"lo arreglara" y rompera el match.

## Salida temprana que el ROM comparte: dale la vuelta al `if`

**Sintoma:** el ROM hace `beq <bloque comun al final>` y tu emites el `movs r0,#0; pop` **en el
sitio**, con todo lo de despues desplazado.

**Forma que casa:** mete el camino PRINCIPAL dentro del `if` y deja el `return 0` al final.

```c
if (algo() != 0) {
    ...camino largo...
    return handler;
}
return 0;          /* el bloque comun, al final, como en el ROM */
```

Escrito como `if (algo() == 0) return 0;` seguido del camino largo, mwcc pone el retorno donde
esta la condicion. Es el mismo principio que "deja que el bucle no entre" (FSi_StrNICmp), en
version condicional.

## Buffer de pila: inicializador agregado, no asignaciones sueltas

**Sintoma:** el ROM materializa la direccion del buffer (`add r2, sp, #0`) **antes** de la
constante que va a guardar, y guarda a traves de ese registro (`str r1, [r2]`, `[r2,#4]`, ...);
tu emites `mov r1,#0` primero y guardas con `[sp]`, `[sp,#4]`. Residuo tipico: 10 bytes.

**Forma que casa** (func_ov008_0205951c y func_ov025_0208be04, 2026-07-19):

```c
int cfg[4] = { 0, 0, 0, 0 };     /* inicializador agregado */
```

NO valen (medidos, 10 bytes los tres): cuatro asignaciones sueltas; un `int *p = buf;` con las
asignaciones a traves de p; una struct de cuatro campos asignados uno a uno. Lo que cambia el
codigo es que el array **nace inicializado**: ahi mwcc trata el buffer como un objeto y saca su
direccion a un registro antes de rellenarlo.

## Dos stores adyacentes con las DOS constantes materializadas antes = un store de 64 bits

**Sintoma:** el ROM hace `ldr r1, pool; movs r0, #0; str r1, [rX,#N]; str r0, [rX,#N+4]` -- las
dos constantes primero y los dos stores despues. Tu emites `ldr; str; movs; str` (5 bytes de
residuo, solo el orden).

**Causa:** no son dos asignaciones de 32 bits: es **una de 64**.

```c
*(long long *)(page + 0x18) = 0x6646;    /* casa */
```

Probados y descartados: dos asignaciones con locales con nombre, y darles la vuelta. El tell es
que las dos constantes se materializan **antes** del primer store -- con dos asignaciones
independientes mwcc entrelaza cada constante con su store.

## ★ Un registro "sin poner" antes de un `bl` = la mitad ALTA de un retorno de 64 bits

**Sintoma:** el ROM llama a `bl f` con r0 y r2 puestos y **r1 sin tocar**, o guarda `r1` justo
despues de otro `bl`. Parece un bug o un argumento perdido.

**Causa:** la llamada ANTERIOR devuelve un `long long` (r0 = mitad baja, r1 = mitad alta), y ese
r1 es el valor que se esta usando.

```c
extern long long func_02020400(int a, int b);
...
self[0] = (char)(func_02020400(x, 6) >> 32);                 /* strb r1, [r4] */
g(self[1], (int)(func_02020400(x, 6) >> 32), 1);             /* bl g con r1 "sin poner" */
```

Medido el 2026-07-19 en func_ov002_0205e448 (MATCH) y func_ov002_0205e358. Antes de encontrarlo
probe: pasar la constante que quedaba en r1 (`movs r1,#6` de mas), y pasar una variable sin
inicializar (mwcc le da un callee-saved y la copia). **Ninguna de las dos es la respuesta: mira
que devuelve la funcion anterior.**

Corolario: cuando `bytedist` diga +4 en una funcion con llamadas encadenadas y el diff muestre un
`movs rN, #K` de mas justo antes de un `bl`, sospecha de un retorno de 64 bits.

## Un `mov r0, #K` de mas al final = la funcion DEVUELVE lo que devuelve la ultima llamada

**Sintoma:** el ROM acaba en `mov r0, #K; bl f; pop` y tu sacas `mov r0, #K; bl f; mov r0, #K2; pop`.

El ROM no vuelve a cargar el valor de retorno: **devuelve lo que dejo `f`**. En C:

```c
return func_ov000_0204d7c8(1);     /* no `func(1); return 1;` */
```

Detalle que lo hace facil de confundir: el `mov r0, #K` que se ve antes del `bl` es el ARGUMENTO,
no el retorno. Si el argumento y el valor que creias devolver coinciden (aqui los dos eran 1),
la version incorrecta parece plausible y solo la cuenta de instrucciones lo delata.

## Variable de resultado compartida en vez de dos `return`

**Sintoma:** el ROM pone `mov rN, #0` al PRINCIPIO (en un callee-saved), carga el otro valor en
el MISMO registro dentro del `if`, y acaba con `mov r0, rN`. Tu emites dos `return` distintos y
sales 4 bytes corto.

```c
void *next = 0;
if (cond) {
    ...
    next = (void *)&handler;
}
return next;
```

Es la version "con valor" del crack de compartir el bloque de salida. El tell inequivoco: un
`mov rN, #0` **antes** de la condicion, en un registro que sobrevive a las llamadas.

## Truncacion repetida: el TIPO DEL PARAMETRO, no el cast

**Sintoma:** el ROM repite `lsls r0,rX,#0x10 / lsrs r0,r0,#0x10` (o `lsl/asr` con signo) delante de
DOS llamadas distintas, y tu version la calcula una vez y la guarda en un registro. Salen 2 bytes
de menos por cada repeticion perdida.

`(unsigned short)id` escrito dos veces es UNA subexpresion comun y mwcc la elimina. Declarar el
parametro del callee como `unsigned short` y pasar `id` a pelo genera la conversion **en cada sitio
de llamada**, que es lo que hace el ROM:

```c
extern char *func_0202bfcc(unsigned short index);
extern int   func_0202c6a8(unsigned short id);
...
node = func_0202bfcc(id);
x    = func_0202c6a8(id);
```

Probado y descartado: `id & 0xffff` (misma CSE), `(unsigned short)(id | 0)`, variable intermedia.
Solo funciona por el prototipo. Es la version "de conversion" de la regla de la aridad: **el
prototipo del callee es parte del codegen del llamante, no solo de la comprobacion de tipos.**

## `char *` vs `int` en un parametro que se indexa: decide el reparto de registros

`func_ov023_02085910` sale identico instruccion a instruccion pero con **r5 y r6 intercambiados**
entre los dos parametros. Con `int args` + `(void *)(args + N)` en cada uso, mwcc le da a `args` el
registro alto; con **`char *args`** y `args + N` a pelo, le da el bajo, como el ROM.

Vale la pena probarlo siempre que el unico fallo sea un par de registros permutados **y uno de los
parametros se use como base de direcciones**: es de los pocos casos de "permutacion de registros"
que NO es la clase bloqueada. Descartados aqui: variable intermedia para el tag, declaracion
adelantada, reordenar declaraciones.

## Sin `mov r0,#K` antes del `pop`: la funcion devuelve lo que devuelve el callee

Variante del truco de `return f(x);`. Si el ROM termina cada rama con `bl f` seguido DIRECTAMENTE
de `add sp / pop` (sin cargar r0), el fuente es `return f(...)`, no `f(...); return 1;`.
En `func_ov023_02084994` esto ademas explica por que el ROM **duplica el epilogo** en las dos ramas
en vez de compartir uno: con `return f(...)` cada rama esta en posicion de cola. Escrito como
`f(...); return 1;` sale 4 bytes de mas (salto a un epilogo comun) y con `return 1;` dentro de cada
rama sale 4 de mas por otro sitio.

## `switch` vs `if / else if / else`: mira que instruccion sigue al primer `cmp`

Con dos casos y un default mwcc puede generar dos formas y NO son intercambiables:

- **`cmp #1; beq L1; cmp #2; beq L2; b Ldefault`** (los cuerpos DESPUES) = `switch`.
  Ver `func_ov023_02086470` / `func_ov023_02086bf8`.
- **`cmp #1; bne L2; <cuerpo del caso 1 aqui mismo>`** = `if / else if / else`.
  Ver `func_ov023_02084ae8`.

O sea: si el ROM **cae dentro** del primer caso, es un if encadenado; si salta a el, es un switch.
Escribir la otra forma da el mismo tamano con el orden de bloques cambiado, y el diff no lo canta
solo -- hay que mirar el destino del primer salto (otra vez).

## Locales agregados: se colocan en orden INVERSO de declaracion

`func_ov023_02084ae8` fallaba solo en `add r2, sp, #0` vs `add r2, sp, #0xc`: dos structs de 12
bytes al reves. mwcc apila los agregados **de arriba hacia abajo en orden de declaracion**, o sea:
**el que ocupa el offset MAS ALTO va declarado PRIMERO**. Confirmado con cuatro locales en
`func_ov023_0208632c` (0x54, 0x48, 0x18, 0xc -> declarados en ese mismo orden).

Diagnostico de un vistazo: si el unico fallo son offsets de `sp` permutados entre locales, es orden
de declaracion, no reg-alloc.

★ Corolario que costo tres compilaciones: **si un `int` cuya direccion se pasa acaba en un offset
ALTO junto a los agregados, no es un `int` -- es una struct.** mwcc pone los escalares con direccion
tomada en los slots BAJOS, antes que los agregados. En `func_ov023_0208632c` el "int slot" del ROM
esta en sp+0x54 y el frame mide 0x60 = 0x54 + 12: es una struct de 12 bytes de la que solo se lee
el primer campo.

## Un `char *` local que el ROM NO conserva: no lo metas en una variable

`func_ov023_0208681c` recarga `*(char **)(ctx + 0x128)` en cada uso en vez de guardarlo. Escrito
como `world = *(char **)(ctx + 0x128);` y reutilizado, mwcc lo mantiene vivo y lo derrama a la pila,
y salen 8 bytes reordenados. Escribiendo la expresion COMPLETA en cada sitio, mwcc decide por su
cuenta cual reutilizar -- y acierta. Regla: **no hagas CSE a mano; escribe lo que dice el ROM y
deja que el compilador la haga (o no).**

## El orden de los OPERANDOS de una comparacion decide que lado coge el scratch bajo

`func_ov026_02085b9c` salia identico salvo r3 e ip permutados en los dos `cmp`. Escribiendo la
comparacion al reves -- `(unsigned short)(cursor - box[0]) < (unsigned int)box[2]` en vez de
`box[2] > (...)` -- sale byte-exacto. Es otro "swap de registros" que NO es la clase bloqueada:
pruebalo SIEMPRE antes de aparcar cuando el fallo esta en un `cmp`.

(Y el `bls`/`movhi` del ROM frente a `ble`/`movgt` es lo que delata que la comparacion es SIN
SIGNO: con `unsigned char` a la izquierda y `unsigned short` a la derecha, las dos promocionan a
`int` y sale con signo. Hace falta un `(unsigned int)` explicito en un lado.)

## Division: cuenta las instrucciones antes de dar el divisor por bueno

`func_ov026_0208afc4` cargaba `0x2aaaaaab` (el magico de /6) pero llevaba un `asr #1` DETRAS del
`smull`: eso es **/12**, no /6. Escrito como `/6` la funcion sale 4 bytes corta y el diff solo
canta un `lsr` de mas.

Regla: el magico identifica el divisor **hasta un factor de dos**; el desplazamiento posterior
(`asr #N` sobre la parte alta) multiplica el divisor por 2^N. Y si la correccion de signo aparece
como instruccion SUELTA (`lsr r0,r1,#31` + `add r5,r0,r5,asr #1`) en vez de plegada
(`add r5,r5,r3,lsr #31`), es que hay desplazamiento -- porque el segundo operando del `add` ya esta
ocupado por el `asr`.

## `%` no es `a - a/b*b`

`func_ov026_02086778` (contador de tres digitos): el ROM hace la multiplicacion de vuelta con
`umull r0, r1, r4, r1` -- 64 bits -- y escrito como `value - value / 10 * 10` mwcc emite `mul`.
Con **`value % 10`** sale byte-exacto. Son la misma cuenta y distinto codigo; si ves `umull` donde
esperabas `mul`, es un modulo escrito como tal.

## Inicializador agregado vs asignaciones: mira DONDE estan los ceros

Dos formas de poner una struct local a cero y mwcc las coloca en sitios distintos:
- `Vec3 zero = { 0, 0, 0 };` -> los `str` salen al ENTRAR en la funcion.
- `zero.z = 0; zero.y = 0; zero.x = 0;` -> los `str` salen donde esten escritos.

En `func_ov026_02084fdc` el ROM los pone justo antes de la copia, o sea asignaciones (y en orden
z,y,x, que es el orden de los `str`). La entrada anterior de este fichero recomienda el
inicializador para un `int cfg[4]`; **no es una regla general, es cuestion de donde caen los
almacenamientos.** Mira el offset del primer `str` respecto al prologo.

## `lsr` frente a `asr`: `unsigned short >> N` NO da un desplazamiento logico

Trampa de promocion. `*(unsigned short *)p >> 3` promociona a **`int` con signo**, asi que mwcc
emite `asr` aunque el valor sea obviamente no negativo. El ROM emite `lsr`. Hace falta forzar el
tipo del operando:

```c
srcW = (unsigned int)*(unsigned short *)p >> 3;   /* lsr */
srcW = *(unsigned short *)p >> 3;                 /* asr  <- 2 bytes distintos */
```

Mismo origen que la comparacion sin signo de `func_ov026_02085b9c`: **`unsigned char` y
`unsigned short` promocionan a `int` CON SIGNO**, y hay que volver a poner el `unsigned` a mano en
cada operacion donde importe (desplazamiento, comparacion, division).

## Campos de estado del SDK: `volatile`, o mwcc hace CSE de las relecturas

`FS_WaitAsync` salia **40 bytes corto** con `*(int *)(file + 0xc)`: mwcc lee el campo de flags una
vez y reutiliza el valor en los cuatro tests. El ROM lo relee cada vez porque el campo lo modifica
una interrupcion -> es `volatile`.

```c
if ((*(volatile int *)(file + 0xc) & 1) != 0) ...
```

Regla: **si el ROM recarga la MISMA direccion varias veces sin que nada entre medias pueda
cambiarla, el campo es `volatile`.** No es solo cosa de los registros MMIO -- cualquier estado que
toque una IRQ (flags de comando, contadores de DMA, colas) lo lleva. Un tamaño mucho menor que el
original con la logica bien es la firma tipica.

(Y ese `movne r0,#1 / moveq r0,rZERO / cmp r0,#0 / beq` que parece redundante es la materializacion
de un bool: sale sola con el campo volatil; no hace falta inventar helpers `inline`.)

## El bool materializado (`movne rX,#1 / moveq rX,#0 / cmp / b`) = un helper `inline`

Cuando el ROM convierte una condicion en un 0/1 en un registro y LUEGO lo compara con cero, en vez
de saltar directo desde el `tst`, es que la condicion viene del **valor de retorno de una funcion
`static inline`** del SDK:

```c
static inline int FSi_IsCancelRequested(char *file) {
    return (*(volatile int *)(file + 0xc) & 4) != 0;
}
...
if (FSi_IsCancelRequested(file)) { ... }
```

⚠ MATIZ (2026-07-19, `func_ov002_02079f50`): **el `volatile` NO siempre hace falta.** Cuando el
valor que se enmascara viene del RETORNO DE UNA LLAMADA en vez de un campo de memoria, basta con el
helper `inline`:

```c
static inline int Ov002_IsAnimated(unsigned short id, unsigned char kind) {
    return (func_020235d0(id, kind) & 1) != 0;
}
```

El `volatile` hace falta solo cuando el operando es un campo que mwcc podria mantener en registro.

Escrito abierto (`if ((*(volatile int *)(file + 0xc) & 4) != 0)`) mwcc salta directo desde el `tst`
y salen 24 bytes de menos en `FSi_ExecuteAsyncCommand` (los dos `mov` de las constantes 0 y 1, sus
dos registros callee-saved en el push, y las materializaciones). Recuerda que el proyecto compila
con `-inline on,noauto`: **solo se inlinea lo marcado `inline`**, asi que estos helpers son
reproducibles al byte.

## Una carga hoisteada POR ENCIMA de un `return` temprano

`FSi_ExecuteAsyncCommand` empieza con `movs r6,r0 / ldr r4,[r6,#8] / popeq` -- lee `file->arc`
ANTES de comprobar si `file` es nulo. En ARM eso es seguro y mwcc lo hace solo... pero solo si en el
fuente la asignacion va antes:

```c
arc = *(char **)(file + 8);
if (file == 0) { return; }
```

Con el orden "natural" (comprobar y luego leer) mwcc respeta el orden y salen 4 bytes movidos.

## Bucle `while`: mwcc DUPLICA la guarda; si el ROM no la duplica, usa `goto`

Un `while (c) { body; }` normal en mwcc sale asi:

    test; beq fin; L: body; test; bne L        <- la condicion aparece DOS veces

El ROM a veces la tiene una sola vez, saltando dentro:

    b L2; L1: body; L2: test; bne L1

No hay forma de bucle estructurado que de la segunda (probados `while`, `for`, `while(1)+break`,
`if`+`do/while`, y `do/while` con una etiqueta dentro). La unica que funciona son **gotos
explicitos**:

```c
    goto test;
loop:
    func_02001f10(card + 0x10c);
test:
    if ((*(volatile int *)(card + 0x114) & 4) != 0) {
        goto loop;
    }
```

Diagnostico: cuenta cuantas veces aparece la condicion en el ROM. Dos = `while`; una = `goto`.
(Es la simetrica de la regla que ya estaba aqui para el caso contrario -- cuando el ROM SI prueba
antes de entrar y ninguna forma de bucle lo daba.)

## Predicacion vs salto en un if/else: pon el bloque LARGO primero

mwcc decide entre predicar las dos ramas o emitir un salto segun lo que le cuesta cada una, y esa
decision depende de **cual va escrita primero**. Si el ROM tiene un salto (`bne`) donde tu emites
`ldreq/streq`, prueba a invertir la condicion para que la rama con MAS instrucciones sea el `if`:

```c
if (next == 0) {                    /* bloque de 3 instrucciones -> va primero */
    global = alarm->prev;
} else {                            /* bloque de 2 -> se predica */
    next->prev = alarm->prev;
}
```

En `func_02003618` eso son exactamente los 4 bytes del `bne` que faltaban. Es la version "de
seleccion" de la entrada de arriba sobre el orden de los bloques: alli decidia el LAYOUT, aqui
decide si hay salto o no.

## `x == 0 || x == 1` se convierte en un test de RANGO; usa `switch`

mwcc ve valores adyacentes y emite `cmp r0,#1 / bhi` (comparacion sin signo de rango). El ROM de
`FSi_ReadTable` hace `cmp r0,#0 / cmpne r0,#1 / beq`, que es la forma de un **`switch` con dos
etiquetas encadenadas**:

```c
switch (r) {
case 0:
case 1:
    ...
    break;
case 6:
    ...
    break;
}
```

Regla general: `cmp/cmpne/beq` encadenados = `switch`; `cmp #N / bhi` = un `||` sobre valores
consecutivos que mwcc ha colapsado. Cuando el ROM compara valor a valor y tu emites un rango,
cambia a `switch` aunque en el fuente original "pareciera" un `if`.

## `(short)0xffff` es -1; `unsigned short` con `0xffff` sale del POOL

Almacenar el mismo patron de bits de dos maneras da codigo distinto:

```c
*(short *)(p + 0x1a) = (short)0xffff;     /* -1  -> mwcc lo deriva: sub r1, r2, #0x1a  */
*(unsigned short *)(p + 0x1a) = 0xffff;   /* 65535 -> ldr r1, [pc, ...] desde el pool  */
```

Con el cast a `short` el valor es -1 y mwcc lo saca en UNA instruccion de cualquier registro que
ya tenga algo cerca (aqui restando de un 0x19 que estaba vivo). Con `unsigned short` es 65535
positivo, que no cabe en un inmediato de ARM, asi que va al pool.

Diagnostico: **si el ROM carga una constante pequeña del pool y tu la derivas con un `sub`/`mvn`,
es que el fuente la trata como SIN SIGNO.** Costo 4 bytes en `func_ov105_020bd59c`.

## La asignacion COMO EXPRESION: materializa el bool sin romper la agrupacion de cargas

Caso que costo dos pasadas (`func_0200ea64`). El ROM quiere dos cosas a la vez:
lecturas agrupadas al principio **y** el bool materializado (`movne #1 / moveq #0 / cmp / b`).
Las formas obvias dan una u otra:

| como lo escribes | lecturas | bool |
|---|---|---|
| tres locales y `more = len != 0` | agrupadas ✓ | salta desde los flags ✗ (-12 B) |
| `more = (campo -= 0x200) != 0` | separadas ✗ | materializa ✓ |
| helper `static inline` que relee el campo | agrupadas ✓ | relee, no materializa ✗ (-4 B) |
| sin locales, todo en la expresion | agrupadas ✓ | `sub` en vez de `subs` ✗ (-4 B) |

★ **La que da las dos es la asignacion usada como expresion:**

```c
len = *(int *)(card + 0x24);
src = *(int *)(card + 0x1c);
dst = *(int *)(card + 0x20);
more = (*(int *)(card + 0x24) = len - 0x200) != 0;   /* subs + movne/moveq */
```

El `= ... != 0` obliga a mwcc a producir el valor del store como un bool con nombre, y como el
operando ya esta en un registro leido antes, las cargas se quedan donde estan. Merece la pena
tenerlo en el repertorio: es la unica forma que combina las dos propiedades.

## `volatile` rompe la FUSION DE STORES (`stm`) -- y suele ser lo correcto

`MI_SendGXCommandAsync` inicializa seis campos consecutivos de una struct global. mwcc fusiona los
dos primeros en `stm ip, {r0, r4}` (r0 < r4 y offsets consecutivos = fusionable) y salen 4 bytes de
menos; el ROM emite dos `str` sueltos.

La entrada anterior sobre romper la fusion recomendaba desordenar las sentencias. **Hay una via
mejor y ademas semanticamente correcta:** marcar `volatile` el campo que de verdad lo es.

```c
*(volatile int *)&data_020446b0 = 1;      /* el flag "ocupado" que lee la IRQ */
*(unsigned int *)((char *)&data_020446b0 + 4) = channel;   /* normal */
```

Un store volatil no se puede fusionar con uno normal, asi que el `stm` desaparece solo. Y el
indicio de que ESE campo es volatil ya estaba delante: el bucle de espera de mas arriba lo lee en
`while (*(volatile int *)&data_020446b0 != 0) {}`. **Si un campo se lee como volatil en algun
sitio, escribelo volatil en todos** -- ademas de ser correcto, arregla la fusion sin tener que
retorcer el orden de las sentencias.

## Direccion absoluta en la zona compartida: PUNTERO BASE en una variable, no la constante final

Aparecido dos veces el mismo dia (`PXI_SetFifoRecvCallback`, `PXI_InitFifo`). El ROM accede a
0x027fff88 como `base + 0x388`:

```c
int *shared = (int *)0x027ffc00;   /* la variable es lo que importa */
shared[0xe2] = 0;                  /* -> str r2, [r0, #0x388] */
```

Escrito como `*(int *)0x027fff88 = 0` **o** como `((int *)0x027ffc00)[0xe2] = 0` sin variable
intermedia, mwcc pliega la suma y mete 0x027fff88 entero en el pool -> `str r2, [r0]`.
Hace falta que la BASE sea una variable con nombre para que el desplazamiento sobreviva hasta el
`str`. (Los 4 bytes no cambian, pero el byte del desplazamiento si.)

## El truco de `i * sizeof(T)` NO basta si el indice es `unsigned`

Ampliacion importante de la entrada de la induccion en bytes. Con

```c
unsigned int i;
for (i = 0; i < count; i++) { ... base[i * sizeof(long long)] ... }
```

mwcc crea igualmente una induccion en bytes aparte (`mov r2,lr` + `add r2,r2,#8` + `add r0,r0,r2`)
y salen 8 bytes de mas. Con **`int i`** emite `add r0, r0, lr, lsl #3` como el ROM, aunque la
comparacion siga siendo sin signo porque `count` lo es (`blo`).

O sea: **el tipo del INDICE decide la induccion; el tipo de la COTA decide el signo del `cmp`.**
Son independientes y hay que elegirlos por separado. Visto en `func_0200c4fc`; en la familia de
destructores no habia salido porque alli las cotas son constantes y el indice ya era `int`.

## `switch` de dos casos con cuerpo de UNA instruccion: mwcc predica el primero, el ROM no

Variante fina de la entrada "switch vs if-encadenado". Con

```c
if (tab == 0) { caption = 0xd; } else if (tab == 1) { caption = 0x10; }
```

mwcc predica LAS DOS ramas (`moveq r5,#0xd` + `moveq r5,#0x10`) y ademas salta: sobra un `mov` y
faltan 4 bytes. El ROM deja la primera fuera de linea (`beq` + bloque al final). Con **`switch`**
sale exacto:

```c
switch (tab) {
case 0:  caption = 0xd;  break;
case 1:  caption = 0x10; break;
}
```

Regla practica: **cuando los cuerpos son de una sola instruccion, el if-encadenado y el `switch`
NO dan lo mismo** aunque la tabla de la entrada anterior sugiera que se distinguen solo por el
salto del primer caso. Prueba las dos formas; con cuerpos de una instruccion el `switch` gana casi
siempre.

## Indice de array para EVITAR que mwcc haga CSE de la direccion

Dos cargas con el mismo `base + i*4` y desplazamientos distintos, separadas por una llamada:

```c
*(int *)(rows + i * sizeof(int) + 0x14)   /* mwcc guarda base+i*4 en un callee-saved EXTRA */
*(int *)(rows + i * sizeof(int) + 0x28)   /* y lo mantiene vivo sobre la llamada: +4 bytes */

rows[i + 5]                               /* recalcula `add r0,rB,rI,lsl #2` antes de cada carga */
rows[i + 10]                              /* = lo que hace el ROM                               */
```

Con la forma `base + i*N + K` mwcc reconoce la subexpresion comun y la promociona a registro; con
**indice de array y el desplazamiento sumado AL INDICE** no la ve y recalcula. El sintoma es un
registro callee-saved de mas en el `push` (y a veces un `sub sp` para el area de argumentos).

⚠ Es la regla CONTRARIA a la de la induccion en bytes (`i * sizeof(T)` para que NO cree una
induccion aparte). Las dos son sobre el mismo trozo de sintaxis y tiran en direcciones opuestas:
- **una sola carga** por iteracion -> `i * sizeof(T)` (evita la induccion en bytes)
- **dos o mas cargas** con la misma base -> indice de array (evita la CSE de la direccion)

## Store condicional: `if/else` predica el STORE, el ternario predica el VALOR

```c
if (cond) { pos[0] = 0xe0000; } else { pos[0] = 0xd0000; }
/* -> moveq r0,#0xe0000 / streq r0,[sp] / movne r0,#0xd0000 / strne r0,[sp]   (4 instr) */

pos[0] = cond ? 0xe0000 : 0xd0000;
/* -> moveq r1,#0xe0000 / movne r1,#0xd0000 / str r1,[sp]                     (3 instr) */
```

Cuando las dos ramas escriben **al mismo sitio**, el `if/else` hace que mwcc predique el par
`mov`+`str` entero y sale una instruccion de mas. El ternario materializa solo el valor y deja un
unico `str`. Sintoma: ves `streq`/`strne` a la misma direccion donde el ROM tiene un `str` suelto.

(Complementa la entrada de "resultado compartido en vez de dos `return`": es la misma idea aplicada
a una asignacion en vez de a un retorno.)

## Dos escrituras a la misma zona: si hay UNA LLAMADA entre medias, salen dos bases

Patron que aparece mucho en las UI de overlay: el ROM calcula DOS descomposiciones distintas de la
misma direccion para dos escrituras.

```c
char *panel = st + 0xc54c;                     /* -> add r5, rSt, #0x14c  (+0xc400 al usar) */
*(int *)(st + 0xc54c) = f(...);                /* -> add r1, rSt, #0xc000 ; str [r1,#0x54c] */
*(int *)(panel + 4)   = g(...);                /* -> str [r5, #4]                           */
```

**Funciona solo si entre las dos escrituras hay una llamada** (`func_ov026_0208a584`: casa). Si son
ADYACENTES, mwcc unifica las dos expresiones por mucho que las escribas distinto y comparte la base
(`func_ov026_02087ebc`: 8 bytes de menos, sigue sin resolver -- ver `dudas.md`).

Diagnostico: cuenta las llamadas entre las dos escrituras antes de intentar reproducir dos bases.
Sin llamada de por medio, esta via esta cerrada y hay que buscar otra.

## Direccion grande usada VARIAS veces: escribe el split a mano

`st + 0x7530` no cabe en un inmediato ARM, asi que mwcc lo parte en `add #0x530` + `add #0x7000`.
Si la direccion se usa 4 veces y la escribes entera, **repite las dos sumas cada vez** (8
instrucciones). El ROM hoistea la parte baja y solo repite la alta:

```c
char *snd = st + 0x530;      /* add r4, rSt, #0x530   -- una vez  */
... func(snd + 0x7000, ...)  /* add r0, r4, #0x7000   -- en cada uso */
```

Son 16 bytes en `func_ov026_02089780`. Es la excepcion a "no hagas CSE a mano": cuando el ROM
hoistea una direccion PARCIAL (la parte baja de un split), esa parte SI va en una variable. La
regla completa queda: **escribe la expresion entera cuando el ROM recalcula la direccion COMPLETA;
usa una variable cuando el ROM recalcula solo la MITAD ALTA del split.**

## Struct de N bytes de la que solo se copian los primeros M

`func_ov016_020823b0` reserva 20 bytes de pila (`sub sp,#0x14`) pero el `ldm/stm` solo mueve 12, y
los otros dos campos se escriben sueltos (`str` a sp+0xc y sp+0x10). Eso NO es "una struct de 12 y
dos locales": es **una struct de 20 de la que se copian los tres primeros campos**:

```c
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z; int strength; void *source; } Hit;   /* 20 */

Hit hit;
*(Vec3 *)&hit = *(Vec3 *)(self + 0x1c);   /* ldm/stm de 12 */
hit.strength = *(int *)(self + 0x28);
hit.source   = self;
f(target, 0, &hit);
```

Escrito como struct de 12 + dos locales sueltas sobran 4 bytes de pila y el frame no cuadra;
copiando la struct entera (20) sobran 12 en el `ldm/stm`. **La pista es el tamaño del `sub sp`
frente al del `ldm`:** si el frame es mayor que la copia y los campos de mas se escriben
individualmente justo antes de la llamada, es una sola struct parcialmente inicializada.

## Comparacion con valor CONSTANTE que el ROM conserva: helper `static inline`

`func_ov002_02070110` hace tres veces `if (v != -1) *slot = v;` con `v` constante. Escrito abierto,
mwcc decide la comparacion en tiempo de compilacion y se lleva 12 bytes por delante. Metiendola en
un helper `static inline` sobreviven las tres:

```c
static inline void Ov002_SetSlot(void **slot, void *value) {
    if (value != (void *)-1) { *slot = value; }
}
Ov002_SetSlot((void **)rec, (void *)&func_ov002_0206ffa4);
Ov002_SetSlot((void **)(rec + 4), 0);
```

Es el mismo mecanismo que el del bool materializado, aplicado a una COMPARACION en vez de a un
valor: **el helper marca una frontera que mwcc no cruza para plegar.** Sintoma: el ROM compara
contra un centinela algo que a ti te parece obviamente constante.

---

## ★★★ Si estas CASTEANDO PUNTEROS, la C esta mal (2026-07-19, AetiasHax)

Vino de fuera, sobre `func_ov029_020b2ee0`, que llevaba meses aparcada con un diagnostico
equivocado y **cayo a la primera** al aplicar tres reglas. Las tres son generales:

**1. Un cast de puntero es un sintoma, no una tecnica.** Si escribes

```c
group = group << 4;
g = (OverlayGroup *)((char *)tabla + group);      /* MAL */
```

lo que estas diciendo es "esta tabla tiene elementos de 16 bytes", y eso se escribe
`tabla[group]`. Un programador del estudio no habria escrito el cast, asi que casi seguro
no esta en el fuente original, y la C que no se parece al original no casa.

**2. NO hagas CSE a mano. DUPLICA sin miedo.** Recomputar `tabla[group].campo[k]` en cada
uso, en vez de mantener un puntero que avanza, es lo que cerro los ultimos 4 bytes. mwcc
decide que comparte. Nos daba miedo "generar codigo de mas" y es al reves.
(Esta regla YA estaba escrita en `state.md` -- *"no hagas CSE a mano"* -- y aun asi hice lo
contrario. Tenerla escrita no basta si no se aplica al mirar un cast.)

**3. Dos variables escaladas por constantes DISTINTAS y sumadas = ARRAY ANIDADO.**

```c
(*(Fn *)(tabla + group + k * 4))();        /* group ya venia <<4, o sea *16 */
tabla[group].fns[k]();                     /* lo mismo, legible, y CASA */
```

★ **La raiz del error: yo derivaba el offset en bytes PORQUE EL ROM LO HACE.** Eso es
transcribir la forma del ROM a C, que es exactamente el anti-patron que este fichero ya
avisa en otro sitio ("stop transcribing the ROM's SHAPE"). El objetivo no es imitar el
ensamblador, es reconstruir el FUENTE; el ensamblador sale solo.

**Cuando aplicarlo:** cualquier funcion aparcada cuyo `.c` contenga `(char *)`, `(T *)` sobre
una tabla, o un offset en bytes calculado a mano. `python tools/audit_structs.py` cuenta esa
deuda. Es una veta de re-test, no un caso aislado.

## Loop over a table at a fixed offset: keep the offset as a DISPLACEMENT (2026-07-20)

`block + i * sizeof(T)` with `+0xNN` applied at each ACCESS keeps the ROM's
`add rD, rBase, rI, lsl #k`.  Folding the offset into the base — `((T *)(block + 0xNN))[i]`
— makes it a clean array, mwcc strength-reduces it to a walking pointer (`add r5,r5,#8`)
and burns an extra callee-saved register.  Rescued two functions parked as
"strength-reduction tie"; the park had tried three spellings and all three had folded
the base, so the axis was never actually tested.

Also: `i * sizeof(T)`, never `i * 8`.  A literal makes mwcc build a byte-stride
induction variable.

## Hand-hoisting a loop-invariant load: TRY BOTH, there is no rule (2026-07-20)

Two sibling families over the same table, matched an hour apart, need OPPOSITE spellings:
- 96 B `ApplyToLiveSlots` — hand-hoisting `p->a` COSTS 12 bytes.  mwcc hoists it itself
  and lands on the ROM's register count; hoisting in source adds a live value and a
  pushed register.
- 152 B `DrawLiveSlots` — hand-hoisting sx AND sy is REQUIRED, and `int i` must be
  declared before them.

Plausible discriminator is reuse count (two invariants used every iteration pay for
their registers, one does not) but that is a 2-point theory.  Treat it as a 2-way knob
to flip, like branch-vs-predicate.

## Reading fields through a struct pointer is not free

Same addresses, same semantics, different register allocation: on `DrawLiveSlots` the
`e->field` form diverges at 0x0c while byte-offset casts match.  When a pretty rewrite
of already-matching C fails, this is why — re-verify after any cosmetic pass.

## Clamp: in-place vs through a temporary are NOT interchangeable (2026-07-20)

    if (x > cap) x = cap;                  ->  strgt        (predicated STORE)
    t = x; if (t > cap) t = cap; x = t;    ->  movgt ; str  (predicated MOVE + plain store)

Readable straight off the disassembly, and a function can use BOTH: Ov*_AddToSecondaryTally
clamps totalA in place and totalB through a temp, 264 B apart on one byte at 0xff.
Same family as guard-early-exit: predication is the knob, and the spelling picks it.

## Hoisting a constant to function scope leaks into unrelated blocks

On func_ov000_02056e28, `int cap = 0x64000;` at function scope (to reproduce the ROM's
loop-hoisted `mov r1,#0x64000`) kept it live across the whole switch and made the two
EARLIER slot loops strength-reduce into walking pointers.  Scope a hoisted constant to
the block that uses it, and re-check the parts of the function you were not working on.

## ldm/stm block-move register roles: steer with the POINTER TYPE (2026-07-20)

For an inlined struct copy the ROM puts the SOURCE in lr and the DEST in ip.  When they
come out inverted, it is not statement order -- it is how the pointer chain is spelled:

    *(Pose *)(*(int *)*(int **)(obj + 0x38c) + 0x10) = ...   /* roles inverted */
    *(Pose *)(**(char ***)(obj + 0x38c) + 0x10)      = ...   /* ROM's roles   */

Same address, same semantics.  Use char ** / char *** chains and byte arithmetic for
any struct-copy destination.  A park on this shape had concluded "no C reordering flips
mwcc's inline-block-move register roles" -- correct, and it ruled out the wrong axis.
Cracked func_ov134_020cc448 x3 and confirmed on the 312 B x10 family.

## Arity: `extern int f();` is the absence of a declaration

Empty parentheses give the compiler no prototype, so every call under it compiles at any
count, silently.  Three parks died of this today (ov141 x7 at 300 B among them).
tools/audit_arity.py used to skip empty-paren externs as "carrying no arity claim" -- the
DECLARATION carries none, but the CALLS in the file do.  It now judges those directly and
found three more parked files the old check could never have flagged.

## Which SIDE of the assignment the temporary sits on (2026-07-20)

    target = func(...);  ctx->target = target;    /* str reads the COPY */
    ctx->target = func(...);  target = ctx->target;/* str reads r0, the ROM's shape */

Identical semantics; mwcc keeps the call's own r0 live for the store only in the second
form.  Dropping the temporary altogether is NOT the same fix -- on func_ov141_020cce98 it
cost 24 bytes.  Cracked that x7 family together with one more knob: the two radii are
summed target-first, and writing `owner + target` swaps the two loads and nothing else.

Generalises the existing "declaration order" and "don't hand-CSE" entries: when a value
is both stored and reused, the source decides which of the two copies the store reads.

## Where `&stackbuf` materializes: SCOPE is the knob (2026-07-20)

Symptom: the ROM computes the address of a stack buffer at one point and mwcc at another,
same size, "not steerable from C".  It is steerable.  Three positions, three spellings:

    use the array directly              -> `add r1, sp, #0` just before the call
    `T *p = buf;` at FUNCTION scope     -> hoisted ABOVE the guard
    `T *p = buf;` inside the post-guard block -> right after the guard  <- the ROM

Declaring the ARRAY in that block is NOT the same and does not work: it is the pointer's
live range that pins the materialization, not the object's.  Cracked func_ov137_020cd7e8 x7.

Caveat worth keeping: the same early-&buf symptom on func_ov141_020cd2b0 is NOT this.  That
one is parked on a real halfword-order difference and the block pointer changes nothing
there.  Same surface symptom, different cause.

## Declaration order sets the STACK LAYOUT, not just registers (2026-07-20)

mwcc gives the LOWER stack address to the LATER-declared local.  On func_ov147_020cca28 the
ROM has the Vec3 at sp+0 and the Xform at sp+0xc, so the Xform must be declared FIRST.
Declared the other way every frame offset is mirrored and the function reads as a scheduling
mess.  Check the frame offsets in the disassembly before assuming a register problem --
and note this is a SECOND thing declaration order controls, alongside register assignment.

## Two-value guards: use De Morgan or mwcc folds them into a range test (2026-07-20)

    if (x == 0 || x == 1)        ->  cmp #1 ; bhi          (unsigned range fold)
    if (!(x != 0 && x != 1))     ->  cmp #0 ; cmpne #1 ; bne   <- the ROM's chain

Only the negation blocks the fold; reversing the operands and going through an int local
both still fold.  Worth 4 bytes on func_ov147_020cdf70 x5.  A chain of THREE or more values
(Ov*_ReleaseByStateAndSyncSrt) has no range to fold into and needs no care.

## A 12-byte struct argument is passed in r1-r3 with `ldm`

`ldm r1, {r1, r2, r3}` feeding a call is not three separate loads -- it is mwcc putting a
Vec3 into the argument registers BY VALUE.  Writing the callee as taking three ints compiles
and does not match.  func_ov147_020cd50c x5.

## 24-bit big-endian unpack: reversed byte stores + `>> 8`

Three bytes written REVERSED into the high end of a stack word, then an arithmetic `>> 8`,
swaps the byte order and sign-extends from bit 23 in one step.  Model it as a
`union { int w[N]; unsigned char b[4*N]; }` -- the shift-and-or spelling emits shifts, not
the ROM's byte stores.

## Call results: intermediates decide whether the stores interleave (2026-07-20)

    v->z = f(); v->y = f(); v->x = f();       -> each store emitted between the calls
    z = f(); y = f(); x = f(); v->x = x; ...  -> all three held live, stored together

The ROM's shape tells you which.  On func_ov117_020cd698 x5 the ROM keeps all three roll
results in callee-saved registers and stores them after the last call, which only happens
with intermediates -- and their DECLARATION ORDER then has to follow the assignment order
(`int z, y, x;`) or the two callee-saved registers come out swapped.

## hw60: `|=` wants the explicit form, `&=` wants the bitfield

    hi |= 6   -> explicit extract/reassemble; the struct hw60 bitfield adds an
                 lsl#0x10/lsr#0x10 truncation pair, +8 bytes
    hi &= ~x  -> the bitfield form

Both appear within a few functions of each other in ov114/ov117, so neither is "the"
spelling for this field.  Confirmed again on func_ov117_020cd698.

## `sub rN, sp, #k` before an ldm/stm pair = a struct argument straddling regs and stack

A 12-byte struct passed BY VALUE occupies r2, r3 and the first outgoing stack word.  mwcc
lays the whole struct out at sp-8 so the third component lands at sp+0 by itself, which is
why a negative stack offset appears in an otherwise ordinary frame.  Write the parameter as
the struct type; three int arguments compile and do not match.  func_ov214_020ce768 x5.
See also func_ov147_020cd50c, where the same convention shows up as `ldm r1, {r1, r2, r3}`
when the struct fits entirely in registers.

## Hoisted constants: only a LEVER when they cross a call (2026-07-20)

func_ov127_020cc468's loop hoists six constants into callee-saved registers (0x800 and 0
twice each, plus 0xe0) and it matched first try from the ordinary static-inline FX_Mul
spelling -- they are the loop-invariant halves of the inlined 64-bit multiplies and mwcc
hoists them by itself.  Contrast the 96-byte Tally family, where a literal `1` had to become
a source-level variable because it is live across a CALL.

Rule of thumb: hoisting inside straight-line arithmetic is the compiler's job; hoisting
across a call boundary is the source's.  A wall of `mov rN, #const` in a prologue is not by
itself evidence that the source declared anything.

## SOLVED: a mask on one word and ZERO on the next is ONE 64-BIT FIELD (2026-07-20)

Generalised from OR to AND the same day.  The signature is always the same: a real mask
applied to one word, and the SAME OPERATION with zero applied to the word above it.

    *(long long *)(p) |= mask;   ->  ldr, ldr, orr low #mask, orr high #0, str, str
    *(long long *)(p) &  mask    ->  and low #mask, and high #0, cmp, cmpeq

The AND form turned up in func_ov049_020b35f0, where `and r3, r3, #0x100` on the low half
and `and r2, r2, r0` (r0 = 0) on the high half with a `cmp`/`cmpeq` pair is simply
`(*(long long *)self & 0x100) != 0`.  Do not read the zero operand as a no-op.

### Read the signature PER TEST, not per function

func_ov022_0209a1ac has five flag guards: four are 64-bit and the fifth, on an ordinary word
at +0x24, is a plain 32-bit `tst`.  Converting all five puts the function 16 bytes OVER;
converting the right four matches it.  Only the pairs where the ROM emits an `and rX, rY, #0`
beside the real mask are 64-bit fields -- a `tst` on its own is exactly what it looks like.

### Which half carries the mask tells you where the field STARTS

`and r1, r1, #0` on the low word with the real mask on the high one means the 64-bit field
begins at the LOW word's address and the constant needs shifting: 0x2000 in the high half is
`0x2000LL << 32`, not `0x2000LL`.  Writing it unshifted gives `orr r2, r1, #2` where the ROM
has `orr r2, r1, #0x2000` and costs 4 bytes.  Both mistakes made and measured on
func_ov022_020ad838 and func_ov022_0209a630.

### The OR form specifically

    *(long long *)(p) |= mask;

emits two loads, `orr` low with the mask, `orr` high with ZERO, two stores.  That is the
whole thing.  It also explains the second oddity that always came with it: the two-step base
(`add r0, r5, #0x64` then `[r0, #0x404]`) is simply how mwcc addresses the high half, not a
separate construct.  Two adjacent flag words where the second gets a zero mask ARE one
64-bit field.

Unblocked func_ov037_020b37f8, func_ov046_020b362c and func_ov033_020b3970 -- 12 functions
across three families, two of which had been parked all day.

** AND IT WAS ALREADY IN THE TREE. **  func_ov038_020b4940 and func_ov047_020b3630 were
already written with `*(unsigned long long *)(obj + 0x464) |= 0x10000LL;` before any of this.
A grep of the parked files for `long long` would have handed it over in seconds; instead I
spent three attempts trying to make the compiler emit an `orr #0`.  The standing rule --
"when you need an instruction you do not know how to produce, disassemble the matched
functions and grep for it" -- has a second half that I keep not applying: grep the PARKED
files too.  They are full of correctly-decoded C that merely fails on some unrelated
residue, and the construct you want may be sitting in one of them.

The superseded reasoning is kept below because the mistake is instructive.

## (superseded) A no-op `orr rN, rN, #0` in the ROM is REAL -- but volatile does NOT produce it

CORRECTED same day.  `*(volatile int *)p |= 0` brings back the LOAD and the STORE (4 bytes
per site, the +16 measured on func_ov046_020b362c's two sites) but mwcc still folds the
`| 0`, so the orr is still missing.  Five spellings measured on func_ov033_020b3970, which
has the identical block: plain `|= 0`, volatile `|= 0`, explicit `*p = *p | 0`, the same via
a volatile pointer local, and reading into a plain int first.  None emits it.

The ROM PAIRS the no-op OR with a SEPARATE BASE register -- `add r0, r5, #0x64` then
`[r0, #0x404]`, where the folded offset 0x468 is perfectly encodable -- at both ov046 sites
and again in ov033.  One construct probably produces both, most likely a macro or inline
helper taking a base pointer and a mask that is zero at these call sites.  Open question.

Still true: do not "clean up" an OR-with-zero out of a source that matches.

## Some ties need TWO changes at once, and each looks WORSE alone (2026-07-20)

func_ov007_0204d0ec closed ov007 at 14/14 after surviving ~a dozen spellings across two
sessions.  It needed the branch test INVERTED (empty case as the `if`) AND `volatile` on
that branch's store, together.  Each alone had already been tried and filed as a dead end:
the inversion alone is 8 bytes OVER, the volatile alone leaves the diff untouched.

That is the blind spot of one-axis-at-a-time search, which is what the pre-park checklist
and every "RULED OUT" list in this repo encourage.  When a residue survives many single
changes, try PAIRS of the axes that moved the needle at all -- including pairs where one
member scored worse.  A ruled-out list is a list of singletons; it says nothing about
combinations.

Corollary for reading the ROM: this function is internally INCONSISTENT (one block emits
load-then-store, another store-then-load, from what must be the same source shape).  That
inconsistency was the tell that the two blocks differ in source structure -- it is what the
inversion reproduces.

## `x % 3`: write the operator, not the expansion (2026-07-20)

The ROM's magic-multiply-then-multiply-back sequence LOOKS like hand-written
`x - x / 3 * 3`, and writing it that way lets mwcc strength-reduce the multiply-back to
`q + q*2` -- 4 bytes short.  The plain `%` operator keeps 3 in a register and uses smull,
which is what the ROM has.  A variable holding 3 does not help; mwcc folds it.
Cracked func_ov042_020b44e8 x4.  General form: when the ROM expands an operator, prefer the
OPERATOR in the source and let the compiler expand it its own way.

## A search loop can use BOTH idioms at once

func_ov042_020b44e8 TESTS through a walking pointer (`p += 0x10c`) and computes the winner
from the INDEX (`blk + 0x14 + i * 0x10c`, an `mla`).  Using one form for both costs bytes
either way.  When a loop's `add rN, rN, #stride` and an `mla` appear in the same function,
that is two different source idioms, not the compiler being inconsistent.

## `register` on a local: the only way to change what mwcc is WILLING to allocate

func_ov301_020cbfc4 closed ov301 at 16/16.  It was instruction-for-instruction identical to
the ROM (92/92, all 16 relocs matching) for two sessions, differing only in which registers
three short-lived constants got.  The ROM spends r3 -- the register pushed purely for stack
alignment -- on one of them, and mwcc will not.

Twelve spellings had been ruled out: every declaration order, constants inlined, an explicit
local, four parameter counts, the block moved, the struct written through a pointer.  None
of those changes what the allocator is willing to use; only `register void *p` does.

So: when a residue is purely "which register", and the ROM uses a caller-saved or
alignment-filler register for a value that dies before the first call, reach for `register`.
It is not in the same family as declaration order -- that reorders preferences, this changes
the candidate set.

### Limit of `register`: it steers WHETHER, not WHICH

Applied to both ov010 parks the same day it closed ov301, and it moved neither.  On ov301
the qualifier was on a POINTER held live across a whole block, which changed the set of
registers the allocator would draw from.  On func_ov010_0204cac0 both candidates are
short-lived scratch in a six-instruction tail, and asking for a register does not change
which one is chosen.  Do not expect `register` to break a two-colouring tie.

(And on that particular function `register` could never have worked, because the residue
was not in the body at all — see the next two sections, which closed both ov010 parks on
2026-07-21.)

## ★★★ A non-void return type RESERVES r0 — check the signature before blaming the allocator

`func_ov010_0204cac0` sat in `nonmatching/` for months as a "proven two-colouring tie": its
tail was instruction-for-instruction the ROM's except that the surviving `off` coloured to
r1 where the ROM used r2.  Ruled out along the way: all five mwcc build-lines, the full
`-O`/pragma matrix, six typed-struct formulations, four `register` spellings, and an
81k-iteration AST permuter.  Every one of them varied the BODY.

The function **returns the `ResFile *` it just loaded.**  Written `void`, r0 is dead after
the last store and the allocator naturally reuses it, so `off` lands in r1 and *no body
rewrite can prevent that*.  Give it its real return type and r0 is spoken for; `off` has to
go elsewhere, and it goes exactly where the ROM put it.  One-line fix, months of steering.

This is the **third** time "is our `void` actually `void`?" has closed a park (22 functions
on 2026-07-18, then this).  The tell:

    the diff is purely WHICH REGISTER, and the ROM avoids r0 in the tail
      -> ask what this function RETURNS before you touch anything else

It is in the pre-park checklist for a reason; on this one it was skipped for months because
the park note was long and confident, which reads as evidence and is not.

## ★★★ Open-coded MMIO vs `static inline` helpers: same semantics, different CSE pool

`func_ov010_0204cb3c` (580 B title-screen setup) was one callee-saved allocation off: mwcc
lookahead-held the sub-engine base `0x04001000` across both DISPCNT blocks, where the ROM
recomputes `add r2, r1, #0x1000` in each.  Eight source forms and 25 builds failed — all of
them writing the register pokes out longhand.

**Open-coded writes all share one CSE pool, so mwcc hoists the common base once.  Each
expansion of a `static inline` helper gets its OWN address local, so the base really is
recomputed per call site** — which is what the ROM does, because the original called the
SDK's inline accessors.  Rewriting the four blocks as

    static inline void GX_SetVisiblePlaneInline(int plane) {
        volatile u32 *reg = (volatile u32 *)0x04000000;
        *reg = (*reg & ~0x1f00) | (plane << 8);
    }
    static inline void GXS_SetVisiblePlaneInline(int plane) { /* 0x04001000 */ }
    static inline void GX_SetDispSelectInline(int select)   { /* REG_POWCNT1 */ }
    static inline u16  PriRet(volatile u16 *reg, int p) { return (u16)((*reg & ~3) | p); }

closed it byte-exact.  Remember `-inline on,noauto` means the helper must be marked
`inline` — that is the whole reason this lever exists here and not in a `-O2` project.

Generalisation, and it is the important part: **a repeated hardware address that the ROM
recomputes is a signal that the original went through an inline accessor.**  Same for a
2-field header copied as one word (`*(PaletteData *)frame.palette = data_...;`) where you
had written two halfword stores.  When the residue is "mwcc CSEs something the ROM doesn't",
stop looking for a steer and ask which SDK inline the source was calling.

## Two if-arms doing the SAME thing are one condition with `||` (2026-07-20)

    if (a) { x = 4; } else if (b) { x = 4; }   -> mwcc predicates it inline (movgt/strbgt)
    if (a || b) { x = 4; }                     -> both tests branch to ONE shared block

The ROM's shape tells you which: a shared block reached by two branches means one condition.
Worth 4 bytes on func_ov035_020b432c x4.  Same jump-to-versus-fall-into distinction as the
switch lever, but showing up in an ordinary if -- and easy to miss because the two-arm
version reads perfectly naturally from a decompiler.

## Cache exactly what the ROM caches — not the expression built from it (2026-07-20)

`func_ov002_02053260` drains an NNS list held at `ctx + 0xb0`. Three spellings, three
outcomes, and the middle one is the match:

| source | result |
|---|---|
| `char *list = ctx + 0xb0;` then use `list` everywhere | 72 B, r4/r5 swapped **and** the preheader reordered |
| `ctx + 0xb0` written out at all three call sites | **76 B** — mwcc reloads the global each time |
| `char *ctx = *(int**)&global;` then `ctx + 0xb0` at each use | **MATCH** |

The tell is in the disassembly and it is unambiguous: the ROM loads the global into r5
once, computes `r5 + 0xb0` into a scratch register for the call *before* the loop guard,
and only does `adds r5, #0xb0` **after** the guard. That lazy fold is mwcc strength-reducing
a repeated `ctx + 0xb0` at the loop preheader — which can only happen if the source
repeats the expression and caches only `ctx`.

So the existing "don't CSE by hand" rule needs a sharper edge: **don't cache the
expression, but DO cache the load.** Hoisting `ctx + 0xb0` into a local denies mwcc the
strength reduction; inlining the global load as well makes it reload. Read which of the
two the ROM did before choosing — the preheader `adds rN, #imm` is the fingerprint of the
correct middle form.

Declaration order rides along for free here: with no `list` local, `node` becomes the
first local and lands in r4, which is where the ROM has it.

## Inline struct copy: the src/dst register pair is not reachable from the source (open)

`func_ov023_02083cc4` — mwcc's counted byte-copy loop for a 7-byte struct assignment puts
the destination in the lower register; the ROM puts the source there. Instruction stream is
otherwise identical at 104/104. Ruled out: plain struct assignment, assignment through a
source pointer, a union member assignment (no cast anywhere), and an explicit
`do { *d++ = *s++; } while (--n)` (108 B). `memcpy(...,7)` unrolls to 96 B, which confirms
the counted loop really is a struct copy.

**Next lever, and do this before any more compile experiments:** grep the matched tree for
a counted byte-copy loop whose source sits in the LOWER register and read that function's
source form. Per SKILL.md's "grep the matched tree for the instruction" rule, 12,000+
functions of known-good C almost certainly contain one already.

## Hoisting a call out of a short-circuit condition -- both directions (2026-07-20)

The "don't CSE by hand" rule has a mirror image, and both cost a compile:

- **`func_ov002_02053260`**: hoisting `ctx + 0xb0` into a local was WRONG (it denies mwcc a
  strength reduction it wants to do at the loop preheader). Cache the load, not the expression.
- **`func_ov002_02063980`**: NOT hoisting was wrong. Written as

  ```c
  if (func_ov002_020575d0() == 0 && *func_ov002_02063698() > 0)
  ```

  mwcc emits the two calls in source order and comes out 4 bytes short. The ROM calls
  `func_ov002_02063698` FIRST and parks its result in a callee-saved register, then evaluates
  the short-circuit. So the source is:

  ```c
  counter = func_ov002_02063698();
  if (func_ov002_020575d0() == 0 && *counter > 0)
  ```

**The disassembly settles it and costs nothing: read the ORDER OF THE `bl`s before writing
the condition.** A call whose result is parked in a callee-saved register before an unrelated
call was evaluated outside the condition; a call that happens in source order was not.

Related: `x == 0 || (x & 1)` is spelled in the ROM as two separate conditional branches
converging on the same target, NOT as a range test. (Contrast `x == 0 || x == 1`, which mwcc
collapses to a range test -- see the switch-vs-if note.)

## Two pool slots for ONE symbol -- an open lead (2026-07-20)

`func_020234e8` (76 B, main) reaches 72 B and is otherwise instruction-for-instruction
identical apart from an r0/r1 swap in the guard block. The 4-byte gap is the literal pool:
the ROM has **two separate pool words both relocating to `data_0204be08`**, and mwcc CSEs the
two references in my C into one.

```
relocs: 0x40 data_0204be08 , 0x44 data_0204be08     <-- two slots, same symbol
```

The function reads the halfwords at +0 and +2 through one base and passes a pointer to
func_02031384 through the other. Writing both as `&data_0204be08` merges them.

**Lead worth following:** `func_0202348c` (already matched) has the same shape and there the
index gives TWO DISTINCT symbols, `data_0204be08` and `data_0204be0a`, which is exactly what
forces two pool words. So the likely answer here is that the second reference is a distinct
symbol the delink index has collapsed onto the same name -- check `symbols.txt` for another
symbol at or near 0x0204be08 before trying source spellings. The r0/r1 swap is probably a
consequence, not a separate problem.

Not committed: the C was removed rather than left unverified in `calls/`.

## `func_02020400` = `_s32_div_f`: quotient in r0, REMAINDER IN r1 (2026-07-20)

Symptom: the ROM reaches a `bl` with one argument register apparently never set, and the
instruction before is `bl func_02020400`. Not a dropped argument, not a long-long return in the
usual sense -- it is the MetroWerks runtime **signed divide**, which returns the quotient in r0
and the remainder in r1. The next call is consuming the remainder.

Identification is airtight: write `x % K` and mwcc emits byte-identical code, only naming the
reloc `_s32_div_f`. Its body also gives it away -- `eor ip,r0,r1; and ip,#0x80000000` (sign
fixup) then the classic shift-subtract division ladder.

The catch: `symbols.txt` calls 0x02020400 `func_02020400`, so the honest `%` spelling will not
link. Workaround that keeps the project's symbol:

```c
extern long long func_02020400(int a, int b);   /* _s32_div_f: quotient r0, remainder r1 */
...
f(x, (int)(func_02020400(v, 6) >> 32), 0);      /* means: f(x, v % 6, 0) */
```

Always comment what it means -- the `>> 32` is otherwise unreadable. ~90 matched files already
call this helper by address for the QUOTIENT (which needs no trick, r0 is the return value);
this form is only needed for the remainder. Whether to rename the symbol or alias it is an open
infrastructure question -- see `dudas.md`.

⚠ Generalisation worth keeping: **before blaming a compiler tie for an "unset" register, look at
what the PREVIOUS call actually returns.** r1 after a `bl` is a real value about a third of the
time in this codebase -- the high half of a 64-bit return, or a runtime helper's second output.

## switch: compares are sorted by VALUE, bodies are laid out in SOURCE order (2026-07-20)

Symptom: the size is exact, every instruction matches, and two case bodies are simply in the
other order. That reads as a scheduling tie. It is not.

`func_020303d8` dispatches `cmp #0 / cmp #1 / cmp #3` in numeric order -- and mwcc emits that
same compare order whatever the source does, so the dispatch tells you nothing. But the BODIES
come out in the order the cases are written. The ROM had case 1's body before case 0's, so the
original source listed `case 1:` first.

**Check: line the case bodies up against the compare order. If the bodies are permuted relative
to the compares, reorder the cases in the source to match the BODY order.** Costs one compile.

## Split `x = a() << N; x |= b();` -- the one-expression form shifts LATE

Same function, second lever. The ROM does `bl a; lsls r4,r0,#0x10; bl b; orrs r4,r0` -- it shifts
the first result the instant it has it.

```c
packed = func_a() << 16;      /* shifts immediately  */
packed |= func_b();
```
compiles to exactly that. Writing it as one expression:
```c
packed = (func_a() << 16) | func_b();   /* WRONG: +4 bytes */
```
makes mwcc keep the raw value in a register across the second call and shift afterwards, costing
`adds r4,r0,#0` up front and `lsls r1,r4,#0x10 / adds r4,r1,#0` after -- two extra instructions.

Generalises: **when the ROM applies an operation to a call result BEFORE the next call, give that
operation its own statement.** Sequencing inside one expression is mwcc's choice; sequencing
across statements is yours.

## A pool constant reused by shifting is ONE constant, not two addresses

`func_020303d8` writes 0x05000000, 0x05000400, 0x04000000 and 0x04001000. Only two of those are
in the literal pool: mwcc derives 0x04000000 as `lsls r2, r0, #0x10` from the 0x05000400 it
already holds (0x05000400 << 16 wraps to 0x04000000). Plain C with all four constants written out
reproduces it. **Do not go looking for a symbol behind a shifted register that lands on an MMIO
address** -- count the pool entries first.

## Pin a pointer increment's POSITION with a temp (2026-07-20)

Symptom: exact size, identical instruction stream, and **one instruction sits in a different
place** -- typically an `adds rN, #imm` that the ROM emits before a `bl` and mwcc emits after it.
That reads as a scheduling tie. It is steerable.

The ROM computes an argument from the OLD pointer, advances the pointer, then calls:

```
adds r1, r5, #0
adds r1, #0x20        <- argument from the old cursor
adds r0, r7, #0
adds r5, #0x28        <- advance, BEFORE the call
bl   fetch
```

Written the obvious way the increment sinks past the call (and past whatever follows):

```c
params.nCount = fetch(self, descs + 0x20);
descs += 0x28;                              /* WRONG position in the output */
```

Putting the argument in a temp first forces the ROM's order:

```c
pCountDesc = descs + 0x20;
descs += 0x28;
params.nCount = fetch(self, pCountDesc);    /* increment now lands before the bl */
```

**General form: mwcc will only emit the increment before the call if the argument is ALREADY in
a temp when the increment is written.** A statement that could legally move usually does.

Same family as the shift-splitting crack and the truncation-point rule: **mwcc puts an operation
where the source forces it to.** When a diff is "right instructions, wrong order", ask which
statement boundary would pin the one that moved.

### Two companions from the same function, both about loops

- **A counter the ROM re-reads from memory every iteration must stay a memory read in the loop
  condition.** Caching `params.nCount` in a local removes the `ldrsb` and changes the loop.
- **Reuse the incoming pointer as the cursor.** Introducing a separate cursor variable keeps both
  live and makes mwcc spill another argument to the stack -- a different register assignment
  through the whole loop, for +2 bytes. The separate cursor is the more natural C, which is
  exactly why this costs time.

## The three findings above are ONE rule (2026-07-20, confirmed on a fourth case)

Shift splitting, truncation point, and statement position all turned out to be the same thing:

> **mwcc puts an operation exactly where the source forces it to, and any statement it is free to
> move, it moves.**

Confirmed a fourth time in `func_ov021_02080c98`, where a cursor advance inside a switch case had
to be pinned before a store -- the identical lever `func_ov002_0207d610` needed for an advance
before a CALL. So it is not about pointer arithmetic, or arguments, or conversions specifically.

**The move, when a diff is "right instructions, wrong order": put the value that the moving
statement would otherwise be reordered around into a TEMP.**

```c
entry->nValue = fetch(descs); descs += 8;   /* advance sinks past the store */
v = fetch(descs); descs += 8; entry->nValue = v;   /* advance pinned before it */
```

Corollary worth remembering: **a temp variable is a scheduling instruction, not just a name.**
Adding one is the cheapest steer available and it costs nothing when it is not needed.

### And the smaller one from the same function

`lsrs` vs `asr`: reading a packed word as a signed `int` and shifting right gives an ARITHMETIC
shift. If the ROM emits `lsrs`, read through `unsigned int`. One instruction, easy to stare past.

## ★★ A NESTED BLOCK reassigns two callee-saved pointers when nothing else will
*(func_ov131_020cd594, 2026-07-20 — a 5-member AI family, `StrafeThenReact`)*

Symptom: every instruction matches, size exact, and the ONLY residue is two pointers swapped
between two callee-saved registers — here the pre-load `ldr r5,[r4]; ldr r7,[r4,#8]` (ROM) came out
`ldr r5,[r4,#8]; ldr r7,[r4]` (mine). Two owner/target pointers, both `*state`-derived, both held
across one `normalise` call, both read once as `X->radius`, then one register reused for the result.

The full function-level knob set does NOT move it — measured, not guessed:
- sum operand order (`a+b` vs `b+a`): flips the two READ bytes but not the pre-load → still 2 off;
- assignment order (`own=..; tgt=..` vs the reverse): no effect;
- declaration order (the documented r4..r8 direct-mapping): no effect on these two;
- compound-assign (`gap = mag; gap -= a+b`): no effect.
mwcc simply assigns `state[2]`→r5 and `*state`→r7 for this shape, and the ROM wants the reverse.

**The fix: scope the two pointers in a NESTED `{ }` BLOCK, declared in the order the ROM loads
them.** Copied from the matched sibling `func_ov131_020cd334`:
```c
{
    int *o = (int *)*state;      /* declared first  -> the [r4] load, r5 (reused for gap) */
    int *h = (int *)state[2];    /* declared second -> the [r4,#8] load, r7 */
    gap = normalise(&aim,&aim) - (*(int *)((char *)h + 0x80) + *(int *)((char *)o + 0x80));
}
```
Block-scoping a held value narrows its live range to the block, and THAT is what changes the
colouring — the two function-level locals tie for the same pair of registers, the two block locals
do not. So when a "two registers swapped" residue survives every function-level lever, try lifting
the pair into a `{ }` block, ordered to match the ROM's load order. Cheapest to reach for once the
usual four have failed.

(The rest of that function is a catalogue of already-solved AI-handler idioms: the reciprocal
`0x28be60db9391` angle divide into the shared sin/cos table, `RandNextScaled(N) + (v - v)` for the
`add r0,r0,#0` copy artifact, and per-arm duplication of the tail call because mwcc does not
tail-merge here. All copied from `func_ov120_020ccd90` and `func_ov169_020cda08`.)

---

## Flags-byte bitfields: bit 0 codegen DIFFERS from bits 1..7 (2026-07-22, ov002 link-sync)

Setting a 1-bit bitfield emits **`bic #mask; orr #mask`** when the field is at **bit 0**, and a bare
**`orr #mask`** at any higher bit. Reading any of them emits the documented `lsl #(31-n); lsr #31`
pair. Clearing any of them emits a bare `bic #mask`.

This matters because a function that sets bit 0 and bit 2 looks like it has two different source
styles — a bitfield store and a raw `|=`. It does not. One `unsigned char b:1` model per bit
reproduces all of it:

```c
typedef struct {
    /* ... */
    unsigned char bSlotsDirty   : 1;   /* bit 0: `= 1` -> bic #1; orr #1  */
    unsigned char bLocalPending : 1;   /* bit 1: `= 1` -> orr #2          */
    unsigned char bMirrorReady  : 1;   /* bit 2: `= 1` -> orr #4          */
} Ctx;
```
Proven byte-exact across `func_ov002_02066cc8`, `_02066d78` and `_02066f14`, which between them
set and clear all three. **Do not "fix" the asymmetry by writing raw masks** — the raw `|= 1` does
not reproduce the bic.

Corollary for adjacent fields in the same byte: **two consecutive bitfield assignments are folded
into ONE store.** `rec->nSlot = idx; rec->bFresh = 1;` gives
`ldrb; bic #0x38; orr <idx<<3>; and #0xff; orr #0x40; strb` — a single `strb`. Seeing one store
does not mean one source statement, and the `and r0,r1,#0xff` in the middle is the tell (it is the
re-truncation between the two field writes, not a cast in the source).

## A boolean stored to a narrow type is materialised TWICE

`reply[2] = (kind == 2 || kind == 4);` where `reply` is `unsigned short *` compiles to **one**
boolean in mwcc's natural form, but the ROM has two:

```
mov ip,#1 ; cmp r1,#2 ; cmpne r1,#4 ; movne ip,#0     <- fold the pair
cmp ip,#0 ; movne r1,#1 ; moveq r1,#0 ; strh r1,[r0,#4]  <- widen for the store
```
Route it through a local and store the ternary explicitly:
```c
int isAccept;
/* ... */
isAccept = found->nKind == 2 || found->nKind == 4;
reply[2] = isAccept ? 1 : 0;
```
Worth 12 bytes on `func_ov002_02066e40`. And **the local must be ASSIGNED where the ROM computes
it**, not initialised at the top of the block — an initialiser hoists the whole computation above
the surrounding stores.

## When declaration order will not colour a register, widen an UNRELATED variable's scope

`func_ov002_02066e40` ended one register off: `found` in ip where the ROM wants r3. Five
permutations of the other two locals (order, split declaration from assignment, both directions)
all failed **identically** — which is precisely the signature of the blocked register-choice tie,
and precisely why it nearly got parked.

The fix was moving `int i` — the `for` loop's counter, not obviously part of the problem — from
the loop's scope to **function scope**. That alone flipped `found` to r3 and the field scratch to
ip. This is the mirror image of the `{ }`-block crack above: block-scoping narrows a live range to
change colouring, function-scoping widens one. **Both directions are levers, and the variable to
move may not be one of the variables in the diff.**

## Cache the OFFSET, not the index, when the ROM computes it before the base

`func_ov002_02075cac`: the ROM does `lsl #7; add #0x20`, *then* walks the pointer chain to the
base, then adds. Binding the index to a named local that stays live across the base load pushes it
into a spare register and reorders everything after it. Hoisting the whole byte offset into its own
local puts the arithmetic back on top:
```c
offset = (3 - func_ov105_020bd7c4()) * 0x80 + 0x20;
GX_LoadBG3Char((void *)(*(int *)(g + 0x10) + offset), 0x10c0, 0x80);
```

## `> 1` and `>= 2` are different instructions

`x > 1` emits `cmp #1 / ble`; `x >= 2` emits `cmp #2 / blt`. Same meaning, different code. When the
only residue is the compare immediate and the condition code, rewrite the COMPARISON — do not go
looking at the code around it. (`func_ov002_02066ba8`.)

---

## ★★★ Declaration order fixes the STACK LAYOUT too -- but only together with control-flow shape

*(2026-07-22, `func_ov147_020cc00c` and its x4 family, via the peer lane.)*

The parked file was **372 vs 380** with every instruction otherwise matching, and its note recorded
that all **24 permutations of the four locals had been swept, with a script, twice**. The note was
honest and the sweep was real. It still missed the answer, because the answer is not a permutation.

The match declares `buf, tmp, dir` -- the **big buffer first** -- *and*:
- `int k`, not `unsigned int k`;
- an explicit **`goto skip`** for the `k != 0 && k != 1` guard, instead of nesting the body inside
  `if ((k == 0 || k == 1) && ...)`;
- the branches written **`<= 0x4800` first**, i.e. the ROM's fall-through order, with the `0x244d`
  block ahead of the `0x10c1` one.

**Declaration order only pays off in combination with the control-flow shape**, so a sweep over one
axis with the other axis fixed cannot find it, no matter how exhaustive. Two rules fall out:

> **"I permuted the declarations" is not the same claim as "declaration order is not the axis."**
> When a STACK-LAYOUT diff survives a declaration sweep, the next axis is **control-flow shape**
> (goto vs nesting, which arm falls through) -- not more permutations.

And the corollary that makes the note dangerous rather than merely incomplete: an exhaustive-sounding
negative result over one axis reads like a closed door. Say which axis you swept.

## ★★ A WRONGLY SIZED STRUCT SILENTLY SHIFTS EVERY LATER STACK SLOT

*(2026-07-22, `func_ov019_0207fa94`, 500 B THUMB.)*

Its park note blamed "the frame layout of the five local buffers". It was not a layout preference:
`struct namelist` was modelled with **7 words** and is actually **9**. Too small a struct pushes
every object declared after it, and the result reads *exactly* like mwcc choosing a different frame.

The ROM's own frame gives you the size for free:

```
sp+0x00  saved ids (8 B)
sp+0x08  header[6]
sp+0x10  out          <-- 0x34 - 0x10 = 0x24 = 36 B = 9 words, not 7
sp+0x34  found[16]
sp+0x54  scratch[16]
sp+0x74  fmtbuf[4]
sp+0x84  names[256]
```

> **When a frame diff involves an aggregate, measure the gap between its sp offset and the next
> object's, and compare that with your struct's size.** It is arithmetic on the disassembly, not a
> search. Adding two trailing pad fields fixed the frame and everything else fell out.

Same match, three smaller levers: `unsigned char header[6]` not `char` (the ROM uses `ldrb`);
`func_0202fcb8(fmtbuf, found)` with **no cast**, the callee taking `void *`; and the `mode != 3` arm
written first, the ROM's fall-through order.

## ⚠ DO NOT TRANSPLANT A CRACK BY ANALOGY

Same session, same peer: the ov147 lever ("declare the big buffer FIRST") was copied into
`func_ov019_0207fa94`'s note as "declare `names[256]` first". **The ov019 match declares
`names[256] LAST.`** The ov147 crack is real *for ov147*; carried across by shape-similarity it
pointed the next reader in exactly the wrong direction. Retracted in the plate comment.

A crack is a (symptom -> form) pair observed on one function. Until it is confirmed on a second, it
is evidence, not a rule -- and writing it into another function's note dresses it up as a rule.

## ⚠ Relocs that were never relocs

`func_ov019_0207fa94` also carried **four bogus relocs**: `data_ov019_0207fc78/_7c/_80` are literal
pool words (`0x140b`, `0x1415`, `0x141f`) and `data_ov019_0207fc84` is the pool SLOT, not the datum
-- the real target is `data_ov019_0207fd78`. Fixed in commit `7eb65735`; the size dropped 516 -> 512,
but the point is that **with a wrong reloc set the function could never have verified even at the
right size.** The check is the one already in this file: cross-reference every pc-relative load
against `func_index.json`'s reloc table -- **no reloc at that offset means it is a literal.**

---

## ★★★ ONE STRUCT FOR THE WHOLE OBJECT, TYPED ON THE PARAMETER -- not sub-structs with casts

*(2026-07-22, `func_ov000_020552b4` x6 via the peer lane, commit 110af975; re-confirmed on
`func_ov000_0205579c`.)*

When a function reaches a big object at large constant offsets, model the object **from 0 to its
last field in a single declaration** and type the parameter `Root *self`. Do NOT write
`int self` plus inline casts, and do NOT carve out sub-block structs reached through casts.

**Why the natural conclusion is wrong**, because this is subtle and it cost three sessions on one
file. The old note had measured, correctly, that holding the sub-block pointers in local
**variables** dropped the function to 592 bytes -- mwcc parks them in callee-saved registers and
stops rematerialising the base additions -- and concluded that the ROM's repeated adds meant the
original must have used inline casts. Right measurement, wrong inference:

> A local pointer and a typed parameter are **not** the same thing. The local is a *value* mwcc can
> keep in a register; a field access through a typed parameter is an *address computation* it must
> redo, because the offsets exceed the 12-bit `ldr` immediate. **The ROM's repeated add is a
> consequence of the offset range, not an idiom to imitate with casts.**

Two independent payoffs measured on `func_ov000_0205579c`:
- It **removed a constant CSE that a park note had named as its blocker.** The note said mwcc
  hoisted one shared `-1` where the ROM materialises three; with the object typed on the parameter
  mwcc emits three `mvn`, exactly like the ROM. The note's "retry only with a way to stop the -1
  CSE" is retired.
- It made the note's `base` local (self + 0x4000) **unnecessary**. That local had been recorded as
  load-bearing because removing it cost 4 bytes — true of the cast-based C, false once the
  parameter is typed. Adding it back on top of the struct changes nothing at all.

**Re-test vein:** any parked file whose C reaches an object through inline casts at a large constant
offset is a candidate. `grep -l "(int \*)(self + 0x" src/**/nonmatching/*.c` is a decent first cut.
Note this is a *screen*, not a verdict — `func_ov000_0205579c` itself did not fall (it is down to a
uniform one-register rotation), but two of its three documented blockers evaporated.

---

# Session 2026-07-22 (autonomous ov002 run, 55 matches). Five levers, all reusable.

## ★★★ FAR OFFSET -> HELD POINTER. NEAR OFFSET -> REPEAT IT.

This is the single highest-yield rule of the session; it decided four functions.

- A field **beyond the addressing immediate** (roughly >0xfff for `ldr`, >0xff for `strh`/`ldrb`
  scaled forms) that is touched **more than once** must be bound to a pointer ONCE:
  `int *slot = &root->nPauseObject;`. The ROM parks the offset in a callee-saved register and uses
  base+offset addressing for every access. Writing the field access out twice makes mwcc
  rematerialise the offset from the literal pool at each use and **drop the callee-saved register
  entirely** — `push {r3,r4,lr}` where the ROM has `push {r4,r5,lr}`.
  Proven on `func_ov002_0206a048`, `func_ov002_0206a0bc`, `func_ov002_02069ca4`,
  `func_ov002_0206b0b8` (that last one is 4 bytes purely from writing `root + 0x8bb4` instead of
  reusing the held `root + 0x8ba8`).
- A field **inside** the immediate range wants the opposite: repeat the expression, do not cache it.
  `func_ov002_02057620` re-reads its global for the final store; `func_ov002_0205a4a0` re-reads the
  list head every iteration.

The discriminator is the **offset size**, not taste. Both halves were already in this file
separately; the pairing is what makes it usable.

## ★★ COUNTERS BEHIND A GUARD MUST BE ASSIGNED, NOT INITIALISED

Cost three functions before it was named. When a counted loop sits behind an early-exit guard:

```c
int i;                    /* declared, NOT initialised */
int offset;
if (...) return;
work();
i = 0;                    /* assigned here, index FIRST */
offset = 0;               /* then the derived one -- the ROM emits movs/adds, not movs/movs */
for (; i < N; i++) { ... }
```

Initialising at the declaration hoists both above the guard and shifts the whole prologue.
`func_ov002_02078eac`, `func_ov002_02078f60`, `func_ov002_02077e68`.

## ★★ SCOPE IS A LEVER IN BOTH DIRECTIONS

`func_ov002_02078f60` needed its inner-loop `next` pointer at **function** scope; scoped to the
loop body it took the register the outer byte offset wanted and the two swapped. That is the exact
opposite of the ov131 crack, which needed a pair scoped **into** a nested block. So the lever is
the scope boundary itself and either direction can be correct — try both before concluding.

## ★ A PREDICATED MULTI-WAY SELECT WANTS N-1 RETURNS AND A FINAL ASSIGNMENT

`func_ov002_02051318` picks one of two step functions from a flag word. Three `return` statements
cost four bytes; the last test **assigning** to the result and one `return result` at the end lets
mwcc predicate the whole chain into `ldrne`/`bxne` sharing a single `bx lr`.

Related: `func_ov002_02069084` shares its FIRST guard's `return 0` with the function tail and gives
the second its own inline one. Two sequential early returns produce the opposite; nesting the body
inside `if (ok) { ... }` with a bare `return 0` last reproduces it.

## ★ RANGE FOLD MUST BE WRITTEN AS THE SUBTRACT

`phase < 8 || phase > 13` compiles to cmp/blt/cmp/ble — four bytes more than the ROM. mwcc only
emits the `subs #8 / cmp #5 / bls` form when the source says `(unsigned)(phase - 8) > 5`. The
readable spelling is the one that does not match. (`func_ov002_0206a0bc`.)

## ⚠ CORRECTION: `/` and `%` CANNOT replace func_02020400

Recorded because I got this wrong mid-session and committed the error. mwcc compiles `a / b` and
`a % b` to a call named **`_s32_div_f`**, which `config/arm9/symbols.txt` does not define, so the
reloc has nowhere to resolve. The instructions are identical; only the symbol is wrong. The
`long long func_02020400(...)` + `>> 0x20` workaround is still required.

**Why I believed otherwise, which is the more useful lesson:** the function I first tried it on had
a byte difference, and `verify_idx` checks bytes BEFORE relocs — so it never reached the reloc
comparison and I read the absence of a reloc error as a pass. **A verify_idx pass reported at an
earlier check does not clear the later ones.**

Which half of the return you want differs per call site: the cursor steppers
(`func_ov002_0205ed58`, `_0205ed98`) take the REMAINDER (`>> 0x20`), while
`func_ov002_02059730` takes the QUOTIENT (the low half). Both compile.

## ★ `static inline` fingerprint: the SAME constant built DIFFERENT ways

`func_ov002_02071148` installs three callbacks through a setter that skips the sentinel -1, and the
ROM builds that -1 **three different ways** — subs from a live zero, subs from a fresh zero, and
mvns of zero. One shared constant would have been materialised once. Three distinct constructions
of the same value is the signature of three separate `static inline` expansions.

## ★ Induction variables: NO escribas a mano lo que es reduccion de fuerza (2026-07-22)

`func_ov002_02072000` (Ov002_RunSeatHooks). La ROM corre **dos punteros que caminan** junto al
contador: uno +4 por el array de hooks, otro +0x20 por los objetos. Al verlo en el listado, el
movimiento obvio es escribirlos en el C — y es **incorrecto**. Son la reduccion de fuerza que hace
mwcc de dos indexaciones normales.

Escritos a mano dan **las instrucciones correctas en el orden correcto pero con dos registros
intercambiados**, y **ningun orden de declaracion lo arregla**, porque las variables que el
allocator esta ordenando ya no son las del fuente. Se compilaron **once** permutaciones (cuatro
ordenes de declaracion, una version de 3 variables plegando el ctx en el walker, forma `for`,
declaraciones separadas): las once dieron el mismo swap. La forma llana

```c
for (seat = 0; seat < 4; seat++)
    if (ctx->hooks[seat] != 0)
        ctx->hooks[seat](ctx->objects[seat], seat, global);
```

acerto **a la primera**, tanto en `for` como en `do/while`.

**Regla:** un diff que sea SOLO un swap de registros, inmune al orden de declaracion, y que este
en un bucle con variables de induccion → el fuente esta al **nivel de abstraccion equivocado**,
no es que el allocator discrepe. Escribe el bucle como lo habria escrito el programador.

⚠ **No contradice la palanca del walker explicito** (`func_ov002_02071420`, Ov002_FindPeerRow, que
SI necesita `p` declarado antes de `rows`). La diferencia: alli el walker **sobrevive al bucle** —
es la fila devuelta —, asi que es una variable real. Un walker cuyo unico trabajo es avanzar y
desreferenciarse es cosa del compilador.

Corolario util: **el primer byte discrepante avanzando** ordena bien las permutaciones aunque no
baje el numero de diffs (6 permutaciones de Ov002_FindPeerRow: las que ponian `i` primero
divergian en 0x9, las que lo acertaban en 0x12).

## ★ `umull` contra una constante magica: DECODIFICA EL NUMERO antes de tocar codegen (2026-07-22)

`func_ov002_0206dda8` llevaba varias sesiones abierta. Todos los intentos apuntaban a la
secuencia `lsr`/`orr` de 64 bits — que **nunca fue la dificultad**.

`umull` contra el literal **0x82ea** seguido de `>> 6` de 64 bits = **`OS_MilliSecondsToTicks`**.
0x82ea = 33514; el reloj del sistema DS es 33513982 Hz y el tick del OS es 1/64 de el, asi que
ticks por milisegundo = 33513982/64000 = 523,656 = **33514 >> 6**. Los campos almacenados son
milisegundos, las funciones devuelven ticks. En C es **una linea**:

```c
return ((unsigned long long)ms * 33514) >> 6;
```

Y si hay una resta `subs`/`sbc` de dos de estas, el retorno es **`long long` con signo** aunque
los dos operandos sean sin signo — el desbordamiento tiene que seguir siendo representable.

**Regla:** una `umull` contra una constante magica merece decodificarse **como numero** antes de
tratarse como problema de codegen. Vale para divisiones por constante, conversiones de unidades y
punto fijo.

## Dos formas del mismo casi-acierto (misma tanda)

- **`return 1` que es la COLA de caida** (`Ov002_PostMessage`): la guarda se escribe en positivo
  (`if (x != 0) return f(...); return 1;`). La forma invertida mete la constante en medio y
  **intercambia dos registros de argumento**.
- **Parametro `int` estrechado en el call site** (`lsl #16` / `lsr #16`): declarar el parametro
  como `unsigned short` hace el estrechamiento redundante y la funcion sale **2 bytes corta**.
  El estrechamiento visible en la ROM dice que el parametro del LLAMANTE es ancho.

## ★★★ Un DESPLAZAMIENTO DE REGISTRO en todo el cuerpo = PARAMETRO REENVIADO (2026-07-22)

**El hallazgo mas rentable de la sesion.** Cerro tres funciones que llevaban iteraciones abiertas
(`func_ov002_02063660`, `func_ov002_02073ffc`, `func_ov002_02076984`) en un solo intento cada una.

**Sintoma:** la secuencia de instrucciones es correcta y esta en el orden correcto, pero **todos**
los registros estan desplazados uno arriba respecto a la ROM — tipicamente r1→r2, r2→r3, y en
THUMB r3→r4 (que ademas cambia la lista del `push`).

**Causa:** la funcion tiene un **segundo parametro que solo se reenvia** a la callee. Llega en r1
y se pasa sin tocarlo, asi que **no cuesta ni una instruccion y es invisible en el desensamblado**.
Su unico rastro es que **r1 no esta disponible como scratch**, lo que desplaza todo lo demas.

```c
int func_ov002_02076984(int index, int arg) {          /* arg NO se usa aqui... */
    return func_02025694(&root.pTable->entries[index], arg) != 0;   /* ...solo se reenvia */
}
```

⚠ **Un parametro reenviado NO es lo mismo que un parametro sin usar.** Ya lo habia probado con
`int unused` y no funciono: mwcc descarta un parametro que no se usa y libera el registro. **Tiene
que llegar a una llamada.**

Relacionado, misma familia de lectura (tres instancias en la misma sesion):
- **`bxeq lr` pelado que no escribe r0** en una funcion que si devuelve valor por otras vias →
  esta **devolviendo un argumento** (`Ov002_IsPanelModeSet`).
- **r0 nunca escrito entre la entrada y un `bl`** → el argumento del llamante **pasa de largo**
  (`Ov002_SnapshotPausedObject`).
- **Un registro que parece muerto tras un `str`** puede ser el argumento siguiente: en
  `Ov002_CreateSlotContext` la callee recibe **la direccion de la ranura global**, que es lo que
  quedo en r0 tras el store, no el objeto.

**Regla general: un registro que no se escribe pero llega a una llamada es parte de la FIRMA.**
Antes de culpar al register allocation, cuenta que registros entran a cada `bl` y de donde salen.

## Padding explicito en structs con offsets no naturales

`Ov002_GetElementKindAndIndex`: stride `unsigned short` en +0x4e, puntero base en **+0x54**. La
alineacion natural pone el puntero en +0x50 y la carga sale cuatro bytes antes. **Cuando un offset
medido no coincide con el que da la alineacion, mete el `char padXXXX[N]` explicito** — es un
fallo silencioso que produce una funcion del tamano correcto.

## ★★★ "Comprueba un campo y luego llama" NO significa que el campo sea el argumento (2026-07-22)

Cinco instancias en una sola sesion, y **cada vez la respuesta fue distinta**. El sintoma siempre
es el mismo: instrucciones correctas, **dos registros intercambiados**.

Cuando una funcion prueba un campo y despues llama a algo, **lee que hay REALMENTE en r0 en el
`bl`**. Hasta ahora ha sido:

| funcion | lo que va en r0 |
|---|---|
| `Ov002_SnapshotPausedObject` | el **parametro del llamante**, que pasa de largo (r0 nunca se escribe) |
| `Ov002_ClosePause` | la **constante -1** (el -1 del `cmp` sigue vivo) |
| `Ov002_AbortSession` | la **constante -1** |
| `Ov002_SetCurrentSlotFlag1` | la **constante -1** |
| `Ov002_CreateSlotContext` | la **direccion de la ranura global**, que es lo que dejo el pool load tras el `str` |

El caso `-1` es especialmente facil de fallar porque es *plausible*: acabas de comparar el handle
contra -1, asi que pasarlo parece lo natural. Pero `movs r0,#0; mvns r0,r0` deja el **-1** en r0,
no el handle — el handle esta en r1. Si la ROM compara `cmp r1,r0`, el argumento es r0.

**Regla operativa: antes de escribir la llamada, traza hacia atras el registro de cada argumento
desde el `bl`.** Es diez segundos y ahorra rondas enteras de permutaciones de declaracion.

Nota tambien: `lsl #31` / `lsr #30` es simplemente `(x & 1) << 1`. No hay que reproducir los
shifts literalmente.

## ★★ El CERO DEL CONTADOR va ANTES de los punteros walker (2026-07-22)

Dos funciones seguidas con el mismo residuo (`func_ov022_02093b2c`, `func_ov022_0209c6c4`), y el
mismo arreglo de una linea:

```c
/* NO: */                          /* SI: */
walker_a = base + 0x20;            i = 0;
walker_b = base + 0x440;           walker_a = base + 0x20;
for (i = 0; i < 4; i++) { ... }    walker_b = base + 0x440;
                                   for (; i < 4; i++) { ... }
```

Dejado en el inicializador del `for`, mwcc emite el `movs rX,#0` **despues** de montar los
walkers; la ROM lo emite **antes**. Todas las instrucciones son las mismas y estan en el mismo
orden salvo esa, asi que el diff se ve como "una instruccion desplazada" a lo largo de toda la
funcion — facil de leer como scheduling irreparable.

**Sintoma:** el primer byte discrepante cae en el prologo del bucle, y el diff muestra el mismo
bloque de instrucciones con `movs rX,#0` una o dos posiciones corrido.

## `-char signed` obliga a `ldrsb` — el flag suele ser `unsigned char`

`func_ov022_02093b2c`: leer `*self & 1` con `self` declarado `char *` da
`movs rX,#0` + `ldrsb r1,[r0,rX]` (carga con signo y offset de registro) donde la ROM tiene un
`ldrb r1,[r0]` pelado. Declarar el parametro `unsigned char *` lo arregla. Con `-char signed` en
los flags del proyecto, **cualquier byte que sea un campo de flags debe declararse `unsigned`**.

## ★★★ CRACKEADA: la familia "alloc + tres slots por setter `static inline`" (2026-07-22)

Cuatro funciones bloqueadas durante toda la sesion con **el mismo residuo exacto**
(`func_ov002_0206ff6c`, `func_ov002_02070ecc`, `func_ov002_02070d9c`,
`func_ov013_0207fba4`). La respuesta es **un cast**:

```c
static inline void set_callback(void **slot, void *value) {
    if ((int)value != -1) { *slot = value; }   /* SI  -- comparacion de INT */
 /* if (value != (void *)-1)                      NO  -- comparacion de PUNTERO */
}
```

Con la comparacion de **puntero**, mwcc construye el centinela -1 una vez y lo reutiliza en las
tres expansiones. Con la de **int**, lo reconstruye para la tercera — que es lo que hace la ROM
(`mvns` / `subs` / `mvns`, y un cero fresco para el ultimo store).

Nada en estas funciones puede pasar nunca -1, asi que **la guarda entera es codigo muerto**: solo
se nota su *grafia*. Ese es justo el motivo de que costara tanto — no hay ninguna diferencia
semantica que buscar, y probe 12+ variantes en el eje equivocado (locales distintos, helpers
separados, helper con base+offset, firma no-void, campos de struct en vez de casts, `~0` en vez
de `-1`, tipos de puntero a funcion).

**Leccion general: cuando dos formas son semanticamente identicas Y el valor comparado es
imposible, el eje NO es el valor ni el flujo — es el TIPO de la comparacion.** Un `!=` entre
punteros y un `!=` entre enteros son operaciones distintas para el generador de codigo aunque el
estandar los haga equivalentes aqui.

## ★★ ASIGNACION ENCADENADA: `a = obj->f = call()` (2026-07-22)

`func_ov181_020cd1e0` y sus dos hermanas. La ROM hace:

```
bl   query
movs r7, r0        ; copia + flags
str  r0, [r4,#0x10]  ; guarda el RAW r0
```

Es decir, **guarda el retorno crudo y prueba la copia**. Escrito en dos sentencias
(`t = f(); obj->x = t;`) mwcc guarda **la copia** (`str r6`), lo que le cuesta un registro
callee-saved y desplaza toda la asignacion del resto de la funcion. La forma que acierta:

```c
target = obj[4] = func_ov107_020cab14(obj[0], &gap);
```

**Sintoma:** el `str` justo despues de un `bl` usa un registro distinto del que acaba de
recibir el `movs`/`mov` de la linea anterior, y la lista del `push` tiene un registro de mas
o de menos.

## Divisor por constante: NO asumas el divisor del template hermano

Misma familia: `x * 30 / 5` (asr #1 tras el `smull`) vs `x * 30 / 20` (asr #3) vs `/10`
(asr #2) — **la misma magia 0x66666667, distinto shift**. Tres hermanas de la misma familia
usan tres divisores distintos. Si copias de un hermano, **lee el shift del `asr` que va tras
el `smull`**: `asr #1`=/5, `asr #2`=/10, `asr #3`=/20.

## ★★ `bic` / `and #0xff` / `bic` = DOS CAMPOS DE BITS, no una mascara (2026-07-22)

`func_ov022_020b06d8`. La ROM tiene, con **una sola** carga y **un solo** store:

```
ldrb r1, [r0,#0x34]
bic  r2, r1, #1
and  r1, r2, #0xff     <- el estrechamiento a byte ENTRE los dos bic
bic  r1, r1, #2
strb r1, [r0,#0x34]
```

Ni `p &= ~3` (una sola mascara), ni `p &= ~1; p &= ~2;` (dos load/store), ni
`(unsigned char)(x & ~1) & ~2` con un local intermedio — todos fallan por un registro. Lo que
acierta son **dos campos de bits puestos a 0**:

```c
typedef struct { unsigned char bA : 1, bB : 1, rest : 6; } Flags;
Flags *f = (Flags *)(self + 0x34);
f->bA = 0;
f->bB = 0;
```

**Regla:** un `and #0xff` intercalado entre dos operaciones de bits sobre el mismo byte, sin
load/store entre medias, es la firma de **campos de bits consecutivos**. La mascara combinada y el
local intermedio dan el mismo valor y distinto registro.

## Otras dos del mismo bloque

- **`0xffff` vs `-1`**: escribir el centinela como `0xffff` lo manda al **pool literal** y arrastra
  un marco de pila entero (`push {r3,lr}`); escrito `-1` sale `mvn r3,#0`. En un `short`, el
  centinela se escribe **-1**.
- **Indexar sin reducir**: `*(short *)(self + i*2 + 0x38)` hace que mwcc cree **dos** variables de
  induccion (contador + offset en bytes); `((short *)self)[i + 0x1c]` da el
  `add r2, r0, ip, lsl #1` con el `+0x38` en el offset del store, que es lo que tiene la ROM.

## ★★★ CRACKEADA: `adds rX,rX,#0` -- la palanca es `+ (v - v)` (2026-07-22)

La familia x6 `func_ov181_020ccf18` (+ov182/183/184/250/251) estuvo bloqueada **toda una sesion**
por una sola instruccion: la ROM pone flags con `adds r0,r0,#0` donde mwcc emite `cmp r0,#0`.

```c
int pad;   /* SIN inicializar, a proposito */
*(int *)((char *)model + 0x84) = (func_02023eb4(2) + (pad - pad) != 0) ? -1 : 1;
```

`+ 0` literal lo pliega el compilador y sale `cmp`. **La diferencia de un local sin inicializar
consigo mismo NO se pliega** y produce el `adds` (un ADD que actualiza flags).

⚠⚠ **La respuesta llevaba meses en el arbol.** `func_ov114_020ccf28` ya estaba matcheada con
exactamente ese truco y difiere del park en **UNA instruccion** (store de byte en +0x48 en vez de
word en +0x84). El escaneo por secuencia exacta de mnemonicos NO las agrupo.

**Leccion de proceso, no de codegen: antes de declarar una clase bloqueada, busca en el C YA
MATCHEADO por forma aproximada.** Para eso esta ahora `tools/park_templates_fuzzy.py`
(distancia de edicion, por defecto 3). Con distancia 2 encontro 14 parks con plantilla, incluidos
los seis de esta familia. Nueve formas y un barrido de 27 compiladores se gastaron buscando fuera.

## ★★ Promocion con signo: `>>` sobre un `unsigned short`/`unsigned char` sale ARITMETICO

Tres funciones distintas han fallado por esto (`Ov022_PublishRecord`, `Ov008_HandleKind4Message`,
`func_ov022_02089784`), siempre con **todo lo demas correcto**:

```c
unsigned short h = ...;
(h << 29) >> 29        /* -> lsl + ASR   (h promociona a int con signo) */
((unsigned int)h << 29) >> 29   /* -> lsl + LSR, que es lo que tiene la ROM */
```

Igual con `>> 16` sobre una palabra leida por `int *`: sale `asr`. Leerla por `unsigned int *` da
`lsr`.

**Regla: si en el diff aparece `asr` donde la ROM tiene `lsr` (o al reves), el eje es el TIPO del
operando, no el shift.** Un campo de bits `unsigned` es la grafia honesta cuando encaja; el cast a
`unsigned int` sirve cuando el campo no es un bitfield real.

## ★★★ Deja el invariante DENTRO del bucle y que mwcc lo hoistee

Sintoma: todo casa menos el ORDEN de dos instrucciones del preheader -- tipicamente
`mov rX,#0` (el contador) frente a la ultima instruccion que calcula una base invariante.

Causa: el codigo hoisteado se emite al FINAL del preheader. Si tu C calcula la base en un
local antes del bucle, esa base sale como codigo normal, ANTES del init del contador; la ROM
la tiene DESPUES porque en su fuente estaba dentro del bucle.

```c
int *base = (int *)(x + 0x2000);       /* mal: add r4 antes del mov r5,#0 */
for (i = 0; ...) f(base[0x191] + off);

for (i = 0; ...) f(((int *)(x + 0x2000))[0x191] + off);   /* bien */
```

⚠ **No pliegues la constante**: `*(int *)(x + 0x2644)` no es lo mismo -- mwcc no puede partir
el desplazamiento y saca una instruccion de mas. Hay que dejar el `+ 0x2000` y el indice como
dos pasos, exactamente como los escribe la ROM.

Cerro `func_ov030_020b3efc` y la familia de 4 `func_ov036_020b4c50` / ov055 / ov075 / ov092,
que llevaba parkeada desde el 18/07 con una nota de "orden de emision de dos movs" y nueve
formas medidas -- ninguna era esta.

## ★★ `return` del primer parametro = r0 reservado hasta el final

Sintoma: la ROM usa r3 (o cualquier scratch alto) para un temporal y mwcc usa r0, en una
funcion aparentemente `void` cuyo primer parametro muere pronto.

Si la ROM **nunca** escribe r0 en todo el cuerpo, r0 sigue vivo al `bx lr`: la funcion
DEVUELVE su primer parametro. Cambia la firma a no-void y devuelvelo.

```c
int func(int a, int b, int c) { ...; return a; }   /* r0 intocable -> temps a r3/r1 */
```

Cerro `func_ov008_02051168` (48 B), parkeada con dos notas anteriores que culpaban al
coloreado. **Un valor de retorno que nadie usa es una señal comprobable, no decoracion:
mira si la ROM escribe r0 antes de dar por buena una firma `void`.**

## ★★ Las notas de park que culpan al "register allocation" mienten mucho

Tres de las cinco cerradas hoy tenian nota de empate de coloreado y ninguna lo era:

- `func_ov022_0208e7a0` -- el callee tiene **3 argumentos, no 4**.
- `func_ov008_0204ffe4` -- la forma del bucle (`for` con int con signo y la base releida
  dentro, no `do/while` con `unsigned`) la sacaba del hermano ya matcheado.
- `func_ov030_020b3efc` -- el hoisting de arriba.

**Antes de creerte una nota de park, corre `tools/park_templates_fuzzy.py` y compara con el
hermano matcheado.** La nota la escribio alguien que no tenia esa plantilla delante.

## ★★ "Empate de tail-merge" = casi siempre ORIENTACION DE LA RAMA

Si el ROM DUPLICA una cola compartida (la predica en un brazo y la repite en el otro) y tu
version la factoriza en una sola cola incondicional, no es que mwcc "siempre fusione": es que
escribiste el brazo equivocado primero.

```c
if (a == b) { tail(); return; }     /* mal: mwcc fusiona las dos colas -> 4 B menos */
...; tail();

if (a != b) { ...; tail(); return; }  /* bien: duplica, como el ROM */
tail();
```

El caso **no** depende de como escribas la cola (`x |= k` vs `x = x | k` dan lo mismo): depende
de cual de los dos casos va delante. Cerro `func_ov022_020902d4`, parkeada con una nota que
decia "mwcc ALWAYS tail-merges ... tried equal-first and not-equal-first" -- la variante buena
era not-equal-first CON `return` explicito y su propia copia de la cola.

## Aun abierto: mwcc convierte `r==1 || r==2` en un range check

`func_ov008_0204eb88`: el ROM hace `cmp r0,#1 ; cmpne r0,#2 ; bne`, mwcc hace
`sub r0,r0,#1 ; cmp r0,#1 ; ...ls`. Escribiendolo como dos comparaciones separadas
(`if (r != 1 && r != 2) goto zero;`) SI sale el `cmp/cmpne`, pero entonces mwcc predica los dos
`return` en vez de ramificar a una cola compartida (48 vs 52 B). Las dos mitades salen, nunca a
la vez.

## ★★★ Struct-typado = mwcc NO saca las direcciones invariantes del bucle

Sintoma: el ROM recarga `ldrb r0,[r6,#0x19]` / `ldr r0,[r6,#0xc]` con desplazamiento inmediato
dentro del bucle; mwcc precalcula `base+0x19` y `base+0xc` antes, los guarda (a veces en pila:
el frame crece) y el cuerpo sale 4-16 B mas largo.

```c
*(unsigned char *)(g + 0x19)   /* mal: reduccion de fuerza + spill */
g->bCount                      /* bien: recarga con offset inmediato */
```

Ya cerro `func_ov022_02091254` + `func_ov022_02091298` (THUMB) y `func_ov022_02088db0` (THUMB),
y estaba escrito desde el 18/07 en la nota de `func_ov048_020b4050` sin haberse aplicado a
ningun otro park. **Es la primera cosa que probar en cualquier park con un bucle sobre campos
de un objeto**, y va doble en THUMB, donde los desplazamientos inmediatos son cortos y el spill
se nota mas.

## ★★ Grupo de `case` "vacio" -> hay que ASIGNAR el valor por defecto

Si la tabla de saltos manda unos indices a un bloque que solo contiene un `b` a la salida
(un trampolin), esos casos estan escritos aparte en la fuente, y **no basta con `case N: break;`**
-- mwcc lo pliega al default. Hay que asignarles el valor por defecto explicitamente:

```c
case 2: case 3: case 4: group = 0; break;   /* 0 ya era el valor inicial */
```

Cerro `func_ov022_02093a1c` (96 B), parkeada como "mwcc does not dedup identical case bodies".

## ★★ Anidamiento invertido para fijar el orden fisico de dos brazos

`if (k == 0) A else if (k == 1) B` emite A primero. Si el ROM tiene B primero (alcanzado por
caida) y A detras (alcanzado por salto), inviertelo:

```c
if (k != 0) { if (k == 1) B; } else { A; }
```

Cerro `func_ov022_020911a8`. El `switch` equivalente añade una comparacion de mas.

## ★★★ Los "empates de reduccion de fuerza" NO son empates: array real + orden de declaracion

Toda la veta `[PROVEN TIE (strength reduction)]` de ov008 cayo con tres palancas. Sintoma:
mwcc convierte `base + i*stride` en un puntero que siembra y avanza (mov + add #N), gastando
uno o dos callee-saved de mas; el ROM mantiene el contador vivo y recalcula la direccion.

1. **Declara la tirada como un ARRAY DE VERDAD dentro de un struct.** `obj->idx[i]` no se
   reduce; `*(int *)(obj + i*4 + 0x14)` si. Con tres campos en la misma fila (0x14/0x34/0x44),
   mwcc calcula el puntero de fila UNA vez y llega a los tres por desplazamiento, como el ROM.
2. **Deja partida la constante grande**: `((int *)(base + 0x19c4))[j]`, no
   `*(int *)(base + j*4 + 0x19c4)` ni `base[...]` con la constante plegada. Asi mwcc emite
   `add #0x1000` + offset de carga `#0x9c4`, que es como lo parte el ROM.
3. **`(base + id)[0x810]` ≠ `base[id + 0x810]`.** La primera da `add r1,base,id` + carga con
   desplazamiento 0x810; la segunda pliega `id+0x810` en un registro de offset.

Y encima, **el ORDEN DE DECLARACION reparte los registros**: con todo lo demas byte-identico,
`func_ov008_0208b148` solo casa con `count, i, j, base` (las otras 23 permutaciones difieren
solo en que registro toca a cada local). Cuando el stream ya coincide y solo bailan los
registros, **barre las permutaciones de declaracion antes de declarar empate** -- son 24
compilaciones, medio minuto.

Cerradas asi: `func_ov008_02054b18`, `02054d3c`, `0205ffe8`, `020830c8`, `0208b148`,
`0204ef30`, `0204ef90`.

## ★ `and rX,rX,#1` antes del bic/orr = campo de bits de UN bit

`flags = (flags & ~1) | (x != 0)` sale una instruccion mas corto que el ROM: mwcc sabe que un
booleano ya vale 0 o 1 y se ahorra el enmascarado. El ROM lo enmascara porque en la fuente es
un campo de bits:

```c
unsigned int bUseAlt : 1;   /* +0x84 bit 0 */
obj->bUseAlt = (useAlt != 0);
```

## ★★ `mov rB, rA` justo despues de `mov rA,#0` = una variable se asigna DESDE la otra

Si la ROM pone un cero en un registro y acto seguido lo COPIA a otro, en la fuente no hay dos
`= 0` independientes: hay `a = 0;` y luego `b = a;`. Escribirlo con dos literales mete una
constante viva de mas y mwcc te tira algo a la pila.

```c
int offset = 0;
r = 0;          /* mal: mwcc spillea el puntero del buffer */
r = offset;     /* bien: adds r4,r5,#0 como la ROM */
```

Cerro `func_ov000_02054ac8` (THUMB, 84 B), parkeada como empate de asignacion de registros.
Aplica igual a los `mov r4,r5` / `mov r7,r5` de la familia ov048/ov022 (ahi arregla los dos
ceros pero queda otro residuo aparte).

## ★★★ `push {r3, ...}` es RELLENO DE ALINEACION, no un store del 4o argumento

Si mwcc necesita salvar un numero IMPAR de registros mas `lr`, mete uno extra en el `push`
para que el marco quede alineado a 8, y el que mete suele ser `r3`. **Ese r3 no es un dato.**

`func_ov008_0204d6a8` estaba parkeada como "+4B frame-layout tie: the ROM stores param_4 into
the struct's 3rd word via the prologue push". Leer ese r3 empujado como dato se invento un
CUARTO PARAMETRO y un TERCER elemento del array. Con el registro de dos palabras y la funcion
de un solo argumento, casa exacto.

**Antes de explicar un `push {r3,...}`, cuenta los registros**: r4,r5,lr = 3 palabras -> hace
falta un cuarto. Y comprueba si algo lee de verdad esa ranura de pila.

## Herramientas nuevas (2026-07-22)

- **`tools/park_sizes.py`** — compila TODOS los parks y los ordena por desviacion de tamaño.
  Separa los dos tipos: `same-size` (189 de 296) = el stream ya esta bien y solo bailan
  registros/orden -> barre permutaciones; `+/-N` = falta o sobra codigo -> arity del callee,
  forma del bucle, un case sin escribir, un cast de mas. **Son ataques distintos; empieza por
  saber en cual estas.**
- **`tools/park_permute.py`** — permuta el orden de declaracion de los locales de un park y
  compila cada permutacion. `--sweep` lo hace con todos.

## ★★ `switch` con pocos casos dispersos SI da cadena de comparaciones

Sintoma: el ROM prueba N valores sueltos, con todas las comparaciones delante y los cuerpos
detras, y una rama explicita "no coincide" a la cola comun. Eso es un `switch`. Un
`if/else if` entrelaza cada cuerpo con su prueba y **se come esa rama** (4 B menos).

`func_ov008_02067484` estaba parkeada diciendo que "a switch() makes mwcc pick a jump table":
con tres casos dispersos (2, 5, 7) no la elige. **No des por hecho que mwcc tabula; miralo.**

## ★★ Callee-arity, otra vez: `push {r3,...}` + "5o argumento" que no existe

`func_ov022_0209b1e8` estaba parkeada por "el 5o argumento va a la ranura de r3 empujado".
No hay 5o argumento: la ROM pone r0 y r1 y **no escribe nada en la pila**. El callee toma dos.
Es el mismo error de lectura que en `func_ov008_0204d6a8`. **Si crees que hay un argumento en
pila, busca el `str` que lo pone. Si no esta, no lo hay.**

## ★ `&= 0xfd` da `and`; `&= ~2` da `bic`

Trivial y cuesta 0 bytes de diferencia... salvo que es LA diferencia. Escribe siempre la
mascara como el complemento del bit que borras.

## ★★ Orientacion de la comparacion: quien va a la izquierda

`if (level < cap())` -> `cmp level, cap` ; `if (cap() > level)` -> `cmp cap, level`. Y si la
ROM usa `bls`/`bhi` en vez de `ble`/`bgt`, la comparacion es SIN SIGNO: el lado que no es el
byte tiene que ser `unsigned`. Cerro `func_ov022_0209be64`.

## Resultado negativo: el barrido de permutaciones no resuelve nada por si solo

`tools/park_permute.py --sweep` sobre los 297 parks restantes: **0 matches**. La palanca del
orden de declaracion es real, pero solo sirve cuando el stream YA es correcto por otro motivo.
Uso correcto: de una en una, despues de arreglar la forma. No como pesca.

## ★★★ Aridad del callee: mira las DOS direcciones (`tools/park_arity.py`)

Declarar **de mas** obliga a mwcc a mantener vivo un valor que la ROM no mantiene ->
un registro o un push de sobra. Declarar **de menos** hace lo contrario: la ROM copia el
resultado a otro registro porque sigue siendo un argumento, y tu version lo usa en sitio y
"ahorra" la copia. Eso es lo que llevaba dos parks archivados como *"our compiler is smarter"*.

`func_ov008_02072d9c` estaba declarado con UN argumento y toma DOS:

```
mov r0, r4          <- el arg 1 se prepara ANTES del store
strb r1, [r4,#0x54] <- ...asi que r1 sigue vivo
bl  func_ov008_02072d9c
```

**La prueba es el ORDEN.** Si un registro sigue vivo al llegar al `bl` y no hace falta para
nada mas, es un argumento. Cerro `func_ov008_02073d88` y `func_ov008_02073df0` de golpe.

`tools/park_arity.py` cruza los `extern` del park con lo que escribe la ROM. La direccion
"de mas" es fiable; la "DE MENOS" es ruidosa (el escaneo cruza bloques) y solo sirve como
lista de sitios donde mirar el orden a mano.

## ★★★ El `lsl #16`+`lsr/asr #16` antes de CADA llamada = el PARAMETRO del callee es short

Si la ROM re-estrecha el mismo valor antes de dos llamadas distintas, no esta "recalculando":
el prototipo del callee tiene `short`/`unsigned short` y el ABI obliga al LLAMANTE a estrechar
en cada sitio. Escribirlo en C como `x & 0xffff` mete el valor en el dataflow del llamante y
mwcc lo CSEa -> te faltan 8 bytes.

```c
extern int f(int list, unsigned short tag);   /* bien: lsl/lsr en cada call site */
f(list, tag);  f(list, tag);

extern int f(int list, unsigned int tag);     /* mal: un solo & 0xffff, CSEado */
f(list, tag & 0xffff);  f(list, tag & 0xffff);
```

Cerro `func_ov008_0206abb8` (parkeada como "-8B CSE tie: the ROM recomputes the mask") y
`func_ov008_0206fa1c` (parkeada igual). **Y ademas encadena las llamadas**: en 0206fa1c hubo
que anidarlas (`f(g(h(...)))`) en vez de pasar por locales, o el valor vuelve a caer en el
llamante.

Escaner: busca en el disasm parejas `lsl rX,rY,#16` + `lsr/asr` con el MISMO rY repetidas.
Solo dieron 6 candidatos sobre los parks, asi que es barato mirarlos todos.

## ★★★ `data[1]` (subindice) recarga el pool; `*(int *)((int)data + 4)` lo CSEa

Sintoma: el ROM hace `ldr rX,[pc,..]` en CADA rama que toca el global; tu version lo carga una
vez y lo guarda en un callee-saved -> 8 B de menos y un registro salvado de mas.

```c
extern int data_x[];
data_x[1]                       /* recarga del pool en cada uso, como el ROM */
*(int *)((int)data_x + 4)       /* una sola expresion -> mwcc la reutiliza */
```

Cerro `func_ov008_02050970` (parkeada como "CSE-recompute tie class") y es el mismo eje que
`func_ov008_0204ffe4`. **Mecanico: hay ~20 parks que usan la forma con cast; merece la pena
pasarlos todos.** `grep -rl "(int)data_\|(char \*)&data_" src --include=*.c | grep nonmatching`

## ★★ Una constante comparada que la ROM materializa = en la fuente es una VARIABLE

`cmp r0, r1` con `mvn r1,#0` delante NO es `x == -1` (eso da `cmn r0,#1`): es `x == algo`
donde `algo` es un local que vale -1. Igual que el truco del cero (`r = offset`).

Cerro `func_ov253_020d0938` junto con el struct-typado del campo (`actor->bReactState`, no
`*(signed char *)(*node + 0x1c7)`, que parte la direccion y gasta un `add` de mas).

## Clase abierta: el literal del pool cae en el registro equivocado

Tres funciones, todas THUMB/ARM pequeñas, con el stream identico y solo el registro del
`ldr rX,[pc,..]` distinto (mwcc siempre r0, la ROM r1 o r2):
`func_ov002_0205e1b8`, `func_ov002_0205e3e4`, `func_ov008_0207b8a8`.
En las tres el resto casa byte a byte. No lo mueve: el orden de declaracion, meter parametros
sin usar, la forma `&data[N]` vs cast, ni sacar la lectura del global antes o despues.
**Si alguna vez cae una, caen las tres.**

## ★★ La direccion de un argumento: LOCAL CON NOMBRE, no expresion inline

Si el ROM calcula el argumento a partir del resultado de la llamada anterior ANTES de meter
la constante en r0, y tu version copia el resultado a otro registro primero, el eje es que en
la fuente hay un local:

```c
MIi_CpuClear16(0, dst + f(...) * 2, n);   /* mal: mov r0,#0 primero, mov r1,r0 de copia */
int addr = dst + f(...) * 2;              /* bien: el add mientras r0 sigue vivo */
MIi_CpuClear16(0, addr, n);
```

Cerro `func_ov008_02050bb0` junto con `data[1]` y `rows <= 0` (no `rows < 1`: el ROM hace
`cmp #0` + `pople`).

## ★★★ El orden de declaracion incluye los temporales DE DENTRO del bucle

Refinamiento importante del crack del orden de declaracion. mwcc reparte los callee-saved
siguiendo el orden de declaracion, y un temporal declarado **dentro del cuerpo del bucle** se
asigna DESPUES de los locales de fuera. Subirlo al principio de la funcion desplaza a todos
los demas hacia arriba:

```c
void f(void) {
    unsigned int *p;        /* el temporal del bucle, PRIMERO -> r4 */
    int i;                  /* -> r5 */
    Row *row;               /* -> r6 */
    Hdr *hdr;               /* -> r7, que es donde lo tiene la ROM */
    ...
    do { p = ...; } while (...);
}
```

Cerro `func_ov022_02088830` y `func_ov022_02093ea8`, las dos parkeadas como
"base-coalescing tie". **Ojo: el struct-typado es lo que quita el coalescing; el orden de
declaracion solo coloca los registros.** Hacen falta los dos.

Esto tambien explica por que `park_permute.py --sweep` dio 0: solo permuta el bloque de
declaraciones del principio, y en muchos parks el temporal que hay que subir esta dentro del
bucle. **Sube los temporales del cuerpo al principio ANTES de barrer permutaciones.**

## ★★★ Resumen operativo del vector "array real de structs"

Ya ha cerrado ~15 parks. **Cualquier park cuya nota diga hoisting, coalescing, reduccion de
fuerza, induccion o "CSE de la direccion" se ataca asi, en este orden:**

1. Declara la tirada como **array de structs de verdad** (`Ent tbl[]` con el stride real como
   `sizeof`), y los campos invariantes como campos del objeto. Eso quita el hoisting y el
   coalescing.
2. Sube al principio de la funcion **los temporales declarados dentro del bucle**.
3. Barre las permutaciones del orden de declaracion (`tools/park_permute.py <func>`).
4. Comprueba la orientacion de la rama y el `<= 0` vs `< 1`.

`func_ov022_020b0ba8` necesito los cuatro pasos: struct + `tb` subido + orden `r,i,tb,lim`
(la unica de 24). `func_ov022_020ad7f0` solo el primero: con `slots[idx].uFlags` la lectura de
la bandera sale con direccionamiento por registro y el `add` aparece solo donde hace falta.

## Balance del vector `data[N]` (2026-07-22)

Cinco parks cerrados en una tarde con la MISMA sustitucion, y cada uno estaba archivado con un
diagnostico distinto:

| funcion | diagnostico del park | causa real |
|---|---|---|
| `func_ov008_02050970` | "CSE-recompute tie" | `data[1]` |
| `func_ov008_02050bb0` | coloreado + scheduling | `data[1]` (+2 mas) |
| `func_ov024_02082c44` | "pure instruction scheduling" | `data[1]` |
| `func_ov024_02084db8` | canonicalizacion `ands`/`tst` | `data[N]` + **valor de retorno** |
| `func_ov022_02092d68` | coloreado del base pooled | `data[0x35]` |

**Regla: en cuanto veas `(int)&data_` o `(char *)&data_` en un park, cambialo a subindice ANTES
de leer la nota.** Quedan ~13 ficheros con la forma de cast:
`grep -rln "(int)&data_\|(char \*)&data_\|(int)data_" src --include=*.c | grep nonmatching`

---

# Sesion autonoma 2026-07-22/23 -- cracks nuevos, todos con funcion matcheada detras

## ★★★ `push {r0,r1,r2,r3}` al principio SIEMPRE es el prologo VARIADICO

Tres parks del mismo dia tenian esta misma causa raiz y tres diagnosticos distintos y equivocados
("empate de layout de marco", "empate de asignacion de registros con struct alojada", "la ROM
duplica en un registro una copia en memoria"). Ese push nunca es una decision de marco ni el "home"
de una struct por valor: es varargs. Consecuencias practicas:

- **Un argumento cuya direccion se pasa a una llamada** (`add r2,sp,#0x1c` con el bloque r0-r3
  justo ahi) => declara la funcion `...` y toma `&param`. El bloque existe gratis y la copia a un
  hueco propio desaparece. (`func_ov008_02082ecc`.)
- **Argumentos leidos de offsets fijos del bloque mientras el ultimo con nombre se queda en su
  registro** => varargs con el ultimo con nombre en registro. (`func_ov008_02069954`, donde el
  segundo argumento se habia modelado como struct por valor.)

## ★★★ NOMBRA los varargs que necesitas -- `va_start(ap, last)` mete `last` en memoria

`va_start(ap, mode)` toma `&mode`, lo que marca el parametro **address-taken**; a partir de ahi mwcc
considera canonica la copia que el prologo variadico ha volcado y **relee el parametro de memoria**
(`ldr r4,[sp,#0x24]`) donde la ROM lo cachea de su registro (`mov r4,r1`). Es un residuo de UNA
instruccion y ninguna reescritura del cuerpo lo toca.

**Arreglo: no tomes nunca la direccion de un parametro que si se usa.** Declara el PRIMER vararg
como parametro con nombre y basa el va_list en SU direccion:

```c
void f(int self, int mode, int rest, ...) {   /* 'rest' es el primer vararg */
    g(self, (char *)&rest);                   /* mismo add r1,sp,#0x28 */
```

`rest` no se lee nunca, asi que no cuesta nada, y `mode` se queda en r1. (`func_ov221_020d3f38`,
`func_ov221_020d43a0`, +8 gemelos por dedupprop; `func_ov006_02051fbc` pasa de -4 a tamaño exacto.)

**Efecto de segundo orden:** alcanzados a traves de un `ap` que avanza, mwcc guarda el puntero en un
registro y calcula el segundo acceso como `add r2,ip,#0xc`, donde la ROM materializa
`add r2,sp,#0x24` desde cero, y ademas funde dos cargas contiguas en un `ldm`. **Un parametro con
nombre por cada vararg** da un offset de marco independiente por acceso y mata las dos cosas.
Si el vararg es una struct por valor, declarala como tal (`Vec3 dest`) -- es lo que realmente es.

⚠ **El contrario tambien existe.** En `func_ov008_0206eb64` la ROM SI relee el parametro del bloque
y usa la forma alineada de APCS (`add sp,#N ; bic #3 ; add #4`): ahi el `va_start(ap, param_2)`
ingenuo es el correcto y nombrar el vararg seria el error. Lee el desensamblado antes de elegir.

## ★★★ Un test de PERTENENCIA quiere un `switch`, no una cadena de `||`

`a == K1 || a == K2 || a == K3 || a == K4` se colapsa a una cadena `cmp/cmpne` de la mitad de
tamaño. Si la ROM **biseca el rango de valores** (`cmp #K2 ; bgt ; bge ; cmp #K1 ; beq ; b` y luego
una comprobacion de rango sobre el par alto, con una constante en el pool), eso ES el layout de
`switch` de mwcc. Cuatro `case` que caen al mismo cuerpo lo reproducen byte a byte, entrada de pool
incluida, porque ni el colapso de flags ni el plegado de rango se aplican a etiquetas `case`.
(`func_ov008_0208b7a8` y su complemento `func_ov008_0208a5e8`, los dos parkeados como "empate
probado de codegen de test de pertenencia".)

## ★★ El orden de la cadena de comparaciones de un `switch` es un MANDO: hazlo `unsigned`

Ya estaba escrito que mwcc ordena la cadena **numericamente** y que por eso `case 0` / `case -2`
prueba -2 primero. Lo que faltaba es que eso se puede voltear: **lee el selector como `unsigned`** y
los mismos dos casos pasan a ser 0 y 0xfffffffe, con lo que 0 se prueba primero.
`beq X ; beq Y ; b Z` es la forma de switch; `bne Z ; b X` es la de if/goto -- si ves la primera,
quieres un switch aunque el fuente parezca una cadena de ifs. (`func_02020928`.)

## ★★ Guarda primero y liga el local DESDE el hueco para partir los registros

La ROM guarda el resultado de una llamada directamente desde r0 y se queda la copia con flags en
otro registro; `x = f(...); slot = x;` guarda el registro de la copia. Escribiendo

```c
state[2] = func_ov107_020cab14(*state, 0);
target   = state[2];      /* mwcc reenvia el valor: ni recarga ni coste de tamaño */
```

sale el reparto de la ROM. La nota anterior habia medido "+4B" releyendo `state[2]` **dentro de la
rama**, que si recarga; ligarlo justo despues del store no. (`func_ov200_020ceee0`, x3.)

## ★★ `goto` a una etiqueta detras del retorno normal = bloque de salida FUERA DE LINEA

Un `return 0;` dentro de un `if` sale EN LINEA y se ahorra el branch (-4 B). Si la ROM salta a un
`mov r0,#0 ; pop` colocado **detras** del retorno normal, escribe `goto ret0;` y pon la etiqueta al
final. Es la version "de salida" del crack de early-return/else ya documentado.
(`func_ov003_0204e5b0`.)

## ★★ `(-i) << 3` en vez de `i * -8` -- la reduccion de fuerza la invita la MULTIPLICACION

`array[k] = i * -8` dentro de un bucle se convierte en un contador `sub r2,r2,#8`. Escrito como
`(-i) << 3` -- negar y luego desplazar, que es lo que emite la ROM (`rsb r2,r3,#0 ; lsl r2,r2,#3`) --
la multiplicacion no aparece y no hay nada que reducir. Lo decide la forma de la expresion.
(`func_ov003_0204e5b0`; su nota decia "reduccion de fuerza no dirigible".)

## ★★ Una conversion de PROTOTIPO no se puede CSEar; un cast escrito dos veces si

`(short)mode` en dos sitios de llamada se saca por CSE a un registro callee-saved y el `int`
original deja de estar vivo (-4 B: falta el `mov r6,r1`). Declarando el parametro del callee `short`
y pasando `mode` pelado, la conversion pasa a la secuencia de paso de argumentos, se emite dos veces
y el original sigue vivo a traves de la primera llamada. (`func_ov117_020cc270`, cabeza de familia
de 5.)

## ★★ Leer un global de 64 bits EN LINEA impide que mwcc funda las dos mitades en `ldm`

Ligado a un local, `*p` (u64 en offset 0) sale como `ldm r4,{r1,r4}`; la ROM emite dos `ldr`. Con el
acceso escrito en linea en sus dos usos salen los dos `ldr`. Solo pasa en offset 0 -- un u64 en
`+0x464` no se puede fundir y por eso no da problema. (`func_ov022_020945a8`, 4 B.)

Y en la misma funcion: un predicado denso de 64 bits **no hay que "derivarlo"**. Los pares
`cmp;cmpeq` son un `!= 0` de `unsigned long long` normal y `mask &= ~0x80ULL` sale de verdad como
"materializa -1 y -0x81 desde un cero y haz AND de las dos mitades" (`sub;sub;and;and`).

## ★★ Una sola lectura `volatile` niega un CSE Y con ello rompe la predicacion

La ROM releia `p5[1]` para la cuarta comparacion de una cadena `&&` en vez de reutilizar la carga de
la tercera, y ademas RAMIFICABA donde mwcc predicaba (`addlt/sublt/cmplt`). Marcar **solo esa
lectura** `((volatile int *)p5)[1]` compra las dos cosas: es el mismo acceso, no cambia la semantica,
y negar el CSE deja el bloque demasiado largo para predicarlo. 8 bytes. (`func_ov008_02069954`.)

## ★ El orden de operandos del `cmp` sigue al local con NOMBRE -- y puede ser el otro operando

Confirmado por segunda vez y con un giro: en `func_ov022_0209ea44` siete formas anteriores habian
variado el OBJETIVO (local, tipo, posicion de la declaracion) sin mover el `cmp`. La palanca era
ligar el **ELEMENTO** a un local dentro del bucle. Cambiar el orden en el fuente no hace nada.

## ★ Una reloc con nombre distinto puede ser solo el `extern` mal escrito

`verify_idx` dice `relocs difieren` con `func_020bd7c4` frente a `func_ov105_020bd7c4`: el simbolo
real lleva prefijo de overlay. Cuesta diez segundos y no es un empate.

## ★★★★ EL INDICE DE ARRAY CON EL OFFSET DE CAMPO PLEGADO -- retira la clase "reduccion de fuerza"

*(2026-07-22. Cierra el que era el mayor bloqueo del catalogo.)*

`deferred-ties.md` y `state.md` decian: *"la ROM mantiene el contador i vivo y lo escala en linea
(`add rX, base, i lsl#N`); la build 139 SIEMPRE lo reduce a un puntero de induccion. Ninguna
escritura del fuente lo evita. **Salta los bucles `base + i*stride`.**"* Con cinco funciones
archivadas asi solo en ov008, mas ov024, ov254, ov000, ov003, ov022...

**Es falso.** La escritura que funciona es:

```c
((T *)base)[i + K]            /* T = tipo del tamaño del PASO, K = OFFSET_DEL_CAMPO / sizeof(T) */
```

es decir: indexa el OBJETO ENTERO con un tipo de elemento cuyo tamaño es el paso, y pliega el
offset del campo DENTRO del indice. Ejemplos reales, todos byte-exactos:

| ROM | escritura correcta |
|---|---|
| `add r0, obj, i lsl #2 ; ldr [r0,#0x384]` | `((int *)obj)[i + 0xe1]` |
| `add r0, ctx, i lsl #2 ; ldr [r0,#0xac]` | `((int *)ctx)[i + 0x2b]` |
| `add r0, self, i lsl #3 ; ldr [r0,#0x3b8]` | `((Pair8 *)self)[i + 0x77].a` |
| `add r0, base, i lsl #3 ; str [r0,#0x140]` | `((Pair8 *)base)[i + 0x28].a` |
| `add r3, msg, i lsl #1 ; strh [r3,#0x24]` | `((unsigned short *)msg)[i + 0x12]` |

**Por que funciona**: no queda ninguna expresion que reducir. La escala ES el tamaño del elemento
y la constante ES un inmediato del modo de direccionamiento, asi que mwcc no tiene un
`i * stride + offset` que convertir en un puntero que avanza.

**Las tres escrituras que SI fallan**, y en que fallan:
- `base[i * K + M]` -> puntero de induccion (`add r5,r5,#4` al final del bucle);
- `*(int *)(base + M + i * 4)` -> puntero de induccion;
- `((int *)(base + M))[i]` -> **iza la base** a un registro y usa `[base', i lsl #2]`, que es la
  forma espejo y ademas roba un registro callee-saved.

⚠ **La tercera es la trampa**: es la escritura "obvia" con indice de array, sale con el TAMAÑO
correcto, y por eso varias notas de park la dieron por buena y concluyeron que el eje estaba
agotado. La diferencia esta en donde vive el offset del campo: **dentro del indice** (bien) o
**dentro de la base** (mal).

**Como buscar candidatos**: la firma en el desensamblado es `add rX, rY, rZ, lsl #N` seguido
inmediatamente de un acceso `[rX, #imm]`. Un barrido sobre las parkeadas encontro **22**.

Ya cerrados con esto: `func_ov008_02068878`, `func_ov024_020859d4`, `func_ov254_020d5474`,
`func_ov278_020cd8cc`/`020ce7d4`, `func_ov245_020cc86c`/`020d3aac`.

## Sesion 2026-07-22 (tarde/noche) — cracks nuevos

### ★★★★ LA PALANCA DE va_start (cierra toda la familia de forwarders variadicos)
El `push {r0,r1,r2,r3}` al entrar es el prologo variadico. La lista `va_list` que el ROM
construye es SIEMPRE `add rX,sp,#N ; bic rX,#3 ; add rX,#4`. Escribelo LITERAL:

```c
void *f(char *dst, const char *fmt, ...) {
    return g(dst, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
```

Dos efectos a la vez: (1) reproduce el trio add/bic/add; (2) tomar `&fmt` marca el ultimo
parametro con nombre como address-taken, asi que mwcc lo RELEE de su hueco homed
(`ldr r1,[sp,#0xc]`) en vez de conservar el registro entrante.
Cerro `OS_SPrintf`, `OS_SNPrintf` y `func_020262a0` (que llevaba parada en "20 vs 26 B").
Ojo: declarar el primer vararg como parametro con nombre y usar `&rest` NO vale aqui
(da 28 B); es la expansion con `& ~3u` la que hace falta.

### La familia de veneers SDK (mina enorme, ~120 funciones en una tarde)
`ldr ip,[pc] ; <1-2 movs> ; bx ip` = forwarder con argumentos constantes. Plantilla:
```c
extern void *TARGET();
void *NAME(args...) { return TARGET(args..., CONST); }
```
K&R (`()`) en el extern para poder pasar mas argumentos de los declarados.
⚠ El modulo al que pertenece cada una sale de QUE `config/arm9/**/symbols.txt` la lista,
no del nombre: `OS_UnlockByWord_0x020bd9ec` vive en ov105, `OSi_IrqDma0_0x020afcbc` en
ov025. `grep -rl "^NOMBRE " config/arm9`.

### Otros cracks confirmados hoy
- **`% 4` vs `/ 4`**: el trio `lsr #31 / rsb lsl#30 / add ror#30` es el RESTO con signo,
  no la division (`/4` da `asr#1 / add lsr#30 / asr#2`). (func_02032cbc)
- **Constante de 16 bits reutilizada**: si escribes `-1` en un int y `0xffff` en un short,
  mwcc ve que coinciden en 16 bits y REUSA el registro, perdiendo la entrada del pool.
  Escribe el 0xffff como `unsigned short` literal. (func_020310e8, 8 bytes)
- **`ldm r1,{r1,r2}` = struct de 2 palabras por valor**, no dos `ldr`. (FS_OpenFile)
- **Salidas compartidas**: cuando dos caminos de fallo devuelven lo mismo, el primero tiene
  que llegar con `goto`; escrito como `return 0` inline mwcc duplica el epilogo o predica.
  (CTRDG_IsOptionCartridge, FS_OpenFile, func_ov002_0207a744)
- **Bucle infinito con la llamada dentro**: `OS_Terminate` es
  `for(;;){ OS_DisableInterrupts(); OS_Halt(); }` — el `b` final salta por ENCIMA de las dos.
- **El indice como array vs induction var**: `o[i + 0xd]` (indice de halfwords) da
  `add r1,r0,ip,lsl#1`; `o + 0x1a + i*2` construye una segunda variable de induccion.
- **Cero copiado del contador**: `int z = i;` reproduce `mov r2,r3` donde `mov #0` no.
- **Bitfields**: `lsl #16 / lsr #20` y `lsl #28 / lsr #28` = extraccion de bitfield
  (12 bits a offset 4 y 4 bits a offset 0 en un contenedor de 16). `>>4` da `asrs`.
  Accede por PUNTERO al elemento del array, no por copia (una copia cuesta 4 bytes).

### Clase BLOQUEADA nueva: constante pequena en el literal pool
`ldr r1,[pc,#N]` cargando 0x17 / 0x69 / 0x6b cuando `mov r1,#0x6b` es codificable.
Ninguna de las 27 builds ni 18 pragmas ni 14 juegos de flags lo reproduce, y NO EXISTE
ninguna funcion ya casada en el arbol con una palabra de pool < 0x100 sin reubicar.
Afecta a func_02035d78/90, func_02001054/108c, func_ov002_0206a418/46c.
Nota previa igual en `nonmatching/func_ov000_0204ee24.c` ("el ROM aparca 0x1c en el pool").
Es la evidencia mas fuerte de que la retail es una build >= 140 que no tenemos.

---

## ★★★ 2026-07-23 -- UNA ASIGNACION ENCADENADA CAMBIA LA PLANIFICACION DEL BLOQUE ENTERO

Sintoma: **las mismas instrucciones en otro orden**, tipicamente mwcc adelantando un `ldr [pc]` o un
`mov rX,#0` una ranura por encima del `str` que le precede en el ROM.

Palanca: **funde dos sentencias en una asignacion encadenada** (`a = b = 0;`) en cualquier punto del
mismo bloque basico. No hace falta que sea cerca del residuo.

Prueba de control (func_02023c60, 14 stores): con las catorce sentencias sueltas mwcc adelanta la
carga del pool; encadenando UN solo par -- `p[5]=p[6]=p[7]=0`, o `p[8]=p[9]=0`, o `p[11]=p[13]=0` --
casa, y las tres opciones producen el MISMO codigo. El stream es identico salvo la posicion de esa
carga, asi que no es un efecto de coloreado: la decision local del planificador depende del numero /
la forma de las sentencias del bloque.

Confirmada en `func_ov245_020cd6d0` (encadenar los dos ultimos stores a cero sube el `mov r2,#0` y el
`sub` por encima del primer store).

⚠ **No es universal.** No mueve func_ov119_020ce610, func_ov022_02092b60, func_ov033_020b350c ni
func_ov200_020cff54. Es la PRIMERA prueba a hacer, no la unica.

## ★★ `(char *)0 + x` tambien LAVA un cero para que no se pliegue

Ya estaba catalogado como la forma de forzar `add rD,rS,#0`. Lo nuevo: sirve para impedir la
propagacion de constantes. En `func_ov245_020cd6d0` el ROM forma 0xff con `sub r3, r2, #1` a partir de
un cero vivo en registro; `0xff`, `-1` y `zero - 1` se pliegan todos a un `mov r3,#0xff` tardio, y
`(int)((char *)0 + zero) - 1` no.

## ★★ Bitfield real contra `and #mask`: mwcc pliega los pares de shift SIMETRICOS

`(x << 0x1d) >> 0x1d` se pliega a `and r0, r0, #7`. `(x << 0x1a) >> 0x1d` no se puede plegar y
sobrevive. Por eso una misma funcion puede tener dos extracciones que casan y una que no, y parece
un empate de codegen cuando es un problema de tipo.

**La forma buena es un struct de bitfields sobre la MEMORIA** (`struct { unsigned char bit:3, row:3,
col:2; } *s = (void *)p; ... s->bit ...`), no un shift explicito sobre un valor ya cargado: mwcc
CSEa el `ldrb`/`ldrh` de las varias lecturas de campo, asi que sale una sola carga y las extracciones
del ROM. Cerro `func_ov022_020b0e64` y arreglo el tamano de `func_ov022_02089784`.

## ★ `& ~BIT` contra `& 0xffXX`

El complemento de un literal `int` (`x & ~0x40`) es lo que mwcc convierte en `bic r1,r1,#0x40`. La
mascara de 16 bits equivalente (`x & 0xffbf`) no es un inmediato ARM y sale como palabra del pool
mas un `and` de registro. Si el ROM tiene `bic`, escribe el complemento. (func_ov022_0209bdbc.)

## ★ Copia de struct contra asignaciones campo a campo -- la firma esta en el ORDEN

Si el ROM emite **las dos primeras cargas antes del primer store**, es una asignacion de struct.
Campo a campo mwcc empareja cada carga con su store (`ldrh;strh;ldrh;strh`) y ademas invierte el par
respecto al fuente. `func_ov008_0205714c` casa con `init = *(Cursor *)cur;` y no casa con ninguna de
las ocho combinaciones de orden de declaracion/asignacion campo a campo.

## ★ Aritmetica de punteros para fijar el orden de operandos de una suma

`adds rd, base, rd` (la base como Rn) solo sale si `base` es un `char *`; con la base como `int` mwcc
canonicaliza la suma conmutativa a `adds rd, rd, base`. La aritmetica de punteros no es conmutativa
en su IR, y eso es lo que fija el orden. (func_ov022_020afe14, seis stores.)

## ★ Un indice MUTADO en vez de dos offsets constantes

Cuando dos campos lejanos se tocan seguidos y el segundo esta a K bytes del primero, el ROM suele
hacer `ldr rN,=off1 ; ... ; adds rN,#K`. Eso NO sale nombrando el segundo offset -- ni directo, ni
como `off1 + K`, ni por puntero, ni con una variable de indice de solo lectura. Sale con la variable
**mutada**: `off = off + K;`. (func_ov002_02079adc, +0x1c2 y +0x1ce.)

## ★ `switch` contra `||` -- y la guarda ALREDEDOR del switch

- `s == 0 || s == 1 || s == 2` se pliega a `and #0xff ; cmp #2 ; bhi`. El `switch` con esas tres
  etiquetas conserva `cmp #0 ; cmpne #1 ; cmpne #2 ; bne`. (func_ov212_020cd494 x3.)
- Al reves: si el ROM comprueba "distinto de cero" Y ADEMAS un switch de dos etiquetas, el test de
  cero tiene que ser un `if` que ENVUELVE al switch. Fundido en una sola condicion mwcc demuestra
  que sobra y pierde una instruccion. (func_ov008_0204eb88.)

## ★ Orden de CARGA y orden de DECLARACION son dos ejes distintos, y a veces hacen falta los dos

`func_ov008_02077908` necesitaba `span` declarado antes que `pos` (para que el ROM cargue el indice
de pagina antes que el offset) **y** `lim` antes que `pos` (para colorear r0/r2 en el clamp). Probar
solo uno de los dos ejes deja exactamente el mismo residuo, lo que hace pensar que el eje no sirve.

## ★★ Post-decremento DENTRO del argumento de la llamada

Si el ROM emite el `sub rN, rN, #1` **entre dos llamadas** -- despues de montar el registro del
argumento y antes del `bl` -- el fuente es `f(..., (short)tag--, ...)`, no una sentencia
`tag = tag - 1;` aparte (esa se planifica detras de las dos llamadas).
Cerro `func_ov008_020679f8` y `func_ov008_02067a7c`, y con dedupprop cuatro gemelas mas.

## ★ La guarda va ANTES de la aritmetica que no depende de ella

`func_ov008_02075f00`: el ROM emite `cmp` (el test de disponibilidad) delante del `lsl` (la
columna). Escribiendo el calculo de la columna primero mwcc intercambia el par. El `moveq`
predicado cae detras de la suma en los dos casos -- esa parte si es el planificador.

## ⛔ Umbral de LONGITUD DE BLOQUE en el orden de montaje de argumentos (medido)

En la cola de `func_0203c634` el ROM siempre hace `ldrsb r1 ; ldr r2,[pc] ; mov r0,rX`; 900+
funciones casadas lo confirman y **ninguna** casada tiene el orden contrario. Compilando
`func_ov206_020ccd68` con 1/2/3/4 llamadas previas a `func_0203b9fc`: con 1-3 sale el orden del
ROM y **con 4 mwcc adelanta el `mov r0`**. No lo mueven el estilo del extern (K&R o prototipado),
ni pasar `self` como `int` o `int *`, ni el numero de sentencias. Es longitud de bloque.
Bloquea ov206_020ccd68, ov206_020ccce8, ov235_020d1c20 y ov235_020d1b98.

## ★★ `orr rD, rS, #0` (copia redundante): la operacion tiene que ser de VERDAD de 64 bits

`func_ov008_0205b720` y `func_ov025_0208dc8c` (gemelas). El ROM copia el parametro a otro registro
con `orr r1, r5, #0` antes del `lsl`; mwcc elimina la copia (76 B contra 80).

La forma que casa:

```c
unsigned int slot = (unsigned int)((unsigned long long)param_1 | 0x100000000LL);
```

El bit que se pone es el 32, que el estrechamiento a `unsigned int` tira, asi que el valor es
exactamente `param_1` -- pero la mitad BAJA del OR de 64 bits sigue teniendo que materializarse en
su propio registro, y esa es la copia.

⚠ **Todas las formas de 32 bits se pliegan**: `param_1 | 0`, `param_1 & 0xffffffff`, un temporal
intermedio, `(unsigned long long)x | 0` y `& 0xffffffffLL` (mwcc sabe que la mitad alta es cero).
Tambien fallan `& ~0x100000000LL` y `& ~0x200000000LL` (salen 88 B). Es especificamente un OR de
64 bits con un bit por encima del 31.

Es la hermana del `(char *)0 + x` que fuerza `add rD, rS, #0`: el catalogo de "copias redundantes"
tiene ya dos entradas y cada mnemonico necesita su propio truco.

## ★★ La cadena decide tambien QUE variable se derrama a la pila

`func_ov024_02083368`: tres handles inicializados a 0 y usados como los tres argumentos de una
llamada. Con `h0 = 0; h1 = 0; h2 = 0;` mwcc elige el PRIMERO para el hueco de pila y deja el
tercero en registro; con `h0 = h1 = h2 = 0;` los inicializa en el orden inverso y cambia esa
eleccion, que es lo que hace el ROM. Tercera funcion de la sesion que decide una cadena.

## ★ El bloque de exito FUERA DE LINEA se pide con un `goto`

`func_0203498c`: el ROM deja el `return 0` local inline y salta al bloque que escribe y devuelve 1
(`bne ->ok ; movs r0,#0 ; pop ; ok: ...`). Escrito como `if (a && b) { ...; return 1; } return 0;`
mwcc mete el exito inline y el `return 0` al final. La forma que casa es
`if (a && b) goto ok; return 0; ok: ...; return 1;`.

## ★ La escala del indice se calcula ANTES de la llamada

En la misma funcion, `off = index * 4` como sentencia propia antes del `bl` reproduce el
`lsls r5,r5,#2` que el ROM emite por encima de la llamada; calculado en el punto de uso se
planifica despues.

## ★★ Dos terminos del mismo indice pueden necesitar DOS deletreos distintos

`func_02025074`: `base + ((x << 0x11) >> 0xf) + (y << 0x10 >> 0xe)`. El primero hay que dejarlo
como el par de shifts explicito (es un truncado a 15 bits y luego *4, y `(unsigned short)x * 4`
sale a 16); el segundo hay que pasarlo por un local `unsigned short` y escribir `y * 4`, porque
como el mismo par de shifts mwcc pliega la mascara dentro del shift (`p << 23 >> 21`) y se ahorra
una instruccion. Escribir los dos igual falla de las dos maneras.
Ademas la mascara 0xfffffc es UN local: el ROM la carga una vez y deriva las mascaras de 0x1f con
`r1, lsr #15`, que es lo que sale gratis con una variable compartida.


## ★★★ La constante en BYTES plegada dentro del INDICE mata la reduccion de fuerza

`func_ov008_0205e734` (2026-07-23). Un bucle `for (i...) { p = *(int *)(base + i*4 + 0x19c4); }`
hace que mwcc reduzca en fuerza el bucle a un puntero de induccion: un callee-saved mas y un push
mas grande. La ROM recalcula `base + i*4` cada vuelta. La forma que casa:

```c
int p = ((int *)base)[i + 0x671];      /* 0x19c4 / 4 */
```

Con el offset dentro del SUBINDICE no hay segunda variable de induccion. Esto **retira la clase
"loop strength-reduction" entera** de la lista de bloqueadas: su nota decia haber probado
"induction/array-index/held-base/byte-offset", pero el array-index que probaron dejaba la
constante fuera del corchete.

## ★★ El orden de DECLARACION colorea, el de ASIGNACION decide que cero se materializa

`func_ov022_020b02a4`. Cuando dos o mas locales valen 0, mwcc materializa el cero del PRIMERO que
se asigna y copia los demas de el (`movs r5,#0` y luego `adds r4,r5,#0`). El orden de DECLARACION
es otra cosa: decide que registro toca a cada variable. Hay que acertar los dos ejes por separado
-- declarar `i, result, slot` y asignar `result = 0;` el primero. Ninguna de las seis
permutaciones de declaracion CON inicializador llega, porque el inicializador ata los dos ejes.

## ★★ Reasignar el offset sobre el propio puntero, constante a la izquierda y con CAST

`func_ov002_0205e1b8` / `0205e1d4`. Escrito como una sola expresion `*(int *)(ctx + 0x4a4)`, mwcc
evalua primero el operando complejo (el deref del global), asi que el deref se lleva el registro
bajo y la constante del pool el alto; la ROM los tiene al reves y ademas mete la carga de la
constante en el hueco de load-use que deja el `ldr [pc]` del global. La forma que casa:

```c
ctx = *(char **)&data_x;
value = 0;
ctx = (char *)(0x4a4 + (int)ctx);   /* sentencia propia, constante a la IZQUIERDA, CON cast */
entry = *(int *)ctx;
```

Las dos mitades son necesarias: sin la sentencia aparte no cambia el orden, y sin el cast mwcc
canonicaliza la suma (`ctx = ctx + 0x4a4;` NO casa, `(char *)(0x4a4 + (int)ctx)` si).

## ★ El bloque de FALLO fuera de linea tambien se pide con un `goto`

`func_02034428`. Ya estaba catalogado para el bloque de EXITO; el brazo contrario es igual. La ROM
salta POR ENCIMA del bloque de fallo hasta el epilogo de exito
(`beq ret0 / stores / b ret1 / ret0: return 0 / ret1: return 1`). Con un `return 0` temprano, en
cualquiera de sus dos formas, mwcc deja que los stores caigan por fall-through dentro del
`return 1` y se ahorra el branch: dos bytes de menos.

## ★★ "La ROM materializa el 0 de retorno antes de los `cmp`" no es predicacion

`func_ov044_020b3a2c` y sus tres gemelas. Si el 0 se devuelve por VARIOS caminos, ponerlo en una
variable asignada en cada case y devuelta UNA sola vez al final lo deja vivo en todos ellos, y
mwcc emite el `mov r0,#0` sin predicar en el hueco entre el `cmp` y el branch -- que es lo que
hace la ROM. Ojo al orden: el puntero base tiene que declararse ANTES que el resultado, o se
intercambian el `add` y el `cmp`.
(No sirve cuando el 0 solo hace falta en un camino: ahi mwcc predica y sigue abierto --
`func_ov006_0204e35c`.)

## ★ Romper un CSE de direccion deletreando la segunda lectura por otra base

`func_ov022_0208a830`. La ROM recalcula `add r0, self, idx lsl #2` despues de una llamada en vez
de guardarla en un callee-saved. Escritas las dos lecturas igual, mwcc las unifica y salen 4 bytes
de menos. `*(int *)(self + idx*4 + 0x18)` la primera y `((int *)((char *)self + idx*4))[6]` la
segunda -- misma direccion, mismas dos instrucciones -- basta para romper el CSE.

## ★★★ El pliegue booleano (0,1): un `if` REDUNDANTE lo desactiva (2026-07-23)

Sintoma: al final de la funcion, `if (c) return 0; return 1;`. La ROM emite
`b<!c> L ; movs r0,#0 ; pop ; L: movs r0,#1 ; pop` (brazo-then inline, la disposicion normal)
y mwcc emite la imagen especular `b<c> L ; movs r0,#1 ; pop ; L: movs r0,#0 ; pop`.

**Es especifico del par de constantes (0,1)**: mwcc lo reconoce como el booleano `!c` y elige la
disposicion el mismo. Medido con un barrido de pares: (0,2), (0,3), (0,0x100), (1,0), (1,2), (2,1)
salen TODOS con el brazo-then inline; solo (0,1) se invierte. Tambien es independiente de la
condicion (`==`, `!=`, `<`, `<=`, `>`, `>=`, contra 0 o contra un registro: los once casos dan lo
mismo) y del tipo de retorno.

**Crack**: un segundo `if` cuya condicion mwcc pueda demostrar redundante. No cuesta ni una
instruccion y saca al par del caso especial:

```c
    buffered = Buffered();
    if (buffered < frames) return 0;
    if (buffered >= frames) return 1;   /* redundante A PROPOSITO */
    return 1;
```

Cerro `func_ov024_02083414` y `func_ov024_020833dc` (+2 gemelas en ov012 por dedupprop).

⚠ Antes de dar con ello se probaron ~45 formas de fuente (goto con una y con dos etiquetas, else,
ternario, switch, variable intermedia, `for(;;) return`, deletreos del 1 -- `2-1`, `!0`, `sizeof`,
enum, `static const` --, seis tipos de retorno), **27 builds de mwccarm, 13 niveles de optimizacion
y 25 combinaciones de flags**. Todas identicas: el pliegue es universal en este compilador, asi que
hay que esquivarlo desde la fuente. Lo resolvio el corpus: seis funciones ya casadas tienen la
disposicion de la ROM y **ninguna es un select (0,1) puro**.

## ★★ Cadena de asignaciones de N bytes: el store mas interno se lleva el `int`, los demas el byte

`func_ov254_020d5884`. La ROM guarda cuatro bytes a cero y materializa DOS ceros: uno crudo
(`mov r2, lr`, reutilizando el valor inicial del contador) para el primer store, y uno enmascarado
(`and r1, r2, #0xff`) para los otros tres. Con cuatro sentencias `= 0` sueltas mwcc funde todo en
un unico cero -- una instruccion menos que la ROM.

**Una sola cadena de cuatro lo reproduce**, y de paso fija el orden de emision:

```c
    e[0xa8] = e[0xaa] = e[0xac] = e[0xa9] = 0;   /* emite a9, ac, aa, a8 */
```

mwcc la evalua de derecha a izquierda: el store mas interno (a9) recibe el `0` entero, y el VALOR
de la cadena es `unsigned char`, de donde sale el `and #0xff` que alimenta a los otros tres.

## ★ `switch` con `default` fuerza la forma con ramas en un select de DOS brazos

Ya estaba catalogado para selects de tres brazos ("si la ROM ramifica a brazos fuera de linea, tira
de switch"); vale igual con dos. `func_ov008_0204d640`: la ROM emite
`bne else ; mov ; strb ; b end ; else: mov ; strb` y mwcc predica el if/else de dos stores con
brazos constantes (`moveq/strbeq/movne/strbne`), exactamente 8 bytes menos. Intercambiar los brazos
del if/else NO lo mueve; el `switch` con `default` si.

## ★★ El test del bucle va sobre el LOOKAHEAD, no a traves de la asignacion

`func_ov008_0205ea18`. `while ((cur = node) != 0)` obliga a mwcc a conservar una segunda copia del
valor (un `mov` y 4 bytes de mas). La forma de la ROM es:

```c
    do { node = Next(list, cur); ...; cur = node; } while (node != 0);
```

## ★★ En THUMB, si las BANDERAS estan vivas la constante viene del POOL

`func_ov022_02083178`: la ROM materializa un `0` con `ldr r1,[pc]` + palabra de pool en lugar de
`movs r1,#0`, porque el `adds r4, r0, #0` que recoge el resultado de la llamada deja las banderas
que consume el `bmi` dos instrucciones despues -- y `movs` las machacaria. mwcc hace exactamente lo
mismo. **Una palabra de pool para un inmediato codificable NO es, por si sola, un empate**; mira si
hay una rama condicional despues que dependa de banderas anteriores.
(Confirmado tambien en `func_ov022_02092384`, ya casada.)

## ★ Modelar una tabla como STRUCT de arrays paralelos en vez de `int` + offsets

`func_ov022_02089fe8`. Con `tbl += 0x14` y offsets crudos, mwcc pliega el 0x14 dentro de cada
inmediato, mantiene vivo el puntero PRE-incremento a traves de una llamada y reconstruye el `+0x14`
despues: un registro callee-saved de mas. Con

```c
typedef struct { unsigned short values[4]; unsigned char b08[4]; unsigned char b0c[4];
                 char pad10[0x9c-0x10]; unsigned short seq[4]; } Tabla;
```

sale el direccionamiento de la ROM entero: una base, `t + idx` compartido por los dos stores de
byte y el par `add rX, t, idx lsl #1` rematerializado alrededor de la llamada.

## ★ La fuente de una copia de struct: CAMPO, no cast

`func_ov119_020cbfc4` (x3). La ROM colorea el puntero ORIGEN en lr y el destino en ip; toda forma
que deletree el origen como CAST de una direccion calculada da lo contrario. Escrito como campo a
traves de un puntero tipado (`self->pNode->transform`) sale el par `ldm lr! / stm ip!`.
**206 funciones ya casadas llevan ese par exacto** -- el corpus lo dijo antes que el compilador.

---

## LICM eager-vs-lazy placement past a loop guard — `func_ov002_020548ec` +2 siblings (2026-07-24)

Tilemap palette fill: `for(i<hTiles) for(j<wTiles) *p = (*p & 0xfff) | ((value&0xf)<<12)`.
Byte-identical, reloc-free, 152 B, x3: `func_ov002_020548ec`, `func_ov008_02055910`,
`func_ov026_020835fc` — one match = three.

Reconstructed the source to **byte-exact except ONE instruction position** (verify_idx: byte diff
@0x8). Size, relocs, structure and **every register** match. The lone difference:

- ROM computes the loop-invariant `value<<0x1c` in the ENTRY block, *before* the `hTiles>0`
  guard (`lsl ip,r2,#0x1c` at 0x020548f4, then `pople` at 0x02054900).
- mwcc 3.0/139 hoists it to the loop PREHEADER, *after* the guard (lazy/latest LICM placement).

The reason the ROM does it: `value(r2)` is reused for the mask (`ldr r2,[pc,#0xfff-pool]`), so
consuming `value` before the guard frees r2 and avoids keeping `value` live across `pople`.

**The trap (why it can't be spelled):** the register allocation that matches the ROM
(`i→r0, ins→ip`) arises *only* from the hoisted-temp form — and a hoisted temp uses lazy
placement (preheader). Writing `ins` as a named entry local *does* put the `lsl` before the guard,
but then the allocator gives `ins→r0` and pushes `i→r2` (23 diffs). The two are mutually
exclusive under this compiler: {ip register} ⇔ {preheader placement}. `register asm("ip")`,
`volatile`, comma-in-guard, comma-seeded zero, for-init, early-return guard, 2-use GCM bait,
all 6 decl-orders, and prod/8 spellings were tried (~110 compiled experiments).

**All 27 available compiler builds fail identically at 12 bytes off** (build_sweep). This is the
documented "retail likely 3.0 ≥140, unavailable" tie class. Best source kept at
`build/try/48ec/best4.c`. NOT parked, NOT moved — external blocker: exact compiler build absent.

---

## Caller-saved (ip) vs callee-saved for a hot loop-invariant — `func_02014224` (2026-07-24)

`Tilemap_FillIncrementing(u16* p, w, h, stride, int base, int palette)` — fills a rectangle with
sequential tile indices + fixed palette: `*p++ = base++ | ((palette&0xf)<<12)`, row stride `+stride`.
92 B, reloc-free, ARM. Same `value<<0x1c` palette idiom as `func_ov002_020548ec`.

Reconstructed to **8 diffs, all one register-allocation choice**: the loop-invariant
`ins = palette<<0x1c` (used `ins>>16` in the hot inner loop) goes to **ip** in the ROM (caller-saved,
not pushed) while mwcc 3.0/139 puts it in **r4** (callee-saved). The ROM threads the transient
palette load through r4, frees it, and reuses r4 as the persistent zero that re-seeds `j`; mwcc
loads palette into ip, keeps ins in r4, and re-derives the zero in lr. Everything else — size,
structure, i/j registers, store order (`base++` BEFORE `strh`, per Ghidra), guard, the eager
pre-guard placement of the `lsl` — matches byte-exact.

Levers that got it to 8 (all real, keep them): **`int base` not the ushort Ghidra guessed** (loaded
with `ldr`, incremented without truncation, `strh` truncates at the store); **`int j;` declared
BEFORE `int i = 0;`** (flips i→r6, j→r5 to match); **explicit `unsigned short v; v = base|ins>>16;
base++; *q=v;`** store order. Levers that do NOT flip ip↔r4 (tried ~40): decl order of ins, ins
scope (entry/outer/inner), `register` hints on any/all vars, explicit persistent-zero var derived
from i, for/while/do outer, store spelling, base signedness. All 27 builds fail identically (15 off).

**Same tie family as `func_ov002_020548ec`**: the retail compiler (likely 3.0 ≥140) allocates a hot
`value<<0x1c` invariant to the caller-saved scratch reg; ours prefers callee-saved. Best source at
`build/try/4224/best.c`. External blocker: exact compiler build absent.

---

## ★★★ RE-TEST VEIN: the `const`-table crack was never tried on the "scheduler slot" parks (2026-07-24)

The `const` crack above (data_0203d210 sin/cos table) had been applied to a couple of functions and
then forgotten. On 2026-07-24 a sweep re-tested it against every parked file whose note said
"scheduler slot" / "one unexplained slot" / "byte-equivalent" and read data_0203d210 -- it matched
**16 functions in 4 shape families** that had all been parked with thorough-looking checklists:
  Ov212_AcquireTargetAndFace x3, Ov212_SteerTowardAnchor x3, Ov214_AimAndFacePoint x5,
  Ov214_EnterAdvancePhase x5 (ov212/214-217/264/266/267).
Every one of those notes ran the pre-park checklist (--thumb, arity, return type, diff-read-back)
and ruled out 6+ source spellings -- but NONE tried `const` on the table, because the diff reads as
a scheduler choice, not an aliasing fact. The tell is the same every time: **the ROM issues both
table loads before the pointer stores; mwcc sinks one load past a store.** When a global-TABLE
reader that also stores through a pointer is permuted only in load/store order, `const` is the first
thing to try, and it is worth sweeping the whole parked set for it (the automated check:
add `const` to every `extern <type> data_...[]`, run verify_idx, keep the matches).

General lesson, third time it has paid off: a park note is one attempt at one moment. When a NEW
crack lands, re-test it against the existing parks by SYMPTOM before assuming they are ties. The
`data_0203d210` vein went from 0 to 16 this way. (Exhausted now: a full sweep of the remaining
36 table-reading parks yields no further const-only matches; those carry other issues.)

---

## ★★★ Materialised `ldrb ; lsl #0x1f ; lsrs #0x1f` bit0 test that mwcc keeps folding to `tst` (2026-07-24)

Symptom: the ROM extracts bit 0 of a byte with a REAL shift pair that also sets flags --
`ldrb r0,[rN,#k] ; lsl r0,r0,#0x1f ; lsrs r0,r0,#0x1f` -- and then predicates off it
(`ldrne ; cmpne ; beq`). Every natural spelling of "bit 0" that mwcc can prove is only tested
(`x & 1`, `(unsigned)(x<<31)>>31`, a `!= 0` guard) folds to a single `tst rX,#1`, so the function
is one instruction short and the following register stream shifts.

The exact form that reproduces it:
```c
unsigned int uVar1 = (unsigned int)((int)*(unsigned char *)(p + k) << 0x1f) >> 0x1f;
if (uVar1 != 0 && ...) ...
```
Three independent casts, each load-bearing:
  - `*(unsigned char *)` keeps the load `ldrb` (a `signed char` gives `ldrsb`);
  - the `(int)` before `<< 0x1f` stops mwcc folding the extract to `tst` -- a signed intermediate
    makes it keep the shift pair and materialise the value;
  - the `(unsigned int)` cast applied to the shifted result, before the final `>> 0x1f`, makes that
    shift LOGICAL (`lsrs`) instead of the arithmetic `asrs` a plain `int >> 31` would give.
Drop any one cast and you get `tst` (fold), or `ldrsb` (signed load), or `asrs` (arith shift).
Closed the last diff of `func_ov022_020a46f8` (Ov022_ReleaseNodeSlotResources).

Same function carried three other levers worth remembering together, all in its commit:
`((int*)(*(int*)(node+4)))[i]` (indexed load, no strength-reduced offset) · a u64 flag read through
`(char*)obj + K` (keeps both words on the base, no split) · the short-circuit `bit != 0 && (h =
e[8]) != 0` (flags-predicated, no boolean spilled to a callee-saved reg) · `&= ~2` for `bic`.

## ★★★ CRACK DE LA CLASE "stride bajo": contadores en ORDEN DE ANIDAMIENTO, acumulador DESPUES (2026-07-24)

`func_ov008_02060a0c` (220B, commit 9a80aae7c) — **primera caida de la clase de 18 funciones**
donde el registro del stride reducido queda POR DEBAJO del contador interior (ambos callee-saved).
La palanca es SOLO el orden del bloque de declaraciones:

```c
int p; int r; int c;   /* contadores de bucle, orden de anidamiento (exterior->interior) */
int n;                 /* acumulador lineal DESPUES, aunque se asigna primero (n=0) */
int ctx; int id;       /* locales post-bucle, al final */
```

Cualquier otro orden rota el coloreado (ip/lr/r4/r5) y deja >=16 bytes. Encontrado por barrido
exhaustivo 6!=720 del bloque. **RETRACTADO**: la conclusion "coloreado inalcanzable / clase
bloqueada por compilador" de state.md era un artefacto de permutar el subconjunto equivocado
(las ~90k variantes fijaban prefijos que excluian sl estructuralmente).

Transferencia a `020573e4` (en curso): con bloques contadores-primero el conjunto de pares
(stride,k2) se EXPANDE de 12 pares uniformes a 16 — aparece sl como stride y (r7,sb) x512
(temp=r7 = posicion de la ROM). La pelea restante es k2 vs gw por el 5o color (sl vs fp).

## ★★ HERRAMIENTA NUEVA: catalogo COMPLETO de pragmas del optimizador extraido del exe (2026-07-24)

`mwccarm.exe` contiene ~84 nombres `opt_*` INTERNOS no documentados (strings del binario):
`opt_markcounterloops`, `opt_markvariablecounterloops`, `opt_transformcounterloops`,
`opt_returnloopdepthinstatementvalue`, `opt_scalarizeliveranges`, `opt_marknonregtemps`,
`opt_docrossconversionofinductionreference`, `opt_defuse_mem_limit`, `opt_usedef_mem_limit`,
`opt_useexpressioncostswhenlinearizingassignments`, `opt_reverseloops`, `opt_rotateloops`, etc.
Extraccion: `re.findall(rb'[ -~]{4,}')` + filtro `\bopt_[a-z_0-9]+\b`. Se aceptan como
`#pragma <nombre> on|off` (los `*_limit` son numericos). Barrido guardado en
`build/try/73e4/hidden.py`. Los `mem_limit` importan: un limite bajo TRUNCA el analisis
def-use y cambia la asignacion de registros -- mecanismo real por el que la maquina/config
de retail pudo colorear distinto que nuestro default.

## ★★★ LA ESCALERA DE DEMOTACION POR DEAD STORES — el crack de `020573e4` (2026-07-24, MATCH x7)

Con `#pragma opt_dead_assignments off`, una secuencia de dead stores al principio de la funcion
(`item = 0; j2 = 0; k2 = 0;`) NO emite ni un byte pero sus webs entran en el orden del allocator:
**cuanto mas tarde aparece el store, mas se demota la variable** (colorea mas tarde -> registro
callee-saved mas alto). Permite fabricar CUALQUIER orden relativo de coloreo entre locales sin
tocar el codigo emitido — es la palanca que faltaba para los 3-ciclos de registros "inalcanzables".

Receta completa del match (fuente: `src/overlays/ov000/calls/func_ov000_020573e4.c`):
1. `k2 = entry->items[j].id;` HOISTED antes de la guarda de fase 1 (ademas de demotar el web de
   fase 2 de k2, ES la estructura del retail: la ROM carga el id antes de sus cmps).
2. Dead stores `item = 0; j2 = 0; k2 = 0;` + `opt_dead_assignments off` -> off=r7, item=r8,
   j2=sb, k2=sl (la afinidad same-variable de mwcc une los dos webs de k2 en sl).
3. Cadena `for (off = j2 = 0; ...)` con j2 asignada primero -> `mov sb,#0; mov r7,sb`.
4. `item` declarada despues de `j2`; `off` explicito (int, bytes) con guarda
   `*(int*)((char*)entry + off + 0x18)`.
5. `#pragma opt_loop_invariants off` (fase 1, crack anterior).

Historia del residuo: ~200k variantes; el "muro k2 nunca sl" (90k+40k+29k compilaciones) era un
artefacto del basin fa — fd.c (hoist + item tras j2) ya alcanzaba k2=sl y nadie lo habia medido.
**Leccion de metodo: cuando un residuo de coloreo resiste todo, mide el REGISTRO OBJETIVO en TODOS
los candidatos historicos antes de declarar el muro** (fd estaba anotado "(26, k2=sl)" en un
comentario de hace dias).

## Load order: a volatile read through a LOCAL POINTER (2026-07-25)

**Symptom.** Two adjacent loads come out in the wrong order and no spelling of the
expression moves them: not operand order, not temps, not statement order, not
`register`, not declaration order. `posdiff` shows `mnemonic 0 / operand 2` with the
two `ldr`s transposed and everything else exact.

**Why.** mwcc will not reorder two `volatile` accesses against each other, but it
reorders a volatile access against a plain one freely. So if only one of the two loads
is volatile, source order buys you nothing.

**Fix.** Make BOTH volatile -- but pick the cheap spelling. Measured on
`func_ov008_02068e68`:

| spelling | cost |
|---|---|
| qualify the field in the struct | **+24 B** -- the same field is read all over the function |
| inline cast `*(volatile int *)&x` | **+24 B** -- re-materialises the address |
| ★ **local pointer** | **0 B** -- reuses the base register that is already live |

```c
{   volatile int *vt = &ctx->aPageTarget[i].y;
    mv.y = (*vt - c1) / 4; }          /* c1 was read volatile just above */
```

That alone took `operand 2 -> 0` and `full 12 -> 2`.

**The choice is measured, not stylistic.** On the *same function*, the cast form is the
right one for `nPageIndex` (`int pi = *(volatile int *)&ctx->nPageIndex;`), where
qualifying the field costs +12 B because the `switch` above reads it too. Rule of
thumb: **cast when the object is read once or twice more, local pointer when it is read
throughout.** That `pi` cast is also what stopped mwcc slotting the nPageIndex load
BETWEEN two adjacent field reads -- which had made the CORRECT source order score worse
than the wrong one for an entire session.

**Corollary that corrects the older `volatile int cur[2]` advice.** A fully volatile
local cannot reproduce code where the ROM stores a field AFTER re-reading its sibling:
a volatile store may not be sunk past a volatile read, so source order is forced and the
ROM's schedule is unreachable. Use a **plain struct read through volatile casts** -- the
store stays freely schedulable and only the re-read is pinned. Fully plain is the other
failure: mwcc scalar-replaces `int cur[2]` and the function comes out 40 bytes short.

## Declaration order colours the SAVED registers -- not the scratch ones

*(2026-07-25, learned from the CodeWarrior matching curriculum at decomp-academy.dev,
then confirmed against our own measurements.)*

"Declaration order colours the registers" is a real and load-bearing rule in this
project -- it closed `func_ov301_020cbfc4` and `func_ov008_02069954`. But the
curriculum states it precisely, and the precision matters: the lesson is
**"Declaration Order Is Register Order: Coloring Saved Regs by Hand"**. It is about
the **callee-saved** set (r4-r8, sb, sl, fp), not about r0-r3.

That explains a large inert sweep here. `func_ov008_02068e68` has a residue that is a
3-cycle in **r1/r2/r3 -- caller-saved scratch** -- and a full permutation of the
declaration order (the 4 leading scalars x the 5 trailing ones = 2,880 orders, run on
two different candidate branches, 5,760 compiles) moved **nothing**. That is not bad
luck; it is the wrong knob for that residue.

**So: read the residue's registers before choosing the knob.**
- residue in r4-r8/sb/sl/fp -> declaration order, and the local's live range.
- residue in r0-r3 -> the shape of the EXPRESSION DAG: operand order, hoisting a
  subexpression into a temp, parenthesisation, and which value each statement makes
  live first. Declaration order will not touch it.

(For the record, on that function the sub-expression axis was then swept too --
`(&a[i])->x` vs `a[i].x`, `pi == i` / `i - pi == 0` / `!(i != pi)`, `cx + 0x8000` vs
`0x8000 + cx` vs `+=`, `cx` vs `cx + 0` -- 72 combinations per branch, all size-exact,
all inert. The lesson about which knob to reach for still stands.)

## Two symmetric reads of the same object want DIFFERENT spellings (2026-07-25)

**Symptom.** A candidate is size-exact and one adjacent pair of instructions is
transposed. You change a knob, the transposition MOVES to a different pair instead of
disappearing, and the score never improves. It reads exactly like an unbreakable
scheduling tie.

**Cause.** Two structurally symmetric reads -- `mv.x = (target[i].x - cur.x) / 4;` and
`mv.y = (target[i].y - cur.y) / 4;` -- were given the SAME spelling, because writing
the two halves of a symmetric expression the same way is the natural thing to do.
They are two independent scheduling knobs, and tying them together makes the search
space look one-dimensional when it is two-dimensional. Measured on
`func_ov008_02068e68`:

| aPageTarget[i].x | aPageTarget[i].y | result |
|---|---|---|
| `volatile int *vx` local | `volatile int *vt` local | +0x0FC `str mv.x` / +0x100 `ldr cur.y` swap (2,0,2) |
| plain | plain | +0x0E0 `ldr tgt.x` / +0x0E4 `ldr cur.x` swap (0,2,2) |
| `volatile int *vx` local | **plain** | **byte-exact** |

**Mechanism.** A read through a `volatile T *` LOCAL pins that load ahead of the
following stack re-read; a plain read lets mwcc schedule it after. So the pointer
local is not a stylistic wrapper -- it is a per-read ordering primitive.

**Rule.** When the residue MOVES between two pairs instead of shrinking, stop varying
global knobs and ask which two source constructs you have been spelling identically
out of symmetry. Cross them independently. This function had survived ~15 sweeps
(14,400 statement orders, 5,760 declaration orders, 27 compiler builds, 29 pragmas,
every -O and -proc value) purely because every one of them gave the two reads the
same spelling.

**Corollary for the corpus search.** The positive form to grep for was
`str rX,[sp,#N]` followed by an independent `ldr rY,[sp,#M]`, and it DOES occur in
matched C -- `func_ov294_020d2008 +0x2CC` is the closest analogue. Reading that
function is what showed the shape was reachable and the tie was not real.

**Retired hypotheses** (all compiled and disproven on this function, do not re-run):
- volatile ORDERING between the store and the load: mwcc does not honour it here --
  making the `mv.x` store volatile (cast or pointer local) scores 18/2/20, worse;
- ALIASING via `Ov008Pair *pc = &cur;`: mwcc resolves the pointer exactly back to
  `cur`, does not force the re-read, and costs 4 extra instructions (808 vs 792 B);
- merely taking `&cur` so its address escapes: completely inert;
- the aggregate model (cur+mv+pos in one struct whose address escapes): 772 B, no
  re-reads at all;
- cx/cy declaration order: swaps which `ldr` is EMITTED first, leaves the register
  colouring untouched -- consistent with "declaration order colours the SAVED
  registers, not the scratch ones" above.

## `const` on a pointer local is a FRAME-LAYOUT knob (2026-07-25)

**Symptom.** Size, instruction stream and registers are all exact, and the only residue
is that the stack-slot NUMBERS are a rotation of the ROM's. On
`func_ov000_02051648`: ours `ctx=8, off=0xc, by=0x18` against the ROM's
`off=8, by=0xc, ctx=0x18`, with `bx=0x10` and `slot=0x14` already right.

**Cause.** mwcc lays the local area out in GROUPS, and an unqualified pointer local
goes BELOW the ints while a `const`-qualified one goes above them:

```c
Ov000LoadPageContext *ctx = data_ov000_0205ac24;         /* -> sp+8, below the ints */
Ov000LoadPageContext *const ctx = data_ov000_0205ac24;   /* -> sp+0x18, above them  */
```

Within the int group the slots then descend by declaration order, and the compiler's
own induction-variable temp takes the bottom slot.

**Why it matters more than it looks.** Declaration order cannot reach the other
layout: **121 declaration positions were compiled and every single one left `ctx` at
slot 8**, as did an `int`-typed copy, a `u8 *` copy, `register`, a reassigned
parameter, and an explicit byte-offset variable. If the residue is a stack-slot
rotation and reordering declarations is inert, reach for the qualifier, not for more
permutations.

## An `else if` that cannot fall through blocks if-conversion -- and that is a REGISTER-PRESSURE knob

Same function, and the more surprising of the two. These are not equivalent to mwcc:

```c
if (k == 3) { ... } else if (k == 4) { ... }        /* mwcc if-converts arm 1  */
if (k != 3) { if (k == 4) { ... } } else { ... }    /* mwcc emits real branches */
```

With real branches the value assigned in both arms is live across the merge and gets a
CALLEE-SAVED register; predicated, it does not. That one extra long-lived value is
what evicts another local from a register onto the frame -- so the wrong branch shape
left the function **28 bytes short**, and the missing instructions were the spill and
reloads of a variable in a completely different part of the body.

**The lesson is the distance.** A size deficit of several instructions is normally read
as "a construct is missing". Here nothing was missing: one `if` was written in the
shape that lets the compiler predicate it. When instructions are missing and they are
spill traffic, look for what SHOULD have been competing for a register, not for
missing work.

## An unset argument register means the callee is VARIADIC

`func_020262a0(buf, size, fmt, value)` is called seven times in `func_ov000_02051648`.
Five call sites set r3; two do not, and the ROM passes whatever r3 happened to hold.
No prototype with four fixed parameters can produce that. The callee is
`void f(u16 *buf, int size, const u16 *fmt, ...)` and those two sites pass three
arguments.

Ghidra renders the missing argument as a live-looking local (`(uint)pbVar10`, where
`pbVar10` was a pointer two statements earlier), so it reads as ordinary phi confusion
rather than as evidence. **A `bl` whose argument register is never written on that path
is the tell** -- check for it before assuming the decompiler dropped something.

## `#pragma opt_strength_reduction off` -- and the flags/infrastructure blocker that wasn't

*(2026-07-25, on `func_ov000_0205474c`.)*

**Symptom.** The candidate is a few instructions SHORT, and the missing ones are all
recomputation: the ROM recomputes an affine address expression every iteration and
reloads loop-invariant values from the frame, where mwcc folds them into one induction
variable and keeps them in registers. On this function that was worth exactly 8 bytes.

**What it looks like in the ROM.** No strength reduction anywhere in the loop:

    +0x0DC  ldr r0, [sp, #4]          stride, reloaded every iteration
    +0x0E0  add r1, r5, r4            sy + i, recomputed
    +0x0EC  add r1, r7, r8, lsl #5    dx + dy * 0x20, recomputed
    +0x110  add r8, r8, #1            dy++

mwcc at -O4,p instead emits `add sb, sb, #0x20` on a merged induction variable.

**The wrong conclusion I reached first, and why it was wrong.** The reduction is absent
at -O1/-O2/-O2,p/-O3 and present at -O3,p/-O4,p, so I concluded the unit was built at a
lower level and filed it as **blocked on infrastructure**, because `tools/configure.py`
holds one global CFLAGS with -O4,p hardcoded and `file_compilers.json` overrides only
the compiler BUILD.

That was wrong. **mwcc takes the optimisation settings as in-source pragmas**, so a
per-file optimisation difference never needed build support:

```c
#pragma opt_strength_reduction off   /* the targeted fix -- stream matched at once */
#pragma optimization_level 2         /* the blunt one; reproduces the -O sweep exactly */
```

With `opt_strength_reduction off` alone, at the tree's own optimisation level, the
function went from 8 bytes short to **mnemonic 0 / operand 0** -- the whole instruction
stream, every immediate, offset and shift correct.

**Rule.** When the residue is "mwcc optimised something the ROM did not", the question
is never the build system. Work down the legal pragma list first -- `peephole`,
`opt_dead_code`, `opt_common_subs`, `opt_lifetimes`, `opt_propagation`,
`opt_dead_assignments`, `opt_strength_reduction`, `opt_loop_invariants`,
`global_optimizer`, `opt_unroll_loops`, `optimization_level`, `optimize_for_size` --
because each one is a one-line experiment and none of them touches the 306 gate.
Ten pragmas x three levels is 30 compiles and it found this in one pass.

**Companion finding.** The loop also needed the explicit guard + do-while form with the
counter initialised INSIDE each branch:

```c
i = 0;
if (h > 0) { do { ...; i++; dy++; } while (i < h); }
```

A plain `for (i = 0; i < h; i++, dy++)` is 8 bytes short at the same level: mwcc emits
one top-tested loop where the ROM emits a zero-trip guard per branch.

## Grep the tree for the callee's DEFINITION, not just its arity

The standing rule is "before writing any call, grep the tree for that callee's real
arity". Widen it: **grep for the callee's matched DEFINITION**, because the return type
is there too and it is part of the caller's register allocation.

On `func_ov000_0205474c` I declared `extern u16 *func_ov000_02054714(int handle,
int *pLayer);` from the disassembly. The tree already contained
`src/overlays/ov000/calls/func_ov000_02054714.c`, matched, with the real signature
`int func_ov000_02054714(int id, int *out)` and a plate comment explaining it. One
`grep -rl` would have given the exact prototype and the semantics for free.

Two cheap commands, and run BOTH:

```bash
grep -rh "func_XXXX(" src/ --include=*.c | grep -v extern | sort -u   # call sites
grep -rl "func_XXXX" src/ --include=*.c                               # its own definition
```

The same search on that function turned up a SIBLING of the one being matched --
`func_ov008_02050bb0` / `func_ov025_020849d8`, the ov008/ov025 version of the same
tile-clear helper -- carrying three documented cracks in its header, one of them a
register-allocation fix (the destination address has to be a NAMED LOCAL when the
address expression contains a call result, or mwcc materialises the literal 0 into r0
first and has to copy the call's result out of the way). Sibling overlays implement the
same helpers; their headers are the closest thing this project has to documentation.

## OPEN RESIDUE: the ov000 tile-blit pair, instruction-exact with a 4-cycle colouring

*(2026-07-25. Recorded so the next session does not repeat nine iterations of it.)*

`func_ov000_0205474c` (380 B) and its twin `func_ov000_020530cc` (384 B) are both
**mnemonic 0 / operand 0** -- every instruction, immediate, memory offset and shift is
correct -- with an identical residue in the callee-saved registers:

    value        ROM   ours
    bCopy/i      r4    sb
    blob, sy     r5    r6
    dst          r6    r4
    h            sb    r5

`r7` (dx), `r8` (dy), `fp` (sx) and `sl` (req) already agree in both.

**The useful structural observation**: the four that permute are exactly the values
assigned in the PROLOGUE; every value assigned during the clipping code allocates
correctly. ROM's four are ascending in definition order (bCopy, blob, dst, h ->
r4, r5, r6, sb); ours are not. But reordering the prologue does NOT fix it -- putting
`blob` before `dst` scores 35, and every order that keeps `dst` first scores 29.

Three cracks were needed to reach instruction-exactness, and all three are real:
  1. `#pragma opt_strength_reduction off` -- the ROM does no strength reduction in
     either loop; -O4,p folds dx/dy into one induction variable, worth 8 bytes.
  2. The explicit guard + do-while form with the counter initialised inside each
     branch; a plain `for` is 8 bytes short.
  3. The function is NOT void -- both callers do `return func(param_1, 0/1);`. The
     return value is the pre-truncation `mask | (1 << layer)`; spell it as a local,
     because `return x |= v;` costs 8 bytes re-truncating.

**Do not re-run these** (all compiled, all size-exact, all still full=29 or worse):
4000 topological prologue statement orders; ~2500 declaration permutations across
three bases; `register` in every combination up to three; `const` on both parameters
and on blob; declaration-with-initialiser for dst/blob/w/h; the pragma space (noting
`register_coloring`/`no_register_coloring` are ILLEGAL and silently ignored -- see
tools.md); types of h/w/sx/sy/bCopy/dx/dy; four return-value spellings; the first
parameter as `int` with a cast; three struct shapes including collapsing the source
pointer to `u16 **`; own-arity 3 and 4; PARAMETER REUSE (bCopy as the copy counter
plus a dead signed local as the clear counter -- this reproduces the ROM's coalescing
exactly and is probably the original's shape, but the score does not move); branch
orientation; and all 27 mwccarm builds, every 2.0/3.0 one reporting the SAME 38-byte
delta, which is what a pure permutation looks like.

Corpus: no matched function calls both MIi_CpuCopy16 and MIi_CpuClear16, so there is
no solved sibling. 38 matched functions share the ROM's allocation signature
(`mov r4,<param>` + `mov r6,r0` after an early bl) but none is structurally close.

**RETRACTED, same day it was written.** This entry used to say the colouring was
INVARIANT to source shape -- that all four prologue statement orders produced an
identical assignment, so the ROM's allocation was unreachable from C through
"statement order, declaration order, qualifiers, types, arity, return form, struct
shape, pragmas or compiler build". The measurement behind it was real but the
conclusion was not: it only ever moved STATEMENTS. Moving a DECLARATION into an inner
block moves the assignment on the first try.

**The actual rule, and it is a general one -- mwccarm hands out callee-saved
registers by DECLARATION RANK:**

- locals that need a callee-saved register get r4, r5, r6, r7, r8 ... in order of
  DECLARATION, so declaration order is the rank;
- a local declared in an INNER BLOCK ranks after every outer local, which makes
  `{ ... }` a precise tool for pushing one value down the list;
- an unmodified PARAMETER ranks after all locals. Copying it into a local does NOT
  raise it -- the copy coalesces straight back into the parameter and inherits its
  rank;
- but a parameter that shares a register with a local (one coalesced web, e.g. a flag
  that dies exactly where a loop counter is born) is ranked by the LOCAL. Declaring
  that local first pulls the whole web to r4. That is what finally moved `bCopy` on
  func_ov000_0205474c after every other axis had failed.

So when a candidate is instruction-exact and only the registers are wrong, the
question to ask is not "which pragma" or "which compiler build" -- it is **"what is
the declaration rank of each value, and which block is it declared in?"**

Two traps when exploiting it:

1. Promoting a loop counter to the first declaration can make mwcc head-merge an
   identical initialiser that opens both arms of an `if`/`else` and hoist it above the
   branch. Sinking one arm's copy inside its own guard blocks the merge. Giving each
   arm its OWN counter also blocks it, but that drops register pressure enough that
   mwcc stops spilling and the whole frame can collapse -- watch the size, not just
   the colouring.
2. Reordering two assignments to reorder their ranks is not free when one of them is
   a call: hoisting the other above the call forces it to survive the call and
   rewrites the stream.

Best forms: `build/try/f838/t4c_BEST.c` and `build/try/f838/t5_twin_BEST.c`.
Neither is parked. One source-shape discovery closes both.


## SOLVED: name the repeated `base + constant` addresses -- IR size is an allocator knob

*(2026-07-26, closed `func_ov000_02058e88` after ~4000 compiled experiments.)*

**Symptom.** Everything byte-exact except a short run where the ROM computes a value into a
volatile register and stores it immediately, while mwcc computes it into `ip` and stores it one
slot later. Reads exactly like a scheduling tie. It is not.

**Fix.** The function repeated three address expressions -- `(char *)base + 0x10c` five times,
`(char *)base + 0x158` four times, `cursor + 0x4800` four times. Giving each one a named local
makes it match. **mwcc rematerialises `base + constant` at every use, so the emitted code is
byte-identical either way**; what changes is the size of the expression tree, and that is enough
to move the register allocator off the behaviour that defers the store.
All three are required -- any one or two alone still leaves the full residue.

**How it was found, which is the reusable part.** A leave-one-out sweep over the whole function:
delete each statement in turn and watch the RESIDUE REGION, not the residue.

- deleting ANY statement *before* the affected block restored the ROM's schedule;
- deleting any statement *after* it changed nothing;
- a minimal standalone reproduction of the block did not show the effect at all.

That pattern -- "every prefix statement matters, no suffix statement does, and the block in
isolation is fine" -- says the residue is a **cumulative allocator threshold driven by the size
of everything preceding it**. Once you know that, the fix is to shrink the prefix's IR without
changing its code, and named locals for repeated address expressions are the cheapest way to do
exactly that.

**What this explains about the earlier dead ends.** Before the leave-one-out, the trigger looked
like the 20-byte `capacity` struct block copy, because removing it also restored the schedule --
but so does removing any other prefix statement. Everything local to the block was inert, and it
had to be: all 720 permutations of its six assignments, all 720 of the neighbouring block's, 256
call-result hoisting combinations, every capacity spelling and struct layout, declaration orders,
`register`/`const`, scopes, basic-block wrappers, restrict, 22 pragmas at file scope and
mid-function, the `-O`/`-opt`/`-ipa`/`-inline`/`-proc` flag space, and all 27 mwccarm builds.

**Rule: when a residue survives every transformation of the code around it, stop varying the
residue and bisect the function for the construct that OWNS it.** The owner routinely has no
textual relationship to the diff -- and "repeated `base + constant` should be a named local" is
better C anyway, so this is worth trying early on any function that repeats an address.


## A struct BLOCK COPY into a second stack object perturbs allocation far away

*(2026-07-26, isolated on `func_ov000_02058e88`, still open.)*

Symptom: everything matches except a short run where the ROM computes a value into a
volatile register and stores it immediately, while we compute it into `ip` and store it
one slot later. It reads exactly like a scheduling tie and it is not.

Diagnosis, and this is the reusable part: **bisect the function statement by statement
and watch the residue region, not the residue**. Deleting or replacing statements far
from the diff is legitimate diagnosis even when the replacement is semantically wrong --
you are asking which construct owns the codegen, not producing a candidate.

On `02058e88` the owner turned out to be a 20-byte `struct` assignment from a const
global into the higher of the two stack objects:

- replace it with an uninitialised `int pad[5]` whose address still escapes to the same
  call (same frame, same two objects, same call) -> mwcc emits the ROM stream exactly;
- fill the same object with five explicit element stores -> ROM stream again;
- do the block copy -> the later store is deferred and `ip` is spent.

So the block copy's temporaries, not aliasing and not the scheduler, change the
allocator's decisions ~60 instructions later. `#pragma scheduling off` and
`#pragma peephole off` leave the output BIT-IDENTICAL, which is the clean proof that the
position is chosen during instruction selection.

Things that do NOT dodge it (all compiled): every spelling of the copy (initialiser,
assignment, through a pointer, cast destination, volatile source, non-const source,
literal initialiser list, file-scope static table), every struct layout of the same
width, merging the two stack objects into one, every scope arrangement, `restrict`, and
`memcpy` (this build does not inline it -- it emits a real `bl`).

**When you meet a residue that survives permutation, hoisting, return types, pragmas and
all 27 builds, stop varying the residue and go bisect for its owner.** The owner is
routinely a construct with no textual relationship to the diff.

## Como reparte mwcc los registros callee-saved (medido, 2026-07-26)

Salio persiguiendo la transposicion r4<->r5 de `func_ov011_0205b814`, y es reutilizable
cada vez que el residuo sea "los registros correctos, mal repartidos".

**La regla base**: los LOCALES se llevan los callee-saved bajos por orden, y un parametro
que hay que preservar se lleva **el siguiente hueco por encima**. Medido con una funcion
minima (`build/try/ov011/repro/`), variando numero de parametros x numero de locales, y
mirando a que registro va el `mov rX, r0` del prologo:

```
        locales:  0    1    2    3    4
  1 parametro:   r4   r5   r6   r7   r8
  2 parametros:  r4   r5   r6   r7   r4
  3 parametros:  r4   r5   r6   r4   r4
  4 parametros:  r4   r5   r4   r4   r4
  5 parametros:  r4   r4   r4   r4   r4
```

O sea: **cuando la presion sube, el parametro deja de subir y cae a r4**. Un residuo en el
que "nuestro parametro esta en r4 y el de la ROM en r5" casi nunca es ruido: significa que
en la ROM habia **un valor menos compitiendo** en ese punto, o que el valor derivado del
parametro sigue vivo cuando en nuestra version ya ha muerto.

**El disparador exacto, aislado por reproduccion minima** (5 parametros, todos vivos):

| forma | copia del parametro |
|---|---|
| `f(a * K);` (el producto se consume en el acto) | **r4** |
| `int q = a * K; f(q); f(q + b);` (q sigue vivo) | **r5** |
| `int q = a * K; int u = G + q; int v = G2 + q;` (q muere en sus dos usos) | **r4** |
| `f(a);` sin multiplicar | **r5** |

Es decir, no basta con que el producto se use dos veces: tiene que **seguir siendo un valor
vivo**, no consumirse en dos derivados. Y multiplicar el parametro por una constante de la
pool, con los demas parametros vivos, es lo que lo empuja abajo.

**Como usarlo**: si te falta exactamente una permutacion de dos callee-saved, no barras
ordenes de declaracion a ciegas (en `0205b814` eso costo 60.480 compilaciones sin mover
nada). Cuenta cuantos valores compiten en el punto de la copia del parametro y pregunta si
alguno de los tuyos vive de mas o de menos que en la ROM.

⚠⚠ **CORRECCION IMPORTANTE (iteracion siguiente, mismo dia): la rejilla es real pero la
CAUSA que deduje de ella NO se transfiere.** Sobre la funcion de verdad
(`func_ov011_0205b814`) compile la misma fuente con 5, 4 y 3 parametros declarados: **las
tres dan r4**. O sea el numero de parametros no es lo que la empuja abajo ahi; lo es la
presion del cuerpo (quitar cualquiera de las tres llamadas devuelve r5). La rejilla sigue
valiendo como observacion del reparto en un caso limpio, pero **no la uses como diagnostico
sin comprobarla sobre la funcion concreta** -- es exactamente el error que este skill
persigue en otros sitios: medir en un modelo y creerselo en el original.

★ **Y confirmalo contra el corpus antes de creerte nada**: `mov r5, r0` inmediato aparece en
3.395 funciones casadas y `mov r4, r0` en 2.468, con la distribucion por numero de
parametros medible en un barrido. Si tu forma esta en el lado raro de esa tabla, el
problema es tuyo, no del compilador.

**Dato de corpus que si aguanta** (medido sobre el arbol casado, funciones ARM con C real):
de las funciones con **5 o mas parametros**, las 13 que ponen la copia del parametro en r5
**ninguna multiplica el parametro 1**; las dos que si lo multiplican
(`func_ov008_0205f388`, `func_ov025_020918d8`) lo ponen en **r4**. Si tu funcion multiplica
el parametro por una constante de la pool y necesitas r5, no hay todavia ningun precedente
casado en el arbol: es terreno nuevo, no un empate conocido.

---

## 2026-07-27 -- Dos reglas de EVIDENCIA que salieron de `func_ov000_02059b14`

### 1. ★★★ Resuelve el destino de un `ldr rX,[pc,#N]` ANTES de dar la diferencia por posicional

`func_ov000_02059b14` llevaba dos sesiones descrito como "residuo de scheduling de 6
palabras". Una de esas seis palabras era `ldr r2,[pc,#0x60]` (ROM) contra
`ldr r2,[pc,#0x6c]` (nuestro), y estaba dada por supuesta como consecuencia de que la
instruccion cayera en otra posicion. **No lo era: eran dos palabras DISTINTAS de la pool.**

```
ROM:      ldr r0,[pc,#0x9c] @ 0x02059bb0 -> 0x02059bb0+8+0x9c = 0x02059c54 = 0x821
          ldr r2,[pc,#0x60] @ 0x02059be8 -> 0x02059be8+8+0x60 = 0x02059c50 = 0x209
nuestro:  las dos leian 0x02059c54
```

Es decir, la fila resaltada del menu se dibuja con el MISMO estilo que las diez filas de la
lista (0x209), no con el del titulo (0x821). Con la constante mal la funcion seguia midiendo
324 bytes y la pool seguia teniendo dos palabras, asi que **ninguna metrica de tamano, de
relocs ni de histograma podia verlo**; solo resolver la direccion pc-relativa.

**Regla:** en cualquier funcion casi-exacta, si una de las palabras que difieren es un `ldr`
pc-relativo, calcula `addr + 8 + offset` en las DOS versiones y compara la palabra apuntada.
Si apuntan a sitios distintos, no tienes un residuo de codegen: tienes un valor equivocado en
la fuente. Cuesta treinta segundos y aqui invalidaba ~4.000 experimentos previos.

### 2. ★★★ mwccarm ACEPTA UN PRAGMA DESCONOCIDO EN SILENCIO -- un pragma inerte no prueba nada

`#pragma zzz_not_a_pragma on` compila limpio y no cambia ni un byte. Exactamente igual que
`#pragma scheduling off`, `#pragma opt_dead_code off`, `#pragma opt_partial_redundancy off`,
`#pragma opt_cse off` y `#pragma no_register_coloring on`. Por eso el argumento que llevaba
escrito el header de esa funcion -- *"`scheduling off` no cambia la salida, luego la
colocacion se decide en la seleccion de instrucciones y no hay palanca de scheduler"* -- **no
demostraba nada**, y habia cerrado en falso el eje del scheduler.

**Regla:** antes de usar "puse el pragma X y no cambio nada" como evidencia, demuestra que el
pragma esta VIVO (que mueve algo en alguna funcion). En este toolchain los que se han
comprobado vivos son `optimization_level N`, `opt_common_subs off`, `opt_propagation off`,
`opt_strength_reduction off` (cerro `func_ov000_0205474c`) y `optimize_for_size on` segun el
caso. Los demas de la lista de arriba pueden ser simplemente ignorados.

### 3. Mide la DISTANCIA, no solo el score

Para un residuo que es una permutacion, un contador de palabras que difieren se queda clavado
(aqui: 6, en las ~150 variantes de la sesion) mientras la estructura si se mueve. Una sonda
que mide la magnitud concreta -- en este caso la distancia entre las dos mitades de un offset
inmediato partido (`add rA,rB,#lo` / `add rC,rA,#hi`) -- distingue variantes que el score
declara identicas, y fue la que localizo el efecto:

```
optimization_level 0 -> distancia 1 (forma del ROM)   88 instrucciones
optimization_level 1 -> distancia 1                   84
optimization_level 2 -> distancia 7                   82
optimization_level 3/4 -> distancia 7                 81   <- el nivel del arbol
```

La separacion entra en -O2 y no la deshace ningun pragma individual. Perturbaciones que si la
mueven (todas cambian el tamano, ninguna es la respuesta, pero son el mapa de a que es
sensible): quitar la llamada anterior -> 4; subir el segundo campo a un local -> 3; **leer la
fila entera por valor (copia de struct) -> 1**, o sea forzar que la base tenga que existir
como valor antes de cualquier carga.

### 4. `volatile` NO puede fijar una computacion de direccion (2026-07-27)

La idea obvia para un residuo de scheduling es poner una barrera: marcar volatile la lectura
del indice para que el `add` de la base no pueda hundirse por debajo. **No funciona, y no es
cuestion de la forma que uses.** En `func_ov000_02059b14` se declararon volatile TODOS los
campos de las dos structs y la salida no cambia ni un byte (81 instrucciones, misma
distancia, mismo score); tampoco con el cast `*(volatile s16 *)&campo` en el punto de uso.

**La razon generaliza:** `volatile` ordena ACCESOS A MEMORIA entre si. `add r5, r0, #0x9000`
es aritmetica pura sin efecto lateral, asi que ninguna barrera lo ancla. **Ninguna
construccion de C fija directamente la posicion de una computacion de direccion**; la unica
palanca es el grafo de dependencias que ve el planificador. No gastes iteraciones en formas de
volatile para mover aritmetica.

### 5. El compilador lleva dentro la lista de sus propias optimizaciones

`mwccarm.exe` contiene ~75 nombres internos `opt_*` en texto plano. Se sacan con:

```python
import re
d = open('tools/mwccarm/3.0_patch4/mwccarm.exe','rb').read()
sorted({m.group().decode() for m in re.finditer(rb'[\x20-\x7e]{5,}', d)
        if m.group().startswith(b'opt_')})
```

Sirve para dos cosas. La primera, **saber que transformaciones existen**: entre ellas esta
`opt_moveinvariantsinaddressexpr`, que nombra exactamente el sintoma de esa funcion. La
segunda, **saber que NO son pragmas**: probados los 24 mas relevantes como
`#pragma <nombre> on|off`, ninguno mueve un byte. Combinado con la regla 2 (los pragmas
desconocidos se aceptan en silencio), la conclusion practica es que el espacio de pragmas
vivos de este toolchain es pequeno y hay que verificarlo, no suponerlo.

---

## 2026-07-27 -- Un par de accessors `static inline` reordena el COLOREADO de registros

*(Sacado de `func_ov011_0205b814`, que llevaba dos sesiones clavado en una transposicion
r4 <-> r5 con el flujo de instrucciones ya exacto.)*

**Sintoma:** tamano, relocs, mnemonicos, inmediatos, offsets y shifts exactos, y el residuo
entero es que dos valores de larga vida tienen los registros callee-saved intercambiados. El
ROM guarda el parametro 1 en r5 y la cadena temporal en r4; nosotros al reves.

**Lo que NO lo mueve** (todo medido en esa funcion): las 5040 permutaciones de declaracion,
60480 compilaciones de orden x spelling, `register`, `const`, copias locales del parametro,
el numero de parametros declarados (3,4,5,6,7), el tipo del indice, la aritmetica de punteros
conmutada, el orden de operandos del multiply, los 13 niveles de optimizacion, los 27 builds
de mwccarm, y los pragmas (ojo: casi todos son no-ops silenciosos, ver la regla 2 de arriba).

**Lo que SI lo mueve:** llegar a los dos objetos por **dos accessors `static inline`
independientes** en vez de por dos cadenas de miembros escritas en linea:

```c
static inline Ov011Pane *Ov011_GetPane(int n)
{ return &data_ov011_0205e960.pScene->aPane[n]; }

static inline const Ov011Tileset *Ov011_GetTileset(int n)
{ return data_ov011_0205e960.pScene->aPane[n].core.pTileset; }
```

El flujo de instrucciones emitido **no cambia** -- el inlining solo re-forma el IR, y eso
basta para que el asignador recorra el grafo de interferencia en otro orden. Score 14 -> 12 y
el parametro pasa a r5, el del ROM. Para esto existe `-inline on,noauto`.

⚠ **El reparto en helpers no es libre.** En esa funcion solo funciona el par
(tileset, pane): un helper solo para el pane da 32, solo para el core da 14, los dos como
core+pane 32, uno para la VRAM se queda 8 bytes corto y anadir un tercero para `wCols` da 32.
Hay que barrer el reparto, no elegirlo a ojo.

**Cuando probarlo:** residuo puramente de coloreado (mismos mnemonicos, mismos inmediatos,
registros permutados) sobre un objeto al que la funcion llega por **dos caminos distintos**
desde la misma raiz. Antes de gastar otro barrido de orden de declaracion, prueba el par de
accessors: son ~6 compilaciones frente a las 5040 del barrido de declaracion.

**Y comprueba el censo de corpus antes de creerte un "no hay precedente".** La nota anterior
de esa funcion decia que no existia ninguna funcion casada que multiplicara el parametro 1 y
lo mantuviera en r5 -- "terreno nuevo". El censo estaba filtrado a funciones de 5+ parametros,
filtro que la propia nota invalidaba ("el numero de parametros no es el driver"). Sin el
filtro salen **siete** precedentes. Un censo que devuelve cero solo es evidencia si el filtro
estaba justificado.

---

## Clamp the signed param FIRST -> anchors it to a callee-saved reg (2026-07-29)

**Symptom:** a function with a loop makes a call inside the loop and re-reads one of its
POINTER params (e.g. the loop stride via `*(param+4)`) after the call. The ROM keeps that param
in a callee-saved reg (`mov fp,r0` as the very first instruction, loop reload `ldr r?,[fp,#4]`),
but mwcc spills it to the stack and reloads it (`ldr r?,[sp]; ldr r?,[r?,#4]`), then hands `fp`
to some loop-invariant instead. Every register in the function cascades from this one choice, so
the diff is huge (80+) even though the C is semantically exact and the instruction MULTISET is
identical. The param's live range is SPLIT (used at entry to derive a pointer, then again in the
loop) and mwcc will not keep a split-range value in a callee-saved reg while a contiguous
invariant is available -- it is a linear-scan tie-break.

**Fix that WORKED (func_ov011_0205b9f4, 82 diffs / -4 B -> byte-exact MATCH):** if the function
starts by clamping a *signed* param (`if (param_4 < 0) param_4 = 0;` -> `movs r,r3; movmi r,#0`),
make that clamp the **FIRST statement**, before reading anything through the pointer param. The
early flag-setting `movs` forces the allocator to commit the pointer param to `fp` at entry
(`mov fp,r0` first) instead of dereferencing it straight away and spilling it. This alone dropped
82 -> 16 diffs and fixed the size. The general principle: **the order of the first few statements
decides which values get `mov rC,rArg` at entry vs get spilled; reorder them to match the ROM's
prologue.**

Two follow-on cracks finished it, both standard:
- **Declaration order of two same-class locals** picks their register numbers: declaring the loop
  counter before the running pointer swapped r4<->r5 (16 -> 10 diffs). (Same lever as
  func_ov301_020cbfc4.)
- **Statement order in the loop tail** drives scheduling: advancing the running pointer BEFORE
  bumping the counters made the pane reload schedule early like the ROM (10 -> MATCH).

⚠ **This RETIRED a whole "build-version tie" family.** The ov011 GFX/title cluster
(b340/d508/b9f4/ac40/be38/b814) was parked across many sessions as "instruction-exact, only
registers differ -> needs retail mwcc 3.0>=140". b9f4 carried that exact residue and matched
byte-exact with **build 139** once the prologue order was fixed. A 27-build sweep saying "no build
differs" is a property of the SOURCE FORM you fed it, NOT of the function -- b9f4's old form would
have swept identically. Re-attack the siblings (d508 is instruction-exact, closest) with prologue
reordering before ever blaming the compiler build again.

## Force a large pointer-offset to split as base+K (not fold to one add) -- 2026-07-30

Symptom: the ROM computes `ptr + BIG` as `add rX, base, #A; add rY, rX, #B` (A+B=BIG) but your C
`ptr + BIG` folds to a *different* split, or `(ptr + A) + B` const-folds to `ptr + BIG` and mwcc
re-splits its own way. Seen on func_ov008_02086da4: ROM wanted `ctx+0x2a8` then `+0x480` for a
CpuClear dst; `ctx + 0x2a8 + 0x480` folded to 0x328+0x400, and a `char *base = ctx+0x2a8` local
fixed the split but got HOISTED into a callee-saved reg (changed the whole allocation).
Fix: express it as a pointer-to-array-of-K-bytes indexed [n]:
  `(u8 (*)[B])(ptr + A) + n`   /* = ptr + A + n*B, emitted as base(ptr+A) + (n*B) */
mwcc treats the element size B as index arithmetic (not a foldable constant add) and computes it
INLINE at the use site (scratch reg, no hoist). `(u8 (*)[0x480])(ctx + 0x2a8) + 1` gave exactly
`add r0,ctx,#0x2a8; add r1,r0,#0x480`. General lever for "the ROM split a constant offset a
specific way and mwcc won't".

## Pointer-typed argument forces frame-address rematerialization (2026-07-30, func_ov008_0205cde8)
Symptom: N consecutive calls that pass the SAME stack buffer (e.g. a sprintf text buffer) as an
argument. The ROM re-materializes the frame-relative address (`add rX, sp, #imm`) fresh before
EACH call; mwcc with an `(int)`-cast argument materializes it once and holds it in a callee-saved
register, coming out N-1 instructions (4*(N-1) bytes) short.
Fix: type the parameter as a POINTER (`void *a6`) and pass the buffer WITHOUT the `(int)` cast.
The pointer-typed argument makes mwcc re-materialize the address at each call site instead of
caching it. On 0205cde8 (save-page renderer, 3 draws sharing a text buffer) this went from 928/936
(2 missing `add r7,sp,#0x20`) to a byte-exact 936 in one edit. The `(int)`-cast form invites CSE of
the address across the calls; the pointer form does not.

## Base-pointer struct zero-init (`add rX,sp,#N; str via rX`) -- iter-73

Symptom: the ROM zeroes a small stack struct through a base register
(`add rX,sp,#N; mov rY,#0; str rY,[rX]; str rY,[rX,#4]`), 1 instruction more than mwcc's
direct `str rY,[sp,#N]; str rY,[sp,#N+4]`. Hit on c7a0 (Ov008Pos2), 301c8 (AxisOffset).

Finding (grepped the matched tree -- 245 matched funcs carry the base-ptr store form):
- For a struct declared+aggregate-initialized INSIDE A BLOCK scope it DOES come from `T v = {0,0};`
  -- proven by func_ov008_02071468 `Vec2 pt = {0, 0};` inside an `if` branch -> `add r2,sp,#8;
  mov r1,#0; str r1,[r2]; str r1,[r2,#4]`, then a field write. (Large structs `= {0}` also use a
  base ptr for bulk zeroing, e.g. func_ov245_020cf870 `Msg m = {0}`.)
- BUT for a small struct at FUNCTION scope used across the whole body (c7a0's pos, 301c8's off),
  `= {0}` / `= {0,0}` makes it WORSE (8-14 diffs), and field-assign gives the direct-sp form.
  The ROM's base-ptr form for a function-scope small struct is NOT reproduced by any zero-init
  spelling tried. Left as a 1-instr tie for those two.

Related: func_0201449c is the same *family* but a SPILL not a zero-init -- the ROM spills a
measured `dims` struct to a stack copy and re-reads it (plus a dead copy), while mwcc holds it in
registers. Register-pressure/DCE artifact; not steerable by the copy spelling. All three held.

## Pointer local `T *p = 0;` -> dead entry-mov of a pooled 0 (2026-07-30, func_02031384)

Symptom: the ROM loads a literal 0 from the pool into a scratch reg at entry and does a DEAD
`mov rHome, r0` into a callee-saved register, before any branch (rHome is reassigned later, e.g. it
becomes the slot pointer). mwcc from clean C omits it (N-1 instructions short) and often `mov #0`s
the 0 inline instead of pooling it.
Fix: explicitly initialize the pointer local that later holds the object to 0 -- `MsgSlot *slot = 0;`
-- and keep a later `->field = 0` literal store. mwcc materializes the init 0 in the pointer's
callee-saved home (the dead mov), CSEs it with the pooled 0, and reuses that 0 for the field store.
On func_02031384 (message allocator) this took 184->188 (exact size) and reproduced the ROM's
`ldr lr,[pool=0]; mov r5,lr` structure.
Also in that function: a 4-byte-header data buffer `base+0xd0 + idx*0x34 + 4` must be a STRUCT
`{u32 hdr; u8 data[0x30]}` accessed as `buf[idx].data` so the `+4` is a separate `add` (mwcc folds
`base+0xd4 + idx*0x34` into the mla otherwise, 1 instr short). And the free-slot counter at +0x750
splits naturally as `+0x700` then `[+0x44]` (ldrh offset limit).
RESIDUE (still in build/try/31384.c): after all the above the instruction STREAM is byte-identical
and size-exact 188, but a register-numbering + scheduling permutation remains (ROM carries the 0 in
lr and the slot-base in ip; mwcc swaps them, 0->r4, slot-base->lr). Declaration order, store order,
pointer types, `register` -- none flip the ip/lr choice. Genuine regalloc tie at that point.

## `|`/`+` operand order flips a register-swap tie; fresh global read forces a reload (2026-07-31)

Two cracks from func_02033d0c (Slot_Spawn), a high-reloc slot-spawn matched 244B exact:

1. **Reload a global instead of caching it** when the ROM re-reads it. The ROM loads
   `base = *data_0204c234` for the early flag/default checks (in r4), then REUSES r4 for the slot
   pointer returned by the allocator, so it RELOADS the global for the final handle calc. Caching
   `base` in a C local keeps it live end-to-end -> mwcc parks it in an extra callee-saved reg (r5,
   push grows) and never reloads: 1 instr short. Fix: cache `base` only for the early uses and
   read `data_0204c234` FRESH at the late use (`slot - (int)(data_0204c234 + K)`). mwcc then
   reuses the register and reloads, matching the ROM. (Also: `char *` gives `ldrsb` under
   `-char signed`; use `unsigned char *` for an unsigned byte flag read -> `ldrb`.)

2. **Operand order of a commutative `|`/`+` picks which operand keeps its register.** The handle
   was `field | (index << 24)`. Written `field | (index<<24)` mwcc put the reloaded base/index in
   r1 and field in r2 (swap vs ROM). Written `((index) << 24) | field` -- the SHIFTED term first,
   the plain reloaded term second -- it kept the index chain and the field in the ROM's registers.
   Byte-exact. General: when a `|`/`+` result differs only by a two-register swap between the two
   addends, try flipping the source operand order before calling it a tie. (Caveat: does NOT help
   every add -- on func_02024ee8 `count*4 + (half>>15)` the shifted operand is forced to rm either
   way, so the swap made it worse; the lever works when BOTH operands are plain values competing
   for rn.)

STRATEGY note that produced these: after several iterations stuck on register ties in LOW-reloc
scalar/MMIO primitives, switching to MEDIUM funcs with MANY sequential calls (8-10 relocs) gave
clean matches -- func_020279e0 first-try, func_02033d0c after 2 cracks. Switch-DISPATCH funcs
(func_020342e8) are still ties (the jump-table preamble reg choice), so prefer sequential-call
funcs. Rank undone MAIN funcs by (#done-callers, reloc-count) to find them.

## Distinct-but-identical struct type to stop scalarize + double-spill (func_0201449c, 2026-07-31)

Symptom: the ROM makes a struct copy on the stack and reads it at two separated points
(one home, e.g. vertical.h then final.w), PLUS there is a second dead struct copy next to it.
Every natural two-copy C form (both copies the SAME struct type) makes mwcc SCALAR-REPLACE the
copies and DOUBLE-SPILL the live one -- it gets two stack homes, so the frame is +8 and the
size overshoots (296/300/308). Using a single copy DSEs the dead one (undershoots). No
declaration order, no `register`, no `volatile`, no `#pragma opt_dead_assignments off`, no
address-taken form moves it (all measured on func_0201449c).

Fix: give ONE of the two copies a DISTINCT struct type with the IDENTICAL layout, and copy
into it with a reinterpret:
```c
typedef struct { int w, h; } TextDims;
typedef struct { int w, h; } TextDimsAlias;   /* same layout, different type identity */
TextDims work;            /* live copy  -> sp+0x20 */
TextDims dims;            /* out param  -> sp+0x18 */
TextDimsAlias hview;      /* dead copy  -> sp+0x10 */
func_0201386c(&dims, ...);
hview = *(TextDimsAlias *)&dims;   /* horizontal pass reads hview.w (dead stack, w kept in reg) */
work  = dims;                      /* vertical.h + final.w read from work */
```
The distinct type stops mwcc from coalescing/scalarizing the two copies together, so the live
copy keeps ONE home and the dead copy survives -- exactly the ROM's `dead@0x10 / dims@0x18 /
live@0x20` layout (declaration order then fixes which slot is which; first-declared = highest).

General rule: when the ROM has a dead struct copy adjacent to a live one and EVERY same-type
two-copy form double-spills the live copy, split them into two distinct-but-identical struct
types. Pairs with the reuse-`t` double-negation lever (`t=-h; x+=t*-b; y+=t*a` -> two rsb, no
`-h*-b -> h*b` fold).

## THUMB register-numbering flip via an early variable reference (func_02030e7c, 2026-07-31)

Symptom: a THUMB function is size-exact and instruction-exact but a long-lived pointer (ctx) is
colored one register lower than the ROM (mwcc ctx=r4, ROM ctx=r5), cascading a whole-function
r4<->r5 swap. mwcc numbers virtual registers by first def/use, so the function's first-defined
long-lived variable (usually the ctx = first-call result) grabs the lowest callee-saved (r4).

Lever (PARTIAL - proven to flip, not yet to fully close): reference ANOTHER long-lived loop
variable (e.g. the outer byte-offset induction) with a REAL, non-dead assignment BEFORE the ctx
fetch. mwcc then numbers that variable first, ctx moves up to r5, and the whole swap flips. On
func_02030e7c, `outer = 0; ctx = NNSi_...();` (outer used later in the loop) flipped ctx r4->r5.
CAVEATS that made it not-yet-a-full-match: (a) a DEAD early assignment is eliminated and does NOT
flip (must be live); (b) an early `outer = 0` emits `movs r6,#0` at the top, whereas the ROM inits
the outer induction from the counter's spilled 0 (`ldr r6,[sp]`) - so flipping via the outer offset
reorders the init; (c) the flip renumbered the inner-offset/inner-counter pair (r4<->r7 swap).
So the lever is real but the register set is COUPLED: flipping one pair perturbs another. For a
clean win you need the early reference to be a variable whose natural init matches the ROM's, so no
extra instruction and no secondary renumber. Recorded because the flip mechanism itself is
transferable to other size-exact THUMB coloring residues; func_02030e7c held in build/try.

## 2026-07-31 — MsgQueue_Init (func_02030e7c, THUMB) two new cracks + a proven 2-way tie

**Crack A — callee-saved COLOURING FLIP via first-declared explicit accumulator.**
mwcc THUMB gave `ctx=r4` (ctx is the first real pointer local) while ROM wanted `ctx=r5,
slotoff=r4`. Declaring the explicit inner byte-offset accumulator (`int so;`) as the FIRST
local, and actually using it (`so += 0xc`) inside the innermost loop, gives `so` the low
reg r4 and pushes ctx up to r5 — matching ROM. Earlier notes called this colouring
"unflippable"; it is flippable, but only with an explicit inner accumulator (a synthesised
strength-reduced offset from member access always lands in the HIGHER reg, keeping ctx=r4).

**Crack B — reuse a just-stored constant for a derived size via CSE.**
ROM: `movs r0,#2; str r0,[r5,#8]  (count=2); ...; lsls r0,r0,#5  (=0x40)` — it reuses the
count value still live in r0 rather than loading 0x40 fresh. Writing the alloc size as the
literal `0x40`, or via a local `n=2; n<<5`, both fold to `movs r0,#0x40`. Writing it as
`ctx->count << 5` (read back the field just stored) makes mwcc CSE the store (r0 still holds
count) and emit `lsls r0,r0,#5`. General lever: express a derived constant in terms of a
field/var written moments earlier to force the shift-reuse instead of a fresh immediate.

**The still-open residue is a genuine 2-way conflict (documented, do NOT treat as done):**
inner slot stores need `adds r1,r6,r1` (slotoff+entries). That operand order is emitted
ONLY by unified member access `ctx->entries[i].slots[j].f`, which synthesises slotoff to r5
(ctx=r4 → wrong colouring). Any explicit `ptr+off` form canonicalises to `adds r1,r1,r6`
(pointer as rn) regardless of C operand order (verified: `entries+eo+so`, `eo+entries+so`,
`(i<<5)+so+entries` all identical). So correct-add-order and correct-colouring each cost
~3 instructions and are mutually exclusive for this loop shape under mwcc 3.0/139. Best
candidate (build/try/30e7c_best.c) keeps colouring+alloc (byte-exact through 0x2a).

## 2026-07-31 (cont.) — MsgQueue_Init two more schedule levers (THUMB)

**Crack C — inner two-variable init order.** When an inner loop carries both a counter `j`
and a separate byte-offset accumulator `so`, ROM emits `movs r7,#0` (j) then `adds r4,r7,#0`
(so = copy of j's zero). Writing `so = 0;` on its own line before the loop makes mwcc emit the
movs for `so` and the copy for `j` (reversed). Fix: initialise BOTH in the for-clause,
`for (j = 0, so = 0; j < 2; j++)` — the left-to-right init makes j the movs and so the copy.

**Crack D — schedule a one-off zero store into a following struct copy.** A `ctx->field0 = 0`
that shares its zero register with the next loop's counter (`movs r6,#0` serving both) is
scheduled by mwcc relative to where the store sits in C. Placing `ctx->field0 = 0;` BEFORE the
adjacent struct copy (`params = data_...;`) pulled it from the very end of the block up into the
copy region (dropped func_02030e7c from 20 diffs to 10). Placing it after the copy pushes it to
the end (worse). Lever: to fold a stray store into a nearby block, move it just ahead of that
block in source, not after.

## 2026-07-31 (cont.) — ★ CONTROL THUMB `adds rd,rn,rm` OPERAND ORDER via pointer-vs-int typing

The single highest-value crack from the MsgQueue_Init work, and general. When mwcc emits a
two-register address add `adds rd, rn, rm` (base + loop-carried offset), **the operand it places
as rn is the one that is POINTER-typed in the C expression.** So you choose the order:

- want `adds r1, r6, r1` (offset/eo as rn, pointer second): make the OFFSET the char* and the
  base the int -> `eo + (int)ctx->entries`, where `char *eo = (char *)(i << 5);` (the cast-to-
  pointer still strength-reduces to the r6 accumulator seeded from i, so no extra instructions).
- want `adds r1, r0, r6` (base/entries as rn, offset second): make the BASE the char* ->
  `(char *)ctx->entries + (int)eo`.

Two identical values, opposite rn, selected purely by which side is pointer-typed. Confirmed by
flipping exactly the inner-loop stores (offset-first) vs the outer-entry stores (base-first) of
func_02030e7c independently. Prior belief ("explicit ptr+int always canonicalises to pointer-rn,
so eo-first is impossible without member access") was WRONG -- it is impossible only while the
POINTER is the base; retype the offset as the pointer and the offset becomes rn. This dissolves
the add-order/colouring conflict documented earlier the same day: keep the explicit `so`/`eo`
accumulators (correct colouring) AND get member-access add order (correct) at the same time.
func_02030e7c went 36 -> 5 diffs with this; the only residue left is copy-preamble scheduling.

## 2026-07-31 — vreg-flip does NOT apply to pooled constants (func_02031384)

The declaration-order vreg-flip (declaring a var first to give it the low callee-saved reg, as it
flipped ctx in func_02030e7c) does NOT work for a POOLED CONSTANT. func_02031384's flags=0 is a
pooled literal (`unsigned int z=0`, size-exact 188 with it). ROM keeps it in lr (freeing r6 for
idx); mwcc here loads it into r6 (shifting idx=r7/mask=r8, +1) REGARDLESS of whether z is declared
first, last, or middle -- tried all three. mwcc picks the register for a pooled constant by its own
allocation, not by C declaration order. Adding register pressure to force z->lr backfires: explicit
pointer vars CSE and shrink the function (172), double-0 (ret=0 / slot=0) add instructions (192).
So the vreg-flip lever is specific to computed/loop-carried variables; pooled-constant register
placement remains uncontrolled from source. func_02031384 stays SIZE-EXACT with this lone residue.

## Callee arity from the ZERO-GATE register (Ov008_Menu_SetupSprites, func_ov008_0207f614)

When the ROM computes a value with `orrs rN, ..., #imm` and then, past the `beq`,
calls `bl f` while rN is STILL LIVE and rN is an argument register (r1/r2/r3),
that value is BOTH the zero-gate AND an argument of `f` -- i.e. `f` takes one more
arg than a naive read suggests. Pattern:

    orrs r1, r0, #tag        ; r1 = handle, sets Z
    addeq sp,..; popeq        ; if (handle == 0) return
    add  r0, r2, #off         ; r0 = region  (arg1)
    bl   f                    ; f(region, handle)   <- r1 (handle) is arg2

Read it as `f(region)` (1 arg) and the guarded value dies in r0 (`orrs r0,...`),
+3 bytes off per call site. Fix: give the guard its own variable and pass it --
`unsigned int h = ...; if (h != 0) f(region, h);` -> h is materialised into the
arg register (r1) and stays live across the compare, reproducing `orrs r1;...;mov`.
The `!= 0` test on a value with bit31 forced set is provably-true but mwcc does NOT
range-eliminate it, so the `orrs;beq` is emitted verbatim. General lesson: the
register a gate value lands in, and whether it survives to the next `bl`, is direct
evidence of the callee's true arity -- check it before trusting a 1-arg reading.

## Bitfield vs manual shift — the flag-bit coloring crack (2026-07-31)

A bit test that disassembles as `ldrh rV,[..]; lsl rS,rV,#(31-n); lsrs rS,rS,#0x1f; b<cc>`
(the `(x << (31-n)) >> 31` extract shape) is a **16-bit bitfield access** `f->bN`,
NOT a hand-written shift and NOT `x & mask` (a mask gives `tst`, and the signed
`(int)(x<<N) < 0` form gives the shorter `lsls;bmi` = 8 bytes less for two tests).

Nobody writes `(x<<27)>>31` by hand; the compiler emits it for a 1-bit field.
Both the manual shift and the bitfield emit the identical `ldrh;lsl;lsr` triple, so
verify_idx passes on SIZE and instruction shape — but they **color differently**:

- manual `((unsigned)*(u16*)p << 0x1b) >> 0x1f` keeps the CSE'd container in a
  scratch reg (r1) and shifts into r0 → diverges at the field load (`ldrh r1,[..]`).
- bitfield `((Flags*)p)->b4` coalesces the container into the field's own register
  (r0) and alternates the scratch (r1 for test 1, r0 for test 2, value dies into
  its last use) → matches the ROM exactly.

Recipe: `typedef struct { unsigned short b0:1,b1:1,...,b15:1; } Flags;` then
`Flags *f = (Flags *)(base + off); if (f->b4) ...`. A bit SET at the tail is the
same bitfield written: `((Flags*)(base+off))->b8 = 1;` → `ldrh;orr #0x100;strh`
(and, crucially, re-derefs a global if you pass the base expression fresh rather
than a cached pointer — the ROM reloads globals, so don't cache the base or you
lose the reload and the function shrinks).

First hit: func_ov008_02058ae0 (Ov008_Menu_CommitEnterSubScene8). Nine expression-
form variants (unsigned extract, signed `<0`, `(x>>n)&1`, local vs inline, 4-param
sig, pointer cache) all stuck at r1; the bitfield matched on the first try. This
resolves the "physical-register-coloring coin-flip" class on flag-bit fields
(the same shape that had 56988-style residues parked). Try the bitfield BEFORE
declaring a coloring tie on any function that tests bits of a status halfword.

## Declaration order picks r4 vs r5 for a load+preserved-copy pair (2026-07-31)

When you load a value and keep a preserved copy of it (working var mutated in
branches + an original kept for a later compare), mwcc colours the two locals in
**declaration order**: first-declared -> r4, second-declared -> r5. This is
independent of assignment order.

The ROM pattern `ldrh r5,[..]; mov r4,r5` (load into the MUTATED/working reg r5,
copy to the preserved r4) is reproduced by declaring the **preserved copy FIRST**
(uninitialised) and the working var SECOND with the load:

    unsigned short cur;                                   /* declared 1st -> r4 */
    unsigned short next = *(unsigned short *)(p + 0x5c0); /* declared 2nd -> r5, gets the ldrh */
    int rec;
    cur = next;                                           /* mov r4,r5 */
    ... mutate next ...; if (cur != next) { ... }

Declaring `next` first (the natural `next = load; cur = next;`) colours next->r4
and emits `ldrh r4; mov r5,r4` instead - a one-register swap that diverges at the
very first load byte and cascades through every use, even though the net register
state after the two instructions is identical (r4==r5==value).

Ran ~18 variants on func_ov008_020579a8 (Ov008_Menu_UpdateDirectionalPrompt):
unsigned/signed/int types, register keyword, p6-first, shared cur/p6 temp, struct
field, re-read CSE - ALL stuck at next->r4. Only reordering the declarations so the
preserved copy is declared first cracked it. This is the same "physical-register
coin-flip" class noted for 56988; try declaration reordering FIRST on any
load+preserved-copy residue before calling it a tie.

## Variadic (K&R) call arity + cached global base for a store pair (2026-07-31)

func_ov008_02057c78 (Ov008_Menu_ToggleDetailPanel) calls func_ov008_02057b7c
(Ov008_Menu_PositionSelector) TWICE with different arg counts: the enter path sets
r0-r3 (4 args: 1,8,nY,nX) and the leave path sets only r0,r1 (2 args). A fixed
prototype can't produce both. The fix is a **K&R declaration** `extern void
func_ov008_02057b7c();` (unspecified args, NOT `(void)`), so each call site passes
its own count. The callee ignores args 3/4, but the ROM's enter path leaves the
selector's nY/nX sitting in r2/r3 anyway - so you must pass them (4-arg call) to
reproduce those regs; the leave path passes 2.

Passing nY/nX as args 4/3 ALSO fixes a coalescing problem: without them, mwcc reads
the two adjacent struct fields with a single `ldm r0,{r3,r4}`; the 4-arg call forces
nX->r3 and nY->r2 (the arg registers), splitting it back into two `ldr` like the ROM.

Separately, the +0x5cc/+0x5d0 store pair reloaded the context pointer each time
until it was cached in a local: `gp = data_ov008_02090f1c; *(int*)(gp+0x5cc)=nX;
*(int*)(gp+0x5d0)=nY;`. The ROM keeps *global in the now-dead ctx register (r4)
across both stores; the explicit `gp` local reproduces that single load. Field-read
locals (nX,nY) declared before `gp`, `gp` before the pointer local - declaration
order still drives the r2/r3/r4 assignment. Match needed all three together.

## Large-function coloring: two-step compute + loop-branch fall-through (2026-07-31)

func_ov008_020574c0 (Ov008_Menu_RefreshSlotPanel, 1256B, all 8 callee-saved regs)
matched only after three cracks that steer register allocation WITHOUT touching
declaration order (declaration order was proven inert here across ~10 permutations):

1. **Two-step computation pins a long-lived value's register.** `mask = (u16)(~uVar8 &
   func_ec18())` coloured `mask` into a mid register (wrong). Splitting it into
   `mask = func_ec18(); mask = (u16)(~uVar8 & mask);` moved `mask` into the high
   callee-saved register the ROM uses and dropped the diff from 66 -> 8. When one
   long-lived local is mis-coloured, computing it in two statements (load, then the
   op in place) changes the interference graph enough to re-pin it.

2. **Loop branch fall-through decides which value mwcc caches in a register for the
   whole loop.** Ghidra emitted `if ((mask & bit) == 0) { hide } else { visible }`;
   the ROM is `if ((mask & bit) != 0) { visible } else { hide }`. With the VISIBLE
   block as fall-through, mwcc caches `&stk` (used only in visible) in fp across the
   loop; with HIDE as fall-through it instead caches the constant 0 (the hide calls'
   `,0)` arg) and recomputes `&stk` inline. Flipping to the ROM's orientation fixed
   66 -> 22 diffs. Match the branch that makes the fall-through block the one whose
   loop-invariant value the ROM hoists.

3. Two adjacent byte loads in the loop (`page = stk[5]`, `bVar2 = cur[3]`) are the
   same load-pair colouring as the 579a8 case: declare the one that must take the
   LOWER register first (here `bVar2`), read the other into its own (later) local.

Net path: 66 (structure right, all coloring) -> flip loop -> 22 -> two-step mask ->
8 -> swap byte-load decls -> MATCH. Structure first, then these three coloring levers.

## Array initializer `= {0}` forces a held-base zeroing (2026-07-31)

func_ov008_02057f58 (Ov008_Menu_RefreshSubitemGrid, 1512B, largest in ov008) came down to a
SINGLE-byte-word residue after everything else matched: the ROM zeroes a 7-word stack array with a
HELD base pointer (`add r6,sp,#0x1c; mov r5,#0; str r5,[r6,#0..0x18]`, 8 instr) while 7 explicit
`flags[i] = 0;` assignments compile to direct `str r4,[sp,#N]` offsets (7 instr) -- one instruction
short, and no source reorder / pointer / register hint moved it (~24 experiments over 5 fires).

THE FIX: declare the array with an initializer -- `unsigned int flags[7] = {0};` -- and delete the
explicit zeroing loop. mwcc lowers the aggregate initializer to the held-base store form the ROM
uses, closing the size exactly. (Grep of the whole matched corpus found NO other function with this
held-base-multi-store idiom, so there was no reference form -- the initializer was the only lever.)
When a stack array's zeroing is one instruction short with direct [sp,#N] offsets vs the ROM's
`add base; str [base,#N]`, try the `= {0}` initializer before anything else.

Two more from the same function (both in the .c comment too): the bVar4 input branch is
`ed3c() != 0 ? 570c0() : ebf0()` (ROM `beq` to the ebf0 arm), and entry-0x93 visibility must
normalise `ebf0() != 0` INTO the bool var before the FindEntryById (ROM's early movne/moveq),
not defer `!= 0` to the call site. Path: initializer closed size -> selection flip + early
normalise -> MATCH.

## unsigned-short temp flows through r0 (table read-OR-write loop)  [2026-07-31, func_ov008_02056ec0]

Loop shape: `SetField(fld, W, GetField(fld, W) | table[i].val)` over a stride-8
table, W a constant. Two register-allocation traps, both fixed by ONE source form:

- Inlining the OR into SetField's 3rd argument rotates the whole callee-saved
  bank by one (const-W lands r5 not r4, copy-of-W steals r4). Cause: nesting the
  inner call inside the outer arg makes the OUTER call's `W` vreg get the lower
  number, so it colours r4.
- Fix: compute the merged value in its OWN statement AND type it `unsigned short`:
    `unsigned short v; v = table[i].val | GetField(fld,4); SetField(fld,4,v);`
  The u16 temp keeps the OR result in r0 (GetField's return reg), which forces
  the field-id recompute into r2/r3 exactly like the ROM, and the separate
  statement lets GetField's `4` colour r4 first -> clean r4/r5/r6/r7.
  (`unsigned int v` gives the right SETUP regs but schedules the value through r3,
  freeing r0 for the field chain -> off by the middle block. u16 is required.)
- Also: unsigned loop counter + unsigned GetField return -> blo/poplo (not blt).

## Base-pointer type flips r4/r5 callee-saved allocation (2026-07-31)

When a function loads `ctx = *data` and derives a second long-lived pointer
`rec = ctx + BIGOFF`, and both survive across calls (so both land in r4/r5), the
DECLARED TYPE of `ctx` decides which gets r4:

- `int ctx = data_ovNNN_...;`  -> rec gets r4, ctx gets r5  (WRONG for func_ov002_0206a230)
- `char *ctx = (char *)data_...;` + `char *rec = ctx + BIGOFF;` -> ctx=r4, rec=r5 (ROM)

Same instructions, only the r4<->r5 naming swaps; verify_idx reports the first
diff at the `ldr r4,[r0]`. Fix: type the context base as `char *` (a real
pointer) rather than `int`, so the first-loaded value keeps the lower register.
Confirmed byte-exact on func_ov002_0206a230 (Ov002_InitHandleRecord, THUMB).

## Single mask literal reused with a barrel shift (2026-07-31, func_ov002_0206b910)

ROM keeps one pool constant (0x00fffffc) in a register and uses it twice:
`and r2,r2,r1` and `and r0,r0,r1,lsr #15`. Write the mask as ONE literal used in
both places -- `x & 0xfffffc` and `y & (0xfffffc >> 15)` -- and mwcc materializes
the shifted form via the barrel shifter instead of pooling a second constant.
Do NOT pre-fold the shift into a separate literal (0x1ff), which would pool it.

## Signed short/int for -1 stores reuses the ~0 register (2026-07-31, func_ov002_02069240)

When several adjacent fields are set to -1 with mixed widths (strh at +0/+2, str at
+8/+0xc, strb 0xff at +4), ROM materializes 0xffffffff ONCE (movs;mvns) and stores
it to every field via strh/str/strb (each truncates). To reproduce, type the store
lvalues as SIGNED `short`/`int` and store `-1`:

    *(short *)(rec + 0) = -1;   *(short *)(rec + 2) = -1;
    *(int   *)(rec + 8) = -1;   *(int   *)(rec + 0xc) = -1;
    rec[4] = -1;   /* char rec -> strb of the ~0 reg */

With UNSIGNED lvalues (u16), mwcc instead makes a clean 0xffff -- pooling a second
constant (if the u16 store is first) or inserting `lsrs r,~0,#16` (if a u32 store is
first) -- both add bytes and break the match. Signed truncation tells mwcc the high
bits are don't-care, so it strh's the ~0 register directly.

## Loop preheader placement: induction-init before vs after the guard (2026-07-31, func_ov002_0206e640, OPEN)

For a guarded search loop `for(i=0; i<count; i++)` walking a table, ROM emits the guard
(`cmp count,#0; bls`) and places the induction-pointer inits (p=hdr, e=hdr+1) in the
preheader AFTER the guard, alongside the hoisted loop-invariant (cmpVal). Two idioms, each
half-right, NOT simultaneously obtainable so far:

- Manual walking pointers (`for(p=hdr,e=hdr+1,i=0; i<*hdr; p+=0xf,e+=0xf,i++)`): produces
  the exact clean walk AND the exact loop register allocation (count=r6, p=r2, e=r3,
  cmpVal=r5, i=r1) and bls guard -- but mwcc emits p/e inits BEFORE the guard. First diff
  at 0x1C; everything from the guard onward is byte-exact.
- Index form (`hdr + i*0xf`): lets mwcc place the strength-reduced inits after the guard,
  but it keeps an `i*stride` multiply in the loop instead of walking (first diff at 0x0).
- Explicit `if (i < count) { p=..; do{}while(i<count); }`: places p/e after the guard AND
  gives bls, but the register allocation shifts (count=r2 not r6) because fewer values are
  live at the guard.

LEVERS that DID work here (keep for reuse): (1) inline `*hdr` in the loop condition (not a
cached `count` var) => count lands in callee-saved r6 and the loop registers all match;
(2) writing the loop-invariant read `*(short*)(ctx+0x8ba8)` INLINE in the body => mwcc
hoists it to the preheader after the guard (matches ROM) instead of computing it before;
(3) `if (i < count)` with i just set to 0 => mwcc const-props to `cmp count,#0; bls`
(a relational, not the `beq` you get from `if (count != 0)`).
Same family as the mla-vs-walk open item. Best candidate parked in build/try/6e640.c (NOT
nonmatching).

## RESOLVED (2026-07-31): preheader placement / walk-vs-multiply -> use a STRUCT with array indexing

The func_ov002_0206e640 "OPEN" entry above is SOLVED. The residue (induction-pointer inits
emitted before the guard instead of in the post-guard preheader; and the index form keeping an
i*stride multiply) was a SOURCE-SHAPE problem, not a compiler limit. Fix: model the walked table
as a real struct and index it as an array.

- WRONG (manual walking pointers): `u32 *p=hdr, *e=hdr+1; for(...; p+=0xf,e+=0xf,...)` -> clean
  walk and correct loop registers, but mwcc places p/e init BEFORE the guard (first diff ~0x1C).
- WRONG (raw pointer index): `hdr + i*0xf` -> mwcc keeps an `i*stride` multiply in the loop.
- RIGHT: `typedef struct { short cmpField; ...; u8 rest[..]; } Entry;` (sizeof == the stride,
  here 0x3c) inside `struct { u32 count; Entry entries[1]; }`, then
  `for (i=0;i<t->count;i++) if (t->entries[i].cmpField==sel) found=&t->entries[i];`
  mwcc strength-reduces `&t->entries[i]` into TWO induction pointers (base+i*stride and
  base+4+i*stride, matching the ROM's two `adds rN,#0x3c`), initializes them in the preheader
  AFTER the guard, and emits no multiply. The struct SIZE being the exact stride is what makes
  the array subscript reduce to a clean pointer walk.

This is very likely the same fix for the other "mla-vs-walk" parks (c010, bd50): try the struct-
array form before treating strength-reduction residues as compiler ties. Final remaining diff on
6e640 after the struct fix was a single else-inline branch flip on the payload byte-select, fixed
the usual way (`if ((flag & 4) != 0) X; else Y;` with the arms swapped).

## int accumulator vs u8 (2026-07-31, func_ov002_02069b70)

A counter that is incremented in a loop and only stored to a byte at the END should be
declared `int`, not `u8`. `u8 count; count++;` forces a per-iteration zero-extend
(`lsls #0x18; lsrs #0x18`) after the add; `int count; count++;` is a plain `adds`, and the
final `data = count;` still truncates with the strb. Declaring the accumulator u8 added 4 bytes.

## for-init comma controls which loop var gets movs vs the copy (2026-07-31, func_ov002_02069b70)

When two loop vars both start at 0 (a counter and the index), mwcc materializes one with
`movs rX,#0` and copies the other with `adds rY,rX,#0`. Which gets the movs follows SOURCE
init order. ROM did `movs r5(j); adds r4(count)` -> put BOTH in the for-init with the index
first: `for (j = 0, count = 0; j < n; j++)`. A separate `count = 0;` statement before the loop
makes count the movs target instead (swapped registers).

## Large switch: case bodies emit in SOURCE order, recover it from the jump table (2026-07-31, func_ov002_0206fb84)

For a dense ARM switch (jump table via `addls pc,pc,r0,lsl#2`), mwcc emits each case BODY in the
order the cases appear in the SOURCE, and the original source order is often NOT numeric. When the
jump table matches but one/some case bodies land at the wrong address, do NOT guess: disassemble
the function, read the jump-table `b <target>` list (target = case body address), sort the bodies
by ADDRESS, and that address order IS the source case order. Re-emit the switch cases in exactly
that order. For 0206fb84 the recovered order put kind 0x12 right after kind 9 and kind 0xb down
with the tail unconditional kinds -- purely from reading the table. Also: a shared tail
(`goto submit;`) must sit AFTER the default `return X;` in source, and the callee's small-int arg
being u16 shows up as `lsl #16; lsr #16` (zero-extend) at the call, so type that param u16.

## Phantom params + -1-via-mvn + u64-return-no-setup (2026-08-01, func_ov002_02068e68 teardown)

Scene handlers returned by a dispatcher are void(void) even when Ghidra invents param_1..param_4:
those are leftover r0-r3 the callees happen to receive. Signs it's really void: the "params" are
only ever PASSED THROUGH to callees, never computed. Also: a callee whose arg the disasm builds as
`mov r0,#0; mvn r0,r0` wants -1 (write `f(-1)`, NOT `f(0xff)` which emits `mov r0,#0xff`); and when
`bl A` is immediately followed by `bl B` with NO register setup between, B reuses A's return - if A
returns a u64 (`long long`), its r0:r1 become B's first two args, so declare B with exactly those
2 args (`f_b((int)v, (int)((unsigned long long)v>>32))`) and mwcc emits no arg setup. Ghidra will
show extra trailing args on B from leftover r2/r3 - drop them.

## 64-bit divide: call func_02020368 DIRECTLY, never the / operator (2026-08-01, func_ov002_020692a8)

`(u64_value) / constant` makes mwcc emit `bl _ll_sdiv`, and `_ll_sdiv` is NOT a defined project
symbol -> reloc points at an unresolved name (verify_idx: "relocs difieren", mine=_ll_sdiv vs
orig=func_02020368) and the gate can't link it. The ROM helper lives at 0x02020368. The matched
idiom (src/calls/func_0201cc1c.c and ~dozens more) is to CALL it directly:
`extern int func_02020368(unsigned long long value, unsigned int divisor, int arg3);`
`result = func_02020368(dividend_u64, divisor, 0);` -- the u64 rides r0:r1, divisor r2, 0 r3.
So for `(ticks<<6)/0x82ea` write `func_02020368((u64)ticks << 6, 0x82ea, 0)`, NOT `/`.

## Two induction cursors to the SAME address: use struct copies (2026-08-01, func_ov002_020692a8)

ROM read the 8-byte entry head via one cursor (r7) and wrote it back via another (r5), BOTH equal
to base+i*0x104 (two registers, same value). Field-by-field `u16 buf[4]` with two u16* pointers, a
single pointer, or struct-array member access all made mwcc CSE the two cursors into ONE (often
spilled) - 280/264 vs 292. Modeling the head as a struct and doing STRUCT COPIES
(`Head buf = *(Head*)rdp; ...; *(Head*)wrp = buf;`) is what makes mwcc keep the read-cursor and
write-cursor in separate registers. Final byte came from emitting the walking-flag `fp++` BETWEEN
the two `rdp += 0x104` / `wrp += 0x104` increments: fp is spilled, so its increment clobbers r0
(the stride constant), forcing mwcc to re-materialise 0x104 for the second cursor - exactly the
ROM's two `movs #0x41; lsl #2`. (Same mla/CSE family as 02069454; there char*+volatile was the
lever, here it is struct-copy + increment ordering.)

## Split [reg] vs [sp] addressing for the same stack buffer (2026-08-01, func_ov002_02076924)

ROM cleared a 4-byte stack record via a base register ([r4,#k]) but wrote the per-iteration byte
through the SP slot ([sp]). To reproduce: declare the record as an `int`, clear it byte-by-byte
through an explicit `u8 *p = (u8*)&buf;` (mwcc materialises &buf in a register and uses [r4,#k]),
and do the loop write through `*(u8*)&buf = ...;` directly (mwcc folds that to [sp]). Using the
pointer for BOTH gives [r4] everywhere; using the array/`buf[k]` for both gives [sp] everywhere;
only the pointer-for-clear + direct-for-update split matches. (Grep found the add-sp+strb-[reg]
idiom in ZERO matched functions, so it is rare - the int+pointer split is the reproduction.)

## CRACK: return the parameter to pin r0 across a global null-check (was func_ov002_02078e18 residue) — SOLVED 2026-08-01

**Lever:** when a `void`-looking function guards its whole body with `if (global != 0) return;` and
the parameter is spilled to [sp] and used only late, mwcc EAGERLY spills param at entry
(`str r0,[sp]; ldr r0,[pc]; ldr r0,[r0,#4]; cmp r0`) — the null-check temp gets r0. The ROM instead
keeps param in r0 across the check (temp -> r1) and folds the spill into the load-delay slot
(`ldr r1,[pc]; str r0,[sp]; ldr r1,[r1,#4]; cmp r1`). The fix: make the function **`int`-returning and
`return <param>` on the early-exit path** (`if (global != 0) return param;`) and FALL OFF THE END on
the create path (no tail `return` — an explicit `return 0` adds `movs r0,#0` -> +4 bytes). Returning
the param on the exists-path keeps it live in r0 across the compare (for the potential return), which
is exactly what forces the lazy spill + r1 temp. The caller ignoring the result makes this invisible
at the call site. func_ov002_02078e18 matched byte-exact this way after ~65 experiments where every
other axis (arity, volatile, struct, base-ptr, decl order, loop shape, CFG) left it at diff@0x2.
Corollary confirmed: THUMB `ldrsh` forces the r1/base form too (no immediate-offset ldrsh) but is the
wrong access width; a kept base pointer fills the slot but goes to callee-saved r6 (short body).

(historical note) OPEN RESIDUE header retained below for context:
### func_ov002_02078e18 entry eager/lazy spill

Play-order frontier dep of constructor func_ov002_020679d4. THUMB, 148B.
Body 0xa..0x93 is **byte-exact**; residue is the 2-instruction entry null-check (offsets 0x2-0x9).

- ROM  : `ldr r1,[pc]; str r0,[sp]; ldr r1,[r1,#4]; cmp r1,#0`  (param kept in r0, LAZY spill in
  the load-delay slot; null-check temp in r1)
- mwcc : `str r0,[sp]; ldr r0,[pc]; ldr r0,[r0,#4]; cmp r0,#0`  (EAGER spill frees r0; temp in r0)

Semantics verified: lazy-singleton init of the scene manager at data_ov002_0207fa28[1]. `param_1`
(scene id 0x792b from the caller) is used exactly once, LATE (record store at mgr+0x2518). No
callee takes param (all args constants: func_020769b0(0x26a8,0x5c,0xa0), NNSi(0x18),
CpuClear(-1,buf,0x18), func_02025668(buf,0xa0), func_0202c594(entry), func_0207643c(0x1f,mgr)).
`data_ov002_0207fa28` must be `volatile` (reproduces the 6 re-reads of root+4; non-volatile caches
the alloc result in r4 -> 132B).

~65 compiled experiments across every axis. The ONLY trigger for the ROM r1/lazy form is keeping
`param` live in r0 across the compare, which requires an EARLY use of param (e.g. `alloc(param,...)`
-> gives the exact ROM entry) — but that changes the (constant) call-arg bytes, so it is wrong.
Also confirmed: `ldrsh` (short read) forces r1 because THUMB ldrsh needs a register offset (not
applicable to the folded int `ldr [rN,#4]`); a kept base pointer fills the delay slot but goes to
callee-saved r6 and shortens the body (140B). Base-kept vs direct-global is the fork: named base ->
kept (r6, short body); direct global -> re-materialised (correct body) + eager r0 entry.
Best candidate: build/try/78e18.c (diff@0x2). NEXT: think about what pins r0 at the compare with a
folded int access and constant call args — possibly a mwcc scheduler input not reachable via
equivalent C at this shape; revisit before the constructor func_ov002_020679d4.

## CRACK BUNDLE: func_02020e58 (gameplay action interpreter, 496B THUMB) — SOLVED 2026-08-01 (3 fires)
A large goto-based command interpreter with a jump table. Five distinct levers, all confirmed:
1. **e/cmd register swap (r4<->r5).** Mainloop `e = base+count*stride; cmd = e[0x10]`. mwcc put
   e=r5/cmd=r4; ROM e=r4/cmd=r5. UNRESPONSIVE to decl order (24 perms), register, volatile,
   type-alias, full struct typing, init/increment order. **FIX: read the dispatch key back through
   the base (`data_tbl[*(u8*)*(char**)(e+0x10)]`) instead of the cached `cmd[0]`.** Using e for the
   first post-compute access makes mwcc keep e in the low reg r4 and cmd in r5. (The "earlier-USED
   value gets the low register" rule.)
2. **Two-way test block order = fall-through-first.** For every `if`, write the arm the ROM keeps
   as fall-through as the taken branch's *complement*: ROM `if (h==0) branch-away; hb fall-through`
   is written `if (h != 0) { hb } else { null; goto }` (NOT `if(h==0){null;goto} hb`). Applied to
   handler-present, field!=0, callback-result==0, and count>0. Each wrong orientation is a whole
   swapped-block region in the diff.
3. **switch bound check: explicit `default: goto X;`, no separate `if (r > N)`.** An explicit
   `if (r>6) goto` emits a signed `bgt` ON TOP of the switch's own unsigned `bhi` bound check (2
   instr). Drop the if, add `default:`, and switch on `(unsigned)r` so the single `bhi` covers it.
4. **Accumulate an address into ONE temp to fix its base-load schedule + register.**
   `func(base + idx*K)` gave idx loaded first / base in the low reg. `int a = base; a += idx*K;
   func(a);` forces the base load first and lands base in the high reg like ROM.
5. Jump-table `add pc,rN` recovered by reading the 7 halfword offsets at table_base+k*2 as signed,
   target = (pc_of_add+4)+offset (see the decoder in the fire log).

## CRACK: GX/hardware register block -> struct field access fixes RMW register (func_02023cc0, 2026-08-01)
An RMW on a hardware/register-block global (`*(int*)((char*)&data + 0xNN) &= ~m`) allocated the base
to the WRONG register (r1 vs ROM's r0) and mis-scheduled the surrounding block (51 diffs). The tree
already models these blocks as a typed struct (`data_02047394` in src/calls/func_02015630.c, a GX
geometry-engine register block with field_00..field_238). Rewriting the RMW as
`data_02047394.field_d4 &= ~m` (struct field, not a hand-cast byte offset) fixed the base register
and dropped it to 22 diffs. ALSO: aliases in that file -- `data_0204739c` = &data_02047394+0x08,
`data_020473e0` = +0x4c -- are declared `extern char data_X[];` and passed by name (the reloc goes
to data_X, verify accepts by address). And data_020475ac/b8/c4 (the 3 VecFx32 copied in) are
data_02047394.field_218/224/230; using the struct fields keeps the reloc address-equal (verify OK).
Lesson: when a function bit-twiddles a `data_020473xx`/`data_020475xx` global, grep src for a file
that already declares it as a struct and reuse that type -- it is a GX register block.
OPEN RESIDUE on func_02023cc0: 22 diffs left are a pure list-scheduler ordering of the 3-VecFx32
copy block (the `add ip` for the p14 pointer is emitted one slot later than ROM; identical
instruction multiset). Best candidate build/try/23cc0.c. Not a register/arity problem.

## Whole-block scheduler tie -> vary the PRECEDING call's arg structure (func_02023cc0, 2026-08-01)

Symptom: an in-body copy/computation block (here three VecFx32 struct copies feeding an
MTX_LookAt call) is byte-identical to ROM in instruction MULTISET but ~7 instructions are
reordered (two address `add`s and a pool `ldr` land one slot off). Every in-body lever gives the
SAME schedule: local decl order, ptr vars, const/typed args, struct vs separate globals, big
struct, volatile, restrict, RMW placement, block-copy, store-after-call, return types. ~40
experiments, all 9-diffs or worse.

Cause: mwcc's list scheduler works on the WHOLE basic block, so the schedule of a late block
depends on the DFG of EARLIER statements even when those earlier statements compile to identical
bytes. Here the first statement was a call `func_02004d60(...)` whose first argument I modelled as
a 16-byte struct passed by value (compiles to `ldm r4,{r0,r1,r2,r3}`). The ROM's source passes the
same four words as FOUR SEPARATE SCALAR ARGS (also `ldm`-coalesced, identical front bytes) - but
the different DFG shape reschedules the downstream copy block into the ROM's order. Switching to
scalar args: instant byte-exact match.

Rule: when an in-body block-scheduler residue will not move under any in-body lever, change the
ARGUMENT STRUCTURE (struct-by-value vs N scalars, arity grouping) of a PRECEDING call in the same
basic block. Two arg shapes can produce identical front bytes yet different whole-block schedules.
Confirm the callee's real arity via its Ghidra decompile first (func_02004d60 genuinely takes 7
scalar params, so the scalar form is also the semantically correct one).

Related tooling fix (same day): verify_idx.py now compares final reloc addresses = symbol +
RELA r_addend for data relocs (type 2), not just symbol name/address. mwcc emits a struct-field
address `data_X.fieldN` as a reloc against base `data_X` with r_addend = field offset; that resolves
to the same address as the ROM's standalone symbol `data_Y` at data_X+off, and now verifies MATCH.
The pool word itself is 0 (RELA), so the addend is the only place the offset lives. This is required
for the mandatory struct-first form whenever a function writes fields of a global struct.

## Deferred-assignment CSE local pins a register pair + schedule (func_02021418, 2026-08-01)

Symptom: a function is byte-exact EXCEPT the last few instructions of a tail block, where two
registers (here r0/r1) are swapped: a held pointer (a `short*` sin/cos TABLE base, 2 uses) took r0
and a spilled scalar (1 use) took r1; the ROM has them the other way. The block, pool placement and
instruction multiset are otherwise identical.

Cause: mwcc colours the pointer (more uses / longer live range) first -> r0. The ROM colours the
scalar first because the scalar is LOADED before the base and stays live across the base load (its
store is deferred past the literal-pool `b`). Whatever is DEFINED first in the linearised IR of the
block wins the low register. A hoisted `T *base = ...;` declared at the block head defines the base
first -> it wins r0.

Fix: don't hoist the pointer, and drive the index through a local ASSIGNED AFTER the first store,
using byte-offset addressing so the base is materialised inline (not kept in a named local):
  int i2;
  obj->field = scalarValue;              /* store first -> scalar defined/used first */
  i2 = (angle >> 4) * 2;                 /* CSE assigned AFTER the store */
  obj->sin = *(short *)((char *)table + i2 * 2);
  obj->cos = *(short *)((char *)table + (i2 + 1) * 2);
Two things had to be true together and each was tested: (a) i2 must be a NAMED local so it stays a
shared CSE - inlining `(angle>>4)*2*2` folds to `*4` (lsls#2) and the two offsets stop sharing;
(b) i2 must be assigned AFTER the store, not at the block head - a head declaration schedules the
shift before the pool and shifts everything. The struct form `table[i].nSin/.nCos` (FxSinCos{s16,s16})
materialises base AND base+2 as two pool words instead of one held base - wrong.

General rule: when a tail block is byte-exact except a swapped register pair, the lever is which
value is DEFINED first in that block's IR. Move the competing definition earlier/later (a store
before it, a deferred CSE assignment) rather than hunting register hints - `register`, temps, and
signedness did nothing here. data_0203d210 is the shared global sin/cos angle table (short[], entry
stride 4, [i*2]=sin [i*2+1]=cos); declare it `extern short data_0203d210[];`.

## Pointer-typed parameter survives in a callee-saved register (func_020220dc, 2026-08-01)

Symptom: a function is size-exact but a PARAMETER that must live across several calls is spilled to
the stack (`str r1,[sp]` at entry, reloaded before each use), while the ROM keeps it in a
callee-saved register (r7) the whole time - the two competing values swap between reg and [sp].
Same instruction count, pure allocation difference.

Fix: type the parameter as a POINTER instead of int. mwcc keeps a pointer-typed argument that is
live across calls in a callee-saved register; the same value typed `int` gets spilled to the stack.
Here `func_020220dc(int *state, short *cmd)` (cmd used as cmd[4] / cmd+4) matched, whereas
`int cmd` spilled it. The command/operand pointer was genuinely a pointer, so this is the correct
type as well as the matching one. General: when a parameter used only for pointer arithmetic /
dereferences is spilled where the ROM holds it in a register, give it its real pointer type.

(Also in that function: hold `base` and `slotBase = obj+0xN` in registers and re-add per use rather
than caching the summed pointer; write the optional-operand test `if (desc != 0) resolve; else 0;`
so the null case is the branch target.)

## Relocation loop: struct-array base + pointer-arith + while + branch-tail (func_02025464, 2026-08-01)

A per-object "fix up relative offsets to absolute pointers" loop (8 sections, each with a count +
entries). Four INDEPENDENT levers, each ruled a distinct residue, ALL required together for the
byte-exact match - a good worked example of stacking cracks:

1. Section base register: model the object as a Ghidra/C struct with the slots as `sections[8]` and
   access `state->sections[i]`. That yields ONE callee-saved per-iteration base
   `add rB, state, i, lsl#2 ; ldr [rB, #8]`. The two wrong forms bracket it: a plain array
   expression `param_1[i+2]` splits the base between a scratch reg (outer) and a recomputed index
   (inner, across the call); a cached `int *sec = param_1 + i` strength-reduces to an advancing
   pointer `sec += 4` (loop-carried).
2. Entry-guard condition: write the inner walk as `while (i < count)`, NOT `if (count != 0) do {}
   while (i < count)`. The while makes mwcc derive the leading guard from the loop's unsigned
   back-edge -> `cmp count,#0 ; bls` (constant-folding i=0); the explicit `if (count != 0)` guard
   emits `beq` (plain equality). `0 < (unsigned)count` does NOT help - mwcc folds it back to `!=0`.
3. Commutative add operand order: write base+offset relocation as POINTER arithmetic
   `(int)((char *)state + offset)`, not `(int)state + offset`. Pointer arithmetic makes the base
   the add's Rn (`add r0, r8(state), r1(offset)`); the int form canonicalises the freshly-loaded
   offset as Rn (`add r0, r1, r8`). Source operand order does NOT change it (swap tested).
4. Empty-slot guard: `if (slot != -1) { work } else { slot = 0; }` so the small set-zero is the
   `beq` branch-tail block (matching ROM), not a predicated `moveq/streq` inline.

Lesson: a "size-exact but N register/condition diffs" function is often several stacked
canonicalization choices, each fixed by a different idiom (struct member vs array vs cached ptr;
while vs if+do-while; pointer-arith vs int-add; if/else orientation). Fix them one at a time and
re-measure; the diff count drops per lever (here 208 -> 200 -> 4 -> 2 -> MATCH).

## Ghidra hides a REUSE behind a recomputed constant (Anim_GetBlendFactor func_0202136c, 2026-08-01)
Angle wrap `iVar1 = q - 0x4000; if (iVar1 < 0) iVar1 += 0x10000;` - the ROM adds 0x10000 to the
ALREADY-biased iVar1 (and mwcc materializes 0x10000 as the 0x4000 register `<<2`, one instr:
`lsls r0,r1,#2; adds`). Ghidra's decompile INSTEAD prints the algebraically-equal
`iVar1 = q + 0xc000` (recompute from the quotient q), which mwcc emits as `movs #3; lsls #0xe;
adds` (+1 instr) and comes out too big. **Lesson: when Ghidra shows `x = base + K2` right after
`y = base - K1` on the same value, suspect the ROM actually did `y += (K1+K2)` reusing y** - the
reuse form is shorter and matches. Fixed func_0202136c at the first retry (152B, was +8).

## Two levers for object-init functions with struct copies + a sin/cos table (Camera_Init func_02021060)
1. **VecFx32 struct copy to an object field: address it through a TYPED int* base with POINTER
   arithmetic, not a byte offset.** `*(VecFx32 *)(param_1 + 6) = data_global;` (param_1 is `int *`,
   so +6 = +0x18) matches; `*(VecFx32 *)((int)param_1 + 0x18) = ...` (byte offset, param_1 an int)
   makes mwcc HOIST a second param_1 copy into a scratch reg for the ldm/stm dest and renumber the
   whole tail (95 diffs, same size). This is the crack-5b "hand-computed byte offset is wrong C"
   symptom, but for a struct COPY: model the whole object as `int *` and index it (`param_1[N]`).
   The matched tree already had the exact form: `int *state; *(struct vec3 *)(state + 3) =
   data_02041dc8;` (func_ov123_020cd9ec).
2. **The {sin,cos} angle table (data_0203d210): when a function reads BOTH sin and cos of the same
   index, use the flat short[] view `tbl[idx*2]` / `tbl[idx*2+1]`, NOT a SinCos struct.** With the
   struct, `[idx].cos` compiles to the WRONG offset (idx*4, i.e. .sin) once the two accesses share
   the index CSE; the ROM computes `.cos` as `(idx*2+1)*2` (a short-array index). A struct `.sin`
   ALONE is fine (Anim_GetBlendFactor), so this only bites when both fields of one entry are read.

## Shared-return-tail via `goto` (2026-08-05, HIGH-YIELD, ov002 reloc-free vein)

When a function has several early-exit `return N;` with the SAME value, mwcc predicates each one
inline (`movXX rD,#N; popXX`/`bxXX`) — but the ROM often branches them ALL to ONE shared tail
(`bXX #tail ... tail: mov rD,#N; bx lr`). Force the shared tail by writing every one of those
exits as `goto retN;` with a single `retN: return N;` at the end. This flipped predicated→branched
byte-exact in **func_ov002_0207c788** (packed hi/lo mask predicate) and **func_ov002_02070384**
(2D point-in-box test). It's the branchy-predicate analogue of the guard-earlyexit crack.

Companion levers proven the same day on the reloc-free ov002 algorithmic vein (7/8 matched
first-or-second try — this vein is high-yield, prefer it when mid-size dispatchers tie out):

- **Precompute a sum/expr into a local to fill a scheduling slot.** mwcc hoists an independent
  `add` into the slot after a `cmp` (before the branch) only if the value is "ready". Writing
  `s = cx + w;` before the `if (cx - w > x)` pulled `add r2,ip,lr` ahead of the `bgt` to match the
  ROM (func_ov002_02070384). The byte-identical prefix otherwise fixes the schedule.
- **Put the loop-invariant/global LOAD last in an expression** to fix both operand order AND which
  register it lands in: `(j + i*0xf + 0x15 + *(int*)(p+0x14))` matched where base-first did not
  (func_ov002_02052650 tilemap fill); same lever as pointer-first `base + *(int*)(base+8)` keeping
  the base as the first `add` operand (func_ov002_02066fc0 header relocation).
- **Declaration order picks the register / ldmib pairing.** Declaring `entry` before the loop
  counter made `entry` claim r2 to pair with the count in `ldmib r0,{r1,r2}` (func_ov002_02066fc0);
  declaring the loop counter `i` first gave it the lower register r4 (func_ov002_0205249c).
- **Inverted if-condition places a block out-of-line + enables `||` shared tails.** Writing the
  border case as the if-body with the inverted test produced the ROM's `cmp;cmplt;blt <end>` with
  the core case out of line, and combining two equal-value conditions into one `||` gave the shared
  return (func_ov002_0205b728 classifier).
- **STILL-TIE:** func_ov002_02063bf8 (nibble writer) — 18/24 instrs match; the loaded byte lands in
  r1 (mine) vs r2 (ROM) because the byte is loaded before the value nibble is computed. Byte-
  identical prefix fixes the register state; pure commutative-`orr` coloring tie. Also
  func_ov002_020646d4 (12B): ROM returns the raw global after an UN-normalized dead `cmp` — mwcc at
  -O4 always either canonicalizes `!=0` to 0/1 or DCEs the cmp; likely an inlined-then-outlined
  predicate. Both parked in build/try/, not nonmatching.

## Search / dispatch levers (2026-08-05, cont. — 31-match ov002 run)

The high-yield ov002 vein keeps paying out. Reusable levers proven across many matches this run:

- **`volatile` on a re-read loop bound** forces the ROM's per-iteration reload when mwcc would hoist
  an invariant memory read (no stores in the loop). Use it ONLY in a **do-while** where the read is
  the `while` condition (bottom-tested) — in a `for`/top-tested loop it over-corrects and adds
  instructions. Cracked func_ov002_020711d0 (`while (i < *(volatile int*)base)`). If the loop body
  makes a CALL, the reload happens naturally (the call may change the bound) — no volatile needed
  (func_ov002_0207a23c).
- **Declare the running pointer BEFORE `base`** to flip an ip/lr (or r4/r5) coloring tie between the
  loop pointer and the count/base. This finally cracked func_ov002_02074460 and _020711d0, both
  previously parked as "pure coloring ties". Combine with the 74460 shape: `int result=-1; int i=0;
  T *entry; int base=...; if (count>0){ entry=...; do{...}while(i<count); }`.
- **`switch` (not if/else-if) for a small type dispatch** produces the ROM's `cmp;beq <case>` chain
  with the case bodies placed OUT OF LINE after the dispatch; an if-else chain inlines the first
  case instead. Cracked func_ov002_0207be9c and _0206c834.
- **`goto ret0` shared-return tail generalises broadly** — any function with several equal-value
  failure exits (return 0 / -1): the ROM branches them all to one tail, mwcc predicates each inline
  unless you `goto`. Cracked func_ov002_0207c788, _02070384, _020702fc, _02076dac(struct), _0206e770.
  Keep genuinely-different-value returns (e.g. `return x==7`) as their own predicated path.
- **Arg-forwarding / arg-transforming thunks match first-try** once the callee arity + narrow arg
  types are right: prepend-context (func_ov002_02053634), field-extract-and-forward
  (func_ov002_0206d1b4). Read narrow stack args as their real width (ldrb->unsigned char, ldrh->
  unsigned short) or the size is wrong.
- **`unsigned char` vs signed `char`** for a byte field read: `-char signed` makes plain `char`
  emit ldrsb; use `unsigned char` when the ROM has ldrb (func_ov002_020766e0, _02064a30).
- **Struct copy = ldm/stm**: a `struct{int a,b,c;}` assignment gives the ROM's ldm/stm block move
  (func_ov002_0207a500 vector snapshot, _02061df8 pool insert).

**STILL-PARKED tie classes (build/try/, documented):** large-offset addressing recompute
(func_ov002_0206d144/_0206d0e0 via base+0x8d14 -> mwcc recomputes base+0x8000), param-register
coloring on field-copies (func_ov002_02064a30, _0206bdcc), leaf-vs-nonleaf on the ldm pool insert
(func_ov002_02061df8), OSR row*32 (func_ov002_020667a0), and the `field&1` bool MATERIALISATION that
mwcc -O4 always elides (func_ov002_02076dac/_02076e08 — likely a lower-opt TU).
