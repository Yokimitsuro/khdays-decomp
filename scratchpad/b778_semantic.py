"""Semantic receipt for func_ov002_0205b778."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelListPairValue"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205b778. Construye el par de valores de un widget "
     "de clase lista: coge la entrada en el indice nIndex+2 de pList, lee su "
     "nTag en +0x02, lee el nTag de la entrada que la sigue en lists[0] de la "
     "sesion, y pasa los dos mas nKind al formateador compartido en "
     "0x0205b728, el mismo que alimenta el camino del array de celdas con dos "
     "celdas contiguas. La llama el repaint ya casado func_ov002_0205b7dc en "
     "sus casos de clase 2 y 3."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad CUATRO, confirmada en el desensamblado: r0, r1, r2 y r3 se leen "
     "antes de escribirse y no hay lectura por encima del marco. Renombrados a "
     "pList, nIndex, nKind y bSuppress. El cuarto es un supresor, no un "
     "selector: cuando es distinto de cero el ROM salta directo a la cola con "
     "los dos acumuladores todavia a cero, asi que el formateador ve un par "
     "nulo. Read-back PARAMS 4 en r0, r1, r2 y r3."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el marco es push {r4,r5,r6,lr} sin sub sp y "
     "ninguna llamada pasa de cuatro argumentos. Los dos acumuladores viven en "
     "r4 y r5, nKind se preserva en r6 y la entrada consultada pasa por r0 y "
     "r1. Read-back LOCALS 0, asi que no hay nada que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_PanelListPairValue(NNSFndList *pList, int nIndex, int nKind, "
     "int bSuppress). Devuelve tal cual el resultado del formateador: el ROM "
     "termina con bl seguido del epilogo, sin tocar r0 ni enmascararlo, asi que "
     "el retorno es la palabra completa y no un u16 truncado."),
    ("layout_decision", "reused"),
    ("layout_evidence",
     "Reutiliza dos tipos existentes y NO crea rivales. Primero NNSFndList, "
     "aplicado al parametro pList: read-back len=12 con head_object, "
     "tail_object, num_objects y offset, y el ROM confirma el tamano al "
     "direccionar lists[0] en +0x480 de la sesion. Segundo, y mas importante, "
     "los objetos de lista que recorre son Ov002PanelEntry, que ya existia con "
     "len=8: la funcion lee exactamente +0x02, que es el campo nTag ushort de "
     "ese tipo, y el ayudante 0x0205a754 del mismo frente lee +0x00 y +0x02, es "
     "decir nKey y nTag. Se comprobo antes de tipar que Ov002PanelEntry solo "
     "tiene como padres su propio array y su puntero, de modo que reutilizarlo "
     "no puede repetir la regresion anterior de desbordar el struct de sesion. "
     "No aparece ningun offset nuevo."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: pList tipado NNSFndList * con "
     "almacenamiento r0, los otros tres parametros int, NNSFndList len=12 con "
     "sus cuatro campos, Ov002PanelEntry len=8 con nKey +0x00, nTag +0x02 y "
     "nState +0x04, y el pool slot arm9_ov002.bss::0207f620 como "
     "Ov002PanelSession *. No se creo ni extendio ningun tipo."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los tres scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction."),
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
     "tools/audit_struct_sync.py sale con codigo 0 y no lista NNSFndList, "
     "Ov002PanelEntry ni Ov002PanelSession con variantes en conflicto. Esta "
     "tanda reutiliza tipos existentes sin modificarlos."),
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
