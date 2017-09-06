#ifndef QVICKYFIX_FIXSPECMANAGER_H
#define QVICKYFIX_FIXSPECMANAGER_H

#include <iostream>
#include <pugixml.hpp>
#include <memory>
#include "FIXFieldStore.h"
#include "FIXParser.h"
#include "FIXWriter.h"

namespace QvickyFix
{
    class FIXSpecManager
    {
    public:
        enum class FIXVersion
        {
            FIX42 = 42,
            FIX43 = 43,
            FIX44 = 44,
            FIX50 = 50
        };

        FIXSpecManager()  = default;
        ~FIXSpecManager() = default;

        void loadFields()
        {
            for(pugi::xml_node child = docPtr_->child("fix").child("fields").first_child(); child; child = child.next_sibling())
            {
                QvickyFix::FIXField field(std::stoi(child.attribute("number").value()),
                                          child.attribute("name").value(),
                                          child.attribute("type").value());

                for (pugi::xml_node value = child.first_child(); value; value = value.next_sibling())
                {
                    field.fixEnumFields_[value.attribute("enum").value()] = value.attribute("description").value();
                }

                fieldStorePtr_->insert(std::move(field));
            }
        }

        void load(FIXVersion version)
        {
            //TODO : Change to strategy Or Factory Method
            if(version == FIXVersion::FIX42)
            {
                fieldStorePtr_.reset(new QvickyFix::FIXFieldStore());

                //TODO : Read from config file later
                docPtr_ = std::make_shared<pugi::xml_document>();

                if(docPtr_->load_file("/home/vikram/vikram/gitrepo/study/cpp/QvickyFix/spec/FIX42.xml"))
                {
                    loadFields();
                }
                else
                {
                    throw std::runtime_error("Not able to load the spec file");
                }
            }
        }

        void prettyPrint(const std::string& msg)
        {
            FIXParser parser(msg);
            FIXWriter<QvickyFix::FIXField> writer;

            auto tokens = parser();

            for(const auto &token : tokens)
            {
                //std::cout << token << std::endl;
                auto found = token.find("=");

                if(found != std::string::npos)
                {
                    std::string tag   = token.substr(0, found);
                    std::string value = token.substr(found + 1);

                    //std::cout << tag <<"," << value  << std::endl;

                    const auto field = fieldStorePtr_->getFieldData(std::stoi(tag));
                    writer(std::move(value), std::move(field));
                }
            }
        }

    private:
        std::shared_ptr<pugi::xml_document> docPtr_;
        QvickyFix::FIXFieldStorePtr fieldStorePtr_;
    };
}


#endif //QVICKYFIX_FIXSPECMANAGER_H
