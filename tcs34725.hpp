//#include "MyI2CInitStuff.hpp"
namespace srbots {
#ifndef _MY_TCS34725_H_
#define	_MY_TCS34725_H_

constexpr uint8_t coloraddr = 0x39;
/// @brief represents a color sensor
class ColorDetector : public I2CSensor {
private:
	bool tcsgetID();
	uint16_t _iTimeMS;
	

public:
	/// @brief initializes the color sensor
	/// @param i2cport the i2cbus object the sensor is on
	ColorDetector(i2cbus* i2cport)
		: I2CSensor(i2cport, coloraddr) {}

	/// @brief initializes the color sensor
	/// @param i2cport the i2cbus object the sensor is on
	/// @param addr the overriden address of the color sensor
	ColorDetector(i2cbus* i2cport, const uint8_t addr)
		: I2CSensor(i2cport, addr) {}
	
	/// \brief init color sensors
	/// \returns true if successful
	bool init();

	/// \brief init color sensors
	/// @param iTimeMS - integration time in MS
	/// \returns true if successfulbool init();
	bool init(uint16_t iTimeMS);
	
	/// \brief Can I read Colors from sensors
	/// \return true if colors are ready    
	bool colorReady();

	/// \brief Gets colors from sensors
	/// \param red The Red luminosity
	/// \param green The Green luminosity
	/// \param blue The Blue luminosity
	/// \return true if successfull    
	bool getColors(uint16_t& red, uint16_t& green, uint16_t& blue);

	/// \brief Gets colors from sensors
	/// \param red The Red luminosity
	/// \param green The Green luminosity
	/// \param blue The Blue luminosity
	/// \param brightness The total luminosity (how bright)
	/// \return true if successfull  
	bool getColors(uint16_t& red, uint16_t& green, uint16_t& blue, uint16_t& brightness);

	/// \brief Gets colors from sensors
	/// \param iTimeMS - integration time in mS
	/// \return true if successfull  
	bool setADCIntegrationTime(uint16_t iTimeMS);

};
#endif
};