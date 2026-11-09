// Tests de SHA-256 avec les vecteurs officiels du NIST (FIPS 180-4 / CAVP).
#include <iostream>
#include <string>

#include "sha256.hpp"

static int failures = 0;

static void check(const std::string& name, const std::string& got, const std::string& expected) {
    if (got == expected) {
        std::cout << "[OK]     " << name << '\n';
    } else {
        std::cout << "[ECHEC]  " << name << "\n  obtenu  : " << got << "\n  attendu : " << expected << '\n';
        ++failures;
    }
}

int main() {
    check("chaine vide", sha256_hex(""),
          "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    check("abc", sha256_hex("abc"),
          "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    check("56 octets (bourrage sur deux blocs)",
          sha256_hex("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
          "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");

    // Un million de 'a', envoyé par petits morceaux pour tester update() en plusieurs fois.
    SHA256 million;
    const std::string chunk(1000, 'a');
    for (int i = 0; i < 1000; ++i) million.update(chunk);
    check("un million de 'a' (en morceaux)", million.hexdigest(),
          "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");

    // Tailles autour de la limite de bourrage (55, 56, 63, 64, 65 octets) : cas classiques de bug.
    check("55 fois 'a'", sha256_hex(std::string(55, 'a')),
          "9f4390f8d30c2dd92ec9f095b65e2b9ae9b0a925a5258e241c9f1e910f734318");
    check("56 fois 'a'", sha256_hex(std::string(56, 'a')),
          "b35439a4ac6f0948b6d6f9e3c6af0f5f590ce20f1bde7090ef7970686ec6738a");
    check("63 fois 'a'", sha256_hex(std::string(63, 'a')),
          "7d3e74a05d7db15bce4ad9ec0658ea98e3f06eeecf16b4c6fff2da457ddc2f34");
    check("64 fois 'a'", sha256_hex(std::string(64, 'a')),
          "ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb");
    check("65 fois 'a'", sha256_hex(std::string(65, 'a')),
          "635361c48bb9eab14198e76ea8ab7f1a41685d6ad62aa9146d301d4f17eb0ae0");

    SHA256 piecewise;
    piecewise.update("The quick brown fox ");
    piecewise.update("jumps over the lazy dog");
    check("update en deux fois = update en une fois", piecewise.hexdigest(),
          sha256_hex("The quick brown fox jumps over the lazy dog"));
    check("The quick brown fox...", sha256_hex("The quick brown fox jumps over the lazy dog"),
          "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");

    std::cout << (failures == 0 ? "\nTous les tests passent.\n" : "\nDes tests ont échoué.\n");
    return failures == 0 ? 0 : 1;
}
