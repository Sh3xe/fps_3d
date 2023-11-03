#include "config.hpp"
#include "utils.hpp"
#include "core/logger.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

static bool check_stream( std::stringstream &ss, const std::string &type, uint32_t line)
{
	if(ss.fail())
	{
		VV_WARN("Config loading: invalid type at line ", line, " should be of type ", type);
		return false;
	}
	return true;
}

Config::Config( const std::string &path )
{
	parse(path);
}

void Config::parse( const std::string &path )
{
	std::ifstream file { "../" + path };

	if(!file)
	{
		m_is_valid = false;
		return;
	}

	std::string line;
	uint32_t i = 0;
	while( std::getline(file, line) )
	{
		++i;
		if( line.size() < 3 )
		{
			VV_WARN("Config loading: line size < 3, skipping line ", i);
			continue;
		}

		// getting the index of the equal symbol
		size_t equ_index = line.find_first_of('=');
		if( equ_index == std::string::npos )
		{
			VV_WARN("Config loading: no '=' sign, skipping line ", i);
			continue;
		}

		std::string
			name = line.substr(2, equ_index - 2),
			value = line.substr(equ_index+1);

		value = vv::trim(value);
		name = vv::trim(name);

		// conversion
		char type = line[0];

		std::stringstream ss(value);

		switch( type )
		{
			case 'i':
			{
				int val = 0;
				ss >> val;
				if(check_stream(ss, "INT", i))
					m_int_data.emplace(name, val);
				break;
			}
			case 'f':
			{
				float val = 0.0f;
				ss >> val;
				if(check_stream(ss, "FLOAT", i))
					m_float_data.emplace(name, val);
				break;
			}
			case 's':
			{
				m_str_data.emplace(name, value);
				break;
			}
			default: break;
		}

		// VV_DEBUG(name, value);
	}
}

float Config::get_float( const std::string &name )
{
	return m_float_data.at(name);
}

bool Config::get_bool( const std::string &name )
{
	return m_int_data.at(name) >= 1;
}

int Config::get_int( const std::string &name )
{
	return m_int_data.at(name);
}

std::string Config::get_str( const std::string &name )
{
	return m_str_data.at(name);
}