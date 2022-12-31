#if !defined(__gauze_argparser_hpp) // argparser.hpp include guard
#define __gauze_argparser_hpp

#include <vector>
#include <string>


namespace chirk {
    class argparser;
};


class chirk::argparser {
public:

    // constructors and initializing method
    argparser(char* argv[]);
    argparser(int argc, char* argv[]);
    void parseargs(const char** flags, unsigned int* flag_arg_counts);

    // methods for querying this->parsed_argv
    int num_flags();
    bool was_passed(const std::string& flag);
    std::vector<const std::string> flag_args(const std::string& flag);

    // wrappers for methods of this->parsed_argv->front()
    int args_size();
    std::string args_at(int index);
    
private:
    /*
     * These are declared private by default because they're
     * internal variables, and not meant to be part of the
     * user API.
     */
    int argc;
    char** argv;
    std::vector<std::vector<const std::string>>* parsed_argv;
};


#endif // argparser.hpp include guard
