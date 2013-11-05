#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Node;
class NExpression;
class NStatement;
class AST_Program;
class NBinaryOperation;
class NNegation;
class NReturn;
class NIdentifier;
class NAssign;
class NIf;
class NWhile;
class NFor;
class NBreak;
class NLValue;
class NArrayCreation;
class NFunCall;
class NInteger;
class NFunctionDec;
class NImport;

class Node
{
    public:
        int lin;
        int col;

    public:
        virtual ~Node()
        {
        }

        virtual string to_string() = 0;

        void set_line(int lin)
        {
            this->lin = lin;
        }

        void set_column(int col)
        {
            this->col = col;
        }
};

class NExpression : public Node
{
};

class NStatement : public Node
{
};

class AST_Program : public Node
{
    public:
        vector <NStatement*> *stmList;
        //NExpression *exp;
	vector <NExpression*> *expList;

    public:
        AST_Program(vector<NStatement*> *stmList, vector<NExpression*> *expList, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->stmList = stmList;
            this->expList = expList;
        }

        virtual string to_string()
        {
            stringstream stream;
            
	    stream << "<AST_PROGRAM>\n";
            if (stmList != NULL) {
                 stream << "<STATEMENTS_SECTION>\n"; 
		 
		 for (int i = 0; i < stmList->size(); i++)
		    stream << stmList->at(i)->to_string();
		 
		 stream << "</STATEMENTS_SECTION>\n";
            };
            if (expList != NULL) {
	        
		stream << "<EXPRESSION_SECTION>\n";

		for (int i = 0; i < expList->size(); i++)
		    stream << expList->at(i)->to_string();

                stream << "<EXPRESSION_SECTION>\n";

            };
            stream << "</AST_PROGRAM>\n";
            return (stream.str());
        }
};

class NBinaryOperation : public NExpression
{
    public:
        NExpression *rExp;
        NExpression *lExp;
        int op;

    public:
        NBinaryOperation(NExpression *lExp, int op, NExpression *rExp, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->rExp = rExp;
            this->lExp = lExp;
            this->op = op;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<BINARY_OPERATION>\n" 
                << "<LEFT_EXPRESSION>\n"  << lExp->to_string() << "</LEFT_EXPRESSION>\n"
                << "<OPERATION>\n" << op << "\n</OPERATION>\n"
                << "<RIGHT_EXPRESSION>\n" << rExp->to_string() << "</RIGHT_EXPRESSION>\n"
                << "</BINARY_OPERATION>\n";
            return stream.str();
        }
};

class NInteger : public NExpression
{
    public:
        int value;

    public:
        NInteger(int value, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->value = value;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<INTEGER>\n" << value << "\n</INTEGER>\n";
            return stream.str();
        }
};

class NNegation : public NExpression
{
    public:
        NExpression *exp;

    public:
        NNegation(NExpression *exp, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->exp = exp;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<NEGATION>\n" + exp->to_string() + "</NEGATION>\n";
            return stream.str();
        }
};

class NReturn : public NExpression
{
    public:
        NExpression *exp;

    public:
        NReturn(NExpression *exp, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->exp = exp;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<RETURN>\n" << exp->to_string() << "</RETURN>\n";
            return stream.str();
        }
};

class NIdentifier : public NExpression
{
    public:
        string identifier;

    public:
        NIdentifier(char *identifier, int lin, int col)
        {
            set_line(lin);
            set_column(col);
	        this->identifier = identifier;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<IDENTIFIER>\n" << identifier << "\n</IDENTIFIER>\n";
            return stream.str();
        }
};

class NLValue : public NExpression
{
    public:
        NIdentifier *identifier;
        vector <NExpression*> *indexList;

    public:
        NLValue(NIdentifier *identifier, vector <NExpression*> *indexList, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->identifier = identifier; 
            this->indexList = indexList;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<LVALUE>\n" << identifier->to_string() << "</LVALUE>\n";

	    if (indexList != NULL){
	        for (int i = 0; i < indexList->size(); i++)
		    stream << "<INDEX>\n" << indexList->at(i)->to_string() << "</INDEX>\n";
	    }

            return stream.str();
        }
};

class NAssign : public NExpression
{
    public:
        NLValue *lvalue;
        NExpression *exp;

    public:
        NAssign(NLValue *lvalue, NExpression *exp, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->lvalue = lvalue;
            this->exp = exp;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<ASSIGN>\n" 
	    	   << "<LEFT_EXPRESSION>\n" << lvalue->to_string() << "</LEFT_EXPRESSION>\n"
		   << "<RIGHT_EXPRESSION>\n" << exp->to_string() << "</RIGHT_EXPRESSION>\n"
		   << "</ASSIGN>\n";
            return stream.str();
        }
};

