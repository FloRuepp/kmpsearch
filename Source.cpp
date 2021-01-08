#include<string>
#include<vector>
#include<iostream>

//A function to nicely format and print all input strings and the calculated kmax vector to console
void print_query(std::string text, std::string patt, std::vector<int> kmax) {
	std::cout << "\nINDEX:\t";
	for (int i = 0; i < text.length(); i++) {
		std::cout << "|" << i << "\t";
	}
	std::cout << "\nTEXT:\t";
	for (char& c : text) {
		std::cout << "|" << c << "\t";
	}
	std::cout << "\nPATT:\t";
	for (char& c : patt) {
		std::cout << "|" << c << "\t";
	}
	std::cout << "\nK-MAX:\t";
	for (int& i : kmax) {
		std::cout << "|" << i << "\t";
	}
	std::cout << std::endl;
}

//this function calculates the kmax vector for the kmp search
std::vector<int> get_kmax(const std::string& patt) {
	//kmax isa vector of integers
	std::vector<int> kmax;
	//kmax must have the same size as the search pattern
	kmax.resize(patt.length());
	int i = 0;
	int j = -1;

	kmax[i] = j;
	while (true) {
		while (j >= 0 && patt[j] != patt[i]) {
			j = kmax[j];
		}
		i++;
		j++;
		if (!(i < patt.length())) {
			break;
		}
		kmax[i] = j;
	}
	return kmax;
}

int kmpsearch(const std::string& text, const std::string& patt) {
	std::vector<int> kmax = get_kmax(patt);
	print_query(text, patt, kmax);

	/////////////////////////////////////////////////////////////////////////////////////
	//This part is basically copied from the lecture slides, except for the addition of "j >= 0" in the while loop!
	int M = patt.length();
	int N = text.length();
	int i, j;
	for (i = 0, j = 0; i < N && j < M; ++i, ++j) {
		while (j >= 0 && text[i] != patt[j] && i < N) {
			j = kmax[j];
		}
	}
	if (j == M) {
		return i - M;
	}
	else {
		return -1;
	}
	/////////////////////////////////////////////////////////////////////////////////////
}


int main() {
	std::string text, patt;
	std::cout << "INPUT REFERENCE TEXT\n";
	std::getline(std::cin, text);
	std::cout << "\nINPUT SEARCH PATTERN\n";
	std::getline(std::cin, patt);
	int start = kmpsearch(text, patt);
	std::cout << std::endl;
	if (start < 0) {
		std::cout << "PATTERN NOT DETECTED\n";
	}
	else {
		std::cout << "PATTERN DETECTED AT POSITION " << start << std::endl;
	}
	std::getline(std::cin,text);
}