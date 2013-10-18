////realization
#include "runtimeequation.h"
#include <cstdlib>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <list>
//void RunTimeEquation::str_replace(std::string& str, std::string orig, std::string rep){
//    std::string bcpstr;
//    int size=orig.size();
//    do{
//        bcpstr=str;
//        //str.find()
//        //str.replace()
//        str.rfind(orig);
//        //str.replace(str.rfind(orig),size,rep);
//    }while(bcpstr!=str);
//}
std::string& RunTimeEquation::str_replace(std::string &subject, const std::string &search, const std::string &replace)
{
    std::string buffer;

    int sealeng = search.length();
    int strleng = subject.length();

    if (sealeng==0)
        return subject;//no change

    for(int i=0, j=0; i<strleng; j=0 )
    {
        while (i+j<strleng && j<sealeng && subject[i+j]==search[j])
            j++;
        if (j==sealeng)//found 'search'
        {
            buffer.append(replace);
            i+=sealeng;
        }
        else
        {
            buffer.append( &subject[i++], 1);
        }
    }
    subject = buffer;
    return subject;
}

bool RunTimeEquation::isVariable(int j){
    size_type strlng;
    for(int i=0; i<CountVars;++i){
        strlng=arrVarNames[i].length();
        if(arrVarNames[i]==equation.substr(j,strlng)){
            return true;
        }
    }
    return false;
}


RunTimeEquation::size_type RunTimeEquation::VariableNumber(int j){
    size_type strlng;
    for(int i=0; i<CountVars;++i){
        strlng=arrVarNames[i].length();
        if(arrVarNames[i]==equation.substr(j,strlng)){
            return i;
        }
    }
    return false;
}


RunTimeEquation::size_type RunTimeEquation::VarLength(int j){
    size_type strlng;
    for(int i=0; i<CountVars;++i){
        strlng=arrVarNames[i].length();
//        qDebug()<<equation.midRef(j,strlng);
        if(arrVarNames[i]==equation.substr(j,strlng)){
            return strlng;
        }
    }
    return 0;
}


bool RunTimeEquation::isFunc(int j){
//    std::list<double> L;
//    L.push_back(0);
//    L.push_front(1);
//    L.insert(++L.begin(), 2);
//    std::list<double>::iterator iterator=L.begin();

    int strlng;
    for(std::set<std::string,mysetcompare>::iterator i=setFuncs.begin();i!=setFuncs.end();++i){
        strlng=(*i).length();
        if(*i==equation.substr(j,strlng)){
            return true;
        }
    }
//    for(int i=0; i<FuncSize;++i){
//        strlng=arrFunc[i].length();
//        if(arrFunc[i]==equation.substr(j,strlng)){
//            return true;
//        }
//    }
    return false;
}


RunTimeEquation::size_type RunTimeEquation::FuncLength(int j){
    size_type strlng;
    for(std::set<std::string,mysetcompare>::iterator i=setFuncs.begin(); i!=setFuncs.end();++i){
        strlng=(*i).length();
        if(*i==equation.substr(j,strlng)){
            return strlng;
        }
    }
//    for(int i=0; i<FuncSize;++i){
//        strlng=arrFunc[i].length();
//        if(arrFunc[i]==equation.substr(j,strlng)){
//            return strlng;
//        }
//    }
    return 0;
}


std::string RunTimeEquation::FuncName(int j){
    size_type strlng;
    for(std::set<std::string,mysetcompare>::iterator i=setFuncs.begin(); i!=setFuncs.end();++i){
        strlng=(*i).length();
        if(*i==equation.substr(j,strlng)){
            return *i;
        }
    }
    return "";
}

int DiffeQCompareVarNames(const void* first,const void* second){
    return -((std::string*)first)->length()+((std::string*)second)->length();
}


void RunTimeEquation::sortVars(){
    std::string* TmpNames;
    std::string* Tmp2Names;
    double** TmpVars;
    TmpNames=new std::string[CountVars];
    Tmp2Names=new std::string[CountVars];
    TmpVars=new double*[CountVars];
    for(int i=0;i<CountVars;++i){
        TmpNames[i]=arrVarNames[i];
        Tmp2Names[i]=arrVarNames[i];
        TmpVars[i]=arrVarVal[i];
    }
    qsort((void*)TmpNames,CountVars,sizeof(std::string),DiffeQCompareVarNames);
    for(int i=0;i<CountVars;++i){
        for(int k=0;k<CountVars;++k){
            if(TmpNames[i]==Tmp2Names[k]){
                //qDebug()<<TmpNames[i];
                arrVarNames[i]=TmpNames[i];
                arrVarVal[i]=TmpVars[k];
                break;
            }
        }
    }
}


