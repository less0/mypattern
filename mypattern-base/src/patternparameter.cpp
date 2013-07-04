#include "patternparameter.h"
#include "constants.h"

#include "floatpatternparameter.h"
#include "intpatternparameter.h"

PatternParameter::~PatternParameter()
{
    //dtor
}

shared_ptr<PatternParameter> PatternParameter::create_object(Glib::ustring name, Glib::ustring type, Glib::ustring valueRange)
{
    shared_ptr<PatternParameter> createdObject(NULL);

    if(type.compare(Constants::PARAMETERTYPE_INT))
    {
        shared_ptr<IntPatternParameter> derivedObject(new IntPatternParameter(name));
        derivedObject->parse_value_range(valueRange);
        ///\todo find out how casts work with shared_ptr
        //createdObject = dynamic_cast<PatternParameter*>(derivedObject);
    }
    else if(type.compare(Constants::PARAMETERTYPE_STRING))
    {
        /*! \todo Create an object of Type StringPatternParameter */

    }
    else if(type.compare(Constants::PARAMETERTYPE_FLOAT))
    {
        shared_ptr<FloatPatternParameter> derivedObject(new FloatPatternParameter(name));
        derivedObject->parse_value_range(valueRange);
        ///\todo find out how casts work with shared_ptr
        //createdObject = dynamic_cast<PatternParameter*>(derivedObject);
    }
    else if(type.compare(Constants::PARAMETERTYPE_BOOL))
    {
        /*! \todo Create an object of type BoolPatternParameter */

    }

    return createdObject;
}

