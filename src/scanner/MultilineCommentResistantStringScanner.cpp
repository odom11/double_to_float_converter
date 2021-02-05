//
// Created by ich on 2/1/21.
//
#include <iterator>
#include "MultilineCommentResistantStringScanner.h"

extern int column_number, line_number;

MultilineCommentResistantStringScanner::MultilineCommentResistantStringScanner(const std::string &filecontent) : filecontent(filecontent) {
    it = this->filecontent.begin();
}

ScannerOutput MultilineCommentResistantStringScanner::read() {
    if (it == filecontent.end()) {
        return std::make_pair(Token::END_OF_FILE, "");
    }
    if (isAtMultilineComment()) {
        std::string commentText = multilineCommentText();
        it += commentText.size();
        updateLinenumberAndColumnGlobals(commentText);
        return std::make_pair(Token::COMMENT, commentText);
    }
    if (!currentStringScanner) {
        std::string sourceCode = noCommentText();
        currentStringScanner = std::make_unique<StringScanner>(noCommentText());
        return currentStringScanner->read();
    }
    if (currentStringScanner) {
        auto readByScanner = currentStringScanner->read();
        if (std::get<TOKEN>(readByScanner) == Token::END_OF_FILE) {
            it += currentStringScanner->getString().size();
            currentStringScanner.release();
            if (it == filecontent.end()) {
                return readByScanner;
            } else {
                return read();
            }
        }
        return readByScanner;
    }
    throw std::runtime_error("case should not occur");
}

const std::string MultilineCommentResistantStringScanner::noCommentText() {
    if (it == filecontent.end()) {
        throw std::runtime_error("cannot call textTill methods at EOF");
    }
    auto tmpIt = it + 1;
    for (;tmpIt != filecontent.end() && (*tmpIt != '*' || *(tmpIt - 1) != '/'); ++tmpIt);
    std::string noCommentText;
    if (tmpIt == filecontent.end()) {
        noCommentText = std::string(it, tmpIt);
    } else {
        noCommentText = std::string(it, tmpIt - 1);
    }
    return noCommentText;
}

const std::string MultilineCommentResistantStringScanner::multilineCommentText() {
    if (it == filecontent.end()) {
        throw std::runtime_error("cannot call textTill methods at EOF");
    }
    auto tmpIt = it + 3;
    for (;tmpIt != filecontent.end() && (*tmpIt != '/' || *(tmpIt - 1) != '*'); ++tmpIt);
    std::string commentText(it, ++tmpIt);
    return commentText;
}

bool MultilineCommentResistantStringScanner::isAtMultilineComment() {
    if (std::distance(it, filecontent.end()) < 4) {
        return false;
    }
    return *it == '/' && *(it + 1) == '*';
}

void MultilineCommentResistantStringScanner::updateLinenumberAndColumnGlobals(const std::string &comment) {
    int i, line_count, col_inc;
    for (
            i = 0, line_count = 0, col_inc = 0;
            comment[i] != '\0';
            comment[i] == '\n' ? ++line_count, ++i, col_inc = 0, column_number = 1 : ++i, ++col_inc);
    line_number += line_count;
    column_number += col_inc;
}