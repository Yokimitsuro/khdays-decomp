#!/usr/bin/env bash
# El gate de 306 modulos, en el orden CORRECTO y abortando a la primera.
#
#   bash tools/gate.sh
#
# POR QUE EXISTE (2026-07-18): el orden importa y equivocarse da un falso verde.
#   1. `audit_shadowed.py --fix` borra stubs -> el build.ninja viejo los sigue listando.
#   2. Si no vuelves a lanzar configure.py, `ninja` falla con "missing and no known rule".
#   3. Y `dsd check` lanzado DESPUES de ese ninja fallido **sigue diciendo 306**, porque compara
#      contra los binarios de la compilacion anterior. Un 306 detras de un ninja roto no vale.
#
# `set -e` mas la comprobacion explicita del codigo de salida de ninja evitan exactamente eso.
#
# SEGUNDO FALSO VERDE, CORREGIDO EL 2026-09-11 (issue #6): `dsd check modules` solo hashea el
# fichero que cada modulo declara en `object:` (build/build/*.bin) contra el hash de la referencia.
# Este script COPIABA la referencia a esas rutas en el paso 3 y nunca enlazaba (el `ninja` a secas
# solo compila: build.ninja lleva `default compile`), asi que el 306 comparaba la referencia
# consigo misma. Ahora el paso 4 borra esos binarios, el paso 7 enlaza de verdad (el enlace es lo
# unico que los escribe, via los redirects del lcf mas fix_interwork.py) y el paso 8 hashea el
# resultado del enlace. Un 306 aqui significa que los 306 modulos ENLAZADOS son byte-identicos a
# la ROM; nada menos.
set -euo pipefail

cd "$(dirname "$0")/.."

echo "== 1/8 propagando gemelas byte-identicas"
# POR QUE ESTA AQUI (2026-07-19): `dedupprop.py` propaga un .c casado a sus gemelas byte-identicas
# (mismos bytes tras enmascarar relocs). Es GRATIS y la skill lo pone como primer paso del bucle de
# familias... y aun asi estuve un dia entero casando funcion por funcion sin ejecutarlo ni una vez.
# Cuando por fin lo lance: 32 matches y 4 rescates de nonmatching/ de golpe -- ov008 resulto tener
# un espejo byte-identico de toda la pantalla de seleccion de ov026 que llevaba media tarde
# haciendo a mano. Depender de acordarse no funciona; por eso vive en el gate y no en una nota.
python tools/dedupprop.py --write | tail -3

echo "== 2/8 barriendo stubs sombreados"
python tools/audit_shadowed.py --fix | tail -1

echo "== 3/8 auditando nombre de fichero frente a simbolo definido"
# POR QUE ESTA AQUI (2026-09-11): 40 fuentes definian el simbolo de OTRA direccion (el prefijo
# de overlay reescrito al propagar, el sufijo no). Ningun check lo veia: verify_idx compara bytes
# por nombre de fichero y PROGRESS.md cuenta por nombre de fichero, asi que los 40 pasaban como
# casados mientras rompian el enlace (uno multiply-defined, 39 undefined). Issue #6.
if ! python tools/audit_symbol_names.py; then
    echo "!! hay fuentes cuyo simbolo no coincide con su fichero: el enlace no puede ser correcto."
    exit 1
fi

echo "== 4/8 borrando los binarios del enlace anterior"
# POR QUE ES rm Y NO cp (2026-09-11): la version anterior COPIABA aqui los binarios de referencia
# de dsd_extract/, y `dsd check modules` no hace mas que hashear esos mismos ficheros contra el
# hash de la referencia. Como ademas el `ninja` a secas nunca enlaza (build.ninja: default
# compile), el paso 8 comparaba la referencia consigo misma: 306/306 con el ELF de dos meses antes,
# 305 al voltear un byte, 306 al repetir la copia. Un binario viejo tampoco puede sobrevivir aqui:
# si el enlace de abajo falla, el check debe encontrar el fichero ausente y ponerse rojo.
rm -f build/build/arm9.bin build/build/itcm.bin build/build/dtcm.bin build/build/arm9_ov*.bin

echo "== 5/8 configure (OBLIGATORIO tras borrar stubs)"
# NO silenciar la salida: configure.py imprime el stdout/stderr del subproceso que falla.
# Sin esto, un fallo intermitente de gen_delinks.py solo se ve como "failed: ..." sin causa
# (visto 4 veces el 2026-07-19, siempre verde al repetir). Con la salida visible se puede
# diagnosticar en lugar de reintentar a ciegas.
# Reintento: el subproceso gen_delinks.py muere de vez en cuando SIN imprimir nada y con codigo
# de salida != 0 (visto ~7 veces entre el 18 y el 19 de julio de 2026, en overlays distintos).
# Lanzado a mano justo despues, el MISMO comando sale con rc=0 -- o sea, lo esta matando algo de
# fuera (antivirus, casi seguro), no es un problema del arbol. Tres intentos y luego rendirse.
cfg_ok=0
for attempt in 1 2 3; do
    if python tools/configure.py; then cfg_ok=1; break; fi
    echo "   (configure fallo en el intento $attempt -- reintentando)"
done
if [ "$cfg_ok" != "1" ]; then
    echo "!! configure FALLO 3 veces. Esto ya NO es el fallo transitorio: mira el mensaje."
    exit 1
fi

echo "== 6/8 ninja (compila todos los objetos)"
if ! ninja; then
    echo "!! ninja FALLO -- el dsd check que viene despues seria un falso verde. Abortando."
    exit 1
fi

echo "== 7/8 ninja build/arm9.elf (enlace completo: escribe build/build/*.bin y parchea interworking)"
# El lcf redirige cada modulo a build/arm9*.bin relativo al ELF, o sea a build/build/*.bin, y
# tools/_run_mwld.py ejecuta fix_interwork.py --write al terminar. SOLO este paso produce los
# ficheros que el check de abajo hashea. Si aborta, no hay binarios y el check es rojo, como debe.
if ! ninja build/arm9.elf; then
    echo "!! el ENLACE fallo -- los modulos no existen y el check de abajo no puede ser verde."
    exit 1
fi

echo "== 8/8 dsd check modules (hash de los modulos ENLAZADOS contra la referencia)"
ok=$(tools/dsd.exe check modules --config-path config/arm9/config.yaml -f 2>&1 | grep -c ": OK" || true)
echo "DSD_OK=$ok"
if [ "$ok" != "306" ]; then
    echo "!! esperaba 306 modulos OK; los que fallan:"
    tools/dsd.exe check modules --config-path config/arm9/config.yaml -f 2>&1 | grep -v ": OK" | head -40
    exit 1
fi
echo "GATE VERDE (306/306, modulos enlazados)"
