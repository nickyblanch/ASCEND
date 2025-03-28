///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Read the spectrum of light
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include "AS726X.h"

/*
  This is a library written for the AS726X Spectral Sensor (Visible or IR) with I2C firmware
  specially loaded. SparkFun sells these at its website: www.sparkfun.com

  Written by Nathan Seidle & Andrew England @ SparkFun Electronics, July 12th, 2017

  https://github.com/sparkfun/Qwiic_Spectral_Sensor_AS726X

  Do you like this library? Help support SparkFun. Buy a board!

  Development environment specifics:
  Arduino IDE 1.8.1

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

class SpectralSensor : public Sensor
{
private:
    AS726X sensor; // Creates the sensor object
    double data[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    String descriptors[6] = {"R", "O", "Y", "G", "B", "V"};
    bool operational = false;

public:
    SpectralSensor()
    {
        muxIndex = 1; // Set the MUX index for this sensor
    }
    int init()
    {
        operational = sensor.begin(); // Initializes the sensor with non default values
        return operational ? 0 : -1;  // Return 0 if successful
    };
    int getDataCount()
    {
        return 6;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        sensor.takeMeasurements();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        data[0] = sensor.getCalibratedRed();
        data[1] = sensor.getCalibratedOrange();
        data[2] = sensor.getCalibratedYellow();
        data[3] = sensor.getCalibratedGreen();
        data[4] = sensor.getCalibratedBlue();
        data[5] = sensor.getCalibratedViolet();

        return data;
    }
    String getName()
    {
        return "Vis";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};