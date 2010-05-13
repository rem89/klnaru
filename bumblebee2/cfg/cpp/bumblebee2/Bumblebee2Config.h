//#line 2 "/opt/ros/boxturtle/stacks/driver_common/dynamic_reconfigure/templates/ConfigType.h"
// *********************************************************
// 
// File autogenerated for the bumblebee2 package 
// by the dynamic_reconfigure package.
// Please do not edit.
// 
// ********************************************************/

/***********************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 ***********************************************************/

// Author: Blaise Gassend


#ifndef __bumblebee2__BUMBLEBEE2CONFIG_H__
#define __bumblebee2__BUMBLEBEE2CONFIG_H__

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <boost/thread/mutex.hpp>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>

namespace bumblebee2
{
  class Bumblebee2Config
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l, 
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      
      virtual void clamp(Bumblebee2Config &config, const Bumblebee2Config &max, const Bumblebee2Config &min) const = 0;
      virtual void calcLevel(uint32_t &level, const Bumblebee2Config &config1, const Bumblebee2Config &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, Bumblebee2Config &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const Bumblebee2Config &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, Bumblebee2Config &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const Bumblebee2Config &config) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;
    
    template <class T>
    class ParamDescription : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string name, std::string type, uint32_t level, 
          std::string description, std::string edit_method, T Bumblebee2Config::* f) :
        AbstractParamDescription(name, type, level, description, edit_method),
        field(f)
      {}

      T (Bumblebee2Config::* field);

      virtual void clamp(Bumblebee2Config &config, const Bumblebee2Config &max, const Bumblebee2Config &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;
        
        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const Bumblebee2Config &config1, const Bumblebee2Config &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, Bumblebee2Config &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const Bumblebee2Config &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, Bumblebee2Config &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const Bumblebee2Config &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }
    };

//#line 49 "../cfg/Bumblebee2.cfg"
      int brightness;
//#line 52 "../cfg/Bumblebee2.cfg"
      std::string encoding;
//#line 55 "../cfg/Bumblebee2.cfg"
      int exposure;
//#line 58 "../cfg/Bumblebee2.cfg"
      int gain;
//#line 61 "../cfg/Bumblebee2.cfg"
      int shutter;
//#line 65 "../cfg/Bumblebee2.cfg"
      std::string whitebalance;
