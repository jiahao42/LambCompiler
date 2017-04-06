#include <iostream>
#include <fstream>



int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Invalid parameter!" << std::endl;
		return 0;
	}
	
	std::ifstream text;
	std::string line;
	int line_count = 0;
	int error_code = 0;
	
	text.open(argv[1]);
	if (text.is_open()) {
		while (std::getline(text, line)) {
			line_count++;
			std::cout<<line_count<<std::endl;
		}
	} else {
		std::cout << "Failed to open file! Please check your input!" << std::endl;
	}
	return 0;
}











