#include "hardware/i2c.h"

#ifndef _MY_I2CStuff_H_
#define	_MY_I2CStuff_H_
namespace srbots {


/// @brief a buffer to send over the I2C line
struct I2CBUFF {
	/// @brief pointer to the buffer
	uint8_t *buf;
	/// @brief the size in bytes to send
	size_t sz;
};

/// @brief a device that can act as an I2CBus.  This could be an I2C port OR a mux port
class i2cbus {
protected:
	i2c_inst_t* _i2cport;
	uint8_t _sda_pin;
	uint8_t _scl_pin;
	uint32_t _bus_speed;
	bool initialized;

public:
/*! \brief Represents an I2C bus
 *  \ingroup i2c_sensor
 *
 *  \param  i2cport - i2c0 or i2c1 port 
 *  \param  sda_pin - valid SDA pin for the port 
 *  \param  scl_pin - valid SCL pin for the port
 *  \param  bus_speed - baud rate 
 *  \return none
 */
	i2cbus(i2c_inst_t* i2cport, uint8_t sda_pin, uint8_t scl_pin, uint64_t bus_speed)
		: _i2cport(i2cport),
		_sda_pin(sda_pin),
		_scl_pin(scl_pin),
		_bus_speed(bus_speed),initialized(false) {
		//init();
	}
/*! \brief Copy constructor
 *  \ingroup i2c_sensor
 *
 *  \param  other - existing i2cbus object  
 *  \return none
 */
	i2cbus(const i2cbus& other)
		: _i2cport(other._i2cport),
		  _sda_pin(other._sda_pin),
		  _scl_pin(other._scl_pin),
		  _bus_speed(other._bus_speed),
		  initialized(other.initialized) {}

/*! \brief Move constructor
 *  \ingroup i2c_sensor
 *
 *  \param  other - existing i2cbus object  
 *  \return none
 */
	i2cbus(i2cbus&& other) noexcept
		: _i2cport(other._i2cport),
		  _sda_pin(other._sda_pin),
		  _scl_pin(other._scl_pin),
		  _bus_speed(other._bus_speed),
		  initialized(other.initialized) {}

/*! \brief assignment op
 *  \ingroup i2c_sensor
 *
 *  \param  other - existing i2cbus object  
 *  \return none
 */
	i2cbus& operator=(const i2cbus& other) {
		if (this == &other)
			return *this;
		_i2cport = other._i2cport;
		_sda_pin = other._sda_pin;
		_scl_pin = other._scl_pin;
		_bus_speed = other._bus_speed;
		initialized = other.initialized;
		return *this;
	}

/*! \brief Move op
 *  \ingroup i2c_sensor
 *
 *  \param  other - existing i2cbus object  
 *  \return none
 */
	i2cbus& operator=(i2cbus&& other) noexcept {
		if (this == &other)
			return *this;
		_i2cport = other._i2cport;
		_sda_pin = other._sda_pin;
		_scl_pin = other._scl_pin;
		_bus_speed = other._bus_speed;
		initialized = other.initialized;
		return *this;
	}

/*! \brief initialize bus
 *  \ingroup i2c_sensor
 *  \return none
 */
	virtual void init();

/*! \brief deinitialize bus
 *  \ingroup i2c_sensor
 *  \return none
 */
	virtual void deinit(bool full);

/*! \brief initialize bus
 *  \ingroup i2c_sensor
 *  \return none
 */

	virtual void i2cbuff(I2CBUFF buf, uint8_t first = 0, uint8_t second = 0, uint8_t third = 0, uint8_t fourth = 0, uint8_t fifth = 0, uint8_t sixth = 0);
	/// @brief writes to a device on the i2cbus port
	/// @param buf the data sent of the device on the channel
	/// @param _addr the address of the device to send to
	/// @param numbytes number of bytes to send in buf
	/// @return 
	virtual int  Write(I2CBUFF buf, uint8_t _addr, uint16_t numbytes);
	/// @brief reads from  a device on the i2cbus port
	/// @param buf the buffer that is read into
	/// @param _addr the address of the device
	/// @param numbytes number of bytes to read
	/// @return 
	virtual int  Read(I2CBUFF buf, uint8_t _addr, uint16_t numbytes);

	/// @brief returns the port
	/// @return the port this represents
	[[nodiscard]] i2c_inst_t* i2cport() const { return _i2cport; }
	[[nodiscard]] uint8_t sda_pin() const { return _sda_pin; }
	[[nodiscard]] uint8_t scl_pin() const { return _scl_pin; }
	[[nodiscard]] uint64_t bus_speed() const { return _bus_speed; }
	
	virtual void scan();

};

/// @brief an abstract base class that all I2C sensors are derived from.
class I2CSensor {
protected:
	i2cbus* _i2cbus;
	uint8_t _addr;
	struct twovals {
		uint8_t first;
		uint8_t second;
	};

public:
	/// @brief constructor 
	/// @param i2cbus the bus object the sensor is on
	/// @param addr the address of the sensor
	I2CSensor(i2cbus* i2cbus, uint8_t addr)
		: _i2cbus(i2cbus),
		_addr(addr) {}
public:

	/// @brief initializes sensor
	/// @return true if successful
	[[nodiscard]]virtual bool init() = 0;
	/// @brief initializes an I2CBUFF object
	/// @param buf the I2CBUFF object
	/// @param first the first byte value
	/// @param second the second byte value
	/// @param third the third byte value
	/// @param fourth the fourth byte value
	/// @param fifth the fifth byte value
	/// @param sixth the sixth byte value
	void i2cbuff(I2CBUFF buf, uint8_t first = 0, uint8_t second = 0, uint8_t third = 0, uint8_t fourth = 0, uint8_t fifth = 0, uint8_t sixth = 0);
	/// @brief writes to the device
	/// @param buf the i2cbuff object
	/// @param numbytes the number of bytes to write
	/// @return the i2cerror
	int  Write(I2CBUFF buf, uint16_t numbytes);
	/// @brief reads from the device
	/// @param buf the i2cbuff object
	/// @param numbytes the number of bytes to read
	/// @return the i2cerror	
	int  Read(I2CBUFF buf, uint16_t numbytes);

	/// @brief performs a write and read (for accessing reg values)
	/// @param buf  the i2cbuff object that holds what to write prior to the call and after holds what was read
	/// @param numbytesWrite number of bytes to write
	/// @param numbytesRead number of bytes to read
	/// @return the i2cerror
	int  WriteRead(I2CBUFF buf, uint16_t numbytesWrite, uint16_t numbytesRead);
};

/// @brief Represents i2c0
extern i2cbus i2cport0;
/// @brief Represents i2c1
extern i2cbus i2cport1;

/// @brief Represents i2c0
#define port0 (&i2cport0)
/// @brief Represents i2c1
#define port1 (&i2cport1)
};

#endif