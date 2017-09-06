#ifndef QVICKYFIX_FIXFIELDSTORE_H
#define QVICKYFIX_FIXFIELDSTORE_H

#include <FIXField.h>
#include <memory>
#include <iostream>

namespace QvickyFix
{

    class FIXFieldStore
    {
    public:

        using FIXFieldsDictionary = std::map<int, QvickyFix::FIXField>;

        FIXFieldStore()  = default;
        ~FIXFieldStore() = default;

        void insert(const QvickyFix::FIXField& field)
        {
            fields_.insert(std::make_pair(field.fieldTag_, field));
        }

        void insert(const QvickyFix::FIXField&& field)
        {
            fields_.insert(std::make_pair(field.fieldTag_, field));
        }

        QvickyFix::FIXField getFieldData(int tag)
        {
            auto found = fields_.find(tag);
            if(found != fields_.end())
                return QvickyFix::FIXField(found->second);
            else
                return QvickyFix::FIXField();
        }

    private:
        FIXFieldsDictionary fields_;
    };

    using FIXFieldStorePtr = std::unique_ptr<FIXFieldStore>;
}


#endif //QVICKYFIX_FIXFIELDSTORE_H
