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
            _value = rhs.getValue();
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

    T               getValue(void) const {
        return (_value);
    }

    double          getOperandValue(IOperand const &rhs) const {
        switch (rhs.getType()) {
            case Int8:
                return (static_cast<double>(dynamic_cast<const Operand<int8_t> *>(&rhs)->getValue()));
                break;
            case Int16:
                return (static_cast<double>(dynamic_cast<const Operand<int16_t> *>(&rhs)->getValue()));
                break;
            case Int32:
                return (static_cast<double>(dynamic_cast<const Operand<int32_t> *>(&rhs)->getValue()));
                break;
            case Float:
                return (static_cast<double>(dynamic_cast<const Operand<float> *>(&rhs)->getValue()));
                break;
            case Double:
                return (static_cast<double>(dynamic_cast<const Operand<double> *>(&rhs)->getValue()));
                break;
        }
    }

    bool        operator==(IOperand const &rhs) const {
        return (static_cast<double>(_value) == getOperandValue(rhs)
            && _type == rhs.getType()
            && _str == rhs.toString());
    }

    IOperand        const * operator+(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = getOperandValue(rhs);
        double result = lvalue + rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator-(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = getOperandValue(rhs);
        double result = lvalue - rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator*(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = getOperandValue(rhs);
        double result = lvalue * rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator/(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = getOperandValue(rhs);

        if (rvalue == 0.0)
            throw RuntimeException("Division by zero");
        double result = lvalue / rvalue;

        return (Factory::getInstance()->createOperand(type, std::to_string(result)));
    }

    IOperand        const * operator%(IOperand const &rhs) const {
        eOperandType type = (this->getPrecision() > rhs.getPrecision()) ? this->getType() : rhs.getType();
        double lvalue = static_cast<double>(this->_value);
        double rvalue = getOperandValue(rhs);

        if (rvalue == 0.0)
            throw RuntimeException("Modulo by zero");
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
