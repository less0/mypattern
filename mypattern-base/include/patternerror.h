#include "objecttype.h"
#include <string>
#include "errorcode.h"

#ifndef PATTERNERROR_H
#define PATTERNERROR_H

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class PatternError
        {
            public:
                /*! \brief Initializes a blank "no error" PatternError object
                *
                * This standard constructor initializes a blank PatternError object. Since PatternError
                * object are de facto immutable, the object maintains the default ErrorCode ErrorCode::OK
                * thus this can be considered as an PatternError object indicating that everything is fine
                */
                PatternError();
                /*! \brief Initializes a general PatternError object with a error message
                *
                * This constructor initializes a new PatternError object with the ErrorCode
                * ErrorCode::GENERAL and an error message indicating what went wrong.
                *
                * \param part_name The name of the part the error occurred in
                * \param object_name The name of the object causing the error
                * \param object_type The type of the object causing the problem
                * \param error_message Message indicating the error
                */
                PatternError(string part_name, string object_name, MyPattern::Base::ObjectType object_type, string error_message);
                /*! \brief Initializes a specific PatternError with a proper ErrorCode
                *
                * This constructor initializes a new PatternError object with the ErrorCode
                * provided indicating the cause of the errror
                *
                * \param part_name The name of the part the error occurred in
                * \param object_name The name of the object causing the error
                * \param object_type The type of the object causing the problem
                * \param error_code ErrorCode indicating the type of the error
                */
                PatternError(string part_name, string object_name, MyPattern::Base::ObjectType object_type, MyPattern::Base::ErrorCode error_code);
                virtual ~PatternError();

                /*! \brief Gets a string representation of the PatternError
                *
                */
                string to_string();
                /*! \brief Gets the name of the part the error occurred in
                *
                */
                string get_part_name();
                /*! \brief Gets the name of the object causing the error
                *
                */
                string get_object_name();
                /*! \brief Get the ObjectType of the object causing the error
                */
                MyPattern::Base::ObjectType get_object_type();

                /*! \brief Gets the message assigned to the error
                */
                string get_error_message();
                /*! \brief Gets the error code assigned to the error
                */
                MyPattern::Base::ErrorCode get_error_code();
            protected:
            private:
                string m_error_message;
                string m_part_name;
                string m_object_name;
                MyPattern::Base::ObjectType m_object_type;
                MyPattern::Base::ErrorCode m_error_code;
        };
    }
}


#endif // PATTERNERROR_H
