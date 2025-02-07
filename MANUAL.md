# NOM

    analog: Traite des fichiers de logs Apache

# RESUME

    analog [options] <nomFichier.log>

# DESCRIPTION

    analog est un outil de traitement de fichiers de logs Apache. Cet outil permet de générer un graphe des visites des utilisateurs.

# EXEMPLES

- Sans options, permet d'afficher les 10 documents les plus consultés:

  ```
  bin/analog <nomFichier.log>
  ```

- Pour lancer analog avec des options:
  ```
  bin/analog -param1 -param2 <fichierParam2> <nomFichier.log>
  ```

## Options disponibles

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

- `-d CLF`

Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire
correspondant à l’intervalle [CLF, CLF + 1 heure].
Exemple : -d 08/Sep/2012:11:16:02

- `-r referer`

Cette option permet de ne prendre en compte que les hits qui viennent du referer en paramètre.

- `-s ressource`

Cette option permet de ne prendre en compte que les hits qui touchent la ressource en paramètre.

# VOIR AUSSI

- `apache`

# BUGS

Aucun bug connu, merci de signaler tout bug rencontré aux développeurs

# AUTEURS

    - B3212: Yoen PEYROT, William MICHAUD
    - B3210: Leo MARNAS, Clement JAQUIER

# COPYRIGHT

    © 2025 Yoen.site - All rights reserved.
