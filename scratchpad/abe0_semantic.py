"""Semantic receipt for func_ov002_0205abe0."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelPushSlotState"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205abe0. Empuja el estado de un slot del panel: "
     "reenvia nSlot y nState a la contabilidad de slot en 0x0205abb8, vuelve a "
     "empujar el nKind del propio nodo junto con el nValue del llamante, e "
     "invoca el callback del nodo. Solo despues, y solo cuando nState es 0 o "
     "esta entre 3 y 6, refleja el nValue y el nKind del nodo sobre el widget "
     "que el contexto guarda para el tag 2. Es la segunda mitad de "
     "Ov002_PanelRefreshRowHeader, tras Ov002_PanelWriteSlotLabel."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad TRES, confirmada en el desensamblado: solo r0, r1 y r2 se leen "
     "antes de escribirse y no hay ninguna lectura por encima del marco. "
     "Renombrados a nSlot, nState y nValue. nState NO es un booleano: el ROM lo "
     "compara contra 0, 3 y 6, asi que es un indice de estado con rangos, y eso "
     "es lo que obligo a escribir el ternario del caller con constantes de enum "
     "en vez de 0 y 1. Read-back PARAMS 3."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el prologo no tiene sub sp y ninguna llamada pasa "
     "de tres argumentos, asi que el r3 empujado es solo relleno de "
     "alineacion. El puntero de sesion vive en r5, nSlot en r4, nState en r7 y "
     "nValue en r6. Read-back LOCALS 0, asi que no hay nada que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelPushSlotState(int nSlot, int nState, int nValue). Retorno "
     "void: las tres salidas restauran pc sin definir r0. Las dos salidas "
     "tempranas son ldmialt y ldmiagt, es decir epilogos predicados, lo que "
     "confirma que en la fuente son return explicitos y no un else-if hacia una "
     "cola compartida."),
    ("layout_decision", "created"),
    ("layout_evidence",
     "Layout nuevo, creado como tipo de Ghidra. Los objetos que cuelgan del "
     "campo de sesion en +0x620 se leen con ldrsh en +0x02 y +0x04, es decir "
     "dos enteros de 16 bits CON SIGNO, y los dos se pasan a las mismas "
     "posiciones de argumento de 0x02053578 y de 0x02053720, lo que fija sus "
     "roles: valor y kind. Creado Ov002TagTrackerNode de 6 bytes con pad0000, "
     "pad0001, nValue short en +0x02 y nKind short en +0x04; los dos primeros "
     "bytes quedan como relleno porque el ROM no los toca y no invento lo que "
     "no puedo probar. El campo aWords0620 int[1] se retipo a aNodes "
     "Ov002TagTrackerNode *[1]: se conserva la anchura de cuatro bytes y el "
     "read-back confirma que Ov002PanelSession sigue midiendo 1572, de modo que "
     "NO se repite la regresion anterior de desbordar el struct de sesion. La "
     "longitud del array se deja en 1 a proposito: el ROM indexa por slot pero "
     "no acota el maximo, y no afirmo un tamano que no puedo demostrar."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: los tres parametros int, el tipo "
     "Ov002TagTrackerNode con len=6 y sus cuatro componentes, el campo aNodes "
     "Ov002TagTrackerNode *[1] de 4 bytes en +0x620 de Ov002PanelSession con la "
     "estructura todavia en 1572 bytes, y el pool slot "
     "arm9_ov002.bss::0207f620 como Ov002PanelSession *. Ademas se comprobo la "
     "decompilacion despues de aplicar: ahora lee pOVar2->aNodes[nSlot]->nKind, "
     "asi que el tipo esta realmente en uso y no ha roto el decompilador."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los tres scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction, incluido el que "
     "crea el tipo y hace replaceAtOffset."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada devolvio Program saved successfully y el "
     "read-back posterior informa CHANGED False."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: la funcion sale de la cuenta de ov002 al recibir "
     "nombre semantico, asi que la deuda baja y no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py sale con codigo 0 y no lista "
     "Ov002TagTrackerNode ni Ov002PanelSession con variantes en conflicto. Se "
     "busco antes de crear: no existia ningun tipo de nodo con esa forma, y el "
     "campo se retipo en el sitio en vez de crear una estructura rival."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    if r.returncode != 0:
        fail += 1
        print("%-30s FAIL %s" % (field, (r.stdout + r.stderr).strip()[:120]))
print("failures:", fail)
