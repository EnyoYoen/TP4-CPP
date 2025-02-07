//---------- Interface de la classe <Reader> (fichier Reader.h) ----------------

#ifndef READER_H
#define READER_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>

//------------------------------------------------------ Include personnel
#include "Graph.h"



//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Reader>
// Cette classe permet de gérer toutes les opérations de fichiers et de générer le graphe associé.
//------------------------------------------------------------------------

class Reader
{
//----------------------------------------------------------------- PUBLIC
public:

//----------------------------------------------------- Méthodes publiques
    void writeGraph(const string &out);
    // Mode d'emploi :
    //  Cette méthode affiche les 10 ressources les plus demandées dans la console 
    //  si un chemin de fichier out est fourni, génère le fichier au format .dot 
    // Contrat :
    //

    void readRequests();
    // Mode d'emploi :
    //  Ouvre un fichier spécifié par l'attribut filename, lit chaque ligne et l'ajoute au graphe en appelant unmarshalRequest() pour chaque ligne
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Reader(const string &filename, const string &fromReferer, const string &toRessource, const string &start = string(), int hour = -1, bool exclude = false);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Reader();
    // Mode d'emploi :
    //
    // Contrat :
    //

    
//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privée
    void writeGraphToFile(const string &out);
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs privées
    Graph graph;
    string filename;
    string out;
};

//-------------------------------- Autres définitions dépendantes de <Reader>

#endif // READER_H