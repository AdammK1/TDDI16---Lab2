#include <iostream>
#include <chrono>
#include <string>
#include "key.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:" << endl;
        cout << argv[0] << " <hashed password> < rand8.txt" << endl;
        return 1;
    }

    // Hashed password.
    Key hashed{argv[1]};

    // Table.
    Key table[N];

    // Read table.
    for (int i{0}; i < N; i++) {  // Ittererar 25 gånger, eftersom char_in_pass==5 & bits_in_char == 5 --> N = 5*5=25
        string buffer;
        if (!(cin >> buffer)) {                     // Om vi inte har korrekt N = C * B är table för liten!
            cerr << "Too short table!" << endl;
            return 1;
        }
        table[i] = Key{buffer.c_str()}; //Lägger varje ord från easy5.txt nycklat till en siffra 1..25.
    }

    auto begin = chrono::high_resolution_clock::now();

    // Try all possible subsets of T.
    Key candidate{};
    Key zero{};
    do {
        Key enc = subset_sum(candidate, table);
        if (enc == hashed)
            cout << candidate << endl;
        ++candidate;
    } while (candidate != zero);

    auto end = chrono::high_resolution_clock::now();
    cout << "Decryption took "
         << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
         << " seconds." << endl;

    return 0;
}
