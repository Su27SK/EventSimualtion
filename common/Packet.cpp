#include "Packet.h"
Packet::Packet(double size, unit type)
{
	this->_size = size;
	this->_type = type;
}

/**
 * @brief Packet&setPacketSize 
 * set the packet size
 * @param {double} size
 */
Packet& Packet::setPacketSize(double size)
{
	this->_size = size;
	return *this;
}


/**
 * @brief Packet 
 * 显式拷贝构造函数
 * @param {Packet} P
 */
Packet::Packet(const Packet& P)
{
	this->_size = P._size;
	this->_type = P._type;
}

/**
 * @brief Packet 
 * 拷贝构造函数
 * @param {Packet} P
 */
Packet::Packet(Packet& P)
{
	this->_size = P._size;
	this->_type = P._type;
}

/**
 * @brief Packet&setPacketType 
 * set the packet size unit 单位
 * @param {unit} type 枚举类型
 */
Packet& Packet::setPacketType(unit type)
{
	if (type != _type) {
		bool plusMinus = (type - _type) > 0 ? true : false;
		convertToType(abs(type - _type), plusMinus);
	}
	return *this;
}

/**
 * @brief getPacketInfo 
 * get the packet info (as: 4.2Mbytes)
 * @return {string}
 */
string Packet::getPacketInfo()
{
	stringstream ss;
	string value;
	ss<<this->_size;
	ss>>value;
	ss.clear();
	return value + this->getPacketUnit();
}

/**
 * @brief getPacketSize 
 * get the packet size (as: 4.2)
 * @return {double}
 */
double Packet::getPacketSize() const
{
	return this->_size;
}

/**
 * @brief getPacketUnit 
 * get the packet size's Unit (as:Mb)
 * @return {string} 
 */
string Packet::getPacketUnit()
{
	switch (this->_type) {
		case 1:
			return string("Byte");
		case 2:
			return string("Kb");
		case 3:
			return string("Mb");
		case 4:
			return string("Gb");
	}
	return string("Kb");
}

/**
 * @brief 
 * 重载操作符
 * @param {Packet} packet
 *
 * @return 
 */
Packet& Packet::operator = (const Packet& packet)
{
	if (this != &packet) {
		Packet bulkPacketTemp(packet);
		this->_size = bulkPacketTemp._size;
		this->_type = bulkPacketTemp._type;
	}
	return *this;
}

/**
 * @brief convertToType 
 * from one unit to anther type;
 * @param {interge} degree (放大或者缩小倍数 base is 10)
 * @param {boolean} isLarge(true:单位放大, false:单位缩小)
 *
 * @return {boolean} false/true
 */
bool Packet::convertToType(int degree, bool isLarge)
{
	int nowType = isLarge? this->_type + degree: this->_type - degree;
	if (nowType >= 1 && nowType <=4) {
		switch (nowType) {
			case 1:
				_type = Byte;
				break;
			case 2:
				_type = Kb;
				break;
			case 3:
				_type = Mb;
				break;
			case 4:
				_type = Gb;
				break;
		}
		if (isLarge) {
			_size = _size / pow(1024, degree);
		} else {
			_size = _size * pow(1024, degree);
		}
		return true;
	} else {
		return false;
	}
}
