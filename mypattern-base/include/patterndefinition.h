#ifndef PATTERNDEFINITION_H
#define PATTERNDEFINITION_H

#include "mypattern-data.h"
#include "pattern.h"
#include "measures.h"
#include "patternparameter.h"
#include "patternparametervalue.h"
#include "partdefinition.h"
#include "patterntype.h"
#include <string>
#include "patternerror.h"
#include "user.h"
#include <list>

using namespace std;
using namespace MyPattern::Data;

namespace MyPattern
{
    namespace Base
    {
        /*! \brief Abstract definition for a sewing pattern
        *
        * The PatternDefinition class defines an generic definition of a sewing pattern,
        * incorporating Landmark objects to define generic positions within the pattern.
        * A pattern definition is meant to be used to create an actual pattern by
        * passing Measures and PatternParameterValue objects.
        */
        class PatternDefinition
        {
            public:
                PatternDefinition();
                PatternDefinition(const PatternDefinition& instance);
                PatternDefinition(string name);

                /*! \brief Create a Pattern object from a PatternDefinition and Measures.
                *
                *
                */
                Pattern get_pattern(Measures);
                Pattern get_pattern(Measures, std::list<PatternParameterValue>);

                /*! \brief Creates a new PartDefinition object
                *
                * Createa a new PartDefinition object and adds it to the current
                * PatternDefinition.
                * \param name Name of the new part definition
                * \return A pointer to the newly created PartDefinition object, or NULL,
                * if the creation failed
                */
                shared_ptr<PartDefinition> create_part_definition(string name);

                /*! \brief Adds an existing PartDefinition object to the current
                * PatternDefinition
                *
                * \param part Existing part definition to add to the current pattern
                * definition
                * \return false if the part definition could not be added to the pattern
                * defintion, true otherwise
                */
                bool add_part_definition(shared_ptr<PartDefinition> part);

                /*! \brief Gets a PartDefinition object by name
                *
                * \param name Name of the part definition
                * \return A pointer to the according PartDefinition object, if an object
                * with the given name exists, NULL otherwise
                */
                shared_ptr<PartDefinition> get_part_definition(string name);

                /*! \brief Gets a PartDefinition object by index
                *
                * Gets a PartDefinition based on a zero-based index, which will usually
                * reflect the order of adding the part defintions to the current
                * PatternDefinition object.
                * \param index Zero-based index of the PartDefinition object
                * \return A PartDefinition object, if an object with the given index
                * exists, NULL otherwise
                */
                shared_ptr<PartDefinition> get_part_definition(unsigned long index);

                /*! \brief Returns a list of all PartDefintion objects in the current
                * PatternDefinition object
                */
                std::list<shared_ptr<PartDefinition>> get_part_definitions();

                /*! \brief Returns a list of all PartDefinition names in the current
                * PatternDefinition object
                */
                std::list<string> get_part_defintion_names();

                /*! Removes a PartDefinition from the current PatternDefinition
                *
                * Removes a PartDefinition object from a PatternDefinition, based on the
                * name of the PartDefinition.
                * \param name Name of the part definition to remoove
                * \return true if the object existed and was removed, false otherwise
                */
                bool remove_part_definition(string name);

                /*! \brief Adds a PatternParameter to the current PatternDefinition
                *
                * \param parameter The pattern parameter to add
                * \return true if the parameter was added, false otherwise
                */
                bool add_pattern_parameter(shared_ptr<PatternParameter> parameter);
                /*! \brief Returns a list of the names of all pattern parameters
                */
                std::list<string> get_pattern_parameter_names();
                /*! \brief Gets a PatternParameter by name
                *
                *
                * \param name Name of the pattern parameter
                * \return A pointer to the PatternParameter object with the given name,
                * NULL, if there was no PatternParameter object with the given name
                */
                shared_ptr<PatternParameter> get_pattern_parameter(string name);

                list<shared_ptr<PatternParameter>> get_pattern_parameters();

