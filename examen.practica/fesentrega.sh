#!/bin/sh -f

if [ -x /assig/cl1/generaid ]; then 
	/assig/cl1/generaid 1000111111
else
	echo "Warning: No s'ha pogut generar l'identificador."
	echo "Aquest exàmen no es podrà entregar!" 
	echo local > identificador
fi

tar cf entrega.tar identificador cl.g myASTnode.hh codegen.cc codegen.hh semantic.cc semantic.hh ptype.cc ptype.hh symtab.cc symtab.hh util.cc util.hh
