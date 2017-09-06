#ifndef QVICKYFIX_FIXWRITER_H
#define QVICKYFIX_FIXWRITER_H

#include <iostream>
#include <iomanip>

namespace QvickyFix
{
    template <typename FIELD>
    class FIXWriter
    {
    public:

        FIXWriter()
        {
            std::cout << std::left << std::setw(15) << "TAG" << std::setw(30) << "VALUE"
                      << std::setw(20) << "FIELD" << std::setw(15) << "DESCRIPTION" << std::endl;
            std::string line(100, '-');
            std::cout << line.c_str() << std::endl;
         }

        ~FIXWriter()
        {
        };

        void operator ()(const std::string& val, const FIELD&& field)
        {
            std::string enumVal;
            auto itr = field.fixEnumFields_.find(val);
            if(itr != field.fixEnumFields_.end())
                enumVal = itr->second;

            std::cout << std::left << std::setw(15) << field.fieldTag_<< std::setw(30) << val
                    << std::setw(20) << field.fieldName_ << std::setw(15) << enumVal << std::endl;
            std::string line(100, '-');
            std::cout << line.c_str() << std::endl;
        }
    };
}


#endif //QVICKYFIX_FIXWRITER_H
