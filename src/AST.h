//LambCompiler
//by James 2017/05/01
#ifndef LAMB_COMPILER_AST_H_
#define LAMB_COMPILER_AST_H_

/* Base node of AST */
class expr_node {
public:
	virtual ~expr_node() {}
};

/* NumberExprNode - expression for numeric literal */
class number_expr_node : public expr_node {
private:
	double val;
public:
	number_expr_node(double _val) : val(_val) {}
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
	char op;
	expr_node *lhs, *rhs;
public:
	binary_expr_node(char _op, expr_node* _lhs, expr_node* _rhs) : op(_op), lhs(_lhs), rhs(_rhs) {}
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




















#endif