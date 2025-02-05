//---------- Réalisation de la classe <Graph> (fichier Graph.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>


//------------------------------------------------------ Include personnel
#include "Graph.h"


//------------------------------------------------------------- Constantes


//----------------------------------------------------------------- Fonction comparaison
bool sortHits(const Hits &a, const Hits &b)
// Algorithme :
//
{
	// Compare deux hits pour les trier
	return a.second > b.second;
} //----- Fin de Fonction

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Constructeurs - destructeur

//-------------------------------------------- Constructeur
Graph::Graph(const string &fromReferer, const string &toRessource, const string &start, int hour, bool exclude)
// Algorithme :
//
	: fromReferer(fromReferer), toRessource(toRessource), exclude(exclude), hour(hour), nextVertexId(0)
{
	#ifdef MAP
    cout << "Appel au constructeur de <Graph>" << endl;
	#endif

	if (!start.empty())
	{
		istringstream iss(start);
		iss >> this->start;
		startSet = true;
	}
	else
	{
		startSet = false;
	}
} //----- Fin de Méthode

//-------------------------------------------- Destructeur
Graph::~Graph()
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel au destructeur de <Graph>";
	#endif
} //----- Fin de Méthode


//----------------------------------------------------- Méthodes publiques
void Graph::unmarshalRequest(const string &rawRequest)
// Algorithme :
//
{
	#ifdef MAP
    cout << "Appel a la methode unmarshalRequest" << endl;
	#endif
	// Ajoute une requete au graphe

	try
	{
		// Extrait les informations de la requete
		Request req;
		istringstream iss(rawRequest);
		iss >> req;

		if (isExtensionExcluded(req.resource) || isTimeExcluded(req.infos.dateTime) || isStatusCodeCorrect(req.infos.statusCode) || !isRefererCorrect(req.infos.referer) || !isRessourceCorrect(req.resource))
		{
			return;
		}

		const string &source = getSourceFromReferer(req.infos.referer);
		const string &resource = trimOptions(req.resource);

		// Ajoute les sommets et les arcs
		if (vertices.find(source) == vertices.end())
		{
			reverseVertices[nextVertexId] = source;
			vertices[source] = nextVertexId++;
		}
		if (vertices.find(resource) == vertices.end())
		{
			reverseVertices[nextVertexId] = resource;
			vertices[resource] = nextVertexId++;
		}

		int sourceId = vertices[source];
		int resourceId = vertices[resource];

		// Ajoute l'arc / edge
		if (edges.find(resourceId) == edges.end())
		{
			edges[resourceId] = unordered_map<int, int>();
		}
		unordered_map<int, int> resourceMap = edges[resourceId];

		// Incrémente le nombre de hits
		if (resourceMap.find(sourceId) == resourceMap.end())
		{
			resourceMap[sourceId] = 1;
		}
		else
		{
			resourceMap[sourceId] += 1;
		}

		edges[resourceId] = resourceMap;
	}
	catch (const runtime_error &e)
	{
		cerr << "Invalid Request (may be incorrect: " << e.what() << "): " << rawRequest << endl;
	}
} //----- Fin de Méthode

list<Hits> Graph::getMostHitResources() const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode getMostHitResources";
	#endif
	// Retourne les 10 ressources les plus demandées

	unordered_map<string, int> hits;

	for (const EdgeMap &edge : edges)
	{
		for (const Edge &edge2 : edge.second)
		{
			const string &hit = reverseVertices.at(edge.first);
			if (hits.find(hit) == hits.end())
			{
				hits[hit] = edge2.second;
			}
			else
			{
				hits[hit] += edge2.second;
			}
		}
	}

	list<Hits> result;
	for (const Hits &hit : hits)
	{
		result.push_back(Hits(hit.first, hit.second));
	}

	result.sort(sortHits);

	return result;
} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs
ostream &operator<<(ostream &os, const Graph &graph)
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la surcharge de l'operateur <<";
	#endif
	// Permet de generer le graphe au format .dot

	os << "digraph {" << endl;
	os << "layout = fdp;" << endl; // Le layout qui marche le mieux pour le rendering
	for (const Vertex &vertex : graph.vertices)
	{
		os << "node" << vertex.second << " [label=\"" << vertex.first << "\"];" << endl;
	}
	for (const EdgeMap &edge : graph.edges)
	{
		for (const Edge &edge2 : edge.second)
		{
			os << "node" << edge2.first << " -> node" << edge.first << " [label=\"" << edge2.second << "\"];" << endl;
		}
	}
	os << "}" << endl;

	return os;
} //----- Fin de Méthode


//----------------------------------------------------------------- PRIVE
//----------------------------------------------------- Méthodes privées

const string Graph::getSourceFromReferer(const string &referer) const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode getSourceFromReferer";
	#endif

	// Extrait la source de la requete referer

	size_t last = referer.find_last_of('/');
	string source = referer.substr(last == string::npos ? 0 : last, referer.size());
	return trimOptions(source);
} //----- Fin de Méthode

const string Graph::trimOptions(const string &address) const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode trimOptions";
	#endif

	// Extrait l'adresse sans les options

	size_t option = address.find_first_of('?');
	string trimmedAddress = address.substr(0, option == string::npos ? address.size() : option);
	size_t jsessionid = address.find(";jsessionid");
	return trimmedAddress.substr(0, (jsessionid == string::npos) != 0 ? trimmedAddress.size() : jsessionid);
} //----- Fin de Méthode

bool Graph::isExtensionExcluded(const string &resource) const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode isExtensionExcluded";
	#endif

	// Exclut les ressources de type 'image', 'css' et 'js'

	bool result = false;

	if (exclude)
	{
		size_t last = resource.find_last_of('.');
		if (last != string::npos)
		{
			const string extension = resource.substr(resource.find_last_of('.'));
			if (extension == ".css" || extension == ".js" || extension == ".png" || extension == ".jpg" || extension == ".gif" || extension == ".ico")
			{
				return true;
			}
		}
	}

	return result;
} //----- Fin de Méthode

bool Graph::isTimeExcluded(const DateTime &dt) const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode isTimeExcluded";
	#endif

	bool result = false;

	// Exclut les requetes qui ne sont pas dans l'intervalle [heure, heure+1[
	if (hour != -1 && dt.getHour() != hour)
	{
		result = true;
	}

	// Exclut les requetes qui ne sont pas dans l'intervalle [clf, clf + 1 heure]
	if (startSet)
	{
		ll seconds = dt.secondsBetween(start);
		result = seconds < 0 || seconds > 3600;
	}

	return result;
} //----- Fin de Méthode

bool Graph::isStatusCodeCorrect(const int code) const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode isStatusCodeCorrect";
	#endif

	return !(code >= 200 && code < 400);
} //----- Fin de Méthode

bool Graph::isRefererCorrect(const string &referer) const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode isRefererCorrect";
	#endif

	return fromReferer.empty() || referer == fromReferer;
} //----- Fin de Méthode

bool Graph::isRessourceCorrect(const string &ressource) const
// Algorithme :
//
{
	#ifdef MAP
	cout << "Appel a la methode isRessourceCorrect";
	#endif

	return toRessource.empty() || ressource == toRessource;
} //----- Fin de Méthode