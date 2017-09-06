#ifndef QVICKYFIX_FIXFIELD_H
#define QVICKYFIX_FIXFIELD_H

#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>


namespace QvickyFix
{
    struct FIXField
    {
    public:
        using FixEnumFieldsMap    = std::map<std::string, std::string>;
        using FixEnumFieldsMapItr = FixEnumFieldsMap::iterator;

        FIXField()  = default;
        ~FIXField() = default;

        FIXField(int tag, const std::string fieldName, const std::string fieldType)
            : fieldTag_(tag)
            , fieldName_(std::move(fieldName))
            , fieldType_(std::move(fieldType))
        {
        }

        friend std::ostream& operator << (std::ostream& out, const FIXField& obj);


        int fieldTag_;
        std::string fieldName_;
        std::string fieldType_;

        FixEnumFieldsMap fixEnumFields_;
    };

    std::ostream& operator << (std::ostream& out, const FIXField& obj)
    {
        out   << obj.fieldTag_  << " "
              << obj.fieldName_ << " "
              << obj.fieldType_ << " " << std::endl;

        std::for_each(std::begin(obj.fixEnumFields_), std::end(obj.fixEnumFields_),
                      [](QvickyFix::FIXField::FixEnumFieldsMap::value_type fixTagValPair)
                      {
                          std::cout << "\t" << fixTagValPair.first << " " << fixTagValPair.second << std::endl;
                      });
        return out;
    }
}


#endif //QVICKYFIX_FIXFIELD_H
