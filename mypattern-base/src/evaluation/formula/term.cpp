#include "evaluation/formula/term.h"
#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/scalarterm.h"
#include "evaluation/formula/quotientterm.h"
#include "evaluation/formula/productterm.h"
#include "evaluation/formula/differenceterm.h"
#include "evaluation/formula/sumterm.h"
#include "exceptions/formulaevaluationexception.h"

#include <map>
#include <sstream>
#include <regex>

using namespace std;
using namespace MyPattern::Exceptions;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

string Term::s_operators = "/*-+";
string Term::s_valid_symbol = "^[@$#\\?]{1,1}[A-Za-z0-9]+(\\[[XY]\\]|(\\[0\\]|\\[0?\\.[0-9]*\\])(\\[[XY]\\]){0,1}){0,1}$";
string Term::s_valid_number = "^[0-9]+$|^[0-9]{0,}\\.[0-9]{1,}$";

Term& Term::operator=(const Term& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

shared_ptr<Term> Term::parse(const string &formula)
{

    map<string, shared_ptr<Term>> substitutions;
    int substitutions_index = 0;


    ///\todo remove all whitespaces, etc.


    return parse_internal(formula, substitutions, substitutions_index);

}

shared_ptr<Term> Term::parse_internal(string formula, map<string, shared_ptr<Term>> &substitutions, int &substitution_index)
{
    int operator_index = 0;
    int start_index = 0;
    int end_index = 0;

    if(formula[0] == '-')
    {
        formula = "0" + formula;
    }

    std::regex regex_number(s_valid_number);
    std::regex regex_symbol(s_valid_symbol);

    if(std::regex_match(formula, regex_number))
    {
		//parse number and return ConstantTerm
        stringstream s(formula);
        double value;
        s >> value;
        return shared_ptr<Term>(new ConstantTerm(value));
    }
    else if(std::regex_match(formula, regex_symbol))
    {
        //return substitution or ScalarTerm
        if(substitutions.count(formula) > 0)
        {
            return substitutions.at(formula);
        }

        return shared_ptr<Term>(new ScalarTerm(formula));
    }

    string parentheses_pattern = "\\([A-Za-z#$\\?@0-9\\[\\]\\.\\*\\+\\/\\-]*\\)(.*)";
    std::regex parentheses_regex(parentheses_pattern);

    std::smatch match_info;

    while(std::regex_match(formula, match_info, parentheses_regex))
    {
        string subformula = match_info.str(0);

        subformula = subformula.substr(1, subformula.length()-2);

        shared_ptr<Term> parentheses_term = parse_internal(subformula, substitutions, substitution_index);

        stringstream s;
        s << s_substituion_marker <<  substitution_index++;

        unsigned int subformula_index = formula.find(subformula);

        formula.erase(subformula_index-1, subformula.length()+2);
        formula.insert(subformula_index-1, s.str());

        substitutions.insert(pair<string, shared_ptr<Term>>(s.str(), parentheses_term));

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

        substitutions.insert(pair<string,shared_ptr<Term>>(s.str(), substituted_term));
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

        substitutions.insert(pair<string,shared_ptr<Term>>(s.str(), substituted_term));
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

        substitutions.insert(pair<string,shared_ptr<Term>>(s.str(), substituted_term));
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

        substitutions.insert(pair<string,shared_ptr<Term>>(s.str(), substituted_term));
    }

    return substitutions.at(formula);
}

shared_ptr<Term> Term::get_left_atomic(string formula, int index, const map<string, shared_ptr<Term>> &substitutions, int &start_index)
{
    int current_index = index - 1;
    string subterm;

    while(current_index>=0 &&
        s_operators.find(formula[current_index]) == string::npos)
    { current_index--; }

    start_index = current_index + 1;

    subterm = formula.substr(current_index+1, (index - (current_index+1)));

    return parse_atomic(subterm, substitutions);
}

shared_ptr<Term> Term::get_right_atomic(string formula, int index, const map<string, shared_ptr<Term>> &substitutions, int &end_index)
{
    unsigned int current_index;
    string subterm;

    for(current_index = index + 1;
        current_index < formula.length() &&
            s_operators.find(formula[current_index]) == string::npos;
        current_index++);

    end_index = current_index - 1;
    subterm = formula.substr(index + 1, end_index - index);

    return parse_atomic(subterm, substitutions);
}

shared_ptr<Term> Term::parse_atomic(string term, const map<string, shared_ptr<Term>> &substitutions)
{
    std::regex regex_number(s_valid_number);
    std::regex regex_symbol(s_valid_symbol);

    if(std::regex_match(term, regex_number))
    {
		//parse number and return ConstantTerm
        stringstream s(term);
        double value;
        s >> value;
        return shared_ptr<Term>(new ConstantTerm(value));
    }
    else if(std::regex_match(term, regex_symbol))
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
