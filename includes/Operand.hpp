#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include "Factory.hpp"
# include "Exceptions.hpp"
# include <cmath>

template<typename T>
class Operand : public IOperand{
public:
    Operand<T>() {};

    Operand<T>(Operand<T> const &src) {
        *this = src;
    };

    Operand<T>(T value, eOperandType type) :
    _value(value),
    _type(type)
    {
        switch (type) {
            case Int8:
                _str = "Int8 : " + std::to_string(value);
                break;
            case Int16:
                _str = "Int16 : " + std::to_string(value);
                break;
            case Int32:
                _str = "Int32 : " + std::to_string(value);
                break;
            case Float:
                _str = "Float : " + std::to_string(value);
                break;
            case Double:
                _str = "Double : " + std::to_string(value);
                break;
        }
    };

    Operand<T>  &operator=(Operand<T> const &rhs) {
        if (this != &rhs) {
            _value = dynamic_cast<Operand*>(rhs)->_value;
            _type = rhs._type;
            _str = rhs._str;
        }
        return (*this);
    }

    int             getPrecision(void) const {
        return (_type);
    }

    eOperandType    getType(void) const {
        return (_type);
    }

    bool        operator==(IOperand const &rhs) const {
        return (_value == dynamic_cast<Operand*>(rhs)->_value
            && _type == rhs.getType()
            && _str == rhs.toString());
    }

    IOperand        const * operator+(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = static_cast<double>(dynamic_cast<Operand*>(rhs)->_value);
        double result = lvalue + rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator-(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = static_cast<double>(dynamic_cast<Operand*>(rhs)->_value);
        double result = lvalue - rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator*(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = static_cast<double>(dynamic_cast<Operand*>(rhs)->_value);
        double result = lvalue * rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator/(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = static_cast<double>(dynamic_cast<Operand*>(rhs)->_value);

        if (rvalue == 0.0)
            throw RuntimeException("Division by zero");
        double result = lvalue / rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator%(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = static_cast<double>(dynamic_cast<Operand*>(rhs)->_value);

        if (rvalue == 0.0)
            throw RuntimeException("Division by zero");
        double result = std::fmod(lvalue, rvalue);

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    std::string     const &toString(void) const {
        return(_str);
    }

    virtual ~Operand<T>() {};

private:

    T               _value;
    eOperandType    _type;
    std::string     _str;

};

#endif
