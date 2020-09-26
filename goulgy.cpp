#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

vector <string> SplitInToWords(const string& text) {
	vector <string> words;
	string word;
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == ' ') {
			words.push_back(word);
			word = ""s;
		}
		else {
			word += text[i];
		}
	}
	words.push_back(word);
	return words;
}

set <string> ParseStopWords(const string& text) {
	set <string> stop_set;
	for (const string& word : SplitInToWords(text)) {
		stop_set.insert(word);
	}
	return stop_set;
}

vector <string> SplitInToWordsNoStop(const string& text, set <string> stop_words) {
	vector <string> words;
	for (const string& word : SplitInToWords(text)) {
		if (stop_words.count(word) == 0) {
			words.push_back(word);
		}
	}
	return words;
}

string ReadLine() {
	string s;
	getline(cin, s);
	return s;
}

int ReadLineNumber() {
	int result;
	cin >> result;
	ReadLine();
	return result;
}

void AddDocument(map <string, set <int>>& word_to_documents, const set <string>& stop_words, int doc_id, const string& document) {
	for (const string& word : SplitInToWordsNoStop(document, stop_words)) {
		word_to_documents[word].insert(doc_id);
	}
}

vector <pair <int, int>> FindDocuments(map <string, set <int>>& word_to_documents, const set <string>& stop_words, const string& query) {
	const vector <string> query_words = SplitInToWordsNoStop(query, stop_words);
	map <int, int> doc_ids;
	for (const string& word : query_words) {
		if (word_to_documents.count(word) == 0) {
			continue;
		}
		for (const int& doc_id : word_to_documents.at(word)) {
			++doc_ids[doc_id];
		}
	}
	vector <pair <int, int>> found_documet;
	for (auto [doc_id, relevantse] : doc_ids) {
		found_documet.push_back({doc_id, relevantse});
	}
	return found_documet;
}

int main() {
	setlocale(LC_ALL, "Russia");
	const string stop_words_join = ReadLine();
	set <string> stop_words = ParseStopWords(stop_words_join);

	//Read Document
	map <string, set <int>> word_to_documents;
	const int doc_count = ReadLineNumber();
	for (int documet_id = 0; documet_id < doc_count; ++documet_id) {
		AddDocument(word_to_documents, stop_words, documet_id, ReadLine());
	}
	const string query = ReadLine();
	for (auto [doc_id, relevantse] : FindDocuments(word_to_documents, stop_words, query)) {
		cout << "doc_id = " << doc_id << endl << "relevantse = " << relevantse << endl;
	}
}