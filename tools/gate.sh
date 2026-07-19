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
set -euo pipefail

cd "$(dirname "$0")/.."

echo "== 1/6 propagando gemelas byte-identicas"
# POR QUE ESTA AQUI (2026-07-19): `dedupprop.py` propaga un .c casado a sus gemelas byte-identicas
# (mismos bytes tras enmascarar relocs). Es GRATIS y la skill lo pone como primer paso del bucle de
# familias... y aun asi estuve un dia entero casando funcion por funcion sin ejecutarlo ni una vez.
# Cuando por fin lo lance: 32 matches y 4 rescates de nonmatching/ de golpe -- ov008 resulto tener
# un espejo byte-identico de toda la pantalla de seleccion de ov026 que llevaba media tarde
# haciendo a mano. Depender de acordarse no funciona; por eso vive en el gate y no en una nota.
python tools/dedupprop.py --write | tail -3

echo "== 2/6 barriendo stubs sombreados"
python tools/audit_shadowed.py --fix | tail -1

echo "== 3/6 restaurando los binarios de referencia"
cp dsd_extract/arm9/arm9.bin dsd_extract/arm9/itcm.bin dsd_extract/arm9/dtcm.bin build/build/
for f in dsd_extract/arm9_overlays/ov*.bin; do
    b=$(basename "$f" .bin)
    cp "$f" "build/build/arm9_$b.bin"
done

echo "== 4/6 configure (OBLIGATORIO tras borrar stubs)"
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

echo "== 5/6 ninja"
if ! ninja; then
    echo "!! ninja FALLO -- el dsd check que viene despues seria un falso verde. Abortando."
    exit 1
fi

echo "== 6/6 dsd check modules"
ok=$(tools/dsd.exe check modules --config-path config/arm9/config.yaml -f 2>&1 | grep -c ": OK" || true)
echo "DSD_OK=$ok"
if [ "$ok" != "306" ]; then
    echo "!! esperaba 306 modulos OK"
    exit 1
fi
echo "GATE VERDE (306/306)"
