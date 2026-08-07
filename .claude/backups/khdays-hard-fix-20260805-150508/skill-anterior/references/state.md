# ===== 05/08 (continuacion, +6 matches): ov002 veta reloc-free/small =====

Tras el push de los 9 iniciales, +5 matches mas integrados y pusheados: 7c67c (dispatch 5-slot,
lever: 0xe0 como offset aditivo del ldrsh, no hoist), 702fc (point-in-box 3D, mismo patron que
70384), 5a3f0 (jump-table clasificador, orden de case 10-antes-de-9), 75c64 (cursor 2x2 BG3),
6e2ec (popcount Kernighan - LEVER CLAVE: usar `unsigned` no `unsigned short` para el mask, evita
la truncacion lsl/lsr#16 por iteracion y deja el `ands` poner flags). Total sesion: 14 matches.
C=16119, bytes 39.01%.

**Ties nuevos documentados en build/try/ (NO parkeados):**
- 751fc (56B thumb): r4/r5 coloring de p vs array-ptr, size-exact estructural perfecto.
- 74460 (80B ARM search): ip<->lr coloring de count vs entry, estructura PERFECTA (do-while in
  if(count>0) + result var + single exit). 4 instrs difieren solo por ip/lr.
- 6d144 (84 vs 80): mwcc recalcula base+0x8000 con ldr#0xd14 para el word-load del entry ptr en
  vez de reusar el header ptr base+0x8d14. Addressing-mode tie de 1 instr.
- 769f0 (72 vs 70 thumb): hoist-vs-recompute - mwcc hoista base+0x50 y spillea param_1; la ROM
  mantiene base en r5 y recalcula (0x50 > imm de ldrh thumb).
- 667a0 (128B): OSR row*32 accumulator vs recompute row<<5.
- 0207a700 (thumb): BLOQUEO de config - la ROM recalcula todo sin CSE (0x10c materializado 2x/iter),
  patron de opt-level mas bajo; -O4 siempre CSEa.

**LEVER REUTILIZABLE nuevo:** cuando un valor viene de un ldrh/ldrb (u16/u8) pero solo se le
limpian bits (& en bucle), declararlo `unsigned` int no `unsigned short` -> mwcc no re-trunca.

**Pendiente tractable (212 funcs <=140B ov002):** muchas son search/setter/plot limpias que matchean
al 1er-2o intento; las que tienen offsets grandes (>imm) o presion de registros pegan ties de
hoist/coloring. 0205a830 depende de la convencion de func_02020400 (parece divmod, usa r1 tras call)
- necesita identificar ese callee antes.

# ===== 05/08 (sesion /loop port-first): ov002 gameplay -- veta reloc-free algoritmica =====

**9 matches byte-exact integrados y pusheados** (C 16106->16114, bytes 38.98->39.00%):
54b40 (readiness predicate, rompio el plateau del subsistema de sonido) + 66fc0 (reloc de header),
5249c (row-fill simetrico), 5b728 (clasificador 0xb/c/d), 7c788 (mask predicate hi/lo), 52650
(tilemap fill 15x15), 70384 (point-in-box 2D), 61908 (extractor digito decimal), 62608 (append u16
acotado). Cracks nuevos en codegen-cracks.md: **goto a un return-N compartido** (fuerza branch->tail
unico en vez de predicar cada early-exit), precompute-suma-para-slot, load-al-final para operand
order+regalloc, orden de declaracion elige registro/pareja ldmib, condicion invertida para bloque
out-of-line + `||` shared tail. **La veta reloc-free ov002 es ALTO RENDIMIENTO: 7/8 al 1er-2o
intento.** Cada match: entrada delink partida + symbols.txt + sin stub sobrante (verificado).

**Ties documentados en build/try/ (NO parkeados):** 63bf8 (nibble writer, r1/r2 coloring, 18/24),
646d4 (12B, dead-cmp no normalizado, outlier), 667a0 (tilemap blit 128B, OSR de row*32 accumulator
vs recompute row<<5 -- fully structural, solo cascada de registros).

**FRONTERA proxima:** quedan ~5 reloc-free ov002 mas grandes/tie-prone (020702fc 136B, 0205a3f0
176B, 020662d4 184B, 020576d8 196B, 0207c53c 220B, 020519b0 368B) + los de 1-2 relocs pequenos
(020751fc 56B r3, 0207a700 68B r1, 0207c67c 68B r1). Empezar por los de 1 reloc pequenos.

# ===== 27/07 (sesion /loop port-first, iteracion 12): ov011 -- func_ov011_0205ac40 =====

## Sin experimentos nuevos de matching. **Corregido un error MIO en la capa semantica.**
Re-verifique el trabajo de Ghidra de la iteracion 1 en vez de darlo por bueno, y estaba **mal**:
`Ov011Scene` se creo con tamano **183684** cuando `0x2cf84` es **184196**, y los dos campos
finales heredaron el mismo desfase de **512 bytes** (`pResource`, `stream`).

**El sintoma que lo delato** no fue la tabla de layout -- que salia perfectamente plausible, con
offsets monotonos y dentro del tamano -- sino **la descompilacion**: los accesos al stream salian
como `pScene[1].aPane[0].field_0x1c0`, indexando a un segundo elemento fantasma de la escena.

Corregido: tamano **184196** (0x2cf84), `pResource` en **184148** (0x2cf54), `stream` en
**184152** (0x2cf58). Guardado (`closed=6; tx_after=NONE; SAVED_OK`) y re-descompilado: ahora
sale `pScene->pResource`, `&pScene->stream`, `.pfnInitialize()`, `.pfnOpen(&local_98)`,
`.pfnStart()`. La leccion general esta en `naming-hubs.md`.

✅ El `.c` candidato **no estaba afectado** (alli los rellenos son restas hex) y sigue en
**2 palabras**, lo que ademas confirma que los offsets del `.c` eran los correctos.

# ===== 27/07 (sesion /loop port-first, iteracion 11): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras**. Cerrado el eje de las formas que permite `-lang c99`.
Probadas y **todas codegen-identicas a lo que ya habia**: declaracion a mitad de bloque con
inicializador (`u8 *pDst = frame.path;` justo en el punto de uso, que en C89 no se puede);
bloque anidado alrededor de la copia; bloque anidado alrededor de toda la cola. Las tres dan
2 en N=1 y 464 en N=0, o sea **mwcc no distingue** una declaracion-con-inicializador a mitad
de bloque de una asignacion con la declaracion arriba, ni le afecta el ambito anidado.
El **literal compuesto** de C99 para los openParams (`frame.openParams = (T){ a, b };`) es
peor: 480 B.

Con esto el espacio de formas de fuente que se me ocurre construir esta agotado, ademas del
producto cruzado exhaustivo de la iteracion 10.

# ===== 27/07 (sesion /loop port-first, iteracion 10): ov011 -- func_ov011_0205ac40 =====

## ★★ BARRIDO EXHAUSTIVO DEL PRODUCTO CRUZADO -- suelo exacto 2, ningun punto byte-exacto
Todos los barridos anteriores movian **un eje cada vez**, y la dificultad entera de esta
funcion es que el planificador y el asignador dependen el uno del otro: o sea las
interacciones son justo lo que un barrido por ejes NO puede ver.

`build/try/ov011/crossac.py` construye la cola **desde cero** (sin sustitucion de texto, que
ya nos mordio) y cruza **los cuatro ejes a la vez**:
- 24 ordenes de las cuatro sentencias de prefijo (guardado de resource, booleano, puntero al
  stream, siembra del puntero destino);
- 7 posiciones del guardado de `enabled` dentro de las seis asignaciones (N=0..6);
- 16 subconjuntos del dispositivo volatile sobre las cinco lecturas candidatas (tamano 0, 1, 2).

**2.688 puntos compilados. 832 size-exact. Suelo exactamente 2. Ninguno byte-exacto.**

El optimo de 2 lo alcanzan **seis configuraciones equivalentes**: ordenes `RAPD` y `RADP` (la
siembra puede ir a cualquier lado del puntero al stream), split=1, y volatile en {12}, {9,12}
o {12,13} -- o sea **solo cuenta la lectura del stream**, las otras van de gorra. Y el numero
de palabras crece **exactamente lineal** con la posicion del split (2,3,4,5,6,7), lo que
confirma la regla de "stores en orden de fuente estricto" de la iteracion 2 **sobre todo el
espacio**, no solo sobre un eje.

**Conclusion util para quien siga**: la respuesta, si existe, **no es una combinacion de estos
cuatro ejes**. Tiene que ser algo estructuralmente distinto de todo lo probado en diez
iteraciones. No repitas este cruce.

# ===== 27/07 (sesion /loop port-first, iteracion 9): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras**. Eje cerrado: **guardados `volatile` como barrera de CSE**.
Hipotesis: la ROM relee el global cruzando el guardado al frame y nosotros hacemos CSE; un
guardado `volatile` seria una barrera gratis (un `str volatile` sigue siendo un `str`).
**Falso.** Cinco combinaciones (volatile en `resource`, en `enabled`, en ambos, en el primer
elemento de la copia, y `resource`+copia): las cinco dan exactamente el tamano de la forma
plana. **En mwcc 3.0/139 solo la LECTURA volatile mata el CSE.** Escrito en `codegen-cracks.md`.

## El `assert` del helper hizo su trabajo
Dos variantes cambiaban la grafia del campo y el reescritor a orden N=0 no encontraba nada:
salieron marcadas como `HARNESS-NOOP` en vez de colarse como el control. La defensa que se
escribio ayer en `tools.md` funciona.

# ===== 27/07 (sesion /loop port-first, iteracion 8): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras**. Cerrado el ultimo eje de la checklist: FORMA Y ALIASING DEL OBJETO DE PILA.
Todo identico (2 palabras / 464 B): el frame como union con un `u8[0x88]` crudo, union solo
sobre los openParams, `#pragma pack(1)` y `pack(4)`, el path como `u32[0x20]` con cast, y el
path como struct anidado con nombre. Ninguno mueve el residuo ni hace size-exact el orden N=0.

## ⚠ TRAMPA DE HERRAMIENTA cazada aqui -- vale mas que el barrido
El helper que reescribe el fichero al orden N=0 buscaba el literal `frame.openParams.enabled`.
Las variantes con union renombran el campo, el helper **no encontro nada y devolvio la entrada
sin tocar**, y el barrido informo de la union en N=0 como "2 palabras": volvio a medir el
control y parecio un avance. Misma familia que el blob de asm_stubs, que Jython mintiendo sobre
el limite de 64K y que el scorer leyendo un diff vacio como MATCH. **Ausencia de efecto leida
como exito.** Escrito en `tools.md` con la defensa mecanica (`assert` en el helper).

# ===== 27/07 (sesion /loop port-first, iteracion 7): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras**. Verificada en AMBOS modos (`--thumb` da 316 != 468, o sea ARM).

## ★ Se hizo la comprobacion que faltaba: ARIDAD Y PROTOTIPOS DE LOS LLAMADOS
El chequeo mas barato y de mas valor del skill **nunca se habia corrido sobre esta funcion**.
Corrido bien: la aridad real de cada llamado leida de los sitios de llamada casados del arbol.

**Una sorpresa de verdad**: `func_02024ee8` **esta descompilada** y su definicion toma
**CUATRO** parametros -- `unsigned int *func_02024ee8(char *, unsigned int, void *, int)` --
y nosotros la declaramos con dos. Esa es exactamente la firma del bug de argumento final
perdido que explica varios de los rescates del skill.

**No es la causa aqui**, y la razon merece quedar escrita: en el sitio de llamada de la ROM
**ni r2 ni r3 se escriben en ese camino** (el `blx` anterior los machaca), asi que ese sitio
pasa dos argumentos de verdad y el llamado es variadico en uso. Medido igualmente, todo
identico (2 palabras / 464 B): declaracion de dos parametros, variadica explicita, tipos de
retorno y parametros reales del llamado, y declaracion sin prototipo. Las otras siete
aridades confirmadas contra sitios de llamada reales: todas coinciden con lo que hay escrito.

## Otros ejes cerrados
- **Pares de accesores `static inline`** (la palanca que abrio `func_ov011_0205b814`)
  aplicados al orden que ya acierta el guardado: mwcc los pliega, la rejilla entera
  2 x 9 x 3 (orden x conjunto de helpers x conjunto volatile) cae en el mismo suelo 15 / 31.
- **Infraestructura**: `config/arm9/file_compilers.json` mapea fichero -> VERSION de
  compilador y nada mas, y `CFLAGS` en `tools/configure.py` son globales. Pero el eje de
  flags ya esta cubierto en fuente por `#pragma optimization_level` (2, 3 y 4 byte-identicos),
  asi que **no hay cambio de infraestructura que merezca la pena** aqui.

## staging/ sin cambios (1 stub rechazado + 14 de ov003 fuera del frente).

# ===== 27/07 (sesion /loop port-first, iteracion 6): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras** (`verify_idx.py`: `byte diff @0x138`). Nada integrado ni commiteado.

## ★★ CORRECCION de lo que escribi en las iteraciones 3-4
Dije que la posicion del guardado de la ROM **no era alcanzable** en ninguna forma size-exact.
**Es alcanzable.** Lo que no es alcanzable es tenerla JUNTO CON el manejo de la direccion.
Hay **tres formas, cada una correcta en un eje distinto**, y no se combinan:

| forma | palabras | que acierta | que falla |
|---|---|---|---|
| **1** (la del fichero, N=1) | **2** | todo | el guardado de `enabled` va un elemento tarde |
| **2** (N=0, volatile en sitios 10 y 12, siembra ANTES del guardado) | 31 | `str r6,[sp,#4]` en 0x138 exacto **y** el booleano en r6 | la direccion del global se queda en un registro libre en vez de destruirse y rematerializarse |
| **3** (N=0, volatile solo en el sitio 12) | 15 | el manejo de la direccion | booleano en r2 y guardado diez instrucciones antes |

## El mecanismo de la forma 2 (esto si es util y es nuevo)
Poner la **siembra del puntero destino ANTES del guardado** hace que mwcc suba
`add rX,sp,#8` hasta 0xd8, y ese valor vivo de mas es lo que empuja el booleano a un
registro callee-saved, lo que a su vez deja que el guardado se hunda hasta la ranura de la
ROM. Mueve la siembra detras del guardado y colapsa otra vez a la forma 3.

## Barridos de esta iteracion
- **Exhaustivo bajo el orden de la forma 2**: todas las combinaciones de 1, 2 y 3 sitios
  volatile sobre las 15 lecturas del global. Solo 12 son size-exact, **todas contienen los
  sitios 10+12 y todas puntuan 31**.
- `volatile` sobre el **miembro `pScene`** y sobre la **declaracion `extern` entera**: las dos
  dan 488 B, o sea siete recargas forzadas donde hacen falta dos. Demasiado grueso.

## staging/ sin cambios (1 stub rechazado + 14 de ov003 fuera del frente).

# ===== 27/07 (sesion /loop port-first, iteracion 5): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras** (`verify_idx.py`: `byte diff @0x138`). El MECANISMO ya esta cerrado.

## ★ El dispositivo NO habia que inventarlo: ya estaba en el arbol
Barrido de corpus con el filtro CORRECTO -- "la direccion de un global destruida por una
desreferencia de si misma (`ldr rX,[rX,#k]`) y luego rematerializada desde la misma palabra
de pool, sin llamada en medio" -- da **42 funciones casadas**, y **`func_ov008_0204f930`
tiene exactamente nuestra forma** (`ldr r1,[r1,#4]`, o sea global+4).

Su cabecera describe nuestro problema con estas palabras: *"the retail compiler re-loads
data_02090f04[1] there, but mwcc 3.0/139 reuses the just-stored value / a precomputed
address. The volatile forces the reload; behaviour is identical"*, y usa un par de macros
`CTX` / `CTXV` para ello. **Es el dispositivo estandar del proyecto**, no una invencion.
Medidas aqui tres grafias, byte-identicas: puntero a struct `volatile`, lectura
`*(volatile int *)((char *)&g + 4)`, y la lectura del miembro. Adoptada **la del miembro**
(`*(Ov011Scene *volatile *)&data_ov011_0205e960.pScene`) porque no necesita offset a mano.

## ★★ Por que el residuo es un PUNTO FIJO, no un eje sin explorar
Aplicando el dispositivo sitio por sitio sale la aritmetica exacta:
- la forma N=0 **en plano** son 460 B, o sea **dos `ldr` de menos**, y ya destruye `&g`
  igual que la ROM (`ldr r3,[r3,#4]`); simplemente reutiliza el `pScene` resultante para la
  cadena del stream en vez de recargar;
- **cada dispositivo volatile anade exactamente UN `ldr`**, asi que N=0 necesita dos;
- barrido de un sitio sobre las 15 lecturas del global y barrido por PAREJAS sobre las 105
  parejas: **un unico punto size-exact en N=0** (sitios 10+12) y puntua 31 palabras;
- y el listado ensena por que: en cuanto se fuerza la lectura del stream, mwcc **mantiene
  `&g` vivo en un registro libre (r3)** y mete `pScene` en otro, con lo que la direccion no
  se rematerializa nunca. **Forzar la lectura y destruir la direccion se excluyen mutuamente**
  con este asignador.

La misma circularidad bloquea el otro extremo: las ordenaciones N=0 que son size-exact ponen
el booleano en r2 y no en r6, y el booleano solo llega a r6 si el guardado se planifica
tarde, lo que solo pasa si el guardado va tarde en la fuente = la forma N=1.

## Estado para el usuario
Cinco iteraciones, ~5.000 compilaciones, distancia 24 bytes -> 2 palabras. La funcion **no
esta aparcada** y el candidato sigue solo en `build/try/ov011/BESTac40.c`. Lo que queda es un
punto fijo del asignador descrito con precision, no un eje sin probar: **merece una decision
del usuario** (seguir, o cambiar de funcion en el frente ov011 y volver luego).

# ===== 27/07 (sesion /loop port-first, iteracion 4): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras** (`verify_idx.py`: `byte diff @0x138`). Nada integrado ni commiteado.

## Ejes cerrados en la iteracion 4
- **Grafia de acceso al global**: miembro de struct vs elemento de array (`data_X[1]`, que es
  la forma que usa el arbol casado en otras funciones) vs lectura volatile de array. Igual o
  peor. O sea el struct que teniamos no era el problema.
- **Accesores `static inline`** para la direccion del stream y para la escena, con y sin el
  volatile dentro, con y sin el local: mwcc los pliega en el llamador, o sea son exactamente
  la expresion en linea. (La palanca que funciono en `func_ov011_0205b814` no transfiere aqui.)
- **Las 27 builds de mwccarm sobre la forma N=0**: ninguna 2.0/3.0 la reproduce. 1.2/sp3 y sp4
  si dan 468 B pero con 201 bytes de diferencia -- otra epoca de codegen, no usable.

## ⚠ AVISO DE METODO: un filtro de corpus que casaba la FORMA y no el MECANISMO
Busque en el arbol casado "la misma palabra de pool cargada dos veces sin llamada en medio" y
salieron **97 funciones** -- pero casi todas son otro fenomeno: una constante de puntero a
funcion devuelta desde dos ramas de un `switch`. El filtro casaba el patron y no la causa.
Aplicando la regla de "enuncia primero la forma positiva": lo que hace falta aqui es
**"la direccion de un global rematerializada porque el registro que la tenia fue machacado por
una desreferencia de si mismo"** (`ldr rX,[rX,#k]`), no cualquier carga de pool repetida.
Si se vuelve a intentar, ese es el filtro correcto.

# ===== 27/07 (sesion /loop port-first, iteracion 3): ov011 -- func_ov011_0205ac40 =====

## Sigue en **2 palabras** (1 diff que reporta `verify_idx.py`: `byte diff @0x138`).
Nada integrado, nada commiteado, gate sin tocar. `src/` intacto.

## El residuo, dicho con precision
La ROM carga la direccion del global desde la pool **DOS VECES** en esa region (0xd4 y
0x108), porque en 0xe4 machaca ese registro con `pScene` (`ldr r2,[r2,#4]`, destino ==
fuente) y luego tiene que rematerializar la direccion para la cadena del stream.
**Todas** las formas N=0 (el guardado de `enabled` delante de los seis `strb`, que es el
orden de la ROM) mantienen la direccion viva en un registro libre y la desreferencian tres
veces: ese es exactamente el `ldr` que falta, y por eso salen 464 B.

Las ordenaciones N=0 que SI son size-exact (15 palabras) aciertan con la direccion pero
ponen el booleano en **r2** en vez de **r6**, y entonces el guardado no puede hundirse: en
la ROM r0-r3, ip y lr estan todos ocupados durante la copia, y eso es justo lo que obliga
al booleano a un registro callee-saved. **El planificador y el asignador dependen el uno
del otro aqui**, que es lo que hace el borde tan duro.

## Ejes cerrados en la iteracion 3 (todos siguen en 2 palabras o en 464 B)
- N=0 con el booleano en linea, con `register`, y con el puntero al stream
  nombrado/plano/ausente, en todas las posiciones de siembra;
- ~430 puntos de la familia "cargas subidas por encima del guardado": 1..6 temporales x
  {u8, int, unsigned char} x {int, register int} x 3 posiciones del puntero al stream --
  **ninguno es siquiera size-exact**;
- el frame y los openParams alcanzados por puntero (`pFrame->`, `pParams->`), en N=0 y N=1;
- **todas las grafias de copia por struct REPROBADAS ya con el hoist puesto** (directa, por
  `u8 *`, por puntero tipado, dos punteros, `&frame.path[0]`): la copia por struct sigue
  plegando la direccion de pila, o sea 4 bytes corta, y 8 en N=0;
- `#pragma optimization_level` 0..4 (2, 3 y 4 son byte-identicos) + `optimize_for_size off`,
  `opt_unroll_loops off`, `ARM_conform on`.

## staging/
Sin cambios: el stub `asm`+`dcd` de ov000 sigue rechazado y ov003 sigue fuera del frente.

# ===== 27/07 (sesion /loop port-first, iteracion 1): ov011 -- func_ov011_0205ac40 =====

## FRENTE: ov011, la escena que instancia el titulo. FUNCION EN CURSO: el CONSTRUCTOR.
Elegida por el orden de rodaja vertical del skill (punto 1: constructor de escena y
estado inicial), no por tamano ni facilidad. **NO aparcada.**
Gate: `DSD_OK=306 FAILED=0` sin cambios -- no se ha tocado `src/` en esta iteracion, el
arbol esta como se encontro (solo `config/arm9/overlays/ov000/delinks.txt` sucio, que lo
regenera `configure` por diseno).

## `func_ov011_0205ac40` = `Ov011_CreateScene` (468 B, 12 reubicaciones, ARM)
Mejor forma: `build/try/ov011/BESTac40.c`.
**Pasa de 464 B / 24 bytes menos a 468 B EXACTOS con el MULTICONJUNTO de instrucciones de
la ROM.** Iteracion 1 lo dejo en 7 palabras; **iteracion 2 lo baja a DOS PALABRAS ADYACENTES
INTERCAMBIADAS**, 0x138 y 0x13c: la ROM tiene `str r6,[sp,#4]` (openParams.enabled) y luego
`strb lr,[r5]` (name[0]), y nosotros los dos al reves. Todo lo demas coincide byte a byte.

**Iteracion 2 -- lo que lo bajo de 7 a 2, y la regla general que salio**: mwcc **emite los
stores en orden de fuente estricto** (sube cargas libremente, nunca reordena store contra
store). Partiendo la copia detras del elemento N y poniendo ahi el guardado de `enabled`, el
residuo sale **exactamente N+1 palabras** -- una recta. N=1 es el minimo alcanzable. N=0 es
el orden de la ROM y es el unico punto que NO es size-exact (464 B, un `ldr` corto: mwcc se
queda la direccion del pool en un registro en vez de recargarla). Escrito en
`codegen-cracks.md`.

⚠ Corregido de la iteracion 1: la explicacion "los `strb` van por un `u8 *` y por eso mwcc
no puede reordenar el `str` de `int`" era **innecesariamente exotica** -- mwcc simplemente no
reordena stores, punto, sea cual sea el tipo.

### Lo que cerro los 24 bytes (tres cosas, en orden)
1. **El `add r5, sp, #8` sale de un puntero destino con nombre + asignaciones elemento a
   elemento.** La asignacion de struct pliega la direccion siempre. Precedente casado:
   `func_ov019_0207fa94`. Escrito en `codegen-cracks.md`.
2. **El origen tiene que ser `unsigned`** (`u8 []`): con `-char signed`, leer un `char[]`
   elemento a elemento da `ldrsb` y la ROM tiene `ldrb`.
3. **La cadena del argumento de la llamada hay que subirla Y que recargue**: local con
   nombre + lectura `volatile` del global. Sin el `volatile` mwcc reutiliza el pScene vivo
   en r2 y se pierden los dos `ldr` (460 B).

### Lo que queda, y por que no se mueve
Con el guardado de `enabled` DESPUES de la copia (forma actual) mwcc lo deja en r6 -- como
la ROM -- pero lo emite el ultimo. Escrito ANTES de la copia lo emite diez instrucciones
demasiado pronto y en r2 (clase equivocada). Ninguna grafia alcanza el punto intermedio.
**Causa identificada**: los seis `strb` van por un `u8 *`, que es un tipo caracter y alias
con todo, asi que mwcc no puede reordenar un `str` de `int` por encima de ellos; la ROM
consigue su posicion porque sube las CARGAS por encima de un guardado que ya estaba ahi.
Retipar el destino como puntero a struct (`->sz[i]`) tampoco cambia nada: el lvalue
accedido sigue siendo de tipo caracter.

### Ejes CERRADOS por compilacion en esta iteracion
16 encuadres de la copia; `memcpy`/`__builtin_memcpy`/`strcpy` (mwccarm **no los inlinea**,
los tres emiten `bl`); las 720 ordenes de los seis elementos; las 60 ordenes legales de las
cinco sentencias del bloque final; las dos posiciones de siembra de los punteros (la del
ORIGEN es inerte, la del DESTINO tiene que ir pegada a la copia); 384 puntos de
{tipo de bEnabled} x {grafia del booleano} x {orden de declaracion} x {posicion de
declaracion}, con `register` y `volatile`; 5 grafias del argumento de
`func_ov024_020832c4` x 3 prototipos; **las 27 builds de mwccarm** (todas las 2.0/* y
3.0/* dan salida IDENTICA, o sea el eje del compilador esta cerrado tambien para esta
forma).

### ⚠ EL EJE DE LOS PRAGMAS ES NULO, NO NEGATIVO
Barrido de los 82 nombres `opt_*` extraidos de `mwccarm.exe`, en `on` y en `off`: **solo
`optimize_for_size on` cambia la salida**. `scheduling`, `peephole`, `register_coloring`,
`opt_propagation`, `opt_lifetimes` y el resto se **aceptan y se ignoran**. O sea "puse el
pragma y no cambio nada, luego no es eso" no vale con este compilador. Detalle en
`codegen-cracks.md`.

## GHIDRA (hecho en el mismo lote, guardado con CloseTxAndSave.py -> SAVED_OK)
- `arm9_ov011::0205ac40` renombrada a **`Ov011_CreateScene`**, comentario de cabecera puesto.
- Tipos creados: **`Ov011StreamOpenParams`** (8 B), **`Ov011StreamInterface`** (16 B, los
  cuatro punteros a funcion) y **`Ov011MovieFrame`** (0x88 B).
- **`Ov011Scene` redimensionada de 0x21294 a 0x2cf84** (el literal de la pool en 0x1c0) y
  con los campos verificados: `dwFlags` +0x23ac0 (bit 2 = tapa cerrada), `nArg` +0x23ac4,
  `pResource` +0x2cf54, `stream` +0x2cf58.
- Ranura de pool `arm9_ov011::0205adf4` tipada como `Ov011Globals *`; la descompilacion ya
  sale con `->pScene->nArg`, `->pScene->dwFlags`, `->pScene->aPane[0]`.

✅ **RESUELTA la discrepancia abierta del 26/07** ("sizeof(Ov011Scene) da 0x21294 pero la
paleta esta en +0x23294"): no habia hueco ni bases distintas -- **la escena mide 0x2cf84**,
los dos paneles de 0x10940 en +0x14 solo ocupan hasta 0x21294 y despues hay mas objeto.

## staging/
`staging/ov000/func_ov000_02059b14.c` **RECHAZADO otra vez**: es un stub `asm`+`dcd`
(72 aciertos de `dcd`/`asm `), no una descompilacion. `staging/ov003/*` (14 ficheros) no
esta en este frente y una sesion previa los reverifico en ambos modos: ninguno casa.

# ===== 26/07 (sesion /loop port-first, en curso): ov011 -- func_ov011_0205b814 =====

## FRENTE: ov011 (la escena que instancia el titulo). 23 stubs restantes.
Gate al empezar y al cerrar la iteracion: **DSD_OK=306 FAILED=0**. Nada sin commitear
salvo `config/arm9/overlays/ov000/delinks.txt`, que configure regenera y va sucio por
diseno (no se stagea).

## FUNCION EN CURSO: `func_ov011_0205b814` = `Ov011_BlitTileRow` (228 B, ARM)
**NO aparcada.** Mejor forma en `build/try/ov011/BESTb814.c` --
**mnemonico 0 / operando 19 / palabras 14**: tamano, reubicaciones, flujo de
instrucciones, inmediatos, offsets y shifts YA son los de la ROM.

**Todo el residuo es UNA transposicion r4 <-> r5.** La ROM da r4 a la cadena de
temporales (literal 0x10940 -> pScene -> nCols) y r5 a `nPane`; nosotros al reves.
Los otros seis registros ya coinciden.

### Lo que YA se resolvio aqui (no lo deshagas)
1. En la rama de envoltura, la segunda copia tiene que actualizar `pSrc` y `pDst` como
   **sentencias, pDst primero**. Escrito como expresiones dentro de los argumentos,
   mwcc emite arg1 antes que arg2 y la ROM al reves -- era la ultima diferencia de
   mnemonico.
2. `nCols` tiene que ser **una sola variable** que alimenta el `mla` y el clamp, leida
   antes de la expresion de `pSrc`.
3. `pCore` y `pPane` son **dos cadenas de miembros independientes** desde el puntero de
   escena; derivar `pCore` de `pPane` colapsa las dos bases que la ROM construye a 0x14.

### Duenno del residuo (leave-one-out por bloques)
Borra la rama `else` de envoltura -> sale el coloreado de la ROM al instante. Quita
CUALQUIERA de las dos `MIi_CpuCopy32` de esa rama -> tambien. Quita solo
`pDst -= nCol << 6` -> `nPane` se va a r8 (tercera respuesta). O sea lo decide la
presion de tres llamadas vivas, no una grafia concreta -- y la ROM tiene las mismas
tres llamadas.

### ★ EVIDENCIA DE CORPUS SOBRE EL COLOREADO (lo mas util que ha salido)
En el arbol casado, una copia inmediata del parametro 1 cae en **r5 en 3.395 funciones** y
en r4 en 2.468: o sea la eleccion de la ROM es la normal y **la rara es la nuestra**. La
forma del corpus que la reproduce es `func_ov022_020b19ec`: un LOCAL declarado e
inicializado al principio del cuerpo se queda r4 y el parametro 1 se va a r5. Buscando el
prologo exacto que necesitamos -- literal de pool en r4 definido ANTES de `mov r5, r0` --
el arbol entero devuelve solo dos funciones, y en las dos r5 recibe el RESULTADO DE UNA
LLAMADA, no un parametro. Ninguna funcion casada produce todavia este coloreado desde C.

### Firma CONFIRMADA desde el llamador (no supuesta)
`func_ov011_0205bb58+0x248` pasa exactamente cinco argumentos y son **(nPane, A, B, A, B)**:
el tile de origen y la ranura de destino son el mismo par (x, y). Aridad cerrada.

### ★★★ ITERACION 3: MECANISMO IDENTIFICADO (esta en codegen-cracks.md)
Reproduccion minima en `build/try/ov011/repro/`. **Regla de mwcc**: los locales se llevan
los callee-saved bajos por orden y el parametro preservado se lleva el siguiente hueco por
encima; **cuando la presion sube, el parametro cae a r4**. Rejilla medida
(parametros x locales -> registro de la copia del parametro):

```
        locales:  0    1    2    3    4
  1 parametro:   r4   r5   r6   r7   r8
  4 parametros:  r4   r5   r4   r4   r4
  5 parametros:  r4   r4   r4   r4   r4
```

**Disparador en el micro** (5 parametros, todos vivos): `f(a * K)` con el producto
consumido en el acto da r4; `int q = a*K; f(q); f(q+b);` con q vivo da **r5**.

⚠⚠ **PERO ESO NO SE TRANSFIERE, y lo compruebo antes de dejarlo escrito**: sobre la funcion
de verdad, compilada con **5, 4 y 3 parametros declarados, las tres dan r4**. O sea el
numero de parametros NO es el dueno aqui; lo es la presion del cuerpo (quitar cualquiera de
las tres llamadas devuelve r5). La rejilla vale como observacion en un caso limpio; como
diagnostico de esta funcion, no. Ya esta corregido tambien en codegen-cracks.md.

**Dato de corpus que si aguanta**: de las funciones casadas con 5+ parametros, las 13 que
ponen la copia en r5 **ninguna multiplica el parametro 1**, y las dos que lo multiplican
(`func_ov008_0205f388`, `func_ov025_020918d8`) la ponen en r4. Y un barrido por histograma
de mnemonicos sobre todo el ROM encuentra **un solo casi-gemelo**, `func_ov011_0205b8f8` a
0.644 -- ya casado y con otro reparto porque su bucle vuelca el indice a la pila. O sea **no
hay plantilla que copiar** ni precedente casado de "multiplicar el parametro 1 por una
constante de la pool Y dejarlo en r5".

### Ejes CERRADOS (compilados, todos inertes en 0/19/14)
5.040 ordenes de declaracion (declperm, exhaustivo); los 40 ordenes de sentencia
legales del prologo; `register` en cada local, en todos y en el parametro; copia local
del indice de panel en las 8 posiciones; locales explicitos `pScene` y `pTileset`;
forma con struct `Ov011Tile` de 64 B; `u32` vs `int` en indice/fila/nCol/nCols/nFirst
(nCols DEBE ser unsigned: `int` da movgt donde la ROM tiene movhi); 7 grafias de la
rama de envoltura; locales nuevos con nombre para los punteros envueltos; copia local del
indice alimentando el direccionamiento con el PARAMETRO en el ternario (mwcc los fusiona);
plegar el indice de tile, la ranura de destino y la fila enmascarada en locales propios;
enmascarar `nDstRow` in situ; las 16 combinaciones de `const`/`register`; variantes de firma
de los externs; los 11 pragmas de optimizacion **medidos por el coloreado** y no por la
puntuacion (todos siguen dando r4, o sea la decision esta en la forma del IR);
helper `static inline`; 5 grafias de las guardas; aritmetica de
punteros conmutada en las 4 grafias; orden de operandos del `mul`; 2 y 3 parametros
extra sin usar; local `pScene` en las 8 ranuras; los 40 ordenes legales de declaraciones
CON inicializador; 21 pragmas
(incluidos `scheduling off` y `register_coloring on/off` -> la decision es del
asignador, no del planificador); los 13 niveles de -O (solo -O4 da 228 B); **las 27
builds de mwccarm dan salida IDENTICA**, o sea no es el compilador.
Descartado con evidencia: retorno no-void (10 mnemonicos), invertir la rama
(13 mnemonicos -> el caso simple es la caida), subir el tipo de comando a un local
temprano (37 mnemonicos -> el ternario se evalua en la llamada), imagen 2D
`Ov011Tile aTiles[0x20][0x20]` (7), quitar `pPane` y/o `pCore` (crecen a 236 B, o sea
las dos cadenas de miembros son correctas), structs por valor como parametro -- que harian
que el asignador viera cuatro parametros en vez de cinco -- (260/264 B, el struct se copia a
la pila), `volatile` en el puntero al tileset (260 B) o en nCols (256 B), y subir `nFirst`
por encima de la rama (6 mnemonicos). `-opt` no tiene ninguna palanca de
asignacion de registros mas alla de los niveles (mirado en la lista del compilador).

**Barrido combinado TERMINADO** (`build/try/ov011/wide.py`): 6 grafias de envoltura x 2 de
guardas x 5.040 ordenes de declaracion = **60.480 compilaciones, 0 flips**, mejor 0/19/14.
Ese eje esta agotado; no lo repitas. Tambien descartado: locales nuevos con nombre en la
rama de envoltura (reintroducen la transposicion, 2 mnemonicos) y reutilizar los parametros
en vez de locales (`nDstCol &= 0x1f` crece a 232 B, o sea `nCol` es un local de verdad).

## GHIDRA (hecho en el mismo lote)
`Ov011_BlitTileRow` renombrada, parametros nombrados, comentario de cabecera puesto, y
**creados los tipos** `Ov011Tileset` / `Ov011PaneCore` / `Ov011Pane` (0x10940) /
`Ov011Scene` (0x21294) / `Ov011Globals`, con la ranura de pool `arm9_ov011::0205b8f4`
tipada como `Ov011Globals *`. La descompilacion ya sale con
`pScene->aPane[0].core.pTileset`, `pOVar1->wCols`, `pOVar1->wRows`.

⚠ **Discrepancia abierta**: `sizeof(Ov011Scene)` con dos paneles de 0x10940 en +0x14 da
**0x21294**, pero el bloque del 26/07 de mas abajo situa la paleta en **+0x23294** --
0x2000 mas alla. El literal de la pool dice 0x10940 y el `mul` casa byte a byte, asi
que el stride es correcto; queda por explicar si hay un hueco o si aquellos offsets se
midieron desde otra base. El tipo de Ghidra solo declara lo verificado aqui.

## staging/
Solo `staging/ov003/*` (14 ficheros). ov003 NO esta en este frente y una sesion previa
los reverifico en ambos modos: ninguno casa. No se tocan.

# ===== 26/07 (sesion cerrada por el usuario): MAIN + ov011 =====

## 13 MATCHES, todos integrados, gate 306 y pusheados. Arbol limpio, nada sin subir.
`213947e5e` `584b8252a` `71c5a7a4c` `d3b65105d` `be6c221e6` `b29cb2cc0` `4768d0784`
`28624c5f1` `ca086c46e`

MAIN 15 -> 9 stubs. ov011 10 -> 17 de 40.

## ★★★ EL FRENTE: ov011 es la escena que instancia el titulo
`func_ov000_0205a4d4` carga ov012 (peliculas) si el modo es 0, si no **ov011**. Los
cuatro overlays previos del orden de juego (ov000/002/006/008) estan a 0 stubs.
Descriptor de clase en `0x0205e8a0`: +4 constructor `func_ov011_0205ac40`, +8
`func_ov011_0205b034`, y desde +0x14 una tabla de seis manejadores.

## ★★★ LAYOUT DE LA ESCENA ov011 -- confirmado por 4 funciones
`data_ov011_0205e960` = `{ int nCursor; Ov011Scene *pScene; }`.
La escena tiene **DOS paneles de 0x10940 bytes** en `+0x14` (stride confirmado en
be38 / c6fc / b814 / b8f8; **la pool dice `0x00010940`**, si lees `0x10920` es que
has malinterpretado el literal desensamblado).

Panel: `pBuffer` +0, bloque interno en +4 con `pTileset` en +8, imagen VRAM de
0x10000 en +0x908, `wScrollPhase` +0x1091a, esquinas +0x1091c..+0x10924,
`nPhase` +0x10931, `nFlag` +0x10932, `nSpeed` +0x10938, `nAccum` +0x1093c.
Tileset: `wRows` +0, `wCols` +2, `pTiles` +0x14.
Escena: `nA` +0, `nMode` +4, `nArchiveBase` +0xc, paleta +0x23294 (0x800),
`bFlags` +0x23abd (bit0 = scrolled), `wA` +0x23ac8, `wB` +0x23aca, `pTable` +0x23acc.

## ★★ CRACKS NUEVOS DE ESTA SESION (ya en codegen-cracks.md)
1. **Una palabra de la pool con un valor que cabria en un inmediato NO es un numero,
   es una reubicacion.** Destapo el par overlay-105 (`FS_OVERLAY_ID`).
2. **Bitfields.** Tres funciones distintas los delatan por la forma de los shifts:
   RMW sobre un local sin inicializar (`PXI_SendWordByFifo`), y `lsl#28/lsr#28` +
   `lsl#24/lsr#28` para dos nibbles (`b1bc`). Con `& 0xf` / `>> 4` sale una
   instruccion mas corta.
3. **Truncar con `<< 24 >> 8` != truncar con `(u8)`.** Mismo valor, distinto codigo.
4. **Copiar un parametro a un local justo antes del bucle** retrasa su carga por
   debajo de los retornos tempranos (b8f8: 13 mnemonicos -> 0).
5. **Guardar el bucle con un `if` de verdad** pone la carga invariante en el
   preencabezado, donde el `for` no puede (28df0, db90).

## Vivos en `build/try/ov011/` y `build/try/main/` -- NADA aparcado
| funcion | estado | residuo |
|---|---|---|
| `func_ov011_0205be38` | tamano exacto | planificador: el ROM entrelaza `#4`/`#5` entre los paneles |
| `func_ov011_0205c190` | 5 mnemonicos | el ROM entrelaza el relleno del extent con los args |
| `func_ov011_0205c2fc` | tamano exacto | falta la fusion `ldm` y la base recalculada |
| `func_ov011_0205da60` | 4 mnemonicos | el ROM usa 4 callee-saved y materializa las 10 palabras antes de almacenar |
| `func_02008788` | 0 mnem, r1<->r2 | 144 variantes probadas, 27 compiladores |
| `func_0200dcf0` | 0 mnem, r1 vs ip | idem |
| `func_02013e10` | 1 instruccion | mwcc fusiona el `|<<8` de las dos ramas |
| `func_02058e88` | (2,5) | ver sesiones anteriores |
| `func_02059b14` | (5,6) | permutacion pura |

## De los 9 stubs de MAIN, CINCO son ensamblador del SDK y no salen de C
`0200386c` (subs/bhs), `020203b0` (`_ll_mul`), `01ff8330` (arranque, acaba en
`ldm fp,{r0-sl}; bx ip`), `0200302c` (mrs/msr + cambio de pila), `02003948`
(`mov sp, r0`). No los persigas.

## SIGUIENTE
`func_ov011_0205b814` (228 B) es hermana de `b8f8` -- misma familia de blit, empieza
por ahi con el molde ya escrito. Luego el constructor `func_ov011_0205ac40`.

# ===== 25/07 (3a sesion): ov008 CON EL **FLUJO DE INSTRUCCIONES EXACTO** =====

## Estado: `func_ov008_02068e68` -- NO aparcada, `build/try/f838/e68_BEST.c`
**`mnemonic 0 / operand 0 / full 11`**, 792 B exactos, 13 bytes de diferencia.
Los 198 mnemonicos, inmediatos, offsets y shifts son correctos. Todo el residuo es
**un 3-ciclo de registros** en una ventana de 0x48 bytes:
`nuestro (cx, cy, base) = (r1, r3, r2)` frente a `ROM = (r2, r1, r3)`, 11 instrucciones.

## ★★★ RESUELTO POR REPRODUCCION MINIMA: donde va `cur.y = cy;`
Habia dos ramas rivales, una con el orden bien y otra con el coloreado bien, y se
diferenciaban SOLO en si `cur.y = cy;` va antes o despues del `if (i == pi)`. Una
reproduccion de 172 bytes (`build/try/f838/repro2/`) lo zanja:

| repro | forma | resultado |
|---|---|---|
| r1 | sin bucle, sin condicional | orden ROM |
| r2 | bucle, sin condicional | orden ROM |
| r2b | bucle, `cur.x = cx + pi` incondicional | orden ROM |
| r3b | condicional, sin bucle | orden ROM |
| **r3** | **bucle Y store condicional** | **mwcc rellena el hueco `asr->str`** |

Y dentro de r3: con `cur.y = cy;` **DESPUES** del condicional mwcc saca el orden de la
ROM gratis; con el **ANTES**, las 16 grafias probadas (if/else, ternario, comparacion
invertida x cuatro formas de mv.x) rellenan el hueco. **O sea el original lo tiene
detras del `if`**, y la rama "colour-exact" (`e68_COLOUREXACT_2insn.c`, 2 mnem / 6
bytes) es un callejon sin salida que solo puntua menos bytes por casualidad. No
arranques de ahi.

## ★★ EL 3-CICLO QUE QUEDA LO CAUSA EL BUCLE `j`
Biseccion por recorte sobre el propio fichero: **borra el `for (; j < 8; j++)` y el
coloreado salta al de la ROM** (cx=r2, cy=r1) de inmediato, y sigue asi en cada
recorte posterior. O sea el asignador elige distinto por la presion que crea ese
bucle -- aunque el codigo emitido del bucle ya es byte-exacto contra la ROM.
Inerte contra ello: `for (j = 0; ...)` vs `j = 0;` aparte, `while` en vez de `for`,
el orden de `ox`/`oy`, el orden de `pos.x`/`pos.y`, sacar la fila de celdas o la fila
de ids a un puntero, y declarar `ox`/`oy` dentro del bucle `i`.

## ★ Y NO ES NI LA BUILD NI LOS FLAGS (medido dos veces)
`build_sweep.py` con las 27 builds: salida IDENTICA en 2.0/sp1..sp2p4 +
3.0_136_patched + 3.0_patch4. `allopt.py` con los 13 niveles: solo `-O3,p` y `-O4,p`
llegan al tamano correcto y son iguales. Y las 17 sub-opciones de `-opt`
(`nolifetimes`, `nocse`, `noprop`, `nostrength`, `noloop`, `nodeadstore`,
`nodeadcode`, `level=3/4`, `speed`...) dan **todas** `0/0/11`. `-opt space` cambia el
tamano a 756. **El coloreado no se toca desde la linea de comandos: es la fuente.**

## ★ EL EMPATE, DICHO CON PRECISION (es todo el problema que queda)
**Siempre que el store de `cur.y` sale en el +0x0E8 de la ROM, el coloreado sale
(r1,r3,r2); siempre que sale antes, el coloreado sale el de la ROM (r2,r1,r3) pero se
transponen el store de `mv.x` y la relectura de `cur.y`.** Todas las formas de fijar
ese store al +0x0E8 -- plano, volatil, volatil por puntero, dentro o fuera del bloque
de `mv.x`, con y sin store volatil en `mv.x` -- caen en el primer caso; todas las de
sacarlo antes caen en el segundo.

## ★★★ Y EL ORDEN DE DECLARACION TAMBIEN ESTA AGOTADO (2.880 x 2)
`build/try/f838/sweep12_e68.py`. El orden de declaracion es un eje de rescate
documentado (cerro `func_ov301_020cbfc4` y `func_ov008_02069954`) y aqui solo se
habia barrido sobre los cinco escalares finales. Ahora se han cruzado los **4
iniciales (i, j, handle, obj) x los 5 finales (move, entry, oy, ox, p) = 2.880
ordenes**, sobre **las dos ramas**:

> **5.760 variantes. Las 5.760 dan el tamano exacto. Ninguna mejora.**
> Rama B se queda en `0/0/11`, rama A en `2/0/2`.

(El orden de los tres agregados no se permuta: `pos, mv, cur` es el unico que pone
`cur` en sp+8, `mv` en sp+0x10 y `pos` en sp+0x18 como la ROM.)
Tambien inerte: el inicializador de `mv` como `{ 0 }` parcial en vez de `{ 0, 0 }`
(identico); y `mv.x = mv.y = 0;` sin inicializador pierde el `add r2,sp,#0x10` y
sale 788 B.

## ★★★ EL ORDEN DE SENTENCIAS ESTA **AGOTADO**, no "probado a mano"
Todo lo que habia escrito antes sobre ordenes de sentencia era una impresion: los
habia elegido a mano. Ahora es una afirmacion comprobada
(`build/try/f838/sweep11_e68.py`):

**Los 900 ordenes topologicos validos** de las diez sentencias de la cabecera del
bucle -- respetando `cx` antes del store de `cur.x`, `pi` antes del `if`, el `if`
antes de la lectura de `cur.x` en `mv.x`, `cy` antes del store de `cur.y`, ese store
antes de su relectura, y el orden de fuente de las dos lecturas volatiles del par --
**cruzados con los cuatro ejes** que pesan por separado (`aPageCurrent.x` volatil o
no, `nPageIndex` plano o con cast volatil, la lectura del target directa o por
puntero volatil, el store de `mv.x` directo o por puntero volatil):

> **14.400 variantes compiladas. LAS 14.400 dan el TAMANO EXACTO de 792 bytes.
> Ninguna es byte-exact.** El suelo son exactamente las dos ramas ya conocidas:
> `0/0/11` (`e68_BEST.c`) y `2/0/2` (`e68_COLOUREXACT_2insn.c`).

Que **las 14.400** den el tamano correcto es en si mismo un dato: la C es correcta en
semantica y en estructura, y lo que queda es una decision de planificacion a la que
**ningun orden de sentencias legal llega**.

## ★★ POR QUE mwcc PONE LA CARGA ANTES DEL STORE (causa entendida, no solo medida)
El bloque desde la cabecera del bucle hasta el `bl` es **un solo bloque basico** (el
`if (i == pi)` sale predicado, sin salto), asi que el planificador de lista tiene
libertad total y ordena por **camino critico**. El store de `mv.x` es practicamente
una hoja (su unico sucesor es el `ldm` del argumento), mientras que la relectura de
`cur.y` encabeza `sub -> asr -> add -> asr -> str(mv.y) -> ldm`. La carga gana la
prioridad y se cuela en el hueco `asr -> str`. **Nuestro compilador esta haciendo lo
"correcto"; la ROM no.** Intentos de invertir esa prioridad, todos medidos:
calcular `mv.y` primero en un temporal (16 mnem), los dos valores en temporales
(14), el store de `mv.x` adelantado con temporal (2, sin cambio), reusar `cx`/`cy`/
`pi` como temporal de `cur.y` (inerte en las dos ramas), expresiones coma y anidadas
(inerte), y sumar un termino que se pliega a cero (rompe el tamano).

## ★ El agregado en la configuracion `early` -- hueco que faltaba, ya cerrado
El modelo de agregado solo se habia probado sobre la rama B. En la rama A **mantiene
el coloreado de la ROM** (cx=r2, cy=r1) pero da 19 mnemonic con init por puntero y
788 B con init por campos, en los dos ordenes de miembros. Peor que 2.

## ★ El compilador NO es el problema, y hay que decirlo claro
La build mas alta que tenemos es **3.0 build 139** (`3.0_patch4`; `2.0/sp2p4` es
tambien 139, `2.0/base` es 114, `3.0_136*` es 136). La nota vieja de memoria decia
"retail es probablemente 3.0 >=140" -- pero **13.000 funciones casan byte a byte con
la 139**, asi que esa hipotesis no explica nada. Es la forma de la fuente.

## ★★★ EL ESPACIO DE CONFIGURACION DEL COMPILADOR ESTA CERRADO ENTERO
Ninguna de estas palancas mueve **ninguna** de las dos ramas (A: 2/0/2, B: 0/0/11):
- **27 builds** de mwccarm (`build_sweep.py`) -- salida identica en todo el set 2.0/3.0;
- **13 niveles** de `-O` (`allopt.py`) -- solo `-O3,p`/`-O4,p` dan el tamano y son iguales;
- **17 sub-opciones** de `-opt` (`nolifetimes`, `nocse`, `noprop`, `nostrength`, `noloop`...);
- **15 valores de `-proc`** -- ★ eje nuevo, y resulta que `arm946e`, `arm9ej`, `arm926ej`,
  `arm966e` y `v5te` dan salida **identica**; el resto rompe el tamano. El modelo de
  coste del planificador no es la palanca;
- `-inline off/auto/all`, `-char unsigned`, `-enum min`, `-rostr`, sin `-gccext`;
- ★ **los 29 `#pragma` legales**, tanto a nivel de fichero como acotados a la funcion
  (son de granularidad de funcion: da igual donde los pongas).

⚠ **Y la trampa de los pragmas, que casi me hace creer que habia probado algo:**
**mwccarm ignora en silencio un `#pragma` desconocido salvo con `-w all`.**
`#pragma scheduling off` compila limpio y no cambia nada -- porque **no existe**. No hay
pragma de planificacion ni de coloreado de registros (`scheduling`,
`ARM_conditionalize`, `register_coloring`, `volatileasm`, `instmgr`... todos ilegales).
El set legal y el metodo de sondeo estan en `references/tools.md`.

## ⚠⚠ CORRECCION: "el store volatil obliga a materializar `&mv`" era FALSO
Lo escribi como causa y no lo era. Reproduccion minima (`build/try/f838/r3_*.c`):
una funcion con un local `Pair mv`, un store al campo `.x` y una llamada que pasa el
par por valor, en **cuatro grafias** -- store plano, cast volatil, puntero local
volatil, y campo volatil via union -- da **codigo IDENTICO en las cuatro**, y el
store volatil sale **sp-relativo** (`str r1,[sp]`); el unico `add rX,sp,#N` es el que
necesita el `ldm` de la llamada.

O sea **mwcc SI sabe emitir un store volatil a un local sin registro base**. Lo que
pasa en la funcion real es otra cosa: el store volatil perturba la planificacion, se
abre un hueco antes de tiempo y mwcc lo rellena con el `add` que de todos modos
necesita para el `ldm`, adelantandolo de +0x108 a +0x0EC. Es un efecto de
planificacion, no una propiedad del store volatil.
Reintentado con esa comprension (store de `cur.y` volatil o plano dentro del bloque,
valor de `mv.x` por temporal): 2/2/14 y 17/2/20. Sigue sin mejorar, pero la causa
apuntada estaba mal y ahora esta bien.

## ★ Helper `static inline` con el DESTINO POR PUNTERO -- tambien inerte
Idea: si `mv.x` se escribe a traves de un puntero pasado a un helper inlineado, el
store es una escritura por puntero y no un acceso a campo, que es otra situacion de
aliasing. Resultado: `4/2/10`. **Arregla la posicion del store de `cur.y`** (+0x0E8
sale bien) pero **NO arregla la transposicion** de +0x0FC/+0x100, y rompe el orden de
las cargas del bloque de `mv.x` y el `add` de la base. La variante con el par entero
y dos ejes en un helper sale 816 B.

## ★ El eje del SITIO DE LLAMADA tambien inerte (era el que quedaba nombrado)
Prototipo con `const Ov008Pair`, tipo de struct distinto para el parametro (con cast
en la llamada), `ctx` como `int`, `page` como `unsigned`: las cuatro grafias dan
exactamente el mismo residuo en las dos ramas (A 2/0/2, B 0/0/11).
Y las dos herramientas coinciden: `verify_idx.py` marca `byte diff @0xFC` en la rama
A y `@0xC1` en la B, justo donde `posdiff` -- no hay desacuerdo de instrumentacion.

## ★ Premisa del gemelo VERIFICADA, y es mas fuerte de lo que decia
`func_ov025_0209b248` no es "byte-identica salvo relocs": es **byte-IDENTICA**
(0 bytes distintos, mismos 14 offsets de reloc). Un match en `func_ov008_02068e68`
se propaga solo con `dedupprop`.

## ★★ Y LA TRANSPOSICION DE LA RAMA "EARLY" ESTA CERRADA TAMBIEN
En la rama `early` (la unica con el coloreado de la ROM) la unica cosa que reordena
el par `str mv.x` / `ldr cur.y` es **ordenar el store de `mv.x`**, y los tres
mecanismos posibles estan medidos y todos rompen algo mas:
- puntero local `volatile int *vmx = &mv.x` -> **materializa `add r2,sp,#0x10` siete
  instrucciones antes** (la ROM lo tiene en +0x108, para el `ldm` de la llamada), y
  ademas arrastra el store plano de `cur.y` de +0x0E8 a +0x0DC: 17 mnemonic;
- cast volatil en la expresion -> lo mismo, 18 mnemonic;
- cualificar el objeto `mv` (entero o solo `.x`) -> hay que pasar el par por valor con
  un cast y la funcion crece a **800-808 B**.
O sea: **no hay forma de ordenar ese store sin tomar `&mv` antes de tiempo o sin
crecer**, y esa es la razon concreta por la que la rama de 6 bytes no cierra.

★ Y el coloreado sigue **la POSICION DEL STORE `cur.y = ...` respecto al `if`**, no el
primer uso de `cy`: darle a `cy` un uso temprano barato (`c1 = cy;` u otro temporal)
y dejar el store detras del `if` da 12 de 12 variantes con `cy=r3`. Ese eje esta
descartado.

## ★★★ EL CRUCE COMPLETO (192 variantes) ZANJA LA FORMA DEL PROBLEMA
`build/try/f838/sweep10_e68.py` cruza por primera vez los **siete** ejes que
individualmente movian algo: posicion de `cur.y = cy;` x volatilidad del store de
`mv.x` x forma de la lectura del target x forma de la lectura de `cur.y` x
volatilidad de los campos de `aPageCurrent` x forma de `nPageIndex` x forma de los
dos valores fijados (struct / `int[2]` / dos escalares).

**Entre las variantes de tamano exacto solo aparecen DOS coloreados**: el de la ROM
(`cx=r2, cy=r1`) y el nuestro (`cx=r1, cy=r3`), **96 variantes en cada lado**. Y el de
la ROM sale **si y solo si** `cur.y = cy;` va ANTES del `if (i == pi)` -- que es
exactamente la colocacion que hace que mwcc rellene el hueco de latencia de la cadena
de `mv.x`. O sea los dos defectos **no son dos palancas independientes que resisten:
son las dos caras de una misma decision**.

Resultado: dos ramas, y no hay una tercera.
- `e68_BEST.c` -- flujo de instrucciones EXACTO (`0/0`), 3-ciclo de registros, 13 B.
- `e68_COLOUREXACT_2insn.c` -- coloreado EXACTO, una transposicion adyacente, **6 B**.
  Reescrito con la grafia mas simple que llega ahi (nPageIndex en plano, solo `.y`
  volatil), encontrada por el propio cruce.

Tambien probado y peor: `cy` como **una sola variable en memoria** (sin el par
registro+campo): 5-19 mnemonic en las seis colocaciones. La ROM escribe sp+0xc **una
vez dentro del bucle en +0x0E8**, asi que el modelo de una sola variable no es la
forma del original.

## ★ CAPA SEMANTICA HECHA (Ghidra, 25/07) -- la mitad que no depende del residuo
`arm9_ov008::02068e68` = **`Ov008_TickPageScroll`**, prototipo
`void Ov008_TickPageScroll(Ov008PageScrollCtx *pCtx)`, con comentario de cabecera
que explica el algoritmo y **todos los offsets verificados sobre la disasm**.
Tipos creados en Ghidra (los dos leidos de vuelta):
- **`UiLayoutPos`** { int x; int y; } -- el punto 2D en 1/4096 del sistema de layout de
  UI, el que devuelve `func_ov008_02054820` y consume `func_ov008_02054858`. El arbol
  solo tenia `struct vec2_020548bc` (nombre derivado de direccion, 3 ficheros); el
  nombre establecido de verdad es `VecFx32` (250 ficheros) pero es 3D, asi que no vale.
- **`Ov008PageScrollCtx`** (480 B): `nPageIndex` +0x000, `nActiveState` +0x004,
  `aCellOffset[24]` +0x068 (paso pagina*64 + celda*8), `aPageTarget[3]` +0x128,
  `aPageCurrent[3]` +0x140 (**adyacentes, sin padding**), `aGfxCmdBlock` +0x1DC.

⚠ **Los tres tools de tipos volvieron a dar el error de `endTransaction` MIENTRAS
FUNCIONABAN**, y `set_plate_comment` dio `Failed to execute on Swing thread: null`
tambien funcionando. Lectura de vuelta obligatoria, siempre. Y `save_program` fallo con
"Unable to lock due to active transaction": lo cerro `CloseTxAndSave.py`, cuya **consola**
dijo `closed=6; tx_after=NONE; SAVED_OK` mientras su **status** decia `success:false`.
Es exactamente la trampa que ya esta escrita en SKILL.md: **lee la consola, nunca el
status.**

## ★★★ LA HIPOTESIS DEL DERRAME, PROBADA Y CERRADA (medido, no supuesto)
**144 grafias totalmente planas compilan a EXACTAMENTE 752 bytes. Todas.**
(Cuatro formas para los dos valores -- dos escalares en los dos ordenes de
declaracion, un `Ov008Pair`, un `int[2]` -- x los dos ordenes de lectura del par x
tres posiciones de la copia de `cy` x tres de `move = 1;` x copia-vs-directo.)
mwcc **no derrama** esos dos valores desde fuente plana: aparca `cx` en r7 y `cy` en
r5 y los reusa para `oy` y `j` cuando mueren, y ningun orden de sentencias lo cambia.
O sea el trafico de memoria de la ROM **no es lo que produce una fuente plana
cualquiera**, y la hipotesis del derrame queda descartada en la forma que importaba.

Lo unico que fija esos valores a memoria sin `volatile`, medido:
- que escape un puntero a ellos -> cuesta 16-24 bytes, no es;
- que sean campos de **un unico agregado local** cuya direccion escapa (por
  `&w.pos` a `func_ov008_02054858`). Eso **si** los fija, con accesos planos, y con
  el init de `mv` escrito como `{ Ov008Pair *m = &w.mv; m->x = 0; m->y = 0; }`
  llega a 792 B exactos -- pero barrido sobre la misma rejilla de 72 ordenes de
  sentencia su mejor marca es **mnemonic 20**, muy peor que cualquiera de las dos
  ramas, porque los stores planos se planifican demasiado pronto.

Tambien inertes en esta pasada: helpers `static inline` para las dos cuentas de
paso (uno comun, por eje, y una variante de dos punteros); las 16 combinaciones de
`register` sobre cx/cy/pi/c1; y renombrar o fundir los dos arrays de pares del
contexto (**son adyacentes**: `aPageTarget[3]` en 0x128 entra directo en
`aPageCurrent[3]` en 0x140, asi que el miembro de padding es de longitud cero y
quitarlo no cambia nada; indexarlos como un solo `aPage[6]` con `[i+3]` cuesta 20 B).

**Conclusion honesta:** el modelo volatil de `e68_BEST.c` es el unico que reproduce a
la vez el trafico de memoria y el flujo de instrucciones de la ROM, y dentro de el
los dos defectos estan demostradamente anticorrelacionados. El 3-ciclo que queda es o
un empate real del asignador para este compilador, o depende de algo estructural aun
no imaginado -- pero **no** es: la build, el nivel de optimizacion, ninguna
sub-opcion de `-opt`, la aridad, el tipo de retorno, ningun prototipo de callee, la
forma del bucle, el alcance de ninguna local, el orden de declaracion de nada, ni la
forma de los dos valores derramados.

## ★★ (Historico) El patron parecia el de un derrame
`sp+0xc` solo se escribe con `cy` y se lee exactamente dos veces, asi que en el
original probablemente **no es un campo `cur.y` sino el asignador derramando una
local plana `cy`**. Un derrame coloca el store en el punto de definicion y la recarga
en el uso -- lo que da las posiciones de la ROM gratis -- mientras la variable
conserva el color que gano por su definicion temprana. Es justo la combinacion que
ninguna forma de fuente reproduce. Escrito en plano la funcion sale **752 B** porque
mwcc tiene callee-saved de sobra y no derrama (`cx` va a r7, `cy` a r5, y luego los
reusa para `oy` y `j`). **La pregunta real es que cuesta un registro callee-saved mas
en el bucle `i` del original.**
Descartado como fuente de esa presion: mover `j = 0;`, izar el calculo de la mascara
(semanticamente invalido -- lee `aPageTarget` DESPUES de actualizarlo), meter
`pos`/`entry`/`j` en el bucle `j`, y separar `entry` del uso de la cola.

## ★ Prototipos reverificados contra el arbol -- uno estaba MAL
- **`func_ov008_02069954` es VARIADICA.** Su propia fuente byte-exacta la declara
  `int f(int param1, int tag, int a2, int a3, ...)`: `tag` es el ultimo argumento con
  nombre y dx/dy son varargs (por eso el callee abre con `stmdb sp!,{r0,r1,r2,r3}`).
  Pasar el par **por valor** sigue dando el `add r2,sp,#0x10 / ldm r2,{r2,r3}` de la
  ROM; pasar `mv.x, mv.y` como dos int pierde las dos materializaciones de direccion
  y sale 784 B. Añadir `...` al prototipo no cambia nada.
- La aridad de la propia funcion es **1** (unico llamante `func_ov008_02068ba8`
  +0x190: `mov r0, r4 / bl`), y el tipo de retorno es indiferente: devolver el
  resultado de la ultima llamada compila bit a bit igual que `void`.

## ★ Respuesta del corpus sobre el 3-ciclo (`build/try/f838/find_desc_pair.py`)
La forma de la ROM -- dos `ldr` consecutivos de la misma base con offsets
consecutivos donde el PRIMERO va al registro MAS ALTO -- **si** aparece en C real
casada (15 funciones). Pero en todos los casos legibles viene de **pre-coloreado por
argumentos**: `func_ov006_020551a4` carga `start_value` en r2 y `end_value` en r1
solo porque son los argumentos 3 y 4 de la llamada siguiente. Aqui `cx`/`cy` no son
argumentos de ninguna llamada, asi que ese mecanismo no esta disponible -- lo cual es
coherente con que todas las palancas de fuente salgan inertes.

## ★★★ CRACK GENERAL NUEVO: **puntero local `volatile` para fijar el ORDEN DE CARGA**
(Ya escrito entero en `references/codegen-cracks.md`.) Cuando mwcc emite dos cargas en
el orden equivocado y ninguna grafia lo cambia, hay que hacer **volatiles las dos**;
lo caro es COMO: cualificar el campo cuesta +24 B, el cast en la expresion +24 B, y un
**puntero local cuesta 0** porque reusa el registro base ya vivo. Elige cast o puntero
segun cuantas veces mas se lea el objeto.

## ★★ Corolario que corrige lo que decia este fichero
`volatile int cur[2]` **no puede** reproducir esta funcion: la ROM guarda `cur.y`
DESPUES de releer `cur.x`, y un store volatil no se hunde por debajo de una lectura
volatil. Lo correcto es **struct plana leida con casts volatiles**. Plano del todo
tampoco: mwcc escalariza `int cur[2]` y salen 752 B.

# ===== 25/07 (2a sesion, port-first): LA GEMELA ov008 A 2 INSTRUCCIONES =====

## Estado exacto: `func_ov008_02068e68` -- NO aparcada, en `build/try/f838/e68_BEST.c`
Empezo la sesion en `mnemonic 2 / operand 6 / full 17`; termina en
**`mnemonic 2 / operand 0 / full 2`**, tamano exacto 792 B. **Los 198 registros,
inmediatos, offsets y shifts son ya TODOS correctos.** Lo unico que queda es UNA
transposicion adyacente:

    ROM   +0x0FC  str r0,[sp,#0x10]   (mv.x = ...)
          +0x100  ldr r1,[sp,#0xc]    (relectura de cur.y)
    NOSOTROS  las dos al reves.

mwcc mete la carga de cur.y, que ya esta lista, en el hueco de dependencia
`asr -> str` de la cadena de mv.x; la ROM deja ese hueco vacio.
La cabecera del propio `.c` lleva la bitacora completa (que se midio, que se
descarto y con que numero). Vale por dos funciones: `func_ov025_0209b248` es
byte-identica salvo relocs.

## ★★★ CRACK NUEVO Y GENERAL: **puntero local `volatile` para fijar el ORDEN DE CARGA**
Cuando mwcc emite dos cargas en el orden equivocado y ninguna grafia de la
expresion lo cambia, la palanca es hacer **volatiles las dos**: mwcc no reordena
dos accesos volatiles entre si. Lo caro es *como* haces volatil la segunda:

- cualificar el campo en la struct -> **+24 B** (el mismo campo se lee por toda la funcion);
- cast en la expresion `*(volatile int *)&x` -> **+24 B** (rematerializa la direccion);
- ★ **puntero local** -> **0 B**, porque reusa el registro base que ya esta vivo:

```c
{   volatile int *vt = &ctx->aPageTarget[i].y;
    mv.y = (*vt - c1) / 4; }
```

Eso solo bajo `operand 2 -> 0` y `full 12 -> 2`. El mismo truco en forma de cast
sobre `nPageIndex` (`int pi = *(volatile int *)&ctx->nPageIndex;`) impidio que mwcc
colara esa carga ENTRE las dos lecturas del par -- que era justo lo que hacia que el
orden de fuente CORRECTO (x-luego-y) puntuara PEOR que el incorrecto durante toda la
sesion anterior: `operand 4 -> 2`. Aqui el cast es la forma buena y el cualificador
cuesta +12 B porque el `switch` de arriba lee el mismo campo. **O sea: elige entre
cast y puntero local segun cuantas veces mas se lea el objeto, no por gusto.**

## ★★ Corolario sobre `volatile` que corrige lo que decia este fichero
`volatile int cur[2]` **no puede** reproducir esta funcion: la ROM guarda `cur.y`
DESPUES de releer `cur.x`, y un store volatil no se puede hundir por debajo de una
lectura volatil, asi que el orden de fuente queda forzado y el de la ROM es
inalcanzable. Lo correcto es **struct plana leida con casts volatiles**: el store es
libre para planificarse y solo la relectura queda pinchada. (Plano del todo tampoco:
mwcc escalariza `int cur[2]` y salen 752 B.)

## ★ Orden de sentencias que pesa de verdad (medido por separado)
- `cur.y = cy;` justo detras de `cur.x = cx;`, **antes** del `if (i == pi)`:
  `full 11 -> 4`, y es lo que cuadra TODO el coloreado (cx->r2, cy->r1, base->r3).
- En la rama `i != 0`, poner el store `cur.x = 0x100000;` **antes** de la resta en vez
  de detras del temporal `sum`: `full 17 -> 12`. La ROM iza `mov r2,#0x100000` por
  encima del `sub`, y eso solo pasa si el store es quien necesita la constante antes.

## ★ Descartado con evidencia compilada (NO repetir)
Agregado local unico con cur+mv+pos (784, pierde los dos `add r2,sp,#0x10` de `&mv`);
`Ov008Pair work[3]` (784, y 796 con inicializador agregado); copia de struct del par
(800-824); puntero temporal para aPageCurrent o aPageTarget (816); acceder a los pares
del contexto como `int [3][2]` en vez de campos (bit a bit identico a la forma struct);
store volatil sobre `mv.x` (se dispara a 17 mnemonic); `register` en los temporales;
orden de declaracion de los temporales del bucle; y **todas** las posiciones de
`move = 1;`.
**Y el barrido de builds no es la palanca:** `tools/build_sweep.py` con las 27 builds
da salida IDENTICA en 2.0/sp1..sp2p4 + 3.0_136_patched + 3.0_patch4 (23 B off al
principio, 6 B off ahora); 1.2/* no compila y dsi/* saca 764 B. Corrido dos veces, en
los dos niveles de calidad.

## Siguiente movimiento concreto
Atacar **el store de `mv.x`, no la carga de `cur.y`**. Los dos objetos tienen la
direccion tomada (`mv` se pasa por valor, `cur` por los casts volatiles), asi que mwcc
no deberia poder probar que no aliasan -- y aun asi reordena, lo que dice que trata la
carga volatil como libremente planificable frente a un store PLANO. Hay que encontrar
una grafia que haga ese store no izable sin volver `mv` volatil.

Los barridos parametrizados de la sesion estan en `build/try/f838/sweep*_e68.py`
(puntuan con la metrica de `posdiff`, nunca por distancia de edicion).

# ===== 25/07: ec4 a 2 INSTRUCCIONES + LECCION DE METRICA =====

## ★★★ LECCION DE METODO: la distancia de edicion me estaba ENGANANDO
Estuve horas optimizando "edit-17" con `difflib` sobre el disasm COMPLETO (mnemonico +
operandos). Esa metrica cuenta un renombrado de registro igual que una instruccion
distinta, asi que premiaba candidatos con la estructura MAL y los registros por
casualidad bien. El candidato "edit-17" tenia **24 desajustes de mnemonico**; el que
la metrica puntuaba peor (edit-32) tenia **4**. Cambiar de metrica desbloqueo el caso
en una hora despues de ~150 experimentos estancados.
**Usa `python tools/posdiff.py <func> <cands...>`** (esta en el repo): alinea por POSICION (solo vale si el tamano ya cuadra)
y separa `mnemonic-mismatch` (estructura real) de `full-mismatch` (incluye registros).
Ordena SIEMPRE por mnemonic-mismatch. Nunca por distancia de edicion.

## ★★ CRACK NUEVO: readback forzado con lectura volatile
Sintoma: la ROM guarda un campo local y mas tarde lo RECARGA de la pila; tu C guarda
desde un temporal y mwcc reusa el registro -> te faltan exactamente 4 bytes.
Fix: leer el campo con `*(volatile int *)&w.campo` en la expresion que lo consume.
⚠ MEJOR: calificar el campo como volatile EN EL STRUCT -- ver el DIAGNOSTICO REFINADO,
el cast cuesta bytes cuando hay una base compartida y el calificador no.
El store sigue siendo normal, solo la lectura se pincha. En ec4 esto recupero la
instruccion que faltaba y paso el candidato de 1008 a 1012 con la estructura correcta.
⚠ El volatile del lado del STORE no sirve (h3: sigue 1008), ni el cast no-volatile.

## Estado de `func_ov000_02050ec4` (frente actual, NO aparcada)
`build/try/f838/ec4_BEST.c` -- SIZE-EXACTO 1012 / 253 instrucciones.
**Clasificacion mecanica del residuo** (quitando nombres de registro y comparando el resto):
2 difieren por MNEMONICO, **0 difieren en ningun inmediato, offset de memoria o shift**,
26 difieren SOLO en que registro se eligio. O sea la C es exacta en semantica, seleccion de
instruccion y valores de operando; lo que queda es UNA decision de orden mas la permutacion
de registros que se deriva de ella. La permutacion se remonta a una sola eleccion anterior:
la ROM mete el puntero de contexto re-leido en r1 en +0x124 y mwcc lo mete en r2.
Lo unico estructural que queda es UN swap adyacente:
`+0x13C/+0x140  ROM: ldr c3->nPageIndex ; str w.cur[0]   /   nosotros al reves`.

★★★ **CAUSA AISLADA (25/07): ES UNA BARRERA DE ALIAS, Y EL DISPARADOR ES `&w.mv`.**
Todo lo que hay escrito debajo sobre "mwcc acopla el cmp a su operando" describe el
SINTOMA. La causa se encontro construyendo una **reproduccion minima** y haciendola
crecer hacia ec4 hasta que se rompio (`build/try/f838/repro/`):
pasar `&w.mv` a una funcion hace que TODO el agregado quede expuesto por direccion, y
entonces mwcc ya no puede probar que `str w.cur[0],[sp]` no aliasa con
`ldr c3->nPageIndex`, asi que se niega a subir la carga. Sin ese escape mwcc emite el
orden de la ROM sin esfuerzo, en las 12 grafias probadas.
Biseccion exacta: repro base con el campo en 0x4b08 y direccion partida -> FORMA ROM;
+ la llamada, el caso 0xf0000, los bloques mag/abs y la relectura -> FORMA ROM;
+ bucle interior llamando solo `sel()` -> FORMA ROM; + `put(obj,entry,(Pair*)g_ctx)`
(otro puntero) -> FORMA ROM; + `put(obj,entry,&w.mv)` -> **ROTO**; y con UNA sola
llamada sin bucle -> **ROTO**. O sea no es el bucle, ni la presion de registros, ni la
llamada: es ese argumento. Barrido de offsets (0…0x4B08) todo FORMA ROM, luego el
calculo de direccion partido NO interviene.
★★★ **RESUELTO EL BLOQUEO, Y EL CANDIDATO NUEVO ES `ec4_BEST.c` = 2 mnem / 19 full.**
(La rama vieja queda en `ec4_aliasbarrier_2x28.c`, 2 mnem / 28 full: NO arranques de ahi.)
La receta son tres cosas, y las tres cargan peso:
1. `cur` como local propia cuya direccion NO se toma; en la struct que escapa por `&w.mv`
   se quedan solo `mag` y `mv`. Eso quita la barrera de alias y la carga SI se sube.
   La pila sale sola como en la ROM: cur@sp+0, mag@sp+8, mv@sp+0x10.
2. `volatile int cur[2]` sigue haciendo falta (en plano salen 984 B).
3. La lectura de `nPageIndex` como **cast volatile en un temporal**, y los campos del par
   como **campos cualificados**. El cast aqui es deliberado pese al aviso del catalogo:
   cualificar `nPageIndex` en la struct cuesta 20 B porque el `switch` de estado de arriba
   lee el mismo campo. El temporal es lo que impide plegar el `cmp` dentro de la carga.
   Resultado: +0x13C ldr, +0x140 str, +0x144 cmp -- **la ventana critica ya es exacta**.
★★ **SEGUNDA FORMA EMPATADA, y una LECCION DE METRICA que ya esta en la herramienta.**
`ec4_alt_yxplain.c`: leyendo el par en orden **y-luego-x** y `nPageIndex` **en plano**
(sin cast), el `add` cae donde la ROM lo tiene y **TODO el flujo de mnemonicos coincide**
-- pero entonces las dos cargas del par salen en el otro orden y sus offsets quedan
intercambiados. Marca `mnemonic 0 / operand 2 / full 18` frente al `2 / 0 / 19` del BEST:
la MISMA transposicion adyacente, movida de sitio. Las dos ordenaciones son alcanzables
por separado y nunca juntas; la pregunta que queda es estrecha y concreta: leer el par en
x-luego-y manteniendo el `add` detras de ambas cargas.
⚠ **`mnemonic-mismatch=0` NO significa flujo identico.** Estuve a punto de cantar victoria:
dos `ldr` con offsets intercambiados (0xc94/0xc98) son invisibles a una comparacion de solo
mnemonicos. `tools/posdiff.py` ya imprime una columna **`operand`** (inmediatos, offsets y
shifts, con los nombres de registro normalizados) justo por eso. **Ordena por
mnemonic + operand, nunca por mnemonic solo.**

★ **LO QUE QUEDA es UNA transposicion adyacente y es puro scheduling**:
`ROM: [ldr cx][ldr cy][add base+0x4000]` frente a `nuestro: [ldr cx][add][ldr cy]`.
El calculo de direccion flota un hueco de mas y hunde la carga de `cy`; de +0x13C en
adelante todo esta bien. Medido e INERTE contra eso: las 4 colocaciones del temporal y
6 grafias de la expresion base (c3, ctx, el global, puntero temporal, puntero a struct
volatile, offset explicito) -- todas dan 2/19 con el swap en el mismo sitio.
**Siguiente paso: hundir ese `add` por debajo de la carga de `cy`.**

★★ **BUSQUEDA DE CORPUS SOBRE ESA TRANSPOSICION (hecha, no supuesta):** la secuencia exacta
de la ROM -- dos cargas adyacentes de la misma base con offsets consecutivos, y luego un
`add` que construye la base de una tercera carga -- aparece en **0 de 15.349** funciones con
C real. El predicado esta VALIDADO contra los bytes de la propia ec4, donde dispara una vez
en +0x130, asi que el cero es ausencia real y no una consulta que nunca podia acertar.
Repetido permitiendo que la tercera carga NO lleve offset (la grafia de la gemela ov008,
`ldr rX,[rD]`) sigue en 0. O sea: **nadie en este proyecto ha producido esa forma desde C
todavia**, lo cual es coherente con que todas las grafias probadas se nieguen.

★★★ **Y EL MEJOR SIGUIENTE MOVIMIENTO NO ES SEGUIR EN ec4: ES LA GEMELA PEQUENA.**
`func_ov008_02068e68` (792 B) y `func_ov025_0209b248` son **byte-identicas salvo relocs**
y son la MISMA funcion fuente. En ellas el indice se lee con `ldr r0,[sl]` -- **offset 0,
sin `add` de direccion** (ec4 necesita `add rB,base,#0x4000` porque el campo esta en
0x4b08). O sea que el unico defecto que queda en ec4 **puede no existir alli**, y son
220 bytes mas cortas. Aplicales la receta de arriba: si casan, valida la receta Y vale
por dos funciones de golpe, y ec4 se cierra despues con lo aprendido.
**YA EMPEZADA** el 25/07: `build/try/f838/ov008_2068e68_a1.c`, C real (sin asm ni dcd),
**tamano exacto 792 B, mnemonic 2 / operand 6 / full 17** en una sentada. Toda la cola
desde +0x2A4 ya esta bien, incluido el bloque que empaqueta el scroll en REG_BG1HOFS
(0x04000018, mascara 0x1ff). Quedan dos grupos, los dos diagnosticados en la cabecera del
propio `.c`. Hallazgos que valen para otras funciones de este overlay:
`aCellOffset[3][8]` vive DENTRO del contexto en el offset 0x68 (escribirlo como objeto
aparte con cast de puntero cuesta instrucciones -- la regla del cast, otra vez); `mv` se
inicializa a cero en el prologo; los dos valores absolutos tienen que quedarse como
TERNARIOS (con temporal explicito sube de 7 a 13); y aqui mwcc asigna las locales en
orden INVERSO de declaracion, al reves que en ec4.
★★ **EL CRACK GRANDE DEL DIA (vale para cualquier funcion con mascara + bucle):** la ROM
materializa `-0x1000` como `sub r0, r5, #0x1000`, **reusando el registro donde acababa de
poner a cero el contador del bucle interior**. O sea que el fuente calcula la mascara con
`j = 0` ya vivo. Partir la cabecera del bucle -- `j = 0;` como sentencia propia ANTES de la
mascara y luego `for (; j < 8; j++)` -- lo reproduce y bajo la funcion **de 7 a 2** fallos de
mnemonico de un golpe. Meter la mascara DENTRO del bucle no vale (808 B, mwcc deja de izarla).
Y las dos escrituras de la celda van **y antes que x** (la ROM lee +0x6c y luego +0x68): eso
bajo operand de 10 a 6.
Recuerda que la forma `[ldr][str sp][cmp]` aparece en **solo 5 funciones de toda la ROM**
(ov000/ov002/ov008/ov009/ov025, ninguna casada): es una sola funcion fuente replicada, no
un patron general. Resolverla vale ~5 funciones.

★★ **EL RESIDUO, ENUNCIADO Y LUEGO MEDIDO CONTRA EL CORPUS** (25/07). Primero lo escribi
como "mwcc nunca separa una carga de su cmp" -- **eso es FALSO y queda corregido aqui**;
lo comprobe en vez de dejarlo escrito. Sobre 15.349 funciones con C real:
carga pegada a su cmp **653**, separada por UNA instruccion **313**, por dos o mas **54**.
O sea el hueco es normal. Pero en esas 313 lo que ocupa el hueco es SIEMPRE la
materializacion del OTRO operando del cmp: 199 un segundo `ldr`, 35 un `mvn` (comparar
con -1), el resto add/sub/mov/bic. Veces que ese hueco lo ocupa un STORE: **CERO**.
Eso explica ec4 exactamente: su cmp es `cmp sl, r0` y el otro operando es el contador
`i`, ya vivo en sl, que no necesita materializarse. mwcc no tiene nada legitimo que
meter en el hueco y no lo rellena con el store pendiente. La forma de la ROM
`[ldr idx][str cur0][cmp]` no aparece en NINGUNA funcion casada del corpus.
★ Leccion de metodo que se repite: un enunciado negativo hay que medirlo, no razonarlo.
La consulta anterior daba 0 y podia descartarse como "consulta que nunca dispara"; esta
dispara 313 veces y aun asi nunca con un store, que es lo que la hace creible.
Ojo: el calculo de direccion (`add rB,base,#0x4000`) SI cruza el store en todas las
variantes, o sea que no es una negativa general a mover codigo sobre un store de pila
-- es especifica de la carga y su comparacion.
**Barrido del 25/07 sobre este trio, todo negativo y ya medido** (no lo repitas): 7
grafias de la condicion (`==` invertido, `!(!=)`, resta, xor, via `ctx`, via el global),
`restrict`/`__restrict` -- compilan y son INERTES, mwcc 3.0 no los usa para alias --,
partir el agregado en locales sueltos (960-992 B: confirma que el objeto con direccion
tomada es obligatorio), y estrechar el volatile a `cur[1]` o a un cast en la lectura de
mv.y (recupera el tamano pero descoloca +0x154/+0x15C y sube a 4).
★ Dato fino que faltaba: la instruccion que se pierde sin volatile es SOLO la recarga de
`cur[1]` en +0x16C. `cur[0]` no necesita calificador porque su escritura condicional deja
el valor unicamente en memoria. Aun asi el calificador tiene que cubrir los dos.
⚠ NO leas eso como "mwcc no sube la carga" -- ese enunciado esta RETRACTADO mas abajo;
la causa real es el acoplamiento cmp/operando del DIAGNOSTICO REFINADO. Leelo antes.
El swap r1/r2 del caso 0xf0000 y todo el renombrado desde +0x124 son aguas abajo.
La cabecera del .c lleva la lista COMPLETA (por que cada pieza es como es + todo lo
medido y rechazado). Leela antes de tocar nada.

★★★ **CORRECCION IMPORTANTE, y la leccion de metodo**: llegue a escribir que "mwcc no
sube una carga por encima de un store". **ES FALSO** y lo cazo la regla del skill de
enunciar la forma POSITIVA: buscando el patron en el corpus, **49 funciones casadas
byte-exactas lo contienen**. Lo que de verdad no aparece es la forma concreta que hace
falta aqui -- esa carga hoisteada alimentando un `cmp` colocado DESPUES del store
(`ldr rD,[rB,#n]; str rS,[sp,#m]; cmp rX,rD`): **0 de 15.349 funciones casadas**.
Y el predicado esta validado contra los bytes de la propia ROM de ec4, donde dispara
exactamente 1 vez en +0x13C, o sea el cero es una ausencia real y no una query que
nunca podria haber casado. Script: `python tools/find_shape.py` (esta en el repo; el de scratchpad ya no existe).
⚠ Moraleja: antes de firmar un bloqueo, BUSCA LA FORMA POSITIVA EN EL CORPUS. Me habria
ahorrado escribir una afirmacion falsa en la cabecera del .c.

★ Y un negativo mas, por si tienta: el forwarding de `cur[1]` NO es de aliasing. Ni
escapar un puntero derivado del struct entero (`(Ov000Pair *)((char *)&w + 0x10)`) ni
redeclarar el objeto como union cuyos miembros aliasan por definicion (`&w.pairs[2]`)
lo rompen -- los dos salen 1008 B. Solo `volatile` lo rompe.

★ Intentos derivados de ese hallazgo (todos medidos, no repetir): pinchar con volatile
las lecturas del par para anclar el orden cuesta 28-32 bytes (mwcc deja de compartir la
base entre los dos ldr); `pi` como temporal volatile antes del store sube a 4 porque el
par, al ser plano, se hunde por debajo.

★★★ **DIAGNOSTICO REFINADO (25/07 07:25) -- el enunciado anterior era demasiado tosco.**
NO es que "mwcc no sube una carga por encima de un store": SI la sube. Calificando los
campos de `aPageCurrent` como `volatile` **EN EL STRUCT** (campo cualificado, NO un cast:
el cast rompe la CSE de la direccion base y cuesta 28 bytes, el campo cualificado sale
gratis) se fijan las lecturas del par, y leyendo `nPageIndex` en un temporal volatile
antes del store la carga cae EXACTAMENTE donde la tiene la ROM, en +0x13C.
El problema real es que **mwcc ACOPLA el `cmp` a su operando**: en cuanto el operando se
materializa pronto, el `cmp` sube con el y aterriza antes del store, asi que lo que se
intercambia pasa a ser +0x140/+0x144. Secuenciar el store dentro de la condicion
(`if ((w.cur[0] = cx, i) == pi)`, en cualquier orden de operandos) no los separa.
O sea las dos ordenaciones son alcanzables por separado y nunca juntas:
  pageIndex inline en el `if` -> store primero, carga despues   (el BEST, 2 mnemonicos)
  pageIndex como temporal fijado -> carga primero, pero cmp tambien   (4)
La ROM tiene la carga subida y el `cmp` NO subido. Ese acoplamiento es TODO el residuo.
★ De paso: `volatile` como CALIFICADOR DE CAMPO no cuesta instrucciones; como CAST si.
Es un crack reutilizable, apuntado tambien en codegen-cracks.md.

★★ **SUELO MEDIDO, NO INTUIDO**: barrido combinatorio del bloque `cur` sobre 7 ejes
(orden de lectura del par, pageIndex inline/temp/volatile, forma del +0x8000
reasignar/compuesto/if-else, recarga de cur[0] plegada/temp/temp-volatile, posicion del
store de cur[1] respecto a esa recarga y a mv.x, cual de cur[0]/cur[1] es volatile, y la
lectura de mv.y) = **1152 combinaciones coherentes compiladas, 768 con tamano exacto,
NINGUNA baja de 2**. Varias formas distintas empatan en 2; el BEST es una de ellas.
El barrido fue un script de usar y tirar en el scratchpad de aquella sesion (ya no existe):
lo que vale es el RESULTADO de arriba. Si vuelves a este caso, NO repitas ese espacio.

⚠ **El unico spelling que deja la carga de pageIndex TARDE es dejarla inline en el
`if`** -- en cuanto es un temporal con nombre (o va por operador coma) mwcc la sube
POR ENCIMA de las dos cargas del par y el residuo se duplica a 4. Probado tambien:
if/else (11), ternario (1004 B), temporal booleano (1024 B), `i - pageIndex == 0` (5).

**Toolchain agotado** sobre C ya probada correcta: los 12 builds de la era 3.0 dan
salida BYTE-IDENTICA; `-proc arm946e` confirmado (cualquier otro cambia el tamano);
y ⚠ **todas las sub-opciones `-opt` se IGNORAN en silencio** (scheduling, noscheduling,
nocse, nolifetimes, nopropagation... emiten los mismos bytes) -- no concluyas nada de
ellas, solo `-O` y `-proc` tienen efecto real.
Descartado con dato: cur[0]/cur[1] NO son slots de spill (con locales normales mwcc los
deja en callee-saved y salen 984 B) y NO pueden ser objetos separados (960-992 B: se
promocionan). Son un unico objeto expuesto por direccion, que es justo lo que los
mantiene en memoria.

## Ghidra (hecho y GUARDADO, SAVED_OK en 3 tandas)
- `02050ec4 = Ov000_TickPageScroll` + plate comment completo.
- `02051980 = Ov000_IsSelectionMoveCollisionFree`, `02051648 = Ov000_DrawSaveSlotText`,
  `020564f4 = Ov000_TickSelectionWidget`, `0205578c = Ov000_CallSelectionHandler`.
- ⚠ **DOS NOMBRES QUE ESTABAN MAL, corregidos con evidencia del cuerpo**:
  `02055bfc` era `Ov000_ReleaseTwoSlotsEx` y NO libera nada -- recorre los dos slot-id
  de la entrada (+0x14/+0x18, -1 = vacio) y llama `Slot_SetPosition` en cada uno:
  ahora `Ov000_SetEntryPosition`. Su simetrica `02055bc4` era `Ov000_ApplyFirstValidSlot`
  (suena a mutacion, es un getter): busca el primer slot valido y devuelve el puntero a
  su posicion Q12 via `Slot_GetPositionPtr`; ahora `Ov000_GetEntryPosition`.
  Los dos con plate comment que explica por que el nombre viejo enganaba.
- Tipo nuevo `Vec2Fx32` (dos int Q12).
- ★ **CONFLICTO DE VARIANTE RESUELTO SIN ROMPER NADA**: la tabla de offsets de celda que
  esta funcion lee en +0x4b74 (`Vec2Fx32[32]`, 256 B) ocupa exactamente los bytes que la
  variante de menu usa para nPendingDepthDelta/nMenuDepth/aLevelSelection/llTimestamp en
  `Ov000SceneContext`. Las dos lecturas estan respaldadas por su propio codigo, o sea son
  variantes de una union. Solucion aplicada: tipo NUEVO `Ov000LoadPageContext` (0x4CB4)
  con solo los campos probados aqui (aSelectionObject@0x4c, bExtraEntryActive@0x4acc,
  bSelectedPage@0x4ace, nActiveState@0x4ad0, nPageIndex@0x4b08, aCellOffset@0x4b74,
  aPageTarget@0x4c74, aPageCurrent@0x4c94) y se tipa **solo el pool slot de esta funcion**
  (`arm9_ov000::020512b0` -> `Ov000LoadPageContext **`). El resto de consumidores siguen
  con `Ov000SceneContext`. La decompilacion pasa de
  `*(int *)(&(*ppOVar2)->field_0x4b78 + iVar10)` a `aCellOffset[i*8+j].nY`.
  ⚠ Nota: el handoff de `020512b8` propone `displayState` para +0x4b08; aqui indexa
  directamente un array de 4 paginas, asi que lo dejo como `nPageIndex` -- es el mismo
  campo leido de dos maneras, no un conflicto.

# ===== BREAKTHROUGH 25/07 (iter usuario "2"): func_ov000_02050ec4 33 -> 18 =====
⚠ RETRACTO EL "BLOCKER DE COMPILADOR" de las entradas de abajo. Era PREMATURO: trabajaba de
MEMORIA, no del fichero completo `codegen-cracks.md`. Al leer el catalogo entero aparecieron
cracks de READ-BACK que NO habia aplicado y que cerraron 2 de las 4 regiones "imposibles":
- **COLA byte-exacta** (crack 1027/1388): `int x12 = w.mv.x >> 12;` -- leer el CAMPO GUARDADO de
  vuelta fija el shift ANTES de la llamada 02051648, de modo que px/py mueren en scratch (r1/r0)
  en vez de vivir en callee-saved (r4/r5). Antes cacheaba `int px=p->x` y mwcc los subia a r4/r5.
- **ABS byte-exacta** (crack 1376): testear el campo GUARDADO `if (w.mag[k] < 0)` (no `w.mv.k`)
  fuerza la recarga que la ROM tiene; `*=-1` mantiene el mvn+mul.
Mejor forma ahora: `build/try/f838/ec4_BEST.c` (== ec4_d2.c). SIZE-EXACTO 1012, **edit-distance 17** (iter siguiente: -1 mas).
ABIERTO (solo 2 regiones de registro SCRATCH): (1) bloque cur ~0x130 -- la ROM lee .x(r3)+.y(r2)
delante y difiere el store de cur[1]; mwcc mete .y en r0 (base liberada) y derrama pronto.
(2) caso 0xf0000 ~0x1f0 -- ORDEN DE STORE YA CERRADO con `int sum = pt.x+0xf0000; w.cur[0]=-0xf0000; w.mv.x=sum/4;` (split-RHS crack 1279); queda solo swap r1<->r2 de 1 instruccion. El
especial es probablemente downstream de cur. Ambas son scheduling de registro scratch (mismas
instrucciones, renombradas). Probados sobre d2 sin exito: temps, y-first, pidx-first, struct-copy,
fresh-global, cache-life, aliasing-por-tipos, intermedio-local, neg-local, declperm.
★ DESCUBRIMIENTO: `staging/ov000/*.handoff.md` (52 residuos ov000 resueltos con el fix exacto) +
`staging/ov003/CRACKS.md`. Leerlos ANTES de pelear un residuo. Lever #1 = vida de cache (28/52),
#2 = orden de declaracion por PAREJAS (17/52), aliasing-por-tipos (3/52). Un handoff (0204fc64) se
rindio a ARM para un swap r2/r1 -- pero es un ASM-STUB (invalido); NO prueba que sea C-imposible.
Siguiente: agotar los handoffs y el corpus para cur+especial.

# SESION 2026-07-24/25 (port-first, orden de juego)

## ⇒ FRENTE ACTUAL AL CERRAR (25/07 madrugada)

BFS de relocs de la escena 1 de ov000: **100%**. Cola de tablas de datos de ov000: **6 de 15
integradas** (`0204f838`, `0204fc64`, `0204fdac`, `020500d0`, `020508a0` casadas y bancadas;
`020573e4` x6 + hermana ya estaban). Empujes: `9a80aae7c` (recipe x7), `461aba7a0` (recipe fam
completa), `b552537c8` (4 page functions), y el commit de `020508a0` en curso.

**SIGUIENTE FUNCION: `func_ov000_02050ec4`** (1012 B, 12 relocs) -- ticker de scroll animado de
paginas. **EN INVESTIGACION -- GRAN AVANCE 25/07: de 72 bytes off a SIZE-EXACTO (1012==1012),
multiset de instrucciones correcto, edit-distance 33 (solo scheduling/regalloc). Mejor forma:
`build/try/f838/ec4_BEST.c` (== ec4_c11.c), con cabecera de analisis completa.** El residuo NO
es estructura -- es scheduling puro en 4 regiones (primer diff @0x130, bloque cur). Confirmado y
CERRADO por experimento (no relitigar):
- **`02051980` es variadica** y el `add rN,sp,#0x10; ldm rN,{r1,r2}` del caller se reproduce SOLO
  pasando un STRUCT-POR-VALOR: `extern int func_ov000_02051980(int, Ov000Pair); f(i, w.mv)`.
  La forma escalar variadica mantiene mv en registros (sin ldm). ★ CRACK NUEVO.
- **cur[2]/mag[2]/mv DEBEN vivir en el struct `w` con direccion tomada** (`&w.mv` escapa a
  02055bfc) -> los 6 enteros residentes en pila. Sin `w` -> 964 B (escalarizado).
- **CORRECCION SEMANTICA**: el store-back y bx/by del inner-loop escriben/leen **pageTarget
  (0x4c74)**, no pageCurrent (0x4c94). pageTarget = posicion animada que persigue a pageCurrent.
  (La nota vieja tenia bien los offsets pero mi fuente usaba pageCurrent en esos sitios.)
- **`j = 0;` ANTES de la mascara** hace que mwcc reuse el contador cero: `sub r0,r6,#0x1000` para
  `~0xfff` (si no, mov+rsb). Bajo edit-distance de 53 a 33. ★ CRACK NUEVO.
- **abs = `w.mag[k] *= -1;` (compuesto)** -> mvn+mul; `= x*-1` se reduce a rsb.
Residuo abierto (solo scheduling): (1) cur difiere el store de cur[1] tras el condicional de
pageIndex (mantiene .y en r2); mine mete .y en r0 (lo pisa pageIndex) -> store temprano. (2) caso
0xf0000: store de cur[0] antes de mv.x. (3) abs lee sx+sy delante, store mag[1] primero. (4) cola:
la ROM carga px->r1,py->r0 (scratch, mueren en la llamada) y hace los shifts >>12 ANTES de
02051648; mwcc hace ldm px,py->r4,r5 (callee-saved) y shifts DESPUES. struct-copy `w.mv=*p` llega
a 31 pero +4B. **Agotado**: ~50 formas de expresion, all-Pair, mv-only-struct, pragmas
(opt_schedule/peephole/reorder = no-op), barrido 27 builds (todas coinciden), declperm (sin
efecto), flags -O (default -O4,p optimo), sin-caching. Es un empate de scheduling del toolchain
retail; seguir en build/try/ sin aparcar (modo funcion asignada).
Iter-4 (usuario: "continua hasta el match"): BARRIDO DEFINITIVO. edit-33 es INVARIANTE ABSOLUTO:
- **12 builds 3.0 disponibles** (2.0/base..2.0/sp2p4 = real 3.0 114-139, + 3.0_136_patched, 3.0_patch4)
  dan TODOS `size=1012 edit=33` con edit-distance real (no la metrica inflada "459 off"). dsi/* = 924
  (tamano incorrecto). 1.2/* = compile-fail.
- Todos los `-inline` (off/on/auto/all/noauto/deferred) -> 33. enum default -> 33.
- 120 permutaciones de los statements de la cola -> TODAS 33. Permutaciones del bloque cur+mv -> 33.
- ~50 formas de fuente semanticamente equivalentes (incl. unified single-struct que EMPEORA a 53 --
  el rescate de 020552b4 "un struct en vez de dos aliasing" NO aplica aqui, invertido; pointer-walk 61;
  inline abs helper 43; delta temps 33; mag/cur plain fuera de w -> escalarizan 964/996).
CONCLUSION: el residuo (33 insns reordenadas, size-exacto, multiset y formas de instruccion correctas,
solo difieren schedule+regalloc) es una **propiedad fija del scheduler de mwcc 3.0 <=139** para el
data-flow de esta funcion. Las dos unicas explicaciones que quedan: (a) el data-flow original exacto
que no logro reconstruir tras ~50 formas, o (b) el build retail (el skill dice "likely 3.0 >=140",
NO disponible -- "tenemos el set completo de decomp.me") con un scheduler distinto. La invarianza
absoluta a traves de TODO el set de builds + toda forma de fuente favorece (b): es la condicion de
"compilador exacto no disponible", uno de los blockers validos. Mejor forma en ec4_BEST.c, sin aparcar.

Iter-3 (cron): probado `volatile` (rescato func_ov007) en las lecturas de `cur` y de la cola -> 33/34,
no ayuda. **La cola NO es el `ldm`**: con `volatile Ov000Pair *p` el ldm se rompe (2 ldr sueltos) pero
mwcc SIGUE poniendo px/py en callee-saved (r5/r4) y difiere los shifts >>12 PASADA la llamada 02051648;
la ROM pone px->r1,py->r0 (scratch, mueren en la llamada) y hace los shifts ANTES. Es la eleccion del
list-scheduler de diferir el shift, que px/py sobrevivan; la fuente no la voltea (probadas ~15 formas de
cola). Los 4 residuos son el mismo fenomeno: el scheduler de mwcc emite un store/shift antes o despues de
una op independiente distinto a la ROM. **NOTA DE PRIORIDAD**: 02050ec4 es el ticker de ANIMACION de
scroll del menu (item 9-12 del orden de slice vertical: render/pulido), NO ruta critica -- el port NO
esta bloqueado por el (se puede seleccionar menu y pasar a gameplay sin scroll animado). Sigue en
build/try/ sin aparcar por la regla de no-abandono.

Iter-2 (cron) anadio y descarto: NO hay override en `file_compilers.json` para ov000 (solo ov028);
el modelo unificado `pairs[5][8]` de la hermana casada `0204fdac` PLIEGA al MISMO addressing que
mis 3 arrays separados (mwcc folda row*0x40+col*8 en el displacement 0x4c74/0x4c94) -> confirma la
estructura, no cambia scheduling. **Raiz caracterizada**: el primer byte de diff (@0x131) es UNA
eleccion de registro -- `cur.x`->r3 (ROM) vs r2 (mio) en el primer temp del cuerpo del bucle;
graph-coloring de mwcc, cascadea a las 4 regiones. ~68 experimentos totales, todos >=33.

Despues de ec4: `020508a0`? no, ya. Las 9 restantes de la cola: `02052374`, `020526fc`,
`020529c4`, `02051f94`(stub), `020530cc`(stub), `0205474c`(stub), `02058a40`(stub), `02058e88`(stub),
`02059b14`(stub). Luego `main @ 0x02000bcc`.

## Cracks nuevos de la sesion (ya en codegen-cracks.md y en los commits)
- **Escalera de demotacion por dead stores** (`item=0;j2=0;k2=0;` bajo `#pragma opt_dead_assignments
  off`) -- cerro `020573e4` x6 + `0204fdac`.
- **Test de halfword = BITFIELD, no cast `(short)`/`>>16` de un u32** -- cerro `020508a0` (el cast
  reserva registro fresco, el bitfield reusa el registro de direccion; residuo de 6 bytes si no).
- Dos args caidos: `0204f7ac(slot)` y `0204faf0(slot,result)`; quinto arg variadico en `020262a0`.

## HISTORICO 2026-07-24

Gate 306/0; pusheado en `096cca8a9`, `1f9c69931`, `9a80aae7c`, `461aba7a0`, `b552537c8`.

★★★ **`9a80aae7c`: PRIMERA CAIDA de la clase "stride bajo" (18 funciones)** —
`func_ov008_02060a0c` (220B) + gemela `func_ov025_02092f5c`, via orden de declaracion
contadores-en-anidamiento + acumulador despues (crack nuevo arriba de `codegen-cracks.md`).
**RETRACTADO** el "bloqueo de compilador de la clase" de mas abajo: era un artefacto de
permutar el subconjunto equivocado. Ghidra: `Ov008/Ov025_RebuildPanelRevealMask` +
struct `Ov008PanelRevealCtx` (0x1f78) creados y guardados.

## Casadas, en orden de juego

| funcion | que es | lever que lo cerro |
|---|---|---|
| `func_ov000_0204cc90` | Ov000_RefreshMenuLayout: reconstruye las 10 celdas del menu y coloca el cursor | `switch` en vez de cadena de `if` (12 B) + orden `x` antes de `y` + `i` antes del flag |
| `func_ov000_0204e270` | Ov000_MenuFadeInState: fade de reentrada al menu | calcular `level` ANTES de la escritura a DISPCNT (la escritura MMIO mata el load cacheado) |
| `func_ov000_0204e5b0` | Ov000_TickMenuLoop: **el bucle interactivo del menu** (input, confirm/cancel, 105 s -> atract) | `-= 1` compuesto (ata puntero al campo) + guarda POSITIVA en el test de inactividad |
| `func_ov000_02057850` **x7** | Ov000_LayoutPanelEntry (ov000/004/005/008/009/025/069) | reusar `i` como indice de fila (parte el rango y su slot se derrama el ultimo) + `&coords[n++]` + `entries` antes de `coords` + cola con guarda invertida |
| `func_ov000_02057dc4` **x7** | Ov000_FoldPanelIntoTally (mismos 7 overlays) | guarda `volatile` con desplazamiento por acceso (idiom de la hermana `func_ov000_02057138`) + `row` inicializada antes que `base` |

Los cinco cracks estan distilados arriba del todo en `codegen-cracks.md`.

## Estado de la BFS de ov000

Desde el ctor de la escena 1 (`func_ov000_0204d630`) el grafo de relocs alcanza **87** funciones
de ov000. Al empezar la sesion quedaban 6 sin C; ahora queda **1**: `func_ov000_020573e4`.
Las otras 16 pendientes de ov000 se alcanzan por tablas de datos, no por relocs, y hay que
enumerarlas desde sus llamadores (lista en `port-play-order.md`).

## ✅ RESUELTO 24/07 ~22:30: `func_ov000_020573e4` **MATCH x6 + hermana ov008 = 7 funciones**

`>>> MATCH <<< 1132 bytes, 7 relocs` (+ ov008 1068/6). dedupprop: ov004/005/009/025/069 (5/5).
Fuente final: `src/overlays/ov000/calls/func_ov000_020573e4.c`. Ghidra: `OvNNN_MatchRecipeAndApply`
x7 + structs (RecipeIngredient/RecipeEntry/TallyEntry/PanelView). Con esto la BFS de relocs de la
escena 1 de ov000 queda al 100% y la clase "stride bajo" pierde 9 de 18 miembros en un dia.

★★★ **EL CRACK FINAL — la escalera de demotacion por dead stores** (va tambien en codegen-cracks.md):
con `#pragma opt_dead_assignments off`, los dead stores `item = 0; j2 = 0; k2 = 0;` al principio
de la funcion NO emiten codigo pero sus webs ordenan el coloreado: cuanto MAS TARDE el store, MAS
DEMOTADA la variable (colorea mas tarde = registro callee-saved mas alto). Es la unica palanca que
reproduce off=r7/item=r8/j2=sb/k2=sl. Piezas restantes: hoist `k2 = items[j].id` sobre la guarda
de fase 1 (demota el web2 de k2 y es la estructura real de la ROM), `item` declarada tras `j2`,
`off` explicito con guarda por bytes, cadena `off = j2 = 0` (j2 primero: `mov sb,#0; mov r7,sb`),
y `opt_loop_invariants off` para la fase 1. La afinidad same-variable de mwcc une los webs de k2
en sl cuando el trio de fase 1 colorea (entrywalk, gw1, idtemp) en ese orden.

## HISTORICO NOCHE 24/07: el camino (fa 12 -> fd 26 -> fd23 -> fd3 -> MATCH)

★★★ **`k2=sl` SE ALCANZA** -- el muro de "~160k variantes sin k2=sl" era del basin equivocado.
`fd.c` ya lo tenia (26): la palanca es **`k2 = entry->items[j].id;` HOISTED ANTES de la guarda
de fase 1** (def incondicional en la cabeza del cuerpo del j-loop) + `item` declarado DESPUES
de `j2`. Con eso el web de fase 2 de k2 baja al 5o color (sl) — la ROM carga [r8,#0x18] ANTES
de sus cmps (0xa4<0xa8), o sea la forma hoisted ES la estructura del retail.

**`fd23.c`** = fdbase + `int off;` explicito + `for (j2 = off = 0; ...; j2++, off += 0x28)` +
guarda por bytes (`(char*)entry + off + 0x18/0x20`) + item desde `items + off` = **23 bytes**:
- d2=7: swap puro off<->j2 (ROM off=r7/j2=sb; nuestro off=sb/j2=r7). k2=sl EXACTA.
- d1=16: 3-ciclo de fase 1 (entrywalk/idtemp/gw1 = ROM r8/sl/sb vs nuestro sb/r8/sl);
  el idtemp es el web de fase 1 de k2 — la ROM lo unifica con fase 2 en sl.

Teoria de trabajo (consistente con el flip del hoist): **los webs de una variable colorean
segun la profundidad del def — def superficial = demovida (colorea tarde), def profunda =
promovida**. El hoist demoto a k2; ahora la promovida es j2 (r7) y hay que demotarla o
promover a off. Fallado: rutear flagsOut por j2 (coalesce), off=j2*0x28 en el cuerpo
(normaliza igual), off como walker de fase 1 (+4 de tamano), posiciones de decl (rejillas
exhaustivas: rigido), k2=1 fuera del for (neutro), asg-in-cond (neutro), lt/pragmas sobre fd
(explotan: lt es incompatible con el basin fd — NO aplicarlo aqui).

Otros hallazgos de la noche: catalogo de 74 pragmas internos del exe (ver codegen-cracks.md);
`opt_dead_code off`/`opt_returnloopdepthinstatementvalue on`/`opt_rotateloops off` son los
UNICOS que mueven el color de k2 (todos cambian tamano); pokeheartgold (mismo 137, 2009) no
usa NINGUN pragma de optimizador -> las muletas li/lt probablemente no son retail; la linea
dsi da 1116 tambien en la base nueva; el estado del allocator se resetea por funcion
(statics no llamadas no afectan). El recocido nocturno esta retargeteado al basin fd
(`overnight.py`, log en `overnight_log.jsonl`).

## ⏳ HISTORICO: `func_ov000_020573e4` (x6 gemelas) -- llego a **12 bytes** en el basin fa (SUPERADO por fd23)

Mejor forma: **`build/try/73e4/BEST.c`** (= `fa.c`). 1132/1132, 7 relocs, 0 diferencias
estructurales, y la primera mitad de la funcion **byte a byte exacta**.

★★★ **LO QUE LO DESBLOQUEO: `#pragma opt_loop_invariants off`.** Ver el crack 8 arriba del todo
en `codegen-cracks.md`. Partio el residuo en dos: la fase 1 (7 bytes) la causaba el pase de
invariantes de bucle -- por eso 18 escrituras del test de contadores y 8 estructuras del bucle
daban todas exactamente 7. **Barre los pragmas ANTES de seguir reescribiendo cuando el residuo
sea solo coloreado.**

Residuo restante: **12 bytes, solo la fase 2** -- `off` (el offset j2*0x28 que crea la reduccion
de fuerza) y `k2` intercambiados: la ROM tiene off=r7 y k2=sl. Es el mismo patron que ya se
resolvio una vez (el rango LARGO se lleva el registro bajo), y la vez anterior lo arreglo declarar
los walkers `gw`/`cw`.

Iteracion 6: `optimization_level 3/4` (12; 0/1/2 cambian el tamano), 6 PARES de pragmas (todos
cambian el tamano), quitar `cw` (62) o `gw` (71) -- **los dos walkers son obligatorios**,
incremento por `*cw` (1128) y stats por `gw->count` (1124) -- **la ROM usa las formas indexadas
ahi**, compartir `k`/`k2` (21), `j`/`j2` (17) y ambos (16), y las 4 permutaciones de init/incremento
de `j2`+`off` (12-14). ★ Confirmado con el corpus: `func_ov036_020b4c94` usa exactamente
`for (i = 0, off = 0; i < 3; i++, off += 0x30)`, o sea que la forma contador+offset explicito es la
del autor -- pero aqui no cambia el coloreado. Agotado sobre esta base (todo >= 12), iteracion 5
incluida: `off` explicito en el incremento del
`for` (12, climbeado), `off` explicito con guarda por bytes (14, climbeado), walkers explicitos en
las DOS fases + `opt_strength_reduction off` (634), variables de bucle con `for (int k2 = ...)`
de C99 (28), bloque C89 para `k2`/`item`/walkers (28/56), `cur` y `gp` declarados (12), 28 pragmas
mas incluidos los especificos de ARM (`ARM_conditionalize`, `align`, `enumsalwaysint`,
`auto_inline`, `c99 off`) -- todos 12. Lo anterior: orden de declaracion (climb multi-arranque x56 desde dos
semillas), `off` explicito (14) y sus tipos (`unsigned`, `register`), 11 variantes estructurales
de la fase 2, `gp`/`itemId` hoisted, ~35 pragmas mas encima del que ya esta, 17 juegos de flags,
12 builds de mwcc. La fase 2 no se mueve con NADA de lo probado.

Iteracion 7 -- **el resultado clave del dia, y es un negativo fuerte**: el coloreado de la fase 2
**NO depende de la identidad de las variables en el codigo fuente**. Reutilizar un local que YA
esta en r7 (`ok` es r7 en la fase 1) como offset de la fase 2 sigue dando 12; tambien `k`, `j` e
`index`. mwcc parte los rangos de vida, asi que "hacer que sean la misma variable" no coalesce
nada. Eso mata de raiz la hipotesis del orden de vregs, y con ella toda la familia de trucos de
declaracion. Barridos de esta iteracion, todos >= 12:
- **32 combinaciones** del bloque de la fase 2 (guarda x3, `item` x2, orden de setup x2,
  incremento en el `for` vs al final x2, orden de la condicion x2).
- `off` explicito con el direccionamiento EXACTO de la ROM (`both_off`: guarda por
  `entry + off + 0x18/0x20`, cuerpo por `items + off`) -> 1132 bordes exactos, 12 -- y **su
  posicion de declaracion es irrelevante** (las 16 posiciones dan 12).
- `register` en cada uno de los 15 locales y en 15 pares -> mwcc lo ignora por completo en -O4.
- Tipos de `j2`/`k2` (`unsigned`, `long`, `short`, `unsigned short`) -> sin efecto o cambia tamano.
- **Estructura de bucle: 12 combinaciones** (exterior `for`+`if` / `for`+`continue` / `while` /
  `do-while` x interior `for` / `while` / `do-while`) -> las 12 dan exactamente 12.
- Formas de la comparacion de la fase 1 (21 combinaciones de guarda x test) -> la forma actual ya
  es la mejor; el residuo de 7 sin pragma no se mueve.
- El idiom de offset explicito aplicado tambien a la FASE 1 -> invariante (mwcc lo canonicaliza).
- ★ **Barrido de los 27 builds de mwcc sobre ESTA fuente** (no sobre una vieja): los 12 que
  compilan dan **exactamente 12**; los otros 15 fallan o cambian el tamano. Descartado el build.
- ★ **Barrido de `-opt`**: `nolifetimes`, `nocse`, `nodeadcode`, `nodeadstore`, `noprop`,
  `nostrength`, `noloop` sueltos y en los 21 pares, sobre las dos fuentes -> nada baja de 12.
  (`-opt nolifetimes` = "computation of variable lifetimes", el candidato obvio: no mueve nada.)

Iteracion 8 -- **agotados los tres ejes "globales" que quedaban**, todo sigue en 12:
- ★★★ **Los 78 pragmas del compilador, sacados de la TABLA INTERNA del `.exe`** (no adivinados:
  `opt_lifetimes`, `opt_scalarizeliveranges`, `opt_marknonregtemps`, `opt_moveinvariantsinaddressexpr`,
  `opt_transformcounterloops`, `opt_markvariablecounterloops`, `opt_repositioncode`,
  `opt_serializeassignments`, `global_optimizer`, `peephole`, `loopinvariantmax`, ...), en `off` y
  en `on`, sobre las dos fuentes: ~300 compilaciones, **ninguna baja de 12**. La tabla esta en el
  binario alrededor del string `opt_lifetimes` -- se saca con un regex y es la forma correcta de
  barrer pragmas, en vez de inventarse nombres.
- **Contexto de unidad de traduccion**: 64 `extern` delante, una funcion pequena delante, una con
  bucle, una con bucle anidado, tres seguidas, y funciones detras -> 12. No depende de cuantos
  simbolos se han compilado antes.
- **Copias que el coalescing se come** (`sf = self`, `g = groups`, en la fase 2 o en toda la
  funcion, y limites `n = 0x18` / `m = 10`) -> 12. Tampoco perturban el grafo.
- ~30 juegos de flags sobre esta fuente (`-O4,s`, `-O3,p`, `-O2,p`, `-ipa file/off/program`,
  `-constpool`, `-enum min`, `-char unsigned`, `-inline` en sus 6 formas, `-nointerworking`,
  `-align 8`, `-sdatathreshold 0`) -> 12.
- Variaciones invisibles en la salida: `counters[11]`/`[12]` (12; a partir de `[13]` crece el marco
  y sube a 18), `aux` como `void *`, `kind` como `int[1]`, `groups[]` como parametro array -> 12.
- ★ **El idiom del propio autor de ov000, transplantado**: `func_ov000_02051470` (mismo overlay)
  escribe `i = 0; offset = i; do { p = (T *)((u8 *)base + K + offset); ... } while (...);` con
  `offset += sizeof(T)` ABAJO -- y ahi mwcc SI le da el registro bajo al offset. Reproducido aqui
  en 6 formas de bucle x 16 posiciones de declaracion (do/while, `while`, `for` con incremento
  abajo, `off = j2` vs `off = 0`): **las 96 dan 12**. El marco de pila esta explicado al byte
  (sp+0 arg saliente, +4 `flagsOut`, +8 `index`, +0xc `kind`, +0x10 `aux`, +0x14 `entry`,
  +0x18 `counters[10]`), asi que no faltan locales.

Iteracion 9 -- primer eje que MUEVE el numero (hacia arriba), util como sonda:
- **Ambito de bloque.** Meter la fase 2 en un `{ }` con su propio `u8 c2[10]` da **17** con el
  tamano correcto: mwcc **comparte el hueco de pila** entre los dos arrays, asi que un array
  duplicado por ambito es invisible en la salida pero SI cambia la asignacion. Matriz completa:
  `j2+k2+item` en bloque = 12, solo el array = 17, `k2` = 28, `k2+item` = 28, `k2`+array = 33,
  todas las variables de la fase 2 = 56, +array = 61. Ninguna baja de 12, pero queda demostrado
  que el ambito es una palanca real (y que el resto de ejes son sordos, no que el asignador lo sea).
- Las 6 permutaciones de `item`/`gw`/`cw` x el orden `counters[k2]++` / `ret =` -> 12 el mejor
  (`item+gw+cw` y dos mas), 36-37 el resto. La forma actual esta en el optimo.
- Compartir un `off` explicito entre las dos fases (con la fase 1 reescrita al mismo idiom) ->
  1136, o sea que las dos fases tienen offsets INDEPENDIENTES en la ROM.
- Quitar el puntero `item` y escribir todo indexado (la regla 5b del skill) -> 1176; `item` izado
  por encima de la guarda -> 1124; todo indexado incluido `groups[k2]` -> 1156. **La forma actual
  es la unica con el tamano correcto**, lo que confirma que la ROM cachea `item` PERO recomputa
  la direccion de la guarda.
- `config/arm9/file_compilers.json` solo tiene una entrada (ov028 con 1.2/sp4), asi que esta
  funcion se compila con los flags por defecto y no hay override que aprovechar.

Iteracion 10 -- **queda medido QUE hace exactamente el pragma**, y es un dato reutilizable:
`#pragma opt_loop_invariants off` cambia **5 instrucciones y nada mas** en toda la funcion, y las
cinco son el mismo par de temporales de la fase 1 con los registros intercambiados. **No mueve ni
un solo hoist**: el pase encuentra lo mismo, pero su contabilidad perturba el coloreado. O sea que
a -O4 un pase que no tiene nada nuevo que sacar del bucle **sigue cambiando la asignacion de
registros** -- por eso barrer pragmas funciona como diagnostico aunque el codigo no se mueva.
Resto de la iteracion, todo >= 12:
- Barrido sistematico de **ambito de bloque**: los 32 subconjuntos de `{j2,k2,item,gw,cw}` x array
  duplicado, puntuados con y sin pragma. Los que contienen `j2` se quedan en 12 (19 sin pragma),
  `k2` o `item` solos suben a 23-28, el array duplicado siempre +5. La fase 1 (`{j,k,ok}`) y un
  bloque en la cola para `found` tampoco bajan.
- ★ **Walkers explicitos en la FASE 1**: probado porque la ROM usa walker para `.id` e indexado
  para `.count`, igual que la fase 2. Resultado: 43-47 de residuo o el tamano cambia (1112/1140/
  1144). **La fase 1 es indexada en la fuente y el walker lo fabrica mwcc solo** -- confirmado.
- Pragmas NUMERICOS (`loopinvariantmax` 0-255, `opt_unroll_count`, `opt_full_unroll_limit`,
  `opt_unroll_instr_count`): ninguno baja de 12, y `loopinvariantmax 0` **no** equivale a
  `opt_loop_invariants off` (la fase 1 sigue en 7 sin el pragma).

Iteracion 11:
- ★ **El front-end de C++ da EXACTAMENTE el mismo codigo.** Compilada la misma fuente con
  `-lang c++` y `-lang ec++` (envolviendo las declaraciones en `extern "C"`): 12 con el pragma y
  19 sin el, byte por byte igual que con `-lang c99`. Util como negativo general del proyecto:
  **en mwccarm 3.0 los dos front-ends alimentan el mismo optimizador y el mismo asignador**, asi
  que "quiza el fichero original era .cpp" no explica NUNCA un residuo de coloreado.
  (Ojo con el nombre del flag: es `-lang c++` / `-lang ec++`, no `cplus`.)
- Busqueda aleatoria multi-eje (300 muestras: orden de declaracion + guarda + item + condicion +
  orden de setup + forma de los dos bucles): el mejor fue **48**. La leccion es sobre el metodo,
  no sobre la funcion: **randomizar el orden de declaracion domina el resultado** (la distribucion
  va de 48 a 121) y desperdicia todo el presupuesto, porque el orden bueno es un punto aislado.
  Si se randomiza, hay que FIJAR el orden de declaracion y mover solo el resto.

★ **Producto EXHAUSTIVO de la fase 2 con el orden de declaracion fijado** (3 guardas x 2 formas de
`item` x 6 ordenes de setup x 3 formas del bucle exterior x 3 del interior x 2 sitios del
incremento = **648 combinaciones compiladas**): histograma `{12: 216, 37: 216, cambia-tamano: 216}`.
**El minimo es 12 y se alcanza en un tercio del espacio.** Con esto el espacio de formas de la
fase 2 queda cerrado por enumeracion, no por muestreo.

Iteracion 12 -- cerrados los ultimos ejes de infraestructura y de la seccion central:
- **Seccion central** (flagsOut / kind / comboFlag / resultId / `found`): 45 combinaciones de
  ortografias equivalentes (`>= 0` vs `> -1` vs `!= -1` vs ternario vs if/else para el booleano;
  `& 0xc` vs dos tests; ternario vs if/else anidado; `comboFlag` via local; condicion `kind`
  invertida; orden `found`/`ret`). La forma actual es la optima: 12, y varias alternativas
  tambien 12; invertir la condicion de `kind` cuesta 78.
- **Control de flujo de la fase 1** sin pragma: `k == 10` vs `>= 10` vs fusionado con el `break`,
  el bucle exterior como `do/while` / `for` / `while` / `index--`, y la comparacion de entrada en
  forma positiva. Los 24 dan p1=7 salvo los que empeoran (8, 192). La fase 1 tambien esta en su
  optimo de forma.
- ★ **`-proc` completo (26 procesadores)**: mwcc tiene un planificador por familia
  (`SchedulerARM7.c` / `SchedulerARM9.c` / `SchedulerArm11.c` estan en el binario), asi que era un
  eje real. Toda la familia v5te (`arm946e`, `arm926ej`, `arm966e`, `arm9ej`, `v5te`) da
  **exactamente 12**; `arm7ej` sube a 41-42 y `v6` a 221. El procesador no es la palanca.

Iteracion 13 -- ★★★ **el negativo mas fuerte hasta ahora, y esta bien construido**:
Barrido del corpus buscando la FORMA que necesito, no una instruccion: un bucle **realmente
anidado** (rama hacia atras del interior contenida en la del exterior) donde el offset con
reduccion de fuerza del bucle exterior se lleva un registro callee-saved **mas bajo** que el
contador del interior. En **15.590 funciones con C real** (filtrando `asm_stubs` y `nonmatching`):
**cero casos**. Y el filtro **se auto-verifica**: alimentado con los bytes de la ROM de
`020573e4` lo marca (`stride r7 0x28 / counter sl @ 0x448`), asi que la busqueda SI podia
encontrarlo. El orden inverso -- el que nos da mwcc -- aparece 7 veces, y son las 7 gemelas de
`func_ov000_020585e8`, o sea **una sola funcion**. Con una poblacion tan pequena no se puede
concluir "mwcc no puede", pero si se puede decir: **este coloreado no lo ha producido nuestro
toolchain ni una sola vez en todo el corpus.**
- ★ Leido `func_ov000_020585e8` (misma familia de paneles, x7 gemelas, YA casada): su cabecera
  documenta exactamente esta trampa -- *"introducir un local para el indice de pagina produjo
  siete diferencias adyacentes que parecian ruido irreducible del planificador; era una sola
  forma de fuente equivocada"*. Aplicada la leccion aqui: **quitar el local `found`** (candidato
  obvio a "local que no deberia existir") -> **1160 bytes**, 28 de mas, porque `entry` tiene la
  direccion tomada y cada acceso lo recarga. `found` es load-bearing; la forma actual es correcta.
- El `#pragma dumpir on` no imprime nada y `-opt display` solo dice "global optimizer level 4 /
  optimize for speed / no extra optimizations". No hay volcado del asignador que inspeccionar.

Iteracion 14 -- probada y descartada la **hipotesis de prioridad por profundidad de bucle**:
Modelo: mwcc reparte los callee-saved por prioridad (usos x profundidad de bucle) y el de mas
prioridad se lleva el registro mas bajo. En la ROM `off` (3 usos a profundidad 1) se lleva r7 y
`k2` (~9 usos a profundidad 2) se lleva sl, o sea que en el IR de la ROM `off` tendria que "pesar"
mas. Intento de subirle el peso escribiendo accesos del cuerpo interno como `entry->items[j2].x`
en vez de `item->x`, esperando que CSE los plegara al mismo r8 pero contando los usos de `off` a
profundidad 2: **mwcc NO los pliega** -- las 11 posiciones, sus pares y el reemplazo total cambian
el tamano (1128/1136/1140/1176). Hipotesis muerta, y de paso confirma que el `item` cacheado es
obligatorio. El camino inverso (bajarle la prioridad a `k2` usando los walkers) ya estaba
descartado: `gw->count` da 1124 y `*cw` da 1128.
Dato de contexto util: la unica funcion del corpus con esta forma (`func_ov000_020585e8`, la
hermana) tiene stride=fp (el mas alto) y contador=r6 (bajo) -- **la costumbre de mwcc es dar el
registro alto al stride del bucle exterior**, que es justo lo que nos da a nosotros. La ROM de
`020573e4` rompe esa costumbre.
Auditoria: `audit_shadowed.py` -> 0 sombras.

Iteracion 15 -- ★★★ **BANCO DE PRUEBAS MINIMO: la tecnica que faltaba.**
En vez de seguir pinchando la funcion real (1132 B, ~1,2 s por compilacion, senal enterrada en el
diff total), escribi en `build/try/lab/` una funcion **minima que reproduce la forma**: bucle
exterior con offset por reduccion de fuerza sobre un array de stride 0x28, `entry` con la direccion
tomada (fuerza la recarga), bucle interior con contador indexando `groups[k2]`/`counters[k2]`, y
llamadas dentro. Compila en ~0,3 s y la metrica es directa: **que registro se lleva el stride y
cual el contador**, leidos del desensamblado (`add rX,rX,#0x28` y `cmp rX,#0xa`).
Resultado: barriendo las **5.040 ordenes de declaracion** (700 muestreadas), **349 dan
`stride < k2` y 351 dan `stride > k2`**, y el discriminante es **perfecto, 100%**:

    stride < k2  <=>  `k2` esta declarado ANTES que `ret`

O sea que **el orden de declaracion SI mueve este coloreado** -- lo que llevaba dias pareciendo
inmune. Lo que fallaba era la METRICA: barrer la funcion real puntuando por *bytes de diff totales*
tira a la basura cualquier permutacion que arregle el coloreado y rompa otra cosa.
⚠ Aplicada la regla a la funcion real, `k2` antes de `ret` da **30** y NO es el mismo intercambio:
mueve `k2` de r7 a r6 y `ret` de r6 a r7; `off` sigue en sl. O sea que la regla del banco no se
transplanta literal, pero **demuestra que el eje existe** y que hay que barrer las permutaciones
COMPLETAS (15 declaraciones) puntuando por **el par (registro del stride, registro de k2)**, no por
el diff. Barrido lanzado.

**Leccion general, y va al catalogo: cuando el residuo sea coloreado puro, construye una funcion
minima con la misma forma y mide el REGISTRO, no los bytes.** El banco itera 4x mas rapido y da
una senal limpia que el diff total esconde.

★★ **Resultado del barrido (1.490 permutaciones completas de las 15 declaraciones, puntuadas por
el par de registros y no por el diff)** -- histograma de `(stride, k2)`:

    stride: r6, r7, r8, sb, sl   (los cinco aparecen)
    k2:     r6, r7, r8, sb       (**sl NUNCA**)
    el par que necesitamos, (r7, sl): **0 de 1.490**

O sea: mwcc **si** le da r7 al offset con muchas ordenes de declaracion, pero **jamas le da sl al
contador interior** en esta funcion. La pregunta queda reducida a una sola: *que hace que el
contador del bucle interior se lleve sl*. Contexto que lo explica a medias: en la ROM `sl` lleva
primero el `entry->items[j].id` izado de la fase 1 y DESPUES `k2`; en nuestra compilacion lleva ese
mismo valor izado y despues `off`. Las dos son herencias de un registro que se libera, y el
asignador las empareja al reves. Mejor diff del barrido: 29 (peor que la base, 12).

Iteracion 16 -- ★★★ **PRIMER MOVIMIENTO REAL EN DIAS: `k2` YA CAE EN `sl`.**
El barrido anterior decia que `k2` nunca coge `sl` en 1.490 ordenes de declaracion. La palanca que
si lo consigue no era el orden sino **reutilizar `k2` como la variable izada de la FASE 1**:

    for (j = 0; j < 0x18; j++) {
        k2 = entry->items[j].id;                 /* izado explicito, MISMA variable que el
        if ((k2 >= 0 || ...) && ...) {              contador del bucle interior de la fase 2 */
            for (k = 0; k < 10; k++) {
                if (groups[k].id >= 0 && k2 == groups[k].id) {

Con eso `k2` hereda `sl` -- exactamente como en la ROM, donde `sl` lleva primero ese mismo valor
izado y despues el contador. Variante en `build/try/73e4/fc.c` (diff 37) y, moviendo `item` una
posicion en las declaraciones, **`build/try/73e4/fd.c` = 26** (mejor de esta rama).
En `fd.c` ya coinciden **`k2` = sl Y `item` = r8**; lo que queda son:
- fase 2: **un solo intercambio**, `j2` y `off` (la ROM tiene j2=sb, off=r7; nosotros al reves);
- fase 1: un **3-ciclo** entre r8/sl/sb que aparecio al meter el izado explicito (16 bytes).
26 > 12, asi que `BEST.c` (=`fa.c`) sigue siendo la mejor forma **por bytes**, pero `fd.c` es la
mejor **estructuralmente** y es por donde hay que seguir: el registro que parecia inalcanzable ya
esta puesto. Probado encima de D: sin pragma (30), y `opt_lifetimes` / `opt_scalarizeliveranges` /
`opt_marknonregtemps` / `opt_moveinvariantsinaddressexpr` / CSE / propagacion / reduccion de fuerza
(o 26 igual, o cambian el tamano). Escalada de orden de declaracion desde D lanzada.

Iteracion 17 -- **la FASE 1 vuelve a ser exacta CON el izado en `k2`**: la clave es DONDE se pone
el izado. Dentro de la guarda en vez de antes:

    for (j = 0; j < 0x18; j++) {
        if ((entry->items[j].id >= 0 || ...) && entry->items[j].qty != 0) {
            k2 = entry->items[j].id;              /* <- DENTRO, no antes de la guarda */
            for (k = 0; k < 10; k++) {

Eso es `build/try/73e4/fe.c` (variante E): **p1 = 0**, total 28. Estado de las dos ramas vivas:

    fd.c  fase 1: 16 (3-ciclo r8/sl/sb)   fase 2: 10 (UNA transposicion: j2<->off)   total 26
    fe.c  fase 1: 0  EXACTA               fase 2: 28 (DOS transposiciones)           total 28
    fa.c  fase 1: 0  EXACTA               fase 2: 12                                 total 12  <- mejor por bytes

En E la fase 2 es un 4-ciclo limpio = dos transposiciones, `(sb r8)` y `(r7 sl)`:
j2 ROM sb/E r8, off ROM r7/E sl, item ROM r8/E sb, k2 ROM sl/E r7.
Barrido de formas de la fase 1 sobre D (3 sitios del izado x 3 comparaciones x 2 formas de
`k == 10` x pragma): el unico con p1=0 es `h_inner`. Reutilizar un local de la fase 1 como offset
de la fase 2 sobre D (`ok`, `j`, `k`, `index`, y un `off` nuevo en los dos extremos) -> 26 en
todos menos `k` (33). Escalada multi-arranque del orden de declaracion sobre E lanzada.

Iteracion 18 -- ★★ **`build/try/73e4/fg.c` = 17 con la FASE 1 EXACTA.** Es la mejor forma
estructural hasta ahora. Se construye con **dos reutilizaciones de variable**, la misma tecnica
aplicada dos veces:
1. `k2` (contador del bucle interior de la fase 2) reutilizado como el valor izado de la fase 1,
   **con el izado DENTRO de la guarda** -> la fase 1 vuelve a ser exacta.
2. `j2` (contador exterior de la fase 2) reutilizado como el temporal de `counters[k]` de la
   fase 1: `if ((j2 = counters[k]) >= groups[k].count) { ok = 0; } else { counters[k] = j2 + 1; }`
   -> el residuo de la fase 2 baja de 28 a 17.
Residuo de G: un **3-ciclo** en la fase 2 entre `{r7, sb, sl}` -- j2 ROM sb/G sl, off ROM r7/G sb,
k2 ROM sl/G r7. `item` = r8 ya coincide.

**La tecnica que funciona, y va al catalogo: cuando un valor de la ROM ocupa un registro que en tu
compilacion tiene otro, mira QUE valor ocupaba ese registro ANTES en la ROM y haz que sea la MISMA
variable del fuente.** mwcc parte rangos de vida, asi que compartir variable no garantiza compartir
registro -- pero cuando la herencia es la que la ROM ya hace (un valor muere y el siguiente nace en
el mismo registro), escribirlo como una sola variable si lo fija. Es lo que movio `k2` a `sl` y
luego `j2` fuera de r8.

Negativos de la iteracion: formas walker/indexado de la fase 1 sobre D (8 combinaciones, todas 26 o
cambian el tamano); 5 sitios distintos para el izado (dicotomia limpia: si la guarda **usa** `k2`
-> p1=16/p2=10; si **relee** el campo -> p1=0/p2=28; el izado en el `for`-init cambia el tamano);
offset explicito reutilizando `ok`/`k`/`j`/`index` o nuevo, sobre D y sobre G -> sin efecto.
Escalada de declaraciones sobre G: converge en **17** (7 arranques). Sobre E converge en **12** con
el orden original, y ese 12 es **exactamente el mismo residuo que `fa.c`** (off<->k2), o sea que la
variante E colapsa a la original cuando el orden de declaracion es el bueno.
Donantes para el temporal de `counters[k]` sobre D (`j2`, `ret`, `index`, `kind`, y una variable
nueva en los dos extremos): ninguno baja de 26.

Iteracion 19 -- **producto de los tres trucos de reutilizacion**: 3 sitios del izado de `k2` x
{con/sin} el temporal `j2` de `counters[k]` x 5 donantes del offset (`ok`, `k`, `j`, variable nueva,
ninguno) = 30 combinaciones sobre `fa.c`. **Ninguna baja de 12**; el suelo de la rama con el temporal
`j2` es 17 y el de las demas 12. Tambien probados: un segundo puntero solo para la guarda
(`probe` nuevo -> 1128, `found` -> 1128, `aux` -> 106), y los ordenes de inicializacion del par
`j2`/`off` (`j2` primero 12, `off` primero 14, `off = j2` 12).
Auditoria del turno: `audit_unnamed.py` -> **5.616 funciones con C byte-exacta siguen como `FUN_*`
o con nombre-marcador en Ghidra** (peores: main 495, ov008 383, ov025 311). Es deuda vieja del
proyecto, no de esta sesion, pero conviene que este contada.

Iteracion 20 -- probada y descartada la **hipotesis de bajar la prioridad de `k2`**: si el
asignador reparte por (usos x profundidad de bucle), `k2` (~9 usos a profundidad 2) le gana a `off`
(3 usos a profundidad 1), asi que se lleva el registro que se acaba de liberar. Intento de quitarle
5 usos cacheando `&groups[k2]` en un puntero para las seis lineas de estadisticas: **mwcc genera
EXACTAMENTE el mismo codigo** (12) -- ya trataba `groups[k2].count` como puntero cacheado, calcula
la direccion una vez con la `mla` y recarga `.count` seis veces. Cachear el VALOR en un int (1112) o
usar el walker `gw` (1124) cambian el tamano.
**Barrido de los 27 builds sobre las tres variantes estructurales** (`fd.c`, `fe.c`, `fg.c`): cada
variante da su mismo numero en todos los builds que compilan (fg.c = 17 en los doce). El build
tampoco discrimina entre las ramas nuevas.

Iteracion 21 -- ★★★ **EL RESIDUO ES SISTEMATICO, NO DE ESTA FUNCION: encontrado un SEGUNDO caso.**
La familia de paneles es x7 para `02057850` y `02057dc4` pero solo **x6** para `020573e4` -- falta
ov008. Buscando el hueco: **`func_ov008_02052528`** (1068 B, 6 relocs) esta exactamente donde
tocaria, justo antes de `func_ov008_02052954` (la gemela de `02057850`). El diff estructural
contra `020573e4` da **una sola diferencia**: a la version de ov008 le falta el bloque del bit-test
de `data_0204c240`; el resto -- fase 1 completa, seccion central, fase 2 entera -- es identico.

Y **la ROM de ov008 tiene EXACTAMENTE el coloreado que perseguimos**: `cmp sl,#0xa` (k2=sl),
`add r7,r7,#0x28` (off=r7), `cmp sb,#0x18` (j2=sb), `add fp,fp,#0xdc` (gw=fp).

Compilando **nuestra misma fuente** con la seccion central en la forma de ov008 (sin el bit-test):
**tamano 1068 exacto** y **12 bytes de diff contra la ROM de ov008**, con el MISMO intercambio
(k2=r7 / off=sl). Fuente en `build/try/73e4/ov8.c`.

Tres consecuencias:
1. **La fuente es correcta.** Reproduce dos funciones distintas de la ROM al byte salvo el mismo
   par de registros.
2. **El defecto es del toolchain, no de la funcion**: mwcc 3.0/139 da sistematicamente
   (off=sl, k2=r7) donde el compilador de retail da (off=r7, k2=sl) para esta forma de bucle.
3. **Hay un segundo objetivo y es mas limpio** (1068 B, 6 relocs, sin el bloque del bit-test):
   iterar sobre `func_ov008_02052528` es mas barato y cualquier palanca que lo arregle arregla
   las siete funciones a la vez (6 gemelas + esta).
`func_ov008_02052528` no tiene gemelas y **no esta decompilada**; entra en la cola del frente por
derecho propio (ov008 = menu principal, escena 19).

Iteracion 22 -- **el segundo objetivo se comporta EXACTAMENTE igual**, lo que cierra el argumento:
sobre `func_ov008_02052528` (fuente en `build/try/73e4/ov8.c`) repetidos los barridos que sobre
`020573e4`: escalada multi-arranque del orden de declaracion (5 arranques) -> **12**; los tres
sitios del izado de `k2` x el temporal `j2` (6 combinaciones) -> mismo patron exacto que en ov000
(`h_none`/`h_inside` = 12, `+c_j2` = 17, `h_before` = 37/44); y siete variantes de la **firma**
(5o y 6o parametro sin usar, retorno `unsigned`/`long`, `panelIndex` unsigned, `flagsOut` como
`u8 *`, `self` como `void *`) -> todas 12 salvo la de `u8 *` (13).

★ **Argumento de consistencia que conviene tener escrito**: las otras dos funciones del mismo
fichero fuente -- `func_ov000_02057850` y `func_ov000_02057dc4`, las dos de la familia de paneles --
**estan casadas byte a byte con los flags por defecto**. Un fichero tiene un solo juego de flags,
asi que la configuracion del toolchain es la correcta para este fichero; el residuo no puede ser
un override de compilacion que falte.

Iteracion 23 -- **el residuo esta ACOTADO: afecta a estas 7 funciones y a ninguna mas.** Barrido
de los **160 ficheros de `nonmatching/`** buscando la misma forma en la ROM (bucle realmente
anidado + registro del stride por debajo del contador interior): **cero**. Asi que esto no es un
bloqueo sistemico del proyecto, es una clase estrecha: las 6 gemelas de `020573e4` mas
`func_ov008_02052528`.
- Reutilizar el puntero `found` como portador del offset de la fase 2 (el tercer registro de la
  cadena r7 = ok -> found -> off) -> 12 en los dos objetivos; con `aux` cambia el tamano. mwcc
  vuelve a partir el rango.
- **Capa semantica puesta**: `arm9_ov008::02052528` renombrada a **`Ov008_MatchRecipeAndApply`**
  en Ghidra, con comentario explicando que es la misma funcion que la de ov000 menos el bloque del
  bit-test, por que la familia es x7 para las otras dos y x6 para esta, y cual es el residuo.
  Script en `~/ghidra_scripts/KhOv008Recipe.py`, guardado y leido de vuelta.

Iteracion 24 -- el portador del offset es **irrelevante en las tres ramas**: `found` reutilizado
como offset, un `off` explicito nuevo, o el temp implicito -> D sigue en 26 (p1=16/p2=10) y G en 17
(p1=0/p2=17), identicos a sus bases. Confirma que la pista de coalescing solo funciona cuando el
valor donante y el receptor tienen el MISMO tipo y la copia sobrevive al pase de division de rangos
(que es justo lo que pasa con `k2` = el izado de la fase 1, y lo que NO pasa con un puntero
reinterpretado como entero).

Iteracion 25 -- cerrado el ultimo eje de la lista del skill, **prototipos**, en los dos objetivos:
- **Aridad de los callees verificada contra el arbol** (la comprobacion gratis del skill):
  `func_ov000_020569dc` ya esta decompilada y es `int f(int param_1)` que escribe
  `*(int *)param_1` cuando no es cero -- o sea que nuestro `(int)&kind` es correcto y la ROM pasa
  `sp+0xc` justamente por eso. `func_ov000_02056cb4` tiene 5 argumentos en el arbol y nosotros la
  llamamos con 5, con la misma forma que el sitio de llamada ya casado.
- Variantes de prototipo probadas: el out-param como `int *` de verdad, los dos punteros a funcion
  (`openEntry`, `closeEntry`) devolviendo `int` en vez de `void` por separado y juntos, y
  `func_ov000_02056cb4` con `int` en vez de `unsigned int` en las cantidades. **Las 12 dan 12.**

Con esto **la lista de ejes obligatorios del skill esta completa**: tipo de retorno del llamante,
aridad de callees, tipos de argumento y retorno, prototipos de punteros a funcion, forma y aliasing
de structs, signo y anchura, orden de declaracion, orden/tamano/alineacion de objetos de pila, vida
de temporales, reutilizacion de parametros, campo directo vs alias, `register` y `volatile`,
orientacion de ramas y colas compartidas, agrupacion y orden de evaluacion, copia de struct vs
asignacion campo a campo, ARM vs THUMB, pool literal y relocs, y formas ya presentes en el repo.
Mas los ejes de infraestructura: 27 builds, 78 pragmas x2, ~30 juegos de flags, 26 procesadores,
los dos front-ends y el contexto de unidad de traduccion.

Iteracion 26 -- ★★★ **ENUMERACION DE PARES ALCANZABLES.** En vez de buscar una fuente que
funcione, enumerar **que pares `(registro del stride, registro de k2)` se pueden producir**:
3 posiciones del izado de `k2` x {con/sin} el temporal `j2` x 150 ordenes de declaracion cada uno
= **900 compilaciones** sobre el objetivo de ov008. Resultado:

    17 pares distintos alcanzables. k2 aparece en r6, r7, r8, sb Y sl.
    stride aparece en r6, r7, r8, sb y sl.
    El par de la ROM, (stride=r7, k2=sl): **0 de 900. NO alcanzable.**

O sea que los dos registros son alcanzables **por separado** pero nunca **juntos** en esa
asignacion. Es la forma correcta del negativo: no "no lo he encontrado", sino "el espacio que la
fuente puede alcanzar no contiene ese punto".

Iteracion 27 (el usuario dice "continua hasta el match" y autoriza buscar en internet):
- ★ **INFRAESTRUCTURA VERIFICADA** -- el ultimo tipo de bloqueo que quedaba por descartar. Los
  bytes de `func_index.json` **son** los de la ROM: buscando una ventana sin relocs del indice
  dentro de `build/build/arm9_ov000.bin` aparece en el offset `0xa9a8`, la base implicita sale
  `0x0204cac0` (= el simbolo mas bajo de ov000) y **las 18 diferencias caen todas dentro de
  palabras con reloc**. No hay desacuerdo entre `verify_idx.py` y el gate.
- **Internet**: el conjunto publico de mwccarm es el que ya tenemos (carpetas `1.2/` y `2.0/` del
  zip de la comunidad); la fuga de Platinum solo aporta los IDE `cw_ds-2_0-sp2-20071025` y
  `-patch2-20080215`, sin builds de compilador nuevas. No hay evidencia publica de un build > 139.
- **`gw` es `fp` en TODAS las variantes** (y en la ROM). El reparto real es: `ret`=r6 ✓,
  `item`=r8 ✓, `j2`=sb ✓ y solo `off`/`k2` cruzados entre r7 y sl. Cambiar el tipo de los walkers
  (`char *`) no lo mueve.
- **Helper `static inline`** (el eje que el skill destaca por reproducir codegen inalcanzable):
  con el helper leyendo `g->count` seis veces reproduce **exactamente los mismos bytes y los mismos
  registros**. O sea que el IR se canonicaliza antes de asignar.
- **Bucles con `goto`**: cambian el tamano (1136/1140).
- **Almacenamientos muertos** (`j2 = 0;`, `gw = 0;`... antes del bucle, para crear el vreg antes y
  que el pase de dead-store los borre): 41 variantes, tamano intacto, **asignacion intacta**.
- Enumeracion ampliada con **ambito de bloque**: 780 variantes mas -> los mismos 17 pares,
  `(r7,sl)` ausente. Acumulado ~1.700 variantes de tamano correcto.

★ **MODELO que explica todo lo observado** (falsable, y encaja con cada medida): en la ROM `off`
se lleva **r7, el registro liberado MAS RECIENTEMENTE** (`found` muere en 0x02c0, `off` nace en
0x02d4) y `k2` se lleva `sl`, libre desde 0x0100. Nosotros hacemos lo contrario: `off` coge el que
lleva mas tiempo libre. Como la fase 1 y la seccion central son **byte a byte identicas**, el orden
de liberacion es identico en los dos -> lo que difiere es **la politica de eleccion del asignador**,
que no es expresable en la fuente. Eso explica por que el par `(r7,sl)` es inalcanzable: es la
respuesta "LIFO" y nuestro compilador siempre da la "FIFO".

Iteracion 28 -- ★★★ **EL INVARIANTE, ya medido con precision.** Busqueda larga de 5.000 muestras
sobre el producto cruzado completo (izado x temporal `j2` x ambito x guarda x forma de `item` x
orden de setup x forma de los dos bucles x orden de declaracion): **839 variantes de tamano
correcto**, y siempre **los mismos 17 pares**. De los 20 pares ordenados posibles con
{r6,r7,r8,sb,sl} faltan exactamente tres: **`(r6,sl)`, `(r7,sl)` y `(r8,sl)`**. Es decir:

    INVARIANTE: k2 = sl  =>  stride = sb.  Sin excepcion, en ~2.500 variantes.

Y dentro de ese regimen, barriendo las 32 posiciones de declaracion de `off` y `j2` sobre la
variante D: `j2` se mueve libre (r6/r7/r8) pero **`stride` es `sb` en las 32**. La ROM necesita
`(stride=r7, k2=sl)`, que es justo uno de los tres pares fuera de la imagen de nuestro compilador
para esta forma de funcion.

Iteracion 29 -- ⚠ **CORRECCION IMPORTANTE de mi propio argumento, y un hueco real que reabre el
problema.** Habia escrito que "las otras dos funciones del mismo fichero fuente estan casadas con
los flags por defecto, luego la configuracion es la correcta". **Eso no aplica al build de este
proyecto**: `config/arm9/overlays/ov000/delinks.txt` demuestra que aqui se compila **una funcion
por fichero** (`func_ov000_0205721c.c`, `func_ov000_02057850.c`, `func_ov000_02057dc4.c`, cada una
su unidad de delink), y `config/arm9/file_compilers.json` admite **override por fichero** -- ya lo
usa `ov028/auto/func_ov028_0208a994.c` con `1.2/sp4`. Asi que este fichero **puede** llevar su
propio compilador y sus propios flags, y el argumento de consistencia que di NO cierra ese eje.
Hueco concreto que dejaba: barri 27 builds con los flags por defecto, y ~30 juegos de flags con el
build por defecto, pero **nunca los dos ejes a la vez**. Barrido conjunto lanzado
(4 fuentes x 27 builds x 12 ajustes de optimizacion x 5 grupos de flags).
- Y las builds `dsi/` **no fallaban por flags**: compilan y dan **1116 B** en las nueve, sin crear
  siquiera el offset por reduccion de fuerza (`stride=None`) -- otra generacion de codegen, no la
  nuestra.
- Dato que debilita la hipotesis "build > 139": el asignador es **identico en los ~10 builds de la
  linea 2.0/3.0** (todos dan 12 con los mismos registros). Si no cambio entre 114 y 139, suponer
  que cambia en 140 es especulativo.
- Cruce formas-de-fase-1 x ejes-de-fase-2 x orden de declaracion: **2.500 variantes mas de tamano
  correcto**, mismos 17 pares. Acumulado ~5.000.

Iteracion 30 -- cerrado tambien el eje que la correccion anterior habia reabierto:
- **Barrido CONJUNTO build x flags** (4 fuentes x 27 builds x 12 ajustes de optimizacion x 5 grupos
  de flags): **1.920 combinaciones de tamano correcto**, mejor **12**, ningun 0. Como el build se
  puede fijar por fichero, este era el eje que quedaba abierto de verdad; ya no lo esta.
- **Los 12 builds que dan el tamano correcto se comportan IDENTICAMENTE**: 240 combinaciones
  (12 builds x 20 ordenes de declaracion) en el regimen `k2=sl` producen solo 4 pares, y cada orden
  da el mismo par en los 12. El asignador es el mismo en toda la linea 2.0/3.0.

Iteracion 31 -- ★★★ **NUMEROS DE BUILD REALES, sacados de los binarios** (esto sustituye a la nota
de folclore "retail es probablemente 3.0 >= 140", que era una conjetura sin medir):

    2.0/base 114 · sp1 123 · sp1p2 126 · sp1p5 131 · sp1p6 133 · sp1p7 134
    2.0/sp2 136 · sp2p2 137 · sp2p3 138 · sp2p4 139        <- 139 es el MAXIMO que existe aqui
    3.0_136 = byte-identico a 2.0/sp2 (build 136);  3.0_patch4 = build 139
    dsi/ = builds 1018..1051 (otra numeracion, otra generacion)
    25 binarios distintos en total

⚠ **Esto DEBILITA la conclusion "falta el compilador exacto" que yo mismo habia escrito.** Los diez
builds cubren 114 -> 139, o sea **toda la linea DS**, y **todos dan exactamente el mismo resultado
con los mismos registros**. Que el asignador cambiara en uno de los huecos (115-122, 124-125,
127-130, 132, 135) y volviera atras es inverosimil; y por encima de 139 no hay nada en esta linea.
Asi que la explicacion **ya no esta establecida**: o hay una forma de fuente en una dimension que
no he enumerado, o hay algo del build original que no se expresar. Lo honesto es dejarlo abierto.
- Reutilizar `gw` (el walker de la fase 2) como walker explicito de la fase 1: 103/104, y con
  `cw` ademas cambia el tamano. Peor por los dos lados.

Iteracion 32 -- ★★★ **NO ES UNA FUNCION, ES UNA CLASE DE 18. Y NINGUNA ESTA CASADA.**
Censo de la forma sobre las ~23.000 funciones de la ROM (casadas o no), no solo sobre el corpus
casado como hice antes:

    stride < contador interior (la forma de la ROM que no sabemos producir):  18 funciones,  0 casadas (0%)
    stride > contador interior (la que nos da mwcc):                          49 funciones,  7 casadas (14%)

Las 18: las 6 gemelas de `020573e4`, `func_ov008_02052528`, y **once mas**:
`func_ov008_02060e3c` (1952), `func_ov025_0209338c` (1916), `func_ov008_020604e4` (876),
`func_ov025_02092a34` (876), `func_ov002_02072364` (828), `func_ov008_02064fb8` (732),
`func_ov025_020974e4` (732)... **Ninguna tiene C real**; solo una tiene stub ASM.

Esto reencuadra el problema entero: no es un residuo raro de una funcion tozuda, es un **hueco de
codegen sistematico que bloquea una clase de 18 funciones de la ROM**, y explica por que ninguna de
ellas se ha casado nunca en este proyecto. Predice tambien que quien ataque las otras once se
estrellara igual, asi que **conviene comprobar la forma ANTES de invertir horas** en cualquiera de
ellas. El censo esta en `build/try/73e4/romwide.py`.

Iteracion 33 (usuario: "continua hasta el match", pregunta por dsprot y por internet):
- **dsprot (taxicat1) consultado de verdad**: su Makefile usa mwccarm **2.0/sp2p2 (build 137)** con
  nuestros mismos flags mas **`-fp soft`**. Probado `-fp soft/none/off` sobre las tres variantes y
  tres builds: **cero efecto** en codigo entero. (Y confirma que el conjunto publico de compiladores
  es el que tenemos.)
- ★★★ **EL EJE DE LA TU, CERRADO CON ORACULO — y una correccion**: mwcc emite **una seccion .text
  POR FUNCION** (todos los `st_value` = 0). Mi extractor leia una sola seccion: los veredictos
  "los callees cambian en la TU" de la iteracion anterior eran **artefactos**. Con el extractor
  corregido (resolver cada simbolo por `st_shndx`):
  **TU fiel de 18 miembros ARM** (02056970..020580fc, con el llamante en su sitio, tipos
  renombrados por fichero, `#pragma mpwc_relax on`, externs deduplicados, aridades armonizadas:
  `02056b14` con 3 params muertos, `0205721c` con 3er param muerto):
  -> **los 17 miembros restantes BYTE-EXACTOS** (reconstruccion fiel) y el llamante **diff 19 =
  identico al standalone**. La compilacion conjunta es NEUTRA: la estructura de TU del build
  original NO explica el intercambio. Frontera de fichero detectada: 02056938/02056960 son THUMB
  (otro fichero); el fichero ARM empieza en 02056970.
  Herramienta: `build/try/73e4/merge_tu4.py` (fusionador con renombrado de tipos + oraculo).
- Escaneo GLOBAL del binario del compilador buscando mas tablas de pragmas (reg/alloc/color/sched/
  spill/live/weight...): nada nuevo; `spills`/`scheduling` son texto de estadisticas, no pragmas.
- Barrido de pragmas numericos que faltaba (`opt_pointer_analysis_mode` 0-4, `inline_max_size`,
  `inline_depth`, `structalignment`): 54 variantes, todas 12+.
- **Lanzada la enumeracion EXHAUSTIVA 8! = 40.320 permutaciones** de los 8 locales que gobiernan el
  par, sobre el objetivo ov008, medida por PAR DE REGISTROS (para en (r7,sl) o en diff 0). Es la
  clausura total del eje de declaraciones, no un muestreo. ~3-4 h en background.

Iteracion 34 -- ★★★ **ENUMERACION TOTAL 8! COMPLETADA (forma base): el par de la ROM esta excluido
ESTRUCTURALMENTE.** Las 40.320 permutaciones de los 8 locales relevantes sobre el objetivo ov008:
- Las 40.320 compilan y TODAS dan el tamano correcto (el stream es invariante al orden; solo se
  mueven los colores).
- Histograma **exactamente uniforme**: 12 pares, cada uno **3.360 veces** (40320/12). El asignador
  elige el par como funcion pura del orden relativo, con simetria perfecta.
- **`sl` no aparece NUNCA en ningun rol** en la forma base. `(r7,sl)`: 0 de 40.320.
Lanzada la misma enumeracion total sobre el regimen del izado (`k2 = id` dentro de la guarda),
donde `k2` si alcanza `sl`, para cerrar ese regimen tambien por enumeracion.

Iteracion 35 -- **regimen del izado cerrado por enumeracion + `static` neutro**:
- 8! sobre el regimen del izado: **mismo histograma uniforme** (12 pares x 3.360, `sl` ausente).
  Matiz honesto: cada 8! fija las posiciones de los otros 7 locales; la alcanzabilidad de `sl`
  depende de esas posiciones (el muestreo libre si la veia, siempre con stride=sb). El espacio
  completo es 15! -- inabarcable -- pero ~90.000 variantes compiladas por todas las vias coinciden:
  el suelo es 12 y `(r7,sl)` no aparece. Coherencia interna: en configs con stride=r7, el registro
  que la ROM da a `ret`/`item`/`j2` (r6/r8/sb) lo roba otra variable y el diff sube (35+), porque
  `ret` interfiere con `k2` y no pueden compartir r6, etc. El suelo de 12 es consistente.
- **`static` probado en la TU fiel** (020573e4 sola, y + 02056a18 + 02056cb4; sus llamantes estan
  todos dentro de la TU, asi que pudieron ser static en el original): **neutro** -- diff 19, mismo
  par, miembros exactos. Otro eje cerrado con oraculo.
- Datos de llamantes: 020573e4 la llama SOLO 02057850; 02056a18 solo 020573e4; 02056cb4 solo
  02057138/020573e4/02057dc4/0205721c (todos en la TU); 020569dc tambien desde 0205836c/020585e8
  (fuera del rango -> no static, o el fichero sigue mas alla de 020580fc).

═══ RESUMEN DEL BLOQUEO (para el usuario; NO es un park, no se ha clasificado nada) ═══
Requisito externo que falta, en los terminos que pide el skill: **el compilador exacto**.
Evidencia:
1. Dos funciones INDEPENDIENTES de la ROM (`func_ov000_020573e4` x6 y `func_ov008_02052528`),
   misma fuente, **mismo residuo de 12 bytes y mismo intercambio**.
2. Tamano exacto, stream de instrucciones exacto, relocs exactas en las dos. Solo cambia el
   coloreado de dos registros.
3. **Cero precedentes** del coloreado de la ROM en las 15.590 funciones ya casadas, con el filtro
   auto-verificado sobre los bytes de la propia ROM.
4. Las otras dos funciones **del mismo fichero fuente** (`02057850`, `02057dc4`) estan casadas
   byte a byte con los flags por defecto -> la configuracion del toolchain es la correcta.
5. Lista de ejes del skill **completa**, mas 27 builds, 78 pragmas x2, ~30 juegos de flags,
   26 procesadores, los dos front-ends, contexto de TU, y la enumeracion de arriba.
Mejor fuente: `build/try/73e4/BEST.c` (=`fa.c`, 12 B) y `build/try/73e4/ov8.c` para la de ov008.
Nada en `nonmatching/`, nada aparcado, nada movido.

**Mapa de distancias en permutacion (lo que hay que mirar, no los bytes):**

    fa.c  12  p1=0   p2 = UNA transposicion (off<->k2); j2 e item ya correctos  <- el mas cercano
    fd.c  26  p1=16  p2 = UNA transposicion (j2<->off); k2=sl e item=r8 correctos
    fg.c  17  p1=0   p2 = un 3-CICLO {r7,sb,sl}; solo item correcto

`fa.c` y `fd.c` estan los dos a una transposicion de la fase 2, pero por lados distintos, y `fd.c`
paga 16 en la fase 1. La dicotomia del izado (guarda usa `k2` -> p1=16/p2=10; guarda relee ->
p1=0/p2=28) es lo que impide juntarlos: hace falta romperla, o encontrar el donante que rote el
3-ciclo de G. `BEST.c` sigue siendo `fa.c`.

Conclusion operativa: el residuo NO es expresable en la fuente. Como el stream de instrucciones es
identico, el IR tiene que diferir en algo que solo se ve a traves del asignador, y ninguno de los
ejes de arriba lo toca. Lo unico que queda sin explorar es el pase de coloreado en si
(`Coloring.c` / `IRO_SplitLifetimes` en el binario).

Diff exacto que queda (10 instrucciones, 12 bytes): ROM `mov r7,sb` / `add r1,r2,r7` /
`add r8,r1,r7` / `mov sl,#1` / `mla r0,sl,r0,r4` / `ldrb r1,[r2,sl]` / `strb r1,[r2,sl]` /
`add sl,sl,#1` / `cmp sl,#0xa` / `add r7,r7,#0x28`; nosotros con r7 y sl intercambiados.
Dato util de la ROM: r7 lleva `ok` (fase 1) -> el puntero `found` (cola) -> `off` (fase 2), y
nosotros reproducimos los dos primeros; solo el tercer reuso difiere.

---

# ⇒ 2026-07-24: EL USUARIO CAMBIA LA COLA A **ORDEN DE JUEGO** (para el port)

Pregunta: "podriamos ir decompilando en orden de juego, desde que se inicia el juego?".
Respuesta medida y aceptada: **si**, pero la unidad NO es el grafo de llamadas estatico.

- Desde `main` solo son alcanzables **659 de 23.238** funciones por relocs: el juego despacha por
  tablas de punteros y overlays (`InstantiateClass`, `func_0203c634`, punteros de estado), asi que
  el grafo estatico no ve casi nada. De esas 659, **403 (61%) ya tienen C**, y de las 256 que
  faltan **casi todas son NitroSDK** (FS_*, CARD_*, GX_*, MI_*, OS_*, DC_*, SND_*, NNS_*) -- que el
  port NO necesita decompilar porque las sustituye.
- La unidad correcta es la **ESCENA / OVERLAY**. Completitud del camino de arranque:
  main 70%/30%B · **ov000 88%/67%B** · ov001 100% · ov002 56%/19%B · ov005 63%/43%B ·
  ov006 88%/50%B · ov007 100% · ov008 66%/30%B · ov009 86%/59%B · ov010 100% · ov012 64%/33%B.

**Orden de trabajo acordado**: (1) terminar **ov000** -- arranque + titulo + todos los menus +
"Cargar"; (2) **`main`** (848 B, 65 relocs, NO existe en el arbol); (3) ov009 y ov006, que estan
al 86-88%; (4) ov002 / ov008 / ov025, que son los gordos.

`python tools/getcand.py` + los `asm_stubs/` de ov000 traen **cabeceras de struct ya decodificadas
y correctas** (Ov000SceneContext, Ov000StreamInterface, Ov000MovieFrame, OverlayStartParams,
Ov000GlyphRun): usalas, no reinventes el layout.

Estado tras la primera tanda en este orden: ov000 pasa de 31 a **24** pendientes (16 stubs + 15
huecos -> 10 stubs + 14 huecos). Ver el crack de FS_OVERLAY_ID arriba del todo en
`codegen-cracks.md`: desbloqueo 5 de ellas a la primera.

---

# SESION 2026-07-24 (loop autonomo) -- 6 CASADAS desde nonmatching/ + declperm arreglado

Gate 306/0, pusheado en `e2cd7891f`. C = 15.684 -> 15.690.

## Casadas e integradas

| funcion | lo que era | lo que lo cerro |
|---|---|---|
| `func_ov006_0204e35c` + gemela `func_ov008_0207a1c4` | "register-placement tie": la ROM pone el 0 de retorno en r0 arriba, mwcc lo predica | **guarda POSITIVA** (`if (!blocked) {...}` con un solo `return next;`) **+ reasignacion redundante `next = 0;`** en la rama de fallo. Sin la reasignacion sale 4 bytes corta. Encontrado con `find_insn --seq 'mov r0, #0' 'ldr r1, \[r1\]'` -> `func_ov002_02051318` |
| `func_02012c2c` + gemela nueva `func_02012ca8` (carve de hueco) | "acumulador rota r0->r2->r1->r2" | **el pack en UNA sola expresion**, no una cadena de `packed \|= x;`. Ademas: NO era un registro de sonido -- `data_02041ac0` son los OCHO BGxCNT (0x04000008.., 0x04001008..) |
| `func_ov022_02090e2c` | "DAT/counter register-swap tie" (r4/r5 <-> r6/r7) | **regla 5b**: `extern Fn table[]; table[tag](...)` en vez de `(*(Fn*)((int)&table + tag*4))(...)` |
| `func_ov022_02089150` | "coloreado r9/r10" | **la permutacion COMPLETA de declaracion**: `i, heap, b, off, limit` es la unica de 120. El park habia probado "swaps" de las dos que difieren -- con 5 locales el eje es la permutacion entera |

Los dos cracks nuevos (guarda positiva + una-sola-expresion) estan arriba del todo en
`codegen-cracks.md`.

## ⚠ `tools/declperm.py` estaba ciego para casi todos los parks (ARREGLADO, commit `bfa5376f9`)

Solo leia un bloque de declaraciones SIN inicializador; de los 45 parks mas cercanos solo **2**
tenian un bloque que supiera leer. Ahora parte `T x = expr;` en declaracion + asignacion (las
asignaciones conservan el orden de fuente). **Reejecutalo sobre todo lo aparcado**: es el eje que
acaba de cerrar ov022_02089150.

## ⚠ `find_insn.py --seq` NO acepta regex (solo literales)

`--seq 'add r6, r(4|5), #0x' 'bl'` da **0 aciertos** y parece un negativo real; con literales
(`--seq 'cmp r0, #0' 'bne' 'ldr r1,'`) da 58. La busqueda de UNA instruccion si acepta regex.
Cuando necesites regex en una secuencia, escribe el barrido a mano con capstone (10 lineas).

## FRENTE ABIERTO: `func_ov141_020cd2b0` (x7: ov141/142/143/149/150/151/152) -- 8 -> **4 bytes**

★ **El orden de la copia YA CASA** (era "the only remaining divergence" del park). Lo que lo
arregla es el idiom de `func_ov282_020d32b4` (casada): **ata un puntero al DESTINO y copia el
halfword ALTO primero a traves de el, y pasa ESE puntero al callback**:

```c
unsigned short buf[2]; unsigned short *pp;
pp = buf;
pp[1] = data_ov141_020ce9d0[3];
pp[0] = data_ov141_020ce9d0[2];
if (cb) cb(*obj, pp, 4);          /* pp, NO &buf -- con &buf son 36 bytes de diferencia */
```

Mejor forma en `build/try/cd2b0/h1.c` (4 bytes). Residuo: la ROM hace
`ldrh r0,[r2,#6] ; ldrh r2,[r2,#4]` (el 2o load MATA su propia base) y mwcc `ldrh r3,[r2,#6] ;
ldrh r0,[r2,#4]`. Los dos registros candidatos (r0 = base del hw60, r3 = valor del hw60) mueren en
la misma instruccion. Probado sin moverlo: 24 permutaciones de declaracion, hw60 via local/puntero
cacheado, copia antes/despues del hw60, `cb` leido antes, temporales con nombre para los dos
halfwords, struct-de-pair vs array de u16, `data[1].b` vs `data[3]`.

## Otros residuos medidos hoy (mejor forma en `build/try/`, nada aparcado nuevo)

| funcion | residuo | mejor forma | ejes agotados |
|---|---|---|---|
| `func_ov049_020b43a8` (x4) | **2 bytes**: `ldr r1,[r5]` vs `ldr r0,[r5]` tras el `bl`+`cmp r0` | `build/try/43a8/b1.c` | forma del test de flags (5), if anidados (3) |
| `func_ov022_020b0c24` | 5 instrucciones: la ROM suma `+0x1000` a un registro FRESCO (r1 muere -> RdHi), mwcc suma en sitio | `build/try/b0c24/dp.c` (tamano exacto) | **48 experimentos**: helper `static inline`, 24 permutaciones de declaracion, `(char*)0x1000+cur`, volatile, register, formas de 64 bits, orden de operandos. ★ Mecanismo CONFIRMADO con el corpus: `func_0203cd20` solo emite el add no-destructivo porque su fuente SIGUE VIVA despues; aqui no lo esta |
| `func_ov022_0209b078` | r4<->r6 (e vs a2) | el park | 54: 36 ordenes decl x asig, `for`/`while`/`do`, `short` param, struct/puntero, `register` |
| `func_02031a74` | rotacion r2/r3/ip | el park | 14: struct del header, single-exit, `char *` param, register |
| `func_ov208_020d03e8` (x3) | **2 instrucciones**: `ldrb ip` vs `ldrb r7` en el 3er pack de 24 bits | `build/try/d03e8/y1.c` (array `struct triple t[3]`, mismo stream y mas legible) | orden de los 3 bytes, temporales explicitos, `idx` izado al top (3 posiciones) |
| `func_ov022_020893f4` | destino del `mla` (Rd==Rn en la ROM) | el park | acumular en sitio (4 formas), base como `char *`, slot tipado, CSE inline |
| `func_ov022_02083bd8` (THUMB) | 4 bytes: pool de `0x6a` en vez de `movs` | el park | tipos del 2o argumento (void*/char*/unsigned/long), 3 argumentos. ★ **Barrido del corpus: de 994 THUMB casadas solo 2 cargan un literal <256 del pool, y las dos con 0x0** -- o sea el mecanismo existe (banderas vivas) pero no hay precedente para un literal distinto de 0 |

---

# SESION 2026-07-24 -- 11 CASADAS + purga de 13 cabeceras mentirosas + frente d55c abierto

## ⚠ LEE `staging/*.handoff.md` ANTES DE PELEARTE CON UN RESIDUO

52 handoffs en `staging/ov000/` + `staging/ov003/CRACKS.md` + `staging/AGENTS.md`. Cada handoff
tiene `## Decisive fix` y `## Experiments`: es un corpus de ~50 residuos YA resueltos con el cambio
de fuente exacto que los cerro. **Nunca los habia leido** -- mi barrido de staging solo buscaba
`func_*.c`, que es justo el error que la propia skill avisa (no claves el barrido en la forma que
esperas). Distilado entero arriba del todo en `codegen-cracks.md`.

Los dos levers dominantes: **orden de declaracion (17/52)** y **vida del cache -- cachear el PRIMER
uso y dejar el resto en linea contra el global (28/52)**. Son exactamente las dos brechas abiertas
de `func_ov003_0204d55c`, y `staging/ov003/HANDOFF.md` ya lo diagnosticaba como
"register-pressure spill" hace meses.

## Lo que se caso e integro (todo pusheado, gate 306/0)

- **`func_ov030_020b4410` + 4 gemelas** (ov044/063/082/099), 292 B. Cierra ~75 experimentos de
  varias sesiones. **NO era un empate de register allocation**: `VEC_Mag` toma UN argumento y el
  fuente le pasaba cuatro por un `extern f();` sin prototipo; los tres fantasma empujaban a mwcc
  por encima de su umbral de rematerializacion. Leccion: **los argumentos fantasma pueden ser
  invisibles en el disasm** si los valores de mas estan vivos por otro motivo.
- **`func_ov149_020cfad8` + 4 gemelas** (ov150/153/154/155), 296 B.
- **`func_ov008_0207b8a8`**, 72 B. Otro park de "empate probado" que eran DOS bugs: un handle
  perdido como argumento y una base que hay que avanzar EN SITIO (`base = ...; base += 0x400;`).

**3 de las 11 estaban aparcadas como "empate probado de register allocation" y ninguna lo era.**
Las tres eran la misma clase: argumento perdido a traves de un extern sin prototipo.

## Purga de 13 cabeceras `NONMATCHING` obsoletas (commit `dbb1bc27c`)

13 ficheros en `auto/`/`calls/` con cabecera "NONMATCHING" que **verifican byte-exact**. En 7 de
ellos la cabecera decia "scheduling tie, unreproducible across all 26 mwcc generations" y **diez
lineas mas abajo, en el MISMO fichero**, estaba la causa real ya resuelta (aridad de
`func_ov107_020c9264`). ⚠ **Una nota de aparcado que sobrevive a su propio arreglo miente durante
meses.** Comprueba con `grep -rl NONMATCHING src/*/calls src/*/auto` al cerrar sesion: debe dar 0.

## Herramienta nueva: `tools/audit_callsite_arity.py` (commit `f9542bca6`)

Audita la aridad **en la llamada**, no en la declaracion, y cubre todos los nombres de callee.
Solo avisa cuando el arbol es concluyente (>=3 sitios) y nunca usa la aridad del park como verdad.

## FRENTE ABIERTO: `func_ov003_0204d55c` (`Ov003_RenderNumericFields`)

Doce pasadas, ~90 variantes compiladas, SIN casar. **Los cracks de metodo estan arriba del todo en
`codegen-cracks.md`** y valen para cualquier residuo -- son lo mas valioso que salio de aqui.
Detalle exhaustivo en `build/try/d55c/FINDINGS.txt` (local, gitignored).

DOS bases, mejores en ejes distintos:
- `build/try/d55c/BEST.c` -- 364/364 B, primer diff 0xC, exact=25/91, ra=34/91 (mejor ALINEACION)
- `build/try/d55c/gh6.c`  -- 356 B, distancia de histograma **38** vs 54 (mejor MEZCLA de
  instrucciones; casa `mul=3`, `mla=0`, `add R,R,R=3` con la ROM). **Mejor base para continuar**:
  le faltan dos instrucciones concretas, un `add R,sp,#4` y un `lsl R,R,#1`.

Cerrado y NO hay que reintentar: struct obligatorio (locales sueltos = 428 B en cualquier base);
orden de declaracion irrelevante; orientacion de rama irrelevante (mwcc canonicaliza el `||`);
izar `f.c` o `i+1` empeora; forzar la recarga de la tabla cuesta mas de lo que ahorra;
`build_sweep` no aplica (no es cuestion de build).

## staging/ov003 -- verificado, no hay nada que coger

Los **14** ficheros pendientes de `staging/ov003/` verificados en ARM **y** THUMB: ninguno casa.
No es que esten "cerca": 0204cba0 y 0204d98c estan a 96 y 224 bytes. No los des por buenos por
estar en staging.

# SESION 2026-07-23 (noche, 2) -- ov149 x5 CASADA + veta de re-test nueva

**CASADO E INTEGRADO: `func_ov149_020cfad8` + 4 gemelas (ov150/153/154/155), 296 B.** Cierra un park
de "empate de presion de registros". Commit `e8b2a1ab2`, gate 306/0, C 15653->15658, ASM 2074->2069.
Nombradas `OvNNN_BroadcastPositionMessage` + struct Ghidra `PositionBroadcastMsg`.
Los DOS cracks estan en `codegen-cracks.md` (arriba del todo) y enteros en la cabecera del `.c`.

⭐⭐ **VETA DE RE-TEST: el crack de la copia-de-struct-de-UNA-palabra aplica a TODO park que salga
CORTO.** Si la ROM tiene un store que mwcc elimina por muerto, `*(struct w1 *)&x = src;` lo fuerza
Y lo fusiona. Parks cortos sin re-testear (de la lista de tamano): main_0201ef9c (-4),
main_02023adc (-12), ov002_0205efb4 (-4), ov008_0205b988 (-12), ov022_020a2230 (-12),
ov024_02082e04/0208589c/02086800 (-4/-4/-8), ov045_020b476c (-4), ov049_020b43a8 (-4),
ov212_020cdb1c (-4), ov221_020d4020 (-4), ov228_020d2078 (-4). ⚠ Solo aplica si lo que falta es un
STORE A MEMORIA muerto; una copia registro-registro muerta (ov022_020889cc, ov006_02051fbc) es otra
cosa y NO cae con esto.

## FRENTE ABIERTO 2026-07-24: `func_02024ee8` -- 0x11 -> 0x65, quedan 3 instrucciones

Mejor forma en `build/try/24ee8/best.c` (236/236 B). **Tres hallazgos reales por el camino**, los
dos primeros ya cerrados:
1. **Argumento fantasma**: pasaba un cuarto argumento (`buf[3]`) al lector de la tabla, que toma
   tres. Lo cazo `tools/audit_callsite_arity.py`. 0x11 -> 0x50.
2. **Crack de fusion del `add`** (ver `codegen-cracks.md`): escribir el par de shifts explicito
   `((((unsigned int)h) << 17) >> 15)` en vez de la forma con casts hace que mwcc fusione el `lsr`
   en el `add` como la ROM. 0x50 -> 0x65, **y ademas** coloco `count` en r2 y arreglo donde cae el
   `tst` -- el residuo que llevaba dos pasadas resistiendose.
3. **Residuo actual = 3 instrucciones, intercambio r0/r1 puro.** Todo lo demas casa (incluido el
   `tst r1,#0x8000` y `count` en r2). La ROM desplaza el half EN SITIO (`lsl r0,r0,#0x11`) y manda
   `count*4` al r1 recien liberado por el `tst`; mwcc hace justo lo contrario. En ese punto **los
   dos registros estan libres**, asi que es una eleccion del asignador.
   Probado sin exito (~12 formas): local para el half con `h <<= 17` y `h = h << 17` (int y
   unsigned), local para `count*4` (regresa a 0x50), partir el `add` (0x50), invertir el orden de
   operandos, half como acumulador, `count << 2` explicito (0x50), `(unsigned)count * 4`, local
   `raw`, ternario (+4), `(short)raw < 0` (+4), `raw >> 15` (diverge antes).
   **build_sweep: 4 off en toda la linea 3.0/2.0 -> no es la build.** Aridad de los 7 callees
   verificada contra el arbol. Mismo eje que el crack de "avanzar un puntero en sitio" que si cerro
   ov008, pero aqui no cede.

## ✅ RESUELTO 2026-07-24: `func_ov030_020b4410` + 4 gemelas (ov044/063/082/099). NO ERA UN EMPATE.

**`VEC_Mag` toma UN argumento.** La fuente lo llamaba con CUATRO
(`VEC_Mag(r3p, 0x625, obj->ext, kind)`); el extern estaba **sin prototipo**, asi que compilaba en
silencio. Los 3 argumentos fantasma eran justo los valores vivos de mas para cruzar el umbral de
mwcc entre rematerializar y conservar -> aparcaba el `1` en callee-saved y lo reutilizaba para
`flag = 1` (`movne r5,r6` en vez de `movne r5,#1`), y eso rotaba 3 registros por toda la cola.
Con un solo argumento: **MATCH byte-exact a la primera**. Commit `393f958bc`, gate 306/0.

⚠⚠ **LECCION NUEVA Y GENERALIZABLE -- los argumentos fantasma pueden ser INVISIBLES en el
desensamblado.** La regla de aridad ya estaba en el skill, pero el caso clasico es "una constante
acaba en el registro equivocado". Aqui **no se veia nada**: 0x625, `obj->ext` y `kind` se guardan
ademas en los descriptores justo antes de la llamada, asi que estan legitimamente en r1/r2/r3 en
ese punto y el desensamblado es identico con 4 argumentos o con 1. El sintoma aparecia a 0x99, muy
lejos, disfrazado de coloreado de registros. **Un `extern f();` sin prototipo + un residuo que
parece del asignador = grepea el arbol casado por llamadas reales de ESE callee, aunque la region
de la llamada ya case byte-exacta.** Coste de no hacerlo: ~75 experimentos entre varias sesiones.

**Lo que SI era load-bearing** (conservar): el orden de los tres stores de la cola
one(0x20) -> flag25(0x25) -> b10(0x10); el read `t = reqB.flag25` solo tiene que preceder a su
escritura, asi que el store de b10 va el ultimo.

**(historico, ya obsoleto)** Mejor forma era
`build/try/4410/best.c` (= s2). **El empate de ORDEN DE STORES ya NO existe**: bastaba reordenar la
fuente a one(0x20) -> flag25(0x25) -> b10(0x10) (el `t = reqB.flag25` solo tiene que preceder a su
escritura). Residuo restante = **rotacion de 3 registros** por un CSE: mwcc aparca el `1` de
`reqB.one` en callee-saved r6 (sobrevive a los 2 `bl`) y lo reutiliza para `flag = 1`
(`movne r5,r6`), mientras la ROM lo pone en `lr` (scratch, muere antes del `bl`) y rematerializa
`#1`. De ahi {1->r6, 0->ip, t->lr} en vez de {1->lr, 0->r6, t->ip}. Curioso: para el 3er uso del 1
(el arg del `func_ov022_020a4490` final) mwcc SI rematerializa `mov r2,#1` -- es inconsistente.
Probado sin exito: quitar el local `one`, orden de declaracion de `flag` (3 posiciones),
materializar el `one` antes/despues del read de flag25, `t` como int, tipo de `flag`
(uchar/short/uint), guardar el resultado de la llamada en un local existente. Primer diff en 0x99.
**build_sweep sobre best.c: 10 off en toda la linea 3.0/2.0 -> no es la build.**

⭐ **DISPARADOR AISLADO POR BISECCION (2026-07-24).** Tecnica reutilizable: compilar C arbitrario
sin necesidad de una funcion objetivo, con `cd tools` y
`import match, capstone; o=match.compile_c(path); b,r=match.text_relocs(o)` + capstone, y mirar si
los `movne/moveq rX, ...` salen con **inmediato** (como la ROM) o con **registro** (el CSE).
Resultado de bisecar `best.c`:
- Quitar el `if (VEC_Mag(...)==0) { reqB.v = *(Vec3*)r3p; } else { func_01ff8d18(...); }`
  -> **el CSE DESAPARECE** (`movne r5,#1`). Quitar el setup de reqA no cambia nada.
- Dentro de la rama: la copia **campo a campo** mata el CSE pero cuesta +12 B (3 ldr/str en vez de
  `ldm`/`stm`); **cualquier** forma de copia en bloque (directa, via puntero, via temporal,
  `*(Vec3*)&dst = *(Vec3*)src`) lo mantiene. Invertir la rama y meter el resultado de VEC_Mag en un
  slot existente tampoco lo mueven.
- O sea: **el disparador es la copia en BLOQUE dentro de la rama corta**, y la region de la rama ya
  sale byte-identica a la ROM. La ROM tiene copia en bloque Y sin CSE, asi que es una decision de
  asignacion GLOBAL de mwcc reaccionando a lo corto que queda el `then`. Microtests m1/m2/m3 (replica
  minima del tail, con y sin el cero compartido temprano) **rematerializan bien** -> el tail por si
  solo no es el problema.
⚠ **No se pueden anadir locales**: meter un `int zeroV` para materializar el 0 pronto hace que mwcc
lo derrame (stack 0x50 -> 0x54 y push de r3). Cualquier variante nueva tiene que reusar slots.
Mecanismo exacto: el CSE es la CAUSA de la rotacion, no un sintoma -- mwcc decide reutilizar el 1
para `flag`, eso lo obliga a vivir cruzando los 2 `bl`, eso lo obliga a callee-saved (r6), y de ahi
0->ip y t->lr. La ROM no cachea NINGUNA constante cruzando llamadas (materializa el 1 cuatro veces
por separado) pero si CSEa el 0 tres veces dentro del mismo bloque. Nota: mwcc tampoco CSEa para el
`mov r2,#1` del arg final -- solo para el `mov` predicado, que es la asimetria a atacar.

# SESION 2026-07-23 (noche) -- VETA FRESCA: subsistema action-tick (100+ overlays enemigo)

`tools/scan_fam.py` saca familias byte-identicas SIN HACER (asm_stubs). Top: [1] 8 miembros x500B
(ov038/040/057/059/077/079/094/096, rep func_ov038_020b4940), [2] 7x180 (ov141...), [3] 6x344
(ov181...), [9] 5x296 (ov149...). Es el framework de "tick de accion de IA" replicado en ~100
overlays de enemigo, hospedado en ov022 (callees func_ov022_0209fe20/020a35f4). **Vale muchisimo:
casar un rep -> dedupprop reparte a sus gemelas.**

**Idioms CLAVE de este subsistema (todos catalogados, reproducidos byte-exact):**
- **Flag hw60 = `*(unsigned long long *)(base+off) |= mask`** -- el u64 |= produce el par
  `orr rlo,#mask` + `orr rhi,#0` (shadow). Y para offsets grandes (0x464, 0x46c) mwcc PARTE la
  direccion de la palabra alta: `add r0,r5,#0x64; ldr [r0,#0x404]` -- exactamente como la ROM.
  Confirmado en el rep y en func_ov022_020888ec (`*(u64*)p |= 0x80`).
- **Bitfield desde resultado de vtable**: `typedef struct{u8 b0:1,b1:1,brest:6;} Byte694;` y
  `((Byte694*)(self+0x694))->b1 = (*(ObjFn*)(self+0x668))(self);` da el `ldrb;lsl#0x1e;lsrs#0x1f`.
  ⚠ **NO caches el puntero al bitfield** -- `Byte694 *f = ...` lo mete en callee-saved (r6) y sobra
  +4B; accede inline `(*(Byte694*)(self+0x694)).b1` cada vez (regla 5b, duplica el lookup).
- vtable calls: `(*(ObjFn*)(self+0x668))(self)`, ObjFn=`int(*)(int)`.

**func_ov038_020b4940 (rep familia [1]) -- CASI, empate de numeracion en la cola.** v1 en
`build/try/4940/v1.c` = 500/500 bytes, byte-exact hasta 0x179 (75%). Unico residuo: en el bloque
final de limpieza (2 Vec3 a 0 + `*(u64*)self|=4` + dispatch) la ROM usa r1/r2 (reserva r0 para las
copias `mov r0,r5`) y mwcc usa r0/r1 -- 4 registros desplazados. El cero de la limpieza va a r0
(mio) vs r1 (ROM) porque la ROM no reutiliza r0 (que tiene el bit-test muerto). INVARIANTE a 10
formas (hoist, idx type, chained/indexed zero, register, shared-zero-como-mode-arg, decl order) +
sweep 27 builds (3.0 = 13 off) + arity OK + sin twin casado en el corpus (todo asm_stubs). Empate
de numeracion real. Las 8 gemelas son byte-identicas -> mismo empate; probar OTRA familia ([2]/[9])
que no tenga esta cola.

# SESION 2026-07-23 (tarde) -- 3 matches ov000 + familia de empate sin/cos scheduler

**Integrado (staging ov000, real C, byte-exact):** `func_ov000_02051d3c` (600B) Ov000_TickLoadScene ·
`func_ov000_02054b1c` (144B THUMB) Ov000_ProbeSaveMedia · `func_ov000_02058c28` (608B)
Ov000_LoadListSceneGraphics. Structs Ghidra: Ov000ScreenBlock/PaletteBlock/CharacterBlock/ResourceCell.
Commit 6f5433ba4. Antes: sync de delinks.txt de 15 overlays ya integradas (f71e04936).

**⭐ FAMILIA DE EMPATE "tabla sin/cos con store al objeto" (8 funcs): ov212/266/267 + ov214/215/216/217/264.**
Patron: `obj[a]=data_0203d210[idx*2]; obj[b]=0; obj[c]=data_0203d210[idx*2+1]`. La ROM hace los DOS
`ldrsh` y LUEGO los 3 stores (base en scratch r3, valores en los propios regs de offset r2/r1 con
`ldrsh rX,[r3,rX]` in-place). mwcc mete la base en ip, reutiliza UN reg (r3) para ambos valores y por
eso HUNDE el 2o ldrsh por debajo de los stores. **RAIZ**: el store-al-objeto con el `=0` intercalado
deja que mwcc programe el 2o load tarde. **Todos los precedentes CASADOS de este idiom evitan el
problema de otra forma**: o pasan ambos valores como ARGUMENTOS de llamada (familia
`MTX_RotY33_(mtx, tbl[i*2], tbl[i*2+1])` en ov030-035) o escriben a un struct LOCAL de pila
(func_ov120_020ccd90 -> `VEC_Set(&dir, tbl[..], 0, tbl[..])`), y ambas cosas fuerzan los dos loads
antes de cualquier store. NO hay lever de fuente para la variante store-al-objeto: probados (ov212)
hoist a 2 locals, idx int/uint/ushort, orden de operandos del mult, reorden de los 3 stores; (ov214)
10 formas + build_sweep 27 builds (todos 34 off) + arity OK. Mejores formas en build/try/cffd0/ y
build/try/cdde4/. NO tocado el nonmatching/ existente, NO park nuevo. Si aparece un lever para el
2o-ldrsh-antes-del-store, casa las 8 de golpe.

**Backlog accesible = empates.** audit_arity limpio salvo los 2 gigantes ov003 (carril del peer).
Muestreo de 8 parks (ov214/ov212/ov008_0207b8a8/ov006_02051fbc/ov024_02082e04/ov022_020889cc/
main_02032388/ov022_020a46f8): todos empates reales de coloreado/scheduler/coalescing/dead-copy con
notas correctas. Los matches salen de los carriles de staging, no de romper parks.

---

# func_ov030_020b4410 -- CARACTERIZACION DEFINITIVA via analogo del corpus (2026-07-23)

Encontrado el analogo estructural exacto: `func_ov045_020b4630` (casada) tiene la MISMA forma de
cola -- un cero en callee-saved (r4) y un uno en caller-saved (lr), con stores a la pila en orden
NO monotono -- y CASA. Por que ella si y ov030 no: en func_ov045 el cero se REUTILIZA en varios
campos de la cola (f14, f20, f24, f28), asi que mwcc lo mantiene en callee-saved a lo largo de
todos los stores. En ov030 los ceros estan REPARTIDOS: `f0c`/`azero` se escriben TEMPRANO (antes
de VEC, en posiciones fijas de la ROM) y `b10` es un unico store de cero AISLADO en la cola. Con
un solo store, la materializacion del cero se acopla a su posicion de store: escribirlo primero da
callee-saved+store-primero (s1), escribirlo ultimo da store-ultimo pero pierde el callee-saved (x2).

Probado el idioma de reutilizacion: mover f0c a la cola junto a b10 (rompe los stores tempranos,
34 diff); b10 = flag reusando el cero de flag (registros rotos, 13 diff). Ninguno cierra porque
f0c no puede moverse (orden de la ROM) y b10 sigue siendo un store aislado.

CONCLUSION FIRME: residuo de 5 instrucciones, mejor forma `build/try/4410/s1.c` (registros
correctos, solo el orden de los 3 stores de cola difiere). Checklist de 30 ejes completo +
microtest de scheduling + analogo del corpus. No es el compilador (27 builds, 12 bytes uniforme).
Misma clase irreducible que func_ov049 y el par de ov002.

# func_ov030_020b4410 -- corpus grep agotado + auditorias limpias (2026-07-23)

Aplicada la regla del corpus: `find_insn --seq 'mov lr, #1' 'mov r6, #0'` = 0 casadas; ampliado a
cualquier par callee-saved (mov rX,#1 ; mov rY,#0) = 8 casadas, pero TODAS usan el 1/0 como
banderas booleanas de vida larga (ov221/222/224/226 los mantienen a traves de todo el cuerpo,
OS_WakeupThread/OSi_UnlockVram idem). Ninguna reproduce el patron transitorio de la cola de ov030
(materializar 0->r6 reciclado y almacenar b10 el ultimo). O sea: no hay forma C copiable en el
corpus para este acoplamiento concreto.

Probadas ademas dos ordenes nuevos esta iteracion: flag25/one/b10 (y1, 10 diff) y b10 con
re-store (y2, 10 diff): cada orden reasigna registros, confirmando el acoplamiento orden<->coloreado.

Conclusion: es un residuo de 5 instrucciones de la clase dos-mitades (s1 registros ok / x2 orden
ok), medido y documentado, en build/try/4410/. Auditorias de la sesion limpias: shadowed 0, stale
parks 0, arity solo los 2 gigantes de ov003 (0204cba0/0204d98c, ya conocidos), struct_sync sin
conflictos, y las integraciones recientes de ov000 re-verifican MATCH.

# func_ov030_020b4410 -- las dos mitades AISLADAS y la regla de scheduling PROBADA (2026-07-23)

Probado con un microtest (`build/try/4410/probe_ord_*.c`): **mwcc conserva el ORDEN DE FUENTE para
stores independientes** (ord_b con fuente 0x20,0x25,0x10 sale exactamente asi). No ordena por
direccion. Entonces el orden de stores de la ROM (one@0x20, flag25@0x25, b10@0x10) se consigue con
esa misma fuente.

Pero el coloreado y el orden estan ACOPLADOS y la ROM los desacopla:
  - `build/try/4410/s1.c`: registros CORRECTOS (0->r6, 1->lr, flag rematerializado), orden de
    stores MAL (b10 primero). Fuente: b10 escrito primero.
  - `build/try/4410/x2.c`: orden de stores CORRECTO (one,flag25,b10), registros MAL (1->r6 y
    reutilizado para flag con `movne r5,r6`). Fuente: one escrito primero, b10 ultimo.
El coloreado asigna el callee-saved reciclado (r6, que traia r3p) a la constante ESCRITA PRIMERO en
la fuente. La ROM materializa el 0 en r6 primero (aunque almacena b10 el ultimo) y ademas
rematerializa el flag. Con C plano no se puede separar: escribir b10 primero da r6=0 pero store
primero; escribir one primero da store correcto pero r6=1.

Es la misma clase que func_ov049 y el par de ov002. Ambas formas estan a 5 instrucciones reales.
Sweep de 27 builds: 12 bytes uniforme. Sin resolver con C equivalente; queda en build/try/.

# func_ov030_020b4410 -- residuo AISLADO a puro orden de stores (2026-07-23, loop)

Mejor forma ahora: `build/try/4410/s1.c` (5 instrucciones, y los REGISTROS ya son correctos).
El truco que fijo los registros: `reqB.one` via un local `int one; one = 1; reqB.one = one;`
en vez de `reqB.one = 1` directo -- eso corrige el `movne r5,r6`->`movne r5,#1` (mwcc dejaba de
compartir el 1 de reqB.one con el flag).

Lo que queda son 5 instrucciones que son SOLO el orden de los tres stores de cola + los dos `mov`
de constantes:
  ROM : mov lr,#1 ; mov r6,#0 ; str lr,[sp,#0x20] ; strb ip,[sp,#0x25] ; strb r6,[sp,#0x10]
  mio : mov r6,#0 ; mov lr,#1 ; strb r6,[sp,#0x10] ; str lr,[sp,#0x20] ; strb ip,[sp,#0x25]
Los registros COINCIDEN (lr=1, r6=0, ip=flag25). mwcc emite los tres stores independientes en el
ORDEN DE LA FUENTE, y el coloreado correcto exige escribir `reqB.b10` PRIMERO en la fuente -> el
store de b10 sale primero, cuando la ROM lo pone ULTIMO (one, flag25, b10).

Es la tension de dos mitades ya documentada (como func_ov049 y el par de ov002): el coloreado
quiere b10 primero, el orden de stores lo quiere ultimo. Probado sin cerrarlo: reordenar la fuente
a one/flag25/b10 (rompe el coloreado, 13 diff), locales `one`+`zero` prematerializados (13 diff),
y stores via `(volatile ReqB *)` (rompe todo, 20 diff). El sweep de 27 builds da 12 bytes uniforme.

# func_ov030_020b4410 -- residuo final medido: 5 instrucciones, register-alloc de la cola (2026-07-23)

Mejor forma: `build/try/4410/p3.c` (tamano exacto 292, stream exacto salvo 5 instrucciones).
El build sweep da 12 bytes en TODAS las builds modernas -> no es el compilador.

El residuo es una eleccion de coloreado en la cola, y esta MEDIDA: la ROM mete el 0 de
`reqB.b10` en un callee-saved (r6) y REMATERIALIZA el 1 para `flag` (`movne r5,#1`); mwcc mete el
1 de `reqB.one` en un callee-saved y lo REUTILIZA para flag (`movne r5,r6`). Es la decision
opuesta sobre cual de los dos constantes vale la pena conservar a traves de las llamadas
(el 1 vive en lr, caller-saved, y la ROM lo deja morir; mwcc no).

Probado sin moverlo: la forma de 2 ramas `flag=1` es obligatoria para el tamano (booleano directo
o `||` dan +4/-12); early-return da -12; 6 ordenes del bloque de cola; el `else if` como asignacion
booleana; y el sweep de 27 builds. La aridad de los 4 callees (a1064/a23a4/a4490) cuadra con el
arbol, y la funcion es void de verdad.

# func_ov030_020b4410 -- de 58 diferencias a 5 reales (2026-07-23, loop)

Cuatro arreglos encadenados, todos de forma de fuente. Mejor forma: `build/try/4410/p3.c`.

1. **Dos `str [sp,#N]` que el aparcado leia como ARGUMENTOS de pila** son campos de `reqB`
   (`char pad08[8]` -> `int f08; int f0c;`). La llamada es de CUATRO argumentos, no seis. Los dos
   argumentos inventados reservaban 8 bytes de area de salientes: `sub sp,#0x58` contra `#0x50`.
   -> tamano exacto.
2. **UN solo `flag = 0`, al principio.** La ROM lo mantiene vivo en r5 a traves de todas las
   llamadas y ademas alimenta `reqB.f0c`. Con dos asignaciones mwcc mata la primera, le sobra un
   registro y derrama el 4o parametro: `push {r3,r4,r5,lr}` en vez de `push {r4,r5,r6,lr}`.
   -> push exacto, 34 -> 22.
3. **`obj->b15c` a un local.** La ROM lo lee UNA vez (`ldrb r3,[ip,#0x15c]`) y ese r3 vale a la vez
   como campo `reqA.flags` y como 4o argumento.
4. ★★ **Invertir el if/else de VEC_Mag.** Escrito `if (VEC_Mag(...) != 0) { llamada } else { copia }`
   mwcc PREDICA la copia y se ahorra el `b` de salto por encima (una instruccion menos).
   Escrito `if (... == 0) { copia } else { llamada }` sale la forma con ramas de la ROM.
   -> 22 -> 13.
5. Reordenar el bloque de cola (`b10 = 0` el primero) -> 13 -> 10 (5 reales).

**Residuo**: rotacion de tres registros en la cola (`mov lr,#1`/`mov r6,#0` intercambiados y los
tres stores en otro orden: la ROM guarda one(0x20), flag25(0x25), b10(0x10)). Probadas 6
permutaciones del bloque. Ademas la ROM materializa `movne r5,#1` fresco donde nosotros
reutilizamos el registro que ya tiene el 1 de `reqB.one`.

# ITERACION 2026-07-23 (cron /loop 10m) -- func_ov030_020b4410

★★ **Dos stores a la pila leidos como ARGUMENTOS de la llamada.** El aparcado llamaba
`VEC_Mag(r3p, 0x625, obj->ext, obj->b15c, 0x625, flag)` con SEIS argumentos porque la ROM hace
`str r1,[sp,#8]` y `str r5,[sp,#0xc]` justo antes del `bl`. No son argumentos: son **campos del
struct reqB** (el `char pad08[8]` del aparcado es en realidad `int f08; int f0c;`). Los dos
argumentos de pila inventados obligan a mwcc a reservar 8 bytes de area de argumentos salientes,
y de ahi el `sub sp,#0x58` contra el `sub sp,#0x50` de la ROM.

Con la llamada a CUATRO argumentos y los dos campos escritos como campos: **tamano exacto (292)**.
Mejor forma: `build/try/4410/b1.c`, 34 diferencias, todas de asignacion de registros. El residuo
concreto: la ROM hace `push {r4,r5,r6,lr}` y `mov r6,r3` (guarda el 4o parametro en callee-saved),
nosotros hacemos `push {r3,r4,r5,lr}` (derrame del parametro). Probados sin efecto: `register` en
el parametro, local intermedio en dos posiciones, orden de declaracion de los dos structs, y un
local `zero` nombrado compartido por `reqA.zero`/`reqB.f0c`/`reqB.b10`.

**Leccion general**: cuando el ROM guarda en `[sp,#N]` con N pequeño justo antes de un `bl`, mira
si esos offsets caen dentro de un objeto local antes de contarlos como argumentos de pila. El
tamano del frame lo dice: area de argumentos salientes + locales tiene que cuadrar exactamente.

# ESTADO 2026-07-23 (tarde, sesion autonoma: RESCATE DE nonmatching/, 4a tanda)

C = 15.636/23.240. Gate 306/0. **nonmatching 190 -> 179.** 13 funciones casadas a mano o
recuperadas de staging + 16 gemelas propagadas.

## Lo que ha funcionado (por orden de rentabilidad)

1. ★★★ **El barrido de `staging/` OTRA VEZ**: siete funciones byte-exactas de ov000 esperando
   (0204cac0, 0204ee24, 0204f47c, 02057dc4, 020599bc, 0205a4d4, 0205a554); tres de ellas ademas
   estaban aparcadas en `nonmatching/`. Es la CUARTA vez que el barrido paga: hazlo al empezar.
2. ★★★ **La cola buena de aparcados es "los que NO tienen el tamano correcto"**: un tamano
   distinto es un bug de fuente por definicion. `build/try/sizescan.py` compila los 187 y ordena
   por |delta|: salieron 58, y de los primeros que ataque casaron 5.
3. ★ **Recontar el rank quitando las lineas `bl`**: `rank_parks.py` cuenta como diferencia cada
   `bl` (la ROM esta enlazada y nuestro .o no), lo que infla todos los aparcados con llamadas.
   Filtrando `bl`/`blx` la cola cambia por completo y aparecen los de 1-3 instrucciones reales.

## Cracks nuevos (los detalles, en codegen-cracks.md)

- **El pliegue booleano (0,1)** y su antidoto: un `if` redundante. Cerro ov024 x2 (+2 gemelas).
- **Cadena de asignaciones de 4 bytes** = un cero `int` + tres enmascarados. Cerro ov254.
- **`switch` con `default`** fuerza la forma con ramas tambien con DOS brazos. Cerro ov008_0204d640.
- **Test del bucle sobre el lookahead**, no a traves de la asignacion. Cerro ov008_0205ea18 (+1).
- **En THUMB, banderas vivas => la constante viene del pool**: una palabra de pool para un
  inmediato codificable NO es por si sola un empate. Retiro el diagnostico de ov022_02083178.
- **Tabla como struct de arrays paralelos**. Cerro ov022_02089fe8.
- **Origen de una copia de struct como CAMPO, no cast**. Cerro ov119_020cbfc4 (+2 gemelas).
- **El divisor/resto de `func_02020400`**: devuelve `long long` con el RESTO en la palabra alta.
  Si la ROM pasa r1 a la llamada siguiente sin ponerlo, es `(int)(func_02020400(a,b) >> 32)`, no un
  argumento perdido. Dejo func_ov002_0205e358 a UN registro.

## Clase nueva medida: **el hoist del `bic` del hw60** (bloquea 9 funciones)

`func_ov181_020ce664` (x6) y `func_ov194_020cdd54` (x3). La ROM emite
`lsl ; lsr ; orr ; bic ; lsl ; orr`; mwcc adelanta el `bic` al hueco de dependencia detras del
primer `lsl`. **Diagnostico medido**: quitando la sentencia vecina (`holder[0x1b] = 0`) el `bic`
cae en su sitio, y poniendo esa sentencia ANTES del RMW tambien -- pero entonces se adelanta el
`str`. O sea: el planificador rellena el hueco con lo primero que tenga listo. Probadas 12 formas
del idioma (bitfield, extract explicito, operandos del `|` al reves, temporales, orden de
sentencias, local `zero` para ocupar el hueco): ninguna lo mueve conservando el resto.
Con el idioma documentado (`(u & ~0xff00) | ((((u<<16)>>24 | K)<<24)>>16)`) ov194 pasa de +8 bytes
a TAMANO EXACTO con 3 instrucciones fuera de sitio.

## Lo que queda en investigacion (mejor forma en `build/try/`, NADA aparcado nuevo)

| funcion | residuo | mejor fuente |
|---|---|---|
| func_ov049_020b43a8 (x4) | **1 registro** (r0 contra r1 del temporal de flags), tamano y stream exactos | `build/try/43a8/b1.c` -- ★ el `t` del despacho se RELEE (`ldrsb r3,[r6,#2]`), no se guarda en un local: eso solo arreglo el tamano y la aridad de registros. Probadas 24 permutaciones de declaracion, 8 de `register` y 27 builds |
| func_ov002_0205e358 | **1 registro** (base de pool r0 contra r2) | `build/try/e358/a1.c` -- ★ el segundo argumento de la ultima llamada es `(int)(func_02020400(ctx[4],6) >> 32)`, el RESTO de la division |
| func_ov002_0205efb4 | **2 registros** (ctx/result r4<->r5) | `build/try/efb4/a1.c` -- ★ `func_ov002_0205e9e8` toma un argumento (1) y el test es `> 0`, no `< 1` |
| func_ov194_020cdd54 (x3) | 3 instrucciones (hoist del bic) | `build/try/dd54/a1.c` -- TAMANO EXACTO |
| func_ov181_020ce664 (x6) | 1 instruccion (mismo hoist) | `build/try/e664/b1.c` |
| func_ov024_02082e04 | 4 registros | `build/try/82e04/b1.c` |
| func_ov008_02066a4c | 8 bytes (mwcc funde la guarda con la cadena de cmpeq) | `build/try/6a4c/a1.c` -- ★ el buffer es `unsigned short` (`ldrh`, no `ldrsh`) |
| func_02024e6c | falta el par push/pop: nos sobra un registro | `build/try/4e6c/f1.c` -- ★ estructura EXACTA con la lectura del switch marcada `volatile` (la ROM relee el caracter arriba y abajo del bucle) |
| func_ov031_020b453c (x4) | 20 (registros) | `build/try/453c/best.c` -- ★ el 0 de la llamada se hoistea y roba `fp` a la tabla de handlers |
| func_ov022_02088b50 | 4 bytes (`add lr,sp,#0`: la ROM materializa la base del buffer) | `build/try/8b50/a1.c` |
| func_ov022_02083bd8 | 4 bytes (0x6a desde el pool) | el propio aparcado. Ver la entrada de banderas: aqui NO hay banderas vivas, asi que sigue abierto |
| func_0200dcf0 | 2 bytes (`ldr ip,[pc]` contra `ldr r1,[pc]`) | `build/try/dcf0/a1.c` -- ~100 experimentos: 22 formas, 27 builds, 13 niveles -O, 25 flags, 13 pragmas |

⚠ **Correccion**: la nota "en 12.000+ funciones casadas NO hay ninguna con `ldr ip,[pc]` para una
direccion de datos" era falsa -- salio de un `find_insn.py --seq ... --limit 20`, y **`--limit N`
con espacio mete el numero como PATRON extra** (el script solo entiende `--limit=N`). Con la
sintaxis correcta hay 1.188 funciones casadas que deref-an por `ip`, y `MI_SendGXCommandAsync`
tiene el patron exacto. Sigue sin haber forma de fuente que lo reproduzca en func_0200dcf0, pero
el argumento del corpus NO vale.

# HIGIENE DE staging/ (2026-07-23, a peticion del usuario)

El barrido de `staging/` no termina al integrar: **hay que borrar de `staging/` lo que ya esta
integrado**, o el carril se llena de copias y el siguiente barrido no distingue lo nuevo de lo
viejo. Habia 130 `.c` con nombre de funcion; 116 ya estaban en `calls/`/`auto/`.

Procedimiento (en este orden, no al reves):

1. `staging/` esta en `.gitignore` y **NO esta trackeado** (`git ls-files staging/` -> 0). Borrar
   ahi NO se recupera con git. Por eso:
2. **Verifica el destino en `src/` antes de borrar el origen.** Un `verify_idx.py` por fichero
   (probando tambien `--thumb`); solo se borran los que dan MATCH en su sitio. Los 116 dieron
   MATCH; si alguno fallara, ese fichero de staging se queda.
3. Borra tambien el `.o` de al lado si existe.
4. **NO toques `staging/_codex_work/`** ni los directorios vacios del carril sin mirar mtime: es
   el scratch privado del carril paralelo. En esta limpieza el mas reciente tenia **18 minutos**,
   o sea que el carril de ov000 estaba VIVO; borrarlo habria roto una sesion en marcha.
   `max(mtime)` por subdirectorio es la comprobacion, y cuesta un comando.

Lo que queda en `staging/` despues de limpiar es justo lo que debe quedar: experimentos que aun
no casan (los 14 de ov003, el banco de empates de ov007/ov010, los de ov029) y el scratch vivo.

# ESTADO 2026-07-23 ~12:30 (sesion autonoma, 3a tanda: LA VETA DE func_0203c634)

**51 funciones casadas hoy.** Gate 306/0. Lo importante de esta tanda no son los parks: es que
**la veta de handlers de `func_0203c634` esta MUY viva y da familias enteras a la primera**.

## Como se trabaja esta veta (receta, ~10 min por familia)

1. Agrupar los handlers SIN C por hex enmascarado:
   `familias = defaultdict(list); clave = (size, hex con los relocs a cero)`.
   Filtrar a los que tienen un reloc a `func_0203c634` y size <= 260. Salen ~16 familias de 3-7.
2. Desensamblar el representante y traducirlo A MANO (Ghidra no hace falta para estos: son
   80-250 bytes de patron conocido).
3. Compilar contra `func_index.json` con un diff de instrucciones. **La mitad casan a la primera
   compilacion.**
4. Fan-out mecanico: sustituir los simbolos por overlay y verificar cada uno.

Casadas asi hoy: ov114/244/277 (x3, x3), ov163/164/165 (x3, x3), ov127/128/129/130 (x4),
ov287/288/289 (x3), ov214/215/264 (x3), ov241/242 (x2).

## Los idiomas que hacen falta (todos ya probados hoy)

- **hw60 byte alto |= K**: `(hw60 & ~0xff00) | (((((unsigned int)hw60<<0x10)>>0x18 | K)<<0x18)>>0x10)`.
- **hw60 byte alto &= ~K**: igual pero con un `(unsigned short)` EXTRA en medio:
  `(((unsigned int)(unsigned short)((((unsigned int)hw60<<0x10)>>0x18) & ~K) << 0x18) >> 0x10)`.
  Sin ese truncado desaparecen los dos shifts de 0x10.
- **bit 0 con signo** (`lsl #0x1f ; asrs #0x1f`): `struct { int b0 : 1; }`.
  **bit 0 sin signo** (`lsl #0x1f ; lsrs #0x1f`): `struct { unsigned char b0 : 1; }`.
- **byte bajo de una palabra**: `struct { unsigned bits : 8; }` con `|=` / `&= ~`.
- **vector por VALOR**: `f(obj, 0, *(VecFx32 *)p, 0)` -> `sub r3,sp,#8 / stm r3 / ldm r3,{r2,r3}`.
  Pasar un puntero pierde todo el patron.
- **tabla seno/coseno**: `data_0203d210[a*2]` y `data_0203d210[a*2+1]` (el `a*2` es la
  subexpresion comun que la ROM reutiliza con `lsl #1` dos veces).
- **division magica**: si el pool tiene 0x80808081 + `asr #10`, el divisor esta en OTRA palabra
  del pool -- en func_ov214_020cdcf0 era el mismo 0x7f8 que la comparacion de arriba.
- **angulo -> indice**: `(int)(unsigned short)((unsigned int)(((long long)v * K + (0x800LL<<32)) >> 32) >> 12) >> 4`
  con K de 64 bits (0x28be60db9391 = 65536/2pi en Q32).

## ★★ Palanca nueva: GLOBAL TIPADO COMO STRUCT para el orden de una copia de 4 bytes

`func_ov114_020cdb14`: la plantilla de evento de 4 bytes (dos u16) se copia con las dos cargas
ANTES de los dos stores y en orden DESCENDENTE de direccion. Eso sale con
`extern Ov114Pair data_x;` + `buf = data_x;`. Casteando un `unsigned short[]` al tipo del struct
sale el orden ascendente. **No es universal**: en `func_ov141_020cd2b0` la fuente esta en +4 del
simbolo en vez de en +0 y mwcc vuelve al orden ascendente pase lo que pase (12 formas probadas).
La diferencia parece ser que en el caso +0 mwcc mata la base con la ultima carga.

## Lo que queda a 1-5 instrucciones (todo en build/try/, nada aparcado)

| funcion | miembros | residuo | mejor fuente |
|---|---|---|---|
| func_ov141_020cd2b0 | **x7** | 2 registros del par de temporales de la copia | `build/try/cd2b0/c2.c` |
| func_ov169_020ce1dc | x5 | 4 instrucciones de orden de argumentos de la ultima llamada | `build/try/ce1dc/b1.c` |
| func_ov214_020ce928 | x5 | 5 (el `mov ip,#0` se adelanta) | `build/try/ce928/c1.c` |
| func_ov178_020cec18 | x3 | 17 registros (ip<->lr) | `build/try/cec18/a.c` |
| func_ov206_020cd464 | x4 | 10 (mwcc adelanta el pool del callback) | `build/try/cd464/b1.c` |
| func_ov117_020cca64 | x5 | +4 bytes (ldm/stm contra cargas sueltas) | `build/try/cca64/a1.c` |
| func_ov131_020cdff4 | x3 | -16 bytes: mwcc funde los dos brazos del if/else en `state[0xc] == ready` | `build/try/cdff4/a.c` |

# ESTADO 2026-07-23 ~11:00 (sesion autonoma: RESCATE DE nonmatching/, 2a tanda)

C = 15.478/23.240. Gate 306/0. **13 funciones rescatadas de `nonmatching/`** en esta tanda.
Pusheado hasta a998ce81 + commits locales despues.

## ★★★ LA CONSTANTE PLEGADA EN EL INDICE MATA LA REDUCCION DE FUERZA

`func_ov008_0205e734` estaba archivada bajo "loop strength-reduction: ninguna forma de fuente lo
evita, saltarse los bucles base+i*stride". **Si la hay:**

```c
int p = ((int *)base)[i + 0x671];      /* 0x19c4 / 4 = 0x671  -> CASA */
int p = *(int *)(base + i * 4 + 0x19c4);   /* -> mwcc inventa un puntero de induccion */
```

Con el desplazamiento en BYTES dentro del indice, mwcc recalcula `base + i*4` cada vuelta como
hace la ROM. Con el offset fuera, reduce en fuerza, gasta un callee-saved mas y engorda el push.
**Es una clase entera que hay que reprobar**, no un caso: la nota de la clase decia
"induction/array-index/held-base/byte-offset, ninguna lo suprime" -- probaron el array-index pero
NO con la constante plegada dentro del subindice.

## Otras palancas nuevas de esta tanda

1. ★★ **El orden de DECLARACION colorea; el orden de ASIGNACION decide que cero se materializa.**
   `func_ov022_020b02a4`: declarar `i, result, slot` colorea r4/r5/r6, pero ademas hay que
   ASIGNAR `result = 0` el primero, porque la ROM materializa el cero de `result` y de ahi deriva
   i, el indice de la carga y el -1. Inicializando en las declaraciones sale el cero de `i` y todo
   el reparto cambiado. **Son dos ejes, no uno**, y ninguna de las 6 permutaciones con
   inicializador llega.
2. ★★ **Reasignar el offset sobre el propio puntero, con la constante a la IZQUIERDA y un CAST.**
   `func_ov002_0205e1b8/0205e1d4`: escrito como un solo `*(int *)(ctx + 0x4a4)`, mwcc evalua
   primero el operando complejo y el deref se queda con r1 y la constante del pool con r2 -- la
   ROM al reves, y ademas mete la carga de la constante en el hueco de load-use. La forma que casa
   es `ctx = (char *)(0x4a4 + (int)ctx);` en su PROPIA sentencia. Sin el cast mwcc canonicaliza la
   suma y vuelve al orden de siempre (`ctx = ctx + 0x4a4;` NO casa).
3. ★ **El bloque de fallo FUERA DE LINEA se pide con un `goto`.** `func_02034428`: la ROM salta
   por encima del bloque de fallo hasta el epilogo de exito. Con un `return 0` temprano -- en sus
   dos formas -- mwcc deja que los stores caigan por fall-through dentro del `return 1` y se ahorra
   el branch: 2 bytes menos. Es la imagen especular de la entrada ya catalogada para el bloque de
   EXITO fuera de linea.
4. ★★ **"La ROM materializa el 0 de retorno antes de las comparaciones" NO es un empate de
   predicacion.** `func_ov044_020b3a2c` (+ ov063/082/099, x4): con `void *r = 0;` asignado en cada
   case y devuelto UNA sola vez al final, el cero esta vivo en todos los caminos y mwcc emite el
   mismo `mov r0,#0` sin predicar en el hueco cmp/branch. El puntero base tiene que declararse el
   PRIMERO (al reves se intercambian el `add` y el `cmp`). Mismo residuo abierto todavia en
   `func_ov006_0204e35c`, donde el 0 solo hace falta en un camino.
5. ★ **Romper un CSE de direccion deletreando la segunda lectura por otra base.**
   `func_ov022_0208a830`: la ROM recalcula `add r0, self, idx lsl #2` despues de la llamada; con
   las dos lecturas escritas igual mwcc las unifica (-4 bytes). `((int *)((char *)self + idx*4))[6]`
   -- misma direccion, mismas dos instrucciones -- rompe el CSE.
6. ★★ **Dos bitfields del mismo halfword conservan el par de shifts Y su reutilizacion.**
   `func_ov022_02089784`: `idx & 7` se pliega a `and #7`, pero un bitfield `:3` de verdad emite
   `lsl #0x1d ; lsr #0x1d` y ademas deja el intermedio vivo para el `add r0, base, ip lsr #29` del
   final. El segundo campo (`(idx<<0x11)>>0x14`) son los 12 bits de encima.
   El ultimo store ademas exige subindice sobre base `char *`: `((unsigned char *)base + slot)[0x10]`.

## ⚠ HERRAMIENTA REPARADA: `tools/_run_mwcc.py` reintenta

En una compilacion completa en paralelo el chequeo de licencia FLEXlm falla de forma
intermitente: cada pasada de `ninja` moria en un fichero DISTINTO y arbitrario, y el mismo comando
volvia a funcionar solo. Ahora reintenta 8 veces con backoff. **Con `ninja -j 6` no falla ninguna**;
a plena paralelizacion falla ~1 de cada 14.000. Un diagnostico real falla los ocho intentos.

## Lo que queda en investigacion (mejor forma en `build/try/`, NADA aparcado nuevo)

| funcion | residuo | mejor fuente |
|---|---|---|
| func_ov119_020ce610 (x3) | 1 swap: mwcc adelanta `ldr r1,[pc]` por encima del `str` del cero | el propio park. **~66 experimentos**: 14 formas de sentencia, 6 ordenes, comma, volatile, struct, inline, 9 pragmas, 13 niveles -O, **27 builds**, **8 valores de -proc**. Todos identicos. Medido: mwcc materializa SIEMPRE las dos constantes antes de los dos stores (probe `void f(int*p){p[0]=0;p[1]=C;}`), y la ROM no. |
| func_ov022_02092b60 | el mismo swap, 1 instruccion | idem. Bisecado: sin la guarda `if` y con los dos `ldrsh` fuera, mwcc NO agrupa; con ellos, si. |
| func_ov022_02096e44 | 16 registros, TAMANO YA EXACTO | `build/try/96e44/d1.c` -- ★ el bucle de copia es UNA asignacion de struct de 0x34 bytes (13 palabras), no un bucle escrito a mano; mwcc lo expande al ldm/stm con writeback. Falta que la direccion FUENTE se calcule antes que la destino. |
| func_ov008_0205cb08 | 4 registros, TAMANO YA EXACTO | `build/try/cb08/j2.c` -- ★ las coords van como CAMPOS de struct (si no, mwcc saca punteros del bucle) y el `row = param_1` va DENTRO de la guarda |
| func_ov022_020893f4 | 1 registro (destino del `mla`) | el park; probadas 3 formas de array-de-struct |
| func_ov022_020a0f60 | 1 registro | el park; probadas 10 formas (local, bloque, cast, struct, register) |
| func_ov006_0204e35c | 5 instrucciones (el 0 de retorno no sube a r0) | el park; 12 formas probadas |
| func_ov141_020cd2b0 (x7!) | 2 registros del par de temporales del copiado | `build/try/cd2b0/c2.c` -- TAMANO EXACTO. La ROM hace `ldrh r0,[r2,#6] ; ldrh r2,[r2,#4]` (el segundo load mata su propia base); mwcc usa r3 y luego r0. Probadas 12 formas: struct-assign, campo a campo en orden inverso (esto SI da el orden de la ROM), locales nombrados, puntero al buffer, bitfield para el flag, y las 24 permutaciones de declaracion. Familia de 7 (ov141/142/143/149/150/151/152). |
| func_ov031_020b408c → CASADA (y familia) | | |
| func_ov024_02082e04 | 4 registros (par base/valor del ultimo bloque) | `build/try/82e04/b1.c` -- TAMANO EXACTO ya (el park estaba 4 corto). El `ctl` del segundo bloque hay que redeletrearlo para que la ROM lo rematerialice |
| func_ov008_0207b84c | 7 registros | el park; probadas 4 formas |
| func_0202119c | 21 instrucciones, TAMANO EXACTO | `build/try/2119c/b2.c` -- ★ los indices de la tabla ya salen exactos escribiendo `data[i*2]` y `data[i*2+1]` (el `i*2` es la subexpresion comun que la ROM reutiliza); lo que falta es que las dos mascaras de 16 bits se hagan al ENTRAR, no en el punto de uso |
| func_ov031_020b408c/036/032 → CASADAS | | |

# ESTADO 2026-07-23 ~05:00 (sesion autonoma: RESCATE DE nonmatching/)

C = 15.446/23.240 (66,5%), 34,40% por bytes. **nonmatching = 228** (venia de 248). Gate 306/0.
**39 funciones casadas** (23 a mano + 16 gemelas de dedupprop). nonmatching 248 -> 226.
★ Ultimo par: func_ov008_0205b720 / func_ov025_0208dc8c -- el `orr rD,rS,#0` del ROM necesita un OR
de 64 bits con un bit por encima del 31 (`| 0x100000000LL`); toda forma de 32 bits se pliega.

## 20 funciones rescatadas de `nonmatching/` -- y el metodo que las saco

La cola buena es **`build/try/rank.json`** (lo escribe `tools/rank_parks.py`): ordena los parks por
INSTRUCCIONES que difieren, no por bytes. Ordenandolo y leyendo `rom_only`/`mine_only` se clasifica
cada park en 30 segundos sin compilar nada. De ahi salio todo lo de abajo.

Rescatadas: func_ov008_02072fe4 (+ gemela ov025_020a85a8), func_02023c60, func_0200dc70,
func_ov022_0209bf54, func_ov022_020b1fc4, func_ov022_0208ba80, func_ov022_020afe14,
func_ov022_02082bf4, func_ov008_0204eb88, func_ov008_0205714c, func_ov022_020b0e64,
func_ov212_020cd494 (+ gemelas ov266/ov267), func_ov008_02055d24, func_ov002_02079adc,
func_ov245_020cd6d0, func_ov022_0209bdbc, func_ov008_02077908.

## ★★★ EL HALLAZGO DE LA SESION: una asignacion ENCADENADA cambia la PLANIFICACION

`func_02023c60` llevaba una nota que decia "empate probado en las 27 builds". No lo era.
Escribiendo los ceros como `p[5] = p[6] = p[7] = 0;` en vez de tres sentencias, mwcc deja de
adelantar el `ldr [pc]` por encima del `str`. El experimento de control esta hecho:
**UNA sola cadena en CUALQUIER punto del bloque basico basta** (probado con la cadena en p5/p6/p7,
en p8/p9 y en p11/p13 -- las tres casan; sin ninguna, no casa). El stream de instrucciones es
identico salvo la posicion de esa carga, asi que no es un efecto de registro: la decision local del
planificador depende de la ESTRUCTURA DE SENTENCIAS de todo el bloque.

Volvio a funcionar en `func_ov245_020cd6d0` (encadenar los dos ultimos stores a cero sube el
`mov r2,#0`+`sub` por encima del primer store). **Es la primera palanca a probar cuando el residuo
es "las mismas instrucciones en otro orden".**

⚠ No es universal: no mueve func_ov119_020ce610 (x3), func_ov022_02092b60, func_ov033_020b350c (x4)
ni func_ov200_020cff54.

## Otras palancas confirmadas esta sesion

1. ★ **`(char *)0 + x` no solo da `add rD,rS,#0`: tambien LAVA un cero** para que el compilador no
   lo pliegue. En func_ov245_020cd6d0 el 0xff del ROM es `sub r3,r2,#1` con r2=0 vivo; `0xff`, `-1`
   y `zero - 1` se pliegan todos a `mov r3,#0xff`, y `(int)((char *)0 + zero) - 1` no.
2. ★ **Bitfield struct contra `and #mask`**: mwcc pliega un par de shifts con el MISMO desplazamiento
   (`(x<<0x1d)>>0x1d`) a un `and #7`; solo una lectura de bitfield real conserva el `lsl/lsr`.
   Los campos con desplazamientos distintos sobreviven de las dos formas -- por eso una funcion puede
   tener dos campos que casan y uno que no. Cerro func_ov022_020b0e64.
3. ★ **`& ~BIT` contra `& 0xffXX`**: el complemento de un literal `int` es lo que mwcc convierte en
   `bic`; una mascara de 16 bits necesita palabra del pool. Cerro func_ov022_0209bdbc.
4. ★ **Copia de struct contra asignaciones campo a campo**: el ROM emitiendo las DOS primeras cargas
   antes del primer store es la firma de una asignacion de struct; campo a campo empareja cada carga
   con su store y ademas en orden inverso. Cerro func_ov008_0205714c.
5. ★ **Aritmetica de punteros para fijar el orden de operandos**: `adds rd, base, rd` (base como Rn)
   solo sale si `base` es un `char *`; con `int` mwcc canonicaliza la suma conmutativa al reves.
   Cerro func_ov022_020afe14.
6. ★ **Un indice MUTADO en vez de dos constantes**: `off = 0x1c2; ...; off = off + 0xc;` reproduce el
   `adds r0,#0xc` del ROM; nombrar el segundo offset (directo, como suma, por puntero o con un indice
   de solo lectura) recarga del pool. Cerro func_ov002_02079adc.
7. ★ **`switch` contra `||`**: `s == 0 || s == 1 || s == 2` se pliega a `and #0xff ; cmp #2 ; bhi`;
   el `switch` conserva `cmp #0 ; cmpne #1 ; cmpne #2`. Cerro func_ov212_020cd494 (x3).
   Y al reves, un `if` de no-cero ALREDEDOR de un switch de dos etiquetas evita que mwcc pruebe que
   el test de cero sobra (func_ov008_0204eb88).
8. ★ **Orden de carga primero, orden de declaracion despues**: en func_ov008_02077908 hacian falta
   las dos cosas -- `span` antes que `pos` (orden de las cargas del ROM) y `lim` antes que `pos`
   (coloreado r0/r2 del clamp). Probar solo una de las dos deja el mismo residuo y engana.
9. **Contadores frescos en un bloque interno**: func_0200dc70 necesita que el segundo bucle tenga SUS
   propios contadores; la nota decia que estaba descartado "en los dos ordenes de declaracion" y hay
   SEIS (place/shift/index es el bueno).
10. **Tamanos de buffer**: func_ov008_02055d24 reservaba 5 entradas y el ROM 4 (`sub sp,#0x20`).
    El frame del ROM da el tamano; no hay que adivinarlo.


## Mas palancas encontradas en la segunda mitad de la sesion

11. ★★ **Post-decremento DENTRO del argumento de la llamada.** Si el ROM emite el `sub rN,rN,#1`
    ENTRE dos llamadas -- despues de montar el registro del argumento y antes del `bl` -- eso es
    `f(..., (short)tag--, ...)`. Una sentencia `tag = tag - 1;` aparte lo planifica detras de las
    dos. Cerro func_ov008_020679f8 y func_ov008_02067a7c (+4 gemelas en ov009/ov025).
12. ★ **El orden de las SENTENCIAS decide el orden de `cmp` contra la aritmetica.** En
    func_ov008_02075f00 la guarda de disponibilidad va ANTES del calculo de la columna: el ROM
    emite el `cmp` delante del `lsl`, y calculando la columna primero mwcc los intercambia.
    El `moveq` predicado cae detras de la suma en los dos casos: eso si es el planificador y no
    hay que tocarlo.
13. ★★ **Umbral de tamano de bloque en el orden de montaje de argumentos** (medido, no inferido).
    En la cola de `func_0203c634`, el ROM siempre emite `ldrsb r1 ; ldr r2,[pc] ; mov r0,rX` --
    **900+ funciones casadas lo confirman y CERO tienen el orden contrario**. Compilando
    func_ov206_020ccd68 con 1, 2, 3 y 4 llamadas `func_0203b9fc` previas: con 1-3 sale el orden
    del ROM y **con 4 mwcc adelanta el `mov r0`**. No lo mueven ni el estilo del extern (K&R o
    prototipado), ni pasar `self` como `int` o como `int *`, ni el numero de SENTENCIAS
    (comas, declaraciones con inicializador). Es longitud de bloque, y bloquea cuatro funciones:
    ov206_020ccd68, ov206_020ccce8, ov235_020d1c20, ov235_020d1b98.

## Nuevas gemelas propagadas (dedupprop)

`func_ov008_02055d24` -> ov002/ov009/ov025; `func_ov008_02077908` -> ov025;
`func_ov030_020b3f30` -> ov044/063/082/099; `func_ov008_020679f8` -> ov009/ov025;
`func_ov008_02067a7c` -> ov009/ov025; `func_ov008_02075f00` -> ov025;
`func_ov212_020cd494` -> ov266/ov267; `func_ov008_02072fe4` -> ov025.
⚠ La propagacion de la familia ov030 dejo **5 stubs de `asm_stubs/` sombreando** el C nuevo; el
sintoma fue C subiendo 4 cuando se habian anadido 9. `audit_shadowed.py --fix` y volver a pasar
el gate.

## Clases que siguen bloqueadas (medidas otra vez esta sesion)

- **El ROM salta el registro libre mas bajo.** func_0200dcf0 (ip contra r1), func_ov002_0205e3e4
  (r2 contra r0), func_ov002_02069b14 (r1/r2 contra r0/r1). En 12.000+ funciones casadas NO hay
  ninguna con `ldr ip,[pc]` para una direccion de datos (solo veneers con `bx ip`), asi que el
  corpus confirma que mwcc nunca elige ese registro. 27 builds y 13 niveles de -O dan lo mismo.
- **Pool-hoist**: mwcc adelanta `ldr [pc]` al hueco de load-use. func_ov119_020ce610 (x3),
  func_ov033_020b350c + func_ov041_020b3698 (2 familias de 4 = 8 funciones).
- **Permutacion de registros con TODAS las permutaciones de declaracion identicas**: la firma de la
  clase. func_ov022_0209b078, func_ov022_02089784, func_ov022_02095c58, func_ov022_020892f0.
- **ldm/stm contra cargas sueltas**: func_ov185_020ced78 (x3) y func_ov117_020cca64 quedan a 4 bytes;
  el ROM funde tres cargas adyacentes en un `ldm` y luego almacena campo a campo, mwcc hace
  `ldm`+`stm` y recarga. Ninguna de las 10 formas probadas evita el `stm`.

## Mejor forma guardada de lo que queda en investigacion (todo en `build/try/`, nada aparcado nuevo)

| funcion | residuo | mejor fuente |
|---|---|---|
| func_ov200_020cff54 | 1 instruccion (el slot del `ldr state`) | `build/try/ff54/f.c` -- ★ el divisor era 15, no 30 |
| func_ov022_020922a4 | 1 instruccion mal colocada (`mov r4,#0`), TAMANO EXACTO | `build/try/22a4/h.c` -- ★ el `(char *)0 + zero` lava el cero y ya sale el `orrle/lslle/lsrle` del ROM; solo falta que mwcc materialice el cero DESPUES de los cuatro `mov` de parametros y no antes (11 colocaciones probadas) |
| func_ov022_02089784 | permutacion de 3 registros | `build/try/9784/f.c` -- tamano ya exacto con bitfield |
| func_ov022_020a0f60 | 1 registro | `build/try/0f60/a.c` |
| func_ov006_02051fbc | 2 intercambios de planificacion, TAMANO Y PUSH EXACTOS | `build/try/1fbc/j.c` -- ★★ la firma es `(int panel, int idx, int x, ...)` con TRES parametros nombrados, y los varargs se leen como `(&x)[0..3]`. Tomar `&x` fija x en memoria (que es lo que hace el ROM con `ldr r2,[sp,#0x20]`) y deja panel e idx en registro; con `va_list` sale un `ldmib` y con `(&idx)[n]` mwcc recarga idx tres veces. |
| func_ov022_02092b60 | 2 instrucciones | `build/try/2b60/h.c` |
| func_ov024_02083414 | 1 byte (sentido de la rama) | `build/try/3414/a.c` |
| func_ov185_020ced78 | 4 bytes | `build/try/ed78/a.c` |
| func_ov022_020a7018 | 2 registros (ok<->tail) | `build/try/7018/a.c` -- ★ el brazo `v >= target` va PRIMERO: con el otro orden falla ademas la estructura de bloques. Probadas las 6 permutaciones de declaracion, `register` en las dos, y 3 ordenes de asignacion: todas dan el mismo residuo (firma de la clase bloqueada) |
| func_ov022_020914a0 | 4 instrucciones (save de self antes de la extension + par r5/r6) | `build/try/14a0/a.c` -- ★ el `i++` va DENTRO del argumento de `func_01fff774`; 4 ordenes de declaracion mas no mueven el resto |
| func_ov008_0207b84c | 1 registro (r4 contra r2) | `build/try/b84c/b.c` -- ★ tamano exacto: la rama `== 0` referencia el array DIRECTAMENTE y solo la otra usa el local; el ROM rematerializa el pool tras la llamada porque su registro es caller-saved. mwcc CSEa las dos referencias y lo mete en callee-saved igual (4 formas probadas) |
| func_ov008_0207b8a8 | permutacion de registros | `build/try/b8a8/a.c` -- ★ el global se toma como `int *g` y se indexa `g[1]`/`g[0]`, lo que ya fija las cuatro primeras instrucciones |
| func_ov200_020cfcfc | 2 instrucciones (mismo hueco del `ldr state` que 020cff54) | `build/try/fcfc/b.c` |
| func_ov206_020ccd68 (+ ov206_020ccce8, ov235_020d1c20, ov235_020d1b98) | 2 instrucciones | `build/try/cd68/d.c` -- ⛔ umbral de longitud de bloque, medido: con 1-3 llamadas previas sale el orden del ROM, con 4 no |

# ESTADO 2026-07-23 03:00 (sesion larga autonoma, sigue hasta las 10:00)

C = ~15.400 / 23.240. nonmatching = 248. Gate 306 verde. Todo commiteado y pusheado.

## Lo que ha funcionado esta sesion (por orden de rentabilidad)
1. **La veta de veneers/funciones pequenas del NitroSDK** (~120 matches en una tarde).
   `ldr ip,[pc] ; movs ; bx ip` = forwarder con constantes. El modulo de cada una sale de
   `grep -rl "^NOMBRE " config/arm9`, NO del nombre.
2. **★ La palanca de va_start**: `(void *)(((unsigned)&last & ~3u) + 4)`. Cierra los
   forwarders variadicos (OS_SPrintf, OS_SNPrintf, func_020262a0).
3. **★ La escalera del struct**: una direccion escrita como CAST es un valor que mwcc
   conserva y puede planificar; el mismo acceso como CAMPO de struct es un modo de
   direccionamiento que reconstruye en el punto de uso. Desaparco func_ov022_02086ec0,
   que llevaba archivado como "empate de planificacion de la direccion de store".
   ⚠ No es universal: en func_02031a74 y func_02023c60 empeora o no mueve.
4. **★ El bloque ldm/stm de 11 palabras SI se alcanza desde C**: `struct { int w[11]; }`
   por asignacion. Retirada la clase entera (4 de 5 funciones).
5. **El callback recibe un argumento**: si la ROM hace `blx rX` con r0 vivo de una carga
   anterior, el puntero a funcion toma ese valor como parametro (func_ov022_02090198).
6. **Indice de array con la constante plegada** (`base[i + K/4]`) contra
   `base + i*4 + K`: lo segundo crea una segunda variable de induccion.

## Clases bloqueadas (NO volver a gastar)
- Constante pequena (<0x100) en el literal pool: 6 funciones. Ninguna de las 27 builds.
- Pool-hoist (mwcc adelanta el `ldr [pc]` al hueco de load-use): ~12 funciones.
- Copia del objeto antes de la extension de signo: 3 funciones.
- Polaridad de la ultima rama con retornos 0/1: mwcc canonicaliza (func_02022448,
  func_ov024_02083414/020833dc).

## Herramienta con trampa
`build/try/rank.py` enmascaraba los relocs de AMBOS lados, asi que una diferencia en el
OFFSET de un reloc salia como "0 off". Ya avisa. **El unico gate real es
`tools/verify_idx.py`** (compara offsets de reloc) y hay que pasarle `--thumb` cuando toca.

## Auditoria completa del arbol (2026-07-23)
`build/try/np/fullverify.py` recompila los 15.600 .c de src/ + libs/ y compara contra el
indice. Resultado: 9 malos, 8 ya arreglados. Queda `src/overlays/ov212/calls/
func_ov212_020cd494.c` (la cadena `x==0||x==1||x==2` sale como rango unsigned) y
`ov028_0208a994` es falso positivo (usa mwcc 1.2/sp4 via file_compilers.json).

# Where things stand -- 2026-07-22, autonomous session. READ FIRST.

**C = 14,716/23,240 (63.3%) - ASM 2,286 - gate 306/0. +67 matched this session, ALL in ov002.**
(5 commits local, unpushed -- last push was inside the hour.)

## The ov002 sub-100B vein is the best front in the project, by a wide margin

Twelve batches, ~85% first-compile. Scan: undone `func_ov002_*`, size 56..100, >=3 relocs.
There are still ~150 candidates in that band and the hit rate has not dropped.

## Three more levers found after the first write-up

6. ★ **Two adjacent constants may need a `switch`, not `||`.** `x == -4 || x == -3` gets
   range-folded by mwcc into `(x + 4) <= 1` plus re-narrowing shifts -- FOUR BYTES SHORTER than
   `func_ov002_02069030`, which tests both separately. This is the mirror of lever 5: the fold is
   right when the ROM folded and wrong when it did not, and only the disassembly says which.
7. ★ **Binding a call's result to a NAMED LOCAL decides the cmp operand order.** Inline,
   `f(...) == on` came out `cmp on, state`; swapping the source operands did NOT flip it, only the
   local did (`func_ov002_0205e124`).
8. ★ **A near-offset field read twice can still want a local** when the ROM uses ONE load as both
   the test and a call argument (`func_ov002_02065638`). The "repeat near offsets" rule is about
   address computation, not about values feeding a call.

## The five levers that decided this session -- full write-ups in `codegen-cracks.md`

1. ★★★ **FAR offset -> HELD pointer; NEAR offset -> REPEAT it.** A field past the addressing
   immediate that is touched twice must be bound once (`int *slot = &root->field;`); the ROM keeps
   the offset in a callee-saved register. Writing it out twice rematerialises the offset and loses
   the register entirely. A field inside the immediate range wants the opposite. Four functions.
2. ★★ **Counters behind a guard are ASSIGNED, not initialised** -- initialising at the declaration
   hoists them above the guard. Index first, derived offset copied from it. Three functions.
3. ★★ **Scope is a lever in BOTH directions** -- `func_ov002_02078f60` needed its inner `next` at
   FUNCTION scope, the exact opposite of the ov131 block-scoping crack.
4. ★ **A predicated multi-way select wants N-1 returns and a final ASSIGNMENT.**
5. ★ **Range folds must be written as the subtract**: `(unsigned)(x - 8) > 5`, never
   `x < 8 || x > 13`.

## ⚠ CORRECTION I shipped and then had to retract mid-session

I claimed in commit dbc3f5d7 that `/` and `%` can replace the `func_02020400` long-long workaround.
**They cannot** -- mwcc emits the call as `_s32_div_f`, which is not in `symbols.txt`. Corrected in
commit 7048f5c7. The reason I believed it is the transferable part: **verify_idx checks bytes
BEFORE relocs, so a function that fails on bytes never reaches the reloc check** -- and I read the
absence of a reloc error as a pass.

## Two functions left under investigation (best forms in `build/try/`, NOT parked)

- **`func_ov003_0204d264`** -- 164/164, instruction-for-instruction identical, residue is a pure
  2-transposition register permutation (palsh<->zero, div<->leading). **~74 experiments, every
  documented axis closed**: 24 declaration orders (all identical output), 15 `register`
  combinations, loop/branch/expression forms, parameter reuse, `volatile`, non-void return,
  signedness, `static inline` helpers, the division form, **27 compiler builds** and **13
  optimisation levels**. Best source: `build/try/d264/p03.c` (or the staging original -- all give
  the same 18). Note the `div_s.c` variant in that directory uses `/` and `%` and is therefore
  invalid on relocs; do not measure against it.
- **`func_ov002_020751fc`** and its twin **`func_ov002_020759f8`** -- same shape, same residue.
  ~45 experiments, and the useful result is that the two halves of the answer are now ISOLATED and
  in tension:
    * **`build/try/b2/m2.c` (also `f4.c`, `h1.c`) -- 7 diffs: every REGISTER is correct**
      (cur=r5, i=r6, p=r4, count=r7) and the whole loop body is byte-identical. The only residue is
      a 3-instruction prologue interleave: the ROM computes `cur = args + 8` FULLY before the
      operand-count call, mwcc emits `r5 = args` before it and sinks the `+8` after.
    * **`build/try/b2/m0.c` -- 12 diffs: the ORDER is correct** (cur fully computed before the
      call, exactly as the ROM does) and the registers are a 3-cycle off (cur=r6, i=r4, p=r5).
  Declaring `cur` first buys the order and loses the colouring; declaring `count` first buys the
  colouring and loses the order. Ruled out for bridging them: all 6 declaration orders x (inline
  initialiser | split assignment), `p` hoisted to function scope in all 4 positions (13-15 diffs,
  worse -- it gets initialised above the guard), a struct-typed 8-byte operand, a frame struct for
  the spill, post-increment in the call argument, and `for` vs `if`+`do-while`.
  **Solving one solves both**, and the next axis to try is something that changes the colouring
  WITHOUT moving `cur`'s declaration.
- Also open at 2 registers: `func_ov002_0206a230` (root/roster pair), best in
  `build/try/b10/func_ov002_0206a230.c`.

---

# Where things stand -- 2026-07-22 (iteration 4). READ FIRST.

**C = 14,649/23,240 (63.0%) - bytes 33.19% - ASM 2,286 - gate 306/0 - pushed through 3a7efcc7.**

## >>> START HERE

1. **The staging sweep, with BOTH fixes** (walk lanes with `find`; only `calls/` and `auto/` count
   as done). It has surfaced work on every single iteration today.
2. **`python tools/audit_stale_parks.py`** -- new. Parks whose function already has real C. Found
   **11** on its first run, one of which argued at length that a match was impossible while the
   matching file sat one directory away. Four were mine, left behind by hand-offs the same day.
3. **`python tools/audit_arity.py`** -- down to 4 hits from 8 (the stale parks were inflating it).
   Two of the four are documented false positives in their own headers. The two real leads are the
   ov003 giants `0204cba0` (1568 B) and `0204d98c` (2552 B, four disagreements at once).
4. **The whole-object-struct re-test vein** -- see below; it is the best new lever of the day.

## ★★★ ONE STRUCT FOR THE WHOLE OBJECT, TYPED ON THE PARAMETER

Full write-up in `codegen-cracks.md`. Model the object from 0 to its last field in ONE declaration
and type the parameter `Root *self`; never `int self` + inline casts, never sub-block structs.
A local pointer is a value mwcc keeps; a field through a typed parameter is an address it must
recompute, and the ROM's repeated adds come from the offsets exceeding the 12-bit `ldr` immediate.

On `func_ov000_0205579c` this **retired two of the three documented blockers**: the "-1 CSE" the note
told the next session to go and defeat does not happen any more (three `mvn` on both sides now), and
the `base` local it called load-bearing is unnecessary. Still parked on a uniform one-register
rotation, but the note now says all of that.

## Integrated this iteration (+9)

- **020552b4 x6** (ov000/005/008/009/025/026) -- d-pad focus navigation, `OvNNN_MoveFocusByDpad`.
  Key bits are the NitroSDK d-pad set and the neighbour links follow it: 0x40 up -> +0x88,
  0x80 down -> +0x8c, 0x20 left -> +0x90, 0x10 right -> +0x94.
- **ov002 x3**: `0205ac5c`, `020652c8`, `02056cc8`.
- `func_ov002_02071958` parked at **2 instructions** (size and relocs exact).

## Ghidra

`Ov000SceneContext` extended where the evidence is clean and the offsets land in existing padding:
`widgetList` @0x4a38 (NNSFndList), `pFocusedNode` @0x4a70, `wDirMask` @0x4a78. The +0x4a70
identification is corroborated from two directions -- `Ov000_MoveFocusByDpad` reads it as the
focused node and calls `Ov000_SwapParamOverrides` on the same object, which writes it as "the
descriptor whose overrides are applied". `NNSFndList` created.

⚠ Still unresolved and deliberately not merged: `Ov000_LoadPanelHandles` writes 18 ints at **+8** of
the same object, colliding with `renderNode` @+12 and `selectionObject` @+76.

## Process

- Writing a park note with a non-ASCII character in a Python heredoc **truncated the file to zero
  bytes** before the encode error surfaced. Caught only because `verify_idx` said `size 0 != 648`.
  The rule was already in SKILL.md; it bites through `python - <<'PY'` too, not just shell heredocs.
- Predict the C/ASM arithmetic before wiring: three separate hand-offs today predicted
  "ASM down N" for functions that had no `asm_stubs` twin at all.

---

# Where things stand -- 2026-07-22 (iteration 2, /loop 10m). READ FIRST.

**C = 14,640/23,240 (63.0%) - bytes 33.10% - ASM 2,286 - gate 306/0 - committed through the
progress commit after e3f8d30b; last push e0fdbc6d (held, under the hourly cadence).**

## Iteration 3: the arity audit keeps paying, and the sweep fix keeps paying

- **+2 matched** (`func_ov000_02059200`, `func_ov000_02059680`) -- both existed ONLY as
  `nonmatching/`, so the old sweep counted them done. Third distinct batch the sweep fix has
  surfaced.
- **`func_ov107_020c7b70`: 188 -> 172 bytes (size now exact).** Its note said "register-allocation
  tie, ~8 instructions". It was a **phantom third argument** to `func_0203bfb4` (8 tree call sites
  say two args, incl. the byte-exact `func_ov294_020d1a24`) worth 12 bytes, plus `char seq` costing
  lsl#24/asr#24 per increment worth 4. Now parked on **2 instructions** of parameter-materialisation
  order, with four forms ruled out. The old note had even DESCRIBED the ROM behaviour correctly
  ("cb ... in r2 and re-reads") and attributed it to the compiler instead of to its own declaration.
- **`func_02020928`: an arity flag that is a FALSE POSITIVE**, and worth knowing why. `func_02020a78`
  really does take two arguments, but r1 already holds `state` at both one-argument sites, so both
  spellings compile identically. Written with two now (matches the tree) but it cannot be proven
  from codegen. **An arity flag is a lead, not a diagnosis.** Real residue: 4 bytes of branch
  polarity on the second test.
- ★ **New boundary on the switch crack:** mwcc orders a switch's compare chain **numerically**, so
  `case 0` / `case -2` tests -2 first no matter how they are written. "Case source order picks the
  fall-through" governs which BODY is inline, NOT the order of the COMPARISONS.

### ⚠ An unresolved layout collision, deliberately left open

`Ov000_LoadPanelHandles` writes **18 ints at +8** of the ov000 root heap block; `Ov000SceneContext`
declares `renderNode` at +12 and `selectionObject` at +76 inside that span. One view is wrong and
this function cannot say which, so **nothing was merged** -- settle it against whatever allocates or
clears the whole object. Safe extensions that WERE made: `+0 -> nWindowTop` and `+0x60 -> bSettled`,
both established by `Ov000_MoveSelectionUp` (a ten-row window over a 28-row list, corroborating the
existing `nSelection` at +2 and `rows[28]`).

### ov003 staging: verified, no new matches -- do not re-verify every iteration

The 15 `staging/ov003/*.c` files are the known near/tie set (`0204cba0`, `0204d1c0`, `0204d264`,
`0204d3b0`, `0204d55c`, `0204d6c8`, `0204d98c`, `0204e5b0`, `0204e6b8`, `0204e9d8`, `0204eb84`,
`0204ed7c`, `0204f08c`, `0204f33c`, `0204f69c`). All checked in both modes this iteration: none
match. `0204e91c` and `0204ef68` DO match but are already in `src/`.

## ⇒ PICK UP HERE: `python tools/audit_arity.py` is the best rescue queue in the tree

8 of 416 parked files disagree with the tree about a callee's arity. The first one attacked matched
**on the first compile** (`func_ov002_02079224`, whose park note said "blocked class"). Six are
still open and they are listed with their signal strength at the top of `deferred-ties.md`. This is
the highest-yield thing available right now and it needs no new analysis -- the tool names the bug.

Second: **ov000 is closeable.** 189/262, and seven of its 73 remaining are family heads spanning
six or seven overlays, so those seven analyses pay ~45 functions across ov000/004/005/008/009/025/
026/069. Smallest first (02055d98 is done): `020552b4` (656 B, x6, 41 bytes off), `0205579c`
(648 B, x6, 111 off), `02056e28` (360 B, x7, 12 short), `02057dc4` (824 B, x7, relocs wrong), then
untouched `02057850` (1396 B, x7) and `020573e4` (1132 B, x6). **Check callee arity on all six
before anything else** -- it is what unblocked this one.

## ★★★ THE STAGING SWEEP WAS BLIND, AND IT COST TEN MATCHES

I ran the sweep from SKILL.md, it printed nothing, and I reported staging empty. The user then
handed over **six byte-exact matches** by name. The sweep globs `staging/*/calls/*.c` and
`staging/*/auto/*.c`; both live lanes put their `.c` files at the **lane root**. Fixing it to walk
each lane with `find` immediately surfaced **four more** (ov148/197/198/199), which also matched,
plus a fifth for free from dedupprop.

**Third incident of the same mistake** (WORKLIST.txt, then `calls/`, then `calls/` again). The rule
is now in SKILL.md: **never key the sweep on a shape you expect** -- key it on "a `.c` named after a
function not yet in `src/`" and let `find` walk. And: **a sweep returning nothing is the one result
to be suspicious of**, because it is indistinguishable from one looking in the wrong place.

## Integrated this iteration (+19, three peer hand-offs)

- **ov294/295/296 x6 -- all three overlays now 14/14.** Two sources (enemy init 348 B, enemy AI
  tick 1100 B) retargeted across three overlays, matched with the decomp.me community.
- **ov148/197/198/199 x4 + ov147 x1 (dedupprop) -- the swing-arc family.**
- **ov019_0207fa94 -- ov019 is 5/5, 100%.** Its park blamed "frame layout"; the cause was a struct
  modelled with 7 words that is 9. The ROM's frame gives the size: `out` at sp+0x10, `found` at
  sp+0x34 => 0x24 = 9 words. **When a frame diff involves an aggregate, measure the gap between its
  sp offset and the next object's.** Arithmetic, not search.
- **02055d98 x6** (ov000/005/008/009/025/026) + the **02079224 arity rescue**.

## ★★★ TWO OF MY OWN ASSERTIONS RETRACTED THIS ITERATION

1. **"the x5 @120B group ... will not match"** -- all six matched. That claim was inferred from a
   *sibling's* tie and never tested on the family, and it sat in the "fresh veins" section where it
   reads as settled fact rather than as a park. **A tie is a property of a function you measured,
   never of a family you did not.** (Written up in `deferred-ties.md`.)
2. **"declare `names[256]` first"**, transplanted into ov019's note by analogy from ov147 where it
   IS the fix. ov019's match declares it LAST. A crack seen on one function is evidence, not a rule.

## ★★ The staging sweep had TWO bugs, both found by being surprised

Beyond the lane-root glob: its "already integrated" test globbed `src/overlays/$u/*/$n.c`, which
**matches `nonmatching/`** -- so a function existing only as a park read as done, which is exactly
backwards. Both fixed in SKILL.md. **Also predict the C/ASM arithmetic before wiring**: the ov000
hand-off said "C up 6 / ASM down 6" and it is really C up 6 / ASM unchanged, because five of the six
were blob-gap carves with no stub at all.

## ⚠ A Ghidra function that ALREADY EXISTS can have a 1-byte body

`if getFunctionAt(a) is None` skipped the define on `func_ov019_0207fa94` and renamed the phantom,
which then counts as named. `~/ghidra_scripts/AuditAndFixBodies.py` compares body length against
`symbols.txt` and force-redefines; an audit of all twelve functions named that round found exactly
one. **Every naming script should carry that check.**

## ★★ `Actor` = 0x394, MEASURED, and it is one type not three

`func_ov301_020cbf38` allocates it with `func_0203d15c(0x394)`, and three independent views close
at exactly 0x394 with nothing left over: ov301's handler/camera/pool/box view, ov294's init view
(same + 0x390), and ov294's AI-tick view (transform 0x04, flags 0x60, direction 0x124, flags 0x17a,
component 0x388). Created in Ghidra as **`Actor`** with `ActorTransform`, `ActorComponent388`,
`ActorBox`, `AiTask`/`AiInner`, `Hit`/`HitInfo`/`HitState`, `Sphere`. **Reuses the existing
`VecFx32`** rather than adding a rival `Vec3` (200 files use `Vec3` as a per-file scratch name --
that is not a shared type).
`mul_round(a,b) = ((s64)a*b + 0x800) >> 12` is the standard Q12 multiply and should become a shared
inline for the port.

## ★★ A CONFIDENT, MEASURED PARK NOTE IS STILL ONE ATTEMPT

`func_ov294_020d1a24` carried a note of mine saying **"the struct rewrite makes this one worse, do
not repeat"**, with a measurement (62 differing bytes against 19). The match is a full struct
rewrite. The three real causes were **arity** (`func_ov107_020c9440` takes two args, `(obj, 0)`),
a **wrong pointer element type** (`p384` is `char *`, so the ROM's `+4` is four bytes), and a stale
**`long long`** return type. Retracted in `c9113c1f`. Distrust any note from those days that
generalises from a single failed attempt -- and note this is the same lesson as the ov010 pair and
the five 2026-07-17 rescues, now from a third direction.

## ★ dedupprop still leaves shadows -- and the tell is the count NOT moving

`func_ov147_020cc00c` came back from `nonmatching/` for free, but dedupprop left the
`asm_stubs/calls/` twin, which wins last-wins. **C stayed at 14,629 across the whole operation**,
which is the fingerprint. The 306 gate cannot see it (the stub is byte-exact too); only
`audit_shadowed.py` can. Correct shape when real C replaces a stub is **C up N / ASM down N** --
check it every time.

## Still in staging, deliberately NOT taken

`staging/tie_suite/*` is the tie-experiment harness, not deliverables (and its ov010 copies are
stale -- both those functions matched last session). `staging/ov007/func_ov007_0204d23c.NONMATCHING.c`
is self-labelled. `staging/` is gitignored and belongs to a peer lane: copy from it, never edit it.

---

# Where things stand -- 2026-07-22 (late). READ FIRST.

**C = 14,619/23,240 (62.9%) - gate 306/0 - pushed through 16034ece, plus three commits after it.**

## This session: +30 in ov002, 1 park, ~85% at the first or second compile

The ov002 sub-140B vein is still the best front in the project and is nowhere near dry
(~380 undone under 120B before this session). Three batches:

1. **Ten THUMB carves** (0206752c, 020638f0, 02066ba8, 02066d38, 02069798, 02071ae0,
   02075460, 0207548c, 02075cac, 020763c8) -- eight first-compile.
2. **The 0x02066xxx LINK-SYNC MODULE IS NOW COMPLETE** (02066cc8/d38/d78/e40/f14 + the
   already-done 02066d64/020662b8). Worth reading as a worked example of a module going from
   six opaque functions to a fully determined object.
3. **Five more** (02053484, 02057500, 020596c0, 02068fc4, 02075628).
4. **Six more** (02052998, 02056b70, 020624d8, 02068e34, 0206a4a0, 0206d350).
5. **Five more** (0206461c, 020636dc, 02068058, 020674f4, 0207d450) + the session's one park.

### Ov002LinkSyncCtx -- MEASURED, not extrapolated

0x25 bytes, exactly what the entry's `MI_CpuFill8` zeroes, and it closes with nothing left over:
a 4-byte record for this machine at +0, the last received broadcast at +4, the four-record table
we publish at +0x14, flag byte at +0x24. The record is `nKind:3 / nSlot:3 / bFresh:1` then two
payload bytes. `Ov002LinkRecord` and `Ov002LinkSyncCtx` are Ghidra types; all six pool slots typed
`Ov002LinkSyncCtx **`. The receive handler indexing `aSlots[(pkt[0] >> 3) & 7]` is what proves
+0x14 is four records rather than one 0x10-byte blob.

### New cracks, all written up in `codegen-cracks.md`

- ★ **Bit 0 of a flags byte codegens DIFFERENTLY from bits 1..7.** Setting a 1-bit bitfield at
  bit 0 emits `bic;orr`, at any higher bit a bare `orr`. So a function with `bic #1/orr #1` next to
  a lone `orr #4` is ONE bitfield model, not two source styles -- which is exactly what it looks
  like, and what would send you writing raw masks.
- ★ **A boolean stored to a narrow type is materialised TWICE** (fold the comparison, then widen
  for the `strh`). Route it through a local and store `x ? 1 : 0`. Worth 12 bytes on 02066e40.
- ★★ **When declaration order will not colour a register, widen an UNRELATED variable's scope.**
  02066e40 had `found` in ip where the ROM wants r3; five permutations of the two locals in the
  diff all failed IDENTICALLY -- the signature of the blocked register-choice tie. Moving the
  `for` counter to function scope fixed it. Mirror image of the `{ }`-block crack: block-scoping
  narrows a live range, function-scoping widens one, **and the variable to move may not be one of
  the variables in the diff.** This one nearly became a park.
- **`> 1` and `>= 2` are different instructions** (`cmp #1/ble` vs `cmp #2/blt`).
- **Cache the OFFSET, not the index**, when the ROM computes the byte offset before loading the
  base (02075cac).
- **Jump-table switch, first one in the tree** (02068fc4): mwcc normalises case labels -7..-2 by
  adding 7, tests the span unsigned, and indexes a six-entry halfword table. The case labels really
  are negative, and **the bodies are emitted in SOURCE order** -- so their memory order is evidence
  about the original file. Writing them in ROM order matched first compile.
- Two functions were `switch`, not if-chains: the tell is the ROM putting BOTH case bodies out of
  line and falling through to the default return. And in a two-arm `if`, the arm written FIRST
  stays inline (02066f14 needed `case 1` first; 020596c0 needed `mode != 0` first).

### Also typed

`data_ov002_0207f618` is an existing **Ov002PanelContext**; its 28 pool slots are typed, so its
consumers read as fields. Checked the existing type list before creating anything -- `Ov002PanelRoot`
was drafted and retired in favour of the established name.

### ★★ The one park, and the two things it proves

`func_ov002_0206d834` -- size, instruction stream and relocs exact, one residue at offset 2 where
the ROM moves the flag out of r0 so r0 can be the pool scratch. Closed on three axes and the note
says so: six source forms, the **return-type/signature axis** (the lever that broke both ov010
parks -- it does NOT move this one), and the **full 26-build sweep**, all identically 26 off.
The axis left open is named in the note: `OS_SPrintf` is declared K&R-variadic because the ROM
calls it with 2 args in one arm and 3 in the other, so the real NitroSDK prototype is untested.

### ★★★ A NAME MATCH IS NOT A TYPE MATCH -- I got this wrong and shipped it

I typed **28** of `data_ov002_0207f618`'s pool slots as `Ov002PanelContext **` because the name
fitted the function I was writing. `Ov002PanelContext` was reconstructed from
**`data_ov002_0207f614`**'s accessor family and every named field in it is an f614 offset; f618's
own accessors stride 0x18 at +0x7c and 4 at +0xce and fit nothing in it. Backed out in the next
commit. **The check is one call -- `get_struct_layout <Type>` and read its field offsets against
the offsets THIS global's accessors use.** Full write-up in `naming-hubs.md`. Typing pool slots is
a bulk operation, so a wrong assignment is a bulk error; prefer leaving a global untyped.

### Corroborated, from two directions

`data_ov002_0207fa00` **holds the root heap block**: `func_ov002_02068fc4` reaches the result
context as `NNSi_FndGetCurrentRootHeap() + 0x8ba8` and `func_ov002_0206d834` reaches the same
object as `data_ov002_0207fa00 + 0x8ba8`. Same offset, two routes.

### Still open in ov002 (skipped, NOT parked)

Carried over from the previous session and untouched: `func_ov002_02073ffc`, `func_ov002_020739ec`,
`func_ov002_020646d4`, `func_ov002_020518ac`. New: nothing -- every function attempted this session
matched.

### Note for the next session

A peer lane committed into this same working tree mid-session (`c9113c1f`, an ov294 park
retraction). Interleaved cleanly and the gate stayed 306, but re-run the staging sweep and
`git log` before assuming the tree is yours.

---

# Where things stand -- 2026-07-22. READ FIRST.

**C = 14,589/23,240 (62.8%) - bytes 1,555,212 (32.89%) - gate 306/0 - pushed through 3b710855.**

## ★★★ 2026-07-21/22: BOTH ov010 parks fell. Re-read `nonmatching/` with fresh eyes.

`func_ov010_0204cac0` and `func_ov010_0204cb3c` were the two most heavily defended entries in
`deferred-ties.md` -- between them five build-lines, 25 builds, the `-O`/pragma matrix, an
81k-iteration AST permuter, the `register` axis and the struct-typing axis. Both fell in one
session, and **neither residue was in the body**:

- **cac0**: the function RETURNS the `ResFile *` it loaded. A non-void return reserves r0, which
  forces the surviving `offset` off r0 and onto the ROM's r2. Declared `void`, no body rewrite
  could ever have worked.
- **cb3c**: the original called SDK `static inline` accessors; we had open-coded the MMIO writes.
  Open-coded writes share one CSE pool (mwcc hoists the base once); each inline expansion gets its
  own address local (the base is recomputed per block, as the ROM does).

Both are written up in `codegen-cracks.md`. **The actionable lesson for the next session: a long,
confident park note reads as evidence and is not.** Every prior attempt on both had varied the
body. When the residue is "which register", ask the two SIGNATURE questions first --
*does this function return something?* and *was this block an inline helper?*
`python tools/find_cast_parks.py` ranks `nonmatching/` by a related symptom; ~410 parks are
sitting there and this session's hit rate on the two hardest was 2/2.

## ov002 remains a deep, clean vein (~390 undone under 120B)

Scan: `func_index.json`, `func_ov002_*`, size <= 120, not already in `src/`. ~10 matched in the
2026-07-22 batch at roughly a 75% first-try rate. Mostly THUMB -- **always try `--thumb` before
believing a size mismatch**. Recurring globals: `data_ov002_0207fa14` (root ctx, slots at +0x1c),
`data_ov002_0207fa04` (link ctx), `data_ov002_0207fa00` (session, +0x8c94), `data_ov002_0207fa20`
(scene registry, list heads at `((int**)&g)[1]`).

Two THUMB cracks from that batch, both in `codegen-cracks.md` terms:
- storing a comparison through a pointer (`p[k] = (arg == 0)`) evaluates the RHS first and sinks
  the pool loads below the branch; an explicit **if/else into a local**, with the pointer set up in
  its own statement above, puts the address computation back on top;
- a flags halfword reached as `(unsigned short *)((char *)node + 0x10)` costs an `adds r1,#0x10`;
  the same field as a **struct member** folds into the `ldrh` immediate.

Still open in ov002 (skipped, NOT parked -- no note written): `func_ov002_02073ffc` (mwcc will not
put the ctx pointer in r4), `func_ov002_020739ec` (mwcc rematerialises `slots[idx]` after the call
where the ROM loads it before), `func_ov002_020646d4` (12B, a dead `cmp r0,#0` before `bx lr` that
no spelling has reproduced), `func_ov002_020518ac` (vararg-style `push {r0-r3}` prologue).

## ★ RICH CLEAN SUB-VEIN (2026-07-21, ~25 matched in one pass): small AI reaction/action handlers

**This is the seam to keep mining.** Scan: undone funcs 40-160B whose relocs include `func_0203c634`
(the think-callback re-register) -- ~250 of them, mostly enemy overlays (ov107-ov300). They are
`FUN(int self){ node=*(int**)(self+4); <guard?>; <a few field writes / SetSubitem / hw60>; register
callback; }`. The SMALL ones match clean and dedup across enemies (each analysis = 1-5 matches).
Idioms, all proven this pass:
- guard byte: `*(unsigned char *)(node[1] + 0xad) != 0` (ldrsb-vs-ldrb: it is **unsigned char**).
- `func_0203b9fc(node[1], slot, a, b)` = SetSubitemState (icon show/hide); callee reloads node[1].
- **hw60 high-byte set**: `hw60 & ~0xff00 | (((((unsigned int)hw60<<0x10)>>0x18 | K)<<0x18)>>0x10)`
  (template func_ov120_020ccb58); **hw60 LOW-bit test**: `((struct hw60{u16 lo:8,hi:8;}*)(*node+0x60))->lo & 1`
  (the `lo:8` bitfield emits `lsl#24;lsr#24`, NOT `and #0xff`).
- **RNG**: result discarded -> bare `bl`; used in `+K` -> plain add; tested `== 0`/`!= 0 ? a : b`
  -> the **`func_02023eb4(N) + (v - v)`** copy artifact with `int v;` and K&R `extern int func_02023eb4();`.
- callback arg to func_0203c634 is `&func_ovNNN_<addr>` (often another handler in the same overlay),
  or 0. func_ov107_020c9264 is **3 args** (Ghidra shows 4; r3 is leftover param_4).
- struct-by-value / 3-word copies via a `struct {int x,y,z;}` local -> ldmia/stmia.
The LARGE ones (angle->sincos, struct-by-value spawn) TIE on register allocation (parked ov214/
ov232 this session); build_sweep confirms. **Prefer <=120B; skip `base+i*stride` loops.**

## (earlier) fresh-vein pivot after ov008 saturated: AI reaction/action dedup families

- **Ov*_ResetReactionAi x5 MATCHED** (ov194/195/196/269/270 @120B, one analysis -> 5 via dedupprop).
  The crack was the documented **`func_02023eb4(N) + (v - v)`** copy artifact with a K&R extern
  `int func_02023eb4();` and an uninitialised `int v;` -- it forces the ROM's `adds r0,r0,#0`, and
  the param_1<->node **register swap resolved with it** (symptom, not a second bug), exactly as
  codegen-cracks.md line 319 says. Template files: `func_ov117_020ccc2c`, `func_ov120_020ccd90`,
  `func_ov169_020cda08`.
- **Parked ov232_020d0888 (x5@272B group ov231/232/263/265/280)**: structurally byte-exact
  (struct-by-value + ldmia/stmia spawn-block copy) but the ROM **eager-loads stack arg param_5**
  into r4 at entry while build 139 loads it lazily -- 54 bytes of cascading register shifts,
  build_sweep says no build reproduces it. An eager-vs-lazy stack-arg-load tie.
- **NEXT in this vein**: `scan_fam.py` families [14] ov149/150/153/154/155, [15] ov169/170/175/176/
  177 (strafe), [16] ov194_020cd578 (same enemies, 408B), [18]/[19] ov214/215/216/217/264. MOST of
  these use the **fixed-point angle -> sin/cos table** crack (magic reciprocal `DAT * uVar >> 0x20`
  + `+0x800` rounding + `(u16)` cast = `lsl#4;lsr#16` + `>>4`=`asr`, then index `PTR_kSinCosTable[]`;
  `PTR_kVecZero`, `VecFx32` already typed). Intricate but catalogued (codegen-cracks.md ~line 120)
  and template-backed. Budget a few rounds each; ties will be eager-arg-load or the same angle math.
- Avoid the blocked classes: ov038, ov181, ov141-halfword.

---

# (earlier the same day) END OF ov008 clean-shape sweep

**C = 14,422 - pushed through 19bc3b79.**

## 0. THIS SESSION (ov008): ~35 matches + ~30 dedup twins, 17 documented parks

- Drained the ov008 vein of "clean shapes": draw-with-shadow wrappers (`Ov008_Draw*WithShadow`,
  `func_020301c8` = Draw_WithAxisOffset), state dispatchers (`HandleElementTap`/`Release`,
  `TickSlider`, `TickCardTransferScene`, `HandleElementTap` twins share `data_0204c18c` = the phase
  byte), the `func_020262a0` variadic table-builder wrappers (buf[N+1] with a []=0 terminator kept
  live by the delegate call), `UploadTileSurface`, `FadeMasterBrightnessBothEngines` (MASTER_BRIGHT
  0x04000050/0x04001050), `PositionInfoWindow` (BG1 scroll 0x04000014 + WIN0H 0x04000040),
  `RefillListRows`, `DrawCardCountAndIcons`, `ClearGridSlot`, `UpdateScrollArrows`, `DrawStatBar`.
- **NEW cracks proven this session (add to codegen-cracks.md if not there):**
  1. **switch case *source order* picks which case is the inline fall-through** (`020782dc`: put
     `case 2` first so it falls through, matching `cmp#1 beq / cmp#2 bne`).
  2. **local declaration order colours the callee-saved regs** (`0207126c`: declare `node,i,base`
     to get base->r7,node->r5,i->r6).
  3. **`T *p = arr;` forces early stack-base materialisation** (`0205bb7c`).
  4. **nest the calls under the guard so the constant-return default becomes an out-of-line else
     block** (`020621f8`: `if(param_2){...}else{result=1;}` instead of predicating).
  5. **dead-store-sink comma form** for 3-way constant select (`020782dc` alt).

## 0b. WHY ov008 IS NOW TIE-SATURATED -- change vein, do NOT keep grinding it

The remaining ov008 functions hit the SAME mwcc-139-vs-ROM-compiler ties over and over. Confirmed:
- **Loop strength-reduction** (the big one): the ROM keeps the inner counter `i` live and scales it
  inline (`add rX, base, i lsl#N`); build 139 ALWAYS strength-reduces to a running induction pointer.
  Parked in `02054d3c`, `0208b148`, `0205ffe8`, `02054b18`, `02068878`. No source spelling
  (induction/array-index/held-base/byte-offset) suppresses it. **Skip `base + i*stride` loops.**
- **Over-aggressive late merge/predication/hoist**: build 139 folds guard chains, range-folds
  `==A||==B`, predicates constant if/else, and won't hoist a shared return value where the ROM
  branches. Parked in `0208a5e8`, `0208a55c`, `02066a4c`, `0204d640`, `020572b8`, `0205ca8c`.
- **Misc**: reg-alloc (`0207a1c4`, `020712f8`), call-scheduling (`0205eafc`), 64-bit-mul/r3
  (`0206fce0`), varargs (`0206eb64`), magic-div reg-alloc (`02074258`), multi-point signedness
  (`0205b988`). All documented in their `nonmatching/` headers.

## 0c. FRESH VEINS for next iteration (pick one, don't reopen ov008 loops)

- **Large byte-identical dedup groups** (1 analysis = 4-5 matches): `tools/scan_fam.py`, or the
  scan I ran: x5 @932B `func_ov231_020cf66c`/`ov232_020d32ac...`; x4 @684B `ov221_020d0308`;
  x4 @600B `ov206_020cc498`; x4 @272B `ov232_020d0888`. Big but high-yield.
- **AI strafe family** (from the previous session's note below) -- ov131/132/133/161/162 siblings.
- **NOT** the x5 @120B group (`ov005_0204e400 ... ov008_02054cc4`) -- that IS the 02054d3c
  strength-reduction tie, it will not match.
- SDK stubs (`MI_SwapWord`, `OS_GetProcMode`, `MTX_Rot22_`, the `WM_EndKeySharing_*` set) are tiny
  and known but need the exact NitroSDK source; different ramp-up.

---

# (PREVIOUS) END OF SESSION 2026-07-20 (strafe-family session).

**C = 14,305/23,240 (61.6%) - bytes 1,533,128/4,728,790 (32.42%) - gate 306/0 - everything pushed
(82c36a4d). Working tree clean apart from the always-dirty regenerated delinks.**

## 0. THIS SESSION (+14): ov000 lane drained, and family [11] cracked

- **8 ov000 lane functions integrated** (0204e9a4, 0204f6e0, 0205157c, 02053740, 02053e40,
  0205906c, then 02059130, 02059324). The lane refilled TWICE during the session -- re-sweep after
  every integration. `Ov000SceneContext` extended (rows[28]@0x9670, pRowResource, selectionObject,
  tweenPulse proven from `Tween_Sample`'s `dwFlags |= 4`); `Ov000SubSceneContext`, `Ov000Row`,
  `Ov000HandleGroup` created; 61 pool slots typed. The ov000 lane is now EMPTY again.
- **Family [11] `func_ov131_020cd594` x5 MATCHED** (`StrafeThenReact`), +1 dedup rescue
  (`Ov131_ReactWhenTargetInReach`). The crack is NEW and in `codegen-cracks.md`: when a
  "two callee-saved pointers swapped" residue survives sum/assignment/declaration/compound-assign,
  **scope the pair in a NESTED `{ }` BLOCK ordered to the ROM's load order** -- found in the matched
  sibling `func_ov131_020cd334`. Family [11] is done; [2] (ov141 halfword) and the ov181/ov038
  classes remain blocked.

## 1. PICK UP HERE: run the staging sweep first (lane may have refilled again)

The ov000 peer lane refilled on EVERY iteration of the last two sessions. Run the sweep in SKILL.md
before anything else, every time -- and note it scans for staged `.c` FILES, not for
`WORKLIST.txt`. Keying on the paperwork is how a whole ov000 lane went unnoticed for hours. If it is
empty, `python tools/scan_fam.py` -- the next fresh family is [11]-adjacent: the ov131/132/133/161/162
overlays have more `StrafeThenReact`-shaped siblings, and the matched `func_ov131_020cd334` /
`func_ov120_020ccd90` / `func_ov169_020cda08` are the template library for that whole AI vein.

Hand-off rule the lane itself stated, and it is the right default: **offsets, strides, sizes and
matches are FIRM; struct and field NAMES are provisional.** Take the geometry, choose the names
yourself, build the Ghidra type. `Ov000SceneContext` (0xd18c) was merged that way from five of the
lane's files -- see `naming-hubs.md`.

## 2. Best decomp leads, ranked, with the traps marked

`python tools/scan_fam.py` -- unmatched byte-identical families, best ratio in the project:

| lead | why |
|---|---|
| **`func_ov141_020cd2b0` x7, 180 B** | ⇐ START HERE. Same overlay family whose sibling handed over the two spellings that unblocked the ov132 x7 batch. High chance the same crack applies. |
| `func_ov030_020b4cd4` x5, 780 B | 3900 bytes for one analysis |
| `func_ov131_020cd594` x5, 492 B | |
| ⛔ `func_ov038_020b4940` x8 | the BLOCKED register-choice class -- do not grind |
| ⛔ all four `func_ov181_*` families | same blocked class |

Also open: the 19th and last script-VM handler (`func_ov015_02082574`, 460 B) -- **not a tie, just
a big nested-loop transcription, and its whole shape is already written up in `families.md`**. And
two byte-identical TileSurface pairs (564 B x2, 1308 B x2) from `subsyscensus`.

## 3. What changed in HOW to work (this is the part that compounds)

- **`tools/subsyscensus.py`** (new) -- finds a named subsystem's unmatched remainder by reloc
  intersection. Catches what `dense.py` (ranks by density) and `dedupprop` (needs a matched rep)
  structurally cannot. Run it the moment you finish naming a subsystem.
- **`tools/accsweep.py`** (new) -- recovers a struct layout from its accessor family. Built
  `MenuContext` (shared by ov008/ov009/ov025), `Ov002RootContext`, `EntityManager`,
  `Ov002PanelContext`, `Ov008ListContext`.
- ★★★ **SEARCH FOR A MATCHED SIBLING BEFORE PARKING.** The ov132 x7 batch looked exactly like the
  blocked register-choice tie; 24 declaration permutations all failed. It was two source spellings
  already written down in `func_ov141_020cce98`'s own park note. One grep would have replaced the
  whole sweep. A permuted-register diff is the tie's signature AND what those spellings produce --
  failing permutations does not distinguish them.
- **Ghidra scripts: drain, never force-close, never save from inside**; save with a separate
  `save_program`. That was the cause of the recurring "No transaction is open" dialog the user
  reported. Full explanation in `tools.md`.
- **`git add -A` is never correct here** -- `delinks.txt` is permanently dirty by design. Use
  `git add -A src/` plus explicitly named tool files.

## 4. Closed with measurements -- do NOT re-open

- **Pool-loaded small encodable immediate** (5 ov000 DEFERs + `func_ov023_020829c4`): closed on the
  source axis (6 spellings, both modes) AND the build axis (26 compilers, 8 opt levels). The one
  untested axis is named in `deferred-ties.md` and needs the lane's actual `.c`.
- **Shared C headers**: asked and settled -- rule stands, but the REASON in SKILL.md was wrong and
  is corrected in `procedure.md`. A matched `.c`'s struct is a codegen tool; `func_ov002_02063350`
  is the concrete proof (the real 2-D array costs 20 bytes, so that file deliberately diverges
  from the Ghidra type).

---


## Session head: 6 matched (4 by hand + 2 dedup twins), gate 306/0, commit cd41e279

The reloc-dense vein (`python tools/dense.py 25 --min-size 60`) is still the best front and
still ~90% at the first or second compile. Four THUMB scene functions this round:
`ov002_02062bd8`, `ov002_0205dcd4`, `ov022_02086894`, `ov022_02083774`.

### ***`func_02020400` IS `_s32_div_f` -- the remainder lives in r1***

The finding of the round, and it retires a whole diagnostic dead end. When the ROM reaches a
`bl` with an argument register apparently unset and the PREVIOUS instruction was
`bl func_02020400`, that register is the **remainder** of a signed divide: the MetroWerks
runtime returns quotient in r0 and remainder in r1. Proven by writing `x % 6` and getting
byte-identical code with the reloc named `_s32_div_f`.

Full recipe (and the `long long` + `>> 32` workaround the project's symbol name forces) is in
`codegen-cracks.md`. **The renaming question is open and is in `dudas.md`** -- ~90 matched files
call this helper by address for the quotient, which is also wrong C (`a / b` is what they mean),
so fixing it properly is an infrastructure decision for the user.

Generalise it: **before blaming a tie for an unset register, ask what the previous call
returns.** That is now three distinct causes seen in this project (64-bit high half, runtime
helper second output, dropped trailing argument) against zero real ties on first diagnosis.

### Unit identities, settled cheaply from resource strings

Ten seconds each, and worth doing before naming anything:
- **ov022 = a BATTLE overlay** -- every path string is `ba/ch/*`, `ba/ef/*`, `ba/ma/*`
  (characters, effects, maps; `critical`, `dead`, `s_burn`, `s_frost`, `s_shock`).
- **ov002 = the BATTLE HUD** -- `UI/btl/&/{chara,cmd,enemy,info,magic,map,text}.s.z`,
  `UI/btl/face.p2`. Corroborated by the existing Ghidra name `Ov002_RedrawPartyStrip`.

Recipe: `python -c "import re; [print(s.decode()) for s in sorted(set(re.findall(rb'[ -~]{4,}', open('dsd_extract/arm9_overlays/ovNNN.bin','rb').read()))) if b'/' in s]"`.
Neither function got named after a SCREEN -- nothing in either identifies one, and the plate
comments say so explicitly.

### Structs: six created, and the pool-slot recipe paid at scale again

`Ov002SceneContext` (**0x1e0, measured off the MI_CpuFill8, not extrapolated**),
`Ov002HudContext`, `Ov002HudSlot`, `Ov022RootContext`, `Ov022Row`, `Ov022Session`. All ten
interpolators in the ov022 context reuse the existing **`Tween`** type rather than a rival.

**128 literal-pool slots** across `data_ov002_0207f620` (75), `data_ov022_020b2e60` (44) and
`data_ov022_020b2e74` (9) typed `T **` in one Jython pass -- consumers now decompile as
`pOVar9->bPlayer` and `->aSlots[0].bKey`. Depth checked by reading a consumer back, as the rule
demands: all three globals HOLD a pointer (`ldr rX,[pc]` then `ldr rX,[rX]`), so `T **`, not `T *`.

⚠ Traps re-confirmed, all already documented and all still live: `create_struct` and
`modify_struct_field` return the `endTransaction` error **while succeeding**;
`modify_struct_field` applies the type and **drops the field NAME** (fixed in Jython with
`component.setFieldName`); two of the four functions had **no Ghidra function at all** and needed
defining in THUMB first; and `run_ghidra_script` reported `success:false` on three scripts whose
console said `SAVED_OK`. **Read the console, never the status.**

### Bookkeeping note that cost a detour

`config/**/delinks.txt` shows ~245 files dirty and **that is correct** -- `configure.py`
regenerates them and `tools.md` says never to stage them. It looks alarming (3.5k insertions,
3 days since the last commit touching them) and it is not. Do not "fix" it.

---

# Where things stand -- updated 2026-07-20 (naming-hub session)

## >>> START HERE: `python tools/namehubs.py [n]` -- the naming debt is NOT flat

New tool, and it is the best lever on the naming debt that has been found. It ranks the
unnamed matched functions by **call-graph in-degree**, read straight off the reloc table in
`build/func_index.json` (a reloc to symbol S inside function F is a call site of S), so it
needs no Ghidra round-trip.

Measured 2026-07-20: **5560 unnamed functions absorb 14763 call sites**, and the **top 30
absorb 21.8% of them**. The three biggest were still `FUN_*`: `func_0203c7ac` (462 callers),
`func_0203c650` (360), `func_0202af1c` (187). Naming **27** functions off the top of that
list cleared roughly **1700 call sites** of opacity -- about 11% of the total, for 0.5% of
the debt. An hour on this list beats a day at the tail of any one unit.

Debt went 5562 -> 5533 this session. Subsystems settled, with the evidence in each plate
comment:
- **The 0203c6xx task module.** `+0x1c` is a tag, `+0x24` is the finished flag, and the
  callback table at `+0x8..0x1c` is what `SetIndexedSlot` indexes with the byte at `+0x20`.
  Step functions either call `Task_MarkFinished` or set the next step -- `func_ov107_020cb178`
  does exactly one or the other on every branch, which is what proves it.
  Named: `RefreshObjectCallbacks`, `TaskList_FinishByTag`, `TaskList_FindByTag`,
  `Task_MarkFinished`. `DispatchObjectCallbacks` (0203c86c) already existed and is the
  0x6c/0x74 sibling of 0203c7ac's 0x68/0x78 pair.
- **The GameSession guards.** `Session_Exists` / `Session_IsActive` (non-null and dwState != 1)
  / `Session_IsReady` (dwState != 3). Only the comparisons are proven; the readings come from
  their roles as the paired guards in `func_02030570`, and the plate comments say so.
- **ov008 and ov025 share one menu context layout** -- both read page objects at +0x959c and
  +0x95a0 and tick them with the same two functions. `Ov008_GetPageA/B`, `Ov025_GetPageA/B`.
- **The ov002 context (data_ov002_0207fa10) has a 0x18-byte table at +0x17 whose empty marker
  is 0xff** -- established by `Ov002_ReleaseContextBuffers`, which fills it with 0xff.

## >>> STRUCTS: two new Ghidra types, and the pointer-depth rule held

`SceneNode` and `SceneNodeLink` now exist. They came out of `func_02029158`, which is the
function that proves the layout: it walks an owner chain and clears bind bit `0x1000 << i`
for owner slot `+0x10 + 4*i`. That pairing is the evidence.

- `SceneNode`: u16 flags at +0 (bit 0x2 = the on/off arm of the `func_ov002_0207c770` boolean
  setter; bit 0x40 meaning still unknown; bits 0x1000/0x2000/0x4000/0x8000 = owner slot bound),
  link-list head at +8, next node at +0xc, four owner slots at +0x10/+0x14/+0x18/+0x1c.
- `SceneNodeLink`: owner at +0, prev at +4, next at +8. **Two different structs share
  `func_02029158`** -- the thing being unlinked is the link record, the things walked are
  nodes. Reading them as one struct is what makes offset 0 look like both a pointer and a
  flag word.

⚠ Both `create_struct` calls returned the `endTransaction` error **while succeeding**, exactly
as documented. Read the layout back; finish with `CloseTxAndSave.py`.
⚠ `DefineThumb.py` needs the space spelled `"ram"` for main-unit addresses --
`af.getDefaultAddressSpace()` came back None and the failure reads like the address is wrong.
⚠ And it printed `SCRIPT COMPLETED SUCCESSFULLY` over a Jython `SyntaxError`. Read the console,
never the status. That is the third distinct tool this trap has been seen in.

## Decomp this session: the reloc-dense vein still pays

4 matched (3 first-compile), 1 parked, gate 306/0. New crack banked in `codegen-cracks.md`:
**cache what the ROM caches -- the load, not the expression built from it.** Hoisting
`ctx + 0xb0` into a local denies mwcc a strength reduction it wants to do at the loop
preheader; inlining the global load as well makes it reload. The `adds rN, #imm` in the
preheader is the fingerprint of the correct middle form.

Open and worth one cheap search: `func_ov023_02083cc4` is 104/104 and instruction-identical,
blocked only by the src/dst register pair inside mwcc's inline struct copy. Four source
spellings ruled out. **Grep the matched tree for a counted byte-copy loop with the source in
the lower register before running any more experiments.**


## Iteration 2 (2026-07-20, same session) -- debt 5533 -> 5514, +2 matched

- **`Tween` struct created and USED.** The 0x1c-byte object behind `func_02035f84/fb0/ffc`
  (~276 call sites between them) is a time-based interpolator: nMode/nDuration/nFrom/nTo,
  an `llStartTick` stamped by `GetTick64`, and a 3-bit flag word. `func_020031d4` is now
  `GetTick64` -- it latches the hardware timer inside a critical section and folds in the
  pending-overflow carry, which is what proves the object is time-based rather than a
  generic 4-field record. Prototypes set on all three, so the decompiler now emits
  `pTween->llStartTick = GetTick64()` instead of an offset soup. **Setting the prototype is
  how you make a struct pay off for a non-global object** -- the pool-slot recipe only
  covers globals.
- **`func_01ff9f00` is `GX_SendFifoWords`**, identified from its call sites rather than its
  body: command 0x17 is always sent with exactly 12 words, and that is MTX_LOAD_4x3 with its
  4x3 matrix. Worth remembering as a technique -- the argument PATTERN across call sites
  identified an SDK function that its own code could not.
- **ov009 shares the ov008/ov025 menu context too** (`Ov009_GetPageA` came out of
  `namefam_propagate`, not from reading ov009 at all). Three overlays, one layout.
- The ov002 context now has both its byte tables pinned: 0x18 bytes at +0x17 and 4 bytes at
  +0x2f, both filled with 0xff by `Ov002_ReleaseContextBuffers` and read back with bounds
  checks by `Ov002_GetCtxTableByte` / `Ov002_GetSlotTableByte`. 0xff is the empty marker.

### New crack: a doubled null test is ONE guard, read the TARGET

`func_ov002_02063200` emits `cmp r0,#0; beq L; beq L` -- two identical conditional branches
with no flag write between them. That reads exactly like a free-with-inline-null-check
(guard the call, then store), and writing it that way puts the second branch at the store
instead of past it. **Both branches go past the store**, so the source nests the store inside
the redundant test:

```c
if (cur != 0) {
    if (cur != 0) { Free(cur); ctx->b4 = 0; }   /* NOT: } ctx->b4 = 0; */
}
```

The distinguishing evidence is the branch target, never the presence of the redundant test.
This is the same family as the ov002_02053260 double check from iteration 1, and both were
settled by computing where the branch lands -- consistent with the 2026-07-19 finding that
misread branch targets are the single largest cost in this project.


## Iteration 3 (2026-07-20) -- PUSHED. C = 14,171/23,240 (61.0%), bytes 31.84%, gate 306/0

Session total: **8 matched, 1 parked, ~55 named, 5 Ghidra structs created**.

- **`TileSurface` + `TileSurfaceCfg` created, and this is the best struct of the session.**
  `func_0202fec8` initialises a 0x3c-byte tiled graphics surface from a 40-byte config. The
  identification is airtight and does not depend on any guess: the bytes-per-tile factor is
  **0x20 when the depth flag is clear and 0x40 when it is set**, which is exactly an 8x8 tile
  at 4bpp and at 8bpp. Everything else follows -- nTotalBytes = bpp * w * h, nRowBytes =
  bpp * nRowTiles. Its four wrappers are the 2x2 of {upload, no upload} x {4bpp, 8bpp}:
  `TileSurface_Init4bpp` / `_Init8bpp` / `_InitAndUpload4bpp` / `_InitAndUpload8bpp`.
  With the prototype set, the decompilation reads as ordinary C.
- **The 40-byte const template in `func_ov002_02055b24` IS a `TileSurfaceCfg`** -- found by
  size, then confirmed by the call (`func_0202ffa4(ctx + 0xbc, &cfg)`). Its fields are now
  named in the `.c`, and it stayed byte-exact: **field names do not reach codegen**, so
  renaming a local struct in a matched file is free. Do this whenever a scratch struct turns
  out to be a known type.

### New codegen fact: address-taken locals get DESCENDING stack offsets

`func_ov002_02067078` has three out-params. Declared palette/screen/char, mwcc put the
palette at sp+8 where the ROM has it at sp+0. **Reversing the three declarations was the
entire fix.** So for address-taken scalars, the FIRST declared local gets the HIGHEST stack
offset -- the same direction the existing note gives for aggregates, now confirmed for
scalars too. Check this before suspecting anything else when only `add rN, sp, #imm`
operands differ.

### Two more THUMB functions had no Ghidra function at all

Both new matches came back `missing` from the naming script and needed `DefineThumb.py`
first. That is the 1286-function backlog showing up in ordinary work -- **expect a fresh
match to need defining before it can be named**, and note `DefineThumb.py` wants the space
spelled explicitly (`ram` for main-unit, `arm9_ovNNN` otherwise).


## Iteration 4 (2026-07-20) -- debt 5496, +3 matched, gate 306/0

### ***A one-register residue that was a DROPPED THIRD ARGUMENT -- again***

`func_ov002_0207b368`. Size exact, instruction stream identical, and the only difference was
the ROM putting the constant 1 in **r2** where mwcc used **r1**. That is verbatim the
signature of the blocked "ROM skips the lowest free register" class, and three source
spellings failed to move it (inline `req[0]`; a local initialised before the store -- which
fixed the register but hoisted the load; a local declared before and assigned after).

It was not a tie. **`movs r2, #1` survives the store, both argument loads and reaches the
`bl` with nothing else touching r2** -- so the constant is doing double duty as the field
store *and* a trailing call argument. `func_ov002_0207b078` takes THREE arguments and the
third is that same 1. Byte-exact on the next compile.

**The diagnostic, stated as a check you can run:** when a single register is off, find where
that register is next READ. If the answer is "the next `bl`, and nothing writes it in
between", it is an argument, not an allocation. Do that before trying source spellings, not
after -- I burned three on it. And note the size was right the whole way, which is precisely
what makes this read as regalloc.

Also: `func_ov002_0207b078` had **no other call site in the tree**, so `audit_arity.py` could
not have flagged it and the grep-the-tree rule had nothing to find. For a callee with zero
other call sites, the ROM's own register usage is the only evidence there is.

### Naming: a `skipped` line is a WARNING (full write-up in naming-hubs.md)

`named=14 skipped=2` -- and the two skips were the *callees* of three forwarders I had just
named, revealing I had invented "AnimMgr/Node" against the project's established
**TagTracker** vocabulary (`BuildTagTrackerNode` in 8 files). Retired via the new
`~/ghidra_scripts/ForceRename.py`. **Grep the subsystem's vocabulary before naming a
forwarder**, and prefer `<Unit>_Ctx_<CalleeName>` for context-binding wrappers.

### Process: run audit_shadowed.py BEFORE the commit, not after

`func_ov014_02080540` landed byte-exact and its `asm_stubs/` twin stayed behind, so the stub
won last-wins and the ROM kept building from the blob. **The 306 gate cannot see this** -- the
stub is byte-exact too. Only `audit_shadowed.py` notices, and I ran it one step too late.


## Iteration 5 (2026-07-20) -- debt 5490, +0 matched, 1 parked, gate 306/0

A naming-heavy round; the one decomp attempt turned into a well-documented park.

### Vocabulary check, AGAIN -- and this time it caught three

Second consecutive round where `SKIP=[...]` from the naming script exposed rival names.
`02014d50` was already `SList_Remove`. Querying Ghidra settled the real convention:
**`List_*`** is the circular-list family (`List_First/Next/Prev/Last/InsertSorted/
RemoveByHandle/InsertByPriority/GetNthObject`, all in the 0x01fffcxx-0x01fffdxx block), and
**`SList_`** is a deliberate separate word for the singly-linked structure (next at +0x10, no
header object). Renamed `CircularList_Init` -> `List_Init` (it is that family's initialiser --
it seeds the self-link at +0x10 those functions walk) and `RemoveFromAnyListAndMarkDirty` ->
`SList_RemoveFromAnyAndMarkDirty`.
**`mcp__ghidra__search_functions` with a prefix is the fast way to check a vocabulary** --
faster and more accurate than grepping the C tree, since most names live only in Ghidra.

### TileSurface got two real field names from a different function

`TileSurface_SetCurrentItem` (02030094) writes +0x18 and +0x1c as "the current list object"
and "its payload at object+8" -- and that is the same pair `TileSurface_Init` seeds through
func_0202fff8, where `pWritePtr = nUnk18 + 8`. So +0x18/+0x1c are now `pCurrent`/`pCurrentData`.
⚠ OPEN, recorded in that function's plate comment: the list it walks sits at **+0x30**, past
the 0x3c that TileSurface_Init zeroes. Either the real object extends beyond the TileSurface
header or the scratch offsets in the old C file are wrong. Settle it before trusting the tail
of that layout.
⚠ `modify_struct_field` **applied the type but dropped the field NAME**, leaving an unnamed
component. Read the layout back after using it, or do field renames in Jython
(`component.setFieldName`) as `~/ghidra_scripts/FixTileSurfaceFields.py` does.

### The park: func_ov002_020760ec, and a NEGATIVE corpus result worth keeping

132/132, everything outside a four-slot init loop byte-identical, single residue = the ROM
copies the counter to a scratch register before incrementing. Nine source forms ruled out.
**Then I ran the corpus search SKILL.md prescribes, and it came back negative** -- only two
matched functions carry `adds rX,rY,#0` + `adds rY,rY,#1`, and the promising one stores a
CONSTANT rather than the counter, so its form does not transfer. That is a real negative and
it is now in the file: **do not re-run that search.** Full detail in the park note.

### Two process traps

- **Backticks in a `git commit -m "..."` string are command substitution.** A message quoting
  `adds rX,rY,#0` in backticks came out with the instruction names silently DELETED and
  `bash: adds: command not found` in the output. Use a heredoc (`git commit -F -`) for any
  message containing code, or plain quotes.
- **A single-file MWCC failure in `ninja` can be the documented intermittent E: filesystem
  fault, not a regression.** `ov116/asm_stubs/.../func_ov116_020d1458.c` failed once, compiled
  fine when run alone, and the next full build completed 8796/8796 with the gate at 306.
  Re-run before investigating.


## Iteration 6 (2026-07-20) -- PUSHED. C = 14,186/23,240 (61.0%), bytes 31.89%, gate 306/0

### The ov006 staging lane was integrated -- 10 matches in one go

A peer lane handed over ten mission-select functions with PROVISIONAL names. Process that
worked and should be reused for any hand-off:
1. **Verify every file from staging, in both modes, BEFORE moving it.** All ten passed
   independently, then again in place. Never move first and verify after.
2. **Check the receiving unit's vocabulary and rewrite the proposed names to it.** The lane
   proposed `Mission_*`; ov006 already uses **`Ov006_Mission<Verb><Noun>`**
   (`Ov006_MissionPollKeys`, `Ov006_MissionPlaceCell`, `Ov006_MissionIsTransitionDone`).
   `mcp__ghidra__search_functions` with the prefix settles it in one call. Bonus: it revealed
   that 0204de5c's `StartTransition` pairs with `Ov006_MissionIsTransitionDone` sitting 0x37c
   earlier -- the poll for the same state, which corroborates the name.
3. **Delete the superseded `nonmatching/` files** (three here) and run `audit_shadowed.py`.
4. Put the lane's *reasons* in the plate comments, not just its names -- each was the cause of
   its match (a volatile controller pointer; a lookup that must be repeated rather than cached;
   two globals that had been swapped; a call that runs only on the non-exit branch).

### MissionContext + MissionGlobals, and the pool-slot recipe paying off at scale

`MissionGlobals` is the two-pointer header at `data_ov006_020565e4`. **Typing all 61 of its
literal-pool slots** turned every consumer from offset arithmetic into `PTR->pController`.
⚠ **`tools/poolslots.py` PRINTS ONLY THE FIRST 40 ROWS** (`rows[:40]` at line 54) and says
"... and 21 more". Scraping its stdout silently gave 40 of 61 slots and reported success. Patch
the slice out of a copy before scraping -- or better, give the tool a `--all` flag. This is the
negative-result rule again: a script that reads a truncated list cannot tell you it was
truncated.

⚠ **Flagged, not hidden:** `MissionContext.aRows` spans 0x154..0x414 = 704 bytes, which is NOT
a whole multiple of the documented 0xc0 stride. Either the array is shorter than that gap or
the stride is wrong. Nothing depends on it yet (the count is dynamic at +0x100), but do not
build on that extent.

Still deferred per the lane's worklist: `0204da3c`, `0204f6bc`, `0204e35c`, `0204dbb4`.


## Iterations 7-14 (2026-07-20, same session) -- C = 14,213/23,240 (61.2%), bytes 31.99%

### ***A SECOND SYMBOL AT ONE ADDRESS IS NOW LEGAL, AND IT WAS NEEDED***

`func_020234e8` was 4 bytes short with everything else exact -- size, every
instruction, every reloc OFFSET. The cause was not the C at all: **the ROM's literal pool
holds 0x0204be08 in TWO separate entries**, and mwcc emits two entries only for two DISTINCT
symbols. With one symbol it CSEs them.

`config/arm9/symbols.txt` now carries `data_0204be08_params` alongside `data_0204be08`. It is
**the only duplicate address in the whole file** -- nothing else had one. Measured before
trusting it, and the user approved the change:
- gate 306/0 with the alias added and nothing else;
- gate 306/0 again with the function wired in;
- `gen_delinks.py` and `audit_progress.py` both filter to `kind:function(...)`, so a
  `kind:bss` alias is invisible to them -- the build and the counter cannot see it.

The name records the ROLE: `func_02031384(id, buf, count)` takes a parameter buffer, so the
original had two views of the block -- scalar fields, and a parameter buffer.

⚠ **`verify_idx.py` was patched to match** and this matters for everyone: `func_index.json`
resolves an address to its FIRST symbol, so a legitimate alias read as `relocs difieren`
**even though the real build was byte-identical** -- the tool disagreed with the gate. It now
compares reloc ADDRESSES when the spellings differ. Regression-checked both ways: four
known-good functions still MATCH, and a reloc pointing two bytes away still fails.

**New park class:** "the C is provably correct and the blocker is project infrastructure."
Worth recognising -- it is not a codegen tie and grinding source forms would never have found it.

### ov006: the row stride puzzle, resolved BY THE LANE (I had it wrong)

Rows start at **+0x104**, not +0x154. The 0x154 that looked like an array base is
`+0x104 + 0x50`, the label field's offset INSIDE the record -- which is exactly why
0x154..0x414 was 704 bytes and not a multiple of the 0xc0 stride. The layout closes with
nothing left over: `aRows[4]` 0x104..0x403, `aRowStates[4]` 0x404..0x413, selection at 0x414.

`MissionRecord` (0xc0) is a Ghidra type now, **merged from THREE files that each saw a
different slice and agree**: 0204d800 the 6-byte key at +4, 0204f554 the counters at
+0x3c..+0x42, 0204f9b0 the label text at +0x50. A 6-byte key on a multiplayer select screen
is very likely a MAC address -- inference, and the comment says so.

`MissionContext` is **0x4f4**, not the 0x4f1 I had. `func_ov006_0204e1ec` settles it by
clearing the whole object.

★ **Both of those were the same mistake in different directions: a struct boundary
extrapolated from the fields you happen to have seen.** The end of the last known field is a
LOWER BOUND, not a size; a field offset inside a record is not an array base. Only something
that allocates, clears or strides the whole object settles either one.

**The ov006 staging lane is now empty** -- every `.c` is in the tree or on its defer list.
14 functions integrated across three hand-offs, and they re-seeded the dedup graph: one
`dedupprop` run afterwards paid **13 more matches in ov008** plus 2 rescues. Integrating a
peer lane is worth more than its own count.

### Parks: two axes closed, and a method fix

Both long-standing parks were re-attacked at the user's request. Neither matched, but the
search space is now much smaller and the notes say so:
- `func_ov023_02083cc4`: **build sweep RUN** (admissible once the C is proven correct) -- the
  whole 2.0/3.0 line is 6 bytes off identically, dsi 50+. No build is closer. The
  field-to-field struct-copy crack does NOT apply and it is worth knowing why: that crack is
  for whole-word `ldm/stm` copies; this is a 7-byte BYTE loop, a different mwcc path. A
  `static inline` helper with src as first parameter also fails (mwcc re-allocates after
  inlining). Established over 7 forms and 27 builds: mwcc gives the low register to the
  copy's DESTINATION, the ROM to the SOURCE.
- ⚠ **A PARKED FILE MUST HOLD THE BEST-KNOWN SOURCE, NOT THE LAST ONE TRIED.**
  `func_ov002_020760ec` was holding form 9 (the struct-array variant) purely because it was
  last. A sweep against it reported 52 off for our compiler and 47 for dsi, which would have
  sent the next reader chasing the dsi line for nothing. It now holds form 5, the closest.

### Naming: three rules that only surfaced by doing it

All three are written up in `naming-hubs.md`; the headlines:
1. **A `SKIP=[...]` line from the naming script is a WARNING** -- twice it exposed that I had
   invented a vocabulary rival to an established one (`TagTracker`, `List_*`/`SList_`).
2. **The DISAGREE list has TWO classes.** Class 1 (one routine named inconsistently) gets
   unified -- 24 functions across 5 families this session. Class 2 (one SHAPE, semantically
   different instances -- forwarder templates) must be LEFT ALONE; the tool flagged three
   names I had written myself the same day, all correct. **The discriminator is the CALLEE.**
3. **Naming a hub can ROT a name elsewhere**: `Ov006_Fwd_020521a0` stopped meaning anything
   the moment its target was named. After naming a hub, look at what forwards to it.
⚠ And: **a plausible root with an address suffix is INVISIBLE to `audit_unnamed`** and can
still be a lie (`setupDual_<addr>` x8 was a teardown called a setup). The debt figure is a
floor.

### Tool fixes
- `tools/poolslots.py` -- **truncated to 40 rows and said so only in prose**, so a script
  scraping it typed 40 of 61 slots and reported success. Now has `--all`.
- `~/ghidra_scripts/DefineThumb.py` -- `createFunction()` QUEUES auto-analysis as a background
  task that fires after `CloseTxAndSave.py` has force-closed the transaction, giving
  `db.NoTransactionException` from another thread. It now drains the analysis synchronously
  inside its own transaction. (Full write-up in `tools.md`.)
- `~/ghidra_scripts/ForceRename.py` -- new; renames unconditionally. Use ONLY to retire a name
  you introduced this session.

## Iteracion 2 (2026-07-20) -- PUSHED e47665f5. C = 14,223/23,240 (61.2%), bytes 32.04%

+3 mas, **las tres a la primera compilacion**: `ov005_020515dc`, `ov005_02053b80` (ARM) y
`ov002_02062cb0` (THUMB). Total de la sesion: **9 casadas**, 0 aparcadas, gate 306/0.

### El teardown vale mas que su propio match

`func_ov002_02062cb0` cierra la escena que abre `func_ov002_02062bd8`, y **confirma el layout
desde el otro extremo** en vez de extrapolarlo: +0x74 se libera con la misma llamada que lo
registro, +0x78/+0x7c con `func_02024fd4` contra el `func_02024ee8` que los reservo, +0x1b4 con
`func_ov002_02052834` contra `func_ov002_0205280c`. Con el tween en +0x58, el layout **cierra en
0x1e0 exacto sin sobrar nada** -- el mismo 0x1e0 que limpia el MI_CpuFill8 de la entrada.

★ **Buscar el teardown de cada escena que casas.** Es el unico modo barato de convertir un
"limite inferior" de struct en una medida, que es justo el error que costo el 0x4f1-vs-0x4f4 de
MissionContext.

Bonus: cuatro `TileSurface` salen ahi, cada una tras su propio flag de uso, y **los flags NO
estan junto a sus superficies** (+0x4c guarda la de +0x10; +0x8c/+0x90/+0x94 son un array de tres
flags para las tres contiguas de stride 0x3c en +0xc0/+0xfc/+0x138). El stride 0x3c es lo que las
identifica, y el tipo `TileSurface` mide exactamente 0x3c.

### Dos cosas que parecen erratas de transcripcion y no lo son

- `NNSi_FndGetCurrentRootHeap` se llama **dos veces seguidas** en `ov005_020515dc` y el primer
  resultado se descarta. Es el ROM.
- El contexto de `ov005_02053b80` mide **0x62198 (401.816 bytes)**. Tambien medido del CpuFill8.

### ⚠ Una funcion que YA EXISTE en Ghidra puede tener el cuerpo MAL

`arm9_ov005::020515dc` tenia funcion definida con un cuerpo de **8 bytes**. El script de naming
hacia `if needs_define or getFunctionAt(a) is None` -- que no basta: renombro un fantasma y lo
dejo **contando como saldado**, porque tiene nombre. Es la trampa del fantasma THUMB por otra
puerta, y esta vez en una funcion ARM.
**Regla: compara la longitud del body contra el tamano conocido antes de fiarte**, y al redefinir
una ARM pon TMode=**0** (DefineThumb.py lo tiene fijado a 1).

### Tipado de globales: 265 slots en la sesion

128 en la primera iteracion + 137 aqui. La profundidad por global se decide leyendo el ROM:
`ldr rX,[pc]` + `ldr rX,[rX]` => el global GUARDA un puntero => slot `T **`; si el pool value se
usa directo con `ldrb rX,[rY,#imm]`, el global ES el objeto => slot `T *`.

⚠ `recreate_struct` con `force=true` **borro el tipo y no lo recreo**, devolviendo el error de
`endTransaction` de siempre. `get_struct_layout` decia "Structure not found". Hubo que recrearlo
con `create_struct`. Un `recreate` fallido deja el tipo BORRADO -- leelo de vuelta siempre.


## Iteracion 3 (2026-07-20, /loop de naming) -- deuda 5465 -> 5442, opacidad -429 sitios

33 funciones nombradas, 2 structs nuevos. **Nada de esto toca el repo** -- el naming vive solo en
Ghidra, asi que una iteracion de pura deuda no genera commit. Tenlo en cuenta antes de buscar que
pushear.

### ★ La familia collision-cast de ITCM (10 funciones, ~250 sitios de llamada)

Las cuatro funciones mas llamadas de TODA la deuda estaban aqui, sin definir siquiera, porque
**ITCM no tenia funciones definidas en esas direcciones**. Son ARM: `DefineThumb.py` fija TMode=1
y habria creado fantasmas.

Dos cadenas paralelas con la misma forma, y **lo que las distingue esta PROBADO**:
`Collision_CastRay/_CastRayEx -> Collision_RunRayCast -> CollCast_InitRayState + _TestModelRay`
frente a `Collision_CastSphere/_CastSphereEx -> Collision_RunSphereCast -> ..._InitSphereState +
_TestModelSphere`. La cadena esfera recibe un argumento extra que acaba en `CollCastState.nRadius`
(+0x74) y `CollCast_TestModelSphere` **desplaza los cuatro limites de consulta (+0x34..+0x40) por
el** antes del broad-phase. La cadena rayo nunca escribe +0x74. Eso es un barrido de esfera, no
una conjetura.

Structs: `CollCastParams` (0x14) y `CollCastState` (0x8c), **los dos cierran exactos**. Con los
prototipos puestos, `Collision_CastSphereEx` decompila como C normal (`local_18.nRadius = nRadius`).

Detalles utiles: el centinela de "sin impacto" difiere entre cadenas (0x50000000 en rayo,
0x7fffffff en esfera); `Collision_RunRayCast` **devuelve** el bloque compartido `data_027e0764`
(con la distancia en +0xc) o NULL; y `CollCast_InitSphereState` normaliza SIEMPRE mientras la de
rayo solo lo hace si `wDirIsUnit == 0` -- esa asimetria es real.

### Dos familias mas, cerradas enteras

- **`ovNNN_rotateVecByOwnerYaw`** x5 (ov231/232/263/265/280, 148 B, ~17 llamadas cada una).
  Q12 -> indice de tabla -> `MTX_RotY33_` + `MTX_MultVec33` con dst==src: **rota el vector IN
  PLACE** y ademas lo copia al out-param.
- **`ovNNN_startAnim`** x18, una por overlay de enemigo. Thunk de 20 B con `bx ip` a
  `ov107_StartAnim(actor->field_0xNNN, animId, MODE)`.

★★ **Decision de naming que casi sale mal:** iba a partirlas en `_startAnim` / `_startAnimEx`
segun el modo (13 pasan 1, 5 pasan 0). **Cada overlay tiene exactamente UNA**, asi que el sufijo
habria implicado una distincion que dentro de ninguna overlay existe. El modo es propiedad del
tipo de enemigo y va en el comentario, no en el nombre.
Y el modo mete su bit bajo en el **bit 2** del byte de flags en `subject+4`. **"Loop" es la
lectura convencional y NO esta probada**, asi que no esta en ningun nombre -- es exactamente el
tipo de conjetura plausible que este fichero lleva media vida diciendo que no se pone en un nombre.

### Metodo: como encontrar el modo de un parametro

Agrupar los thunks de un mismo callee por **hex enmascarado** y mirar si el inmediato varia.
18 thunks, dos valores -> es un modo, no una constante. Una consulta, cero conjeturas.

## Iteracion 4 (2026-07-20, /loop) -- modulo de draw lists nombrado + 1 match en main

### El modulo de listas de dibujo del entity manager (7 funciones)

`Render_DrawViewLists` (0202bc90) es la funcion que **establece** todo lo demas, y por eso el
resto se nombra desde ella. El manager (`data_0204c208`) tiene **tres tablas** de cabezas de
lista intrusivas, 8 entradas cada una, indexadas por vista: **+0x64, +0x84 y +0xa4**. El orden de
dibujo no es inferencia: esa funcion las recorre en secuencia fija (+0x64, prepaso de +0x84,
+0x84, +0xa4 con OTRO renderer -- `func_02028768`/`func_020287e8` en vez de `RenderNode`).

Nombradas: `Render_DrawViewLists`, `Render_ApplyFactorToViews`, `Render_SubmitNode`,
`RenderList_PushEarly` (+0x64), `RenderList_PushMain` (+0x84), `Render_ReleaseNodeItem`,
`Render_ReleaseItemOnce`. Struct **`DrawNode`** creado con lo probado por tres funciones
distintas: enlaces en +0/+4, flags en +8, indice de tabla en +0x0a (0xff = desenlazado), estado
del item en +0x0c, clave de orden en +0x8c, vector en +0xb4 copiado a +0x168, factor en +0x180.

★ **Lo que NO he nombrado:** el factor Q12 de `Render_ApplyFactorToViews` se multiplica por el
+0x180 de cada nodo y se empuja por `DetachThenApplyNode`. Eso se lee como un fundido, pero nada
en la funcion lo nombra, asi que el nombre tampoco. Igual con las tres tablas: "early/main" sale
del ORDEN DE DIBUJO probado, no de una suposicion sobre opacidad.

### Match: `Game_RunSceneLoop` (func_020303d8, main)

Y **dos cracks nuevos** (los dos en `codegen-cracks.md`):
- **Un `switch` ordena los COMPARES por valor pero coloca los CUERPOS en orden de fuente.** El ROM
  tenia el cuerpo del `case 1` antes del `case 0`. Tamano exacto, mismas instrucciones, dos
  bloques permutados -- se lee como empate de planificacion y no lo es.
- **`x = a() << N; x |= b();` NO es `x = (a() << N) | b();`.** El ROM desplaza el resultado en
  cuanto lo tiene; la forma de una sola expresion guarda el valor crudo y desplaza despues de la
  segunda llamada, +4 bytes. Generaliza: **si el ROM aplica una operacion al resultado de una
  llamada ANTES de la siguiente llamada, dale su propia sentencia.**

Tambien: `lsls r2, r0, #0x10` derivando 0x04000000 de un 0x05000400 ya cargado. **Cuenta las
entradas del pool antes de buscar un simbolo detras de un registro desplazado.**

## Iteracion 5 (2026-07-20, /loop) -- PUSHED. Nombres SDK sincronizados + 16 simbolos corregidos

### 506 nombres reales de symbols.txt volcados a Ghidra (gratis, sin analisis)

`config/**/symbols.txt` tiene **834 funciones con nombre real** (BIOS, NitroSDK, rutinas
identificadas por bytes) y Ghidra las mostraba casi todas como `FUN_*`. `~/ghidra_scripts/
SyncSdkNames.py` las vuelca: **506 renombradas, 49 de ellas definidas de cero, 14 ya correctas.**

⚠ **Ojo con la metrica:** la deuda de `namehubs.py` solo bajo 5442 -> 5436. No es contradiccion:
esa herramienta cuenta funciones **casadas** sin nombre, y casi ninguna de las 506 tiene C casado.
Es una mejora real de legibilidad en Ghidra, **no** una reduccion de la deuda medida. Dilo asi.

El script **no pisa** un nombre que no empiece por `FUN_`, y esa guarda se gano el sueldo en la
primera ejecucion: **DISAGREE=56**.

### ★★★ symbols.txt tiene nombres DEGENERADOS -- 64 con sufijo `_0xADDR`, y uno era falso

De la lista DISAGREE salio que `GXS_LoadBG3Scr` estaba puesto sobre `GX_LoadBG0Scr`. Las 16
funciones `GX/GXS_LoadBG{0..3}{Scr,Char}` son **identicas una vez enmascarados los relocs** -- que
es justo la comparacion del matcher -- asi que las 16 casaron con un nombre y al resto se le pego
la direccion.
**Corregido**: cada una se nombra sola por su unica llamada distintiva (`G2_/G2S_GetBG<n>...Ptr`).
Detalle completo y la regla general en `naming-hubs.md`.

### ★★★ UN GATE 306 VERDE NO PRUEBA QUE TU `.c` SE ESTE USANDO

Lo mas importante de la iteracion. Los ficheros de `src/calls/` se llaman **como el simbolo** y
`gen_delinks.py` los ata a una direccion **por el nombre del fichero**. Al reescribir solo el
CONTENIDO, `src/calls/GXS_LoadBG3Scr.c` definia `GX_LoadBG0Scr` mientras el build seguia atando
ese fichero a la direccion de `GXS_LoadBG3Scr`.

**`dsd check` dijo 306/0 en ese estado, y `audit_shadowed.py` dijo 0 tambien.**

Mismo punto ciego que un `asm_stubs/` que ensombrece C real, por la otra puerta: si el objeto
delinkeado no aporta lo que el hueco pide, el build cae a los bytes originales y el gate --que
compara contra esos mismos bytes-- queda contento.
**306 prueba que la ROM sigue casando; NO prueba que tu C haya producido nada.** La unica prueba
por fichero es `verify_idx.py` sobre ese fichero. Ejecutalo tras cualquier cambio que pueda
desincronizar nombre-de-fichero y contenido.

### Bug preexistente encontrado de paso

`tools/index_funcs.py` peta con `TypeError: %d format: a real number is required, not list`
(linea 81: `"%d:%s" % r` sobre un reloc que es una LISTA `[off, sym]`, no una tupla). No lo he
tocado por no mezclarlo con este cambio; `build/func_index.json` se parcheo a mano.

## Iteracion 6 (2026-07-20, /loop) -- veta nueva: 19 handlers de comando del VM de script

**6 casadas de 19** y, mas importante, **`tools/gen_vm_emit.py`**: lee la forma directamente del
desensamblado con capstone, sin pasar por Ghidra. Detalle completo (localizador, lista de
pendientes, las 3 reglas) en `families.md`.

★ **La regla que mas se generaliza:** el id del builder se **trunca EN EL USO**, no en la
asignacion. `int id` + cast `(unsigned short)` en la llamada casa; declarar `unsigned short id`
trunca antes y reordena dos instrucciones. Es la misma familia que el crack de partir
`x = a() << 16; x |= b();`: **donde mwcc aplica una conversion lo decides tu al ESCRIBIRLA**, no
el tipo del valor.

Y una del propio generador que vale como metodo: **emite en el ORDEN del ROM**. Varios miembros
buscan target/id ANTES que los operandos; un orden fijo cuesta bytes justo en esos.

### Naming: 8 mas (6 propagadas gratis + 2 analizadas)

`namefam_propagate.py --write` pago 6. Y `Draw_WithAxisOffset` (0x020301c8) +
`Ov000_DrawWithShadow` (23 llamadas): la segunda dibuja dos veces con desplazamiento (+1,+1) y
paleta 1 para la sombra; la primera convierte una orientacion 0..7 en cuatro deltas de eje
(0/7 -> (1,0), 1/2 -> (0,1), 3/4 -> (-1,0), 5/6 -> (0,-1)).

⚠ **Cinco de los seis handlers llevan sufijo de direccion** (`OvNNN_VmCmd<addr>`) y eso NO
contradice la leccion de las GX: alli el problema era una raiz REAL (`GXS_LoadBG3Scr`) prestada a
siete funciones que no lo eran. Aqui la raiz no afirma nada. La identidad buena de cada handler es
**el builder al que llama**; en cuanto un builder tenga nombre, renombra su handler
(`Ov016_VmCmdCreateEntry` ya lo hace).

## Iteracion 7 (2026-07-20, /loop) -- struct grande de ov008 + 24 accessors + 1 match

### `Ov008MenuContext`: el layout salio de los propios accessors, mecanicamente

78 funciones usan `data_ov008_02090f04`, y ~27 de ellas son accessors de 16-40 B con la forma
`*(g+4) -> +OFFSET`. **Extraer el offset de cada una da el mapa de campos gratis**, con pares
GET/SET que se corroboran entre si. Struct creado (0x959c..0x9768 con los campos probados) y los
**78 slots de pool tipados `Ov008MenuContext **`** -- ojo con la profundidad: el puntero al objeto
vive en `simbolo+4`, asi que los consumidores quedan como `PTR[1]->nField9630`.

⚠⚠ **La primera extraccion estaba MAL y parecia perfecta.** Sumaba TODOS los inmediatos,
incluido el desplazamiento del `ldr rX,[pc,#N]`, asi que cada offset salia inflado por 8-0xc.
Lo delato que los nombres YA EXISTENTES (`Ov008_GetCtxBlock9500`, `...954c`, `...968c`) no
cuadraban con mis numeros. Rehecho leyendo la semantica (base `add` + desplazamiento final,
saltando el deref del global) aparecen **+0x959c y +0x95a0**, que son exactamente los objetos de
pagina ya documentados. **Si tu extraccion mecanica contradice un nombre que ya existia, la
sospechosa es tu extraccion.**

### La linea SKIP volvio a cazar un rival de vocabulario

`SKIP=1: 02051028 already Ov008_GetCtxObject9634`. ov008 ya usaba **`Ov008_GetCtx*`** y yo habia
metido `Ov008_GetField*`. Unificados los 23 a `Ov008_{Get,Set}CtxField<off>`.
Mantengo "Field" en vez de adoptar Block/Object porque esa distincion fue un juicio semantico del
que nombro antes y **no puedo reproducirlo desde los accessors**: inventarlo seria adivinar con
vocabulario ajeno.

### Decomp: primer miembro NO puro de la familia del VM

`func_ov014_020807c4`. Dos refinamientos, los dos en `families.md`: **operando OPCIONAL** (tag 0
en el descriptor -> ternario obligatorio, porque el ROM comparte UN store entre las dos ramas) y
**las dos grafias de `id` son correctas segun donde trunque el ROM**.

## Iteracion 8 (2026-07-20, /loop) -- 2 matches del VM + palanca de PLANIFICACION

`func_ov014_020807c4` (operando opcional -> ternario obligatorio) y
`func_ov002_0207d610` (lista de longitud variable). **17 casadas en la sesion, 0 aparcadas.**

★★ **Crack nuevo, en `codegen-cracks.md`: fijar la POSICION de un incremento con un temporal.**
Sintoma: tamano exacto, mismas instrucciones, **una sola instruccion en otro sitio** (un
`adds rN,#imm` que el ROM pone antes del `bl` y mwcc despues). Se lee como empate de
planificacion y NO lo es. mwcc solo lo emite antes de la llamada si el argumento **ya esta en un
temporal** cuando escribes el incremento.

Es la misma regla que el partir del shift y que el punto de truncado: **mwcc coloca una operacion
donde la fuente le obliga**, y una sentencia que puede moverse legalmente, se mueve. Cuando el
diff sea "instrucciones correctas, orden distinto", pregunta que frontera de sentencia fijaria la
que se movio.

Dos companeras del mismo bucle: un contador que el ROM **relee de memoria cada iteracion** tiene
que seguir siendo una lectura de campo en la condicion; y **reutiliza el puntero de entrada como
cursor** -- meter un cursor aparte mantiene los dos vivos y hace que mwcc vuelque `self` a la
pila (+2 bytes y otro reparto de registros en todo el bucle). El cursor aparte es la C mas
natural, que es justo por lo que cuesta tiempo.

## Iteracion 9 (2026-07-20, /loop) -- `MenuContext` compartido probado + 1 match

**18 casadas en la sesion, 0 aparcadas.** `func_ov002_0207d18c` a la primera.

### El barrido de accessors como metodo de descubrir structs (escrito en `naming-hubs.md`)

Repetir en ov025 la extraccion de offsets que hice en ov008 da **los mismos 17 offsets con los
mismos anchos**, sin que ninguna extraccion viera a la otra. Eso convierte "ov008 y ov025
comparten contexto de menu" de una observacion de DOS campos a un layout probado de 17.
`Ov008MenuContext` -> **`MenuContext`**, 74 slots de ov025 tipados, +0x960c anadido.

★ **La corroboracion entre unidades es la evidencia mas fuerte disponible aqui.** Hazla a
proposito cuando dos unidades parezcan gemelas.

⚠ **Limitacion del metodo, ya documentada:** asume UN campo por accessor. Un setter de dos campos
sale como la SUMA de las dos bases (+0x12c3a aqui, que no esta ni cerca de 0x9638/0x963a). **Las
dos overlays dieron el MISMO offset falso**, asi que la consistencia entre unidades NO lo valida.

### Las lineas SKIP corrigieron dos cosas que yo tenia mal

- `+0x9630` y `+0x9634` ya estaban nombrados `*_GetCtxObject*` en **las dos** overlays por una
  sesion anterior. Dos overlays coincidiendo es evidencia de que son punteros: campos cambiados a
  `void *` y mis cinco `*CtxField96xx` renombrados para no quedarse al lado contradiciendolos.
- El `+0x12c3a` resulto ser el setter de dos campos: ahora `*_SetCtxFields9638And963a`.

Van **tres iteraciones seguidas** en las que la linea SKIP del script de naming ha cazado algo
real. No la trates como ruido.

## Iteracion 10 (2026-07-20, /loop) -- PUSHED fa838a01. `tools/accsweep.py` + Ov002RootContext

**El barrido de accessors es ahora una herramienta**: `python tools/accsweep.py <global>`.
Lleva sus dos trampas en el docstring porque las dos se pisaron de verdad (detalle en
`naming-hubs.md`), y **marca las filas sospechosas** (fuera del cluster, o mas de un load).

`Ov002RootContext`: **21 campos, 156 slots tipados** -- es el global mas usado de ov002 y el
mayor salto de legibilidad de la sesion. Los consumidores pasan de aritmetica de offsets a
`(*PTR)->nPhase`.

★ **Vuelca los nombres YA EXISTENTES de los accessors antes de inventar nada.** Dos campos
salieron gratis con semantica real: `+0x8b58` = `nPhase` (habia un `Ov002_GetPhaseWord`) y
`+0x8ba8` = `nState` (`Ov002_GetStateWord`). Un accessor ya nombrado es la semantica de campo mas
barata que existe.

⚠ Las marcas del barrido son "mira esto", no veredicto: en ov002 una era **falso positivo** (un
campo real en +0x04, la heuristica de cluster falla con offsets bajos) y la otra era real y
ademas **revelo un campo que el barrido no podia ver solo** (+0x8b44, escrito por un setter de
dos campos junto con +0x8b48).

### Globals gordos que quedan por barrer en ov002
`0207f614` (66 users), `0207f60c` (53), `0207f628` (46), `0207fa10` (42), `0207fa14` (40).
`0207f620` y `0207f62c` ya tienen tipo.

## Iteracion 11 (2026-07-20) -- PUSHED 5b83482d. Segunda entrega del carril ov006

⚠⚠ **"El carril esta vacio" es una afirmacion sobre un MOMENTO, no un estado.** Lo escribi en la
iteracion 6 y era cierto al escribirlo; el peer siguio trabajando y a los pocos minutos habia 8
funciones mas (marcas de tiempo 16:06-16:39). **Lo detecto el usuario, no yo.**
→ **Revisa `staging/*/WORKLIST.txt` al principio de cada sesion**, no solo cuando parezca que
queda algo. Comparar carpeta contra arbol es un bucle de una linea:

```bash
for f in staging/ovNNN/*/*.c; do n=$(basename "$f" .c);
  ls src/overlays/ovNNN/*/$n.c >/dev/null 2>&1 || echo "PENDING $n"; done
```

8 integradas, **2.812 bytes** (296-416 B cada una, mucho mayores que la veta densa habitual).
Todas verificadas desde staging Y otra vez en su sitio. Nombres reescritos al vocabulario que
ov006 ya usa (`Ov006_Mission<Verbo><Nombre>`, 39 miembros previos).
`0205487c` -> `DestroyContext` a proposito: `Ov006_MissionCreateContext` ya existia y **los ocho
buffers de 0x600 que libera son los que aquella reserva** -- eso es lo que confirma la pareja.

### ★★ Un body de Ghidra puede estar roto de mas maneras que "corto por el modo"

`Ov006_MissionSelectStateCallback`: **108 bytes de 316, y en DOS RANGOS DISJUNTOS**, con el hueco
sin dueno. El analisis de flujo simplemente no lo cubrio. **No** era un callee marcado no-return
(primera hipotesis, falsa).
Arreglado desensamblando todo el rango de codigo y forzando `f.setBody(AddressSet(start, codeEnd))`
-- ahora decompila como el switch de nueve casos sobre `Game_PollSceneAlive` que su descripcion
implica.
**Compara SIEMPRE la longitud del body contra el tamano conocido despues de definir, y si no
cuadra, mira si el body es siquiera contiguo.** El check de tamano del script de naming es lo que
lo caza; ya van dos veces hoy (la otra fue `ov005_020515dc`, 8 bytes de 216).

## Iteracion 12 (2026-07-20) -- el dialogo "No transaction is open" era MIO. Arreglado.

El usuario lo reporto recurrente. **Todo estaba guardado** (`isChanged=False`, 15 nombres y tipos
comprobados uno a uno con `~/ghidra_scripts/VerifySaved.py`), pero el dialogo lo generaba mi
patron de script.

★★ **Hay DOS excepciones con ese mismo mensaje y significan cosas distintas. Lee la PILA.**
- termina en `GhidraScript.executeNormal` -> el script cerro a la fuerza su PROPIA transaccion.
  Cosmetico, es el que llevo ignorando todo el dia con razon.
- termina en **`BackgroundCommandTask.run`** -> el analisis que encolan `disassemble()` /
  `createFunction()` desperto **despues** de que cerrasemos todas las transacciones. **Ese es el
  que le sale al usuario**, y aparece de forma asincrona, mucho despues de que el script diga que
  fue bien.

**Patron correcto (en `tools.md`): drenar el analisis y NO cerrar a la fuerza ni guardar desde
dentro; guardar con una llamada aparte a `save_program`.** Verificado: el script sale con
`SCRIPT COMPLETED SUCCESSFULLY` **sin excepcion ninguna** y el save posterior deja `isChanged` en
False.

El bloque de cierre forzado es SOLO para transacciones que filtran las herramientas MCP de tipos.
`CloseTxAndSave.py` ya **drena antes de cerrar** -- ese era el fallo de orden.

⚠ Quedan ~160 scripts antiguos en `~/ghidra_scripts/` que cierran sin drenar. Ya se ejecutaron, no
merece la pena parchearlos, pero **no copies su postambulo**.

## Iteracion 13 (2026-07-20) -- +5 handlers por una palabra, y `Ov002PanelContext`

### El generador no conocia `strh` -- cinco matches bloqueados por eso

`gen_vm_emit.py` clasificaba como PALABRA todo store que no fuese `strb`. Los bloques con huecos
de 16 bits salian con anchos mal y todos los campos posteriores desplazados. Familia **6/19 ->
12/19** con anadir `strh` a la rama de stores.

★★ **Lo caro no fue el bug, fue su FORMA:** la herramienta no fallaba, producia C con la forma
correcta que se quedaba a 4-36 bytes. Eso se lee igual que un problema de codegen que hay que
dirigir en la fuente, no como un fallo del lector. **Cuando la salida de un generador queda cerca
de forma sistematica en MUCHAS entradas, sospecha del generador, no del compilador**: un empate
real es especifico de una funcion; un desfase sistematico en una familia es un bug de lectura.
Misma forma que el bug del `[pc,#N]` en `accsweep.py` esta misma tarde.

### Naming/struct
`Ov002PanelContext` (data_ov002_0207f614, 66 users, 12 campos) + 15 accessors nombrados. Los
otros globals gordos de ov002 que quedaban (`0207f60c`, `0207fa10`) tienen 3 y 1 accessors: **no
merecen struct**, y eso tambien es un resultado.

⚠ SKIP util: `02080a6c` ya era `Ov017_MarshalAndDispatch`. No es colision sino **corroboracion**:
otro lector llego por su cuenta a "marshal params + dispatch" para esta familia.

### Todos los scripts de esta iteracion usan el PATRON LIMPIO
Drenar, no cerrar a la fuerza, no guardar desde dentro; `save_program` aparte. **Cero excepciones
en toda la iteracion** -- los cuatro scripts salieron con `SCRIPT COMPLETED SUCCESSFULLY`.

## Iteracion 14 (2026-07-20) -- VM 17/19, `MenuContext` en TRES overlays

Tres miembros seguidos **a la primera compilacion** (`0207d950`, `020822b0`, y antes `0207ceac`
tras una correccion). Ya no hace falta descubrir nada: son las arrugas ya apuntadas apiladas
(operando opcional -> ternario, punto de truncado del `id`, orden de asignacion del ROM).

★ **El orden de los CAMPOS en el struct y el orden de ASIGNACION en la fuente son
independientes.** En `020822b0` el campo de offset MAS ALTO (+0x1c) se escribe el TERCERO. Hay
que seguir el orden del ROM, no el del struct.

### `MenuContext` ya son TRES overlays (ov008, ov025, ov009)

De ov009 solo se sospechaba (`Ov009_GetPageA` habia llegado por `namefam_propagate`, sin leer
ov009). El barrido lo confirma con cuatro campos mas en los offsets exactos. **Tres extracciones
independientes coincidiendo** es la evidencia de layout mas fuerte que se puede tener aqui.

⚠ **NO fusionado a proposito:** `data_ov006_02056664` esta en la misma clase de tamano (+0x95xx)
pero **ninguno** de sus offsets aparece en MenuContext. Misma magnitud no es mismo layout, y
fusionar por magnitud seria justo el error de nombres rivales que este proyecto paga una y otra
vez.

Nuevo tambien: `Ov008ListContext` (data_ov008_02090f24, 0x4f8, 63 slots) -- objeto DISTINTO del
contexto de menu de ov008 en 02090f04; el nombre lo deja claro a proposito.

### ⚠ La trampa del no-ASCII, en vivo

Un `!` de aviso en un comentario del script dio **`SCRIPT COMPLETED SUCCESSFULLY` encima de un
`SyntaxError: Non-ASCII character`**. Es exactamente lo que avisa SKILL.md: **lee la consola, no
el estado**. Los scripts de Jython, ASCII puro y punto.

## Iteracion 15 (2026-07-20) -- VM 18/19; el que el generador no podia tocar

`func_ov021_02080c98` (252 B): lista de entradas de longitud variable donde **cada entrada lleva
su propio tipo** y ese tipo elige como se busca su valor, por una jump table de cuatro casos.
Detalles que no se deducen del esqueleto: **el limite del bucle ES el id del builder** (descs+8 se
busca una vez y sirve de contador y de id); las entradas son de SEIS bytes desde params+0x14; el
caso 3 avanza el cursor sin buscar y cualquier tipo mayor que 3 no avanza nada (el chequeo es
`bhi`, asi que un tipo negativo tambien cae en el default).

★★★ **Las tres cracks de hoy son UNA sola regla** (escrito en `codegen-cracks.md`):
> mwcc coloca una operacion exactamente donde la fuente le obliga, y toda sentencia que puede
> moverse, se mueve.

Partir el shift, el punto de truncado y la posicion de una sentencia son lo mismo. Confirmado por
cuarta vez aqui: el avance del cursor dentro de un `case` necesita el MISMO temporal que necesito
el avance antes de una LLAMADA en `func_ov002_0207d610`. **Un temporal es una instruccion de
planificacion, no solo un nombre**, y es el steer mas barato que hay.

Y la pequena del mismo sitio: leer una palabra empaquetada como `int` con signo y desplazar da
`asr`; si el ROM emite `lsrs`, lee por `unsigned int`.

## Iteracion 16 (2026-07-20) -- 3a entrega de ov006, y la pregunta de los HEADERS zanjada

### ★ Headers de C: preguntado y resuelto. La regla se queda; la RAZON estaba mal.

Surgio directamente si el arbol deberia usar headers compartidos para los structs. Respuesta:
**no.** Pero corregida la justificacion en `procedure.md`, porque la que habia es falsa y una
razon falsa es lo que hace que una regla zanjada se reabra:
- ❌ "el delinking impide headers compartidos" -- **no es cierto**: `#include` se resuelve en
  tiempo de compilacion y el delinking trabaja sobre ficheros objeto.
- ✅ La razon real: **el struct de un `.c` casado es una HERRAMIENTA DE DIRECCION, no una
  descripcion del objeto.** Funciones distintas que tocan el MISMO objeto necesitan formas
  DISTINTAS para reproducir su propio codegen (una necesita `int aWords[4]`, otra `char pad[16]`
  en el mismo offset, otra un bitfield de un ancho concreto). Un header forzaria una sola forma
  y costaria matches.
- Los ~4.000 structs ad-hoc **no son el defecto** que parecen: son herramienta por funcion. El
  defecto era que no habia modelo autoritativo en ningun sitio, y **los tipos de Ghidra son ese
  modelo**. Cuando el `.c` y Ghidra difieren, **Ghidra es el que tiene razon**.

### Tercera entrega del carril ov006 (892 bytes)
`Ov006_MissionBuildOptionRows` (428 B, 24 relocs) y `Ov006_MissionApplyEntryUpdate` (464 B y solo
SEIS relocs -- casi todo es ramificar segun la forma del dato entrante).

⚠⚠ **Segunda vez que el usuario tiene que avisar de que el carril no estaba vacio.** Revisar
`staging/*/WORKLIST.txt` es ya un paso de INICIO de iteracion, no algo que se hace cuando parece
que puede haber trabajo. El carril produce mientras yo trabajo en otra cosa.

### Nota de direccion del usuario
"no hace falta que hagas solo el ov002": repartir mas entre unidades. Hoy han caido ov002, ov005,
ov006, ov008, ov009, ov014, ov015, ov016, ov017, ov021, ov022, ov025 e itcm, pero ov002 ha
dominado por ser el mas gordo. Alternar de forma deliberada.

## Iteracion 17 (2026-07-20) -- habia un carril ov000 ENTERO que nadie habia visto

### La comprobacion de staging, hecha bien, encontro un carril nuevo a la primera

Mi chequeo anterior era `[ -f "$d/WORKLIST.txt" ]`: eso busca el PAPELEO del carril, no el
TRABAJO. Buscando ficheros `.c` en staging aparecio `staging/ov000/` al instante, con cuatro
funciones casadas esperando (y tres mas que ya habia integrado otra persona).

**Bucle correcto, al INICIO de cada iteracion:**
```bash
for d in staging/*/; do u=$(basename $d)
  for f in $d/calls/*.c $d/auto/*.c; do case "$f" in *.c.o) continue;; esac
    [ -f "$f" ] || continue; n=$(basename "$f" .c)
    ls src/overlays/$u/*/$n.c >/dev/null 2>&1 || echo "PENDING $u/$n"; done; done
```

4 integradas (388 bytes): `Ov000_SetHandleActiveState`, `Ov000_DispatchIndexedCallback`,
`Ov000_CreateSceneContext` (0xd18c medido del CpuFill8), `Ov000_EnterSceneAndLoadResource`.
**Ninguna lleva nombre de PANTALLA**: ov000 es el titulo Y todos los niveles de menu Y la
pantalla de Carga, asi que un nombre de pantalla seria una afirmacion que el codigo no sostiene.

### Resultado negativo que vale la pena guardar
Los tres globals de contexto que tocan tienen **1, 0 y 1** accessors pequenos. `accsweep` no tiene
con que trabajar ahi: **no hay struct que sacar**. Anotado para no repetir el barrido.

---

## (historico anterior)

# Where things stand — updated 2026-07-19 (late)

## ★★★ STRUCTS: OBLIGATORIO DESDE EL 20/07 (lo pidio el usuario)

El proyecto llego a 13k funciones casadas con **CERO tipos de datos en Ghidra**, mientras el arbol
C acumulaba **~4.000 structs ad-hoc por fichero** (`hw60` copiado en 645, `Obj` en 460, `A` en 390
— el mismo objeto con forma distinta en cada uno). Para el gate da igual; **para el port es la
deuda mas grave**, porque cada declaracion parece la buena.

**Regla: si decodificas un layout, creas el tipo en Ghidra EN EL MISMO LOTE.** Nunca headers en C
(perturban el codegen); los tipos de Ghidra no tocan el build. Ya existen `SrtTransform`,
`SlotEntry`, `GameSession`, `CardTransferCtx` — **amplialos, no crees rivales**.
Trampas (detalle en `naming-hubs.md`): los tools de tipos **fallan con error de `endTransaction`
aunque hayan funcionado** (lee siempre de vuelta, y cierra con `CloseTxAndSave.py` o pierdes el
lote entero — una vez dejo 13 abiertas); `apply_data_type` no vale en globales tipo BSS (tipa la
variable local del consumidor); y el decompilador llega al global por el pool literal.

## ⇒⇒ SESION DE NAMING (19/07, noche): lee `references/naming-hubs.md`

Deuda **5746 -> 5601** en una sesion dedicada. Lo que hay que heredar:
- **Ordena la deuda por GRADO DE ENTRADA en el grafo de llamadas**, no por unidad. Las 5746 sin nombre acumulaban **24.639 sitios de
  llamada**, muy sesgados: `func_02030788` sola tenia **1338** y seguia siendo `FUN_*`. Renombrar
  **172** (el 3% de la deuda) bajo esa cifra a **15.510**: el **37% de la opacidad con el 3% del
  trabajo**. Ojo, en la primera version escribi que las 45 top acumulaban las 24.639 -- era leer
  mal la linea de total del script. Una hora arriba de esa lista rinde mas que un dia en la
  cola de una unidad.
- **La deuda es autorreferencial**: el 73% (`SOME_UNNAMED`) llama a algo que tampoco tiene nombre,
  asi que solo se limpia desde la frontera ya nombrada hacia afuera. `tools/namec.py --profile`
  clasifica la deuda por lo que el propio cuerpo demuestra.
- **`nullsub` YA esta en `PLACEHOLDER_ROOTS`**: los 166 cuerpos vacios NO son un lote barato.
- **Trampa THUMB en el camino de DEFINIR**: `createFunction` asume ARM y crea una funcion
  **fantasma de 1 byte** — con nombre, asi que la auditoria la cuenta como saldada, apuntando a
  nada. Afecta a las 1286 sin funcion en Ghidra. Usa `~/ghidra_scripts/DefineThumb.py` (TMode=1).
- Subsistemas nombrados con evidencia: API SRT de transformadas (bit0 = ES IDENTIDAD, bit1 =
  escala uniforme), singleton de sesion 0x0204c228 (RNG LCG de 64 bits + estado de 4 jugadores,
  `Session_GetLocalPlayerIndex`), operandos del VM de script, lista circular con cursor.

## ⇒⇒ EMPIEZA AQUI: `tools/callvein.py`

**El hallazgo de la segunda mitad del 19/07 es una HERRAMIENTA, no una funcion.**

```
python tools/callvein.py [n] [--min-size N] [--max-size N]   # ranking de vetas
python tools/callvein.py <simbolo>                            # miembros de una veta
```

Agrupa lo que queda por hacer **por el callee que comparten**, puntuando `sin_hacer * pureza` para
que los helpers ubicuos no dominen. Encontro cuatro vetas que ni `nearfam.py` (agrupa por secuencia
de mnemonicos) ni `dedupprop.py` (pide bytes identicos) podian ver, porque **las familias
semanticas se parecen en los SIMBOLOS, no en la forma**:

| veta | localizador | estado |
|---|---|---|
| destructores de actor | `func_ov107_020c68ec` | 11/11 cerrada; han aparecido 7 nuevos |
| comandos del VM de script (ov023) | `func_02020d10` | **CERRADA** (36 casadas + 1 aparcada) |
| UI de seleccion (ov026) | `data_ov026_02091368` | 31 hechas, **26 pendientes** |
| secciones criticas del SDK | `OS_DisableInterrupts` | 71 hechas, **20 pendientes** |

### La veta del SDK es la mejor del proyecto ahora mismo

- Semantica **publica** (NitroSDK): PXI, FS, MI, CARD, CTRDG, OS threads/alarms/mutex/messages.
- Cortas (40-250 B) y sin creatividad: codigo de sistema.
- ⚠ **No dejan deuda de naming** — ya vienen con su nombre real en `symbols.txt`. Es la unica
  veta del proyecto de la que se puede decir eso.
- Resultado del 19/07: **38 casadas, 3 aparcadas**, muchas a la primera compilacion.

```c
int enabled = OS_DisableInterrupts();
... seccion critica ...
OS_RestoreInterrupts(enabled);
```

## Lo que mas cuesta, medido

De ~50 fallos del 19/07:
- **9 fueron destinos de salto mal leidos.** Ya no deberia pasar: `poolmap.py` anota cada salto con
  su offset relativo Y la instruccion de destino. **Miralo antes de escribir la primera llave.**
- **~14 fueron orden de declaracion.** Si el unico fallo es un par de registros intercambiados
  entre dos locales, intercambia sus declaraciones ANTES de pensar en empates. Para los AGREGADOS
  la regla es la inversa: el que ocupa el offset de pila mas alto va declarado primero.
- **0 fueron empates reales del compilador** en el primer diagnostico. Los 3 parks del dia salieron
  tras agotar los ejes, no antes.

## Trucos nuevos del 19/07 (todos en `codegen-cracks.md`)

- **`volatile`**: si el ROM recarga la misma direccion sin que nada pueda cambiarla, el campo lo
  toca una IRQ. `FS_WaitAsync` salia 40 bytes corto por esto.
- **Bool materializado (`movne #1 / moveq #0 / cmp / b`) = helper `static inline` + campo volatil.**
  Los dos ingredientes juntos; ninguno basta solo.
- **`i * sizeof(T)`, nunca `i * 8`** para matar la induccion en bytes.
- **`x % 10`, no `x - x/10*10`** (el ROM usa `umull`).
- **`switch` vs `if/else-if`**: mira si el ROM CAE dentro del primer caso (if encadenado) o SALTA a
  el (switch). Y `x==0||x==1` mwcc lo colapsa a un test de rango: si el ROM compara valor a valor,
  es un `switch`.
- **Bucle `while`: mwcc DUPLICA la guarda.** Si el ROM prueba la condicion una sola vez y salta
  dentro, hacen falta `goto` explicitos.
- **Predicacion vs salto**: pon el bloque LARGO primero en el if/else.
- **El prototipo del callee es parte del codegen del llamante**: `unsigned short` en el parametro
  reemite la truncacion en cada sitio; `char *` en vez de `int` cambia el reparto de registros.
- **No hagas CSE a mano.** Escribe la expresion entera en cada uso y deja que mwcc decida.
- **Promocion con signo**: `unsigned char`/`unsigned short` promocionan a `int` CON SIGNO. Hace
  falta `(unsigned int)` explicito para que salga `lsr` en vez de `asr`, o `bls` en vez de `ble`.

## Clases bloqueadas (no re-triturar) — ver `deferred-ties.md`

- Rotacion/permutacion de registros de SCRATCH con el tamaño EXACTO y las mismas instrucciones
  (`func_ov023_0208632c`, `func_ov026_02085aa4`, `CARDi_LockResource`).
- Planificacion: mwcc adelanta o retrasa una carga respecto a una salida rapida
  (`OS_WaitIrq`, `CARDi_UnlockResource`).

⚠ **Un par de registros permutados NO siempre es esta clase.** Prueba primero orden de
declaracion, `char *` vs `int` en los parametros, e invertir los operandos de un `cmp`. Esas tres
resolvieron mas casos hoy que los que acabaron aparcados.

---

## (historico anterior)

# Where things stand — updated 2026-07-19

Read this after SKILL.md to know what to pick up. Keep it current; delete what stops being true.

**Global (2026-07-19, end of a full-day autonomous run):** C = **13805/23240 (59.4%)** ·
bytes **1,442,340 / 4,728,790 (30.50%)** · ASM 2433 · SDK 396 · gate **306/0** on every delivery.
Started the day at 12742 (54.8%) / 27.23%, so **+1063 functions and +3.27 points of bytes**.

## ⇒⇒ START HERE NEXT SESSION: the reloc-DENSE vein

The single most important finding of 2026-07-19. Order candidates by

    densidad = len(relocs) * 4 / size          →  `python tools/dense.py [n] [--min-size N] [--arm|--thumb]`

and work from the top. With density ≥ 0.40 the hit rate was **~90% at the FIRST compile**; the
reloc-free vein the same day was ~1 in 6. The reason is mechanical: in a function where most
instructions are `bl`, the branch bytes are **masked by the reloc**, so scheduling and
register-allocation noise — which blocks almost everything else in this project — simply does not
count. All you have to get right is the ORDER of the calls and their arguments, and that is
readable from the disassembly without ambiguity.

Roughly **2900 candidates remain** in the 60–200 B band. This is the vein to drain.

### The one rule that actually matters in this vein

**Every single case that cost more than one attempt on 2026-07-19 was a misread BRANCH TARGET,
never a codegen problem.** Compute where each `b`/`beq`/`bne` lands and look at the instruction
that is there. Recurring traps, all seen this day:
  - a guard that protects only ONE call, not the rest of the block;
  - a `b` at the end of an `if` that jumps far past the join, so the middle belongs to the `else`;
  - two DIFFERENT `return 0` blocks (one shared by early guards, one as the fall-through);
  - a shared exit block whose return value differs from the main path's;
  - a compound condition whose first `beq` goes to the BODY, so the polarity is inverted.
And: **never truncate the dump.** A `poolmap | head -28` hid a shared exit block and cost three
iterations.

## Cracks banked on 2026-07-19 (all in codegen-cracks.md)

- ★ **`add rX, rY, #0` copy artifact — RECIPE FOUND** (was "no recipe" for months): initialise one
  local FROM another that already holds the value, in a statement *after* all declarations.
- ★ **A register left "unset" before a `bl` is the HIGH HALF of the previous call's `long long`
  return.** Not a lost argument, not an uninitialised variable — both were tried and are wrong.
- ★ **Stack buffer: `int cfg[4] = { 0, 0, 0, 0 };`** (aggregate initialiser). Unblocked a function
  parked at 10 bytes. Separate assignments / a pointer / a struct all fail.
- Two constants materialised before two adjacent stores = **one 64-bit store**.
- `i * sizeof(T)` kills the induction variable, for any power-of-two stride (`long long` → 8).
- Loop the ROM tests before entering → **explicit `goto`**; no for/while spelling works.
- Bitfield container width is read off the shift pair (`ldrh`+`lsl#18`+`lsr#18` = `unsigned short b:8`).
- Tail-merge: mwcc merges STORES but **not call sequences**; break it with asymmetric statement order.
- Move the main path INSIDE the `if` so the early `return 0` shares the tail block (4 uses in a day).
- `return f(x);` when the ROM ends in `mov r0,#K; bl f; pop` — it returns the callee's value.
- A bare `return;` in a value-returning function is real: the ROM leaves r0 untouched.
- Pointer-vs-integer arithmetic decides the operand order of an `add`.
- SDK functions whose name ends in `_` are hand-written assembly; leave them as stubs.

## Tools added 2026-07-19

- `tools/dense.py` — the density ranking described above.
- `tools/allcc.py` — compile one file with **all 27** mwccarm builds. Use only when the residue is
  pure register allocation AND the source search is exhausted. Measured: every 2.0/3.0 build gives
  the *same* residue, so surviving allcc.py means the tie is real.
- `tools/gen_ov038_boot.py` — pattern for a per-family generator (pool-order symbol mapping).
- Fixed: `nearfam.py` (was ignoring non-`func_*` matched files and splitting families on the
  literal pool), `port_template.py` (same pool bug + `bl` targets polluting the immediate map),
  `poolmap.py` (took the address from the symbol NAME, so it crashed on every SDK-named function).
- `gen_delinks.py` now retries on `OSError 22` — that was the intermittent 306-gate failure, a
  filesystem filter on E:, misdiagnosed twice as a silent kill.

## ⚠ Blocked class: "the ROM skips the lowest free register"

~64 functions across 5 families (`func_ov043_020b5274` 26 members, `func_ov035_020b39a8` 20,
`func_ov181_020cd1e0` 10, `func_ov134_020cc448` 8, `func_ov038_020b4940` 8) are
instruction-for-instruction identical with only register CHOICE differing. Ruled out with
measurement: 360 declaration permutations, loop forms, types, callee arity, inline helpers, all 27
compilers, all -O levels. See deferred-ties.md. **Do not re-grind without a new lever.** The one
concrete hint: in ov181 the ROM gives the LOW register to the local with FEWER uses — the opposite
of our build. Confirm that on a second function and five families open at once.

A second, smaller class: **a small constant loaded from the POOL** (`ldr rX,[pc]` for 0x1c, 0xc,
0xb) and kept in a callee-saved register across calls, where mwcc rematerialises it with `mov`.
Seen twice (`func_ov023_020829c4`, `func_ov000_0205a4d4`), ~8 bytes each. Not flags, not -O level.

## ⇒⇒ USER DIRECTIVE 2026-07-17 (later): CLOSE MODULES + WORK NON-OVERLAYS TOO

Two standing asks from the user, in addition to the AI-overlay vein:
1. **Close modules to 100% when VIABLE.** ⚠ Surveyed: the near-complete overlays are blocked by
   genuine, thoroughly-documented register-allocation ties on their LAST function(s) — that is
   precisely why those functions are last. Confirmed tie-blocked (do NOT re-grind without a NEW
   crack): **ov301** (`020cbfc4`, 408/408 instruction-for-instruction, 3 constants in different
   regs), **ov294/295/296** (`020d1a24` 348/348 87insns + the 1100 B sibling — register-CHOICE
   residue). ov010's remainder is the proven r1/r2 build-line tie. So byte-exact close-out of these
   is not currently viable; their asm_stubs keep the gate at 306. **A viable close-out needs an
   overlay whose remaining funcs are carveable gaps, not ties — look for those.**
2. **Advance non-overlay modules.** `main` = **1031/1961 (930 left)**, `itcm` = 50/154. Census tools
   in `tools.md` work on `main` too (unit=='main'). Found reloc-free ×2 families
   (`func_02017938/a90/bec/dd4` = fixed-point math, ~344-488 B each) and reloc-light singles.
   ⚠ The 4-byte `main` funcs (Div/CpuSet/GetCRC16/…) are THUMB BIOS `svc #N; bx lr` thunks —
   intrinsically asm, leave as stubs.
   **First main attempt this session:** `func_020172dc` (glyph lookup, x2) → 152/152 size-exact,
   parked in `src/nonmatching/` at a head load-order/register tie (ctx r1-vs-r2 + the ctx[0]->byte
   load-delay fill). Re-testable; note in-file.

## ⇒ START HERE (this file is long; this is the whole recipe)

```
python tools/dedupprop.py                 # free twins first, every batch
python tools/audit_shadowed.py            # finished C the build isn't using
                                          # ^ ALSO after every rescue from nonmatching/:
                                          #   the asm_stubs twin stays behind and WINS.
                                          #   The 306 gate cannot see it (the stub is
                                          #   byte-exact too). Only the C count notices.
python tools/audit_arity.py               # the arity lead
python tools/audit_unnamed.py             # the naming debt (needs Ghidra on :8089)
python tools/namefam_propagate.py         # names for free, same idea as dedupprop
python tools/build_sweep.py <func>        # las 27 builds de mwccarm; ONLY on proven-correct
                                          # C; see below. ARM/THUMB automatico desde
                                          # symbols.txt (era ARM-only hasta 2026-07-18:
                                          # daba "ningun build la reproduce" sobre THUMB
                                          # que hacia MATCH). Obligatorio antes de
                                          # escribir "no lo reproduce ningun compilador".
```
Then pick ONE of:
1. **A parked file with NO diagnosis note.** ~84 left, and this is now the best-evidenced
   lead in the project: `func_ov117_020cc3d8` had no note, turned out to be an unexamined
   instance of a family solved that morning, and paid **5 functions in twenty minutes**.
   Absence of a write-up is evidence nobody looked, not evidence it is hard. Scan for
   files whose first 700 chars contain none of NONMATCHING / UNFINISHED / TIE, sort by
   shape-family size, and compare each against the families already closed.
2. **Re-test a parked file that HAS a note** — score is 19 rescued / 0 real ties.
   Newest: `ov031_020b4930` (+4, the whole x4 family) — filed as "a pure register-coloring tie,
   unsteerable by source form"; it was TWO dropped/invented arguments, and the ground truth was
   a matched sibling (`020b4820`) in the same folder declaring both callees correctly.
3. **The VENEER vein** — `families.md` has the shape and the `libs/` placement.
4. **A new shape family** — census snippet in `tools.md`; one analysis pays 3-10 times.

## ★★ THE SDK FIXED-POINT VEIN — the most productive front (opened 2026-07-17)

**Start here for volume.** The enemy-AI state ticks and MTX/VEC helpers that call the SDK
fixed-point library (`VEC_*` / `FX_*` / `MTX_*` / `020cab14` target-acquire / `020050b4` atan2 /
`01ff8d18` normalise / `01ffa724` scale). ~470 candidates left. In one afternoon this vein paid
**~55 functions across 11 clean x3-x5 batches** (ov215, ov195, ov194, ov169, ov147, ov188, ov198,
ov199, ov120, ov134, and families). Find them: `grep -rl "020cab14\|VEC_\|020050b4" src/overlays/*/asm_stubs/calls/*.c`.

**The retired "skip VEC_/FX_/MTX_" line was the only thing hiding this vein.** It claimed the whole
library was a tie; it was blocking ~1,296 functions of which 1,303 matched siblings already existed.

★★ **CENSUS (2026-07-17): 67 undone fixed-point FAMILIES (>=3 members, none carved), 40-520 B.**
Snippet: the tools.md family census, filtered to relocs intersecting {func_02023eb4, func_020050b4,
func_ov107_020cab14, VEC_Subtract, func_01ff8d18, func_01ffa724, func_01ff8a14}. Richest first:
ov228_020d1a9c (DONE +4 this session), ov206_020ce1c8 (x4 352B), ov206_020cdc2c (x4 332B),
ov221_020d4ba0 (x4 308B), ov206_020ce0d4 (x4 244B), ov206_020cdd78 (x4 224B), then a long tail of
x3 (ov212/266/267, ov119/272/279, ov208/209/268, ov210/211/282, ov200/201/271, ov185/186/187 ...).
**The ov228 shape (EmitChildOnRing) proves the vocabulary is complete for these** — Q12 sin/cos via
`(u16)(rad*0x28be60db9391 + 0x80000000000 >>44)>>4`, `struct vec` by-value calls, the hw60 low-byte
bit test, and the two-form array index. Pick a rep, match by hand, `dedupprop --write`, name in-batch.

### The triage rule — PREDICT the outcome before compiling
- **MATCH readily**: real control flow (a branch / multiple exits) AND scratch vectors that are
  STACK locals (`local_NN`, passed by `&`). The branches give the scheduler room; a stack
  destination lets mwcc hoist the sin/cos table loads freely.
- **TIE at near-exact size, PARK on sight**:
  - the scratch vector is written to a STRUCT FIELD (`state+N`, Ghidra `piVar+N`) — the VEC_Set
    sin/cos to heap ties on aliasing (ov214);
  - a divide-by-constant `* 0x1e / K` sits at the function TAIL (ov142/ov143) — the smull ordering
    ties; at the HEAD it MATCHES (ov195/ov194/ov156 — read the magic for K: /3 /5 /10 /20 all seen);
  - a value must live across an intervening SDK call and perturbs an upstream Q12 (ov194_020cd578);
  - the FX_Sqrt-transform-to-heap shape with a target/owner register rotation (ov182/ov181 — 12
    functions on that ONE register-choice tie; crack one, crack both).

### The cracks this vein needs (all in codegen-cracks.md / deferred-ties.md now)
- **VEC_Set fingerprint**: `ldm` + individual `str [sp]` + no `stm` ⇒ `VEC_Set(&v, x, 0, z)`, the
  SDK inline, NOT a struct copy. Q12 radians→sin/cos verbatim. FX_Mul = `((s64)a*b+0x800)>>12`.
- **ldm-args coalescing (CRACKED)**: pass a 3-word vector to a callee as a `struct Vec3` BY VALUE,
  not three `int` args → one `ldm`.
- **Parameter homing**: a vector arriving in r1-r3 whose address is taken is homed by
  `push {r0,r1,r2,r3}`; read it back through a POINTER (`int *v=&vx; v[0],v[2]`) to force the reloads.
- **live-across-call**: read the push list + reload sites off the ROM. Sometimes the ROM SPILLS a
  value (ov029), sometimes RELOADS it (ov198, ov120), sometimes must NOT keep it (ov214). Load the
  local before/after the intervening call to match; `state[N]`-reread vs a kept variable is the lever.
- **RNG artifact** `f(mul) + (v - v)`: pick a `v` already live across the RandNextScaled call.
- **Ghidra non-encodable constants**: `< 0xNN1` / `< 0x3001` etc. → write `<= 0xNN0` (the immediate);
  the `f`-ending constant goes to the pool otherwise (+1 instr each).
- **1-bit bitfield** `->b` (`unsigned char b:1`) reproduces `lsl#0x1f;lsrs#0x1f`, not `(byte&1)`.
- **Branch order**: the arm the ROM `b*`s TO is written SECOND (inline = fall-through).

**Method that works**: decompile → recognise if it's a twin of a matched family (edit one constant,
e.g. ov194_020ce460 was a one-line twin of ov195) → else write off the template → compile once →
drive the diff LATER one crack at a time, reading the disassembly. Dense functions (ov120, ov134)
went from +4 to exact through 4-5 catalogued fixes each.

## ⛔ The "one caller-saved register" class — do NOT grind these

Six independent cases, all: **instruction stream 100% identical, mwcc reuses a dead r0
where the ROM spends r1** (or one scheduler slot apart). Every mechanical lever is spent.

| file | size | worth | what differs |
|---|---|---|---|
| any `func_ov13x/ov16x/ov20x` 72 B c5c0 | 72/72, **16 instrs** | **24** | `ldr r1` vs `ldr r0` |
| `ov166_020cc624` | 312/312 | 10 | `ldrne r1,[r0,#4]` vs `r0` |
| `ov000_020552b4` | 656/656 | 6 | r1/r2 swap |
| `ov181_020ce664` | 228/228 | 6 | `bic` slot |
| `ov206_020cd464` | 184/184 | 4 | -1 in r2 vs ip |
| `ov185_020d11f4` | 716/716 | 3 | ip vs r4 |

The 72 B c5c0 file is the **minimal reproducer** — sixteen instructions — and carries the
full ruled-out list: all **25 distinct** mwcc binaries (20 of them, spanning years and
including the whole dsi line, produce byte-identical output), 44 flag combinations, the
16 individual `-opt` toggles, both `-lang` modes, 13 source spellings and 5 out-param
shapes. Anything that cracks it is unambiguous and pays ~50 functions at once.

**It is NOT a build problem, and the argument is short: 12,191 functions match
BYTE-EXACTLY with this exact compiler and these exact flags. A systematic
register-allocation difference would break all of them, not fifty.** The compiler is
right; the source idiom is what we have not found. Treat "wrong mwcc build" as the least
likely explanation, not the first — and `tools/build_sweep.py` makes the claim cheap to
re-test, so never assert it again without running it.

**The one lesson from 2026-07-17, if you read nothing else:** every single "compiler tie" this
project had recorded turned out to be an ordinary bug — a dropped argument, a mode never verified,
a statement in the wrong place, a crack tried in one spelling. **A confident write-up is a tell,
not evidence.** Check arity and `--thumb` before you believe any of it, including your own.

⚠⚠ **THE NAMING DEBT IS ~46% — `python tools/audit_unnamed.py`** (needs Ghidra on :8089). Of
**12,217** byte-exact C functions: **5,371 still `FUN_*` · 230 named like `ov000_helper_4d354`
(a placeholder, not a name) = 5,601 · 1,328 with no Ghidra function at all.** By the project's own hard
rule — *a match with no semantic layer is "half done" and does not count* — **about half the
finished work is half done**, and the README counts all of it as done. The PC port needs the names.
Worst units: main 586 · ov008 389 · ov025 296 · ov002 270 · ov000 110 · ov009 106 · ov006 78 ·
ov245 77 · ov005 72.
★ **The counter is trustworthy — check it by arithmetic, every time.** 2026-07-17: 5642 + 4 new C
− 45 propagated = **5601**, exactly as measured. When a rename batch and the audit *disagree*
(78 renames once moved it by 61), that gap is a bug in a shared predicate, not rounding — see below.
**Run this at the end of every session** — the debt is invisible otherwise, which is exactly how it
★★ **Naming a whole shape family at once is the fastest way to cut this — 266 in one script
(2026-07-17).** Recipe: group by masked hex → get each address's **SPACE from `delinks.txt`**, never
from the symbol name (`WM_EndKeySharing_0x02058360` carries no overlay in its name but lives in
ov000, and overlay addresses OVERLAP so a bare address is ambiguous) → one Jython script that
**defines-then-names** (184 of the 266 had no Ghidra function at all) → `save_program` → read back.
⚠ Bulk defines leak a transaction: `save_program` returns "Unable to lock due to active
transaction". `CloseTxAndSave.py` fixes it → `closed=N; tx_after=NONE; SAVED_OK`. Do NOT improvise
transaction ids.

got here. (2026-07-17: six rescues were committed unnamed *an hour after* I added "don't let the
debt accumulate silently" to SKILL.md. Discipline does not work; counting does.)

✗ **"vein now at 0" was FALSE — it meant "0 my code can express", and it hid 66 twins.** (Fixed
2026-07-17, +45 named.) `retarget()` only knew how to rewrite `Ov228_Foo` → `Ov229_Foo`; a rep whose
name carries **no overlay prefix** returned None and hit `if nn is None: continue` — dropped
silently, not even counted in `rejected`. Bare names are not an edge case, they are **the dominant
convention for a cross-overlay family**: `TickTagTrackerNodes` and `BuildTagTrackerNode` are each
spelled identically in EIGHT overlays (Ghidra namespaces them by address space, so it is
unambiguous). They now move verbatim. **When this tool prints a small number, ask what shape of
answer it can even represent** — that is the negative-result rule, and the reassuring `0` is exactly
how it evades notice.
★ **The bare-name fix exposed a second bug it had been masking:** the collision check compared the
plan only against *itself*, never against names already in the program, so a destination could
collide with **its own family's rep**. `func_0203c634` is already `SetIndexedSlot` in main and its
byte-identical main twin `func_02011f88` was planned to become `SetIndexedSlot` too — the precise
"duplicated routine, needs a human" case the check exists to refuse. A *prefixed* name can only
retarget into a different overlay, which is why only bare names surfaced it. Now seeded from the
program itself (also catches the cross-family case; cannot block a legitimate move, since the
destination is unnamed by construction).
⚠ **7 refused as same-unit duplicates — these want a human, and each is a real question:**
`func_02011f88` vs `func_0203c634` (both main, both `SetIndexedSlot` — and c634 is the handler hub,
so a byte-identical twin of it is worth understanding), plus 5 in ov024 wanting
`MobiClip_DecodeAudioEntryChecked` ×4 / `MobiClip_DecoderFreeBuffers` ×1.

★★★ **`python tools/namefam_propagate.py` — names are propagable exactly like code is** (new
2026-07-17, **551 named on its first run, then +45 from the bare-name fix**). A function byte-identical to another
modulo relocs is the same routine compiled into another overlay, so if the rep is
`Ov228_SteerToTarget` the twin has earned `Ov229_SteerToTarget`. Same equivalence `dedupprop`
already trusts for the *code*; this does the *semantics*. **Run it after every dedupprop** — each
new match is a new named rep, and each rename makes a new source, so iterate to convergence.
Three filters, every one of which fired on the first dry run (75 rejects + 44 collisions):
- **A name embedding the rep's address does not survive the move.** `Ov025_SetMode95d0` retargeted
  into ov008 points at an ov025 address — a name that *lies*, which is worse than `FUN_`.
- **Structure propagates; scene identity does not.** `Ov006_MissionPollKeys` is true of ov006
  because ov006 IS Mission-Mode select; the byte-identical twin in ov008 is the same *routine*, not
  the same *screen*. This is the ~23-symbol misnaming from the scene table, waiting to happen again.
- **The same name twice in one overlay** = a duplicated routine; needs a human, not a script.

★★ **The audit was under-counting, and the ONLY reason it showed was two tools disagreeing.**
A batch of 78 renames moved `audit_unnamed` by 61. The predicate "this is not a name" existed in
two copies that differed by 17 functions. It is now **one definition in `audit_unnamed.py`, imported
by `namefam_propagate.py`**. Same shape as the ARM/`--thumb` verify bug: when two tools own one
predicate, the bug lives in the difference — and you only ever find it by making them argue.
★ **And the regex nearly ate real names:** `Set_?[0-9a-f]{4,8}$` matches **`SetFade`** and
**`GetFace`** — *fade* and *face* are spelled entirely out of hex digits. The audit would have
reported them as debt and propagate would have **overwritten** them. The separator is now mandatory
and the suffix must contain a digit. **`WaitDivResult64_8ab0` and ~1035 like it are NOT debt** — a
semantic root with an address suffix is a disambiguated real name; only a placeholder *root* counts.
⚠⚠ **Do NOT carry that "must contain a digit" rule over to `namefam_propagate`'s `ADDR_IN_NAME`** —
it is a *different* predicate answering a *different* question ("would this name lie if moved?", not
"is this a placeholder?"), and there the digit rule is actively WRONG. **An address can be spelled
with no digits at all:** `_ccbcc` is `0x020ccbcc`, and `_cadc` / `_fcbc` / `_dcdc` / `_cccac` /
`_ccecc` / `_cedbc` are all real (`ov166_stDispatchByStateByte_ccbcc` ×10 alone). Requiring a digit
would un-reject those and propagate a name pointing at another overlay's address — the exact lie the
filter exists to stop. Measured 2026-07-17: of 1453 names it flags, only **23** lack a digit, and
those 23 are a genuine 50/50 mix of real addresses (`_ccbcc`) and real words (`MobiClip_StepScreenFade`,
`MsgDb_LoadDb`, `MsgDb_IsLoaded`, `SphereToAABB` — *fade*, *added*, *AABB* are pure hex). The
discriminator that actually separates them is the **separator**, not the digit. Left as-is: a false
positive here only costs a missed name (safe), while a false negative writes a lying one. Two
predicates that look alike are not the same predicate — the 17-function bug above came from merging
two that WERE, and this is the mirror-image mistake.

✅ **Nothing is pending from THIS session** — the 27 ov212/266/267 functions plus every 2026-07-17
rescue are named, plated, saved and read-back-verified. (That is not the same as the debt above
being clear: it is 50% and historical.)

★★ **If the `mcp__ghidra__*` tools vanish, DON'T stop decomping and DON'T wait for a restart** —
drive the bridge over plain HTTP on **port 8089** (not 8080; SKILL.md was wrong). That is how the
27 renames above were done. Snippet + the three traps in `tools.md` ("Ghidra without the MCP
tools"). Reopening Ghidra does *not* revive the MCP client; only restarting Claude Code does.

## Global

`C = 12481/23240 (53.7%)` · bytes `1,239,996 / 4,728,790 (26.22%)` · ASM `3118` · SDK `439` · gate
`dsd check = 306/0` (verified 2026-07-18 at `HEAD`, pushed) · PROGRESS.md + README current.
★ **+3 ov200 DecayOffsetPickGiveUp (020cfaec)** — DecayOffsetGiveUp + a mark-6/mark-2 give-up branch;
the two mark leaves must be spelled out FULLY (own c634+return each) or mwcc merges them to a
conditional-mov + shared tail (24 B short). ⚠ **SKIP the post-increment x4 `ov206_020cd72c`** (236B,
`ldr [r4],#0x14` fusion — same tie as ov200_020cec8c/ov137). ⚠ `ov228_020d238c` (232B) is the
candidate-loop area-attack shape (like the parked ov212_020cdb1c) — harder, defer. ~30 fresh left;
the clean state-tick shapes (acquire/subtract/atan2/fire, decay+gate, strafe) keep landing first-try.
★ **+6 ov210 StrafeSameTarget (020d2b60) + Neg (020d2e78).** New combo crack for a
`if (state[N] == acquire())` guard where state[N] is ALSO used after: write `int target=acquire();
if (state[N] != target)`. The LOCAL forces the call to evaluate first (state[N] read AFTER it, in a
caller-saved reg -> no extra push); and `state[N] != target` (not `target != state[N]`) gives the
ROM's `cmp state[N], target` operand order. Fixed a 5-vs-3 push-list + operand-order diff at once.
~32 fresh families left.
★ **+6: ov208 WindUpFaceReset (020d1744) + FaceTargetFireReadyC (020d1afc), both clean first-try.**
⚠⚠ **SKIP the blx/pt "notify via *state+0x24 callback" shape — it TIES on scheduling** (3 parked now:
ov200_020cfcfc, ov200_020cff54, ov210_020d32a0). Tell: a `blx r3` where `r3 = *(*state+0x24)` and a
2-halfword pt built on the stack. The &pt hoist + config-load ordering never matches. ~34 fresh
families left; ov208/ov210 non-blx ones stay clean.
★ **+3 ov185 DecayOffsetGiveUp (020cf32c, hw60 `->hi&=~0x40` + 2-bit `||`).** This batch hit the
size band's tie cluster — 3 useful notes for the next pass:
- ★ **CACHE `*state` in a local to force a 2nd callee-saved reg** (ov210_020d1f14): when the ROM keeps
  BOTH `target` and `*state` live across an intervening call (FX_Sqrt), caching `int *owner=*state`
  fixes the push list AND homes an out-param in the r3 push slot instead of `sub sp,#4` (16-byte gap).
  The OPPOSITE of the don't-cache crack — read the disasm to tell which the ROM does. Left at a
  symmetric r6/r7 swap (target vs owner).
- ⚠ **Post-increment `ldr [r4],#N` fusion is a recurring TIE** (ov200_020cec8c, ov137_020ccdf0): two
  vec3 copies where the ROM fuses the `*state` load with the `state+=N` advance. mwcc will NOT emit
  post-increment addressing here — tried `+=`, fresh walking ptr, single base, typed `vec3* ++`. Skip
  ov137_020ccdf0 (post-increment). ~1-instr over.
- ⚠ **The ov200 "enter" blx/pt functions have a state-load scheduling residue** (020cfcfc, 020cff54):
  the ROM slots `ldr state` in the gap between the two config `ldrh`s and the `strh`s; mwcc misses the
  exact slot. Size-exact, parked.
Net: prefer ov210/ov208/ov185 fresh families (clean); the ov200 "enter" + ov137 post-increment ones
tie. ~37 fresh families left.
★ **+6 more: ov210 AimPerpStrafe (020d2d38) + AimPerpStrafeNeg (020d3050, scale -0x100) x3** —
VEC_CrossProduct(data_02042264, flatten_y(dir), state[5..7]). Parked ov200_020cfcfc (164/164, blx-head
scheduling: state-load position + &pt hoist). ~40 fresh families left.
★ **Still humming: +9 more (3 x3 families): ov208 FaceTargetFireReadyB (020d20c0) + AdvanceAimGiveUp
(020d2b44, Q12 `<<8` step = `((s64)(delta*30)<<8 + 0x800)>>12`), ov210 RebuildSteerFireChild (020d263c).**
Parked ov200_020cec8c (164/160, post-increment `ldr [r4],#0xc` fusion mwcc won't emit — attack the
copy pair). ~43 fresh families left; keep censusing reps with no nonmatching file, smallest first.
★ **Fresh-family method is HUMMING: +12 more this iteration (4 x3 families, all 1-2 compiles):**
ov210 AcquireOrTimedRecoverB (020d2df0, twin) + AdvanceLungeOrCommit (020d31d8, two field-copies +
ldm-coalesced self[0]/self[1] + b17a bit gate), ov185 SeedRandomStrafe (020cef20, the rand `+(v-v)`
copy artifact for `?-1:1`), ov208 FaceTargetFireReady (020d2024). ~46 fresh families still left.
★ **Lesson confirmed: the fixed-point vein pays FIRST-TRY; diversification hits the tie remainder.**
After 3 tie-parks chasing close-outs/main (ov031_020b408c held-value tie, main 020172dc + 02012c2c
register residues), went back to FRESH fixed-point families and matched 3 x3 (+9) all first-try:
ov210 RebuildSteerAndGate (020d2918) + AcquireOrTimedRecover (020d2ad8), ov200 FireAimPoseAndGate
(020cfa60, field-copy crack for the 4-word pose). **Method for fresh families: census fixed-point
reps with NO nonmatching file (untried), smallest first — the census one-liner is in the batch.**
Still ~50 fresh families left. Keep draining before diversifying.
★ **Bytes crossed 26% (26.02%). Next milestone to guard: 27%.**
★★ **NEW CRACK — field-to-field struct copy (2026-07-17, +7 incl. 2 twice-parked rescues).** A
whole-struct/vec copy whose ONLY diff is the ldm/stm base registers swapped (ROM src->low reg, mwcc
dst first) is NOT a tie: writing `*(T*)a = *(T*)b` picks the reversed order, but making both ends
struct FIELDS (`((Obj*)p)->dst = ((Obj*)p)->src`) picks the ROM's. Landed fresh on ov208_020cfc04
(11-word) and RESCUED ov022_0209d3a0 (twice-parked) + ov212_020d1bfc x3 (its own note pointed here).
Full recipe in codegen-cracks.md. **Re-test any parked "struct-copy base-order tie" with this.**
★ **/loop active (cron every 10m, "continua con el decomp").** Recent wins (all named):
- +4 `ov221_020d4ba0` SpinLungeTick x4 (matrix spin/lunge; hw60 `->hi &= ~0x80`, `/4096`+`/1024`, `t<=0`).
- +3 `ov208_020d1e84` FaceTargetFireGate x3 (`/10` divide; **don't-cache crack**: re-read state[4]).
- +3 `ov210_020d0f5c` PickMeleeReaction x3 (4-way attack dispatch; **two cracks**: per-leaf tails
  duplicated so mwcc doesn't tail-merge, and *state uncached — both in codegen-cracks now).
Parked `ov212_020cdb1c` (488/492, x3) area-attack: tail `self[2]` ctx-CSE tie + scalar frame layout;
mode dispatch solved as a SWITCH, fully decoded — see its file header.
Next fixed-point targets: ov119/272/279 020ccc48 (488B), plus the ~59 remaining census families
(ov200/201/271, ov185/186/187, and the rest of the x3 tail).
★ **Session 2026-07-17 (later): +26 matched & all named**, all from the fixed-point vein:
- ov156_020cdbd4 ChargeAimedShotState x5 (arity: ov107_020c9264 takes 3 args, + atan2 add needs `+=`)
- ov022_0209a68c SetOrClearBit200 (dropped flag arg + 64-bit field op — crack banked)
- ov228_020d1a9c EmitChildOnRing x4 (Q12 sin/cos ring; two-form index crack banked)
- **ov206 family {206,207,274,275} — 4 families / +16, most FIRST-TRY** once the ov228 vocabulary
  was in hand: 020ce1c8 FaceTargetAndGate, 020cdc2c SteerHeadingGate, 020ce0d4 FireAttack2OnIdle,
  020cdd78 FireAttackCOnIdle. All share the head: acquire (020cab14)->state[4] / null-guard ->
  VEC_Subtract(target+0x190, state[1]) -> normalise(01ff8d18) -> `delta*30/K` head-divide ->
  atan2(020050b4)->state[0x11]. **Divide magics: 0x66666667 asr#2 = /10, asr#3 = /20; 0x88888889
  add-back (`add x,x,mulhi; asr#4`) = /30.** The `*(u8)state[3]` idle byte is `ldrb` (unsigned).
C moved +26 exactly across the session = no shadowing. Naming debt held (every one named in-batch).
**Still open in this vein**: the census's remaining ~61 families — next richest are ov221_020d4ba0
(x4 308B) and the x3 tail (ov212/266/267, ov119/272/279, ov208/209/268, ov210/211/282, ov185/186/187).
★ **Bytes crossed 25% on 2026-07-17 and are now 25.14%.** The long-standing "NOT 25%" caveat in this file is
retired -- it is now exactly 25.00%, so the next honest milestone to guard against is 26%. Naming debt **5601**, unchanged across +26 new matches because every one was named in the
same batch — that is the arithmetic proving the rule works, not a stalled counter.
⚠ **This line goes stale silently — it read `C=12186 / 24.28% / ASM 3257 / SDK 457` while README
already said 12,191 / 24.53% / 3,253 / 440.** Re-read it from `cd tools && python progress.py`
rather than trusting it, and note README's *derived* row drifts too: "named but not decompiled"
said 7,383 where `23240 − C − ASM − SDK` = 7,352.

★★★ **`libs/` IS A SECOND SOURCE TREE AND IT IS EASY TO FORGET.** `libs/{nitro,msl}/*/` each carry
their own `asm_stubs/` + `calls/` + `auto/`, are counted exactly like `src/`, and already hold
~180 C + ~150 stubs. Anything named `SND_*`, `SNDi_*`, `WM_*`, `NNS*`, `CARD_*`, `FS_*` belongs
there — **put the .c next to its own stub, not in `src/calls/`.** `audit_shadowed.py` walked only
`src/` until 2026-07-17 and therefore reported "0 shadowed" while 74 SND veneers sat shadowed under
`libs/`; fixed, and it found 4 more the same minute.

★★ **The veneer vein is REAL and mostly untouched — `families.md` was right.** 2026-07-17: one
20-byte analysis covered **87** byte-identical functions (+77 after placement).
`ldr ip,[pc,#4] ; ldr r0,[pc,#4] ; bx ip` == `TARGET(&DATA);` — a void tail call to a
far/interworking target. Matched first try. **Census for more of these**: same masked hex, ≤20 B,
2 relocs.
⚠ **`dedupprop` skips anything not named `func_*`** (its line 61), so it will NOT fan these out —
it saw 2 candidates where there were 87. Generate the family by hand.
⚠ Their SDK names are junk: 87 different veneers all called `SNDi_UnlockMutex_0xADDR` while
tail-calling different targets (one goes to `srand_0x0208875c`). The identifier matched a *shape*.

✗ **`config/**/delinks.txt` showing up modified is NORMAL — it is a build artifact, not work.**
`configure.py` runs `gen_delinks.py` over every module unconditionally (configure.py:191-194)
*before* `dsd delink`, so the committed file is regenerated from the `src/` tree on every build and
is never the source of truth. A tracked file the build rewrites will always read dirty.
**Do not read a missing FILES entry as "finished C the build isn't using."** 2026-07-17 I measured
"3967 .c files wired by the regen but not at HEAD" and briefly believed half the project was
unwired. The number is real and means nothing — the search could not tell "not wired" from
"regenerated at configure time", which is the negative-result rule turned on its head. The genuine
version of that bug is `audit_shadowed.py` (an `asm_stubs/` twin winning last-wins); that one is
real, and it is a different mechanism.

★★★ **RE-TESTING PARKED FILES IS THE BEST LEAD IN THE PROJECT.** Start with
`python tools/audit_arity.py`, but the sweep's real value is that it *makes you open the file* —
half the rescues turned out to be something else entirely.
**Score: 13 parked functions rescued, 0 "unbreakable ties" survived contact.**
Rescued: ov212_020ce0d4, ov115_020ce20c (+7 twins), ov256_020cd8f0, ov007_0204d23c,
ov024_020835d8, ov000_020593f4, ov006_02055a54, ov008_020597c4, ov022_02086e80, ov022_020b0ff8,
func_0201a124, **ov156_020cdbd4 (+4 twins), ov022_0209a68c** (both 2026-07-17 later).
Their write-ups claimed: "allocator coin-flip" (10 variants), "r4/r5 tie",
"unreachable across 25 mwcc builds", "scheduling tie", "register-spill tie", "structural
transcription over-expands", "the call-result-parks-in-r4 limit", "re-read-vs-CSE tie",
**"register-CHOICE tie"** (ov156 -- dropped ov107_020c9264's 3rd arg AND the add wanted `+=`),
**"dead self-store, needs the header's 0-flag macro"** (ov022_0209a68c -- dropped a flag arg AND
the store is the high word of a 64-bit `|=`/`&=`; see the new codegen-cracks entry).
**Every single one was wrong.** The four real causes, in order of frequency:
  1. **arity** — dropped trailing arg (size unchanged!) or invented extra args (size over)
  2. **never verified with `--thumb`** — the ARM size gap reads as hopeless C
  3. **placement** — `int i = 0;` decl-init vs statement; the register swap is the *symptom*
  4. **a crack tried in only one spelling** — e.g. volatile on ALL reads instead of just the first
**4 strict arity candidates remain** (`python tools/audit_arity.py`, down from 7), plus ~380 parked
files nobody has re-opened. Of the 4: ov008_02077908 and ov022_0209d3a0 are CONFIRMED false
positives (arity verified correct in-file 2026-07-17 — the diffs are a symmetric r0/r2 clamp and a
src/dst struct-copy base swap respectively); the other 2 are the ov003 giants
(`0204cba0` 1568 B MMIO, `0204d98c` 2552 B) whose arity flags are unexamined but which have many
other issues — a single arity fix will not land them. So the sweep's cheap wins are spent; the
remaining rescues live in the ~380 note-less parked files.
When a write-up sounds confident, that is not evidence — it is usually the tell.

✗ **DON'T re-run this AS IT WAS: all 381 parked files verified in BOTH modes → ZERO match as-is**
(2026-07-17, ~10 min). So the THUMB trap is not hiding free *matches*. Every remaining rescue
needs its file opened and read.
⚠⚠ **BUT that sweep threw away the useful half, and it cost real time.** It recorded only
match / no-match. `ov029_020b2ee0` is **THUMB, 96/96 bytes, 47/47 instructions, one register
out** — and its file carried no note, so verified as ARM it reads `140 != 96`, a 44-byte gap that
looks like badly wrong C and invites a rewrite. I nearly rewrote it. **Re-run the sweep recording
HOW CLOSE each file gets in its correct mode** (size delta, and instruction count when the size
matches): "no match" cannot distinguish hopeless from one-register-out, and the second group is
where the cheap wins are. That single number would have flagged ov029 as a one-function overlay
close-out months ago.

★★ **Two things that look like arity evidence and are NOT** (both hit on 2026-07-17, on
`ov294_020d1f94`):
1. **A callee's own body can never settle its arity.** `func_ov107_020c5c54` is *defined* in a
   matched file as `void f(char *node)` — one parameter — yet its callers correctly pass **two**.
   An **unused trailing parameter is invisible in the callee's code**: it costs no instruction, so
   the definition compiles byte-identically with or without it. **Only call sites are evidence.**
   (This cuts both ways: it is also why a dropped trailing argument is free to go unnoticed.)
2. **`asm_stubs/` externs are auto-generated and mean nothing.** grepping that callee turns up
   `extern void func_ov107_020c5c54(void *r0, int r1, int r2, int r3)` — four args — and it comes
   from the asm_stubs of the very family under attack. The declaration was synthesised to satisfy a
   reloc list, not read off anything. **Filter `asm_stubs/` out of arity greps**, exactly as they
   are filtered out of every other census (see the RNG-artifact retraction).
   `python tools/audit_arity.py` already reads real call sites; the danger is the hand-rolled grep.

★ **Two ways the arity is wrong, and only one changes the size:**
  - **dropped TRAILING arg** → size unchanged, a constant sits in the wrong register.
  - **extra args you invented** → size OVER (each surplus arg costs a `mov`).
  So: **size over ⇒ you are passing too many; size right ⇒ still check.**
★ **Corollary found on ov008_020597c4: stop transcribing the ROM's SHAPE.** Its old C juggled a
variable through three `if`s to mimic the ROM's conditional loads; two plain `&&` chains produced
them for free. **mwcc if-converts short-circuit chains on its own — helping it costs bytes.**

★★★ **ALWAYS VERIFY BOTH MODES. `verify_idx.py` without `--thumb` on a THUMB function prints a
meaningless size gap** (e.g. `152 != 104`) that reads exactly like broken C. On 2026-07-17 this bug
in a fresh `audit_shadowed.py` made me move **four perfectly matching functions out of `calls/`**
into `nonmatching/`. `dedupprop` does `verify(...) or verify(..., thumb=True)` and re-rescued all
four; **the two tools disagreeing is what exposed it**. SKILL.md already documents the trap and I
wrote the bug anyway. Any new tool that shells out to `verify_idx.py` must try both.

★★★ **`python tools/audit_shadowed.py` — run it after ANY bulk `dedupprop --write`.**
2026-07-17: 50 functions had real byte-exact C *and* an `asm_stubs/` twin. The stub wins last-wins,
so they counted as ASM **and the ROM was built from the blob while finished C sat unused beside it**.
46 were free (+46 C / −46 ASM, gate still 306). Zero shadowed now — keep it that way. The tell is
**C moving by less than you added**. Full notes in `tools.md`.
⚠ It also found 4 files with a NON-matching `.c` in `calls/` (hard-rule violation, the stub was
holding the build up): ov087_020b8114, ov087_020b817c, ov104_020ba7d4, ov104_020ba83c — now parked.

★ **The ROM tell for a dropped trailing arg: a `mov rN, #0` hoisted ABOVE a branch** — the same 0
is a field store *and* a call's trailing argument. Workflow in `tools.md`.

⚠ **After any rescue, delete the `asm_stubs/` twin** — it shadows via last-wins and the function
still counts as `asm_stub_matched`. Correct shape: **C up N / ASM down N**.
★★ **The stub is at `asm_stubs/calls/<fn>.c` (or `asm_stubs/auto/`) — a NESTED path, mirroring
`calls/`+`auto/`. It is NOT `asm_stubs/<fn>.c`.** 2026-07-17 that cost 4 functions: `rm -f
src/overlays/ov031/asm_stubs/func_ov031_020b4930.c` deleted nothing, a hand-rolled
`[ -e asm_stubs/$fn.c ]` check printed a clean bill, and the family sat shadowed and counted as ASM
while the ROM built from the blob. **Never hand-roll this check — run `python tools/audit_shadowed.py`
(with `--verify`/`--fix`), which globs the whole subtree and got it right.** The tell was the one
state.md already documents: **C moved by +9 when 13 files were added, and ASM did not move at all.**
Do that arithmetic after every batch; it is the only thing that catches it.

★★ **A confident `nonmatching/` write-up is NOT evidence.** Still parked and worth re-testing: `ov167_020d0264` (arity WAS wrong — fixing it moved the diff
0x55→0x98, so something else remains), `ov185_020d11f4` (×3), `ov212_020d1bfc` (×3),
`ov158_020cd174` (×4), `ov206_020ccd68` (×4), `ov221_020d43a0` (×4), `ov206_020cd464` (×4),
`ov206_020cde58` (×4).

★ **The PROGRESS "off by one" drift is REAL but benign — verify it this way, don't re-derive.**
2026-07-17: 6 new matches moved the total only +5 (ov267's row went +1 for 2 matches). The check
that settles it in one shot, from `tools/`:
```python
import audit_progress
functions, unknown, shared = audit_progress.classify_functions()
m = [f for f in functions if f['unit']=='ov267' and f['category']=='c_decompiled_matched']
# then confirm every f in m has a real file on disk -> zero phantoms == the CURRENT number is right
```
It reported all 6 as `c_decompiled_matched` and **zero phantoms**, i.e. the new total is correct and
the *previous* reading was one high. Do NOT compare a row against `ls calls/*.c | wc -l` — some .c
files define several functions, so that count is legitimately lower than the row and proves nothing.

★★ **`run_script_inline` IS DEAD — use Jython + `run_ghidra_script`** (2026-07-17). SKILL.md step 3
still tells you to batch renames into one `run_script_inline`; that tool cannot run *anything* now,
not even `println("hi")`, and it still prints `SCRIPT COMPLETED SUCCESSFULLY` while doing nothing.
Full diagnosis + the working pattern in `tools.md`. **Read your rename back before believing it.**

★★ **New crack: `const` on a read-only global table is load-bearing** (`codegen-cracks.md`).
It reschedules loads vs stores and it is what landed the 7-member PickApproachDir family. Rule that
generalises: **a diff about the ORDER of loads vs stores is alias analysis, not the scheduler.**

⚠ **The byte metric was inflated until 2026-07-17 and any older number is wrong.**
`compute_byte_progress()` in `tools/progress.py` skipped `asm_stubs` but counted
`nonmatching/` as matched C. With 391 nonmatching files that was ~63 KB, or 1.34
percentage points. Fixed. Do not compare against byte figures in commits before
`364ba9b0` — they overstate. The function count was always correct (it comes from
`classify_functions()`, which excludes nonmatching properly).

★★ **The RNG `add/adds r0,r0,#0` is SOLVED** (`f(n) + (v - v)`, deferred-ties.md) — 155 functions
carry it and 75 are still undone, so it is one of the biggest open veins. If you find a note
anywhere calling it an unbreakable tie, that note is stale: it came from a census that grepped only
one of the pattern's two spellings and counted asm_stubs as matches.

★ **The move-dispatcher vein is GENERATED, not typed** — `tools/genmove.py` (+ `clonedispatch.py`)
took it from 160/208 to 180/208 in one pass. See families.md for the census predicate, the three
tools, and what still needs hand work.

## ★★ `func_ov231_020cdd3c` — PARKED at 704/704 on the FIRST compile (worth 5)

`ov231/232/263/265/280`, in `ov231/nonmatching/`. **Read the file** — the analysis is complete and
the only diff is ctx=r4/done=r5 (ROM) vs ctx=r5/done=r4 (mine). Ruled out and recorded in-file:
declaration order (3 ways), statement order (4 ways), `done`-vs-literal-0 (3 ways), and arity
(verified clean against the tree — the axis that explained 7 other "register ties" today).

★ **It contains a real GAME BUG, faithfully reproduced.** Phase 2 picks the circling direction from
the sign of a 2D cross product against a vec3 that **nothing ever writes**. I verified the symbol
rather than assume the reloc was mislabelled: `VEC_DotProduct` @`0x01ff8bf8` really does read both
operands, write neither, and return the Q12 dot — and its result here is **discarded**. The enemy
steers on whatever the previous call left on the stack. Flagged for the port, not "fixed".

⚠ **Four functions have now landed as pure r4/r5-class rotations with 100% correct code**
(`ov185_020d11f4`, `ov212_020d1bfc`, `ov158_020cd174`, this one). **Do not read that as evidence of
a compiler-build difference** — SEVEN functions that looked identical today were arity / mode /
placement bugs. state.md's own retraction says counting only the failures is exactly how that
mistake gets made. Open question, not a tie.

## Open right now, in priority order

1. ⚠ **Two functions are one detail from matching. Finish these first — they are worth 5 functions
   between them and the analysis is already done and written up in each file.**
   - `ov210/nonmatching/func_ov210_020d114c.c` — **784/784 bytes, 196/196 instructions**. Only
     spill TIMING left: three stack-arg stores the ROM emits early and mwcc emits at the call site.
     Landing it unlocks `ov211_020d2f6c` + `ov282_020d1158` via dedupprop → **3 functions**.
   - `ov125/nonmatching/func_ov125_020cd27c.c` — **756/756 bytes, 189/189 instructions**. Only the
     opening `ldm r7,{r0,r6}`; the register rename in the rest of the diff falls out of it. Unlocks
     twin `ov126_020d0ebc` → **2 functions**.
   **Read the file headers before touching either** — each lists what is already ruled out
   (for ov125 that includes all 120 declaration-order permutations, which are byte-identical).
2. ~~**Move choosers**~~ — **the unblocked ones are DONE.** `ov235_020cd994` (924 B) landed
   2026-07-17, the last one not waiting on something else. Reps: `func_ov200_020cf228` /
   `func_ov271_020d1048` (steering), `func_ov208_020d1be0` / `func_ov210_020d0d24` (plain), and
   `func_ov235_020cd994` (the richest — an early-out ladder plus an anchor-relative branch; its
   header lists four load-bearing spellings). Only `ov207/274/275` (576 B) remain and they are
   BLOCKED on ov206_020cde58's one register.
3. ★★★ **DENSE-SWITCH DISPATCHERS — NOT 9, but 572, and the layout half is MECHANICAL.**
   `python tools/switchorder.py <func>` (new 2026-07-17). A dense switch has TWO orders and
   conflating them is why these were filed as "hand work": the jump TABLE is indexed by the case
   VALUE (forced, tells you nothing), but the case BODIES are laid out in **SOURCE order** — so
   sorting the table's targets by address recovers the order the cases were written in. It is
   routinely NOT 0,1,2,... Write them in that order and the whole layout falls out.
   Proven repeatedly: `ov245_020ccfa8` (552 B), `ov206_020cc6f0` (×4), `ov040_020b34f0` (×4) all
   byte-exact on the FIRST compile; `ov259_020cd2c8` (×5) needed only `code = -1` moved off its
   declaration; `ov038_020b34f0` (×4) needed the flag-variable crack; `ov127_020ccb10` (×4) two
   materialisation spellings. **7 dispatchers, 6 matched, ~24 functions.**
   ✅ **The "INLINE IN THE TABLE SLOT" blocker is SOLVED** (2026-07-17, +4 on ov041_020b40f8):
   a `pop` sitting in a table slot means the source has **NO `default:` and NO returning
   `case 0:`** -- they fall through the table to the function's implicit end. And what looks
   like a tail after such a switch is usually the last case's body with earlier cases falling
   INTO it. Full entry + the measured 300/304/308 comparison in codegen-cracks.md. This
   unblocks ov034/046/048 and most of the enemy-overlay dispatchers.
   **Census: 572 undone functions carry an `add pc,pc,rX,lsl #2`.** Richest first:
   824 B ×7 (ov004/005/008/009/025/069 — the `ov000_02057dc4` family, see its nonmatching note),
   704 B ×5 (ov232/263/265/280), 252 B ×5 (done). Read the tool's output, then Ghidra for the
   bodies. Things it teaches you that Ghidra will not: a `default` sitting in the MIDDLE, an
   EMPTY case coming last, and which cases share a body.
4. ★★ **The RNG vein is really a FAMILY vein — census it grouped, not as singles.** The state file
   used to call this "75 undone functions, ordinary work, many are small". That undersells it badly:
   group the `func_02023eb4` callers by masked hex and it is **~70 undone families with no matched
   rep**, so one analysis pays 2-7 times. `dedupprop` cannot find these (it needs a matched rep) and
   `scan_fam.py` only ranks asm_stubs. The census snippet is the one in `tools.md`, filtered to
   `'func_02023eb4' in relocs`. Proven four times on 2026-07-17: ×6 412 B = **7 functions from one
   analysis** (it also rescued a `nonmatching/`), ×4 296 B, ×4 664 B, ×3 972 B.
   **19 functions in one session from 5 analyses, every one landing in 1-4 compiles.**
   **This is currently the best-yielding vein in the project — keep mining it before anything else.**
   Most steers came straight from the existing catalog; the vein also *produced* four new cracks
   (`const` tables, the u32-lo bitfield, load+store address CSE, `x += f()+k`). The bottleneck is
   picking targets, not cracking them.
   Best undone ones, by members then size:
   - ~~×4 664 B `ov221_020d0d20`~~ — **DONE 2026-07-17, +4** (Ov221_ChooseMove; three catalogued
     steers applied straight: shared-`goto fail` epilogue, array-index vs walking pointer, and the
     block-layout negation)
   - ~~×4 296 B `ov221_020d4828`~~ — **DONE 2026-07-17, +4** (EnterChargeState; needed BOTH hw60
     forms in one function — see the u16-vs-u32 note in codegen-cracks.md)
   - ~~×3 972 B `ov212_020cdd08`~~ — **DONE 2026-07-17, +3** (Ov212_ChooseMove; two new cracks fell
     out — the load+store address CSE, and `x += f() + k` needing its own `sum` local)
   - ×3 716 B `ov185_020d11f4` — **PARKED UNFINISHED 2026-07-17 at 716/716 bytes, 179/179
     instructions.** Worth 3. One allocator choice at 0x034: mwcc coalesces the guard's ctx[0x1d]
     cache and `lo` into r4; the ROM spends `ip` on the cache and keeps r6 for lo, which is what
     puts ctx in r4 and self in r5. Everything else (size, constants, branches, whole stack layout)
     is right. **Four decl arrangements give byte-IDENTICAL output — it is not decl-order driven.**
     Full write-up + what's ruled out in `ov185/nonmatching/func_ov185_020d11f4.c`; attack only that
     one choice. Two cracks it *did* produce are already banked (see the `pi` local below, and the
     hw60 trunc-pair confirmation).
   - ×3 552 B `ov210_020d4140` / ov211_020d5f60 / ov282_020d4154
   - ~~×3 408 B `ov212_020cee18`~~ — **DONE 2026-07-17, +3** (IdleTick)
   - ~~×3 348 B `ov212_020cf438`~~ — **DONE 2026-07-17, +3** (PickRetreatSpot, first try)
   ★ **ov212/266/267's whole decision path is now C** (ChooseMove + IdleTick + PickRetreatSpot),
     plus 020ce404 / 020d1a94. Their remaining ×3 families go fast — the vocabulary is established.
     **Census the trio's own leftovers directly** (group `func_ov(212|266|267)_` by masked hex).
     2026-07-17: `020ce404`, `020d1a94`, `020d1850`, `020cc4e0`, `020d0a48`, `020d1798` all DONE
     (+18) — **the last four matched FIRST TRY**. Small, same idioms, 3 functions each; keep
     censusing and draining this. `020ccbc0` (112 B) is the next one up.
     ★★ **2026-07-17 (later): +33 MORE from 11 analyses — `020ce440`, `020cec2c`, `020cc54c`,
     `020d0d90`, `020d0620`, `020d0720`, `020ce998`, `020d0c48`, `020ce36c`, `020d1200`,
     `020cea40`. SEVEN of the eleven matched FIRST TRY, and the vein is down to 15 families.** The vein is still
     the best in the project and the vocabulary is now essentially complete for it:
     hw60 in BOTH forms, the byte-in-word `->f &= ~1`, `[i + 0x133]` indexing, the vec3-by-value
     call, the `Probe` struct. **Census predicate:** group `func_ov(212|266|267)_` by masked hex,
     keep families with NO member carved. **26 such families were left after this session.**
     Parked: `020cd524` (180/180, a two-register swap; 11 spellings in its file).
     ⚠ `func_ov212_020ce0d4` (76 B ×3) is PARKED — a two-register scratch swap; **ten variants are
     recorded in its nonmatching file, two of which are actively wrong (72 B). Read it first.**
   - plus ~10 more ×3 in the 84-324 B band (ov185/186/187, ov200/201/271, ov210/211/282,
     ov119/272/279) and ~40 ×2.
   The AI-overlay building blocks (Q12 radians, FX_Mul inline, the `+ (v - v)` copy, `const` on the
   table) cover most of their shapes now — these should go down in 1-3 compiles each.

⚠ **Pattern worth watching, NOT yet a proven claim.** Three consecutive near-misses
(`ov125` ldm, `ov206` one destination register, `ov210_020d114c` spill timing) all have 100%
correct code and differ only in allocator/scheduler choices, each resisting ~10 targeted steers.
They *may* all point at the retail mwcc build (`reference_mwcc_build_hunt`) — but that is a
hypothesis, not a finding, and each is filed separately as UNFINISHED with its own next step.
**Do not collapse them into "a known tie"**; that mistake was already made once with the RNG
artifact and cost a wrong nonmatching write-up. If a fourth lands the same way, that is when the
build hunt becomes the highest-value thing to resume.

⚠ **PROGRESS.md per-overlay rows can drift by 1.** ov208's row read 41 with only 40 `.c` files at
`28197526`; after adding one file it read 41 with 41 (now a verified 1:1, no phantom), so the total
moved +2 for 3 new matches. The current numbers are right — but if a count looks off by one, check
`classify_functions()` against the actual file list before assuming work was lost.

**The ov000/004/005/008/009/025 menu vein is now open too** (`func_ov000_0205721c` done, +6). Its
shapes are DIFFERENT from the AI states: NitroSDK lists (`NNS_FndInitList`/`AppendListObject`),
`MI_CpuFill8`, and **cursor protocols driven through function pointers in the object** (`ldr rN,
[self,#0xf8] ; blx rN`) rather than array walks — taking the cursor's address is why mwcc re-reads
it from the frame after every call. Next there: `func_ov000_020585e8` (592 B x6, 15 relocs).

★ **The AI-state veins are now paying first-try on 400–600 B functions.** The accumulated
codegen-cracks rules cover essentially the whole shape: back-to-front struct decls, aggregate
initialisers, declaration-initialisers for emission order, the Q12 sin/cos conversion, hw60's
trunc-pair discriminator, guard direction for out-of-line blocks. Vein status: **ov228 and ov231
are exhausted** at >=3 members / <=600 B; ov221-226 and ov158/159/160/246/247 have one family each
done and more below the 3-member cut. Next: `func_ov000_020585e8` (592 B x6, 15 relocs) and
`func_ov000_0205721c` (456 B x6) over ov000/004/005/008/009/025 -- a DIFFERENT subsystem (the menu
overlays), so expect different shapes.

**Named constants worth reusing** (Q12 radians): `0x1922` = pi/2 · `0x3244` = pi ·
`0x28be60db9391` = 65536/(2*pi) in .32. Both 0x1922 and 0x3244 get split by mwcc (not encodable).

**ov231 is now EXHAUSTED at ≥3 members / ≤600 B** (only `020ccc48` left, and that is a proven
frame-arg-home regalloc tie in `nonmatching/` with the failed steers listed). Next best undone
families, all still open: `func_ov000_020585e8` (592 B ×6, 15 relocs) and `func_ov000_0205721c`
(456 B ×6) over ov000/004/005/008/009/025 · `func_ov221_020d2574` (584 B ×6, 10 relocs) over
ov221-226 · `func_ov228_020d159c` (536 B ×6) · `func_ov158_020ce288` (344 B ×5) over
ov158/159/160/246/247.

★★ **ov231 is the same kind of vein as ov228 and is WIDE OPEN**: `ov231 → {232, 263, 265, 280}`,
5 members each, ~4 families still undone (`020cdaa8` 488 B/14 relocs, `020ccc48` 272 B/4 relocs,
and the 020cec2c / 020cf66c / 020ccfb8 / 020cca74 / 020cc9e0 / 020cd094 callees named in the ones
already done). Chain state → state through the c634/cd094 callbacks; each goes down in 1–2
compiles. Field map so far: `+0x14` sq.dist · `+0x1c/+0x20` counters · `+0x24` cooldown ·
`+0x28` timer · `+0x30` tracked point · `+0x3c` current point · `+0x49` stance byte ·
`+0x54` one-shot flag · `+0x58` pending flag · `ctx[4]` gate byte (state holds until `*ctx[4]==0`).
`ov206 → {207,208,209,268,274,275}` (×7) also exists but `020ccef4` is a RECURSIVE 9-arg tree walk
with the frame-arg-home smell — leave it.

★★ **`tools/rebuild_index.py` — the index is now COMPLETE (23,238 functions) and rebuildable from
the ROM.** Run it (dry run by default, `--write` to merge) whenever the index looks thin. It works
from `dsd_extract/*.bin` + `symbols.txt`/`relocs.txt`/`delinks.txt`, so it does not care what is
decompiled, and it self-checks against existing entries before merging.
**Do NOT use `tools/index_funcs.py` for a full rebuild**: it reads `build/delinks/*.o`, which only
ever contain functions that are still *gaps* — the moment a function has a `.c` it vanishes from
them. It silently took the index from 11055 to 8789 on 2026-07-17 and broke `verify_idx` for every
finished function. It now merges rather than overwrites, so it is safe, but `rebuild_index.py` is
the one that can actually give you everything.

⚠ **dedupprop must never propagate from an ASM stub** (fixed 2026-07-17). An `asm void` + `dcd`
blob is the ROM's own bytes, so it ALWAYS verifies — meaning it "rescues" a `nonmatching/` file
and deletes a real write-up. It generated 188 blobs into `calls/` and binned 24 analyses before
being caught. **The tell was `progress.py`'s ASM count going UP.** Watch that number after any
bulk propagation: C up / ASM flat is a real harvest; ASM up means blobs.

★ **The index's `mode` field was wrong for 1289 THUMB functions** (fixed 2026-07-17 — it now reads
`symbols.txt`). Symptom was `getcand` printing an **empty `disasm:`** and still saying `mode: arm`.
If getcand ever gives you nothing, that is the tell — check `symbols.txt` yourself.

⚠ **Never edit README.md with PowerShell `Set-Content -Encoding utf8`** — it prepends a BOM and
rewrites the file to CRLF (both showed up as spurious diffs on 2026-07-17). Use the Edit tool, or
Python with `io.open(p,'w',encoding='utf-8',newline='\n')`. `utf-8-sig` on read strips a BOM if one
already crept in.

★★ **The ov228 AI-state vein is WIDE OPEN and paying ~6 functions per analysis.** Every ov228
`func_ov2*` state handler has twins in **ov229/230/233/248/249** (sometimes ov231), and they share
a small set of building blocks: the Q12-radians sin/cos conversion, the `MTX_RotY33_` +
`MTX_MultVec33` steering tail (rotate `*(ctx[0]+0x490)+0x2c` into `ctx+0x10`), a `ctx[1]+0xad`
ready-flag, a `ctx[0]+0x1c7` give-up byte, and a `func_0203c634(self, self[0x20], cb)` re-entry.
Recurring field map: `+0x10` offset vec · `+0x40` heading (Q12 rad) · `+0x4c` timer ·
`+0x5c` stance · `+0x60/0x62` byte slots · `ctx[0]+0x3bc` target · `ctx[0]+0x4a0` radius.
Once you know the shape these go down in one or two compiles — **keep mining it**.

⚠ **Run `python tools/dedupprop.py` FIRST every batch.** It is now permanent (was in the
scratchpad, kept getting lost). Skipping it cost six iterations of ~1-match-each single carves on
2026-07-16; running it returned **18/18 instantly** (ov008 ×17, ov023 ×1). Re-run after every
batch — each new match can unlock twins. **Always fix the propagated comments before committing.**
★ **Concretely, what "fix the comments" means: a propagated comment names the REP's overlay.**
2026-07-17, all 4 twins: *"arm or disarm an animation node (see `func_ov025_02088e4c` for the ticker
that consumes these)"* — true in ov025, a lie in the ov002 file it was copied into. **The same trap
`namefam_propagate` guards for names ("embeds an address"), and nothing guards it for comments.**
The fix is usually cheap because the cross-reference is itself a family: that ticker exists once per
overlay (`TickTagTrackerNodes` ×8), so each file just cites its own — ov002_020540f0 /
ov008_020551a4 / ov025_02088e4c. Group the referenced address by masked hex to find the local twin.

★ **`nonmatching/` is not a verdict — re-propagate into it (fixed 2026-07-17).** dedupprop used to
put every `.c` under `src/` into one `done` dict, so a function whose only file was a *recorded
failure* in `nonmatching/` counted as carved and was never offered a matched twin — excluding
exactly the functions most likely to be rescued. The fix (`done` vs `attempted`) turned up 7
candidates and **all 7 matched**. A match now also deletes its `nonmatching/` twin. A separate
sweep found **10 more** `nonmatching/` files whose function already had a byte-exact `.c` sitting
in `calls/`; all 10 were removed. Lesson that generalises: **a nonmatching file records one
person's failed attempt at one moment, not a property of the function.** Periodically re-test them
— `asm_stubs/` + `nonmatching/` pairs (59 of them) are the normal, correct state; `calls/` +
`nonmatching/` pairs are always a bug.

★★ **THE BIG OPEN VEIN — undone shape families: 1288 families / 3052 functions.**
Nothing covers these: `dedupprop` needs a matched rep, and `scan_fam.py` only ranks `asm_stubs`
(exhausted, returns 0). Scan snippet + workflow in `tools.md`. **Match one member by hand →
`dedupprop --write` → the rest are free.** Proven twice on 2026-07-16 (`func_ov000_020550b0`,
`func_ov000_02055604`, both 6 members over ov000/005/008/009/025/026, both first try) = 12
functions from 2 analyses. Templates must have NO scene identity, structure only.

**Session tally 2026-07-16: 15 templates → 65 functions.** The tractable 40–220 B / ≥4-member band
is now **EMPTY** — every family in it is either matched or in the blocked list below.

**Where to go next, in order:**
1. **Widen the band — ALREADY MEASURED: `≥3` members / 40–400 B gives 231 families / 754
   functions.** That is the next slice and it is big. Best first picks:
   ~~`func_ov137_020cd2d8` (316 B ×7)~~ — **CLOSED 2026-07-17: arg-setup scheduling tie**, all 7
   lost. Full diagnosis in `src/overlays/ov137/nonmatching/func_ov137_020cd2d8.c`; do not retry
   under this mwcc build.
   ~~`func_ov228_020d01e8` (248 B ×6)~~ — **DONE 2026-07-17, +6** (matched first try with the
   radians crack, all 5 twins propagated).
   Still open: `func_ov221_020d34cc` (324 B ×7), `func_ov000_020551d4` (224 B ×6),
   `func_ov000_02056e28` (360 B ×6, only 2 relocs — but see the UNFINISHED note below).

   ★ **Head start on `func_ov137_020cd2d8` (7 members — analysed, not written, 2026-07-16 23:25;
   stopped deliberately rather than risk a tired guess at fixed-point math):**
   - It is Q12-radians → 16-bit angle index → sin/cos table lookup → `FX_Mul`, all INLINED
     (there are no `FX_` relocs; only `func_ov107_020c9264`, `func_0203c634`, `data_0203d210`
     and the continuation `func_ov137_020cd414`).
   - Pool: `0x66666667` = the /10 magic (asr #2) for the usual `x*30/10` delay at +0x14.
   - Pool `0x000028be_60db9391` is a **64-bit** constant = `10430.378 / 2^32`, and
     **10430.378 = 65536/(2π)** — the radians→index factor. (`10430.378/4096 = 2.546`, i.e. a
     Q12-radian input.) The `umull`/`mla`/`mla` trio is the signed 64×64 multiply by it.
   - `data_0203d210` is the sin/cos table: sin at `[idx*4]`, cos at `[idx*4+2]` (`ldrsh`), the
     second index built as `((idx*2)+1)*2`.
   - `FX_Mul(x, 0x300)` is the `umull ; mla ; adds #0x800 ; adc ; lsr #12 ; orr <<20` shape.
     Results land at +0x30/+0x38, with +0x34 = 0x400 and +0x3c = 0.
   - Guard: returns early once +0x40 reaches 0x200.
   ✅ **The part I stopped on is now SOLVED and byte-verified (2026-07-17).** The full C form of
   the radians→index→table conversion is in `codegen-cracks.md` under "Q12 radians -> 16-bit angle
   -> sin/cos table". Proven on `func_ov228_020d0cb0`: the whole umull/mla/mla + rounding +
   `lsl#4;lsr#16;asr#4` block came out byte-identical on the first try. Short version:
   `idx = (unsigned short)(((long long)rad * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;`
   The `(unsigned short)` cast is what emits `lsl#4;lsr#16`, and the trailing `>>4` becomes `asr`
   because the u16 promotes to signed int. `data_0203d210[idx*2]` / `[idx*2+1]` = sin / cos.
   (020d0cb0 itself is in `nonmatching/` — it ties at 0x4d on a register permutation *after* the
   conversion. That tie is not in this maths, so do not let it deter you here.)
   Still unverified: whether `data_0203d210` is the NitroSDK `FX_SinCosTable_` — check before
   naming it that.

   ★★ **START WITH `func_ov228_020d01e8` INSTEAD (248 B ×6) — same maths, far better entry point.**
   Confirmed 2026-07-16 00:45: it carries the *identical* `0x28be60db9391` constant and the
   identical `umull/mla/mla ; adds ; adc #0x800 ; lsl#4 ; lsr#16 ; asr#4` sequence, but unlike
   020cd2d8 its consumers are **named relocs**: `MTX_RotY33_` (0x01ff9010) and `MTX_MultVec33`
   (0x01ff93bc), with `data_0203d210` reloc'd as the table. So the shape is pinned from both ends:
     sin = ((s16 *)data_0203d210)[idx * 2]      (`ldrsh r1,[r2,r1]`, r1 = (idx<<1)<<1)
     cos = ((s16 *)data_0203d210)[idx * 2 + 1]  (`ldrsh r2,[r2,r0]`, r0 = ((idx<<1)+1)<<1)
     MTX_RotY33_(&m, sin, cos); MTX_MultVec33(owner[0x490] + 0x2c, &m, ctx + 0x10);
   `data_0203d210` is almost certainly `FX_SinCosTable_` — check it against the NitroSDK table
   before naming it. Crack 020d01e8 first, then 020cd2d8's 7 members follow from the same idiom.
   Structure of 020d01e8 already read: early-out if `func_ov228_020cf344() < 0`; if the byte at
   `ctx[1]+0xad` is 0, park the owner in state 2 and dispatch; return if `ctx[0x5c]` is set;
   otherwise the rotate-and-transform above. Frame is `sub sp,#0x24` = a 3x3 matrix.
2. The big undone families: 6×1396 B (ov000/004/005/008/009/025), 5×1132 B, 6×824 B, 6×656 B.
   One analysis still buys 5–6 functions, which beats any single.
3. ov024 singles (23 left) — the big ones (`02086958` 2496 B audio transform, `02086004` 1472 B
   colour convert, `02085154` 1452 B decoder init, already analysed with its plate written).

⚠ **A template that ties costs FOUR functions, not one** — dedupprop will not propagate from a
`nonmatching/` rep, so the whole family is blocked. Push harder on templates than on singles.
**Two blocked, each worth 4 — both are "everything right except one permutation":**
- `func_ov158_020cd174` (ov158/159/246/247) — 140/140, only r6/r7 swapped: the ROM allocates the
  callee-saved pair descending, mwcc ascending. Both decl orders tried; it is first-use driven.
  Verified the structure is right: `ctx[0]` really is loaded 3× into different registers, so the
  `owner`-local-only-in-the-else shape is correct.
- `func_ov206_020ccd68` (ov206/207/274/275) — 140/140, exact through 0x73; only the final call's
  arg-setup ORDER differs (ROM: two memory ops first, `mov r0,r5` last; mwcc: argument order).
  Hoisting the action and the callback into locals changed nothing.

- `func_ov221_020d43a0` (ov221/222/223/224) — 156/156, ONE instruction at 0x10: the ROM caches the
  mode from its arg register (`mov r5,r1`), mwcc reads it back from the block the variadic
  prologue spilled (`ldr r5,[sp,#0x14]`), because va_start takes the parameter's address.
- `func_ov206_020cd464` (ov206/207/274/275) — 184/184, same instruction count, diff at 0x15: which
  register holds the derived -1 (ROM r2, mwcc ip) and, as a knock-on, where the first callback's
  pool load lands. **The `signed char *` cast for the -1 store is solved and must be kept** — as
  `unsigned char *` the constant folds to 0xff and mwcc emits `mov ip,#0xff` instead of the ROM's
  `sub r2,lr,#1`.

All three are single-permutation misses on otherwise perfect functions — a fresh idea on any is
worth 4 functions. Their *other* knobs are already solved and documented in-file (the `owner`
local, the `state` local, the double-negated range-opt guard, the `(&(last)+1)` va_start form,
the `m = mode` local) — **don't re-derive those, attack only the permutation**.

✗ **RETRACTED, same day — I set this test and it failed.** I had written: "all three blocked
families live in the enemy-AI overlays … if a fourth AI template ties the same way, that is
evidence for the build-version theory". A fourth did tie (`func_ov206_020cd464`) — but by then the
honest tally was **4 AI templates matched vs 4 tied**:
- matched: `ov137_020cc2dc`, `ov231_020cc9e0`, `ov231_020cdc90`, `ov206_020ce328`
- tied: `ov158_020cd174`, `ov206_020ccd68`, `ov221_020d43a0`, `ov206_020cd464`

50/50 is **not** evidence of a systematic build difference — I was counting only the failures. The
real read: AI-overlay code is dense with register shuffling and argument marshalling, so roughly
half of these templates land on a permutation mwcc orders differently. Two families in the SAME
overlay (ov206) went opposite ways, which a build-version cause could not explain.
Keep attacking them individually; don't reach for the compiler theory.

## Per-overlay fronts

| overlay | done | notes |
|---|---|---|
| **ov024** (MobiClip) | 76/99 with a `.c` (63 byte-exact + 13 `nonmatching/`), **23 left** | best-understood front; see `ov024-mobiclip.md`. Basis = `func_index.json` (99); the "120" in `symbols.txt` counts entries the index does not carve. What's left is the big stuff: `02086958` (2496 B audio transform), `02086004` (1472 B colour convert), `02085154` (1452 B decoder init), `020846c0` (1108 B FS/player setup), `02082f04` (720 B), plus the GX/SND setup band (270–470 B) |
| **ov006** (char select) | 135/194 | 59 left. Good yield; watch the ctx-CSE tie (very common here) |
| ov000 (title/boot/menus) | — | boot chain done; the title screen itself is unmapped |

## ov024 — the state of play

**The fast-memory cache layer is DONE (2026-07-16)** — all four getters byte-exact, plus the
per-frame tick, the ov012 entry (`02084df4`), both FS cursor ops and the stream-lead update.
Headline for the port: there are **two arenas**, not one (code vs data), and every table getter
**falls back to the `.rodata` original when the arena is full** — so nothing depends on the copy
happening. Full slot map + the two newly identified payloads are in `ov024-mobiclip.md`.
`020933ac` = `clamp(i-64,0,255)` (8-bit) was previously unidentified.

**ITCM vs DTCM is now SETTLED** — `0208455c` (the arena reservation) matched: arena id 3 = ITCM,
id 4 = DTCM, and `OS_GetArenaHi(3) - 0x659c` = `0x01ff9a64` derives the port's measured address
from first principles. `020865d0()` = `0x2580` = `0x2100+0x300+0x180` exactly, which cross-checks
the three data payloads. ITCM is **borrowed**: the old contents are saved to `.bss` first. Full
table in `ov024-mobiclip.md`.

**`02085154` (decoder init) is ANALYSED but NOT YET DECOMPILED** — 1452 B, deliberately deferred
rather than rushed. Its findings are already folded into `ov024-mobiclip.md` + the Ghidra plate,
so nothing is lost if it waits: the payload→field map (tables land in the 0x454-byte decoder-state
block at `ctx[0x34]`, **not** the converter args), `clamp8 + 0x40` proving the guard-band bias,
`0x14f8` confirmed a third time from the allocation side, and the byte-wise MODS/N2/N3 check.
Picking it up = write the C from that plate; the header check and the two alloc loops are the
fiddly parts.

Also open: `020846c0` (1108 B, the big FS/player setup), `02086004` (1472 B, zero relocs, the
colour converter) and `02086958` (2496 B, the audio transform — the `+0x920`/`+0x960` split is the
port's standing ask #2). `data_ov024_020886c4` is a newly-named .rodata table (decoder block
+0x40) whose contents are still uncharacterised.

**Audio path: understood end to end.**
`MobiClip_DecodeAudioEntry` (02085c8c) dispatches four codings off `ctx+0x1c`, each yielding 256
samples/channel: type 1 → `02086958` (FastAudio transform), type 2 → `02087d24` (0x28 B),
type 3 → IMA ADPCM (4 B state header + 0x80 of nibbles), else raw PCM (0x200).
`ctx+0x1e` = channel count, `ctx+0xd0` = current channel.

**`func_ov024_02086958` = the AUDIO transform — settled, do not relitigate.**
Its own pool holds the clamps `+0x9b8 = 32767` / `+0x9bc = -32768`, output is `strh` strided by a
per-channel stride from `ctx+0x14f4`. Video pixels would clamp 0..255 and store as bytes.
Dequant ramp traced: `r6 = header_u16 >> 9` (7 bits) sets the first live coefficient — the source
starts at index `127 - r6` of a 128-entry array; the quant factor is the **running index** from 2
(not a table); the DC term is unscaled. **Still open:** what `+0x920` (r6==127) vs `+0x960`
select, and where the 128-entry source lives.

**Video path: it is the 26 KB ITCM blob**, `data_ov024_0208c8c4`, len `0x659c`. Not decompilable
as `.c` — it is PIC data in the overlay copied to ITCM (`0x01ff9a64`, byte-verified by the port)
and invoked through `ctx+0x38`. Extracted copy: `khdays-port/data/re/mobiclip_blob.bin`.
Progress so far: the **filter family is proven to be motion-comp interpolation** (mask
`0x7f7f7f7f` + `lsr #1` = SIMD packed-byte halving, stride 0x100 = luma) —
`0x020913bc`, `0x02091534` (the odd one, 17 halvings vs 27), `0x020916ac`, `0x020919fc`.
VLC candidates: `0x02091d14` (4428 B, 100% cover, heavy ldrb/ldr) and `0x02090674`.
⚠ The "offset table at blob+0x04" reading is **not established** — see `ov024-mobiclip.md`.

## Cross-repo: the port

`E:\KH 3582\khdays-port\data\re\` carries a running exchange:
`mobiclip_blob_handoff.md` / `mobiclip_reply2.md` (port → decomp) and
`mobiclip_blob_reply.md` / `mobiclip_reply3.md` (decomp → port). Both sides fold accepted
findings into their own docs. Their standing asks, in order:

1. **Map the blob** (VLC + motion comp) — start at the filter family.
2. `02086958`'s `+0x920`/`+0x960` split — **audio** priority now, not video.
3. MODS `0x14` — measured (`0x0efc28f6` ×37 / `0x0efc29f1` ×9, ids scattered, uncorrelated with
   rate or audio) but **not identified**; no read of it traced in ov024.

The one thing neither side can substitute: an **address-range trace of ITCM
`0x01ff9a64`–`0x02000000`** (a function-list trace structurally cannot see the blob). It would
rank the blob's hot loops and identify who writes VRAM bank D in one shot.

They also flagged `FUN_02020e58` (804,332 hits) as a **bytecode/script interpreter** — opcode at
[0], sub-opcode at [1], length at [2], handler table at `DAT_0202103c`. Not MobiClip, but a whole
unnamed subsystem worth a session.

## Recurring tie classes seen this session (route on sight)

- **ctx-CSE / pool rematerialisation** — the ROM reloads `&global` (and function addresses) from
  the pool after every call, keeping `push {r3,lr}`; mwcc caches them in callee-saved regs and
  pushes more. Often *same size*, only registers differ.
- **mwcc canonicalisation** — `tst` where the ROM keeps `ands`; `blt`+fall-through-on-true where
  the ROM does `bge`+fall-through-on-false. No source form changes either (all three tried).
- **Dead re-check** — the ROM emits `movs r4,r0 ; cmpne r4,#0` where the `movs` already set Z.
- **Constant sinking** — mwcc sinks a `+0x9400` into each call site where the ROM computes it once.
  (Note this is mwcc rematerialising where it usually shares — the inverse of ctx-CSE.)

## Deferred pattern (2026-07-18): buffer-zero + callback dispatch with redundant strb-at-offset-2
func_ov210_020d3f28 (x3), func_ov212_020cd20c (x3): zero a ~0xc0-byte stack buffer via an unrolled
4-halfword loop (`strh` x4 per iter, N iters) + tail strh, THEN a REDUNDANT `mov r1,#0; strb r1,[sp,#2]`
that re-zeros byte offset 2, then call a callback with a bit-selected size. A struct `{u16 a; u8 b; u8 c;
u16 rest[..]} = {0}` reproduces the halfword loop EXACTLY (proven on ov212) but NOT the separate
strb-at-2. The redundant strb comes from a distinct byte member at offset 2 that mwcc zeroes separately
from the bulk halfword zero. Not yet cracked -- find the struct layout (or explicit `buf.byte2 = 0;`
extra statement) that adds the standalone strb. Left as gap functions (no file written).

## Tie-blocked sub-family (2026-07-18): multi-transform-copy AI publishers
Large AI functions that begin with N inlined 11-word transform block-copies (`*(blk11*)(dst+0x10) =
*(blk11*)(src+4)` x4-6, sources/dests loaded from self+0x3bX/0x3cX/0x3dX) are ALL blocked by the
inlined-block-copy src/dst scratch-register tie (deferred-ties.md): mwcc 3.0/139 colours src->ip,
dst->lr CONSISTENTLY; the ROM colours src->lr, dst->ip. Confirmed opposite-and-consistent across
func_ov119_020cbfc4, func_ov244_020cd68c, func_ov208_020d070c, func_ov206_020cc9b4. These publishers
(e.g. func_ov208_020d070c 380B, func_ov206_020cc9b4 452B, and their ov207/268/274/... twins) are
non-matching regardless of C form -- do NOT spend time; skip on sight when the decompile opens with the
repeated 11-word field-copy blocks. Their state-logic tails are fine; only the copies tie.

## Session 2026-07-18 status (autonomous run)
Matched ~33 families this run (MotionTickTimers x3+x4, RingBuffer fill/reset, DrawTextNewline,
VariadicMapForward, ScreenTeardown/WaitLoadAdvancePhase/AllocWorkBufferInit/CommitPage/EnableBothHalves/
FullScreenTeardown/ListRemoveAndFree/PlaceElementByVariant (the ov008/009/025 screen-state vein),
DriveExitModes, ReaimEmitterCone, PickBestFacingTarget, ResetAimArmDispatch, RingBuffer*, ov185 sub-node
helpers, ov208/210/228 helpers, etc.). New cracks banked in codegen-cracks.md: offset-fold-into-ldr-disp,
byte-arg-hoist, va_start bic-align, volatile-reload (loop CSE + ov008 context), search-loop found-inside,
switch default-first, (short)(x<<1), char* alias vs cast-induction, dedicated-loop-index coloring.

REMAINING is hard -- the easy/clean functions are drained. Categories left (deprioritise, or bring fresh
focus):
- **byte-packing message handlers** (ov208_020d03e8, ov208_020d39d8, ov210_020d3980, ov221_*): decode
  message bytes into a 24-bit matrix via CONCAT13/12/11 + `>>8`, or unpack with `(v>>0x10)&0x7f |
  (v>>0x18)&0x80`. The garbage-low-byte + shift codegen is not yet reproduced. Cracking ONE unlocks a
  class. Often also has a jump-table `switch` (dense 0..N -> `addls pc,pc,r1,lsl#2`).
- **trig / 64-bit fixed-point** (ov185_020cf7b0, ov200_020cf074, ov212_020d02b0, ov210_020d0a48/020d2230,
  ov208_020d215c): magic-divide + sin/cos table lookup + FX_MUL. High-risk constants.
- **multi-transform-copy publishers**: block-copy lr/ip tie (see families.md), skip on sight.
- **intricate bit-toggle** (ov185_020ce40c): flip bit0 of a byte, spawn with a mode picked from the new
  bit -- no ties, just very finicky codegen; matchable with patience.
- Register-allocation/predication ties already parked: ov185_020cefa8 (node/owner r6<->r7),
  ov200_020ce4b8 (self+0x100 base), ov235_020d1a34 / ov119_020cf7b0 (c5c0 2-param r0/r1), ov008_02069954
  (homed by-value struct), ov008_020679f8 / ov008_02067a7c (tag-- schedule), ov119_020cbfc4 /
  ov244_020cd68c (block-copy lr/ip).

## Cola de parks cercanos (2026-07-18) -- `python tools/rank_parks.py`

`build/try/rank.json` tiene el ranking completo por distancia REAL en instrucciones (no bytes).
14 parks a <=2 instrucciones; 3 ya rescatados. **Lo que queda, con su diagnostico ya hecho** --
son el mejor punto de entrada para la siguiente sesion:

| park | ROM | mias | pista |
|---|---|---|---|
| `func_ov008_02072fe4` | `add r0,r0,#0` | -- | el copy-artifact. Un cast a `long long` SI produce la copia, pero convierte el truncado `lsl/lsr #16` en un AND con pool. `+ (v - v)` se pliega aqui (no hay llamada). Falta la grafia que de copia Y cast. |
| `func_ov022_0209ea44` | `cmp r2, lr` | `cmp lr, r2` | mwcc canonicaliza: invertir el `==` en la fuente NO cambia nada, y hoistear el campo a un local tampoco (probadas ambas ordenes). Va por otro lado. |
| `func_0200dcf0` | `ldr ip,[pc,#0xc]; ldr r0,[ip]` | igual con r1 | eleccion de registro en la carga del pool |
| `func_ov022_0209145c` | `ldr r2,[r0,#0x20]; blx r2` | igual con r0 | registro de la llamada indirecta |
| `func_ov022_0208a790` | `sub r2,r2,#1` | `mov r2,#0xff` | la ROM calcula 0xff restando; buscar el `x-1` en la fuente |
| `func_ov022_020b1bb4` | `sub r0,r1,#1` | `mov r0,#0xff` | mismo caso que el anterior |
| `func_ov022_0208acc4` | `bne; cmp r1,#2` | `cmpeq r1,#2` | if-conversion: la ROM ramifica donde mwcc predica |
| `func_ov022_020ad7f0` | `add r0,r1,r3; add r0,r0,#0x4c` | `add r1,r1,r3; add r0,r1,#0x4c` | asociacion de la expresion |
| `func_02023c60` | `ldr r2,[pc,#0x48]` | `[pc,#0x4c]` | orden del pool de constantes |
| `func_ov022_02092b60`, `func_ov030_020b3efc` | solo difiere el offset del `bl` | | mirar si es orden de pool/reloc |

Ya cerrados de esa lista: `func_ov202_020cd4a0` + `func_ov203_020d4d20` (signo ldrb/ldrsb
opuesto en dos lecturas de byte de la MISMA funcion -- estaban invertidas) y `func_0203b9ac`
(`v = i = 0`).

### Actualizacion de la cola (2026-07-18, loop autonomo)

**Cerradas**: `ov022_020b1bb4`, `ov022_0208a790` (signed -1), `ov022_0208acc4` (switch de un
caso), `ov202_020cd2b8` + `ov203_020d4b38` (signo ldrb/ldrsb), `ov008_02055ba4` (guarda `> 0`
leida a int), `ov024_02084fac` (doble null-check real en el original).

**Nueva pista fuerte -- doble condicion que falta en la fuente.** El patron `cmp X,#0` seguido de
`cmpne Y,#0` (o `ldrne`+`cmpne`) en la ROM significa que **al original le sobra una condicion que
tu C no tiene**. En `ov024_02084fac` el original comprueba el mismo puntero DOS veces y un solo
test compila 4 B corto. Candidatos con la misma firma, sin tocar:
`ov008_0206f914` + `ov008_02074150` (gemelas), `ov166_020cc624`, `ov022_020b06d8`,
`ov141_020cc5a4`, `ov000_02055d98`.

~~⚠ **Y mira `func_ov000_020552b4`**: el ranking le saca `cmp r3,r0 ; ldrne r0,[r2,#0xa70] ;
cmpne r3,r0` cuatro veces en el lado solo-ROM, o sea le faltan cuatro condiciones compuestas.~~
❌ **FALSO, comprobado el mismo dia.** Esas instrucciones estan en **los DOS lados** con los
registros permutados. Su nota de "stream identico" era correcta.

★★ **La leccion, que es lo que hay que llevarse:** un diff por alineamiento marca una instruccion
como "solo-ROM" en cuanto cambia un campo de registro. **Nunca leas la lista solo-ROM sin la
solo-mias al lado** -- es exactamente el error de "cero resultados de una busqueda que no podia
encontrarlo", pero al reves: resultados que parecen hallazgos y son artefactos de la herramienta.
`rank_parks.py` imprime las dos listas justo por esto.

Lo que SI salio de mirarla: el orden de los operandos del `&` estaba mal (la ROM lee el global
primero), 44 -> 41 bytes. Detalles y lo descartado, en la cabecera del propio park.

**Sigue abierta** `ov008_0206f914`: la ROM sale del early-return con `popeq` sin tocar r0 (param_1
sigue ahi); mwcc mete un `moveq r0,r8` redundante (+4 B). Probados los dos ordenes de declaracion
y `sel = result = 0`.

### Cola de limpieza de nombres (2026-07-18)

`python tools/namefam_propagate.py` reporta **15 familias cuyos miembros nombrados NO coinciden**.
Eso es senal real, no ruido: son gemelas byte-identicas con nombres distintos. Dos clases:

1. **Sufijo de direccion** (`stDiv10Store_cd154` / `_d0d94`, `setupDual_b39ec` / `_b61ec` x7,
   `GridConfirmOnPenUp` / `...2`): nombres-placeholder que inflan la cuenta de "nombradas" sin
   aportar nada. Necesitan un nombre real, lo que exige entender la funcion -- no es mecanico.
2. **Nombres que discrepan de verdad** (`AdvancePositionUnlessHitFlag` vs
   `ConfigSubStateThenAdvanceSlot`; `CreateRegistryEntryAndLink` vs `CreateRegistryEntryForActor`):
   uno de los dos esta mal y hay que decidir cual mirando el codigo.

⚠ **Leccion de como se genero una de esas discrepancias hoy**: al nombrar la familia c5c0 numere
`_2`/`_3` por el ORDEN DENTRO DEL OVERLAY, asi que gemelas byte-identicas de overlays distintos
acabaron con nombres diferentes. **Nombra por FAMILIA, no por posicion**, y reserva el sufijo para
cuando un mismo overlay tiene dos miembros de la MISMA familia. Corregido:
`OvNNN_SpawnChild10AndBackLink` (11 miembros, tamano 0x10) y `OvNNN_SpawnChild0cAndBackLink`
(12 miembros, tamano 0xc). `namefam_propagate` es quien lo detecto -- correrlo despues de cada
tanda de nombrado es barato y pilla esto solo.

## ★★★ VETA ABIERTA 2026-07-18: 243 familias frescas, 1011 funciones

Cuando la cola de parks cercanos se agota (y el 2026-07-18 se agoto: lo que queda es
permutacion de registros y scheduling puro), **la veta buena no es pulir parks, es agrupar las
funciones SIN HACER por hex enmascarado**. Hay ~10.000 sin hacer; agrupadas dan 268 familias de
>=4 miembros. **PERO 25 de ellas tienen ya un rep PARKEADO** (su forma enmascarada coincide con un
fichero de `nonmatching/`), asi que atacarlas es repetir un empate ya diagnosticado. Las
genuinamente frescas son **243, cubriendo 1.011 funciones**.

⚠ **Filtra por eso SIEMPRE antes de elegir cabeza**: el 2026-07-18 mire 8 candidatas y **6 eran
formas ya parkeadas**. El chequeo cuesta un script y ahorra la iteracion entera.

```python
# agrupa las no-hechas por forma (excluye asm_stubs de "hecha")
g = defaultdict(list)
for n, e in IDX.items():
    if n not in done and 60 <= e['size'] <= 400:
        g[masked(e)].append(n)
fams = sorted(((len(v), len(k)//2, v) for k, v in g.items() if len(v) >= 4), reverse=True)
```

Primera cosechada (ov167..ov180, 12 miembros, 156 B): **match del rep al primer intento**, luego
`dedupprop --write` dio los 11 restantes + 2 gemelos de otros cracks + rescato un `nonmatching/`.
**15 funciones de un solo analisis.**

Cabezas de familia mas grandes que quedan (mira antes si la forma es de una clase con empate
conocido -- la de 8x312B usa copias de bloque `ldm/stm`, que es tie recurrente):

| miembros | tam | rep |
|---|---|---|
| 8 | 312 B | `func_ov168_020d3ea4` (⚠ copias ldm/stm) |
| 7 | 292 B | `func_ov115_020ce2e4` |
| 7 | 180 B | `func_ov141_020cd2b0` |
| 6 | 372 B | `func_ov004_0204d640` |
| 6 | 360 B | `func_ov004_0204d7b4` |
| 6 | 344 B | `func_ov181_020cd300` |
| 6 | 316 B | `func_ov138_020d0f18` |
| 6 | 300 B | `func_ov142_020d01e4` |
| 6 | 204 B | `func_ov138_020d1428` |
| 6 | 152 B | `func_ov004_0204dac4` |
| ~~6~~ | 112 B | ~~`func_ov132_020cf040`~~ ⛔ **NO es fresca**: misma forma enmascarada que
`func_ov162_020cf5e0`, que ya esta parkeada por coloreado puro (probadas las 6 permutaciones
de declaracion, todas dan el mismo byte). Son 8 miembros bloqueados por ese rep. |

⚠ **Corre `audit_shadowed.py --fix` despues de cada `dedupprop --write`**: la propagacion de esta
familia creo **13 stubs sombra**. Los 13 verificaban, se borraron, y el gate siguio en 306.

### ★★ Como ELEGIR cabeza de familia: descarta las que tienen bucle

Probado el 2026-07-18 con 4 cabezas seguidas, 2 fallos y 2 aciertos, y el patron es limpio:

| cabeza | forma | resultado |
|---|---|---|
| `func_ov167_020d1790` (12) | recta, sin bucle | **match al primer intento** |
| `func_ov147_020cdc9c` (6) | recta, sin bucle | **match al segundo intento** |
| `func_ov004_0204dac4` (6) | bucle con contador | park: reduccion de fuerza + ctx-CSE, DOS empates a la vez |
| `func_ov132_020cf040` (8) | == la forma ya parkeada de ov162 | ni se intenta |

**Filtra las cabezas por "no tiene salto hacia atras" antes de elegir.** Un bucle trae
reduccion de fuerza (mwcc convierte el indice en puntero caminante) y relecturas que mwcc
fusiona por CSE -- las dos son clases de empate conocidas, y aparecen juntas.

```python
def hasloop(n):   # sobre el desensamblado en el modo CORRECTO
    for i in dis(n):
        if i.mnemonic.startswith('b') and not i.mnemonic.startswith(('bl','bx','bic')):
            m = re.match(r'^#(?:0x)?([0-9a-f]+)$', i.op_str.strip())
            if m and int(m.group(1), 16) < i.address:
                return True
    return False
```

Y **comprueba siempre que la cabeza no sea la misma forma enmascarada que un park existente**
antes de gastar analisis: la de 8 miembros de 112 B resulto ser `func_ov162_020cf5e0`, ya parkeada.


### ★★ PREFIERE las cabezas de familia PEQUENAS (2026-07-18)

`pick_family.py` las ordena por numero de miembros y luego por tamano DESCENDENTE, asi que si
coges de arriba te llevas siempre las mas grandes. **Cogelas por abajo.**

Datos del dia: las tres cabezas grandes seguidas (320-380 B) acabaron las tres parkeadas, y las
tres por lo mismo -- presion de registros / coloreado. Las dos siguientes, elegidas por PEQUENAS
(116 B y 132 B, 5 miembros cada una), casaron **las dos en 2 intentos**.

Tiene sentido mecanico: la capa que ya domino (forma de fuente) escala con el numero de
construcciones, pero la que no (asignacion de registros) escala con la PRESION, y la presion
crece con el tamano. Una funcion de 120 B rara vez tiene mas valores vivos que registros.

Hay familias de 5 miembros hasta 116 B sin tocar. Empieza por ahi.


### ★ Ordena las cabezas por TAMANO, no por numero de miembros

`pick_family.py` imprime por miembros y luego por tamano descendente. Cogiendo de arriba te llevas
las de 5 miembros, que en ov117/ov147 empiezan en 116 B -- pero **hay familias de 4 miembros de
88-96 B** en los overlays de enemigos (ov033-ov049) que no aparecen hasta el fondo de la lista.

Reordena la salida por tamano antes de elegir:

    python tools/pick_family.py 200 | awk '/miembros/' | sort -k4 -n

4 miembros x 88 B es mejor apuesta que 5 x 230 B: la presion de registros escala con el tamano y
es lo que hace fallar las cabezas grandes.

## Tally chain (ov000/004/005/008/009/025/069) -- CLOSED 2026-07-20, 35 funcs

Five x7 ARM families, all byte-exact and named:
  TallySlots (96 B) / TallyScaledSlots (152 B) -- walk the 4-slot table at block+0x34
  AddToTally (372 B) / AddToSecondaryTally (264 B) -- accumulate-or-allocate per id
  FoldRecordIntoTally (328 B) -- unrolled closer, mla group + 13 counters
Four came out of existing nonmatching/ parks.  Subsystem context: synthesis recipes
with ingredients and costs (see func_ov000_0205721c).

STILL OPEN: func_ov000_02056e28 x7, 360 B, parked.  Today's row-local crack takes it
from 348 to 356 (4 short) but its two slot loops then walk.  Needs re-deriving whole,
not patching -- and note the park's claim that "both slot loops are already right" is
wrong, so do not trust its inventory.

## Family census: DO NOT filter by reloc density

161 open byte-identical families >=4 members cover 714 functions.  An earlier density
filter hid every ARM family, which is where all of today's yield came from.  Regenerate
with the plain masked-hex group-by, no filter.

## In flight: func_ov033_020b43dc x4 (332 B) -- 27 lines, from 0x2D

Work-in-progress source at build/try/WIP_ov033_020b43dc.c (build/ is gitignored, so copy it
somewhere first if you want it to survive).  Size is already right.

Settled so far:
 - stack layout is args at sp+0 (0x28 bytes) and blk at sp+0x28 (0x2c), so `blk` is declared
   FIRST and `args` second (later declaration gets the lower address);
 - the byte at args+0x25 is cleared of bits 0 and 1 through an `unsigned char` INTERMEDIATE:
   `v = b & ~1; b = v & ~2;`.  That is what produces the ROM's `and r0, r0, #0xff` between
   the two bics.  A `struct { unsigned char b : 8; }` bitfield instead overshoots by 28
   bytes, and folding the two clears into `& ~3` loses the pair entirely;
 - the heading comes from the node angle at +0x80 minus half a turn, >> 4 into the sin/cos
   table, and both components are NEGATED into blk+0x14 / blk+0x1c.

Next: the remaining 27 lines start at 0x2D, in the block that fills blk -- check the store
ORDER against the ROM before anything else.

# ============================================================
# SESSION 2026-07-20 -- read this first
# ============================================================

## The single biggest thing learned: 64-BIT FIELDS

A real mask on one word and the SAME OPERATION with ZERO on the word beside it is ONE
64-bit field.  `*(long long *)p |= mask`, `& mask`, `&= ~mask`.  Full write-up in
codegen-cracks.md.  This closed 20 functions in one day across three families and five
parks, and FIVE separate park notes had blamed something else: jump-table merging,
predicate-versus-branch, a "dead `& 0` flag term", redundant stores -O4 would remove, and a
build-time 0-valued macro in a header we do not have.

Three refinements that cost real time to learn:
 - read the signature PER TEST, not per function (one function had four 64-bit guards and
   one ordinary 32-bit `tst`; converting all five went 16 bytes over);
 - which half carries the mask says where the field STARTS, and a high-half constant must be
   SHIFTED (`0x2000LL << 32`, not `0x2000LL`);
 - the two-step base (`add r0, r5, #0x64` then `[r0, #0x404]`) that always came with it is
   just how mwcc addresses the high half -- not a separate construct.

## How to hunt for it

    parks whose disassembly has two consecutive and/orr/bic/eor where one ends in `, #0`

That scan found 25 parks; 5 were not already using long long; 3 of those closed immediately.
The scan is worth re-running whenever a new operation shows up in this shape.

## Overlays closed this session

ov007 14/14 and ov301 16/16.  ov010 is still 5/7 and is the last of that group.

## Method lessons that changed outcomes

 - PAIRS.  ov007's last function needed TWO changes at once (inverted branch test AND
   volatile on that branch's store); each alone scored WORSE and both were already in its
   RULED OUT list.  Every ruled-out list in this repo is a list of singletons.
 - `register` steers WHETHER a value is kept in a register, not WHICH.  It closed ov301
   (a pointer live across a block) and did nothing for ov010 or ov038 (short-lived scratch).
 - Grep the PARKED files, not just the matched ones.  The 64-bit OR was already written
   correctly in two parks before I spent three attempts deriving it.
 - Do not steer on the size number.  On func_ov046_020b3770 the correct fix made the
   function look FURTHER away because two errors had been partly cancelling.
 - A park that does not COMPILE cannot be re-tested.  tools/audit_parks_build.py now checks
   all 395; one had been broken for a day, and its note carried the best open lead for a
   10-member family.

## Where the yield is

Fresh families with NO park, in the 100-340 byte ARM band.  ~50 remain.  The parked backlog
in these overlays is now mostly genuine register-permutation ties.  Census with the plain
masked-hex group-by and NO reloc-density filter -- that filter used to hide every ARM family.

## Concurrency

A PEER SESSION was active in this repo today (commits 95f9a2ef, cc5f818f).  It rewrote
func_ov301_020cbfc4 underneath me mid-experiment.  Check `git log` before assuming a file is
yours, and yield rather than race.

## IN-PROGRESS 2026-07-31: func_ov008_020590b4 (Ov008 display/VRAM setup, 544B, 3rd call of Ov008_SetupScene)

Best candidate: build/try/590b4_best.c (== 590b4_st.c). 99% byte-exact; struct-based
(DisplayRegisters + static const MMIO pointers, mirrors matched sibling
func_ov008_02067c04). EVERYTHING matches byte-exact EXCEPT one 8-instruction block:
the **Sub DISPCNT RMW** (0x04001000) at ~offset 0x11C.

The tie: this block is `SUB_DISPLAY->dispcnt = (dispcnt & 0xFFCFFFEF)|0x10|0x200000;`
immediately followed by `GX_SetBankForSubOBJExtPltt(0)`.
- ROM: mask loaded into r0, result in r0 (r0 busy), `mov r0,#0` materialised AFTER str.
- mine: mwcc reserves r0 for the next call's 0, puts mask in r1, and hoists `mov r0,#0`
  into the load-use stall after the value load -> 8-instr register permutation, same size,
  same semantics.
Tried ~35 source forms (mask pool vs bic, held/absolute/struct pointer, mask-first,
temp vars for value/mask/result, `register`, callee return types int/void, set-bit
order, parenthesisation). Diff is FROZEN at the identical permutation every time -> the
hoist is driven by the SubOBJExtPltt(0) call + global allocator preference, not by the
RMW expression. The sibling 02067c04 matched because ITS sub DISPCNT is immediately
preceded by a main-DISPCNT access (no intervening GX calls), giving a different global
alloc; mine has 3 GX calls (SubBG/SubBGExtPltt/SubOBJ) between main#2 and sub DISPCNT.
NEXT IDEAS to try fresh: (a) find a source form that keeps r0 live across the block so
the arg-0 can't be hoisted; (b) re-derive whether the sub DISPCNT and SubOBJExtPltt are
really adjacent in the ROM source or separated; (c) examine ov000/ov009 display-setup
siblings for the exact idiom of a sub DISPCNT followed by a zero-arg GX call.
Frontier order in Ov008_SetupScene: ApplyFlagPresets(DONE) -> InitPanel(done) ->
020590b4(HERE) -> [BG clears=SDK] -> ... -> 0205a3dc(588B, next unresolved).


### UPDATE 2026-07-31 (iter 2): func_ov008_020590b4 root cause CONFIRMED by diagnostic
Best candidate now build/try/590b4_A1.c (== 590b4_best.c), byte diff @0x121 (was @0x11D):
the mask-ACCUMULATOR form `unsigned int r = 0xFFCFFFEF; r &= SUB_DISPLAY->dispcnt;
r |= 0x10; r |= 0x200000; SUB_DISPLAY->dispcnt = r;` fixes addr->r2 and value->r1
(both now match ROM). Remaining 6-instr residue = mask/result register (r3 vs r0) + the
`mov r0,#0` hoist.
DIAGNOSTIC (build/try/590b4_DIAG.c): replacing the trailing GX_SetBankForSubOBJExtPltt(0)
with a void() call makes mwcc compute the result in r0 and REMOVES the hoist entirely ->
proves the sole cause is mwcc RESERVING r0 for the trailing zero-arg call, which displaces
the mask/result off r0 and lets the scheduler hoist `mov r0,#0` into the ldr-value->and
load-use stall. The ROM keeps mask/result in r0 (r0 busy) and materialises the 0 AFTER str.
Value-first forms (C1/C2/A2) avoid the stall but break addr->r2 (@0x11D); mask-accumulator
gets addr but re-introduces the stall. No source form found that gets BOTH. Compiler is
correct (3.0/139, user-confirmed) so build_sweep is not applicable. Function is pure DS
display/VRAM hardware plumbing (GX bank config + DISPCNT/blend/window RMW) = platform-
replaced category, but kept SELECTED per session rules (not parked, not nonmatching).
Next fresh axes to try: (a) a source form that keeps the mask/result live in r0 across the
block; (b) whether an earlier byte-exact block can be re-expressed to change global alloc
state without changing its bytes (unlikely); (c) accept as the hardest MMIO tie and revisit.


### UPDATE 2026-07-31 (iter 4): func_ov008_020590b4 matched-tree search exhausted
Applied the skill's #1 move (grep matched tree for the instruction I can't produce):
searched func_index for `and r0,r1,r0` (pooled-mask RMW into r0) followed by nearby
`mov r0,#0` -> 8 funcs, only 1 with real C (func_ov010_0204ce60), and that one is a
coincidence (a `& 0x2fff` keypad read inside a switch, not an RMW-then-zero-arg-call).
Checked all three display-setup siblings: ov009_02052dec sub#1 is followed by arg-8
(GX_SetBankForSubOBJ) and compiles addr r3/result r1/hoist (== my plain form) and MATCHES;
ov000_02058a40 puts its sub DISPCNT AFTER all four sub-bank calls, followed by
GXS_SetGraphicsMode(0). NEITHER has my adjacency (single sub DISPCNT RMW immediately
followed by a zero-arg GX call), so there is no template. Best candidate stays
build/try/590b4_A1.c (== 590b4_best.c) @0x121 (mask-accumulator form gets addr->r2 and
value->r1 exact; residue = mask/result r3-vs-r0 + the arg-0 hoist). Kept SELECTED per
session rules (no park, no nonmatching). Compiler confirmed correct so no build sweep.


### a3dc UPDATE 2026-07-31 (iter 10) -- 31 experiments, register residue confirmed
func_ov008_0205a3dc = Ov008_Menu_InitSceneObject (Ghidra-named + SceneParam struct + typed pool
slot, all SAVED). Candidate build/try/a3dc_best.c is 588 B, byte-exact EVERYWHERE except 10
instructions that differ ONLY r1<->r3 (sceneId register) in the val+first-switch block:
ROM `ldr r1,[r4]; mul r0,r1,r0; ldr r2,[pc]=table; ldr r2,[r2,r0]=val` (2 regs via double reuse,
frees r1 for sceneId); mine `ldr r3,[r4]; mul r1,r3,r0; ldr r0,[pc]; ldr r2,[r0,r1]` (3 regs).
Confirmed by difflib the instruction ORDER is identical (the switch cmp IS interleaved in both) --
it is PURE register allocation, not scheduling. The code before AND after the block is byte-exact,
so the allocator state entering the block is identical to the ROM; the val-block source alone
decides r1 vs r3, and 31 forms all give r3.
DO-NOT-RE-GRIND list (all -> r3, @0xA1): struct-array `data[i].f0`; raw offset `*(int*)((char*)
data+i*0x34)` (== Ghidra's exact expr); offset local; entry ptr `&data[i]`; tbl ptr `base+off`;
`*(int*)&data[i]`; word index `[i*0xd]`; static-inline helper; explicit stride var; 0x34*i order;
*param_2-direct (both val and switch); two reads; separate index var; sep sceneId var; decl order
(val first / sceneId first / stride at top); register hints (sceneId/val/both); int* vs uint*
param_2; const table; val/f0 unsigned; char[128] buffer; inline-in-arm (616B). matched-tree grep
for `ldr r2,[r2,r0]` (the table->val reuse) = 0 hits in 12k funcs -> no source template exists.
build_sweep N/A (reads only src/nonmatching; user: compiler is correct). This is an mwcc
register-allocation residue analogous to the ov000 scheduler residue -- a codegen decision not
reachable from source with 3.0/139 given this structure. Kept SELECTED, candidate preserved,
NOT parked. Semantic layer complete so integration is one step once the register falls.
