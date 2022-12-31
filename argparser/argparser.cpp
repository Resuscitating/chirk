#include "argparser.hpp"

#include <exception>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace chirk;


argparser::argparser(char* argv[])
    : argv{ argv }, 
      parsed_argv{ new std::vector<std::vector<const std::string>> } {
    for(; this->argv[this->argc] != nullptr; this->argc++);
}


argparser::argparser(int argc, char* argv[])
    : argc{ argc }, argv{ argv }, 
      parsed_argv{ new std::vector<std::vector<const std::string>> } {
}


void argparser::parseargs(const char** flags, unsigned int* flag_arg_counts) {
    this->parsed_argv->clear();
    this->parsed_argv->emplace_back(std::vector<std::string>{  });
    int flag_args_left = 0;
    bool flags_left = true;
    for(int argv_index = 0; argv_index < this->argc; argv_index++) {
        const std::string arg_str = { this->argv[argv_index] };
        if(!flags_left) {
            this->parsed_argv->front().emplace_back(arg_str);
            continue;
        }
        if(flag_args_left) {
            this->parsed_argv->back().emplace_back(arg_str);
            flag_args_left--;
            continue;
        }
        bool found_arg = false;
        for(int flag_index = 0; flags[flag_index]; flag_index++) {
            const std::string flag_str = { flags[flag_index] };
            if(arg_str == flag_str) {
                this->parsed_argv->emplace_back(std::vector<const std::string>{  });
                this->parsed_argv->back().emplace_back(arg_str);
                flag_args_left = flag_arg_counts[flag_index];
                found_arg = true;
                break;
            }
        }
        if(!found_arg) {
            if(arg_str == "-" || arg_str == "--") {
                flags_left = false;
            } else {
                this->parsed_argv->front().emplace_back(arg_str);
            }
        }
    }
}


int argparser::num_flags() {
    return this->parsed_argv->size() - 1;
}


bool argparser::was_passed(const std::string& flag) {
    for(std::vector<const std::string> vec : *(this->parsed_argv)) {
        if(vec.front() == flag) {
            return true;
        }
    }
    return false;
}


std::vector<const std::string> argparser::flag_args(const std::string& flag) {
    for(std::vector<const std::string> vec : *(this->parsed_argv)) {
        if(vec.front() == flag) {
            return vec;
        }
    }
    throw std::out_of_range("flag '" + flag + "' not found");
}


std::string argparser::args_at(int index) {
    return this->parsed_argv->front().at(index);
}


int argparser::args_size() {
    return this->parsed_argv->front().size();
}
