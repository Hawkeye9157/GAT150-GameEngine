#include "Json.h"
#include "EFile.h"
#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace Json {
    
    bool Load(const std::string& filename, rapidjson::Document& doc) {

        std::string buffer;
        if (!File::readFile(filename, buffer)) {
            return false;
        }
        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        doc.ParseStream(istream);
        if (!doc.IsObject()) {
            std::cerr << "Could not parse JSON:" << filename << std::endl;
            return false;
        }

        return true;
    }
    
    bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        if (!value.HasMember(name.c_str())) {
            std::cerr << "Could not read JSON value: " << name << std::endl;
            return false;
        }
        if (!value[name.c_str()].IsInt()) {
            std::cerr << "Invalid type: " << name << std::endl;
            return false;
        }
        data = value[name.c_str()].GetInt();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, float& data)
    {
        if (!value.HasMember(name.c_str())) {
            std::cerr << "Could not read JSON value: " << name << std::endl;
            return false;
        }
        if (!value[name.c_str()].IsFloat()) {
            std::cerr << "Invalid type: " << name << std::endl;
            return false;
        }
        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        if (!value.HasMember(name.c_str())) {
            std::cerr << "Could not read JSON value: " << name << std::endl;
            return false;
        }
        if (!value[name.c_str()].IsBool()) {
            std::cerr << "Invalid type: " << name << std::endl;
            return false;
        }
        data = value[name.c_str()].GetBool();
        return true;
    }
    
    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        if (!value.HasMember(name.c_str())) {
            std::cerr << "Could not read JSON value: " << name << std::endl;
            return false;
        }
        if (!value[name.c_str()].IsString()) {
            std::cerr << "Invalid type: " << name << std::endl;
            return false;
        }
        data = value[name.c_str()].GetString();
        return true;
    }
    
    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
    
    bool Read(const rapidjson::Value& value, const std::string& name, Color& data)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
}

