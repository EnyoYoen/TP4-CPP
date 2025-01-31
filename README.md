# TP C++ n°4

## Analyse de logs apache

Binômes:

- B3212: Yoen PEYROT, William MICHAUD
- B3210: Leo MARNAS, Clement JAQUIER

### Utilisation

Le programme s'exécute différemment en fonction des paramètres de la ligne de commande:

- Sans paramètres

Par défaut, c’est-à-dire quand il n’y a aucune option, il affichera sur la console sous forme textuelle la liste des 10 documents les plus consultés par ordre décroissant de popularité. Aucun fichier “.dot” n’est généré dans ce cas.

- `-g nomfichier.dot`

Cette option permet de produire un fichier au format GraphViz du graphe analysé. Chaque document apparaîtra sous la forme d’un nœud et chaque arc indiquera le nombre de parcours associés.

- `-e`

Cette option permet d’exclure tous les documents qui ont une extension de type image, css ou javascript.

- `-t heure`

Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire [heure, heure+1[, pour chaque jour.

- `-d CLF`

Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire correspondant à l’intervalle [CLF, CLF + 1 heure].
Exemple : -d 08/Sep/2012:11:16:02

- `-r referer`

Cette option permet de ne prendre en compte que les hits qui viennent du referer en paramètre.

- `-s ressource`

Cette option permet de ne prendre en compte que les hits qui touchent la ressource en paramètre.

### Génération du graphe

Afin de générer le graphe, nous avons utilisé un [Google Colab](https://colab.research.google.com/drive/1majZD5knMa9tQFhNKNB2k5eNkj9B504m?usp=sharing), qui permet de générer l'image beaucoup plus rapidement que sur nos machines personnelles.

### Vérification des requêtes

Nous avons fait des vérifications lors du parsing de chaque ligne du fichier log (dans les fichiers Request et DateTime) afin de détecter des lignes invalides, en levant des exceptions. Si une ligne du fichier log est invalide, un message d'erreur est affiché sur `cerr` mais l'execution du programme continue en ignorant la requête.