bool RunTimeEquation::Set(std::string& string,std::string*& VarNames,double** Vars,int VarSz){
    buffer=new char;
    CountVars=VarSz;
    arrVarVal=new double*[CountVars];
    arrVarNames=new std::string[CountVars];
    for(int i=0;i<CountVars;++i){
//        qDebug()<<VarNames[i];
//        qDebug()<<*Vars[i];
        arrVarNames[i]=VarNames[i];
        arrVarVal[i]=Vars[i];
    }
    delete Vars;
    sortVars();
//    for(int i=0;i<CountVars;++i){
//        qDebug()<<arrVarNames[i];
//        qDebug()<<*arrVarVal[i];
//    }
    setFuncs.insert("lg10");
    setFuncs.insert("ln");
    setFuncs.insert("exp");
    setFuncs.insert("abs");
    setFuncs.insert("sqrt");
    setFuncs.insert("acosh");
    setFuncs.insert("asinh");
    setFuncs.insert("cosh");
    setFuncs.insert("sinh");
    setFuncs.insert("asin");
    setFuncs.insert("lg10");
    setFuncs.insert("acos");
    setFuncs.insert("sin");
    setFuncs.insert("cos");
    setFuncs.insert("actgh");
    setFuncs.insert("ctgh");
    setFuncs.insert("atgh");
    setFuncs.insert("actg");
    setFuncs.insert("tgh");
    setFuncs.insert("ctg");
    setFuncs.insert("atg");
    setFuncs.insert("tg");
/*    arrFunc[0]="lg10";
    arrFunc[1]="ln";
    arrFunc[2]="exp";
    arrFunc[3]="abs";
    arrFunc[4]="sqrt";
    arrFunc[5]="acosh";
    arrFunc[6]="asinh";
    arrFunc[7]="cosh";
    arrFunc[8]="sinh";
    arrFunc[9]="asin";
    arrFunc[10]="acos";
    arrFunc[11]="sin";
    arrFunc[12]="cos";
    arrFunc[13]="actgh";
    arrFunc[13]="ctgh";
    arrFunc[14]="atgh";
    arrFunc[15]="tgh";
    arrFunc[16]="actg";
    arrFunc[17]="ctg";
    arrFunc[18]="atg";
    arrFunc[19]="tg";
      */


    equation=string;
    to_lowercase(equation);
    equation="("+equation+")";
    equation=str_replace(equation, " ","");
    equation=str_replace(equation, "(-","(0-");
    equation=str_replace(equation, "-","-1*");
    equation=str_replace(equation, "log10","lg10");
    equation=str_replace(equation, "log","ln");
    equation=str_replace(equation, "tan","tg");
    int lng=equation.length();
    int **BracketsPos;
    BracketsPos=new int*[lng];
    for (int j = 0; j < lng; j++){
        BracketsPos[j] = new int[3];
        BracketsPos[j][0] =-1;
        BracketsPos[j][1] =-1;
        BracketsPos[j][2] =-1;
    }
    int **Blocks;
    int Blocks_size=0;
    int Blocks_shuted=0;
    Blocks=new int*[lng];
    for (int j = 0; j < lng; j++){
        Blocks[j] = new int[2];
        Blocks[j][0] =-1;
        Blocks[j][1] =-1;
    }


    std::string eq=equation;
    std::string eq2=equation;
    eq=str_replace(eq,"()","");
    eq2=str_replace(eq2,")(","");
    bool everythingOK=false;
    int last_variable=0;
    if(lng>0&&eq==equation&&eq2==equation){
        int count_unshuted=0;
        int count_brackets=0;
        //Создаем Массив скобок с диапазонами рассчетов и нужным порядком рассчетов
        for(int i=lng-1;i>=0;--i){
            if(equation[i]==')'){
                BracketsPos[count_brackets][1]=i;
                ++count_brackets;
                ++count_unshuted;
            }else if(equation[i]=='('){
                if(count_unshuted>0){
                    for(int k=count_brackets-1;k>=0;--k){
                        if(BracketsPos[k][0]==-1){
                            BracketsPos[k][0]=i;
                            --count_unshuted;
                            break;
                        }
                    }
                }else{
                    return false;
                }
            }
        }
        if(count_unshuted!=0){
            return false;
        }
////        ///////////////////////////////////////////
////        //Группировка операций с помощью скобок, по приоритету исполнения
        int lastoperpos;
        QChar lastoper;
        everythingOK=true;
        int last_num=0;

        for(int i=count_brackets-1;i>=0;--i){
            lastoperpos=BracketsPos[i][0];
            lastoper='(';
            //qDebug()<<i;
            //теперь для каждой скобки проделать сдедующую операцию
            for(int j=BracketsPos[i][0]+1;j<=BracketsPos[i][1];++j){
                if(equation[j]=='('){
                    //идем на последнюю скобку
                    for(int k=0; k<lng;++k){
                        if(BracketsPos[k][0]==j){
                            //qDebug()<<equation[j]<<j<<BracketsPos[k][1];
                            j=BracketsPos[k][1];
                            break;
                        }
                        if(k==lng-1){
                            return false;
                        }
                    }
                    continue;
                }else if(equation[j]==')'){
                    if(Blocks_size-Blocks_shuted!=0){
                        for(int k=Blocks_size-1;k>=0;--k){
                            if(Blocks[k][1]==-1){
                                Blocks[k][1]=j-1;
                                ++Blocks_shuted;
                            }
                        }
                    }
                }else if(equation[j]=='-'){
                    //если есть не закрытый блок block ends and block starts (во время добавления скобок проверка на символ -)
                    if(Blocks_size-Blocks_shuted!=0){
                        for(int k=Blocks_size-1;k>=0;--k){
                            if(Blocks[k][1]==-1){
                                Blocks[k][1]=j-1;
                                ++Blocks_shuted;
                            }
                        }
                    }
                    Blocks[Blocks_size][0]=j;
                    ++Blocks_size;
                    lastoperpos=j;
                    lastoper='-';

                }else if(equation[j]=='.'||isdigit(equation[j])){
                    last_num=j;
                }else if(equation[j]=='+'){
                    //если есть не закрытый блок - закрываем его
                    if(Blocks_size-Blocks_shuted!=0){
                        //qDebug()<<"exist";
                        for(int k=Blocks_size-1;k>=0;--k){
                            if(Blocks[k][1]==-1){
                                Blocks[k][1]=j-1;
                                ++Blocks_shuted;
                            }
                        }
                    }

                    lastoperpos=j;
                    lastoper='+';
                }else if(isFunc(j)){
                    //взять в скобки всю функцию
                    size_type jaft=j+FuncLength(j);
                    Blocks[Blocks_size][0]=j-1;
                    ++Blocks_size;
                    //std::cout<<"jaft="<<jaft<<std::endl;
                    for(int k=0; k<lng;++k){
                        if(BracketsPos[k][0]==jaft){
                            //qDebug()<<equation[j]<<j<<BracketsPos[k][1];
                            Blocks[Blocks_size-1][1]=BracketsPos[k][1]-1;
                            ++Blocks_shuted;
                            break;
                        }
                        if(k==lng-1){
                            //std::cout<<"k="<<k<<std::endl;
                            return false;
                        }
                    }
                    j=jaft-1;
                }else if(isVariable(j)){
                    last_variable=j+VarLength(j)-1;
                    j=j+VarLength(j)-1;

                    if(equation[j+1]=='^'||
                       equation[j+1]=='*'||
                       equation[j+1]=='/'||
                       equation[j+1]==')'||
                       equation[j+1]=='+'||
                       equation[j+1]=='-'){
                        continue;
                    }else{
//                        qDebug()<<j<<'t';
                        return false;
                    }

                }else if(equation[j]=='^'){

                    //если прошлый символ было число - берем координату прошлого оператора и добавляем новый блок
                    //если следующий символ - число или x e u буква - добавляем конец блока сразу за этим числом,
                    //если следующий символ - символ зарезервированный для функции - ищем конец открывающей скобки функции и записываем окончание блока сразу за этой скобкой
                    //если следующий символ - ( - ищем закрывающую скобку и записываем после нее закрытие блока.

                    if(last_num==j-1||last_variable==j-1){
                        //было число
                        if(equation[lastoperpos]!='^'){
                            Blocks[Blocks_size][0]=lastoperpos;
                            ++Blocks_size;
                        }else{
                            return false;
                        }
                    }
                    if(isFunc(j+1)){
                        size_type jaft=j+1+FuncLength(j+1);
                        if(equation[jaft]=='('){
                            Blocks[Blocks_size][0]=j;
                            ++Blocks_size;
                            for(int k=0; k<lng;++k){
                                if(BracketsPos[k][0]==jaft){
                                    Blocks[Blocks_size-2][1]=BracketsPos[k][1]-1;
                                    Blocks[Blocks_size-1][1]=BracketsPos[k][1]-1;
                                    ++Blocks_shuted;
                                    ++Blocks_shuted;
                                    break;
                                }
                                if(k==lng-1){
                                    return false;
                                }
                            }
                        }else{
                            return false;
                        }
                        j=jaft-1;
                    }else if(equation[j+1]=='.'||isdigit(equation[j+1])){
                        //цифра
                        int k=j+1;
                        while(equation[k]=='.'||isdigit(equation[k])){
                            ++k;
                        }
                        Blocks[Blocks_size-1][1]=k-1;
                        ++Blocks_shuted;
                    }else if(isVariable(j+1)){
                        Blocks[Blocks_size-1][1]=j+VarLength(j+1);
                        j=j+VarLength(j+1);
                        ++Blocks_shuted;
                    }else if(equation[j+1]=='('){
                        for(int k=0; k<lng;++k){
                            if(BracketsPos[k][0]==j+1){
                                Blocks[Blocks_size-1][1]=BracketsPos[k][1]-1;
                                ++Blocks_shuted;
                                break;
                            }
                            if(k==lng-1){
                                return false;
                            }
                        }
                    }
                    //lastoperpos=j;
                    //lastoper='^';
                }else if(equation[j]=='*'||equation[j]=='/'){
                    //qDebug()<<lastoper;
                    //если прошлый опрератор был + или ( тогда открыть скобку на + ( символе, записать оператор.
                    if(lastoper=='+'||lastoper=='('){
                        Blocks[Blocks_size][0]=lastoperpos;
                        ++Blocks_size;
                    }
                    lastoperpos=j;
                    lastoper=equation[j];
                }else{
                    return false;
                }
            }
            if(Blocks_size-Blocks_shuted>1){
               // qDebug()<<"Error3: Too many opened blocks";
                return false;
            }else if(Blocks_size-Blocks_shuted==1){
                for(int k=Blocks_size-1;k>=0;--k){
                    if(Blocks[k][1]==-1){
                        //qDebug()<<'t';
                        Blocks[k][1]=lng-1;
                        ++Blocks_shuted;
                        break;
                    }
                    if(k==0){
                        //qDebug()<<"Error4: sizes not match";
                        return false;
                    }
                }
            }
        }
        std::string eqwithblocks;
        bool breaked=false;
        std::string tmpshut;
        tmpshut="";
        bool isminus=false;
        for(int i=0; i<lng;++i){
            isminus=false;
            for(int k=0;k<Blocks_size;++k){
                if(Blocks[k][0]==i){
                    //
                    if(equation[i]=='+'){
                        tmpshut+="(";
                    }else if(equation[i]=='-'){
                        isminus=true;
                        if(equation[i-2]=='('&&equation[i-1]=='0'){
                            //std::cout<<"t"<<eqwithblocks<<std::endl;
//                            std::string tmp;
//                            tmp=equation.substr(0,i-2);
//                            tmp+=equation.substr(0,lng);
//                            equation=tmp;
//                            equation[i-1]='(';
//                            equation[i]='(';
//                            equation[i+1]='0';
                            eqwithblocks[eqwithblocks.length()-1]='(';
                            //eqwithblocks+='-';
                            tmpshut+="-";
                        }else{
                            tmpshut+="+(-";
                        }
                    }else if(equation[i]=='('){
                        tmpshut+="(";
                    }else if(equation[i]=='*'||equation[i]=='/'){
                        tmpshut+="(";
                    }else{
                        tmpshut+="(";
                    }
                    breaked=true;
                }else if(Blocks[k][1]==i){
                    tmpshut+=")";
                    breaked=true;
                }
            }
            if(!isminus){
                eqwithblocks+=equation[i];
            }
            eqwithblocks+=tmpshut;
            tmpshut="";
        }
        equation=eqwithblocks;
        ///////////////////////////////////////////
    }else{
        return false;
    }
//    //qDebug()<<equation;
    //std::cout<<equation<<std::endl;
    lng=equation.length();
    delete BracketsPos;
    if(everythingOK){
        int **BracketsPos;
        BracketsPos=new int*[lng];
        for (int j = 0; j < lng; j++){
            BracketsPos[j] = new int[3];
            BracketsPos[j][0] =-1;
            BracketsPos[j][1] =-1;
            BracketsPos[j][2] =-1;
        }
        Operands=new double**[lng];
        for (int j = 0; j < lng; j++){
            Operands[j] = new double*[4];
        }
        Operator=new std::string[lng];
        int count_unshuted=0;
        int count_brackets=0;
        for(int i=lng-1;i>=0;--i){
            if(equation[i]==')'){
                BracketsPos[count_brackets][1]=i;
                ++count_brackets;
                ++count_unshuted;
            }else if(equation[i]=='('){
                if(count_unshuted>0){
                    for(int k=count_brackets-1;k>=0;--k){
                        if(BracketsPos[k][0]==-1){
                            BracketsPos[k][0]=i;
                            --count_unshuted;
                            break;
                        }
                    }
                }else{
                    return false;
                }
            }
        }
        if(count_unshuted!=0){
            return false;
        }
        //        ----------------------
        //        Рассчет значений в каждой из скобок
        //qDebug()<<lng;
        //цикл по скобкам
        OperandCount=0;
        int last_num=-1;
        int numbstarts;
        char lastOperator;
        std::string last_numstr;
        double last_numdbl=0;
        bool wasminus=false;
        for(int i=count_brackets-1;i>=0;--i){
            //теперь для каждой скобки проделать сдедующую операцию
            lastOperator='(';
            for(int j=BracketsPos[i][0]+1;j<=BracketsPos[i][1];++j){
                if(equation[j]=='('){
                    for(int k=0; k<lng;++k){
                        if(BracketsPos[k][0]==j){
                            //qDebug()<<equation[j]<<j<<BracketsPos[k][1];
                            j=BracketsPos[k][1];
                            break;
                        }
                    }
                    continue;
                }else if(isVariable(j)){
                    last_variable=j;
                    j=j+VarLength(j)-1;
                }else if(equation[j]=='.'||isdigit(equation[j])){
                    //цифра
                    if(last_num+1==j){
                        last_numstr+=equation[j];
                    }else{
                        numbstarts=j;
                        last_numstr=equation[j];
                    }
                    if(wasminus){
                        last_numstr='-'+last_numstr;
                        wasminus=false;
                    }
                    buffer=last_numstr.c_str();
                    last_numdbl=atof(buffer);
                    last_num=j;
                }else if(equation[j]==')'){
///////////////////////////////////////////////////////////////////
                    //текущий символ является оператором )
//                    if(equation[j]==')'&&OperandCount>0){
//                        Operands[OperandCount-1][0]=new double(BracketsPos[i][1]);
//                    }
                    if(equation[j-1]==')'){
                        if(lastOperator=='('){

                        }else{
                            bool found=false;
                            int l=j-1;
                            while(!found&&l>0){
                                if(equation[l]==')'){
                                    for(int m=OperandCount;m>=0;--m){
                                        if(*Operands[m][0]==l){
                                            *Operands[OperandCount-1][0]=j;
                                            Operands[OperandCount-1][2]=Operands[m][3];
//                                            Operands[OperandCount][1]=Operands[OperandCount-1][3];
//                                            Operands[OperandCount][2]=new double(0);
//                                            Operands[OperandCount][3]=new double(0);
//                                            ++OperandCount;
                                            found=true;
                                            break;
                                        }
                                    }
                                    --l;
                                }else{
                                    //ошибка
                                    //std::cout<<"warn12"<<std::endl;
                                    return false;
                                }
                            }
                            if(!found){
                                //std::cout<<"warn2"<<std::endl;
                                return false;
                            }
                        }
                    }else{
                        if(lastOperator=='('){
                            Operands[OperandCount][0]=new double(j);
                            Operator[OperandCount]="+";
                            Operands[OperandCount][1]=new double(0);
                            Operands[OperandCount][3]=new double(0);
                            if(equation[j-1]=='('){
                                //std::cout<<"false11"<<std::endl;
                                return false;
                            }else if(last_num+1==j){
                                //значит слева число
                                //std::cout<<"asdfasdf"<<last_numdbl<<std::endl;
                                Operands[OperandCount][2]=new double(last_numdbl);
                            }else if(isVariable(last_variable)){
                                //слева должен быть параметр

                                Operands[OperandCount][2]=arrVarVal[VariableNumber(last_variable)];
                            }else{
                                //std::cout<<"false21"<<std::endl;
                                return false;
                            }
                            ++OperandCount;
                        }else{
                            //std::cout<<'b'<<j<<std::endl;
                            *Operands[OperandCount-1][0]=j;
                            if(equation[j-1]=='('){
                                //std::cout<<"false12"<<std::endl;
                                return false;
                            }else if(last_num+1==j){
                                //значит слева число
                                Operands[OperandCount-1][2]=new double(last_numdbl);
                            }else if(isVariable(last_variable)){
                                //слева должен быть параметр
                                //std::cout<<"asdasd"<<*arrVarVal[VariableNumber(last_variable)]<<std::endl;
                                Operands[OperandCount-1][2]=arrVarVal[VariableNumber(last_variable)];
                            }else{
                                //std::cout<<"false22"<<std::endl;
                                return false;
                            }
                        }
                    }
//\\\\\/////////////////////////////////////////////////////////
                }else if(isFunc(j)||equation[j]=='^'
                        ||equation[j]=='*'
                        ||equation[j]=='/'
                        ||equation[j]=='+'
                        ||equation[j]=='-'){
///////////////////////////////////////////////////////////////////
        //текущий символ является оператором * / + - или функцией
                    if(equation[j]=='-'){
                        if(equation[j-1]!='('){
                            Operator[OperandCount]="+";
                        }
                        wasminus=true;
                    }else if(isFunc(j)){
                        Operator[OperandCount]=FuncName(j);
                    }else{
                        Operator[OperandCount]=equation[j];
                    }

                    //qDebug()<<last_numdbl;
                    if(equation[j]=='^'
                       ||equation[j]=='*'
                       ||equation[j]=='/'
                       ||equation[j]=='+'
                       ||(equation[j]=='-'&&equation[j-1]!='('))
                    {
        //текущий символ является оператором * / + -
                        //std::cout<<j<<std::endl;
                        if(equation[j-1]==')'){
                            //слева от операторов скобка )
                            //текущий любой, предыдущий символ скобка )
                            //                        если была закрывающая скобочка до этого оператора
                            //найти закрывающую скобочку в operands и присвоить ее значение для предыдущего 2 операнда

                            //цикличный поиск значения в j-1 скобке.
                            //std::cout<<"bracket"<<std::endl;
                            bool found=false;
                            int l=j-1;
                            while(!found&&l>0){
                                if(equation[l]==')'){
                                    for(int m=OperandCount;m>=0;--m){
                                        if(*Operands[m][0]==l){
                                            if(lastOperator!='('){
                                                Operands[OperandCount-1][2]=Operands[m][3];
                                                Operands[OperandCount][0]=new double(0);
                                                Operands[OperandCount][1]=Operands[OperandCount-1][3];
                                                Operands[OperandCount][2]=new double(0);
                                                Operands[OperandCount][3]=new double(0);
                                            }else{
                                                Operands[OperandCount][0]=new double(0);
                                                Operands[OperandCount][1]=Operands[m][3];
                                                Operands[OperandCount][2]=new double(0);
                                                Operands[OperandCount][3]=new double(0);
                                            }
                                            ++OperandCount;
                                            found=true;
                                            break;
                                        }
                                    }
                                    --l;
                                }else{
                                    //ошибка
                                    //std::cout<<"warn13"<<std::endl;
                                    return false;
                                }
                            }
                            if(!found){
                                //std::cout<<"warn2"<<std::endl;
                                return false;
                            }

/*                            if(lastOperator!='('){
                                for(int m=OperandCount;m>=0;--m){
                                    if(*Operands[m][0]==j-1){
                                        Operands[OperandCount-1][2]=Operands[m][2];
                                        if(equation[j]!=')'){
                                            Operands[OperandCount][1]=Operands[OperandCount-1][3];
                                            Operands[OperandCount][2]=new double(0);
                                            Operands[OperandCount][3]=new double(0);
                                        }
                                        break;
                                    }
                                }
                            }else{
                                //если до этого ( оператор тогда ищем значение для скобки
                                //и вставляем его в текущий оператор


                                if(equation[j]!=')'){
                                    //текущий не скобка ) и предыдущий символ не ) и последний оператор (
                                    for(int m=OperandCount;m>=0;--m){
                                        if(*Operands[m][0]==j-1){
                                                Operands[OperandCount][1]=Operands[m][2];
                                                Operands[OperandCount][2]=new double(0);
                                                Operands[OperandCount][3]=new double(0);
                                            break;
                                        }
                                    }
                                }
                            }
*/
                        }else if(last_num+1==j){
                            //std::cout<<"number"<<std::endl;
                            //значит слева число
                            if(lastOperator!='('){
                                *Operands[OperandCount-1][2]=last_numdbl;
                                Operands[OperandCount][0]=new double(0);
                                Operands[OperandCount][1]=Operands[OperandCount-1][3];
                                Operands[OperandCount][2]=new double(0);
                                Operands[OperandCount][3]=new double(0);
                            }else{
                                Operands[OperandCount][0]=new double(0);
                                Operands[OperandCount][1]=new double(last_numdbl);
                                Operands[OperandCount][2]=new double(0);
                                Operands[OperandCount][3]=new double(0);
                            }
                            ++OperandCount;
                            //qDebug()<<*Operands[OperandCount][1];
                        }else{
                            //std::cout<<"parameter"<<std::endl;
                            //слева должен быть параметр
                            //qDebug()<<"varval: "<<last_variable<<*arrVarVal[VariableNumber(last_variable)];
                            if(isVariable(last_variable)){
                                if(lastOperator=='('){
                                    Operands[OperandCount][0]=new double(0);
                                    Operands[OperandCount][1]=arrVarVal[VariableNumber(last_variable)];
                                    Operands[OperandCount][2]=new double(0);
                                    Operands[OperandCount][3]=new double(0);
                                }else{
                                    Operands[OperandCount-1][2]=arrVarVal[VariableNumber(last_variable)];
                                    Operands[OperandCount][0]=new double(0);
                                    Operands[OperandCount][1]=Operands[OperandCount-1][3];
                                    Operands[OperandCount][2]=new double(0);
                                    Operands[OperandCount][3]=new double(0);
                                }
                                ++OperandCount;
                            }
                        }

                        lastOperator=equation[j];
                    }else if(isFunc(j)){
                        //это какая-то из функций
                        j=j+FuncLength(j)-1;
                        if(equation[j+1]=='('){
                            //записать функцию в текущий оператор.
                            //найти через ( - значение для ), записать ссылку, на результат внутри скобки, в текущий операнд.
                            for(int k=0; k<lng;++k){
                                if(BracketsPos[k][0]==j+1){
                                    bool found=false;
                                    int l=BracketsPos[k][1];
                                    while(!found&&l>0){
                                        //std::cout<<l<<equation[l]<<std::endl;
                                        if(equation[l]==')'){
                                            for(int m=OperandCount;m>=0;--m){
                                                if(*Operands[m][0]==l){
                                                    Operands[OperandCount][0]=Operands[m][0];
                                                    Operands[OperandCount][1]=Operands[m][3];
                                                    Operands[OperandCount][2]=new double(0);
                                                    Operands[OperandCount][3]=new double(0);
                                                     ++OperandCount;
                                                    found=true;
                                                    break;
                                                }
                                            }
                                            --l;
                                        }else{
                                            //ошибка
                                            //std::cout<<"warn14"<<std::endl;
                                            return false;
                                        }
                                    }
                                    if(!found){
                                        //std::cout<<"warn2"<<std::endl;
                                        return false;
                                    }
/*                                    for(int m=OperandCount;m>=0;--m){
                                        if(*Operands[m][0]==BracketsPos[k][1]){
                                            Operands[OperandCount][0]=Operands[m][0];
                                            Operands[OperandCount][1]=Operands[m][3];
                                            Operands[OperandCount][2]=new double(0);
                                            Operands[OperandCount][3]=new double(0);
                                            break;
                                        }
                                    }*/
                                    break;
                                }
                            }
                        }else{
                            return false;
                        }

                    }
//\\\\//////////////////////////////////////////////////////////////////////////////////
                }else{
                    return false;
                }
            }
        }
//        cc=0;
//        BcpOperands=new double[OperandCount];
//        while(cc<OperandCount){
//            BcpOperands[cc]=*Operands[cc][1];
//            ++cc;
//        }

    }else{
        return false;
    }
//    cc=0;
//    while(cc<OperandCount){
//        std::cout<<*Operands[cc][1]<<Operator[cc]<<*Operands[cc][2]<<std::endl;
//        ++cc;
//    }
    return true;
}


