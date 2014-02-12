#include "evaluation/formula/term.h"
#include "glibmm/regex.h"
#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/scalarterm.h"
#include "evaluation/formula/quotientterm.h"
#include "evaluation/formula/productterm.h"
#include "evaluation/formula/differenceterm.h"
#include "evaluation/formula/sumterm.h"
#include "exceptions/formulaevaluationexception.h"

#include <map>
#include <sstream>

using namespace Glib;
using namespace std;
using namespace MyPattern::Exceptions;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

ustring Term::s_operators = "/*-+";
//ustring Term::s_valid_symbol = "^[@$#\?]{1,1}[A-Za-z0-9]+(\[([XY]{1,1}|(1\.[0]{1,})|0.[0-9]{1,})\]){0,1}$";
ustring Term::s_valid_symbol = "^[@$#\\?]{1,1}[A-Za-z0-9]+(\\[[XY]\\]|\\[0\\]){0,1}$";

ustring Term::s_valid_number = "^[0-9]+$|^[0-9]{0,}\\.[0-9]{1,}$";

Term& Term::operator=(const Term& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

shared_ptr<Term> Term::parse(const Glib::ustring &formula)
{

    map<ustring, shared_ptr<Term>> substitutions;
    int substitutions_index = 0;


    ///\todo remove all whitespaces, etc.


    return parse_internal(formula, substitutions, substitutions_index);

}

shared_ptr<Term> Term::parse_internal(ustring formula, map<ustring, shared_ptr<Term>> &substitutions, int &substitution_index)
{
    int operator_index = 0;
    int start_index = 0;
    int end_index = 0;

    ustring parentheses_pattern = "\\([A-Za-z#$\\?@0-9\\[\\]\\.\\*\\+\\/\\-]*\\)";
    RefPtr<Regex> parentheses_regex = Regex::create(parentheses_pattern);

    MatchInfo match_info;

    while(parentheses_regex->match(formula, match_info))
    {
        ustring subformula = match_info.fetch(0);

        subformula = subformula.substr(1, subformula.length()-2);

        shared_ptr<Term> parentheses_term = parse_internal(subformula, substitutions, substitution_index);

        stringstream s;
        s << s_substituion_marker <<  substitution_index++;

        unsigned int subformula_index = formula.find(subformula);

        formula.erase(subformula_index-1, subformula.length()+2);
        formula.insert(subformula_index-1, s.str());

        substitutions.insert(pair<ustring, shared_ptr<Term>>(s.str(), parentheses_term));

        //return shared_ptr<Term>(new ConstantTerm(0));
    }


    while((operator_index = formula.find('/')) > 0)
    {
        shared_ptr<Term> left_atomic = Term::get_left_atomic(formula, operator_index, substitutions, start_index);
        shared_ptr<Term> right_atomic = Term::get_right_atomic(formula, operator_index, substitutions, end_index);

        shared_ptr<Term> substituted_term = shared_ptr<Term>(new QuotientTerm(left_atomic, right_atomic));

        stringstream s;
        s << s_substituion_marker <<  substitution_index++;

        formula.erase(start_index, (end_index - start_index) + 1);
        formula.insert(start_index, s.str());

        substitutions.insert(pair<ustring,shared_ptr<Term>>(s.str(), substituted_term));
    }

    while((operator_index = formula.find('*')) > 0)
    {
        shared_ptr<Term> left_atomic = Term::get_left_atomic(formula, operator_index, substitutions, start_index);
        shared_ptr<Term> right_atomic = Term::get_right_atomic(formula, operator_index, substitutions, end_index);

        shared_ptr<Term> substituted_term = shared_ptr<Term>(new ProductTerm(left_atomic, right_atomic));

        stringstream s;
        s << s_substituion_marker <<  substitution_index++;

        formula.erase(start_index, (end_index - start_index) + 1);
        formula.insert(start_index, s.str());

        substitutions.insert(pair<ustring,shared_ptr<Term>>(s.str(), substituted_term));
    }

    while((operator_index = formula.find('-')) > 0)
    {
        shared_ptr<Term> left_atomic = Term::get_left_atomic(formula, operator_index, substitutions, start_index);
        shared_ptr<Term> right_atomic = Term::get_right_atomic(formula, operator_index, substitutions, end_index);

        shared_ptr<Term> substituted_term = shared_ptr<Term>(new DifferenceTerm(left_atomic, right_atomic));

        stringstream s;
        s << s_substituion_marker <<  substitution_index++;

        formula.erase(start_index, (end_index - start_index) + 1);
        formula.insert(start_index, s.str());

        substitutions.insert(pair<ustring,shared_ptr<Term>>(s.str(), substituted_term));
    }

    while((operator_index = formula.find('+')) > 0)
    {
        shared_ptr<Term> left_atomic = Term::get_left_atomic(formula, operator_index, substitutions, start_index);
        shared_ptr<Term> right_atomic = Term::get_right_atomic(formula, operator_index, substitutions, end_index);

        shared_ptr<Term> substituted_term = shared_ptr<Term>(new MyPattern::Base::Evaluation::Formula::SumTerm(left_atomic, right_atomic));

        stringstream s;
        s << s_substituion_marker <<  substitution_index++;

        formula.erase(start_index, (end_index - start_index) + 1);
        formula.insert(start_index, s.str());

        substitutions.insert(pair<ustring,shared_ptr<Term>>(s.str(), substituted_term));
    }

    return substitutions.at(formula);
}

shared_ptr<Term> Term::get_left_atomic(ustring formula, int index, const map<ustring, shared_ptr<Term>> &substitutions, int &start_index)
{
    int current_index = index - 1;
    ustring subterm;

    while(current_index>=0 &&
        s_operators.find(formula[current_index]) == ustring::npos)
    { current_index--; }

    start_index = current_index + 1;

    subterm = formula.substr(current_index+1, (index - (current_index+1)));

    return parse_atomic(subterm, substitutions);
}

shared_ptr<Term> Term::get_right_atomic(ustring formula, int index, const map<ustring, shared_ptr<Term>> &substitutions, int &end_index)
{
    unsigned int current_index;
    ustring subterm;

    for(current_index = index + 1;
        current_index < formula.length() &&
            s_operators.find(formula[current_index]) == ustring::npos;
        current_index++);

    end_index = current_index - 1;
    subterm = formula.substr(index + 1, end_index - index);

    return parse_atomic(subterm, substitutions);
}

shared_ptr<Term> Term::parse_atomic(ustring term, const map<ustring, shared_ptr<Term>> &substitutions)
{

//    Glib::RefPtr<Regex> regex_number = Regex::create(Term::s_valid_number);
    Glib::RefPtr<Regex> regex_number = Regex::create(s_valid_number);
    Glib::RefPtr<Regex> regex_symbol = Regex::create(s_valid_symbol);

    if(regex_number->match(term))
    {
    //parse number and return ConstantTerm
        stringstream s(term);
        double value;
        s >> value;
        return shared_ptr<Term>(new ConstantTerm(value));
    }
    else if(regex_symbol->match(term))
    {
        //return substitution or ScalarTerm
        if(substitutions.count(term) > 0)
        {
            return substitutions.at(term);
        }

        return shared_ptr<Term>(new ScalarTerm(term));
    }
    else
    {
        throw FormulaEvaluationException("");
    }

}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
