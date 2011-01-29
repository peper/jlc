#ifndef _KEYWORD_HH
#define _KEYWORD_HH

#include <boost/spirit/repository/include/qi_distinct.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace distinct
{
    //[qi_distinct_encapsulation
    namespace spirit = boost::spirit;
    namespace ascii = boost::spirit::ascii;
    namespace repo = boost::spirit::repository;

    // Define metafunctions allowing to compute the type of the distinct()
    // and ascii::char_() constructs
    namespace traits
    {
        // Metafunction allowing to get the type of any repository::distinct(...) 
        // construct
        template <typename Tail>
        struct distinct_spec
          : spirit::result_of::terminal<repo::tag::distinct(Tail)>
        {};

        // Metafunction allowing to get the type of any ascii::char_(...) construct
        template <typename String>
        struct char_spec
          : spirit::result_of::terminal<spirit::tag::ascii::char_(String)>
        {};
    };

    // Define a helper function allowing to create a distinct() construct from 
    // an arbitrary tail parser
    template <typename Tail>
    inline typename traits::distinct_spec<Tail>::type
    distinct_spec(Tail const& tail)
    {
        return repo::distinct(tail);
    }

    // Define a helper function allowing to create a ascii::char_() construct 
    // from an arbitrary string representation
    template <typename String>
    inline typename traits::char_spec<String>::type
    char_spec(String const& str)
    {
        return ascii::char_(str);
    }

    // the following constructs the type of a distinct_spec holding a
    // charset("0-9a-zA-Z_") as its tail parser
    typedef traits::char_spec<std::string>::type charset_tag_type;
    typedef traits::distinct_spec<charset_tag_type>::type keyword_tag_type;

    // Define a new Qi 'keyword' directive usable as a shortcut for a
    // repository::distinct(char_(std::string("0-9a-zA-Z_")))
    const std::string keyword_spec("0-9a-zA-Z_");
    const keyword_tag_type keyword = distinct_spec(char_spec(keyword_spec));
    //]
}

#endif /* _KEYWORD_HH */
