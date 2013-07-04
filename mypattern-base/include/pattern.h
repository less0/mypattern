#ifndef PATTERN_H
#define PATTERN_H

#include "part.h"

class Pattern
{
    public:
        Pattern();

        void set_name(Glib::ustring name);
        Glib::ustring get_name();

        list<Part> get_parts();
        void add_part(Part part);
    protected:
    private:
};

#endif // PATTERN_H
