# sha256-cpp

Implémentation de **SHA-256** (FIPS 180-4) écrite à la main en **C++17**, sans dépendance, avec un équivalent simplifié de la commande `sha256sum`.

Projet pédagogique pour comprendre le fonctionnement interne d'une fonction de hachage. Pour un vrai projet, on utilise une bibliothèque éprouvée (OpenSSL, libsodium...).

## Compilation et utilisation

```bash
make              # construit sha256sum_cpp et test_sha256
make test         # lance les tests
./sha256sum_cpp fichier.txt
echo -n "bonjour" | ./sha256sum_cpp
```

Pour comparer avec l'outil du système : `sha256sum fichier.txt` (Linux) ou `shasum -a 256 fichier.txt` (macOS). Les empreintes sont identiques.

## Contenu

| Fichier | Rôle |
|---|---|
| `sha256.hpp` / `sha256.cpp` | classe `SHA256` (`update`, `hexdigest`) |
| `main.cpp` | lecture de fichiers ou de l'entrée standard, par blocs de 64 Kio |
| `test_sha256.cpp` | tests avec les vecteurs officiels du NIST |
| `Makefile` | compilation avec `-Wall -Wextra -Wpedantic` |

## Concepts illustrés

- **Bourrage** (*padding*) : ajout d'un bit à 1, de zéros, puis de la longueur du message sur 8 octets pour obtenir des blocs de 512 bits.
- **Découpage en blocs** de 64 octets et traitement en flux : `update()` peut être appelé plusieurs fois, y compris avec des morceaux de tailles quelconques.
- **Extension du message** (64 mots de 32 bits), rotations de bits et fonctions `Ch` et `Maj`.
- Arithmétique modulo 2³² avec des entiers non signés de 32 bits, et conversion en gros-boutiste (*big-endian*).
- Lecture d'un fichier binaire par blocs, sans le charger entièrement en mémoire.

## Tests

`make test` vérifie notamment :

- la chaîne vide, `abc`, le message de 56 octets du NIST et le million de `a` ;
- les longueurs autour de la limite de bourrage (55, 56, 63, 64 et 65 octets), classiques sources de bugs ;
- l'équivalence entre un `update` unique et plusieurs `update` successifs.

## Limites

Code volontairement lisible plutôt qu'optimisé. Il n'est pas prévu pour du matériel sensible aux attaques par canaux auxiliaires, et SHA-256 seul ne convient pas pour stocker des mots de passe (voir [password-hashing-demo](https://github.com/samuelbouzendorffer-icam/password-hashing-demo)).

## Pistes d'amélioration

- Ajouter SHA-512 et HMAC-SHA256.
- Mesurer les performances face à `sha256sum`.
- Tester contre les fichiers de vecteurs complets du NIST (CAVP).
- Compiler avec les *sanitizers* (`-fsanitize=address,undefined`).

## Licence

MIT, voir [LICENSE](LICENSE).

---

*Réalisé avec l'aide de Claude (IA), relu et testé par l'auteur.*
