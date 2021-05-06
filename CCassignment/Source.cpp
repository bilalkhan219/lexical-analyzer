#include<iostream>
#include<string>
#include<fstream>

using namespace std;
bool isLetter(char c) {
	if ((c >= 'a' && c <= 'z') ||( c >= 'A' && c <= 'Z')) {
		return true;
	}
	else
		return false;	
}
bool isDigit(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	else
		return false;
}
bool isDelimeter(char c) {
	if (c == ' ' || c == '\n' || c == '\n') {
		return true;
	}
	else
		return false;
}

void writeIntoFile(string s) {
	ofstream out("words.txt", ios::app);
	out << s << endl;
	out.close(); 
}
void writeIntosymbolTable(string s) {
	ofstream out("symboltable.txt", ios::app);
	out << s << endl;
	out.close();
}
bool checksemiColon(string s) {
	
	for (int i = 0; i < s.size(); i++) 
	{
		if ((s[s.size() - 1] == ';')|| (s[s.size() - 1] == '{') || (s[s.size() - 1] == '}') || (s[s.size() - 1] == ')') || (s[s.size() - 1] == '/'))
		{
			return true;
		}
	}
	return false;
}

void lexical(string str,int &count, int &countLine) {
	int state = 0;
	int i = 0;
	string lexeme = "";
	int flag = 1;
	char c = '\0';
	if (!checksemiColon(str))
	{
		cout << "semi colon missing in line number: " << countLine << "\n";
	}
	while (str[i] != '\0') {

		c = str[i];

		switch(state)
		{
		case 0:

			if (isLetter(c))
			{
				state = 1;
			}
			else if (isDigit(c))
			{
				state = 2;
			}
			else if (c=='=')
			{
				state = 5;
				
			}
			else if (c == '+')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< ARTH_OP , " + lexeme + ">";
				writeIntoFile(s);
				//cout << "plus operator of " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == '-')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< ARTH_OP , " + lexeme + ">";
				writeIntoFile(s);
				//cout << "minus operator of " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == '*')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< ARTH_OP , " + lexeme + ">";
				writeIntoFile(s);
				//cout << "Multiply operator of " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == '/')
			{
				state = 9;
			}
			else if (c == '<')
			{
				state = 3;
				
			}
			else if (c == '>')
			{
				state = 4;

			}
			else if (c=='!')
			{
				state = 6;
			}
			else if (c == ':')
			{
				state = 8;
			}
			else if (c == '('|| c==')')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< PARENTHESIS >";
				writeIntoFile(s);
				//cout << "parenthesis: " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == '{' || c == '}')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< BRACES >";
				writeIntoFile(s);
				//cout << "Braces: " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == '[' || c == ']')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< SQUARE BRACKETS >";
				writeIntoFile(s);
				//cout << "Square brackets: " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == ';')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< SEMI COLON >";
				writeIntoFile(s);
				//cout << "Semi colon: " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == ',')
			{
				lexeme = lexeme + c;
				state = 0;
				string s = "< COMMA >";
				writeIntoFile(s);
				//cout << "comma: " << lexeme << "\n";
				lexeme = "";
				i++;
				continue;
			}
			else if (c == '\'') {
				state = 7;
			}
			else if (isDelimeter(c))
			{
				i++;
				continue;
			}
			else if (c == '"')
			{
			state = 12;

            }
			
			else {
				cout << "invalid token " << "\n";
				break;
			}

			break;
			case 1:
				if (!(isLetter(c) || isDigit(c)))
				{
					state = 0;
					if(lexeme=="int"||lexeme == "char")
					{
						string s = "< DATA TYPE, " + lexeme + " >";
						writeIntoFile(s);
						//cout << "data type: " << lexeme << "\n";
					}
					else if (lexeme == "if" || lexeme == "else" || lexeme == "while" || lexeme == "return" || lexeme == "read" || lexeme == "write")
					{
						string s = "< KEYWORD, " + lexeme + " >";
						writeIntoFile(s);
						//cout << "Keyword: " << lexeme << "\n";
					}
					else
					{
						count = count + 1;
						string c=to_string(count);
						string s = "< ID, " + c +" >";
						writeIntoFile(s);
						string id = c + ":" + lexeme;
						writeIntosymbolTable(id);
						//cout << "identifier: " << lexeme << "\n";
					}
					lexeme = "";
					continue;
				}
			break;
			case 2:
				if (!isDigit(c) || c == '\0')
				{
					state = 0;
					string s = "< INTEGER, " + lexeme + " >";
					writeIntoFile(s);
					//cout << "integer literal: " << lexeme << "\n";
					lexeme = "";
					continue;
			    }
				
			break;
			case 3:
				if (c == '=')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< LOG_OP, LE >";
					writeIntoFile(s);
					//cout << "logical operator: " << lexeme << "\n";
					lexeme = "";
					
			    } 
				else 
				{
					state = 0;
					string s = "< LOG_OP, LT >";
					writeIntoFile(s);
					//cout << "logical operator: " << lexeme << "\n";
					lexeme = "";
					continue;
				}
				
		    break;
			case 4:
				if (c == '=')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< LOG_OP, GE >";
					writeIntoFile(s);
					//cout << "logical operator: " << lexeme << "\n";
					lexeme = "";
					i++;
					continue;
				}
				else if (c == '>')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< INPUT_OP >";
					writeIntoFile(s);
					//cout << "input operator: " << lexeme << "\n";
					lexeme = "";
					i++;
					continue;
				}
				else
				{
					state = 0;
					string s = "< LOG_OP, GT >";
					writeIntoFile(s);
					//cout << "logical operator: " << lexeme << "\n";
					lexeme = "";
					continue;
				}
				
				
				break;
			case 5:
				if (c == '=')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< LOG_OP, COMPARISON >";
					writeIntoFile(s);
					//cout << "logical operator: " << lexeme << "\n";
					lexeme = "";
					i++;
					continue;

				}
				
				break;
			case 6:
				if(c=='=')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< LOG_OP, NE >";
					writeIntoFile(s);
					//cout << "logical operator: " << lexeme << "\n";
					lexeme = "";
					i++;
					continue;
				}
				else
				{
					state = 0;
					lexeme = "";
					continue;
				}

				break;
			case 7:
				if (c == '\'')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< LITERAL >";
					writeIntoFile(s);
					//cout << "literal constant: " << lexeme << "\n";
					lexeme = "";
					i++;
					continue;
				}
				
				
				break;
			case 8:
				if (c == '=')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< ASSIGN_OP >";
					writeIntoFile(s);
					//cout << "Assignment operator: " << lexeme << "\n";
					lexeme = "";
					i++;
					continue;
				}
				else
				{
					state = 0;
					string s = "< VARIABLE_DEC_OP >";
					writeIntoFile(s);
					//cout << "variable declaration operator: " << lexeme << "\n";
					lexeme = "";
				}
				break;
			case 9:
				if (c == '*')
				{
					state = 10;
				}
				else
				{
					state = 0;
					string s = "< ARTH_OP , DIV >";
					writeIntoFile(s);
					//cout << "divide operator: " << lexeme << "\n";
					lexeme = "";
					continue;
				}
				
				break;
			case 10:
				if (c == '*')
				{
					state = 11;
				}


				break;
			case 11:
				if (c == '/')
				{
					state = 0;
					lexeme = lexeme + c;
					string s = "< COMMENT >";
					writeIntoFile(s);
					//cout << "this is a comment: " << lexeme << "\n";
					lexeme = "";
					i++;
					continue;
				}
				break;
			case 12:

				if (c == '"')
				{
					state = 0;
					string s = "< string >";
					//cout << "this was the string";
					writeIntoFile(s);
					lexeme = "";
					i++;
					continue;

				}
				break;
		
		
		}






		lexeme = lexeme + c;

		i++;
	}


}

int main() {
	int count = 0;
	int countLine = 0;
	string text;
	string filename;
	cout << "Please enter file path: ";	
	cin >> filename;
	string inputfile = filename + ".txt";
	ifstream in(inputfile);
	if (in.good()) {
		while (getline(in, text)) {
			//cout << text << "\n";
			countLine += 1;
			
			lexical(text, count,countLine);

		}
		cout << "Tokens written into token file successfully" << "\n";
		cout << "identifiers written into symbol table file successfully" << "\n";
	}
	else
	{
		cout << "cannot find the input file" << "\n";
	}
	
}
