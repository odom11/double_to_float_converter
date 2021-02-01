//
// Created by ich on 2/1/21.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "SourceStringTest"

#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include "StringScanner.h"

BOOST_AUTO_TEST_SUITE(SourceStringTestSuite)
BOOST_AUTO_TEST_CASE(hello_world) {
    std::string code = "#include <iostream>\nint main() {\n\tstd::cout << \"hello world\" << std::endl;\n}";
    StringScanner s(code);
    std::list<ScannerOutput> scanner_result;
    ScannerOutput result = std::make_pair(Token::INTEGER, "foo");
    while (std::get<TOKEN>(result) != Token::END_OF_FILE) {
        result = s.read();
        scanner_result.push_back(result);
    }
}
BOOST_AUTO_TEST_SUITE_END()
