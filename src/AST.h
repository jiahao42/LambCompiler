//LambCompiler
//by James 2017/05/01
#ifndef LAMB_COMPILER_AST_H_
#define LAMB_COMPILER_AST_H_

extern std::vector<std::string> code;
extern std::vector<std::string> data;

class value {
private:
	std::string _val;
public:
	value(std::string val) : _val(val) {}
	std::string get_val() {
		return _val;
	}
};

/* Base node of AST */
class expr_node {
public:
	virtual ~expr_node() {}
	virtual value* code_gen() {
		return nullptr;
	}
};

/* NumberExprNode - expression for numeric literal */
class number_expr_node : public expr_node {
private:
	double val;
public:
	number_expr_node(double _val) : val(_val) {}
	virtual value* code_gen() {
		code.push_back(std::to_string(val));
		return new value(std::to_string(val));
	}
};

/* VarExprNode - expression for variable */
class var_expr_node : public expr_node {
private:
	std::string name;
public:
	var_expr_node(const std::string& _name) : name(_name) {}
};

/* BinaryExprNode - expression for binary expression */
class binary_expr_node : public expr_node {
private:
	std::string op;
	expr_node *lhs, *rhs;
public:
	binary_expr_node(std::string _op, expr_node* _lhs, expr_node* _rhs) : op(_op), lhs(_lhs), rhs(_rhs) {}
	virtual value* code_gen(){
		char tmp_op = op[0];
		value* L = lhs->code_gen();
		value* R = rhs->code_gen();
		if(L == 0||R == 0) return 0;

		switch(tmp_op){
			case '+':
				data.push_back(L -> get_val());
				data.push_back(R -> get_val());
				code.push_back("LOADA");
				code.push_back("LOADB");
				code.push_back("ADD");
				break;
			case '-':
				code.push_back("LOADA");
				code.push_back("LOADB");
				code.push_back("SUB");
				break;
			case '*':
				code.push_back("LOADA");
				code.push_back("LOADB");
				code.push_back("MUL");
			default:
				std::cout << "Error in binary expr code gen" << std::endl;
		}
	}
};

/* CallExprNode - expression for function call */
class call_expr_node : public expr_node {
private:
	std::string callee;
	std::vector<expr_node*> args;
public:
	call_expr_node(const std::string& _callee, std::vector<expr_node*>& _args) : callee(_callee), args(_args) {}
};

/* PrototypeNode - expression for prototype of a function
 * including function name and argument list
 */
class prototype_node {
private:
	std::string name;
	std::vector<std::string> args;
public:
	prototype_node(const std::string& _name, const std::vector<std::string>& _args) : name(_name), args(_args) {}
};

/* FunctionNode - expression for function definition itself */
class function_node {
private:
	prototype_node* proto;
	expr_node* body;
public:
	function_node(prototype_node* _proto, expr_node* _body) : proto(_proto), body(_body) {}
};

/* ForLoopNode - expression for for-loop node */
class for_loop_node : public expr_node {
private:
	expr_node *init, *compare, *update;
public:
	for_loop_node(expr_node* _init, expr_node* _compare, expr_node* _update) : init(_init), compare(_compare), update(_update) {}
};





#endif















