#!/bin/sh -f

[ -e checker ] || mkdir checker
rm -rf checker/*

cp basemodules.tar jp.tar entrega.tar infochecker.txt avaluador.cc checker

cd checker
tar xf basemodules.tar
tar xf jp.tar
tar xf entrega.tar cl.g myASTnode.hh codegen.cc codegen.hh semantic.cc semantic.hh ptype.cc ptype.hh symtab.cc symtab.hh util.cc util.hh

./compile.sh
g++ -ansi -Wall -o avaluador avaluador.cc
touch outputexecution
./avaluador
