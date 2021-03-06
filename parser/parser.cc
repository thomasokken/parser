#include <stdio.h>
#include <string.h>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <float.h>

////////////////////////////////
/////  class declarations  /////
////////////////////////////////

class OutputStream {
    public:

    virtual ~OutputStream() {}

    virtual void write(std::string) = 0;
    virtual void write(double d);
    virtual void newline();
};

class FileOutputStream : public OutputStream {
    private:

    FILE *file;
    bool autoFlush;

    public:

    FileOutputStream(FILE *file, bool autoFlush = false) : file(file), autoFlush(autoFlush) {}
    ~FileOutputStream();
    void write(std::string text);
};

class Function;

class Context {

    private:

    std::map<std::string, double> variables;
    std::map<std::string, Function *> functions;
    std::vector<std::map<std::string, double> *> parameters;

    public:

    ~Context();
    void setVariable(std::string name, double value);
    double getVariable(std::string name);
    void setFunction(std::string name, Function *function);
    Function *getFunction(std::string name);
    void push(std::vector<std::string> &names, std::vector<double> &values);
    void pop();
    void dump(OutputStream *os, bool alg);
};

class Evaluator {

    private:

    int tpos;

    public:

    Evaluator(int pos) : tpos(pos) {}
    virtual ~Evaluator() {}

    int pos() { return tpos; }

    virtual double eval(Context *c) = 0;
    virtual void printAlg(OutputStream *os) = 0;
    virtual void printRpn(OutputStream *os) = 0;
};

