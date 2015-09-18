// basic mINI sample
// - rlyeh, public domain

#include <iostream>
#include <cassert>

#include "mini.hpp"

int main() {
    // load file
    std::string content =
    "; this is a comment\n"
    "[test]\r\n"
    "number=123\n"
    " \tstring=hello world\r";

    // load content
    mINI ini;
    bool ok = ini.load( content );

    // tests
    assert( ini["test.number"] == "123" );         // symbol value
    assert( ini["test.string"] == "hello world" ); // symbol value

    assert( ini.line("test.number") == 3 );        // line number
    assert( ini.line("test.string") == 4 );        // line number

    // append new symbols
    ini["added.number"] = "456";
    ini["added.string"] = "new string";

    // save and print
    std::cout << ini.save() << std::endl;
}

#if 0

// or you could create a handy variant class and tell mINI to use it instead, as follows:

struct variant : public std::string {
    template<typename T>
    variant( const T &t ) : std::string( std::to_string(t) )
    {}
    template<size_t N>
    variant( const char (&s)[N] ) : std::string( s, N )
    {}
    variant( const char *cstr ) : std::string( cstr )
    {}
    variant( const std::string &other = std::string() ) : std::string(other)
    {}
    template<typename T>
    operator T() const {
        T t;
        std::stringstream ss;
        return ss << *this && ss >> t ? t : T();
    }
    template<typename T> bool operator ==( const T &t ) const {
        return 0 == this->compare( variant( t ) );
    }
    bool operator ==( const char *t ) const {
        return this->compare( t ) == 0;
    }
};

int main() {
    // load file
    std::string content =
    "; this is a comment\n"
    "[test]\r\n"
    "number=123\n"
    "string=hello world\r";

    // load content
    mINI_basic<std::string, variant> ini;
    bool ok = ini.load( content );

    // tests
    assert( ini["test.number"] == 123 );           // symbol value
    assert( ini["test.string"] == "hello world" ); // symbol value

    assert( ini.line("test.number") == 3 );        // line number
    assert( ini.line("test.string") == 4 );        // line number

    // append new symbols
    ini["added.number"] = 456;
    ini["added.string"] = "new string";

    // save and print
    std::cout << ini.save() << std::endl;
}

#endif
