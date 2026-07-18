#!/usr/bin/env python3
"""Compara cada `extern` de los ficheros aparcados con la DEFINICION real del callee en el arbol.

    python tools/audit_extern_sig.py            # solo los parks
    python tools/audit_extern_sig.py --all      # tambien auto/ y calls/ (deberia salir limpio)

`audit_arity.py` compara contra como LLAMA el resto del arbol. Esto compara contra como esta
DEFINIDO, que es la fuente de verdad: si `func_X` se define con dos parametros y tu `extern` dice
uno, tienes un argumento perdido aunque nadie mas lo llame.

POR QUE (2026-07-18): en func_ov041_020b3c10 el residuo eran 3 bytes y un solo registro distinto
-- la firma exacta de un empate de asignacion. La causa real era un `extern` con un parametro de
menos: el ROM mantenia r1 intacto porque r1 era el segundo argumento vivo. La definicion correcta
llevaba todo el rato en el arbol. Un argumento perdido no cambia el tamaño NI el numero de
instrucciones; a veces solo mueve un temporal de registro.
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# `extern <tipo> nombre(args);` en una linea
EXT = re.compile(r"^\s*extern\s+[\w \*]+?\**\s*(\w+)\s*\(([^;]*)\)\s*;", re.M)
# definicion: `<tipo> nombre(args) {`  (o con el { en la linea siguiente)
DEF = re.compile(r"^[\w][\w \*]*?\**\s*(\w+)\s*\(([^;{]*)\)\s*\{", re.M)


def arity(argstr):
    a = argstr.strip()
    # ⚠ `f()` NO es "cero argumentos": en C es "parametros sin especificar", y el arbol usa esa
    # forma a proposito para los callees cuya aridad varia por call site. Solo `f(void)` es un
    # cero de verdad. Tratarlos igual daba 70 falsos positivos de 377 ficheros.
    if a == "":
        return None
    if a == "void":
        return 0
    if "..." in a:
        return None                      # variadica: no comparable
    depth = n = 0
    for ch in a:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "," and depth == 0:
            n += 1
    return n + 1


def definitions():
    """nombre -> (aridad, fichero). Solo de C real: nada de asm_stubs."""
    out = {}
    for p in glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True):
        rel = os.path.relpath(p, ROOT).replace("\\", "/")
        if "asm_stubs" in rel.split("/") or "nonmatching" in rel.split("/"):
            continue
        try:
            s = open(p, encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        for m in DEF.finditer(s):
            name, args = m.group(1), m.group(2)
            if not name.startswith(("func_", "data_")):
                continue
            a = arity(args)
            if a is not None:
                out[name] = (a, rel)
    return out


def main():
    defs = definitions()
    pats = ["src/**/nonmatching/*.c"]
    if "--all" in sys.argv:
        pats += ["src/**/auto/*.c", "src/**/calls/*.c"]

    files = []
    for pat in pats:
        files += glob.glob(os.path.join(ROOT, pat), recursive=True)

    bad = 0
    for p in sorted(files):
        rel = os.path.relpath(p, ROOT).replace("\\", "/")
        if "asm_stubs" in rel.split("/"):
            continue
        s = open(p, encoding="utf-8", errors="replace").read()
        hits = []
        for m in EXT.finditer(s):
            name, args = m.group(1), m.group(2)
            mine = arity(args)
            if mine is None or name not in defs:
                continue
            real, where = defs[name]
            # ⚠ Solo la direccion "declaro MENOS de los que la definicion tiene" es accionable.
            # Al reves es legitimo y comun: en el ABI de ARM un callee que usa menos parametros
            # simplemente ignora los registros de mas, asi que el original puede pasar 2 a una
            # funcion que solo lee 1 -- y el ROM SI pone r1. Quitar ese argumento "de mas" en
            # func_ov185_020ced78 empeoro de +8 a -44 bytes (2026-07-18). La definicion no es
            # autoritativa sobre lo que pasan los llamadores.
            if mine >= real:
                continue
            # ⚠ Solo importa si el fichero LLAMA al callee. Cuando solo toma su direccion
            # (callback pasado a func_0203c634 y compañia) la aridad declarada no afecta al
            # codegen, y contarla llenaba el informe de ruido inofensivo.
            body = s[m.end():]
            if not re.search(r"(?<![\w&])%s\s*\(" % re.escape(name), body):
                continue
            hits.append((name, mine, real, where))
        if hits:
            bad += 1
            print("!! %s" % rel)
            for name, mine, real, where in hits:
                print("      %-28s extern dice %d, DEFINIDA con %d  (%s)"
                      % (name, mine, real, where))

    print("\n%d ficheros revisados, %d con un extern que contradice la definicion"
          % (len(files), bad))
    if bad:
        print("Cada uno es un candidato a rescate: corrige el extern, añade el argumento y remide.")


if __name__ == "__main__":
    main()
