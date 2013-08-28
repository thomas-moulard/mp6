#!/bin/sh
## moulinette.sh for myreadiso in /u/a1/moular_t/rendu/moular_t-myreadiso/tests
## 
## Made by thomas moulard
## Login   <moular_t@epita.fr>
## 
## Started on  Wed Nov  2 19:40:11 2005 thomas moulard
## Last update Fri Nov 11 19:31:06 2005 thomas moulard
##

r=`uname -s`

cd .. && make && cd tests

n_echec=0
for l in `ls *.in`; do
    test=`echo "$l" | sed 's/\.in$//'`

    echo '------------------------------'
    echo "* Test '$test'"

    echo '1/ Verification'
    if [ -r "$test.in" ]; then
	echo -n ""
    else
	echo "ERREUR: fichier d'entree introuvable."
	exit 1
    fi
    if [ -r "$test.out" ]; then
	echo -n ""
    else
	echo "ERREUR: fichier de sortie introuvable."
	exit 1
    fi
    if [ -r "$test.ret" ]; then
	echo -n ""
    else
	echo "ERREUR: fichier de retour introuvable."
	exit 1
    fi

    echo "2/ Execution"
    make "$test"
    ./test > /dev/null 2> /dev/null
    result=`echo "$?"`

    if [ "$result" = `cat "$test.ret"` ]; then
	echo "TEST REUSSI"
    else
	echo "ERREUR: echec du test (fichiers de retour differents)"
	    n_echec=$(($n_echec+1))
    fi
done

rm -f README.TXT

echo ''
echo ''
echo '------------------------------'
echo ''
if [ "$n_echec" -eq 0 ]; then
    echo 'Tous les tests ont reussi.'
else
    echo "ECHEC: certains tests ont echoue : $n_echec erreur(s)."
fi
exit "$n_echec"