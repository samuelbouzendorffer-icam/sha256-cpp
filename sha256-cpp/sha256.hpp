// sha256.hpp : implémentation pédagogique de SHA-256 (FIPS 180-4), sans dépendance.
// Pour un vrai projet, utilisez une bibliothèque éprouvée (OpenSSL, libsodium...).
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

class SHA256 {
public:
    SHA256();
    void update(const std::uint8_t* data, std::size_t length);
    void update(const std::string& text);
    // Termine le calcul et retourne l'empreinte en hexadécimal (64 caractères).
    // Après cet appel, l'objet ne doit plus être utilisé.
    std::string hexdigest();

private:
    void process_block(const std::uint8_t* block);

    std::array<std::uint32_t, 8> state_;
    std::array<std::uint8_t, 64> buffer_;
    std::size_t buffer_len_;
    std::uint64_t total_bytes_;
};

std::string sha256_hex(const std::string& text);
