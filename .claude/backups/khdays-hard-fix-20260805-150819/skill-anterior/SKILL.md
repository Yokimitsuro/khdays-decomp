---
name: khdays-decomp
description: >
  Procedimiento obligatorio para la decompilacion byte-exact de Kingdom Hearts 358/2 Days
  (NDS EU YKGP) y para avanzar el port de PC en orden real de ejecucion. Usar para cualquier
  trabajo bajo E:\KH 3582\decomp, funciones func_ovNNN_ADDR/func_ADDR, staging, verify_idx,
  Ghidra, structs, renombres, integracion, gate 306 y progreso del frente jugable.
when_to_use: >
  Cuando el usuario pida continuar el decomp, hacer MATCH, revisar staging, avanzar el port,
  trabajar una funcion concreta o ejecutar un loop autonomo.
---

# khdays-decomp: contrato operativo

Objetivo primario: obtener C real que compile con `mwccarm 3.0 build 139` y sea byte-exact
respecto al juego original. Objetivo inseparable: conservar en Ghidra la comprension semantica
necesaria para el futuro port de PC.

Un MATCH sin nombres, prototipo y tipos sincronizados en Ghidra esta incompleto.

## 1. Primera accion obligatoria

Desde la raiz del repositorio, ejecuta siempre:

```bash
python .claude/hooks/khdays_control.py status
```

El resultado gobierna toda la sesion:

- `NO_ACTIVE_FUNCTION`: puedes revisar `staging/`, confirmar el frente y seleccionar una funcion.
- Existe una funcion activa: trabaja exclusivamente en ella. No ejecutes seleccion de candidato.

Nunca edites directamente:

- `build/active_function.json`;
- `build/semantic_receipts/*.json`;
- `build/match_receipts/*.json`.

Solo `khdays_control.py` puede escribir esos archivos.

## 2. Bloqueo de funcion activa

Al seleccionar una funcion, crea inmediatamente el bloqueo:

```bash
python .claude/hooks/khdays_control.py select <funcion> \
  --candidate build/try/<archivo>.c \
  --mode detect \
  --frontier "<hito del port>" \
  --reason "<evidencia de que es la primera funcion no resuelta>"
```

Mientras exista `build/active_function.json`:

- esta prohibido seleccionar otra funcion;
- esta prohibido editar el C de otra funcion;
- esta prohibido mover la activa a `nonmatching/`, `blocked/` o `deferred/`;
- esta prohibido marcarla como parked, held o compiler tie;
- esta prohibido borrar el bloqueo manualmente;
- una familia, una funcion mas facil o un staging posterior no pueden reemplazarla.

Solo este comando puede cerrar la funcion y eliminar el bloqueo:

```bash
python .claude/hooks/khdays_control.py complete
```

Si devuelve codigo distinto de 0, la funcion sigue activa y debes continuar con ella.

## 3. Definicion completa de terminado

Una funcion esta terminada solo cuando supera los tres gates.

### MATCH_GATE

Todos son obligatorios:

1. `verify_idx.py` devuelve MATCH en el modo correcto.
2. Tamano exacto.
3. Instrucciones exactas.
4. Relocaciones exactas.
5. El archivo contiene C real, sin `asm`, `__asm`, `dcd` ni opcodes incrustados.
6. La fuente verificada es el mejor candidato registrado en el bloqueo.

Ejecuta:

```bash
python .claude/hooks/khdays_control.py verify
```

### SEMANTIC_GATE

Todos son obligatorios:

1. Funcion inspeccionada primero en Ghidra, incluyendo desensamblado cuando el decompiler sea dudoso.
2. Nombre semantico aplicado en Ghidra y comprobado por read-back.
3. Parametros revisados y renombrados cuando se comprenden.
4. Locales revisados y renombrados cuando se comprenden.
5. Prototipo corregido y comprobado por read-back.
6. Cada layout descubierto se crea, extiende o reutiliza como tipo de Ghidra en la misma tanda.
7. Los tipos se aplican al parametro, local, global o pool slot correcto y se comprueban por read-back.
8. Las transacciones quedan cerradas.
9. El programa queda guardado y se comprueba el guardado.
10. `audit_unnamed` y `audit_struct_sync` no introducen deuda nueva para la funcion.

Si la funcion no descubre ningun layout nuevo, registra `no_new_layout` y explica que tipos ya
existentes se revisaron o por que no existe un objeto tipable. No omitas la decision.

Registra cada evidencia con `semantic-mark`; consulta el formato en
`references/semantic-ghidra.md`. Comprueba el gate con:

