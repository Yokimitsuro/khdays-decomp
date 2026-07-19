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

echo "== 1/5 barriendo stubs sombreados"
python tools/audit_shadowed.py --fix | tail -1

echo "== 2/5 restaurando los binarios de referencia"
cp dsd_extract/arm9/arm9.bin dsd_extract/arm9/itcm.bin dsd_extract/arm9/dtcm.bin build/build/
for f in dsd_extract/arm9_overlays/ov*.bin; do
    b=$(basename "$f" .bin)
    cp "$f" "build/build/arm9_$b.bin"
done

echo "== 3/5 configure (OBLIGATORIO tras borrar stubs)"
# NO silenciar la salida: configure.py imprime el stdout/stderr del subproceso que falla.
# Sin esto, un fallo intermitente de gen_delinks.py solo se ve como "failed: ..." sin causa
# (visto 4 veces el 2026-07-19, siempre verde al repetir). Con la salida visible se puede
# diagnosticar en lugar de reintentar a ciegas.
if ! python tools/configure.py; then
    echo "!! configure FALLO -- revisa el mensaje de arriba. Si es transitorio, repite el gate."
    exit 1
fi

echo "== 4/5 ninja"
if ! ninja; then
    echo "!! ninja FALLO -- el dsd check que viene despues seria un falso verde. Abortando."
    exit 1
fi

echo "== 5/5 dsd check modules"
ok=$(tools/dsd.exe check modules --config-path config/arm9/config.yaml -f 2>&1 | grep -c ": OK" || true)
echo "DSD_OK=$ok"
if [ "$ok" != "306" ]; then
    echo "!! esperaba 306 modulos OK"
    exit 1
fi
echo "GATE VERDE (306/306)"