class NIf : public NExpression
{
    public:
        NExpression *cond;
        NExpression *trueExp;
        NExpression *falseExp;

    public:
        NIf(NExpression *cond, NExpression *trueExp, NExpression *falseExp, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->cond = cond;
            this->trueExp = trueExp;
            this->falseExp = falseExp;
        }

        virtual string to_string()
        {   
            stringstream stream;
            stream << "<IF>\n" << cond->to_string()
                << "<THEN>\n" << trueExp->to_string() << "</THEN>\n";
            if (falseExp != NULL) {
                stream << "<ELSE>\n" << falseExp->to_string() << "</ELSE>\n";
            }
            stream << "</IF>\n";
            return stream.str();
        }
};

class NWhile : public NExpression
{
    public:
        NExpression *cond;
        NExpression *body;

    public:
        NWhile(NExpression *cond, NExpression *body, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->cond = cond;
            this->body = body;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<WHILE>\n" << cond->to_string() 
                << "<DO>\n" << body->to_string() << "</DO>\n"
                << "</WHILE>\n";
            return stream.str();
        }
};

class NFor : public NExpression
{
    public:
        NIdentifier *identifier;
        NExpression *initExp;
        NExpression *endExp;
        NExpression *body;        

    public:
        NFor(NIdentifier *identifier, NExpression *initExp, NExpression *endExp, NExpression *body, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->identifier = identifier;
            this->initExp = initExp;
            this->endExp = endExp;
            this->body = body;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<FOR>\n" << identifier->to_string()
                << "<ASSIGN>\n" << initExp->to_string() << "</ASSIGN>\n"
                << "<TO>\n" << endExp->to_string() << "</TO>\n"
                << "<DO>\n" << body->to_string() << "</DO>\n"
                << "</FOR>\n";
            return stream.str();
        }
};

class NBreak : public NExpression
{
    public:
        NBreak(int lin, int col)
        {
            set_line(lin);
            set_column(col);
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<BREAK>\n" << "</BREAK>\n";
            return stream.str();
        }
};

class NArrayCreation : public NExpression
{
    public:
        NIdentifier *identifier;
        int dimension;

    public:
        NArrayCreation(NIdentifier *identifier, int dimension, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->identifier = identifier;
            this->dimension = dimension;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<ARRAY_CREATION>\n"
                << identifier->to_string()
                << "<DIMENSIONS>\n" 
		        << dimension 
		        << "\n</DIMENSIONS>\n"
                << "</ARRAY_CREATION>\n";
            return stream.str();
        }
};


class NFunctionCall : public NExpression
{
    public:
        NIdentifier *identifier;
        vector <NExpression*> *args;

    public:
        NFunctionCall(NIdentifier *identifier, vector<NExpression*> *args, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->identifier = identifier;
            this->args = args;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<FUNCTION_CALL>\n"<< identifier->to_string();
            for (int i = 0; i < args->size(); i++)
            {
                stream << (args->at(i))->to_string();
            }
            stream << "</FUNCTION_CALL>\n";
            return stream.str();
        }
};

class NExpressionList : public NExpression
{
    public:
        vector<NExpression*> *expList;

    public:
        NExpressionList(vector<NExpression*> *expList, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->expList = expList;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<EXPRESSION_LIST>\n";
            for (int i = 0; i < expList->size(); i++) 
            {
                stream << (expList->at(i))->to_string();
            }
            stream << "</EXPRESSION_LIST>\n";
            return stream.str();
        }
};


/*
   DECLARATIONS
 */

class NFunctionDec : public NStatement
{
    public:
        NIdentifier *identifier;
        vector<NIdentifier*> *args;
        NExpression *exp;

    public:
        NFunctionDec(NIdentifier *identifier, vector<NIdentifier*> *args, NExpression *exp, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->identifier = identifier;
            this->args = args;
            this->exp = exp;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<FUNCTION_DEC>\n" << identifier->to_string() 
                   <<"<ARGS>\n";
            for(int i = 0; i < args->size(); i++)
                stream << (args->at(i))->to_string();
         
            stream << "</ARGS>\n"
                   << "<BODY>\n" << exp->to_string() << "</body>\n"
                   << "</FUNCTION_DEC>\n";
            return stream.str();
        }
};

class NImport : public NStatement
{
    public:
        NIdentifier *identifier;

    public:
        NImport(NIdentifier *identifier, int lin, int col)
        {
            set_line(lin);
            set_column(col);
            this->identifier = identifier;
        }

        virtual string to_string()
        {
            stringstream stream;
            stream << "<IMPORT>\n" << identifier->to_string() << "</IMPORT>\n";
            return stream.str();
        }
};
