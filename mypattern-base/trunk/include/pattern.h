#ifndef PATTERN_H
#define PATTERN_H

#include "part.h"

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

                void set_name(Glib::ustring name);
                Glib::ustring get_name();

                list<Part> get_parts();
                void add_part(Part part);
            protected:
            private:
                Glib::ustring m_name;
                list<Part> m_parts;
        };
    }
}


#endif // PATTERN_H
