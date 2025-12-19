#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// class za node od trie (mora nekako da E)
class TrieNode {
public:
    bool endofWord;
    TrieNode* children[26];

    // konstruktor za inicijalizacija na trie node (why not)
    TrieNode()
    {
        endofWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

// klasa za implimentacija na trie
class Trie {
private:
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }  //weeee (ovaj komentar nema pricina za postoenje)

    // Func za dodavanje na zbor vo trie
    void insert(const string& word)
    {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->endofWord = true;
    }

    // Func za proveruvanje na zbor
    bool search(const string& word)
    {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return node->endofWord;
    }

    // Func za proverka na prifix na zbor (bara zbor)
    bool startsWith(const string& prefix)
    {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }

    // Funk za brishenje zbor or trie
    void deleteWord(const string& word)
    {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return;
            }
            node = node->children[index];
        }
        if (node->endofWord == true) {
            node->endofWord = false;
        }
    }

    // Funk za printanje  (demonstracija, ne e practicno za 100k words)
    void print(TrieNode* node, string prefix) const
    {
        if (node->endofWord) {
            cout << prefix << endl;
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                print(node->children[i],
                      prefix + char('a' + i));
            }
        }
    }

    // Printaj od root
    void print() const { print(root, ""); }
};

int main()
{
    // Neka Trie
    Trie trie;

   //File
    ifstream file("100k_english_words.txt"); //File so zborovi (ima mn za da se tuka)
    string word;

    if (file.is_open()) {
        int wordCount = 0;
        while (getline(file, word) && wordCount < 100000) {
            // converzija vo lowercase za *consistency*
            for (char& c : word) {
                c = tolower(c);
            }
            trie.insert(word);
            wordCount++;
        }
        file.close();
        cout << "Loaded " << wordCount << " words into the Trie." << endl;//->
        // -> File Loaded successfully(yippee )
    } else {
        cerr << "Unable to open file." << endl; //->
        //-> ako ima proble (failsafe za ne cekanje)
        return 1;
    }


////////////////////////// ZA DR. ZBOROVI MENUVAJ PODOLU -->


    // Pr.
    cout << "Baraj 'the': " << trie.search("the") << endl;
    cout << "Baraj 'algorithm': " << trie.search("algorithm") << endl;
    cout << "Pocnuva so 'al': " << trie.startsWith("al") << endl;

    return 0;
}
