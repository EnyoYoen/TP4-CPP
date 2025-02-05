//---------- Réalisation de la classe <Reader> (fichier Reader.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Reader.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeur - destructeur

// Constructeur 
Reader::Reader(const string &filename, const string &fromReferer, const string &toRessource, const string &start, int hour, bool exclude)
	: graph(fromReferer, toRessource, start, hour, exclude), filename(filename) {} //----- Fin de Méthode


// Destructeur
Reader::~Reader() 
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Reader>" << endl;
#endif
} //----- Fin de Méthode


//-------------------------------------------- Autres méthodes

void Reader::readRequests()
// Algorithme :
//
{
	// Ouvre le fichier et génère le graphe
	ifstream file(filename);
	if (!file.is_open())
	{
		throw runtime_error("Could not open file");
	}

	if (file.peek() == ifstream::traits_type::eof())
	{
		throw runtime_error("File is empty");
	}

	string line;
	while (getline(file, line))
	{
		graph.unmarshalRequest(line);
	}

	file.close();
} //----- Fin de Méthode



void Reader::writeGraph(const string &out)
// Algorithme :
//
{
	// Affiche les 10 ressources les plus demandées
	list<Hits> hits = graph.getMostHitResources();

	int count = 0;
	for (const Hits &hit : hits)
	{
		count++;
		cout << hit.first << " (" << hit.second << " hits)" << endl;

		if (count == 10)
		{
			break;
		}
	}

	if (!out.empty())
	{
		// Ecrit le graphe au format .dot dans un fichier
		writeGraphToFile(out);
	}
} //----- Fin de Méthode


//----------------------------------------------------------------- PRIVE

//----------------------------------------------------- Méthode privée

void Reader::writeGraphToFile(const string &out)
// Algorithme :
//
{
	// Ecrit le graphe au format .dot dans un fichier
	ofstream file(out);
	if (!file.is_open())
	{
		throw runtime_error("Could not open file");
	}

	file << graph;

	file.close();
}  //----- Fin de Méthode