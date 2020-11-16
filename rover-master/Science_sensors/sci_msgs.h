#ifndef _ROS_science_sensors_sci_msgs_h
#define _ROS_science_sensors_sci_msgs_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace science_sensors
{

  class sci_msgs : public ros::Msg
  {
    public:
      typedef float _uv_intensity_type;
      _uv_intensity_type uv_intensity;
      typedef float _ambientC_type;
      _ambientC_type ambientC;
      typedef float _objectC_type;
      _objectC_type objectC;
      typedef float _ambientF_type;
      _ambientF_type ambientF;
      typedef float _objectF_type;
      _objectF_type objectF;
      typedef float _humidity_temperature_type;
      _humidity_temperature_type humidity_temperature;
      typedef float _humidity_type;
      _humidity_type humidity;
      typedef int16_t _co2_ppm_type;
      _co2_ppm_type co2_ppm;

    sci_msgs():
      uv_intensity(0),
      ambientC(0),
      objectC(0),
      ambientF(0),
      objectF(0),
      humidity_temperature(0),
      humidity(0),
      co2_ppm(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_uv_intensity;
      u_uv_intensity.real = this->uv_intensity;
      *(outbuffer + offset + 0) = (u_uv_intensity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_uv_intensity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_uv_intensity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_uv_intensity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uv_intensity);
      union {
        float real;
        uint32_t base;
      } u_ambientC;
      u_ambientC.real = this->ambientC;
      *(outbuffer + offset + 0) = (u_ambientC.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ambientC.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ambientC.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ambientC.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ambientC);
      union {
        float real;
        uint32_t base;
      } u_objectC;
      u_objectC.real = this->objectC;
      *(outbuffer + offset + 0) = (u_objectC.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_objectC.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_objectC.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_objectC.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->objectC);
      union {
        float real;
        uint32_t base;
      } u_ambientF;
      u_ambientF.real = this->ambientF;
      *(outbuffer + offset + 0) = (u_ambientF.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ambientF.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ambientF.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ambientF.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ambientF);
      union {
        float real;
        uint32_t base;
      } u_objectF;
      u_objectF.real = this->objectF;
      *(outbuffer + offset + 0) = (u_objectF.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_objectF.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_objectF.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_objectF.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->objectF);
      union {
        float real;
        uint32_t base;
      } u_humidity_temperature;
      u_humidity_temperature.real = this->humidity_temperature;
      *(outbuffer + offset + 0) = (u_humidity_temperature.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_humidity_temperature.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_humidity_temperature.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_humidity_temperature.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->humidity_temperature);
      union {
        float real;
        uint32_t base;
      } u_humidity;
      u_humidity.real = this->humidity;
      *(outbuffer + offset + 0) = (u_humidity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_humidity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_humidity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_humidity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->humidity);
      union {
        int16_t real;
        uint16_t base;
      } u_co2_ppm;
      u_co2_ppm.real = this->co2_ppm;
      *(outbuffer + offset + 0) = (u_co2_ppm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_co2_ppm.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->co2_ppm);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_uv_intensity;
      u_uv_intensity.base = 0;
      u_uv_intensity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_uv_intensity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_uv_intensity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_uv_intensity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->uv_intensity = u_uv_intensity.real;
      offset += sizeof(this->uv_intensity);
      union {
        float real;
        uint32_t base;
      } u_ambientC;
      u_ambientC.base = 0;
      u_ambientC.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ambientC.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ambientC.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ambientC.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ambientC = u_ambientC.real;
      offset += sizeof(this->ambientC);
      union {
        float real;
        uint32_t base;
      } u_objectC;
      u_objectC.base = 0;
      u_objectC.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_objectC.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_objectC.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_objectC.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->objectC = u_objectC.real;
      offset += sizeof(this->objectC);
      union {
        float real;
        uint32_t base;
      } u_ambientF;
      u_ambientF.base = 0;
      u_ambientF.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ambientF.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ambientF.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ambientF.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ambientF = u_ambientF.real;
      offset += sizeof(this->ambientF);
      union {
        float real;
        uint32_t base;
      } u_objectF;
      u_objectF.base = 0;
      u_objectF.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_objectF.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_objectF.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_objectF.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->objectF = u_objectF.real;
      offset += sizeof(this->objectF);
      union {
        float real;
        uint32_t base;
      } u_humidity_temperature;
      u_humidity_temperature.base = 0;
      u_humidity_temperature.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_humidity_temperature.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_humidity_temperature.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_humidity_temperature.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->humidity_temperature = u_humidity_temperature.real;
      offset += sizeof(this->humidity_temperature);
      union {
        float real;
        uint32_t base;
      } u_humidity;
      u_humidity.base = 0;
      u_humidity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_humidity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_humidity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_humidity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->humidity = u_humidity.real;
      offset += sizeof(this->humidity);
      union {
        int16_t real;
        uint16_t base;
      } u_co2_ppm;
      u_co2_ppm.base = 0;
      u_co2_ppm.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_co2_ppm.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->co2_ppm = u_co2_ppm.real;
      offset += sizeof(this->co2_ppm);
     return offset;
    }

    const char * getType(){ return "science_sensors/sci_msgs"; };
    const char * getMD5(){ return "2b1bbca090f8a25584630307a2ef150a"; };

  };

}
#endif
