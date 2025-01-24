#include "Reader.h"

int main() {
    Reader reader("exemple-mini-non-exhaustif.txt", "court.dot", "08/Sep/2012:11:37:00 +0200", true);
    reader.readRequests();
    reader.writeGraph();

    return 0;
} 