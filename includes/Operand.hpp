#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"

template<typename T>
class Operand : public IOperand{
public:
    Operand<T>() {};

    Operand<T>(Operand<T> const &src) {
        *this = src;
    };

    Operand<T>(T value, eOperandType type) :
    _value(value),
    _type(type),
    _str(std::to_string(value))
    {};

    Operand<T>  &operator=(Operand<T> const &rhs) {
        if (this != &rhs) {
            _value = rhs._value;
            _type = rhs._type;
            _str = rhs._str;
        }
        return (*this);
    }

    int             getPrecision(void) const {
        return  (_type);
    }

    eOperandType    getType(void) const {
        return (_type);
    }

    IOperand        const * operator+(IOperand const &rhs) const {
        return (this);
    }

    IOperand        const * operator-(IOperand const &rhs) const {
        return (this);
    }

    IOperand        const * operator*(IOperand const &rhs) const {
        return (this);
    }

    IOperand        const * operator/(IOperand const &rhs) const {
        return (this);
    }

    IOperand        const * operator%(IOperand const &rhs) const {
        return (this);
    }

    std::string     const &toString(void) const {
        return (_str);
    }

    virtual ~Operand<T>() {};

private:

    T               _value;
    eOperandType    _type;
    std::string     _str;

};

#endif
