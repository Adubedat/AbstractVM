#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <exception>
# include <string>

# define COL_RES "\e[39m"
# define COL_RED "\e[31m"

class	SyntaxException : public std::exception
{
    public:
        SyntaxException(std::string msg);
        virtual const char* what(void) const throw();
    private:
        std::string	_msg;
};

class	LexicalException : public std::invalid_argument
{
    public:
        LexicalException(std::string msg);
        virtual const char* what(void) const throw();
    private:
        std::string	_msg;
};

class	RuntimeException : public std::runtime_error
{
    public:
        RuntimeException(std::string msg);
        virtual const char* what(void) const throw();
    private:
        std::string	_msg;
};

class	OutOfRangeException : public std::out_of_range
{
    public:
        OutOfRangeException(std::string msg);
        virtual const char* what(void) const throw();
    private:
        std::string	_msg;
};

#endif
