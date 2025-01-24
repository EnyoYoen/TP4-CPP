#include "Reader.h"

int main() {
    Reader reader("anonyme.log", "court.dot", /*"08/Sep/2012:11:37:00 +0200"*/ string(), true);
    reader.readRequests();
    reader.writeGraph();

    return 0;
} 