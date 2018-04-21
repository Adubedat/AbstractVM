#ifndef FACTORY_HPP
# define FACTORY_HPP

# include "IOperand.hpp"
# include <vector>
# include <climits>
# include <cfloat>

class Factory {
public:
    typedef IOperand const * (Factory::*createOperandPtr)(std::string const &value) const;


    virtual ~Factory() = default;

    static Factory const *      getInstance( void );
    IOperand const *            createOperand( eOperandType type, std::string const & value ) const;

private:
    Factory();
    Factory(Factory const &src) = delete;
    Factory     &operator=(Factory const &rhs) = delete;

    const std::vector<createOperandPtr>		makeOperandFactory() const;

	IOperand const *   createInt8( std::string const & value ) const;
	IOperand const *   createInt16( std::string const & value ) const;
	IOperand const *   createInt32( std::string const & value ) const;
	IOperand const *   createFloat( std::string const & value ) const;
	IOperand const *   createDouble( std::string const & value ) const;

    static Factory *                        _factory;
    const std::vector<createOperandPtr> 	_operandFactory;
};

#endif
