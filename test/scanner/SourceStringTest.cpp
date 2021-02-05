//
// Created by ich on 2/1/21.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "SourceStringTest"

#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include "../../src/scanner/MultilineCommentResistantStringScanner.h"

BOOST_AUTO_TEST_SUITE(SourceStringTestSuite)
BOOST_AUTO_TEST_CASE(hello_world) {
    std::string code = "#include <iostream>\nint main() {\n\tstd::cout << \"hello world\" << std::endl;\n}";
    MultilineCommentResistantStringScanner s(code);
    std::list<ScannerOutput> scanner_result;
    ScannerOutput result = std::make_pair(Token::INTEGER, "foo");
    while (std::get<TOKEN>(result) != Token::END_OF_FILE) {
        result = s.read();
        scanner_result.push_back(result);
    }
}

BOOST_AUTO_TEST_CASE(fromSourceCode) {
    std::string foo = "/****************************************************************************\n";
    foo += "*                  frame.h\n";
    foo += "*\n";
    foo += "* This header file is included by all C modules in POV-Ray. It defines all\n";
    foo += "* globally-accessible types and constants.\n";
    foo += "*\n";
    foo += "* from Persistence of  Vision(tm) Ray Tracer version 3.6.\n";
    foo += "* Copyright 1991-2003 Persistence of Vision Team\n";
    foo += "* Copyright 2003-2004 Persistence of Vision Raytracer Pty. Ltd.\n";
    foo += "*---------------------------------------------------------------------------\n";
    foo += "* NOTICE: This source code file is provided so that users may experiment:\n";
    foo += " *****************************************************************************/";
    MultilineCommentResistantStringScanner s(foo);
    auto result = s.read();
    BOOST_CHECK_EQUAL(foo, std::get<TOKEN_STRING>(result));
    //std::cout << "got: " << std::endl << std::get<TOKEN_STRING>(result) << std::endl;
}

BOOST_AUTO_TEST_CASE(exclamation_mark) {
    std::string foo = "/*\n";
    foo += " * You have to define the macros ";
    foo += "POVRAY_BEGIN_COOPERATE";
    foo += " and POVRAY_END_COOPERATE!";
    foo += " */";
    std::cout << foo << std::endl;
    MultilineCommentResistantStringScanner s(foo);
    auto result = s.read();
    BOOST_CHECK_EQUAL(foo, std::get<TOKEN_STRING>(result));
    std::cout << "got: " << std::endl << std::get<TOKEN_STRING>(result) << std::endl;
}

BOOST_AUTO_TEST_CASE(multipleComments) {
    std::string foo = "/** a **/\n";
    foo += "x";
    foo += "/** b **/\n";
    foo += "stl::cin ++ \"hm\" --;\n";

    std::string scanned = "";
    MultilineCommentResistantStringScanner s(foo);
    for (auto result = s.read(); std::get<TOKEN>(result) != Token::END_OF_FILE; result = s.read()) {
        scanned += std::get<TOKEN_STRING>(result);
    }
    BOOST_CHECK_EQUAL(scanned, foo);
}
BOOST_AUTO_TEST_SUITE_END()
