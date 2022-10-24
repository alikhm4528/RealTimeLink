#include <iostream>
#include <Main.h>

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Wrong number of arguments.\n";
        exit(1);    
    }
    Main* Program;
    if((std::string)argv[1] == "INTERLEAVING") {
        std::cout << "Interleaving Algorithem\n";
        Program = new Main(INTERLEAVING);
    } else if ((std::string)argv[1] == "HAMMING") {
        std::cout << "Hamming Algorithem\n";
        Program = new Main(HAMMING);
    } else {
        std::cout << "Unknown algorithm.\n";
        exit(1);
    }
    Program->run();

    return 0;
}