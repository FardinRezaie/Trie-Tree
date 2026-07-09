#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int number = 26;

struct TrieNode {
	TrieNode* children[number];
	string meaning;
	bool _$ = false;

	TrieNode(){
		for (int i = 0; i < number; ++i)
			children[i] = nullptr;
	}
};

class Trie {
private:
	TrieNode* root;

public:
	Trie() {
		root = new TrieNode();
	}

	void insert(const string& word, const string& meaning) {
		TrieNode* node = root;
		int size = word.length();
		for (int i = 0; i < size;i++) {
			int index = word[i] - 'a';
			if (node->children[index] == nullptr) {
				node->children[index] = new TrieNode();
			}
			node = node->children[index];
		}
		node->_$ = true;
		node->meaning = meaning;
	}

	string search(const string& word) {
		TrieNode* node = root;
		int size = word.length();
		for (int i = 0; i < size; i++) {
			int index = word[i] - 'a';
			if (node->children[index] == nullptr) {
				return "";
			}
			node = node->children[index];
		}
		if (node->_$) {
			return node->meaning;
		}
		return "";
	}

	void read_from_file(const string& filename) {
		ifstream inFile(filename);
		string line;
		while (getline(inFile, line)) {
			size_t delimiter = line.find(':');
			if (delimiter != string::npos) {
				string word = line.substr(0, delimiter);
				string meaning = line.substr(delimiter + 1);
				insert(word, meaning);
			}
		}
		inFile.close();
	}
};

void character(string& str)
{
	int i;
	for (i = 0; str[i]; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
}

void menu()
{
	cout << "===================== M E N U ===================== \n";
	//cout << "* Add word[1]." << endl;
	cout << "* Search word[1]." << endl;
	cout << "* Exit[2]." << endl;
	cout << "=================================================== \n";
}

int main()
{
	int n = 0;
	bool bol = true;
	

	Trie trie;
	Trie newTrie;
	string word, mean;
	//................. Do while loop for repetation of main function.
	do {
		menu();
		cout << "Enter the number that you choice: ";
		cin >> n;
		system("cls");
		switch (n)
		{
			//{........ Case one for creating a file.......}
		//case 1:
		//	trie.read_from_file("trie.txt");
		//	cout << "Enter Your Words And Its meaning \n(0 for finish). " << endl;
		//	word = "";
		//	while (word != "0") {
		//		cout << "Enter word: ";
		//		cin >> word;
		//		if (word != "0") {
		//			character(word);
		//			cout << "Enter its mean: ";
		//			cin.ignore();
		//			getline(cin, mean);
		//			// Insert words and meanings
		//			trie.insert(word, mean);
		//		}
		//	}
		//	break;

		case 1:
			// Create a new Trie and desave_to_file from file

			newTrie.read_from_file("trie.txt");

			cout << "Enter a Word that you want to find \n(0 for finish). " << endl;
			word = "";
			while (word != "0") {
				cout << "Enter word: ";
				cin >> word;

				if (word != "0") {
					character(word);
					mean = newTrie.search(word);
					if (mean != "") {
						cout << "Meaning : " << mean << endl;
					}
					else cout << "Word not find" << endl;
				}

			}
			break;
		case 2:
			return 0;
			break;
		}

	} while (bol);
}

