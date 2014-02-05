#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_SCALARTERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_SCALARTERM_H

#include <evaluation/formula/term.h>
#include <list>
#include <string>

using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class ScalarTerm : public MyPattern::Base::Evaluation::Formula::Term
{
    public:
        /** Default constructor */
        ScalarTerm(string symbol)
        {
            m_symbol = symbol;
        }
        /** Default destructor */
        virtual ~ScalarTerm();
        /** Copy constructor
         *  \param other Object to copy from
         */
        ScalarTerm(const ScalarTerm& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        ScalarTerm& operator=(const ScalarTerm& other);

        double evaluate(map<Glib::ustring,double> values);

        list<string> get_names()
        {
            list<string> result;
            result.push_back(m_symbol);
            return result;
        }
    protected:
    private:
        string m_symbol;
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_SCALARTERM_H