double RunTimeEquation::Calc(){
//backup variables
//    double* BackupVarVal;
//    BackupVarVal=new double[CountVars];
//    for(int i=0;i<CountVars;++i){
//        BackupVarVal[i]=*arrVarVal[i];
//        //qDebug()<<*arrVarVal[i];
//    }
//tacking and setting all operands from backup
//    cc=0;
//    while(cc<OperandCount){
//        *Operands[cc][1]=BcpOperands[cc];
//        ++cc;
//    }
//taking and setting all variables from backup
//    for(int i=0;i<CountVars;++i){
//        *arrVarVal[i]=BackupVarVal[i];
//    }
    //std::string lastOperator;
    //lastOperator=")";

    cc=0;
    //std::cout<<"calc()"<<OperandCount<<std::endl;
    while(cc<OperandCount){
        if(Operator[cc]=="-"){
            *Operands[cc][3]=*Operands[cc][1]-*Operands[cc][2];
        }else if(Operator[cc]=="+"){
            *Operands[cc][3]=*Operands[cc][1]+*Operands[cc][2];
        }else if(Operator[cc]=="*"){
            *Operands[cc][3]=*Operands[cc][1]**Operands[cc][2];
        }else if(Operator[cc]=="/"){
            *Operands[cc][3]=*Operands[cc][1]/ *Operands[cc][2];
        }else if(Operator[cc]=="^"){
            *Operands[cc][3]=pow(*Operands[cc][1], *Operands[cc][2]);
        }else if(Operator[cc]=="sqrt"){
            *Operands[cc][3]=sqrt(*Operands[cc][1]);
        }else if(Operator[cc]=="cos"){
            *Operands[cc][3]=cos(*Operands[cc][1]);
        }else if(Operator[cc]=="sin"){
            *Operands[cc][3]=sin(*Operands[cc][1]);
        }else if(Operator[cc]=="exp"){
            *Operands[cc][3]=exp(*Operands[cc][1]);
        }else if(Operator[cc]=="tg"){
            *Operands[cc][3]=tan(*Operands[cc][1]);
        }else if(Operator[cc]=="ctg"){
            *Operands[cc][3]=1/tan(*Operands[cc][1]);
        }else if(Operator[cc]=="acos"){
            *Operands[cc][3]=acos(*Operands[cc][1]);
        }else if(Operator[cc]=="asin"){
            *Operands[cc][3]=asin(*Operands[cc][1]);
        }else if(Operator[cc]=="atg"){
            *Operands[cc][3]=atan(*Operands[cc][1]);
        }else if(Operator[cc]=="actg"){
            *Operands[cc][3]=atan(1/ *Operands[cc][1]);
        }else if(Operator[cc]=="cosh"){
            *Operands[cc][3]=cosh(*Operands[cc][1]);
        }else if(Operator[cc]=="sinh"){
            *Operands[cc][3]=sinh(*Operands[cc][1]);
        }else if(Operator[cc]=="tgh"){
            *Operands[cc][3]=tanh(*Operands[cc][1]);
        }else if(Operator[cc]=="ctgh"){
            *Operands[cc][3]=1/tanh(*Operands[cc][1]);
        }else if(Operator[cc]=="ln"){
            *Operands[cc][3]=log(*Operands[cc][1]);
        }else if(Operator[cc]=="lg10"){
            *Operands[cc][3]=log10(*Operands[cc][1]);
        }else if(Operator[cc]=="abs"){
            *Operands[cc][3]=fabs(*Operands[cc][1]);
        }else if(Operator[cc]=="atgh"){
            *Operands[cc][3]=atanh(*Operands[cc][1]);
        }else if(Operator[cc]=="actgh"){
            //HArccotan(X) = Log((X + 1) / (X - 1)) / 2
            *Operands[cc][3]=log((*Operands[cc][1]+1)/(*Operands[cc][1]-1))/2;
        }else if(Operator[cc]=="asinh"){
            *Operands[cc][3]=asinh(*Operands[cc][1]);
        }else if(Operator[cc]=="acosh"){
            *Operands[cc][3]=acosh(*Operands[cc][1]);
        }
        //std::cout<<*Operands[cc][1]<<Operator[cc]<<*Operands[cc][2]<<"="<<*Operands[cc][3]<<std::endl;
        ++cc;
    }
    //std::cout<<*Operands[OperandCount-1][3]<<std::endl;
//setting all variables to initial from backup
//    for(int i=0;i<CountVars;++i){
//        *arrVarVal[i]=BackupVarVal[i];
//    }

    return *Operands[OperandCount-1][3];//*Operands[cc-1][1];
    //return 111;
}
Q_EXPORT_PLUGIN2(RunTimeEquationInterface,RunTimeEquation)
