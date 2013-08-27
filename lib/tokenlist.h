/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2013 Daniel Marjamäki and Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------
#ifndef tokenlistH
#define tokenlistH
//---------------------------------------------------------------------------

#include <string>
#include <vector>
#include "config.h"
#include "token.h"

class Token;
class Settings;

/// @addtogroup Core
/// @{

class CPPCHECKLIB TokenList {
public:
    TokenList(const Settings* settings);
    ~TokenList();

    void setSettings(const Settings *settings) {
        _settings = settings;
    }

    /**
     * Delete all tokens in given token list
     * @param tok token list to delete
     */
    static void deleteTokens(Token *tok);

    void addtoken(const char str[], const unsigned int lineno, const unsigned int fileno, bool split = false);
    void addtoken(const Token *tok, const unsigned int lineno, const unsigned int fileno);

    //ds add custom token
    void addCustomToken( const std::string& p_strToken, const unsigned int& p_uLineNumber, const unsigned int& p_uFileIndex, const Token::Type& p_cType );

    static void insertTokens(Token *dest, const Token *src, unsigned int n);

    /**
     * Create tokens from code.
     * The code must be preprocessed first:
     * - multiline strings are not handled.
     * - UTF in the code are not handled.
     * - comments are not handled.
     * @param code input stream for code
     * @param file0 source file name
     */
    bool createTokens(std::istream &code, const std::string& file0 = "", const std::string& p_strRawCode = "");

    /** Deallocate list */
    void deallocateTokens();

    /** get first token of list */
    const Token *front() const {
        return _front;
    }
    Token *front() {
        return _front;
    }

    /** get last token of list */
    const Token *back() const {
        return _back;
    }
    Token *back() {
        return _back;
    }

    //ds get the first custom token
    const Token *getCustomFront( ) const
    {
        return m_pcCustomTokenFront;
    }

    /**
     * Get filenames (the sourcefile + the files it include).
     * The first filename is the filename for the sourcefile
     * @return vector with filenames
     */
    const std::vector<std::string>& getFiles() const {
        return _files;
    }

    /**
     * get filename for given token
     * @param tok The given token
     * @return filename for the given token
     */
    const std::string& file(const Token *tok) const;

    /**
     * Get file:line for a given token
     * @param tok given token
     * @return location for given token
     */
    std::string fileLine(const Token *tok) const;

    void createAst() const;

private:
    /** Disable copy constructor, no implementation */
    TokenList(const TokenList &);

    /** Disable assignment operator, no implementation */
    TokenList &operator=(const TokenList &);

public:

private: /// private
    /** Token list */
    Token *_front, *_back;

    /** filenames for the tokenized source code (source + included) */
    std::vector<std::string> _files;

    /** settings */
    const Settings* _settings;

    //ds custom token list
    Token* m_pcCustomTokenFront;
    Token* m_pcCustomTokenBack;

};

/// @}

//---------------------------------------------------------------------------
#endif
