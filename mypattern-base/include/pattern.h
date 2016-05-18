#ifndef PATTERN_H
#define PATTERN_H

#include "part.h"
#include <string>

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class Pattern
        {
            public:
                Pattern();
                //copy ctor
                Pattern(const Pattern&);

                void set_name(string name);
                string get_name();

                list<Part> get_parts();
                void add_part(Part part);
            protected:
            private:
                string m_name;
                list<Part> m_parts;
        };
    }
}


#endif // PATTERN_H