                /*! Removes a PatternParameter from the current PatternDefinition
                *
                * Removes a pattern parameter from the current pattern definition based
                * on the name of the pattern parameter
                * \param name Name of the parameter
                * \return true if an object with the given name was found and removed,
                * false otherwise
                */
                bool remove_pattern_parameter(string name);

                void set_author(shared_ptr<User> author);

                /*! \brief Returns the author of the current PatternDefintion */
                shared_ptr<User> get_author();

                /*! \brief Gets the version of the PatternDefinition object
                *
                * This function returns the version of the current pattern definition.
                * \return Pattern definition version
                */
                int get_version();

                /*! \brief Sets the version of the current PatternDefinition
                *
                * This function changes the version of the current pattern definition.
                * This is meant to be changed only, if the pattern definition is
                * uploaded. The version number is increased, if a pattern definition
                * from the same user, with the same name, but a different UID, exists
                * on the server.
                * \param version Main version number of the pattern definition
                */
                void set_version(int version);

                /*! \brief Gets the revision number of the current PatternDefinition
                *
                * This function returns the revision number of the current pattern
                * definition. This number is incremented every time, a pattern with an
                * existing UID is uploaded.
                */
                int get_revision();

                /*! \brief Sets the revision number of the current PatternDefinition
                *
                * This function sets the revision number of the current pattern
                * definition. This number is incremented if (and only if) a pattern
                * with an existing UID is uploaded.
                * \param revision Revision number
                */
                void set_revision(int revision);

                /*! \brief Gets the license text for the current PatternDefinition
                */
                string get_license();

                /*! \brief Sets the license text of the pattern definition */
                void set_license(string);

                /*! \brief Gets the PatternType of the current PatternDefinition
                */
                PatternType get_pattern_type();

                /*! \brief Sets the PatternType
                *
                * Sets the type of the pattern. The pattern type has no influence on the
                * actual pattern, but is only meant to be metadata.
                * \param type The type of the pattern definition
                */
                void set_pattern_type(PatternType type);

                /*! \brief Gets the name of the pattern definition
                *
                * \return The name of a pattern definition.
                */
                string get_name();

                /*! \brief Set pattern definition name
                *
                * This function sets the name of a pattern definition. This name is to
                * be chosen freely an with virtually no restrictions, but should be
                * meaningful, if a pattern is meant to be uploaded.
                * \param name The designated name of the pattern
                */
                void set_name(string name);

                /*! \brief Gets the UID of the pattern definition
                *
                * If a pattern definition is uploaded, the server assigns a unique
                * identifier (UID) to the very pattern, this identifier is used to
                * version patterns.
                */
                string get_uid();

                /*! \brief Sets the uid of the pattern definition
                *
                * If (and only if) a pattern is uploaded, the server assigns an unique
                * identifier to the pattern, for versioning reasons. This UID will be
                * saved along with the pattern
                * \param uid UID of the pattern
                */
                void set_uid(string uid);

                /*! \brief Checks the pattern definition for errors
                *
                * This function checks if there are any errors in the pattern,
                * particularly in CurveDefinition and Landmark objects. Landmark objects
                * are checked for a correct formatting of the Landmark definition and
                * the existence of every of the referenced objects. Line objects are
                * checked for the existence of all of the referenced landmarks.
                * \return A list of PatternError objects occurring in the pattern
                * definition
                */
                std::list<PatternError> check();

                static shared_ptr<PatternDefinition> read_xml(string filename);
            protected:
            private:
                bool on_name_change_request(string name);

                list<shared_ptr<PartDefinition>> m_part_definitions;
                list<shared_ptr<PatternParameter>> m_pattern_parameters;
                shared_ptr<Measures> m_measures;

                shared_ptr<User> m_author;

                string m_name;

                int m_version;
                int m_revision;
                string m_uid;

        };
    }
}


#endif // PATTERNDEFINITION_H
