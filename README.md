# TP C++ n°4
## Analyse de logs apache

Binômes:
- B3212: Yoen PEYROT, William MICHAUD
- B3210: Leo MARNAS, Clement JAQUIER

### Utilisation

Le programme s'exécute différemment en fonction des paramètres de la ligne de commande:

- Sans paramètres

Par défaut, c’est-à-dire quand il n’y a aucune option, il affichera sur la console sous forme textuelle
la liste des 10 documents les plus consultés par ordre décroissant de popularité. Aucun fichier
“.dot” n’est généré dans ce cas. 

- `-g nomfichier.dot`

Cette option permet de produire un fichier au format GraphViz du graphe analysé. Chaque
document apparaîtra sous la forme d’un nœud et chaque arc indiquera le nombre de parcours
associés.

- `-e`

Cette option permet d’exclure tous les documents qui ont une extension de type image, css ou
javascript.

- `-t heure`

Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire
correspondant à l’intervalle [heure, heure+1[.

### Génération du graphe

Afin de générer le graphe, nous avons utilisé un [Google Colab](https://colab.research.google.com/drive/1majZD5knMa9tQFhNKNB2k5eNkj9B504m?usp=sharing), qui permet de générer l'image beaucoup plus rapidement que sur nos machines personnelles.

![Alt Text](https://static.printler.com/cache/c/4/1/7/d/c/c417dc9c0acfba8b61c6a40e81636b953e9a5566.jpg)
