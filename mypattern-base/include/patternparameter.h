#ifndef PATTERNPARAMETER_H
#define PATTERNPARAMETER_H

#include <string>
#include <memory>

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        /*! \brief Base class for pattern parameters
        *
        * This class defines a parameter that can be passed to a pattern. This base class is not
        * meant to be instanciated by itself.
        */
        class PatternParameter
        {
            public:
                virtual ~PatternParameter() = 0;

                /*! \brief Gets the name of the pattern parameter
                *
                * This function returns the name of the pattern parameter. Since this name is used
                * to discriminate between parameters it must be unique within a pattern and can't be
                * changed after the creation of the object.
                * \return Name of the pattern
                */
                string get_name();


                virtual void parse_value_range(string valueRange) = 0;

                /*! \brief Creates a PatternParameter object given a name and a type
                *
                * This static function creates an object of one of the types derived from
                * PatternParameter.
                * \param name Name of the new PatternParameter object. This must be unique within a
                * pattern. Adding a parameter with a name of an existing parameter to a pattern will
                * fail.
                * \param type Type of the derived class. This is not an actual class name, but
                * rather defined as constants in the Constants namespace.
                * \return A new PatternParameter object if the creation succeeded, a NULL-pointer
                * otherwise
                */
                static shared_ptr<PatternParameter> create_object(string name,
                    string type,
                    string = "");

            protected:
                void set_name(string name);
            private:
                string m_name;
        };

    }
}


#endif // PATTERNPARAMETER_H
