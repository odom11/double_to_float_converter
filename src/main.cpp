#include <iostream>
#include <fstream>

#include "scanner/Scanner.h"
#include "scanner/MultilineCommentResistantStringScanner.h"
#include "parser/DoubleToFloatParser.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::runtime_error("provide 2 commandlien arguments: first inputfile, second outputfile");
    }
    std::string inputfile(argv[1]);
    std::string outputfile(argv[2]);
    std::cout << "inputfile: " << inputfile << std::endl;
    std::cout << "outputfile: " << outputfile << std::endl;

    std::ifstream ifs (inputfile);
    std::string filecontent;
    getline (ifs, filecontent, (char) ifs.eof());
    MultilineCommentResistantStringScanner scanner(filecontent);
    DoubleToFloatParser parser(scanner);
    std::stringbuf parsed = parser.parse();
    std::ofstream of;
    of.open(outputfile);
    if (!of.is_open()) {
        throw std::runtime_error("error opening output file");
    }
    of << parsed.str();
    return 0;
}
