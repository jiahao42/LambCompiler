//LambCompiler
//by James 2017/05/01
#ifndef LAMB_COMPILER_AST_H_
#define LAMB_COMPILER_AST_H_

extern std::vector<std::string> code;
extern std::vector<std::string> stack_data;

inline void emit(std::string s) {
	std::cout << "\t" << s << std::endl;
}

class value {
private:
	std::string name;
public:
	value(std::string _name) : name(_name) {}
	std::string get_val() {
		return name;
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

// temp variable
static int temp_index;
class temp : public expr_node {
private:
	std::string name;
public:
	temp() {
		name = "t" + std::to_string(temp_index++);
	}
	std::string to_string() {
		return name;
	}
};

// label for goto 
static int label_index;
class label: public expr_node {
private:
	std::string name;
public:
	label() {
		name = "L" + std::to_string(label_index++);
	}
	std::string to_string() {
		return name;
	}
};

/* NumberExprNode - expression for numeric literal */
class number_expr_node : public expr_node {
private:
	int val;
public:
	number_expr_node(int _val) : val(_val) {}
	virtual value* code_gen() {
		return new value(std::to_string(val));
	}
};

/* VarExprNode - expression for variable */
class var_expr_node : public expr_node {
private:
	std::string name;
public:
	var_expr_node(const std::string& _name) : name(_name) {}
	virtual value* code_gen() {
		return new value(name);
	}
};

/* BinaryExprNode - expression for binary expression */
class binary_expr_node : public expr_node {
private:
	std::string op;
	expr_node *lhs, *rhs;
public:
	binary_expr_node(std::string _op, expr_node* _lhs, expr_node* _rhs) : op(_op), lhs(_lhs), rhs(_rhs) {}
	virtual value* code_gen() {
		char tmp_op = op[0];
		value* L = lhs->code_gen();
		value* R = rhs->code_gen();
		if(L == 0||R == 0) return 0;

		switch(tmp_op){
			default:
				std::cout << "Invalid binary operator" << std::endl;
			case '=':
			{
				if (op.size() == 2) {
					emit(L->get_val() + " == " + R->get_val());
					return new value(L->get_val());
				}
				emit(L->get_val() + " = " + R->get_val());
				return new value(L->get_val());
			}
			case '+':
			case '-':
			case '*':
			case '/':
			{
				temp tmp;
				emit(tmp.to_string() + " = " + L->get_val() + " " + std::string(1, tmp_op) + " " + R->get_val());
				return new value(tmp.to_string());
			}
		}
	}
};

class if_stmt_node : public expr_node {
private:
	expr_node* cond;
	std::vector<expr_node*> if_stmts;
	std::vector<expr_node*> else_stmts;
public:
	if_stmt_node() : cond(nullptr){}
	if_stmt_node(expr_node* _cond , std::vector<expr_node*> _if_stmts, std::vector<expr_node*> _else_stmts) : 
		cond(_cond), if_stmts(_if_stmts), else_stmts(_else_stmts) {}

	virtual value* code_gen() {
		label l0;
		label l1;
		label l2;
		std::cout << "\tif ";
		cond -> code_gen();
		emit("\tgoto " + l0.to_string());
		emit("goto " + l1.to_string());
		std::cout << l0.to_string() << ": ";
		for (expr_node* e : if_stmts) {
			e -> code_gen();
		}
		emit("goto " + l2.to_string());
		std::cout << l1.to_string() << ": ";
		for (expr_node* e : else_stmts) {
			e -> code_gen();
		}
		std::cout << l2.to_string() << ": ";
		return nullptr;
	}
	
};

/* ForLoopNode - expression for for-loop node */
class for_loop_node : public expr_node {
private:
	expr_node *init, *compare, *update;
	std::vector<expr_node*> body;
public:
	for_loop_node(expr_node* _init, 
				  expr_node* _compare, 
				  expr_node* _update, 
				  std::vector<expr_node*> _body) : 
				  init(_init), 
				  compare(_compare), 
				  update(_update),
				  body(_body) {}
				  
	virtual value* code_gen() {
		init -> code_gen();
		label l0;
		label l1;
		label l2;
		std::cout << l0.to_string() << ": ";
		std::cout << "\tif ";
		
		compare -> code_gen();
		emit("\tgoto " + l1.to_string());
		emit("goto " + l2.to_string());
		std::cout << l1.to_string() << ": ";
		
		for (expr_node* e : body) {
			e -> code_gen(); 
		}
		update -> code_gen();
		emit("goto " + l0.to_string());
		std::cout << l2.to_string() << ": ";
		return nullptr;
	}
};

class boolean_expr_node : public expr_node {
	//TODO
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















