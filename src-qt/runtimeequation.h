#ifndef RUNTIMEEQUATION_H
#define RUNTIMEEQUATION_H

#include "RunTimeEquation_global.h"
#include "../LoadPlugins/interfaces.h"
#include <QObject>
#include <string>
#include <set>

//using std::string;
class mysetcompare{
public:
    bool operator() (std::string first,std::string second){
        return first>second;
    }
};

class RUNTIMEEQUATIONSHARED_EXPORT RunTimeEquation:public QObject, public RunTimeEquationInterface
{
    Q_OBJECT
    Q_INTERFACES(RunTimeEquationInterface)
public:
//    virtual ~RunTimeEquation();
    typedef int size_type;
    bool Set(std::string& string,std::string*& VarNames,double** Vars,int VarSz);
    double Calc();
private:
    void to_lowercase(std::string&s){
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
            *i = tolower(*i);
    }
    //void str_replace(std::string& str, std::string orig, std::string rep);
    std::string& str_replace(std::string &subject, const std::string &search, const std::string &replace);
    void sortVars();
    size_type VariableNumber(int j);
    bool isVariable(int j);
    size_type VarLength(int j);
    bool isFunc(int j);
    size_type FuncLength(int j);
    std::string FuncName(int j);
    const char* buffer;
    int cc;
    int OperandCount;
    double* BcpOperands;
    double*** Operands;

    double** arrVarVal;
    size_type CountVars;
    std::string equation;
    std::string* Operator;
    std::string* arrVarNames;
    //static const size_type FuncSize=20;
    //std::string arrFunc[20];
    std::set<std::string,mysetcompare> setFuncs;
};


#endif // RUNTIMEEQUATION_H