//#line 135 "/opt/ros/boxturtle/stacks/driver_common/dynamic_reconfigure/templates/ConfigType.h"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        if ((*i)->fromMessage(msg, *this))
          count++;
      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("Bumblebee2Config::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->toMessage(msg, *this);
    }
    
    void __toServer__(const ros::NodeHandle &nh) const
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->fromServer(nh, *this);
    }

    void __clamp__()
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const Bumblebee2Config &config) const
    {
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->calcLevel(level, config, *this);
      return level;
    }
    
    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__() 
    {
      __init_statics__();
      return __description_message__;
    }

    static const Bumblebee2Config &__getDefault__()
    {
      __init_statics__();
      return __default__;
    }
    
    static const Bumblebee2Config &__getMax__()
    {
      __init_statics__();
      return __max__;
    }
    
    static const Bumblebee2Config &__getMin__()
    {
      __init_statics__();
      return __min__;
    }
   
    static const std::vector<AbstractParamDescriptionConstPtr> __getParamDescriptions__()
    {
      __init_statics__();
      return __param_descriptions__;
    }

    Bumblebee2Config()
    {
      if (this != &__min__ && this != &__max__ && this != &__default__)
				__init_statics__(); // These three need to be initialized before we can initialize.
    }

  private:
    static bool __initialized__;
    static boost::mutex __init_mutex__;
    
    static std::vector<AbstractParamDescriptionConstPtr> __param_descriptions__;
    static Bumblebee2Config __max__;
    static Bumblebee2Config __min__;
    static Bumblebee2Config __default__;
    static dynamic_reconfigure::ConfigDescription __description_message__;

    static void __init_statics__()
    {
      if (__initialized__) // Common case
        return;

      boost::mutex::scoped_lock lock(__init_mutex__);

      if (__initialized__) // In case we lost a race.
        return;

//#line 49 "../cfg/Bumblebee2.cfg"
      __min__.brightness = -1;
//#line 49 "../cfg/Bumblebee2.cfg"
      __max__.brightness = 9999;
//#line 49 "../cfg/Bumblebee2.cfg"
      __default__.brightness = -1;
//#line 49 "../cfg/Bumblebee2.cfg"
      __param_descriptions__.push_back(AbstractParamDescriptionConstPtr(new ParamDescription<int>("brightness", "int", 0, "The camera brightness for automatic gain/exposure.", "", &Bumblebee2Config::brightness)));
//#line 52 "../cfg/Bumblebee2.cfg"
      __min__.encoding = "";
//#line 52 "../cfg/Bumblebee2.cfg"
      __max__.encoding = "";
//#line 52 "../cfg/Bumblebee2.cfg"
      __default__.encoding = "";
//#line 52 "../cfg/Bumblebee2.cfg"
      __param_descriptions__.push_back(AbstractParamDescriptionConstPtr(new ParamDescription<std::string>("encoding", "str", 0, "Image encoding.", "", &Bumblebee2Config::encoding)));
//#line 55 "../cfg/Bumblebee2.cfg"
      __min__.exposure = -1;
//#line 55 "../cfg/Bumblebee2.cfg"
      __max__.exposure = 9999;
//#line 55 "../cfg/Bumblebee2.cfg"
      __default__.exposure = -1;
//#line 55 "../cfg/Bumblebee2.cfg"
      __param_descriptions__.push_back(AbstractParamDescriptionConstPtr(new ParamDescription<int>("exposure", "int", 0, "Exposure setting.", "", &Bumblebee2Config::exposure)));
//#line 58 "../cfg/Bumblebee2.cfg"
      __min__.gain = -1;
//#line 58 "../cfg/Bumblebee2.cfg"
      __max__.gain = 9999;
//#line 58 "../cfg/Bumblebee2.cfg"
      __default__.gain = -1;
//#line 58 "../cfg/Bumblebee2.cfg"
      __param_descriptions__.push_back(AbstractParamDescriptionConstPtr(new ParamDescription<int>("gain", "int", 0, "Gain setting.", "", &Bumblebee2Config::gain)));
//#line 61 "../cfg/Bumblebee2.cfg"
      __min__.shutter = -1;
//#line 61 "../cfg/Bumblebee2.cfg"
      __max__.shutter = 9999;
//#line 61 "../cfg/Bumblebee2.cfg"
      __default__.shutter = -1;
//#line 61 "../cfg/Bumblebee2.cfg"
      __param_descriptions__.push_back(AbstractParamDescriptionConstPtr(new ParamDescription<int>("shutter", "int", 0, "Shutter setting.", "", &Bumblebee2Config::shutter)));
//#line 65 "../cfg/Bumblebee2.cfg"
      __min__.whitebalance = "";
//#line 65 "../cfg/Bumblebee2.cfg"
      __max__.whitebalance = "";
//#line 65 "../cfg/Bumblebee2.cfg"
      __default__.whitebalance = "auto";
//#line 65 "../cfg/Bumblebee2.cfg"
      __param_descriptions__.push_back(AbstractParamDescriptionConstPtr(new ParamDescription<std::string>("whitebalance", "str", 0, "Sets the Blue/U and Red/V components of white balance.", "", &Bumblebee2Config::whitebalance)));
//#line 255 "/opt/ros/boxturtle/stacks/driver_common/dynamic_reconfigure/templates/ConfigType.h"
      
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        __description_message__.parameters.push_back(**i);
      __max__.__toMessage__(__description_message__.max); 
      __min__.__toMessage__(__description_message__.min); 
      __default__.__toMessage__(__description_message__.dflt); 
      
      __initialized__ = true;
    }
  };

  bool Bumblebee2Config::__initialized__ = false;
  boost::mutex Bumblebee2Config::__init_mutex__;
  std::vector<Bumblebee2Config::AbstractParamDescriptionConstPtr> Bumblebee2Config::__param_descriptions__;
  Bumblebee2Config Bumblebee2Config::__max__;
  Bumblebee2Config Bumblebee2Config::__min__;
  Bumblebee2Config Bumblebee2Config::__default__;
  dynamic_reconfigure::ConfigDescription Bumblebee2Config::__description_message__;
  
  
  template <> // Max and min are ignored for strings.
  void Bumblebee2Config::ParamDescription<std::string>::clamp(Bumblebee2Config &config, const Bumblebee2Config &max, const Bumblebee2Config &min) const
  {
    return;
  }


}
    

#endif // __BUMBLEBEE2RECONFIGURATOR_H__
