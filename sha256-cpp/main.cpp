// main.cpp : équivalent simplifié de la commande `sha256sum`.
// Usage : ./sha256sum_cpp fichier1 [fichier2 ...]   (sans argument : lit l'entrée standard)
#include <fstream>
#include <iostream>
#include <vector>

#include "sha256.hpp"

namespace {

// Lit un flux par blocs de 64 Kio : fonctionne pour de gros fichiers sans les charger en mémoire.
std::string hash_stream(std::istream& in) {
    SHA256 hasher;
    std::vector<char> chunk(64 * 1024);
    while (in.read(chunk.data(), static_cast<std::streamsize>(chunk.size())) || in.gcount() > 0) {
        hasher.update(reinterpret_cast<const std::uint8_t*>(chunk.data()),
                      static_cast<std::size_t>(in.gcount()));
    }
    return hasher.hexdigest();
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << hash_stream(std::cin) << "  -\n";
        return 0;
    }
    int status = 0;
    for (int i = 1; i < argc; ++i) {
        std::ifstream file(argv[i], std::ios::binary);
        if (!file) {
            std::cerr << "Erreur : impossible d'ouvrir " << argv[i] << '\n';
            status = 1;
            continue;
        }
        std::cout << hash_stream(file) << "  " << argv[i] << '\n';
    }
    return status;
}