class Abs : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Abs(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Abs();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Acos : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Acos(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Acos();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Asin : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Asin(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Asin();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Atan : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Atan(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Atan();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Call : public Evaluator {

    private:

    std::string name;
    std::vector<Evaluator *> *evs;

    public:

    Call(int pos, std::string name, std::vector<Evaluator *> *evs) : Evaluator(pos), name(name), evs(evs) {}
    ~Call();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Cos : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Cos(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Cos();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Difference : public Evaluator {

    private:

    Evaluator *left, *right;

    public:

    Difference(int pos, Evaluator *left, Evaluator *right) : Evaluator(pos), left(left), right(right) {}
    ~Difference();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Exp : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Exp(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Exp();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Function {

    private:

    std::vector<std::string> paramNames;
    Evaluator *evaluator;

    public:

    Function(std::vector<std::string> &paramNames, Evaluator *ev) : paramNames(paramNames), evaluator(ev) {}
    ~Function();
    double eval(std::vector<double> params, Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Identity : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Identity(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Identity();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Literal : public Evaluator {

    private:

    double value;

    public:

    Literal(int pos, double value) : Evaluator(pos), value(value) {}
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Log : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Log(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Log();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Max : public Evaluator {

    private:

    std::vector<Evaluator *> *evs;

    public:

    Max(int pos, std::vector<Evaluator *> *evs) : Evaluator(pos), evs(evs) {}
    ~Max();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Min : public Evaluator {

    private:

    std::vector<Evaluator *> *evs;

    public:

    Min(int pos, std::vector<Evaluator *> *evs) : Evaluator(pos), evs(evs) {}
    ~Min();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Negative : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Negative(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Negative();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Positive : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Positive(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Positive();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Power : public Evaluator {

    private:

    Evaluator *left, *right;

    public:

    Power(int pos, Evaluator *left, Evaluator *right) : Evaluator(pos), left(left), right(right) {}
    ~Power();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Product : public Evaluator {

    private:

    Evaluator *left, *right;

    public:

    Product(int pos, Evaluator *left, Evaluator *right) : Evaluator(pos), left(left), right(right) {}
    ~Product();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Quotient : public Evaluator {

    private:

    Evaluator *left, *right;

    public:

    Quotient(int pos, Evaluator *left, Evaluator *right) : Evaluator(pos), left(left), right(right) {}
    ~Quotient();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Sin : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Sin(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Sin();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Sqrt : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Sqrt(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Sqrt();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Sum : public Evaluator {

    private:

    Evaluator *left, *right;

    public:

    Sum(int pos, Evaluator *left, Evaluator *right) : Evaluator(pos), left(left), right(right) {}
    ~Sum();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Tan : public Evaluator {

    private:

    Evaluator *ev;

    public:

    Tan(int pos, Evaluator *ev) : Evaluator(pos), ev(ev) {}
    ~Tan();
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

class Variable : public Evaluator {

    private:

    std::string name;

    public:

    Variable(int pos, std::string name) : Evaluator(pos), name(name) {}
    double eval(Context *c);
    void printAlg(OutputStream *os);
    void printRpn(OutputStream *os);
};

//////////////////////////
/////  OutputStream  /////
//////////////////////////

void OutputStream::write(double d) {
    char buf[50];
    sprintf(buf, "%.9g", d);
    write(buf);
}
void OutputStream::newline() {
    write("\n");
}

//////////////////////////////
/////  FileOutputStream  /////
//////////////////////////////

FileOutputStream::~FileOutputStream() {
    fclose(file);
}

void FileOutputStream::write(std::string text) {
    const char *s = text.c_str();
    fwrite(s, 1, strlen(s), file);
    if (autoFlush)
        fflush(file);
}

/////////////////////
/////  Context  /////
/////////////////////

Context::~Context() {
    for (std::map<std::string, Function *>::iterator it = functions.begin(); it != functions.end(); it++)
        delete it->second;
    for (int i = 0; i < parameters.size(); i++)
        delete parameters[i];
}

void Context::setVariable(std::string name, double value) {
    variables[name] = value;
}

double Context::getVariable(std::string name) {
    for (int i = parameters.size() - 1; i >= 0; i--) {
        std::map<std::string, double> *m = parameters[i];
        std::map<std::string, double>::iterator t = m->find(name);
        if (t != m->end())
            return (*m)[name];
    }
    std::map<std::string, double>::iterator t = variables.find(name);
    if (t != variables.end())
        return 0;
    else
        return variables[name];
}

void Context::setFunction(std::string name, Function *function) {
    std::map<std::string, Function *>::iterator it = functions.find(name);
    if (it != functions.end())
        delete it->second;
    functions[name] = function;
}

Function *Context::getFunction(std::string name) {
    return functions[name];
}

void Context::push(std::vector<std::string> &names, std::vector<double> &values) {
    std::map<std::string, double> *h = new std::map<std::string, double>;
    for (int i = 0; i < names.size(); i++)
        (*h)[names[i]] = values[i];
    parameters.push_back(h);
}

void Context::pop() {
    int n = parameters.size() - 1;
    delete parameters[n];
    parameters.erase(parameters.begin() + n);
}

void Context::dump(OutputStream *os, bool alg) {
    for (std::map<std::string, double>::iterator it = variables.begin(); it != variables.end(); it++) {
        os->write(it->first);
        os->write("=");
        os->write(it->second);
        os->newline();
    }
    for (std::map<std::string, Function *>::iterator it = functions.begin(); it != functions.end(); it++) {
        os->write(it->first);
        os->write(alg ? "=" : ":");
        if (alg)
            it->second->printAlg(os);
        else
            it->second->printRpn(os);
        os->newline();
    }
}

/////////////////
/////  Abs  /////
/////////////////

Abs::~Abs() {
    delete ev;
}

double Abs::eval(Context *c) {
    return fabs(ev->eval(c));
}

void Abs::printAlg(OutputStream *os) {
    os->write("abs(");
    ev->printAlg(os);
    os->write(")");
}

void Abs::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" abs");
}

//////////////////
/////  Acos  /////
//////////////////

Acos::~Acos() {
    delete ev;
}

double Acos::eval(Context *c) {
    return acos(ev->eval(c));
}

void Acos::printAlg(OutputStream *os) {
    os->write("acos(");
    ev->printAlg(os);
    os->write(")");
}

void Acos::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" acos");
}

//////////////////
/////  Asin  /////
//////////////////

Asin::~Asin() {
    delete ev;
}

double Asin::eval(Context *c) {
    return asin(ev->eval(c));
}

void Asin::printAlg(OutputStream *os) {
    os->write("asin(");
    ev->printAlg(os);
    os->write(")");
}

void Asin::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" asin");
}

//////////////////
/////  Atan  /////
//////////////////

Atan::~Atan() {
    delete ev;
}

double Atan::eval(Context *c) {
    return atan(ev->eval(c));
}

void Atan::printAlg(OutputStream *os) {
    os->write("atan(");
    ev->printAlg(os);
    os->write(")");
}

void Atan::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" atan");
}

//////////////////
/////  Call  /////
//////////////////

Call::~Call() {
    for (int i = 0; i < evs->size(); i++)
        delete (*evs)[i];
    delete evs;
}

double Call::eval(Context *c) {
    int n = evs->size();
    std::vector<double> values(n);
    for (int i = 0; i < n; i++)
        values[i] = (*evs)[i]->eval(c);
    Function *f = c->getFunction(name);
    double res = f->eval(values, c);
    return res;
}

void Call::printAlg(OutputStream *os) {
    os->write(name);
    os->write("(");
    for (int i = 0; i < evs->size(); i++) {
        if (i != 0)
            os->write(",");
        (*evs)[i]->printAlg(os);
    }
    os->write(")");
}

void Call::printRpn(OutputStream *os) {
    for (int i = 0; i < evs->size(); i++) {
        (*evs)[i]->printRpn(os);
        os->write(" ");
    }
    os->write(name);
}

/////////////////
/////  Cos  /////
/////////////////

Cos::~Cos() {
    delete ev;
}

double Cos::eval(Context *c) {
    return cos(ev->eval(c));
}

void Cos::printAlg(OutputStream *os) {
    os->write("cos(");
    ev->printAlg(os);
    os->write(")");
}

void Cos::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" ");
}

////////////////////////
/////  Difference  /////
////////////////////////

Difference::~Difference() {
    delete left;
    delete right;
}

double Difference::eval(Context *c) {
    return left->eval(c) - right->eval(c);
}

void Difference::printAlg(OutputStream *os) {
    left->printAlg(os);
    os->write("-");
    right->printAlg(os);
}

void Difference::printRpn(OutputStream *os) {
    left->printRpn(os);
    os->write(" ");
    right->printRpn(os);
    os->write(" -");
}

/////////////////
/////  Exp  /////
/////////////////

Exp::~Exp() {
    delete ev;
}

double Exp::eval(Context *c) {
    return exp(ev->eval(c));
}

void Exp::printAlg(OutputStream *os) {
    os->write("exp(");
    ev->printAlg(os);
    os->write(")");
}

void Exp::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" exp");
}

//////////////////////
/////  Function  /////
//////////////////////

Function::~Function() {
    delete evaluator;
}

double Function::eval(std::vector<double> params, Context *c) {
    c->push(paramNames, params);
    double ret = evaluator->eval(c);
    c->pop();
    return ret;
}

void Function::printAlg(OutputStream *os) {
    os->write("(");
    for (int i = 0; i < paramNames.size(); i++) {
        if (i != 0)
            os->write(",");
        os->write(paramNames[i]);
    }
    os->write(")=>");
    evaluator->printAlg(os);
}

void Function::printRpn(OutputStream *os) {
    for (int i = 0; i < paramNames.size(); i++) {
        os->write(paramNames[i]);
        os->write(" ");
    }
    evaluator->printRpn(os);
}

//////////////////////
/////  Identity  /////
//////////////////////

Identity::~Identity() {
    delete ev;
}

double Identity::eval(Context *c) {
    return ev->eval(c);
}

void Identity::printAlg(OutputStream *os) {
    os->write("(");
    ev->printAlg(os);
    os->write(")");
}

void Identity::printRpn(OutputStream *os) {
    ev->printRpn(os);
}

/////////////////////
/////  Literal  /////
/////////////////////

double Literal::eval(Context *c) {
    return value;
}

void Literal::printAlg(OutputStream *os) {
    os->write(value);
}

void Literal::printRpn(OutputStream *os) {
    os->write(value);
}

/////////////////
/////  Log  /////
/////////////////

Log::~Log() {
    delete ev;
}

double Log::eval(Context *c) {
    return log(ev->eval(c));
}

void Log::printAlg(OutputStream *os) {
    os->write("log(");
    ev->printAlg(os);
    os->write(")");
}

void Log::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" log");
}

/////////////////
/////  Max  /////
/////////////////

Max::~Max() {
    for (int i = 0; i < evs->size(); i++)
        delete (*evs)[i];
    delete evs;
}

double Max::eval(Context *c) {
    double res = -DBL_MAX;
    for (int i = 0; i < evs->size(); i++) {
        double x = (*evs)[i]->eval(c);
        if (x > res)
            res = x;
    }
    return res;
}

void Max::printAlg(OutputStream *os) {
    os->write("max(");
    for (int i = 0; i < evs->size(); i++) {
        if (i != 0)
            os->write(",");
        (*evs)[i]->printAlg(os);
    }
    os->write(")");
}

void Max::printRpn(OutputStream *os) {
    for (int i = 0; i < evs->size(); i++) {
        (*evs)[i]->printRpn(os);
        os->write(" ");
    }
    os->write((double) evs->size());
    os->write(" max");
}

/////////////////
/////  Min  /////
/////////////////

Min::~Min() {
    for (int i = 0; i < evs->size(); i++)
        delete (*evs)[i];
    delete evs;
}

double Min::eval(Context *c) {
    double res = DBL_MAX;
    for (int i = 0; i < evs->size(); i++) {
        double x = (*evs)[i]->eval(c);
        if (x < res)
            res = x;
    }
    return res;
}

void Min::printAlg(OutputStream *os) {
    os->write("min(");
    for (int i = 0; i < evs->size(); i++) {
        if (i != 0)
            os->write(",");
        (*evs)[i]->printAlg(os);
    }
    os->write(")");
}

void Min::printRpn(OutputStream *os) {
    for (int i = 0; i < evs->size(); i++) {
        (*evs)[i]->printRpn(os);
        os->write(" ");
    }
    os->write((double) evs->size());
    os->write(" min");
}

//////////////////////
/////  Negative  /////
//////////////////////

Negative::~Negative() {
    delete ev;
}

double Negative::eval(Context *c) {
    return -ev->eval(c);
}

void Negative::printAlg(OutputStream *os) {
    os->write("-");
    ev->printAlg(os);
}

void Negative::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" +/-");
}

//////////////////////
/////  Positive  /////
//////////////////////

Positive::~Positive() {
    delete ev;
}

double Positive::eval(Context *c) {
    return ev->eval(c);
}

void Positive::printAlg(OutputStream *os) {
    os->write("+");
    ev->printAlg(os);
}

void Positive::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" nop");
}

///////////////////
/////  Power  /////
///////////////////

Power::~Power() {
    delete left;
    delete right;
}

double Power::eval(Context *c) {
    return pow(left->eval(c), right->eval(c));
}

void Power::printAlg(OutputStream *os) {
    left->printAlg(os);
    os->write("^");
    right->printAlg(os);
}

void Power::printRpn(OutputStream *os) {
    left->printRpn(os);
    os->write(" ");
    right->printRpn(os);
    os->write(" ^");
}

/////////////////////
/////  Product  /////
/////////////////////

Product::~Product() {
    delete left;
    delete right;
}

double Product::eval(Context *c) {
    return left->eval(c) * right->eval(c);
}

void Product::printAlg(OutputStream *os) {
    left->printAlg(os);
    os->write("*");
    right->printAlg(os);
}

void Product::printRpn(OutputStream *os) {
    left->printRpn(os);
    os->write(" ");
    right->printRpn(os);
    os->write(" *");
}

//////////////////////
/////  Quotient  /////
//////////////////////

Quotient::~Quotient() {
    delete left;
    delete right;
}

double Quotient::eval(Context *c) {
    return left->eval(c) / right->eval(c);
}

void Quotient::printAlg(OutputStream *os) {
    left->printAlg(os);
    os->write("/");
    right->printAlg(os);
}

void Quotient::printRpn(OutputStream *os) {
    left->printRpn(os);
    os->write(" ");
    right->printRpn(os);
    os->write(" /");
}

/////////////////
/////  Sin  /////
/////////////////

Sin::~Sin() {
    delete ev;
}

double Sin::eval(Context *c) {
    return sin(ev->eval(c));
}

void Sin::printAlg(OutputStream *os) {
    os->write("sin(");
    ev->printAlg(os);
    os->write(")");
}

void Sin::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" sin");
}

//////////////////
/////  Sqrt  /////
//////////////////

Sqrt::~Sqrt() {
    delete ev;
}

double Sqrt::eval(Context *c) {
    return sqrt(ev->eval(c));
}

void Sqrt::printAlg(OutputStream *os) {
    os->write("sqrt(");
    ev->printAlg(os);
    os->write(")");
}

void Sqrt::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" sqrt");
}

/////////////////
/////  Sum  /////
/////////////////

Sum::~Sum() {
    delete left;
    delete right;
}

double Sum::eval(Context *c) {
    return left->eval(c) + right->eval(c);
}

void Sum::printAlg(OutputStream *os) {
    left->printAlg(os);
    os->write("+");
    right->printAlg(os);
}

void Sum::printRpn(OutputStream *os) {
    left->printRpn(os);
    os->write(" ");
    right->printRpn(os);
    os->write(" +");
}

/////////////////
/////  Tan  /////
/////////////////

Tan::~Tan() {
    delete ev;
}

double Tan::eval(Context *c) {
    return tan(ev->eval(c));
}

void Tan::printAlg(OutputStream *os) {
    os->write("tan(");
    ev->printAlg(os);
    os->write(")");
}

void Tan::printRpn(OutputStream *os) {
    ev->printRpn(os);
    os->write(" tan");
}

//////////////////////
/////  Variable  /////
//////////////////////

double Variable::eval(Context *c) {
    return c->getVariable(name);
}

void Variable::printAlg(OutputStream *os) {
    os->write(name);
}

void Variable::printRpn(OutputStream *os) {
    os->write(name);
}

//////////////////////////////////////
/////  here is where it happens  /////
//////////////////////////////////////

class Lexer {

    private:

    std::string text;
    int pos;

    public:

    Lexer(std::string text) {
        this->text = text;
        pos = 0;
    }

    int lpos() {
        return pos;
    }

    bool nextToken(std::string *tok, int *tpos) {
        while (pos < text.length() && text[pos] == ' ')
            pos++;
        if (pos == text.length()) {
            *tok = "";
            *tpos = pos;
            return true;
        }
        int start = pos;
        *tpos = start;
        char c = text[pos++];
        // Compound symbols
        if (c == '<' || c == '>') {
            if (pos < text.length()) {
                char c2 = text[pos + 1];
                if (c2 == '=' || c == '<' && c2 == '>') {
                    pos++;
                    *tok = text.substr(start, 2);
                    return true;
                }
            }
            *tok = text.substr(start, 1);
            return true;
        }
        // One-character symbols
        if (c == '+' || c == '-' || c == '*' || c == '/'
                || c == '(' || c == ')' || c == '[' || c == ']'
                || c == '^' || c == ':' || c == '=') {
                // Note: 42S mul/div/NE/LE/GE symbols!
            *tok = text.substr(start, 1);
            return true;
        }
        // What's left at this point is numbers and names.
        // Which one we're currently looking at depends on its
        // first character; if that's a digit or a decimal,
        // it's a number; anything else, it's a name.
        bool multi_dot = false;
        if (c == '.' || c >= '0' && c <= '9') {
            int state = c == '.' ? 1 : 0;
            int d0 = c == '.' ? 0 : 1;
            int d1 = 0, d2 = 0;
            while (pos < text.length()) {
                c = text[pos];
                switch (state) {
                    case 0:
                        if (c == '.')
                            state = 1;
                        else if (c == 'E' || c == 'e')
                            // Note: 42S exponent symbol!
                            state = 2;
                        else if (c >= '0' && c <= '9')
                            d0++;
                        else
                            goto done;
                        break;
                    case 1:
                        if (c == '.') {
                            multi_dot = true;
                            goto done;
                        }
                        else if (c == 'E' || c == 'e')
                            // Note: 42S exponent symbol!
                            state = 2;
                        else if (c >= '0' && c <= '9')
                            d1++;
                        else
                            goto done;
                        break;
                    case 2:
                        if (c == '-' || c == '+')
                            state = 3;
                        else if (c >= '0' && c <= '9') {
                            d2++;
                            state = 3;
                        } else
                            goto done;
                        break;
                    case 3:
                        if (c >= '0' && c <= '9')
                            d2++;
                        else
                            goto done;
                        break;
                }
                pos++;
            }
            done:
            // Invalid number scenarios:
            if (d0 == 0 && d1 == 0 // A '.' not followed by a digit.
                    || multi_dot // Multiple periods
                    || state == 2  // An 'E' not followed by a valid character.
                    || state == 3 && d2 == 0) { // An 'E' not followed by at least one digit
                *tok = "";
                return false;
            }
            *tok = text.substr(start, pos - start);
            return true;
        } else {
            while (pos < text.length()) {
                char c = text[pos];
                if (c == '+' || c == '-' || c == '*' || c == '/'
                        || c == '(' || c == ')' || c == '[' || c == ']'
                        || c == '^' || c == ':' || c == '='
                        // Note: 42S mul/div/NE/LE/GE symbols!
                        || c == '<' || c == '>')
                    break;
                pos++;
            }
            *tok = text.substr(start, pos - start);
            return true;
        }
    }
};

class Parser {

    private:

    std::string text;
    Lexer *lex;
    std::string pb;
    int pbpos;

    public:

    static Evaluator *parse(std::string expr, int *errpos) {
        Parser pz(expr);
        Evaluator *ev = pz.parseExpr();
        if (ev == NULL)
            *errpos = pz.lex->lpos();
        return ev;
    }

    private:

    Parser(std::string expr) : text(expr), pbpos(-1) {
        lex = new Lexer(expr);
    }

    ~Parser() {
        delete lex;
    }

    Evaluator *parseExpr() {
        Evaluator *ev = parseTerm();
        if (ev == NULL)
            return NULL;
        while (true) {
            std::string t;
            int tpos;
            if (!nextToken(&t, &tpos)) {
                delete ev;
                return NULL;
            }
            if (t == "")
                return ev;
            if (t == "+" || t == "-") {
                Evaluator *ev2 = parseTerm();
                if (ev2 == NULL) {
                    delete ev;
                    return NULL;
                }
                if (t == "+")
                    ev = new Sum(tpos, ev, ev2);
                else
                    ev = new Difference(tpos, ev, ev2);
            } else {
                pushback(t, tpos);
                return ev;
            }
        }
    }

    Evaluator *parseTerm() {
        std::string t;
        int tpos;
        if (!nextToken(&t, &tpos) || t == "")
            return NULL;
        if (t == "-" || t == "+") {
            Evaluator *ev = parseTerm();
            if (ev == NULL)
                return NULL;
            if (t == "+")
                return new Positive(tpos, ev);
            else
                return new Negative(tpos, ev);
        } else {
            pushback(t, tpos);
            Evaluator *ev = parseFactor();
            if (ev == NULL)
                return NULL;
            while (true) {
                if (!nextToken(&t, &tpos)) {
                    delete ev;
                    return NULL;
                }
                if (t == "")
                    return ev;
                if (t == "*" || t == "/") {
                    Evaluator *ev2 = parseFactor();
                    if (ev2 == NULL) {
                        delete ev;
                        return NULL;
                    }
                    if (t == "*")
                        ev = new Product(tpos, ev, ev2);
                    else
                        ev = new Quotient(tpos, ev, ev2);
                } else {
                    pushback(t, tpos);
                    return ev;
                }
            }
        }
    }

    Evaluator *parseFactor() {
        Evaluator *ev = parseThing();
        if (ev == NULL)
            return NULL;
        while (true) {
            std::string t;
            int tpos;
            if (!nextToken(&t, &tpos)) {
                fail:
                delete ev;
                return NULL;
            }
            if (t == "^") {
                Evaluator *ev2 = parseThing();
                if (ev2 == NULL)
                    goto fail;
                ev = new Power(tpos, ev, ev2);
            } else {
                pushback(t, tpos);
                return ev;
            }
        }
    }

    Evaluator *parseThing() {
        std::string t;
        int tpos;
        if (!nextToken(&t, &tpos) || t == "")
            return NULL;
        if (t == "-" || t == "+") {
            Evaluator *ev = parseThing();
            if (ev == NULL)
                return NULL;
            if (t == "+")
                return new Positive(tpos, ev);
            else
                return new Negative(tpos, ev);
        }
        double d;
        if (sscanf(t.c_str(), "%lf", &d) == 1) {
            return new Literal(tpos, d);
        } else if (!isOperator(t)) {
            std::string t2;
            int t2pos;
            if (!nextToken(&t2, &t2pos))
                return NULL;
            if (t2 == "(") {
                std::vector<Evaluator *> *evs = parseExprList();
                if (evs == NULL)
                    return NULL;
                if (!nextToken(&t2, &t2pos) || t2 != ")") {
                    fail:
                    for (int i = 0; i < evs->size(); i++)
                        delete (*evs)[i];
                    delete evs;
                    return NULL;
                }
                /* TODO: Parsing an arbitrarily long argument list when you
                 * know you know exactly one seems a bit stupid, and will lead
                 * to unhelpful error messages.
                 */
                if (t == "sin" || t == "cos" || t == "tan"
                        || t == "asin" || t == "acos" || t == "atan"
                        || t == "log" || t == "exp" || t == "sqrt"
                        || t == "abs") {
                    if (evs->size() != 1)
                        goto fail;
                    Evaluator *ev = (*evs)[0];
                    delete evs;
                    if (t == "sin")
                        return new Sin(tpos, ev);
                    else if (t == "cos")
                        return new Cos(tpos, ev);
                    else if (t == "tan")
                        return new Tan(tpos, ev);
                    else if (t == "asin")
                        return new Asin(tpos, ev);
                    else if (t == "acos")
                        return new Acos(tpos, ev);
                    else if (t == "atan")
                        return new Atan(tpos, ev);
                    else if (t == "log")
                        return new Log(tpos, ev);
                    else if (t == "exp")
                        return new Exp(tpos, ev);
                    else if (t == "sqrt")
                        return new Sqrt(tpos, ev);
                    else // t == "abs"
                        return new Abs(tpos, ev);
                } else if (t == "max")
                    return new Max(tpos, evs);
                else if (t == "min")
                    return new Min(tpos, evs);
                else
                    return new Call(tpos, t, evs);
            } else {
                pushback(t2, t2pos);
                return new Variable(tpos, t);
            }
        } else if (t == "(") {
            Evaluator *ev = parseExpr();
            if (ev == NULL)
                return NULL;
            std::string t2;
            int t2pos;
            if (!nextToken(&t2, &t2pos) || t2 != ")") {
                delete ev;
                return NULL;
            }
            return new Identity(tpos, ev);
        } else
            return NULL;
    }

    std::vector<Evaluator *> *parseExprList() {
        std::vector<Evaluator *> *evs = new std::vector<Evaluator *>;
        while (true) {
            std::string t;
            int tpos;
            if (!nextToken(&t, &tpos)) {
                fail:
                for (int i = 0; i < evs->size(); i++)
                    delete (*evs)[i];
                delete evs;
                return NULL;
            }
            pushback(t, tpos);
            if (t == ")")
                return evs;
            Evaluator *ev = parseExpr();
            if (ev == NULL)
                goto fail;
            evs->push_back(ev);
            if (!nextToken(&t, &tpos))
                goto fail;
            if (t != ",") {
                pushback(t, tpos);
                return evs;
            }
        }
    }

    bool nextToken(std::string *tok, int *tpos) {
        if (pbpos != -1) {
            *tok = pb;
            *tpos = pbpos;
            pbpos = -1;
            return true;
        } else
            return lex->nextToken(tok, tpos);
    }

    void pushback(std::string o, int p) {
        pb = o;
        pbpos = p;
    }

    static bool isOperator(const std::string &s) {
        return s.find_first_of("+-*/^(),") != std::string::npos;
    }
};

int main(int argc, char *argv[]) {
    Context c;
    char line[1024];
    char *eqpos;
    OutputStream *out = new FileOutputStream(stdout, true);

    while (true) {
        printf("> ");
        fflush(stdout);
        if (fgets(line, 1024, stdin) == NULL)
            break;
        //strcpy(line, "sin(1.57)");
        int linelen = strlen(line);
        while (linelen > 0 && isspace(line[0]))
            memmove(line, line + 1, linelen--);
        while (linelen > 0 && isspace(line[linelen - 1]))
            line[--linelen] = 0;
        if (linelen == 0)
            break;
        if (strcmp(line, "exit") == 0) {
            break;
        } else if (strcmp(line, "dump") == 0 || strcmp(line, "dumpalg") == 0) {
            c.dump(out, true);
        } else if (strcmp(line, "dumprpn") == 0) {
            c.dump(out, false);
        } else if ((eqpos = strchr(line, '=')) != NULL) {
            // Assignment
            std::string left(line, eqpos - line);
            std::string right(eqpos + 1);
            int p1 = left.find('(');
            std::string name = left.substr(0, p1);
            if (p1 != std::string::npos) {
                // Function definition
                std::vector<std::string> paramNames;
                while (++p1 < left.length()) {
                    int p2 = left.find_first_of(",)", p1);
                    if (p2 == std::string::npos) {
                        paramNames.push_back(left.substr(p1));
                        break;
                    }
                    paramNames.push_back(left.substr(p1, p2 - p1));
                    p1 = p2;
                }
                int errpos;
                Evaluator *ev = Parser::parse(right, &errpos);
                if (ev == NULL) {
                    fprintf(stderr, "Error at %d\n", errpos);
                    continue;
                }
                Function *f = new Function(paramNames, ev);
                c.setFunction(name, f);
            } else {
                // Variable assignment
                int errpos;
                Evaluator *ev = Parser::parse(right, &errpos);
                if (ev == NULL) {
                    fprintf(stderr, "Error at %d\n", errpos);
                    continue;
                }
                c.setVariable(left, ev->eval(&c));
                delete ev;
            }
        } else {
            // Immediate evaluation
            int errpos;
            Evaluator *ev = Parser::parse(line, &errpos);
            if (ev == NULL) {
                fprintf(stderr, "Error at %d\n", errpos);
                continue;
            }
            out->write(ev->eval(&c));
            out->newline();
            delete ev;
        }
    }
    delete out;
    return 0;
}
