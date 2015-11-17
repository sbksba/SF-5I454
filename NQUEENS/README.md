README
======

Nqueens.c
---------

Programme permettant de generer le fichier cnf correspondant au probleme des
N reines.

> prend en parametre la taille de la grille

format.pl
---------

Script permettant de modeliser de facon graphique la solution rendu par le
solveur minitsat.

> prend en parametre le fichier solution ainsi que la taille

Exemple pour 8 reines
---------------------

login@: ./Nqueens 8                     (generation du fichier 8queens.cnf)     
login@: ./minisat 8queens.cnf 8Sol.txt  (generation du fichier 8Sol.txt)     
login@: ./format.pl 8Sol.txt 8

## Licence

(Licence MIT)

Copyright © 2015 sbksba

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
