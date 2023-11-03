#ifndef NUMBER_H
#define NUMBER_H

#include <map>
#include <string>

/**
 * @class Number
 * 
 * Class to represent a number, the number can be integer or floating point.
 * 
 * @author Felipe Borges Alves
 */
class Number {
	public:
		enum Type {
			INT = 0,
			FLOAT
		};
		
		union Value {
			long long int intValue;
			double floatValue;
		};
		
		/**
		 * @return True if the type is an integer.
		 */
		static bool isInteger(Type t);
		
		/**
		 * @return True if the type is a float.
		 */
		static bool isFloat(Type t);
		
		/**
		 * Construct an integer number 0.
		 */
		Number();
		
		/**
		 * Construct a number with the specified type, with the value 0.
		 * 
		 * @param t The type of the number.
		 */
		explicit Number(Type t);
		
		/**
		 * Construct a number with the specified type, and with the specified value.
		 * 
		 * @param t The type of the number.
		 * @param v The value of the number.
		 */
		explicit Number(Type t, Value v);
		
		/**
		 * Construct a number with the specified type, and with the specified value.
		 * 
		 * @param t The type of the number.
		 * @param v The value of the number.
		 */
		Number(Type t, long long int v);
		
		/**
		 * Construct a number with the specified type, and with the specified value.
		 * 
		 * @param t The type of the number.
		 * @param v The value of the number.
		 */
		Number(Type t, double v);
		
		/**
		 * Construct an integer number.
		 * 
		 * @param b If false the number will be 0, if true the number will be 1.
		 */
		explicit Number(bool b);
		
		~Number();
		
		/**
		 * @return The type of the number.
		 */
		Type getType() const;
		
		/**
		 * Cast this number to another type.
		 *  
		 * @param t The type to cast.
		 * 
		 * @return The number cast to the type.
		 */
		Number castTo(Type t) const;
		
		/**
		 * @return True if this number is an integer.
		 */
		bool isInteger() const;
		
		/**
		 * @return True if this number is a float.
		 */
		bool isFloat() const;
		
		/**
		 * @return The value cast to an integer.
		 */
		long long int intValue() const;
		
		/**
		 * @return The value cast to a float.
		 */
		double floatValue() const;
		
		/**
		 * @return The value cast to a boolean.
		 */
		bool boolValue() const;
		
		Number operator+(const Number & other) const;
		Number operator-(const Number & other) const;
		Number operator*(const Number & other) const;
		Number operator/(const Number & other) const;
		Number operator%(const Number & other) const;
		Number operator&(const Number & other) const;
		Number operator|(const Number & other) const;
		Number operator^(const Number & other) const;
		Number operator<<(int shifts) const;
		Number operator>>(int shifts) const;
		
		Number operator+() const;
		Number operator-() const;
		Number operator~() const;
		Number operator!() const;
		
		Number & operator=(const Number & other);
		Number & operator+=(const Number & other);
		Number & operator-=(const Number & other);
		Number & operator*=(const Number & other);
		Number & operator/=(const Number & other);
		Number & operator%=(const Number & other);
		Number & operator&=(const Number & other);
		Number & operator|=(const Number & other);
		Number & operator^=(const Number & other);
		Number & operator<<=(int shifts);
		Number & operator>>=(int shifts);
		
		bool operator==(const Number & other) const;
		bool operator!=(const Number & other) const;
		bool operator<(const Number & other) const;
		bool operator>(const Number & other) const;
		bool operator<=(const Number & other) const;
		bool operator>=(const Number & other) const;
		
	private:
		typedef std::map<std::string, Type> TypeMap;
		
		static TypeMap createTypeMap();
		
		Type getCastType(Type a, Type b) const;
		
		Type type;
		Value value;
		
		static TypeMap typeMap;
};

#endif
