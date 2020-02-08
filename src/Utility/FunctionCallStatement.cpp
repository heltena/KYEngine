#include <KYEngine/Utility/FunctionCallStatement.h>

#include <iostream>
#include <sstream>

FunctionCallStatement::FunctionCallStatement()
    : m_hasErrors(false)
{
}

FunctionCallStatement::~FunctionCallStatement()
{
}

void FunctionCallStatement::init(std::string statement)
{
    size_t c = statement.find_first_of('(');
    if (c == std::string::npos) {
        m_hasErrors = true;
        return;
    }
    m_functionName = statement.substr(0, c);
    size_t c2 = statement.find_last_of(')');
    statement[c2] = ',';
    m_params.clear();
    std::string cur;
    int callParentesis;
    enum {
        BEGIN,
        STRING,
        STRING_ESCAPE,
        NUMBER,
        DECIMALS,
        END,
        CALL,
        ERROR
    } state = BEGIN;
    if (c+1 < c2) {
        for(int i = c+1; state != ERROR && i <= c2; i++) {
            char ch = statement[i];
            switch(state) {
                case BEGIN:
                    if (ch == ' ') {
                    } else if (ch == '\'') {
                        cur = "";
                        state = STRING;
                    } else if (isdigit(ch)) {
                        cur = ch;
                        state = NUMBER;
                    } else if (ch == '.') {
                        cur = "0.";
                        state = DECIMALS;
                    } else {
                        state = CALL;
                        cur = ch;
                        callParentesis = 0;
                    }
                    break;
                case STRING:
                    if (ch == '\'') {
                        state = END;
                    } else if (ch == '\\')
                        state = STRING_ESCAPE;
                    else
                        cur += ch;
                    break;
                case STRING_ESCAPE:
                    if (ch == '\'') {
                        cur += '\'';
                        state = STRING;
                    } else if (ch == '\\') {
                        cur += "\\";
                        state = STRING;
                    } else
                        state = ERROR;
                    break;
                case END:
                    if (ch == ' ') {
                    } else if (ch == ',') {
                        m_params.push_back(cur);
                        state = BEGIN;
                    } else {
                        state = ERROR;
                    }
                    break;
                case NUMBER:
                    if (isdigit(ch)) {
                        cur += ch;
                    } else if (ch == '.') {
                        cur += ch;
                        state = DECIMALS;
                    } else if (ch == ',') {
                        m_params.push_back(cur);
                        state = BEGIN;
                    } else
                        state = ERROR;
                    break;
                case DECIMALS:
                    if (isdigit(ch)) {
                        cur += ch;
                    } else if (ch == ',') {
                        m_params.push_back(cur);
                        state = BEGIN;
                    } else if (ch == ' ') {
                        state = END;
                    } else
                        state = ERROR;
                    break;
                case CALL:
                    if (ch == '(') {
                        callParentesis++;
                        cur += ch;
                    } else if (ch == ')') {
                        callParentesis--;
                        cur += ch;
                    } else if (ch == ',' && callParentesis == 0) {
                        m_params.push_back(cur);
                        state = BEGIN;
                    } else
                        cur += ch;
                    break;
                case ERROR:
                    break;
            }
        }
    }
    
    if (state == ERROR)
        m_hasErrors = true;
}

bool FunctionCallStatement::paramAsBool(int index) const
{
    return m_params[index] == "true";
}

double FunctionCallStatement::paramAsDouble(int index) const
{
    double d;
    std::stringstream ss(m_params[index]);
    ss >> d;
    return d;
}

int FunctionCallStatement::paramAsInt(int index) const
{
    int i;
    std::stringstream ss(m_params[index]);
    ss >> i;
    return i;
}

void FunctionCallStatement::debug()
{
    std::cout << "function: " << m_functionName << ", PARAMS: ";
    for(std::vector<std::string>::iterator it = m_params.begin(); it != m_params.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}