```bash
python .claude/hooks/khdays_control.py semantic-check
```

### INTEGRATION_GATE

Todos son obligatorios:

1. Existe exactamente una fuente integrada en `calls/` o `auto/`.
2. No queda un gemelo en `asm_stubs/` que la sombree.
3. La fuente integrada sigue siendo C real.
4. El C integrado vuelve a verificar byte-exact en su ubicacion final.

Ejecuta:

```bash
python .claude/hooks/khdays_control.py integration-check
```

## 4. Structs: regla no interpretable

Los structs del C y los tipos de Ghidra cumplen funciones diferentes:

- el struct local del `.c` puede ser una herramienta de codegen para MWCC;
- el tipo de Ghidra es el modelo semantico reutilizable del port.

Por tanto:

- no sustituyas el tipo de Ghidra por un struct local;
- no sustituyas el struct de codegen por un header compartido si rompe el delink o el MATCH;
- antes de crear un tipo, busca el nombre ya usado por el arbol y por Ghidra;
- extiende tipos existentes en vez de crear rivales;
- offsets comprendidos no deben quedar solo como comentarios o aritmetica de punteros;
- un acceso crudo puede usarse como experimento temporal, pero no cierra el SEMANTIC_GATE;
- para globals, tipa el pool slot con la profundidad de puntero correcta;
- en overlays, usa el address space correcto, incluida la separacion `.bss` cuando corresponda.

## 5. Protocolo Ghidra obligatorio

Ghidra va antes del primer C y vuelve a usarse cuando cada experimento revela semantica nueva.

1. Lee decompilacion y desensamblado.
2. Confirma modo ARM/THUMB, limites, callers, callees y relocaciones.
3. Escribe un script Jython ASCII en `~/ghidra_scripts/`.
4. Ejecuta `run_ghidra_script`; no uses `run_script_inline`.
5. Guarda con una llamada separada a `save_program`.
6. Lee de vuelta nombres, prototipo y tipos por direccion con el address space correcto.
7. Registra evidencia concreta, no una intencion futura.

El bridge esta en `127.0.0.1:8089`. Si desaparecen las herramientas MCP, usa el HTTP directo
explicado en `references/semantic-ghidra.md`; no cambies a 8080.

Los errores de `endTransaction` de herramientas de tipos pueden ocurrir despues de aplicar el
cambio. No repitas a ciegas: lee el resultado, cierra transacciones de forma segura y guarda.

## 6. Bucle exacto por funcion

Ejecuta en este orden:

1. `khdays_control.py status`.
2. Revisa `staging/` recursivamente, pero no cambies de funcion si existe bloqueo.
3. Rechaza cualquier staging con `asm`, `dcd`, `__asm` u opcodes incrustados.
4. Lee Ghidra y el target real.
5. Confirma modo, tamano, relocaciones, aridad y prototipos de cada llamada.
6. Busca en el corpus matched la forma de instruccion que necesitas antes de inventar C.
7. Escribe o mejora el candidato en `build/try/`.
8. Compila y verifica.
9. Inspecciona el diff real; formula una hipotesis concreta.
10. Registra el residuo y la siguiente hipotesis:

```bash
python .claude/hooks/khdays_control.py record \
  --diff "<diferencias exactas>" \
  --next "<unico siguiente experimento>" \
  --experiments <N>
```

11. Repite hasta MATCH byte-exact.
12. Completa Ghidra y el SEMANTIC_GATE.
13. Integra en `auto/` si no tiene relocs o `calls/` si tiene relocs.
14. Elimina el `asm_stubs/` gemelo.
15. Verifica otra vez en la ubicacion final.
16. Ejecuta `khdays_control.py complete`.
17. Solo tras `COMPLETE_GATE_OK` puedes seleccionar la siguiente funcion.

## 7. Cuando difiere

No aceptes como resultado:

- C semanticamente equivalente;
- mismo tamano;
- porcentaje alto;
- una o dos instrucciones distintas;
- diferencias solo de registros;
- diferencias solo de scheduling;
- diferencias solo de stack;
- una entrada de `deferred-ties.md`;
- una explicacion basada en Ghidra sin leer el desensamblado;
- declarar que el compilador esta mal o falta si el usuario ya confirmo el toolchain.

Antes de un bloqueo genuino, recorre las dimensiones relevantes: aridad, retorno del caller,
prototipos, signedness, width, aliasing, struct shape, array shape, orden de declaraciones,
vida de temporales, stack layout, branch orientation, shared tails, expresiones, ARM/THUMB,
literal pool y relocs. Usa `references/codegen-cracks.md` mediante busqueda concreta.

