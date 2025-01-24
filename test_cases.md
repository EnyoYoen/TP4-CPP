# Description des cas de tests

| N°  | Commande               | Sortie attendue                                                                                                  |
| --- | ---------------------- | ---------------------------------------------------------------------------------------------------------------- |
| 1   | sans paramètre         | 10 documents les + consultés affichés par ordre décroissant                                                      |
| 2   | -g nom_fichier.dot     | Idem que sans paramètre + fichier GraphViz décrivant le graphe                                                   |
| 3   | -e                     | Idem que sans paramètre + exclusion des documents images, CSS, ou JS                                             |
| 4   | -t heure               | Idem que sans paramètre, n'affiche que les hits dans le créneau horaire heure inclut à heure+1 exclut            |
| 5   | -g -e                  | Idem que sans paramètre + fichier GraphViz, le tout sans les fichiers images, CSS et JS                          |
| 6   | -g -t                  | Idem que sans paramètre + fichier GraphViz, le tout pour heure inclut à heure+1 exclut                           |
| 7   | -e -t                  | Idem que sans paramètre + exclusion des documents images, CSS, ou JS, le tout pour heure inclut à heure+1 exclut |
| 8   | -e -t -g               | 10 documents les + consultés + fichier GraphViz + créneau horaire + exclusion des fichiers images, CSS, JS       |
| 9   | -g SANS NOM DE FICHIER | cerr => message d'erreur                                                                                         |
| 10  | -t HEURE INCOHERANT    | cerr => message d'erreur                                                                                         |
| 11  | Fichier log absent     | cerr => message d'erreur                                                                                         |
## TODO

- test 3 : comment définit-on les images, CSS, JS ? 