#include "Reader.h"
#include "DateTime.h"

#include <string.h>

using namespace std;

int showHelp(char *exec_path)
{
	// Affiche l'aide
	cerr << "Usage: " << exec_path << " [options] <nomfichier.log>" << endl;
	cerr << "Options:" << endl;
	cerr << "  -g <nomfichier.dot> : génère un fichier au format GraphViz" << endl;
	cerr << "  -e : exclut les documents de type 'image', 'css' et 'js'" << endl;
	cerr << "  -t <heure> : ne prend en compte que les requêtes sur l'intervalle [heure, heure+1[ pour chaque jour" << endl;
	cerr << "  -d <CLF> : ne prend en compte que les requêtes sur l'intervalle [CLF, CLF+1[" << endl;
	cerr << "  -r <referer> : ne prend en compte que les requêtes provenant de <referer>" << endl;
	cerr << "  -s <ressource> : ne prend en compte que les requêtes vers <ressource>" << endl;
	cerr << "  -h : affiche ce message d'aide" << endl;

	return 1;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		return showHelp(argv[0]);
	}
	// Parse options

	bool excludeMeta = false;

	int timeLimit = -1;
	string timeLimitStr = string();

	bool makeGraph = false;
	string graphOutput = string();

	string fromReferer = string();
	string toRessource = string();

	int i = 1;
	while (i < argc - 1)
	{
		if (strncmp(argv[i], "-e", 3) == 0)
		{
			// Paramètre '-e'
			if (excludeMeta)
			{
				return showHelp(argv[0]);
			}

			excludeMeta = true;
			i++;
		}
		else if (strncmp(argv[i], "-g", 3) == 0)
		{
			// Paramètre '-g'
			if (makeGraph)
			{
				return showHelp(argv[0]);
			}

			makeGraph = true;
			graphOutput = argv[i + 1];
			i += 2;
		}
		else if (strncmp(argv[i], "-t", 3) == 0)
		{
			// Paramètre '-t'
			if (timeLimit != -1)
			{
				return showHelp(argv[0]);
			}

			try
			{
				timeLimit = stoi(argv[i + 1]);
			}
			catch (const invalid_argument &)
			{
				cerr << "Heure invalide: " << argv[i + 1] << endl;
				return showHelp(argv[0]);
			}

			if (timeLimit < 0 || timeLimit > 23)
			{
				cerr << "Heure invalide: " << argv[i + 1] << endl;
				return showHelp(argv[0]);
			}

			i += 2;
		}
		else if (strncmp(argv[i], "-d", 3) == 0)
		{
			// Paramètre -d : spécifie une date au format CLF et regarde dans l'intervalle
			const char *clf = argv[i + 1];
			if (!DateTime::isDateTimeCorrect(string(clf)))
			{
				cerr << "Date invalide: " << clf << endl;
				return showHelp(argv[0]);
			}

			timeLimitStr = clf;

			i += 2;
		}
		else if (strncmp(argv[i], "-r", 3) == 0)
		{
			// Paramètre '-r'
			if (!fromReferer.empty())
			{
				return showHelp(argv[0]);
			}

			fromReferer = argv[i + 1];

			i += 2;
		}
		else if (strncmp(argv[i], "-s", 3) == 0)
		{
			// Paramètre '-s'
			if (!toRessource.empty())
			{
				return showHelp(argv[0]);
			}

			toRessource = argv[i + 1];

			i += 2;
		}
		else
		{
			// Tout le reste (y compris le paramètre '-h' :)
			return showHelp(argv[0]);
		}
	}

	if (i != argc - 1)
	{
		return showHelp(argv[0]);
	}
	string inputFile = argv[argc - 1];

	Reader reader(inputFile, fromReferer, toRessource, timeLimitStr, timeLimit, excludeMeta);

	try
	{
		reader.readRequests();
		reader.writeGraph(graphOutput);
	}
	catch (const runtime_error &e)
	{
		cerr << "Runtime error: " << e.what() << endl;
		return showHelp(argv[0]);
	}

	return 0;
}