//
// Created by Gchiko on 05-Dec-18.
//

#ifndef TAGGER_EXCEPTIONS_H
#define TAGGER_EXCEPTIONS_H

class not_found:public std::exception{};
class not_labeled:public std::exception{};
class hash_already_exists: public std::exception{};
class hash_doesnt_exist: public std::exception{};
class avl_doesnt_exist: public std::exception{};
class same_super_pixel: public std::exception{};

#endif //TAGGER_EXCEPTIONS_H
