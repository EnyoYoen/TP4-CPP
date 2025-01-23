#include "Reader.h"

int main() {
    Reader reader("exemple-mini-non-exhaustif.txt", "court.dot", string(), true);
    reader.readRequests();
    reader.writeGraph();

    return 0;
} 