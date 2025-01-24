#include "Reader.h"
#include <string.h>

int showHelp(char* exec_path) {
	std::cerr << "Usage: " << exec_path << " [options] <nomfichier.log>" << std::endl;
	std::cerr << "Options:" << std::endl;
	std::cerr << "  -g <nomfichier.dot> : génère un fichier au format GraphViz" << std::endl;
	std::cerr << "  -e : exclut les documents de type 'image', 'css' et 'js'" << std::endl;
	std::cerr << "  -t <heure> : ne prend en compte que les requêtes sur l'intervalle [heure, heure+1[" << std::endl;
	std::cerr << "  -h : affiche ce message d'aide" << std::endl;

	return 1;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		return showHelp(argv[0]);
	}

	string inputFile = argv[argc - 1];
	// Parse options

	bool excludeMeta = false;

	int timeLimit = -1;

	bool makeGraph = false;
	string graphOutput = string();

	int i = 1;
	while(i<argc-1){
		if (strncmp(argv[i], "-e", 3) == 0){
			if (excludeMeta) {
				return showHelp(argv[0]);
			}

			excludeMeta = true;
			i++;
		} else if (strncmp(argv[i], "-g", 3) == 0){
			if (makeGraph) {
				return showHelp(argv[0]);
			}

			makeGraph = true;
			graphOutput = argv[i+1];
			i+=2;
		} else if (strncmp(argv[i], "-t", 3) == 0){
			if (timeLimit != -1) {
				return showHelp(argv[0]);
			}

			try {
				timeLimit = std::stoi(argv[i+1]);
			} catch (const std::invalid_argument&) {
				std::cerr << "Heure invalide: " << argv[i+1] << std::endl;
				return showHelp(argv[0]);
			}

			if (timeLimit < 0 || timeLimit > 23) {
				std::cerr << "Heure invalide: " << argv[i+1] << std::endl;
				return showHelp(argv[0]);
			}

			i+=2;
		} else {
			return showHelp(argv[0]);
		}
	}

	Reader reader(inputFile, timeLimit, excludeMeta);

	try {
		reader.readRequests();
		reader.writeGraph(graphOutput);
	} catch (const std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
		return showHelp(argv[0]);
	}

	return 0;
} 