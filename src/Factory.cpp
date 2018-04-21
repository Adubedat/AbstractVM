#include "Factory.hpp"
#include "Exceptions.hpp"
#include "Operand.hpp"

/*
**                  Constructors and destructor
*/

Factory::Factory() : _operandFactory(makeOperandFactory()) {};

/*
**                  Singleton Getter
*/

Factory const *     Factory::getInstance( void ) {
    if (!_factory)
        _factory = new Factory;
    return (_factory);
}
/*
**                  Initialisations
*/

Factory *   Factory::_factory = nullptr;

const std::vector<Factory::createOperandPtr>         Factory::makeOperandFactory() const {

	std::vector<Factory::createOperandPtr> factory;

	factory.push_back(&Factory::createInt8);
	factory.push_back(&Factory::createInt16);
	factory.push_back(&Factory::createInt32);
	factory.push_back(&Factory::createFloat);
	factory.push_back(&Factory::createDouble);

	return (factory);
}

/*
**                  Factory
*/

IOperand        const * Factory::createOperand(eOperandType type, std::string const & value) const {
    createOperandPtr p = this->_operandFactory[type];
    return ((this->*p)(value));
}

IOperand        const * Factory::createInt8(std::string const & value) const {
    try {
        int nbr = std::stoi(value);
        if (nbr < CHAR_MIN || nbr > CHAR_MAX)
            throw OutOfRangeException("");
        return (new Operand<int8_t>(nbr, Int8));
    } catch (std::exception &e) {
        throw OutOfRangeException("int8 value must be between " + std::to_string(CHAR_MIN) + " and " + std::to_string(CHAR_MAX));
    }
}

IOperand        const * Factory::createInt16(std::string const & value) const {
    try {
        int nbr = std::stoi(value);
        if (nbr < SHRT_MIN || nbr > SHRT_MAX)
            throw OutOfRangeException("");
        return (new Operand<int16_t>(nbr, Int16));
    } catch (std::exception &e) {
        throw OutOfRangeException("int16 value must be between " + std::to_string(SHRT_MIN) + " and " + std::to_string(SHRT_MAX));
    }
}

IOperand        const * Factory::createInt32(std::string const & value) const {
    try {
        int nbr = std::stoi(value);
        if (nbr < INT_MIN || nbr > INT_MAX)
            throw OutOfRangeException("");
        return (new Operand<int32_t>(nbr, Int32));
    } catch (std::exception &e) {
        throw OutOfRangeException("int32 value must be between " + std::to_string(INT_MIN) + " and " + std::to_string(INT_MAX));
    }
}

IOperand        const * Factory::createFloat(std::string const & value) const {
    try {
        float nbr = std::stof(value);
        if (nbr < -FLT_MAX || nbr > FLT_MAX)
            throw OutOfRangeException("");
        return (new Operand<float>(nbr, Float));
    } catch (std::exception &e) {
        throw OutOfRangeException("float value must be between " + std::to_string(-FLT_MAX) + " and " + std::to_string(FLT_MAX));
    }
}

IOperand        const * Factory::createDouble(std::string const & value) const {
    try {
        double nbr = std::stod(value);
        if (nbr < -DBL_MAX || nbr > DBL_MAX)
            throw OutOfRangeException("");
        return (new Operand<double>(nbr, Double));
    } catch (std::exception &e) {
        throw OutOfRangeException("double value must be between " + std::to_string(-DBL_MAX) + " and " + std::to_string(DBL_MAX));
    }
}
