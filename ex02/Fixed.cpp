/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btomlins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:33:49 by btomlins          #+#    #+#             */
/*   Updated: 2024/11/02 17:43:54 by btomlins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

const int Fixed::_fractionalBits = 8;

Fixed::Fixed() : _value(0) 
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int integer) 
{
    std::cout << "Int constructor called" << std::endl;
    _value = integer << _fractionalBits;
}

Fixed::Fixed(const float floating) 
{
    std::cout << "Float constructor called" << std::endl;
    _value = roundf(floating * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed &other) : _value(other._value) 
{
    std::cout << "Copy constructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &other) 
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_value = other._value;
    }
    return *this;
}

Fixed::~Fixed() 
{
    std::cout << "Destructor called" << std::endl;
}

bool Fixed::operator>(const Fixed &other) const { return _value > other._value; }
bool Fixed::operator<(const Fixed &other) const { return _value < other._value; }
bool Fixed::operator>=(const Fixed &other) const { return _value >= other._value; }
bool Fixed::operator<=(const Fixed &other) const { return _value <= other._value; }
bool Fixed::operator==(const Fixed &other) const { return _value == other._value; }
bool Fixed::operator!=(const Fixed &other) const { return _value != other._value; }

Fixed Fixed::operator+(const Fixed &other) const { return Fixed(this->toFloat() + other.toFloat()); }
Fixed Fixed::operator-(const Fixed &other) const { return Fixed(this->toFloat() - other.toFloat()); }
Fixed Fixed::operator*(const Fixed &other) const { return Fixed(this->toFloat() * other.toFloat()); }
Fixed Fixed::operator/(const Fixed &other) const { return Fixed(this->toFloat() / other.toFloat()); }

Fixed &Fixed::operator++() 
{
    _value++;
    return *this;
}

Fixed Fixed::operator++(int) 
{
    Fixed temp(*this);
    _value++;
    return temp;
}

Fixed &Fixed::operator--() 
{
    _value--;
    return *this;
}

Fixed Fixed::operator--(int) 
{
    Fixed temp(*this);
    _value--;
    return temp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) { return (a < b) ? a : b; }
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) { return (a < b) ? a : b; }

Fixed &Fixed::max(Fixed &a, Fixed &b) { return (a > b) ? a : b; }
const Fixed &Fixed::max(const Fixed &a, const Fixed &b) { return (a > b) ? a : b; }

int Fixed::getRawBits() const { return _value; }
void Fixed::setRawBits(int const raw) { _value = raw; }

float Fixed::toFloat() const { return static_cast<float>(_value) / (1 << _fractionalBits); }
int Fixed::toInt() const { return _value >> _fractionalBits; }

std::ostream &operator<<(std::ostream &out, const Fixed &fixed) 
{
    out << fixed.toFloat();
    return out;
}