Un bloqueo valido requiere una dependencia externa demostrable que impida continuar. No permite
seleccionar otra funcion; conserva el mejor candidato y el bloqueo activo.

## 8. Seleccion port-first

Solo se ejecuta cuando no existe funcion activa.

Prioridad:

1. Funcion nombrada expresamente por el usuario.
2. Modulo nombrado expresamente.
3. Staging de C real que avance el frente actual.
4. Primera funcion no resuelta del frente real de ejecucion.
5. Dependencia directa necesaria para esa funcion.
6. Teardown o transicion necesaria para el siguiente hito.
7. Resto de la escena alcanzable actual.

Nunca selecciones por overlay, direccion, tamano, facilidad, ausencia de relocs, familia o
rendimiento. `nonmatching/` es historia, no cola global.

Confirma el frente con el arbol, callers/callees, `func_index.json`, escenas y transiciones. Usa
`references/current-frontier.md` y `references/game-flow.md`; no leas el historial completo como
si fuera estado actual.

## 9. Staging

Al principio de cada iteracion:

- busca `.c` recursivamente en toda la raiz de cada lane;
- solo `calls/` y `auto/` cuentan como integrado;
- `nonmatching/` y `asm_stubs/` nunca cuentan como terminado;
- inspecciona el cuerpo, no confies en que `verify_idx` pruebe que es C;
- verifica en ambos modos cuando el modo no este confirmado;
- reescribe nombres heredados para ajustarlos al vocabulario probado del overlay receptor;
- integra staging del frente solo si no existe un bloqueo distinto.

## 10. Toolchain, build y git

Toolchain confirmado:

```text
mwccarm 3.0 build 139
-O4,p -proc arm946e -interworking -lang c99 -enum int -char signed
-inline on,noauto -Cpp_exceptions off -gccext,on
```

`verify_idx.py` es el gate rapido por funcion. Antes de cada push ejecuta el gate completo segun
`references/toolchain.md` y exige:

```text
DSD_OK=306 FAILED=0
```

Reglas de git:

- commit por funcion o lote semanticamente coherente;
- push como maximo una vez por hora;
- comprueba la antiguedad del ultimo push antes de subir;
- nunca añadas `Co-Authored-By: Claude`;
- no subas `build/`;
- todo lo que se suba al repo va en ingles;
- la skill local y sus referencias internas no se mencionan en commits.

## 11. Fin de una vuelta o limite de tiempo

Si la funcion activa no esta completa:

- no selecciones otra;
- no la aparques;
- no elimines el bloqueo;
- conserva el mejor candidato en `build/try/`;
- registra diff y siguiente hipotesis;
- termina solo la compilacion o verificacion ya iniciada;
- informa del estado exacto.

El Stop hook impedira cerrar normalmente mientras exista una funcion activa. Tras varios bloqueos,
Claude Code puede aplicar su proteccion de bucles; `/loop` reanudara la misma funcion porque el
bloqueo persiste en disco.

## 12. Carga progresiva de referencias

Carga siempre, y solo al inicio:

- `references/current-state.md`;
- `references/current-frontier.md`;
- esta skill.

Carga bajo demanda:

- `references/procedure-core.md`: comandos y pasos detallados;
- `references/semantic-ghidra.md`: structs, read-back y recibos;
- `references/toolchain.md`: verify, gate 306, commits y push;
- `references/codegen-cracks.md`: busca solo el sintoma actual;
- `references/deferred-ties.md`: evidencia historica a desafiar, nunca permiso para parar;
- `references/families.md`: solo si la familia pertenece al frente actual;
- `references/game-flow.md`: para confirmar el orden real;
- referencias de middleware/escena cuando el codigo las toque.

No cargues completos los ficheros de `references/history/`. Buscalos solo por funcion, simbolo,
instruccion o crack concreto. Son diarios historicos y pueden contener estados superados.

## 13. Informe obligatorio

Al final de cada vuelta informa:

- funcion activa;
- mejor candidato;
- modo;
- MATCH_GATE;
- SEMANTIC_GATE y campos pendientes;
- integracion y sombras;
- residuo exacto;
- experimentos nuevos y ejes descartados;
- hito actual del port;
- commit y push, si existen;
- ultimo gate 306;
- siguiente hipotesis para la misma funcion.

No escribas `NEXT <otra funcion>` mientras exista un bloqueo activo.
