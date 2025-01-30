#include "Reader.h"

#include <fstream>

Reader::Reader(const string &filename, const string &start, int hour, bool exclude)
	: graph(start, hour, exclude), filename(filename) {} // Constructeur


void Reader::readRequests()
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
}

void Reader::writeGraph(const string &out)
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
}

void Reader::writeGraphToFile(const string &out)
{
	// Ecrit le graphe au format .dot dans un fichier
	ofstream file(out);
	if (!file.is_open())
	{
		throw runtime_error("Could not open file");
	}

	file << graph;

	file.close();
}