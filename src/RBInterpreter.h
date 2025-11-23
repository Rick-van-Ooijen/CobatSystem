#ifndef RBINTERPRETER_H
#define RBINTERPRETER_H

#include <godot_cpp/classes/Node.hpp>
#include <string>
#include <vector>

namespace godot {

enum TokenType {
	// Single-character tokens.
	T_LEFT_PAREN, T_RIGHT_PAREN, T_LEFT_BRACE, T_RIGHT_BRACE,
	T_COMMA, T_DOT, T_MINUS, T_PLUS, T_SEMICOLON, T_SLASH, T_STAR,
	// One or two character tokens.
	T_BANG, T_BANG_EQUAL,
	T_EQUAL, T_EQUAL_EQUAL,
	T_GREATER, T_GREATER_EQUAL,
	T_LESS, T_LESS_EQUAL,
	// Literals.
	T_IDENTIFIER, T_STRING, T_NUMBER,
	// Keywords.
	T_AND, T_CLASS, T_ELSE, T_FALSE, T_FUN, T_FOR, T_IF, T_NIL, T_OR,
	T_PRINT, T_RETURN, T_SUPER, T_THIS, T_TRUE, T_VAR, T_WHILE,
	T_EOF
};

class RBInterpreter : public Node {
	GDCLASS(RBInterpreter, Node)
	
	private:
	
	
	protected:
	static void _bind_methods();
	
	void runFile(std::string path);
	
	public:
	RBInterpreter();
	~RBInterpreter();
	
	void _process(double delta);
	void reportError(int line, std::string message);
	
	//see if this is needed in cpp, otherwise remove
	void main(String arg);
	void run(std::string input);
};

class Token : public Object{
	GDCLASS(Token, Object)
public:
	int type;
	std::string lexeme;
	std::string literal;
	int line;

	Token() {};
	~Token() {};
	Token(int iType, std::string iLexeme, std::string iLiteral, int iLine) {
	type = iType;
	lexeme = iLexeme;
	literal = iLiteral;
	line = iLine;
	}

	std::string toString() {	
		std::string output = (std::to_string(type) + " line: (" + std::to_string(line) + ") " + lexeme + " " + literal);
		return output;}

protected:
	static void _bind_methods() {};
};

class Scanner : public Object{
	GDCLASS(Scanner, Object)
public:
	std::vector<Token> tokens;
	int start = 0;
	int current = 0;
	int line = 1;

	std::string source;
	RBInterpreter* interpreter;

	Scanner() {};
	~Scanner() {};
	Scanner(std::string iSource, RBInterpreter* iInterpreter) {source = iSource; interpreter = iInterpreter;}

	std::vector<Token> scanTokens(std::string source);
	void string();


	void addToken(int type) {addToken(type, "");};
	void addToken(int type, std::string literal);

protected:
	static void _bind_methods() {};
};


















}
#endif